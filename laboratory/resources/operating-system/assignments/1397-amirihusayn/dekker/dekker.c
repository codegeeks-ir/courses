#include <stdio.h>
#include <stdbool.h>
#include <sys/types.h>

bool flag[2];
int turn;
pid_t pid;

void process();
void dekker();

void main()
{   
    dekker();
}

void process()
{
        if(pid == 0)
    {
        flag[0]=true;

        while(flag[1])
        {
            if(turn != 0)
            {
                flag[0]=false;
                // Child process busy waiting :
                while(turn != 0)
                    printf("!!! P0 waits...\n");
                flag[0]=true;
            }
        }
        // Child process critical section :
        printf("*** P0 : critical section done\n");

        flag[0] = false;
        turn = 1;
    }
    else
    {
        flag[1]=true;

        while(flag[0])
        {
            if(turn != 1)
            {
                flag[1]=false;
                // Child process busy waiting :
                while(turn != 1)
                    printf("!!! P1 waits...\n");
                flag[1]=true;
            }
        }
        // Child process critical section :
        printf("*** P1 : critical section done\n");

        flag[1] = false;
        turn = 0;
    }
}
void dekker()
{
    printf("\nDekker :\n");

    flag[0]=false;
    flag[1]=false;
    turn=0;
    pid = fork();
    while(1)
        process();
}


