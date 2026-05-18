#include<stdio.h>
#include<string.h>

char M[200][4];
char IR[4];

int IC = 0;

int TTL = 4;   /* Time Limit */
int TTC = 0;   /* Time Counter */

FILE *fin, *fout;

/* LOAD FUNCTION */

void LOAD()
{
    char line[40];

    int m = 0;

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
            int k = 0;

            for(int i=0; line[i]!='\0'; i++)
            {
                if(line[i]=='\n')
                    continue;

                M[m][k] = line[i];

                k++;

                if(k == 4)
                {
                    k = 0;
                    m++;
                }
            }

            if(k != 0)
                m++;
        }
    }
}

/* READ FUNCTION */

void READ()
{
    char buffer[40];

    fgets(buffer,40,fin);

    int loc =
    (IR[2]-'0')*10 +
    (IR[3]-'0');

    int k = 0;

    for(int i=loc;i<loc+10;i++)
    {
        for(int j=0;j<4;j++)
        {
            if(buffer[k]=='\n' || buffer[k]=='\0')
                return;

            M[i][j] = buffer[k++];
        }
    }
}

/* WRITE FUNCTION */

void WRITE()
{
    int loc =
    (IR[2]-'0')*10 +
    (IR[3]-'0');

    for(int i=loc;i<loc+10;i++)
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
    fprintf(fout,"\nPROGRAM TERMINATED\n");
}

/* EXECUTION FUNCTION */

void EXECUTEUSERPROGRAM()
{
    while(1)
    {
        /* FETCH */

        for(int i=0;i<4;i++)
        {
            IR[i] = M[IC][i];
        }

        IC++;

        /* INCREMENT TIME COUNTER */

        TTC++;

        fprintf(fout,"\nTTC = %d\n",TTC);

        /* CHECK TIME LIMIT */

        if(TTC > TTL)
        {
            fprintf(fout,
            "\nTIME LIMIT EXCEEDED\n");

            TERMINATE();

            break;
        }

        /* EXECUTE */

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