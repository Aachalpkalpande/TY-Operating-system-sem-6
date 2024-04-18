#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void ready();
void insertrq(int);
void displayrq();
void gantt();
void insertgantt(int,int,int);
void displaygantt();
void display();
void displaywt();

struct pcb
{
	int pid,at,cbt,pri,wt,tat,comp;
};

struct rq
{
	int pid,at,cbt,pri;
	struct rq *next;
}*rhead,*rtemp,*rnew;

struct gchart
{
	int pid,start,finish;
	struct gchart *next;
}*head,*temp,*new,*cur;

int nop,count=-1,iflag=0,pr=-1,time=0;
struct pcb *p;
float avgwt=0,avgtat=0;

void main()
{
	int at,i,ch1,flag;
	char ch;
	head = (struct gchart*)malloc(sizeof(struct gchart));
	head->next = NULL;
	rhead = (struct rq*)malloc(sizeof(struct rq));
	rhead->next = NULL;
	do{
	printf("\n How Many Processes : ");
	scanf("%d",&nop);
	if(nop<=0)
		printf("\n Invalid Number of processes !!!");
	}while(nop<=0);
	p = (struct pcb*)malloc(nop*sizeof(struct pcb));
	do{
	printf("\n Does All Process Arrive At Same Time? (y/n) : ");
	scanf(" %c",&ch);
	if(ch == 'y')
	{
		printf("For Process P%d :\n",i);

		do{
		printf("\n Enter Arrival Time : ");
		scanf("%d",&at);
		if(at<0)
			printf("\n Invalid Arrival Time !!! \n");
		}while(at<0);
		for(i=0;i<nop;i++)
		{
			do{
			printf(" Enter Burst time : ");
			scanf("%d",&p[i].cbt);
			if(p[i].cbt<=0)
				printf(" Invalid CBT !!!");
			}while(p[i].cbt<=0);
			do{
			printf(" Enter Priority : ");
			scanf("%d",&p[i].pri);

			if(p[i].pri<=0)
				printf(" Invalid Priority !!!");
			}while(p[i].pri<=0);
			p[i].at = at;
			p[i].pid = i;	
		}
		flag = 0;
	}
	else if(ch == 'n')	
	{

		for(i=0;i<nop;i++)
		{
			 printf("\nFor Process P%d :\n",i);

			do{
			printf("\n Enter Arrival Time : ");
			scanf("%d",&p[i].at);

			if(p[i].at<0)
			printf("\n Invalid Arrival Time !!!");

			}while(p[i].at<0);

			do{
			printf(" Enter Burst Time : ");
			scanf("%d",&p[i].cbt);
			if(p[i].cbt<=0)
				printf("\n Invalid CBT !!! \n");
			}while(p[i].cbt<=0);

			do{
			printf(" Enter Priority : ");
			scanf("%d",&p[i].pri);

			if(p[i].pri<=0)
				printf(" Invalid Priority !!!");
			}while(p[i].pri<=0);

			p[i].pid = i;	
		}
		flag = 0;
	}
	else
	{
		printf("\n Invalid Choice!!!\n");
		flag = 1;
	}
	}while(flag!=0);
	printf("\n-------------------\n Job Queue --------------- ");
	display();
	ready();
	printf("\n\n Gantt Chart : ");
	displaygantt();
	printf("\n");
	displaywt();
	printf("\n");
}

void ready()
{
	int i,flag;
	while(1)
	{
		flag = 0;
		++count;
		for(i=0;i<nop;i++)
		{
			if(p[i].at == count)
			{
				p[i].comp = 1;
				insertrq(p[i].pid);
			}
			if(p[i].comp == 0)
				flag = 1;
		}
		gantt();
		if(flag == 0)
		{
			rtemp = rhead->next;
			if(rtemp == NULL)
				return;
		}
	}
}

void gantt()
{
	int maxpri;
	static int newat=0,newlt=0;	
	rtemp = rhead->next;
	if(rtemp == NULL)
	{
		if(iflag == 0)
		{
			newat = newlt;
			iflag = 1;
		}
		newlt = count+1;
	}
	else
	{
		if(iflag == 1)
		{
			insertgantt(-1,newat,newlt);
			iflag = 0;
		}
		maxpri = rtemp->pri;
		rnew = rtemp;
		rtemp = rtemp->next;
		while(rtemp != NULL)
		{
			if(rtemp->pri < maxpri)
			{
				maxpri = rtemp->pri;
				rnew = rtemp;
			}
			rtemp = rtemp->next;
		}
		newat = newlt;
		newlt = count+1;
		if(pr!=rnew->pid)
		{
			pr = rnew->pid;
			insertgantt(rnew->pid,newat,newlt);
		}
		else
		{
			new->finish++;
		}
		rnew->cbt--;
		if(rnew->cbt == 0)
		{
			p[rnew->pid].tat = new->finish - p[rnew->pid].at;
			p[rnew->pid].wt = p[rnew->pid].tat - p[rnew->pid].cbt;
			avgtat = avgtat + p[rnew->pid].tat;
			avgwt = avgwt + p[rnew->pid].wt;
			rtemp = rhead;
			while(rtemp->next != rnew)
			{
				rtemp = rtemp->next;
			}
			rtemp->next = rnew->next;
		}
	}
}

void insertgantt(int pid,int s,int f)
{
	new = (struct gchart*)malloc(sizeof(struct gchart));
	new->next = NULL;
	new->pid = pid;
	new->start = s;
	new->finish = f;
	temp = head;
	while(temp->next != NULL)
	{
		temp = temp->next;
	}
	temp->next = new;
}

void displaygantt()
{
        temp = head->next;
        printf("\n");
        while(temp != NULL)
        {
                printf("P%d\t|",temp->pid);
                temp = temp->next;
        }
        printf("\n-----------------------------------------------------------");
        temp=head->next;
        printf("%d\t",temp->start);
        while(temp!=NULL)
        {
                printf("%d\t",temp->finish);
                temp=temp->next;
        }
}

void insertrq(int pid)
{
	int i;
	rnew = (struct rq*)malloc(sizeof(struct rq));
	for(i=0;i<nop;i++)
	{
		if(p[i].pid == pid)
		{
			rnew->pid = p[i].pid;
			rnew->at = p[i].at;
			rnew->cbt = p[i].cbt;
			rnew->pri = p[i].pri;
			rnew->next = NULL;
		}
	}
	rtemp = rhead;
	while(rtemp->next != NULL)
	{
		rtemp = rtemp->next;
	}
	rtemp->next = rnew;
}

void displayrq()
{
	rtemp = rhead->next;
	while(rtemp != NULL)
	{
		printf("\n p%d \t %d \t %d \t %d",rtemp->pid,rtemp->at,rtemp->cbt,rtemp->pri);
		rtemp = rtemp->next;
	}
}

void display()
{
	int i;
	printf("\n Pid \t at \t cbt \t priority");
	for(i=0;i<nop;i++)
	{
		printf("\n p%d \t %d \t %d \t %d",p[i].pid,p[i].at,p[i].cbt,p[i].pri);	
	}
} 

void displaywt()
{
	int i;
	printf("\n\nWT\t|\tTAT");
        printf("\n------------------------");
	for(i=0;i<nop;i++)
	{
                printf("\nP%d:%d\t|\tP%d:%d\n",p[i].pid,p[i].wt,p[i].pid,p[i].tat);
	}
	printf("\n\nAverage WT\t|\tAverage TAT");
       	printf("\n-----------------------------------------");
       	printf("\n%f\t|\t%f\n",avgwt/nop,avgtat/nop);
}
