#include <stdio.h>
#include <stdbool.h>
#include <sys/types.h>

bool flag[2];
int turn;
pid_t pid;

void process();
void piterson();

void main()
{   
    piterson();
}

void process()
{
    if(pid==0)
    {
        flag[0] = true;
        turn = 0;
        // Child process busy waiting :
        while(flag[1] && turn==0)
            printf("!!! P0 waits...\n");
        // Child process critical section :
        printf("*** P0 : critical section done\n");
        flag[0]=false;
    }
    else
    {
        flag[1] = true;
        turn = 1;
        // Parent process busy waiting :
        while(flag[0] && turn==1)
            printf("!!! P1 waits...\n");
        // Parent process critical section :
        printf("*** P1 : critical section done\n");
        flag[1]=false;
    }
}
void piterson()
{
    printf("\nPiterson :\n");

    flag[0]=false;
    flag[1]=false;
    
    pid = fork();
    while(1)
        process();
}


