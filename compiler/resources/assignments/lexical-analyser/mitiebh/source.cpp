// Copyrights, written by mitiebh.
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

char delimiters[10] = {'{','}','(',')',';','.','[',']'};
string operatorarr[30];

ifstream sourcefile("Target.cpp");
ifstream keywordsfile("Keywords.txt");
ifstream operatorsfile("Operators.txt");
ofstream outputfile("Output.txt");

struct Token
{
    string name = "";
    string tokenType = "";
    int rowNo = 0;
    int colNo = 0;
    int blockNo = 0;
}token;

void initToken(string name, string type, int row, int col, int block)
{
    token.name = name;
    token.tokenType = type;
    token.rowNo = row;
    token.colNo = col;
    token.blockNo = block;
}
void writetoOutput()
{
    outputfile << "Token------- " << token.name << endl;
    outputfile << "\tType---- " << token.tokenType << endl;
    outputfile << "\tRow----- " << token.rowNo << endl;
    outputfile << "\tCol----- " << token.colNo << endl;
    outputfile << "\tBlock--- " << token.blockNo << endl << endl;
}
bool isdelimiter(char letter) // searching in delimeters array
{
    for (int i = 0; i < 10; i++)
    {
        if (delimiters[i] == letter)
            return true;
    }
    return false;
}
bool isoperator(string word)
{
    for (int i = 0; i < 30; i++) // find the token in operators
    {
        if(operatorarr[i] == word)
            return true;
    }
    return false;
}
int main()
{
    string line ="",tokenname="";
    string keywordsarr[200],sourcearr[200];

    for (int i = 0; i < 30 && !operatorsfile.eof(); i++) // operators array saved
    {
        getline(operatorsfile,line);
        operatorarr[i].append(line);
    }
    for (int i = 0; i < 200 && !keywordsfile.eof(); i++) // keywords array saved
    {
        getline(keywordsfile,line);
        keywordsarr[i].append(line);
    }
    for (int i = 0; i < 200 && !sourcefile.eof(); i++) // source cpp file array line by line stored
    {
        getline(sourcefile,line);
        sourcearr[i].append(line);
    }

    int index_s = 0;
    int sourcearrLength = sizeof(sourcearr)/sizeof(sourcearr[0]);
    while(index_s < sourcearrLength)
    {
        line = sourcearr[index_s];
        int lineindex=0,delindex=0;
        string opword = "";
        while (lineindex < line.length())
        {
            if (line[lineindex] == ' ') //refuse spaces and tabs
            {
                lineindex++;
                continue;
            }
            if (line[lineindex] == '/')
            {
                int commentindexcol = lineindex;
                int commentindexrow = index_s;
                string comment = "";
                comment = line[lineindex];
                commentindexcol++;
                if (line[commentindexcol] == '/') // single line comment
                {
                    comment += line[commentindexcol];
                    commentindexcol++;
                    while (commentindexcol != line.length())
                    {
                        comment += line[commentindexcol];
                        commentindexcol++;
                    }
                    initToken(comment,"comment",index_s,lineindex,token.blockNo);
                    writetoOutput();
                    lineindex += (commentindexcol - lineindex)+1;
                    continue;
                }
                else if (line[commentindexcol] == '*') /* multi line comment recognition */
                {
                    comment += line[commentindexcol];
                    commentindexcol++;
                    string commenttemp = "";
                    while (commentindexrow < sourcearrLength)
                    {
                        while (commentindexcol < line.length())
                        {
                            if (line[commentindexcol] == '*' && line[commentindexcol+1] == '/')
                                break;
                            commenttemp += line[commentindexcol];
                            commentindexcol++;
                        }
                        if (line[commentindexcol] == '*' && line[commentindexcol+1] == '/')
                            break;
                        commentindexrow++;
                        commentindexcol = 0;
                        line = sourcearr[commentindexrow];
                    }
                    comment.append(commenttemp);
                    comment += line[commentindexcol];
                    comment += line[commentindexcol+1];
                    initToken(comment,"comment",index_s,lineindex,token.blockNo);
                    writetoOutput();
                    index_s = commentindexrow;
                    lineindex = commentindexcol+2;
                    continue;
                }
            }
            if(isoperator(string(1,line[lineindex]))) // searching for operator
            {
                int opindex = lineindex;
                opword = line[lineindex];
                opindex++;
                if (isoperator(string(1,line[opindex])))
                {
                    opword += line[opindex];
                    if (isoperator(opword))
                    {
                        initToken(opword,"operator",index_s,lineindex,token.blockNo);
                        writetoOutput();
                        lineindex += (opindex - lineindex)+1;
                        continue;
                    }
                }
                else
                {
                    tokenname = line[lineindex];
                    initToken(tokenname,"operator",index_s,lineindex,token.blockNo);
                    writetoOutput();
                    lineindex++;
                    continue;
                }
            }
            if(isdigit(line[lineindex]) || (line[lineindex] == '.' && isdigit(line[lineindex + 1]))) // recognize constant int or float numbers
            {
                string number = "";
                int numberindex = lineindex;
                number += line[lineindex];
                numberindex++;
                while (isdigit(line[numberindex]) || line[numberindex] == '.')
                {
                    if (isdigit(line[numberindex]))
                    {
                        number += line[numberindex];
                        numberindex++;
                    }
                    else
                    {
                        number += line[numberindex];
                        numberindex++;
                    }
                }
                int floatpoint = 0;
                for (int numindex = 0; numindex < number.length(); numindex++)
                {
                    if (number[numindex] == '.')
                        floatpoint++;
                }
                if(floatpoint == 1)
                {
                    initToken(number,"constant float",index_s,lineindex,token.blockNo);
                    writetoOutput();
                    lineindex += (numberindex - lineindex);
                    continue;
                }
                else if(floatpoint == 0)
                {
                    initToken(number,"costant interger",index_s,lineindex,token.blockNo);
                    writetoOutput();
                    lineindex += (numberindex - lineindex);
                    continue;
                }
                else if (floatpoint > 1)
                {
                    initToken(number,"invalid float - ERROR",index_s,lineindex,token.blockNo);
                    writetoOutput();
                    lineindex += (numberindex - lineindex);
                    continue;
                }
            }
            if (isdelimiter(line[lineindex])) // searching for delimeter in it's function
            {
                if(line[lineindex] == '{')
                    token.blockNo++;
                if(line[lineindex] == '}')
                    token.blockNo--;
                tokenname = line[lineindex];
                initToken(tokenname,"delimiter",index_s,lineindex,token.blockNo);
                writetoOutput();
                lineindex++;
                continue;
            }
            if (line[lineindex] == '"' || string(1,line[lineindex]) == "'") // string and char constant
            {
                string stringconst = "";
                int stringindex = lineindex;
                stringconst = line[lineindex];
                stringindex++;
                if (line[lineindex] == '"')
                {
                    while (line[stringindex] != '"')
                    {
                        stringconst += line[stringindex];
                        stringindex++;
                    }
                    stringconst += line[stringindex];
                    initToken(stringconst,"constant string",index_s,lineindex,token.blockNo);
                    writetoOutput();
                    lineindex += (stringindex - lineindex)+1;
                    continue;
                }
                else
                {
                    while (string(1,line[stringindex]) != "'")
                    {
                        stringconst += line[stringindex];
                        stringindex++;
                    }
                    stringconst += line[stringindex];
                    initToken(stringconst,"constant char",index_s,lineindex,token.blockNo);
                    writetoOutput();
                    lineindex += (stringindex - lineindex)+1;
                    continue;
                }
            }
            if(isalpha(line[lineindex]) || line[lineindex] == '#' || line[lineindex] == '_') // recognize keyword or identifier word
            {
                bool foundkeyword = false;
                int wordindex = lineindex;
                string word = "",wordtemp = "";
                foundkeyword = false;
                while (isalpha(line[wordindex]) || line[wordindex] == '_' || isdigit(line[wordindex]))
                {
                    word += line[wordindex];
                    wordindex++;
                }
                int index_k=0;
                while (keywordsarr[index_k] != "")
                {
                    wordtemp = keywordsarr[index_k];
                    if (wordtemp == word) // find the word in keywords
                    {
                        initToken(word,"keyword",index_s,lineindex,token.blockNo);
                        writetoOutput();
                        lineindex += (wordindex - lineindex);
                        foundkeyword = true;
                        break;
                    }
                    else
                    {
                        index_k++;
                        continue;
                    }
                }
                if (foundkeyword == false && word.length() > 0)
                {
                    initToken(word,"identifier",index_s,lineindex,token.blockNo);
                    writetoOutput();
                    lineindex += (wordindex - lineindex);
                    continue;
                }
            }
            lineindex++;
        }
        index_s++;
        token.rowNo++;
        token.colNo=0;
    }
    sourcefile.close();
    keywordsfile.close();
    operatorsfile.close();
    outputfile.close();
    cout << "Check the Output.txt file";
    cin.ignore();
}
