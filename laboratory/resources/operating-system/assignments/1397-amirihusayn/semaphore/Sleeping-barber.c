#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>

sem_t mutex;
sem_t barberReady;
sem_t customerReady;

int numberOfFreeChairs = 5;

void Enter()
{
    printf("----->>> customer enterd !\n");   
    // barber woke up when customer enters :
    if(numberOfFreeChairs == 5)
    {
        printf("Barber just woke up !\n");
        sem_post(&barberReady);
    }
}
void Wait()
{
    printf("customer added to waiting Queue\n");
}
void Left()
{
    printf("BarberShop is full ! customer left . . .\n");   
}
void Next()
{
    printf("customer sat on barber chair\n");
}
void CutHair()
{
    printf("Cut hair done ! #########################\n");
}
void BarberSleep()
{
    printf("Barber asleep ! ZzZ ZzZ ZzZ zZz ZZz\n");
}



void *Customer(void *arg)
{
    while(1)
    {
        sem_wait(&mutex);
        Enter();
        if(numberOfFreeChairs>0)
        {
            numberOfFreeChairs--;
            // Customer is ready and added to Queue :
            sem_post(&customerReady);
            Wait();
            sem_post(&mutex);
            // Customer is waiting for barber to be ready to cut hair :
            sem_wait(&barberReady);
        }
        else
        {
            Left();
            sem_post(&mutex);
        }
        sleep(1);
    }
}

void *Barber(void *arg)
{
    while(1)
    {
        // Barber is working one by one :
        sem_wait(&customerReady);
        if(numberOfFreeChairs < 5)
        {
            sem_wait(&mutex);
            numberOfFreeChairs++;
            Next();
            // Barber is ready for cuting hair :
            sem_post(&barberReady);
            sem_post(&mutex); 
            CutHair();          
        }
        else
            BarberSleep();
        sleep(1);
    }
}

int main()
{

    sem_init(&mutex,0,1);
    sem_init(&barberReady,0,1);
    sem_init(&customerReady,0,1);


    pthread_t t1,t2;
    pthread_create(&t1,NULL,Customer,NULL);
    sleep(2);
    pthread_create(&t2,NULL,Barber,NULL);


    pthread_join(t1,NULL);
    pthread_join(t2,NULL);


    sem_destroy(&mutex);
    sem_destroy(&barberReady);
    sem_destroy(&customerReady);
    return(0);
}
