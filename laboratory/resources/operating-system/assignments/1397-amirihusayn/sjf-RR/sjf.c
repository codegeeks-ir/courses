#include<stdio.h>

int processList[20] = {2,5,13,14,7,6,9,3,8,1,3,4,5,6,7,3,4,1,2,7};
void sjf();

int main()
{
    for(int i =0 ; i<=19 ; i++)
    {
        printf("P%d:",i);
        printf("has %d process time. \n",processList[i]);
    }
    printf("############################\n");
    sjf();
}

void sjf()
{
    printf("************ SJF :\n");

    // Finds longest process : 
    int longest = processList[0];
    for(int i =1; i<20 ; i++)
        if(processList[i] > longest)
            longest = processList[i];

    int shortest = processList[0];
    int indexOfShortest = 0;

    for(int round=0; round < 20; round++)
    {
        for(int i =0; i<20 ; i++)
            if(processList[i] != -1)
                if(processList[i] <= shortest)
                {
                    shortest = processList[i];
                    indexOfShortest = i;
                }

        processList[indexOfShortest] = -1;
        shortest = longest;

        printf("P%d:",indexOfShortest);
        printf("Done ! \n");
    }   

}