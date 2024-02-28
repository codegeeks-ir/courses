#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

bool flag[2];
int turn = 1;
void *Parent(void *arg);
char message[] = "hello world";

void main()
{
    pthread_t t;
    void *tresult;
    pthread_create(&t,NULL,Parent,(void*)message);

    while(1){
        flag[0] = true;
        turn = 0;
        // Child process busy waiting :
        while(flag[1] && turn==0)
            printf("!!! P0 waits...\n");
        // Child process critical section :
        printf("### P0 : critical section done\n");
        flag[0]=false; 
    }

}

void *Parent(void *arg)
{
    while(1){
        flag[1] = true;
        turn = 1;
        // Parent process busy waiting :
        while(flag[0] && turn==1)
            printf("!!! P1 waits...\n");
        // Parent process critical section :
        printf("### P1 : critical section done\n");
        flag[1]=false;     
    }
}