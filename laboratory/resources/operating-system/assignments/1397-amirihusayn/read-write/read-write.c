#include <stdio.h>
#include <unistd.h>
#include <signal.h>


void readFunc(int);
void writeFunc(int);

int main()
{
    (void) signal (SIGINT,writeFunc);
    kill(getpid(),SIGINT);
}

void writeFunc(int sig)
{
    FILE *filePointer;
    filePointer = fopen("file.txt","w");

    fprintf(filePointer,"%s","I wrote this ...");

    filePointer = fclose(filePointer);
    (void) signal (SIGINT,readFunc);
    kill(getpid(),SIGINT);
}

void readFunc(int sig)
{
    char ch;
    FILE *filePointer;
    filePointer = fopen("file.txt","r");

    while((ch = fgetc(filePointer))!=EOF)
    {
        printf("%c",ch);
    }

    filePointer = fclose(filePointer);
    kill(getpid(),SIGINT);
}
