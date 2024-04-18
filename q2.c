#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct node
{
	int pid,at,bt,ct,st,tt,wt;
};

int gant_chart[10];

void accept(struct node p[],int n)
{
	int i,flag;
	
	for(i=0;i<n;i++)
	{
		printf("\n\nFor Process P%d : \n",i);
		do
		{
			printf("Enter Arrival Time : ");
			scanf("%d",&p[i].at);
			if(p[i].at < 0) 
			{
				 printf("\nInvalid input!!!\n");
			}
		}while(p[i].at < 0);

		 do
                {
                        printf("Enter Burst Time : ");
                        scanf("%d",&p[i].bt);
                        if(p[i].bt < 0)
                        {
                                 printf("\nInvalid input!!!\n");
                        }
                }while(p[i].bt < 0);

		p[i].pid =i;

	}
}

void sort(struct node p[],int n)
{
	int i,j;
	struct node temp;
	for(i=0;i<n;i++)
	{
		for(j=0;j<n-i-1;j++)
		{
			if(p[j].at > p[j+1].at)
			{
				temp=p[j];
				p[j]=p[j+1];
				p[j+1]=temp;
			}
		}
	}
}

void sjf(struct node p[],int n)
{
	int c_t=0,minbt,id,n1=0,i,j=0,completed[10]={0};

	while(n1!=n)
	{
		minbt=1000;
		id=-1;

		for(i=0;i<n;i++)
		{
			if(completed[i]==0 && p[i].at <=c_t && p[i].bt <  minbt)
			{
				minbt=p[i].bt;
				id=i;
			}
		}
		if(id>=0)
		{
			p[id].st=c_t;
			p[id].ct = c_t + p[id].bt;
			p[id].tt = p[id].ct - p[id].at;
			p[id].wt = p[id].st - p[id].at;

			completed[id] = 1;

			c_t=c_t+p[id].bt;
			n1++;

			gant_chart[j]=id;
			j++;
		}
		else
		{
			c_t++;
		}
	}
}

void display(struct node p[],int n)
{
	int i=0;
	float avgtt=0.0;
	float avgwt=0.0;

	printf("\n\n table : \nprocess\tAT\tBT\tST\tCT\tTT\tWT\n");

	for(i=0;i<n;i++)
	{
		printf("\n P%d \t%d \t %d \t %d \t %d \t %d \t %d",p[i].pid,p[i].at,p[i].bt,p[i].st,p[i].ct,p[i].tt,p[i].wt);

		avgtt+=p[i].tt;
		avgwt+=p[i].wt;
	}

	printf("\n\nGantt Chart is : \n");

//	for(int i=0;i<n;i++)
//	{
//		printf("\n %d-----p%d-----%d",p[gant_chart[i]].st,p[gant_chart[i]].pid,p[gant_chart[i]].ct);
//	}
	printf("\n");
	for(int i=0;i<n;i++)
	{
		printf("P%d | ",i);
	}
	printf("\n-------------------------------------------------------------\n0  ");
	 for(int i=0;i<n;i++)
        {
	
                	printf("%d   ",p[gant_chart[i]].ct);
        }


	printf("\n\nAverage TAT : %.2f",avgtt/n);
	 printf("\nAverage WT : %.2f",avgwt/n);
	 printf("\n");


}

int main()
{
	struct node p[10];
	int n;

	do
	{
		printf("\nEnter the number of processes : ");
		scanf("%d",&n);

		if(n<=0)
		{
			printf("\nInvalid number of process!!! Re-enter : ");
		}
	}while(n<=0);

	accept(p,n);
	sort(p,n);
	sjf(p,n);
	display(p,n);

	return 0;
}
