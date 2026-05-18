    #include<stdio.h>
int main()
{
    int n,r,i,j,k;
    int allocation[10][10];
    int max[10][10];
    int available[10];
    printf("Enter number of processes: ");
    scanf("%d",&n);
    printf("\nEnter number of resources: ");
    scanf("%d",&r);
    printf("\nEnter allocation matrix: ");
    for(i=0;i<n;i++)
    {
        for(j=0;j<r;j++)
        scanf("%d",&allocation[i][j]);
    }
    printf("\nEnter max matrix: ");
    for(i=0;i<n;i++)
    {
        for(j=0;j<r;j++)
        scanf("%d",&max[i][j]);
    }
    printf("\nEnter availability vector: ");
    for(j=0;j<r;j++)
    scanf("%d",&available[j]);
    int f[n],ans[n],ind=0;
    for(k=0;k<n;k++)
    {
        f[k]=0;
    }          
    int need[n][r];
    for(i=0;i<n;i++)
    {
        for(j=0;j<r;j++)
        need[i][j]=max[i][j]-allocation[i][j];
    }
    int y=0;
    for(k=0;k<5;k++)
    {
        for(i=0;i<n;i++)
        {
            if(f[i]==0)
            {
                int flag=0;
                for(j=0;j<r;j++)
                {
                    if(need[i][j]>available[j])
                    {
                        flag=1;
                        break;
                    }
                }
                if(flag==0)
                {
                    ans[ind++]=i;
                    for(y=0;y<r;y++)
                    {
                        available[y]+=allocation[i][y];
                    }
                    f[i]=1;
                }
            }
        }
    }   
    printf("Safe Sequence:\n");
    for(i=0;i<n-1;i++)
    printf("P%d ",ans[i]);
    printf("P%d ",ans[n-1]);
    return 0;
}