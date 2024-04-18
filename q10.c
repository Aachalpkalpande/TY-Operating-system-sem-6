#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "LinkedList.h"

#define ROW 10
#define COL 20

int *const convert(const char *const, int *);
void LFU(const int *const, const int, const int);
void MFU(const int *const, const int, const int);
void putTable(int[ROW][COL], const int, const int);

int main()
{

    int n_free_frames = 4;//=-1
    int n_reqd_frames = 4;//=-1
    //char buffer[20] = {0};
    //int *sequence = NULL;
    int choice = -1;
    int len;
	int *sequence=(int *)malloc(len*sizeof(int));
	int i;
    while (1)
    {
        printf("\t\t\t\tPAGE REPLACEMENT TECHNIQUES\n");
        printf(" 1 - Read Input\n");
        printf(" 2 - LFU\n");
	printf(" 3 - MFU\n");
        printf(" 4 - Exit\n");
        printf(" -------------------------\n");
        printf(" Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 4:
            exit(0);
        case 1:
           printf(" Enter the number of pages: ");
           scanf("%d", &len);
            //printf(" Enter the number of required frames: ");
          //  scanf("%d", &n_reqd_frames);
            //getchar();
            //printf(" Enter the Reference String: ");
	   // int *sequence=(int *)malloc(len*sizeof(int));
            //scanf("%[^\n]", buffer);
            //sequence = convert(buffer, &len);
            //for(i=0;i<20;i++)
	//	scanf("%d",sequence+i);
	  
	/*	sequence[0]=7;
		sequence[1]=0;
		sequence[2]=1;
		sequence[3]=2;
		sequence[4]=0;
		sequence[5]=3;
		sequence[6]=0;
		sequence[7]=4;
		sequence[8]=2;
		sequence[9]=3;
		sequence[10]=0;
		sequence[11]=3;
		sequence[12]=2;
		sequence[13]=1;
		sequence[14]=2;
		sequence[15]=0;
		sequence[16]=1;
		sequence[17]=7;
		sequence[18]=0;
		sequence[19]=1;		*/
		printf("Enter the values:-");
		for(i=0;i<len;i++)
		{
			scanf("%d",&sequence[i]);
		}
            break;
	  case 2:
            printf("\n\t\tLFU\n");
            LFU(sequence, len, n_reqd_frames);
            break;
	case 3:
            printf("\n\t\tMFU\n");
            MFU(sequence, len, n_reqd_frames);
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
void LFU(const int *const seq, const int len, const int n_frames)
{
    int size = 0;
    int faults = 0;
    int frequency;
    int table[ROW][COL];
    int i,j,k;
    List alloc = createEmptyList();

    Node *least_frequent = NULL, *tmp;

    printf("\n");
    printf("   Frame ->        In Memory      -> Faults \n\n");

    int val = 0;
    for (i = 0; i < len; i++)
    {
        printf("     %-2d  ->", seq[i]);

        Node *isFound = search(alloc, seq[i]);

        if (!isFound)
        {
        
            if (size < n_frames)
            {
                insertLast(alloc, seq[i]);
                size++;
            }
            else
            {
                tmp = alloc->next;
                frequency = 99;

                //Find the frame which is least frequently used and swap
                while (tmp)
                {
                    if (tmp->freq < frequency)
                    {
                        frequency = tmp->freq;
                        least_frequent = tmp;
                    }
                    tmp = tmp->next;
                }
                least_frequent->d = seq[i];
                least_frequent->freq = 1;
            }
            //Updating Table
            insertTable(alloc -> next, table, n_frames, faults);
            faults++;

        }
        else
            isFound->next->freq++;
        display(alloc);
        for (k = length(alloc) * 3; k <= 22; k++)
            printf(" ");
        printf("->   %-2d   \n", faults);
    }
    putTable(table, n_frames, faults);

}

void MFU(const int *const seq, const int len, const int n_frames)
{
    int size = 0;
    int faults = 0;
    int frequency;
    int table[ROW][COL];
    int i,j,k;
    List alloc = createEmptyList();

    Node *least_frequent = NULL, *tmp;

    printf("\n");
    printf("   Frame ->        In Memory      -> Faults \n\n");

    int val = 0;
    for (i = 0; i < len; i++)
    {
        printf("     %-2d  ->", seq[i]);

        Node *isFound = search(alloc, seq[i]);

        if (!isFound)
        {
        
            if (size < n_frames)
            {
                insertLast(alloc, seq[i]);
                size++;
            }
            else
            {
                tmp = alloc->next;
                frequency = 0;

                //Find the frame which is least frequently used and swap
                while (tmp)
                {
                    if (tmp->freq > frequency)
                    {
                        frequency = tmp->freq;
                        least_frequent = tmp;
                    }
                    tmp = tmp->next;
                }
                least_frequent->d = seq[i];
                least_frequent->freq = 1;
            }
            //Updating Table
            insertTable(alloc -> next, table, n_frames, faults);
            faults++;

        }
        else
            isFound->next->freq++;
        display(alloc);
        for (k = length(alloc) * 3; k <= 22; k++)
            printf(" ");
        printf("->   %-2d   \n", faults);
    }
    putTable(table, n_frames, faults);

}

