#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void Func1(int);
void Func2(int);

int main()
{
(void) signal(SIGINT,Func1);
while(1)
{
printf("Hello World !\n");
sleep(1);
}
}

void Func1(int sig)
{
printf("Function1\n");
sleep(1);
(void) signal(SIGINT,Func2);
kill(getpid(),SIGINT);
}

void Func2(int sig)
{
printf("Function2\n");
sleep(1);
(void) signal(SIGINT,Func1);
kill(getpid(),SIGINT);
}
