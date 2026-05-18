#include<stdio.h>
#include<string.h>

char M[200][4];

void LOAD()
{
    FILE *fp;
    char buffer[40];

    int m = 0;
    int i;

    fp = fopen("input.txt","r");

    while(fgets(buffer,40,fp))
    {
        // Ignore $AMJ
        if(strncmp(buffer,"$AMJ",4)==0)
        {
            m = 0;
        }

        // Ignore $DTA
        else if(strncmp(buffer,"$DTA",4)==0)
        {
            continue;
        }

        // Stop at $END
        else if(strncmp(buffer,"$END",4)==0)
        {
            break;
        }

        // Store program cards in memory
        else
        {
            for(i=0; i<strlen(buffer); i++)
            {
                // Ignore newline
                if(buffer[i]=='\n')
                    continue;

                M[m][i%4] = buffer[i];

                // Move to next word after 4 chars
                if(i%4 == 3)
                    m++;
            }

            // If instruction incomplete
            if(i%4 != 0)
                m++;
        }
    }

    fclose(fp);
}

void DISPLAY()
{
    int i,j;

    printf("\nMEMORY CONTENTS:\n\n");

    for(i=0;i<20;i++)
    {
        printf("%d\t",i);

        for(j=0;j<4;j++)
        {
            printf("%c",M[i][j]);
        }

        printf("\n");
    }
}

int main()
{
    LOAD();

    DISPLAY();

    return 0;
}