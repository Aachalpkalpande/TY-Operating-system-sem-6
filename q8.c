#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "LinkedList.h"

#define ROW 10
#define COL 20

int *const convert(const char *const, int *);

void FIFO(const int *const, const int, const int);
void putTable(int[ROW][COL], const int, const int);

int main()
{

    int n_free_frames = 3;//=-1
    int n_reqd_frames = 3;//=-1
    //char buffer[20] = {0};
    //int *sequence = NULL;
    int choice = -1;
    int len ;
	int *sequence=(int *)malloc(len*sizeof(int));
	int i;
    while (1)
    {
        printf("\t\t\t\tPAGE REPLACEMENT TECHNIQUES\n");
        printf(" 1 - READ INPUT\n");
        printf(" 2 - FIFO\n");
	 printf(" 3 - Exit\n");
        printf(" -------------------------\n");
        printf(" Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 3:
            exit(0);
        case 1:
	    printf("\nEnter no of pages: ");
	    scanf("%d",&len);
       
		printf("Enter the numbers:-\n");
		for(i=0;i<len;i++)
		{
			scanf("%d",&sequence[i]);
		}
            break;
        case 2:
            printf("\n\t\tFIFO\n");
            FIFO(sequence, len, n_reqd_frames);
            break;
		 default:
            printf(" Invalid Input!\n");
        }
        printf("\n");
    }
}
int *const convert(const char *const refstr, int *size)
{
    static int arr[30];
    int i = 0, val = 0,j;

    while (refstr[i])
    {
        if (isdigit(refstr[i]))
        {
            val = refstr[i] - 48;
            for (j = i + 1; refstr[j] && isdigit(refstr[j]); j++)
            {
                val = (val * 10) + (refstr[j] - 48);
                i = j;
            }

            arr[*size] = val;
            (*size)++;
        }
        i++;
    }
    return arr;
}

void putTable(int table[ROW][COL], const int n_frames, const int n_updates)
{
    int i,j;
    printf("\n ");
    for (i = 0; i < n_updates; i++)
        printf("+----");
    printf("+\n ");

    for (i = 0; i < n_frames; i++)
    {
        for (j = 0; j < n_updates; j++)
        {
            if (table[i][j] == -1)
                printf("| -  ");
            else
                printf("| %-2d ", table[i][j]);
        }
        printf("|\n ");
    }
    for (i = 0; i < n_updates; i++)
        printf("+----");
    printf("+\n ");
}

void insertTable(List tmp, int table[ROW][COL], const int n_frames, const int faults)
{
    int i;
    for (i = 0; i < n_frames; i++)
    {
        if (tmp)
        {
            table[i][faults] = tmp->d;
            tmp = tmp->next;
        }
        else
            table[i][faults] = -1;
    }
}

void FIFO(const int *const seq, const int len, const int n_frames)
{
    int size = 0;
    int faults = 0;
    int table[ROW][COL];
    int i,j,k;
    List alloc = createEmptyList();

    Node *oldest;

    printf("\n");
    printf("   Frame ->        In Memory      -> Faults \n\n");

    for (i = 0; i < len; i++)
    {
        printf("     %-2d  ->", seq[i]);

        Node *isFound = search(alloc, *(seq+i));
        Node *tmp;

        if (!isFound)
        {
            if (size < n_frames)
            {
                insertLast(alloc, *(seq+i));
                size++;

                //Initialise first frame as oldest
                if (size == 1)
                    oldest = alloc->next;
            }
            else
            {

                //Swap oldest frame with new frame
                oldest->d = *(seq+i);

                //Update oldest frame
                if (oldest->next)
                    oldest = oldest->next;
                else
                    oldest = alloc->next;
            }
            //Updating Table
            insertTable(alloc -> next, table, n_frames, faults);
            faults++;
        }
        display(alloc);
        for (k = length(alloc) * 3; k <= 22; k++)
            printf(" ");
        printf("->    %-2d   \n", faults);
    }
    putTable(table, n_frames, faults);
}

