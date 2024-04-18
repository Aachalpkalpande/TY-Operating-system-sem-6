#include <stdio.h>
#include<stdlib.h>
int *alloc[10], *max[10], *need[10];
int *avail, *finish;

void display(int *a[10],int n,int r)
{
    int i,j;
    for(i=0;i<n;i++)
    {
        for(j=0;j<r;j++)
        {
            printf("%d\t",a[i][j]);
        }
        printf("\n");
    }
}
int main()
{
   int n,r,i,j,k,p=0;
   
   printf("Enter number of processes : ");
   scanf("%d",&n);

   printf("Enter number of Resources : ");
   scanf("%d",&r);

   int ans[n];
   finish=(int*)malloc(n*sizeof(int));
   for(i=0;i<n;i++)
    {
        finish[i]=0;
    }
    
    printf("\n\nenter allocation matrix:");
    for(i=0;i<n;i++)
    {
        alloc[i]=(int*)malloc(r*sizeof(int));
        printf("\nenter resources allocated to process P%d",i+1);
        for(j=0;j<r;j++)
        {
            printf("\nEnter resource no. %d: ",j+1);
            scanf("%d",&alloc[i][j]);
        }
    }
    
    
    printf("\n\nenter Max matrix:");
    for(i=0;i<n;i++)
    {
        max[i]=(int*)malloc(r*sizeof(int));
        printf("\nenter resources of process P%d",i+1);
        for(j=0;j<r;j++)
        {
            printf("\nEnter resource no. %d: ",j+1);
            scanf("%d",&max[i][j]);
        }
    }
      
    printf("\nEnter the available matrix: "); 
    avail=(int*)malloc(r *sizeof(int));
   for(i=0;i<r;i++)
    {
        printf("\nEnter resource no. %d: ",i+1);
        scanf("%d",&avail[i]);
    }
    
     for(i=0;i<n;i++)
    {
        need[i]=(int*)malloc(r*sizeof(int));
        
        for(j=0;j<r;j++)
        {
            need[i][j]=max[i][j]-alloc[i][j];
            
        }
    }
    printf("Allocation matrix:\n");
    display(alloc,n,r);
   printf("max matrix:\n");
   display(max,n,r);
   printf("need matrix:\n");
   display(need,n,r);
    
    for(k=0;k<n;k++)
    {
        for(i=0;i<n;i++)
        {
            if(finish[i]==0)
            {
                int flag=0;
                for(j=0;j<r;j++)
                {
                    if(need[i][j]>avail[j])
                    {
                        flag=1;
                        break;
                    }
                   }
                
                
            
            int q;
            if(flag==0)
            {
                ans[p++]=i+1;
                for(q=0;q<r;q++)
                
                {
                        avail[q]=avail[q]+alloc[i][q];
                }
                
                finish[i]=1;
                
             }
             
           }
        }
    }
    
    int flag=0;
    for(i=0;i<n;i++)
    {
        if(finish[i]==0)
        {
            flag=1;
        }        
   }
   
   if(flag==1)
        printf("\nSystem is not in safe state");
    
    if(flag==0)
    {
        printf("\nSystem is in safe state and safe sequence is: ");
        for(i=0;i<n-1;i++)
            printf("P%d->",ans[i]);
        printf("P%d",ans[n-1]);
        
    }
    printf("\n\n");
            
        
}
