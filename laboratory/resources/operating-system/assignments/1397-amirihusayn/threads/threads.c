#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<stdlib.h>
#include<string.h>

int turn=1;

void *function(void *arg);
char message[] = "hello world";

void main()
{
    pthread_t t;
    void *tresult;
    pthread_create(&t,NULL,function,(void*)message);

    while(1)
    {
        if(turn==1)
        {
            printf("1");
            turn = 2;
        }
    }
}

void *function(void *arg)
    {
    while(1)
    {
        if(turn==2)
        {
            printf("2");
            turn = 1;
        }
    }
}