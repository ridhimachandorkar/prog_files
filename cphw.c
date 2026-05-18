#include<stdio.h>
#include<string.h>

char M[200][4];
char IR[4];
int IC;
char buffer[40];

FILE *fin, *fout;

/* LOAD PROGRAM INTO MEMORY */

void LOAD()
{
    char line[40];
    int m = 0;
    int i;

    fin = fopen("input.txt","r");

    while(fgets(line,40,fin))
    {
        if(strncmp(line,"$AMJ",4)==0)
        {
            m = 0;
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
            for(i=0; i<strlen(line); i++)
            {
                if(line[i]=='\n')
                    continue;

                M[m][i%4] = line[i];

                if(i%4 == 3)
                    m++;
            }

            if(i%4 != 0)
                m++;
        }
    }
}

/* READ FUNCTION */

void READ()
{
    fgets(buffer,40,fin);

    int loc =
    (IR[2]-'0')*10 + (IR[3]-'0');

    int k = 0;

    for(int i=loc; i<loc+10; i++)
    {
        for(int j=0; j<4; j++)
        {
            if(buffer[k]=='\n')
                return;

            M[i][j] = buffer[k];
            k++;
        }
    }
}

/* WRITE FUNCTION */

void WRITE()
{
    int loc =
    (IR[2]-'0')*10 + (IR[3]-'0');

    printf("\nOUTPUT:\n");

    for(int i=loc; i<loc+10; i++)
    {
        for(int j=0; j<4; j++)
        {
            printf("%c",M[i][j]);
        }
    }

    printf("\n");
}

/* TERMINATE */

void TERMINATE()
{
    printf("\nPROGRAM EXECUTED SUCCESSFULLY\n");
}

/* EXECUTE USER PROGRAM */

void EXECUTEUSERPROGRAM()
{
    while(1)
    {
        // FETCH INSTRUCTION

        for(int i=0;i<4;i++)
        {
            IR[i] = M[IC][i];
        }

        IC++;

        // DECODE + EXECUTE

        if(IR[0]=='G' && IR[1]=='D')
        {
            READ();
        }

        else if(IR[0]=='P' && IR[1]=='D')
        {
            WRITE();
        }

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
    IC = 0;

    LOAD();

    EXECUTEUSERPROGRAM();

    fclose(fin);

    return 0;
}