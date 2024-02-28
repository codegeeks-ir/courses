#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

int main()
{
    pid_t pid;
    char *message;
    int n;
    int exit_code;

    printf("fork program starting\n");
    pid = fork();
    switch(pid)
    {
        case -1:
        perror("fork faild");
        exit(1);

        case 0:
        message ="This is child";
        n=5;
        exit_code = 37;
        break;

        default:
        message ="This is parent";
        n=100;
        exit_code = 0;
        break;
    }
    for(;n>0;n--)
    {
        puts(message);
        sleep(1);
    }
}