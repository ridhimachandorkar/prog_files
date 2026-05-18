#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char M[300][4];
char IR[4];

int IC = 0;

int pageTable[10];
int used[30];

FILE *fin, *fout;

/* ALLOCATE FRAME */

int ALLOCATE()
{
    for(int i=0;i<30;i++)
    {
        if(used[i] == 0)
        {
            used[i] = 1;
            return i;
        }
    }

    return -1;
}

/* ADDRESS MAP */

int ADDRESSMAP(int VA)
{
    int page = VA / 10;
    int offset = VA % 10;

    if(pageTable[page] == -1)
        return -1;

    return pageTable[page] * 10 + offset;
}

/* LOAD FUNCTION */

void LOAD()
{
    char line[40];

    int frame;
    int loc;
    int k;

    while(fgets(line,40,fin))
    {
        if(strncmp(line,"$AMJ",4)==0)
        {
            for(int i=0;i<10;i++)
                pageTable[i] = -1;
        }

        else if(strncmp(line,"$DTA",4)==0)
        {
            break;
        }

        else if(strncmp(line,"$END",4)==0)
        {
            break;
        }

        else
        {
            frame = ALLOCATE();

            /* Store only program page */

            pageTable[0] = frame;

            loc = frame * 10;

            k = 0;

            for(int i=0; line[i]!='\0'; i++)
            {
                if(line[i]=='\n')
                    continue;

                M[loc][k] = line[i];

                k++;

                if(k == 4)
                {
                    k = 0;
                    loc++;
                }
            }
        }
    }
}

/* WRITE FUNCTION */

void WRITE(int RA)
{
    for(int i=RA;i<RA+10;i++)
    {
        for(int j=0;j<4;j++)
        {
            if(M[i][j]=='\0')
                return;

            fprintf(fout,"%c",M[i][j]);
        }
    }

    fprintf(fout,"\n");
}

/* TERMINATE */

void TERMINATE()
{
    fprintf(fout,
    "\nPROGRAM TERMINATED\n");
}

/* EXECUTION FUNCTION */

void EXECUTEUSERPROGRAM()
{
    int VA,RA;

    while(1)
    {
        /* FETCH */

        RA = ADDRESSMAP(IC);

        for(int i=0;i<4;i++)
        {
            IR[i] = M[RA][i];
        }

        IC++;

        /* PD */

        if(IR[0]=='P' && IR[1]=='D')
        {
            VA =
            (IR[2]-'0')*10 +
            (IR[3]-'0');

            RA = ADDRESSMAP(VA);

            /* INVALID PAGE FAULT */

            if(RA == -1)
            {
                fprintf(fout,
                "\nINVALID PAGE FAULT\n");

                TERMINATE();

                break;
            }

            WRITE(RA);
        }

        /* HALT */

        else if(IR[0]=='H')
        {
            TERMINATE();
            break;
        }
    }
}

/* MAIN */

int main()
{
    for(int i=0;i<30;i++)
        used[i] = 0;

    fin = fopen("input.txt","r");

    if(fin == NULL)
    {
        printf("Input file not found");
        return 0;
    }

    fout = fopen("output.txt","w");

    LOAD();

    EXECUTEUSERPROGRAM();

    fclose(fin);
    fclose(fout);

    printf("Execution Completed\n");

    return 0;
}