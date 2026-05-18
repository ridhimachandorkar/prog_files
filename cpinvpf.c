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

int pageTable[10];

/* ALLOCATE FRAME */

int ALLOCATE()
{
    int frame;

    while(1)
    {
        frame = rand()%40;

        if(used[frame]==0)
        {
            used[frame]=1;

            return frame;
        }
    }
}

/* ADDRESS MAP */

int ADDRESSMAP(int VA)
{
    int page;
    int offset;
    int frame;

    page = VA/10;

    offset = VA%10;

    frame = pageTable[page];

    // PAGE FAULT

    if(frame == -1)
    {
        return -1;
    }

    return frame*10 + offset;
}

/* HANDLE VALID PAGE FAULT */

void VALIDPAGEFAULT(int VA)
{
    int page;
    int frame;

    page = VA/10;

    frame = ALLOCATE();

    pageTable[page] = frame;

    printf("\nVALID PAGE FAULT OCCURRED");

    printf("\nPAGE %d ALLOCATED TO FRAME %d\n",
           page,frame);
}

/* LOAD */

void LOAD()
{
    char line[40];

    int frame;
    int loc;
    int i,k;

    fin = fopen("input.txt","r");

    while(fgets(line,40,fin))
    {
        if(strncmp(line,"$AMJ",4)==0)
        {
            PTR = ALLOCATE()*10;

            for(i=0;i<10;i++)
                pageTable[i]=-1;
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

            pageTable[0]=frame;

            loc = frame*10;

            k=0;

            for(i=0;i<strlen(line);i++)
            {
                if(line[i]=='\n')
                    continue;

                M[loc][k]=line[i];

                k++;

                if(k==4)
                {
                    loc++;
                    k=0;
                }
            }
        }
    }
}

/* READ */

void READ(int RA)
{
    char buffer[40];

    fgets(buffer,40,fin);

    int k=0;

    for(int i=RA;i<RA+10;i++)
    {
        for(int j=0;j<4;j++)
        {
            if(buffer[k]=='\n')
                return;

            M[i][j]=buffer[k];

            k++;
        }
    }
}

/* WRITE */

void WRITE(int RA)
{
    printf("\nOUTPUT:\n");

    for(int i=RA;i<RA+10;i++)
    {
        for(int j=0;j<4;j++)
        {
            printf("%c",M[i][j]);
        }
    }

    printf("\n");
}

/* TERMINATE */

void TERMINATE()
{
    printf("\nPROGRAM TERMINATED\n");
}

/* EXECUTION */

void EXECUTEUSERPROGRAM()
{
    int VA,RA;

    while(1)
    {
        // FETCH

        RA = ADDRESSMAP(IC);

        for(int i=0;i<4;i++)
        {
            IR[i]=M[RA][i];
        }

        IC++;

        // GD

        if(IR[0]=='G' && IR[1]=='D')
        {
            VA =
            (IR[2]-'0')*10 +
            (IR[3]-'0');

            RA = ADDRESSMAP(VA);

            // PAGE FAULT

            if(RA==-1)
            {
                 printf("\nINVALID PAGE FAULT\n");

                TERMINATE();

                break;
            }

            READ(RA);
        }

        // PD

        else if(IR[0]=='P' && IR[1]=='D')
        {
            VA =
            (IR[2]-'0')*10 +
            (IR[3]-'0');

            RA = ADDRESSMAP(VA);

            WRITE(RA);
        }

        // HALT

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
    int i;

    for(i=0;i<40;i++)
        used[i]=0;

    IC=0;

    LOAD();

    EXECUTEUSERPROGRAM();

    fclose(fin);

    return 0;
}