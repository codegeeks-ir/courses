#include<stdio.h>

int processList[20] = {2,5,13,14,7,6,9,3,8,1,3,4,5,6,7,3,4,1,2,7};
void RoundRobin(int q);
int main()
{
    for(int i =0 ; i<=19 ; i++)
    {
        printf("P%d:",i);
        printf("has%d process time. \n",processList[i]);
    }
    printf("############################\n");
    RoundRobin(2);
}
void RoundRobin(int q)
{
    // Finds longest process : 
    int longest = processList[0];
    for(int i =1; i<20 ; i++)
        if(processList[i] > longest)
            longest = processList[i];
    

    for(int round=0; round < (longest/q) ;round++)
    {
        printf("*********Round %d :\n",round);
    // Round excecutes :
        for(int i =0 ; i<20 ; i++)
        {
        // Devotes time for process :
            if(processList[i] !=0)
                if(processList[i] > q)
                    processList[i] = processList[i] - q ;
                else
                    processList[i] = 0;

        // Output in this round :
            if(processList[i] == 0)
            {
                printf("P%d:",i);
                printf("Done ! \n");
            }
            else
            {
                printf("P%d:",i);
                printf("%d \n",processList[i]);
            }
        }

        printf("############################\n");
    }
}