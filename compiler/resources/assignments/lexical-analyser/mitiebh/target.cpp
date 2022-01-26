#include <iostream>
#include "simpdata.h"
using namespace std;
int main()
{
    /* main function */ 
    std::cout << "helllo" << endl;
    int doble = 25.362;
    double num= 2.2636;
    int div = doble/num;
    if (num >= 5)
        std::cout << 'G' << "text";
    /*this is 
    a multiline 
    comment*/
    else
    {
        int m;
        std::cin >> m;
        (m>10) ? true : false;
    }
    char a = 'a';
    // this is a singleline comment
    int b =5;
    return 0;
}
