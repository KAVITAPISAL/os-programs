#include<stdio.h>
#include<stdbool.h>
void acceptAvailable(int available[],int n);
void displayAllocationMax(int allocation[][3],int max[][3],int n);
void displayNeed(int need[][3],int n);
void displayAvailable(int available[3],int n);

void bankersAlgo(int available[3],int need[][3],int n);
int main()
{
    int allocation[5][3]={{0,1,0},{2,0,0},{3,0,2},{2,1,1},{0,0,2}};
    int max[5][3]={{7,5,3},{3,2,2},{9,0,2},{2,2,2},{4,3,3}};
    int available[3];
    int need[5][3];
    int choice,n=5;

    //calculate need of matrix

    for(int i=0;i<n;i++)
    {
        for(int j=0;j<3;j++)
        {
            need[i][j]=max[i][j]-allocation[i][j];
        }


    }
    acceptAvailable(available,3);
    displayAllocationMax(allocation,max,n);
    displayNeed(need,n);
    displayAvailable(available,3);  

    bankersAlgo(available,need,n);


    /*
    do
    {
        
        printf("1. accept avaialbe\n");
        printf("2.display allocation and max\n");
        printf("3.display  need\n");
        printf("4.display  available\n");
        printf("5.bankers algo\n");
        printf("6.exit \n");
        printf("Enter choice: \n ");
        scanf("%d",&choice);

        switch (choice)
        {
        case 1:
            acceptAvailable(available,3);
            break;
        case 2:
            displayAllocationMax(allocation,max,n);    
            break;
        case 3:
            displayNeed(need,n);
            break;    
        case 4:
            displayAvailable(available,3);    
            break;
        case 5:
            displayAvailable(available,3);    
            break;    
        default:
            printf("Invalid choice..\n");
        }
    } while (choice != 5);
    */
    return 0;

    
}

void acceptAvailable(int available[],int n)
{
    printf("enter the available resources for A,B,C : ");
    for(int i=0;i<n;i++)
    {
        
        scanf("%d",&available[i]);
        
    }
}

void displayAllocationMax(int allocation[][3],int max[][3],int n)
{
    printf("allocation matrix : \n");
    for(int i=0;i<n;i++)
    {
        printf("P%d\t",i);
        for(int j=0;j<3;j++)
        {
            printf("%d ",allocation[i][j]);
            ///printf("%d ", max[i][j]);
        }
        printf("\n");
    }

    printf("max matrix : \n");
    for(int i=0;i<n;i++)
    {
        printf("P%d\t",i);
        for(int j=0;j<3;j++)
        {
            //printf("%d ",allocation[i][j]);
            printf("%d ", max[i][j]);
        }
        printf("\n");
    }

}

void displayNeed(int need[][3],int n)
{

    printf("need of matrix \n");
    for (int i = 0; i < n; i++)
    {
        printf("P%d\t",i);
        /* code */
        for (int j = 0; j < 3; j++)
        {
            /* code */

            printf("%d ",need[i][j]);

        }
        printf("\n");
        
    }
}

void displayAvailable(int available[3],int n)
{
    printf("available resources matrix:\n");
    
    for(int i=0;i<n;i++)
    {       
        printf("%d ",available[i]);
        
    }
    printf("\n");
}


void bankersAlgo(int available[3],int need[][3],int n)
{
    int pcount=n;
    int rcount=3;
    int safeSequence[pcount]; 
    int finish[pcount];
    int count=0;
    int work[pcount];
    int i,j,k;
    for (int i = 0; i < pcount; i++) {
        finish[i] = 0;
    }
    for(i=0;i<pcount;i++)
    {
            /* code */
        work[i]=available[i];
    
    }

    while(count<pcount)
    {
        printf("%d",pcount);
        bool found=false; // to check if sequence is in safe state or not
        for(i=0;i<pcount;i++)
        {
           
            if(finish[i]==0) 
            // check i=till all finish[i] should be 1
            {
                 printf("%d",finish[i]);
                bool canProcess=true;
                
                for(j=0;j<rcount;j++)
                {
                    if(need[i][j]>work[j])
                    {
                        canProcess=false;
                        break;
                    }
                    
                }
                
                if(canProcess)
                {
                    for(k=0;k<rcount;k++)
                    {
                        work[k]+=available[k];
                    }
                    safeSequence[count++]=i;
                    finish[i]=1;
                    found=true;
                }
                
            }
        }
        if(!found)
        {
            printf("System is not in safe state. \n");
            return false;
        }
    
        
    }

    printf("System is in a safe state.\nSafe sequence is: ");
    for (i = 0; i < pcount; i++) {
        printf("P%d ", safeSequence[i]);
    }
    printf("\n");

    return true;
}


