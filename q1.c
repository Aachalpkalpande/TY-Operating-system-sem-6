#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct process
{
	int pid;
    int bt;
	int at;
    int st;
    int ct;
    int tt;
    int wt;
    struct process *next;
} process;


process *head=NULL;

void main()
{

    process *newnode, *current;
	int atime;
	int i,id,n,btime;

	printf("Enter number of processes: ");
	scanf("%d",&n);

	for(i=0;i<n;i++)
	{
		newnode=(process*)malloc(sizeof(process));

        id=i+1;
        printf("\nFor P%d :",id);
		newnode->pid=id;

		printf("\nEnter the Arrival time: ");
		scanf("%d",&atime);

		newnode->at=atime;

		printf("\nEnter the Burst time: ");
		scanf("%d",&btime);

		newnode->bt=btime;
		newnode->next=NULL;

		if(head==NULL)
		{
			head=current=newnode;
		}
		else
		{
			current=head;
			while(current->next!=NULL)
			{
				current=current->next;
			}
			current->next=newnode;
		}
		
	}
/*
	printf("\nBefore sorting the process \n");
	printf("\nProcess ID\t\t\t Arrival time\t\t\tBurst time");
	current=head;
	while(current!=NULL)
	{
		printf("\n%d\t\t\t\t%d\t\t\t\t%d\t\t\t\t",current->pid,current->at,current->bt);
		current=current->next;
	}
*/
	//Sorting 
	
	int swapped, temp,tmp;

	process *ptr1;
	if(head==NULL)
		return;
	do
	{
		swapped=0;
		ptr1=head;
		while(ptr1->next!=NULL)
		{
			if(ptr1->at > ptr1->next->at)
			{
				         tmp = ptr1->at;
				      ptr1->at = ptr1->next->at;
				ptr1->next->at = tmp;

				temp=ptr1->bt;
                                ptr1->bt=ptr1->next->bt;
                                ptr1->next->bt=temp;

				temp=ptr1->pid;
                                ptr1->pid=ptr1->next->pid;
                                ptr1->next->pid=temp;
		
				swapped=1;
			}
			ptr1=ptr1->next;
		}
	}while(swapped);
/*
	printf("\nAfter sorting the processes\n");

	printf("\nProcess ID\t\t\t Arrival time\t\t\tBurst time");
        current=head;
        while(current!=NULL)
        {
                printf("\n%d\t\t\t\t%d\t\t\t\t%d\t\t\t\t",current->pid,current->at,current->bt);
                current=current->next;
        }

*/     
//Finding idle time 

	int k=0;
	current=head;
	int idle[50],gnt[50];
	temp=0;
	for(i=0;i<n;i++)
	{
		if(current->at>k)
		{
			idle[i]=current->at-k;
		}
		else
			idle[i]=0;
		gnt[i]=current->bt;
		k=idle[i]+current->bt+k;
		current=current->next;
	}


	printf("\n___________Gantt Chart____________\n|");

	current=head;
	 k=0;

printf("\n------------------------------------------------------------------\n");
    for(i=0;i<n;i++)
    {
        printf("P%d\t|",current->pid);
        current=current->next;
    }
    printf("\n---------------------------------------------------------------\n");


    current=head;
     int s=1;

	for(i=0;i<n;i++)
	{
		if(idle[i]>0)
		{
			//printf("%d\t\t\tIDLE time\t\t\t\%d\n",k,k+idle[i]);
			k=k+idle[i];
			
		}
       
        if(s)
        {
            printf("%d\t",k);
            s=0;
        }
		k=k+gnt[i];
		current->ct=k;
		current->tt=current->ct-current->at;
		current->wt=current->tt-current->bt;
		
		printf("%d\t",k);
		current=current->next;
	}

		printf("\n\n\n________Process Details_________\n");
		printf("\nProcess\t\tAtime\t\tBtime\t\tcompletion time\t\t    Ttime\t\tWtime\t\n");

		current=head;
		float total_wt=0, total_tt=0;
		while(current)
		{
			printf("%d\t\t%d\t\t%d\t\t\t%d\t\t\t%d\t\t%d\n",current->pid,current->at,current->bt,current->ct,current->tt,current->wt);
			total_wt=total_wt+current->wt;
			total_tt=total_tt+current->tt;
			current=current->next;
		}
		printf("\nAverage turnaround time: %.2f \n Average waiting time : %.2f\n",total_tt/n,total_wt/n);

}
