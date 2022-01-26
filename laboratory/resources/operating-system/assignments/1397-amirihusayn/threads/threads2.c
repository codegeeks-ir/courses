#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<stdlib.h>
#include<string.h>

void *func(void *ptr);
pthread_t thread[9];

int *zovj=0;
int *fard=1;
int printer=1;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void main()
{
    int i=0;
    int j=0;

    for( i;i<9;i++)
    {
        if(i%2==0)
            pthread_create(&thread[i],NULL,func,zovj);
        else
            pthread_create(&thread[i],NULL,func,fard);
    }

    for(j;j<9;j++)
    {
        pthread_join(thread[j],NULL);
    }
}

void *func(void *ptr)
{
    if( (printer%2) != 0 )
    {
        printf("%d",printer);
        printf("    ");
        zovj = zovj+2;
        printer++;
    }
    else
    {
        printf("%d\n",printer);
        fard = fard+2;
        printer++;
    }
}