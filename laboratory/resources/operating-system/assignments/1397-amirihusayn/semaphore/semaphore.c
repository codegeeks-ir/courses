#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>

sem_t mutex;
int c=0;
void *Thread(void *arg)
{
    sem_wait(&mutex);
    printf("Entered critical section\n");
    c++;
    printf("%d\n",c);
    sleep(4);
    printf("Exiting critical section\n");
    sem_post(&mutex);
}

int main()
{
    sem_init(&mutex,0,1);
    pthread_t t1,t2;
    pthread_create(&t1,NULL,Thread,NULL);
    sleep(2);
    pthread_create(&t2,NULL,Thread,NULL);
    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    sem_destroy(&mutex);
    return(0);
}