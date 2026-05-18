#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char M[400][4];

char IR[4];
char R[4];

int IC;
int PTR;

int used[40];

FILE *fin;

/* ALLOCATE FRAME */

int ALLOCATE()
{
    int frame;

    while(1)
    {
        frame = rand() % 40;

        if(used[frame] == 0)
        {
            used[frame] = 1;

            return frame;
        }
    }
}

/* LOAD FUNCTION */

void LOAD()
{
    char line[40];

    int frame;
    int loc;
    int i,j,k;

    fin = fopen("input.txt","r");

    while(fgets(line,40,fin))
    {
        // START OF JOB

        if(strncmp(line,"$AMJ",4)==0)
        {
            // Allocate frame for page table

            PTR = ALLOCATE() * 10;

            // Initialize page table

            for(i=PTR;i<PTR+10;i++)
            {
                M[i][0] = '*';
                M[i][1] = '*';
                M[i][2] = '*';
                M[i][3] = '*';
            }
        }

        // DATA START

        else if(strncmp(line,"$DTA",4)==0)
        {
            break;
        }

        // END OF JOB

        else if(strncmp(line,"$END",4)==0)
        {
            break;
        }

        // PROGRAM CARDS

        else
        {
            // Allocate frame for program page

            frame = ALLOCATE();

            // Store frame number in page table

            M[PTR][0] = (frame/10) + '0';
            M[PTR][1] = (frame%10) + '0';

            loc = frame * 10;

            k = 0;

            // LOAD INTO FRAME

            for(i=0;i<strlen(line);i++)
            {
                if(line[i]=='\n')
                    continue;

                M[loc][k] = line[i];

                k++;

                if(k==4)
                {
                    loc++;
                    k=0;
                }
            }

            PTR++;
        }
    }

    fclose(fin);
}

/* DISPLAY MEMORY */

void DISPLAY()
{
    int i,j;

    printf("\nMEMORY CONTENTS:\n\n");

    for(i=0;i<100;i++)
    {
        printf("%d\t",i);

        for(j=0;j<4;j++)
        {
            printf("%c",M[i][j]);
        }

        printf("\n");
    }
}

/* MAIN */

int main()
{
    int i;

    for(i=0;i<40;i++)
        used[i]=0;

    LOAD();

    DISPLAY();

    return 0;
}