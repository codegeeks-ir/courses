#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>

sem_t mutex;
sem_t fillRooms;
sem_t emptyRooms;

void produce()
{
    sem_wait(&mutex);
    printf("*** Producer is producing !\n");
    sem_post(&mutex);
}

void consume()
{
    sem_wait(&mutex);
    printf("*** Consumer is consuming !\n");
    sem_post(&mutex);
}

void putItemIntoRoom()
{
    printf("### Producer put item into Room\n");
}

void removeItemFromRoom()
{
    printf("### Consumer removed item from Room\n");
}

void *Producer(void *arg)
{
    while(1)
    {
        produce();
        sem_wait(&emptyRooms);
        sem_wait(&mutex);

        putItemIntoRoom();
        sem_post(&fillRooms);
        sem_post(&mutex);
        sleep(1);
    }
}

void *Consumer(void *arg)
{
    while(1)
    {

        sem_wait(&mutex);
        sem_wait(&fillRooms);
        removeItemFromRoom();

        sem_post(&emptyRooms);
        sem_post(&mutex);
        sleep(1);
        consume();
    }
}

int main()
{
    sem_init(&mutex,0,1);
    sem_init(&fillRooms,0,0);
    sem_init(&emptyRooms,0,20);
    pthread_t t1,t2;
    pthread_create(&t1,NULL,Producer,NULL);
    sleep(2);
    pthread_create(&t2,NULL,Consumer,NULL);
    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    sem_destroy(&mutex);
    sem_destroy(&fillRooms);
    sem_destroy(&emptyRooms);
    return(0);
}