#include <stdio.h>
#include <sys/types.h>
#define MAX_COUNT 10

void ChildProcess(void);
void ParentProcess(void);
void main(void)
{
    pid_t pid;

    pid = fork();
    if(pid==0)
        ChildProcess();
    else
        ParentProcess();
}

void ChildProcess(void)
{
    int i;
    for(i=1;i<MAX_COUNT;i++)
        printf("From child, value= %d\n",i);
    printf("   *** child process is done ***\n");
    sleep(1);
}
void ParentProcess(void)
{
    int i;

    for(i=1;i<MAX_COUNT;i++)
        printf("From parent value= %d\n",i);
    printf("   *** parent process is done ***\n");
    sleep(1);
}