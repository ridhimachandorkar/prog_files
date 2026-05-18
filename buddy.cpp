#include<stdio.h>
#include<math.h>

#define MAX 100

int memorySize;
int allocation[MAX];

int nextPowerOf2(int n){
    int power=1;
    while (power<n)
        power*=2;
    return power;
}

void allocate(int processSize[],int n){
    int used=0;

    printf("\nBuddy System Allocation:\n");

    for (int i=0;i<n;i++){
        int req=nextPowerOf2(processSize[i]);

        if (used+req<=memorySize) {
            allocation[i]=req;
            used+=req;
            printf("Process %d (Size %d)->Allocated %d\n",
                   i + 1, processSize[i],req);
        } else {
            allocation[i] = -1;
            printf("Process %d (Size %d)->Not Allocated\n",
                   i + 1,processSize[i]);
        }
    }

    printf("\nTotal Memory Used: %d / %d\n",used,memorySize);
}

int main() {
    int processSize[]={100, 180, 250, 70};
    int n = sizeof(processSize)/sizeof(processSize[0]);

    printf("Enter total memory size ");
    scanf("%d",&memorySize);

    allocate(processSize,n);

    return 0;
}