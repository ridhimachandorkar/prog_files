#include<stdio.h>
#define MAX 50

void fifo(int pages[],int n,int cap){
int frame[MAX],i,j,found,idx=0,faults=0;
for(i=0;i<cap;i++)frame[i]=-1;
for(i=0;i<n;i++){
found=0;
for(j=0;j<cap;j++)if(frame[j]==pages[i]){found=1;break;}
if(!found){frame[idx]=pages[i];idx=(idx+1)%cap;faults++;}
}
printf("FIFO=%d\n",faults);
}

void lru(int pages[],int n,int cap){
int frame[MAX],time[MAX],i,j,found,faults=0,cnt=0,pos;
for(i=0;i<cap;i++){frame[i]=-1;time[i]=0;}
for(i=0;i<n;i++){
found=0;
for(j=0;j<cap;j++)if(frame[j]==pages[i]){found=1;time[j]=++cnt;break;}
if(!found){
pos=0;
for(j=1;j<cap;j++)if(time[j]<time[pos])pos=j;
frame[pos]=pages[i];
time[pos]=++cnt;
faults++;
}
}
printf("LRU=%d\n",faults);
}

void optimal(int pages[],int n,int cap){
int frame[MAX],i,j,k,found,faults=0,pos,farthest;
for(i=0;i<cap;i++)frame[i]=-1;
for(i=0;i<n;i++){
found=0;
for(j=0;j<cap;j++)if(frame[j]==pages[i]){found=1;break;}
if(!found){
pos=-1;farthest=i;
for(j=0;j<cap;j++){
for(k=i+1;k<n;k++)if(frame[j]==pages[k])break;
if(k==n){pos=j;break;}
if(k>farthest){farthest=k;pos=j;}
}
if(pos==-1)pos=0;
frame[pos]=pages[i];
faults++;
}
}
printf("OPTIMAL=%d\n",faults);
}

int main(){
int pages[MAX],n,cap,i;
printf("Enter number of pages:");
scanf("%d",&n);
printf("Enter page reference string:");
for(i=0;i<n;i++)scanf("%d",&pages[i]);
printf("Enter number of frames:");
scanf("%d",&cap);

fifo(pages,n,cap);
lru(pages,n,cap);
optimal(pages,n,cap);

return 0;
}