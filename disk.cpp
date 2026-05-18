#include<stdio.h>
#include<stdlib.h>
void sort(int arr[],int n){
for(int i=0;i<n-1;i++)
for(int j=0;j<n-i-1;j++)
if(arr[j]>arr[j+1]){
int t=arr[j];arr[j]=arr[j+1];arr[j+1]=t;
}
}
void fcfs(int req[],int n,int head){
int seek=0;
for(int i=0;i<n;i++){
seek+=abs(req[i]-head);
head=req[i];
}
printf("FCFS=%d\n",seek);
}
void sstf(int req[],int n,int head){
int visited[50]={0},seek=0;
for(int i=0;i<n;i++){
int min=1e9,pos=-1;
for(int j=0;j<n;j++){
if(!visited[j]){
int dist=abs(req[j]-head);
if(dist<min){min=dist;pos=j;}
}
}
visited[pos]=1;
seek+=min;
head=req[pos];
}
printf("SSTF=%d\n",seek);
}
void scan(int req[],int n,int head,int size){
int seek=0,arr[50],i;
for(i=0;i<n;i++)arr[i]=req[i];
arr[n]=head;
n++;
sort(arr,n);
int pos;
for(i=0;i<n;i++)if(arr[i]==head){pos=i;break;}
for(i=pos-1;i>=0;i--){
seek+=abs(arr[i+1]-arr[i]);
}
if(pos!=0)
seek+=arr[0];
for(i=pos+1;i<n;i++){
if(i==pos+1)seek+=abs(head-arr[i]);
else seek+=abs(arr[i]-arr[i-1]);
}
printf("SCAN=%d\n",seek);
}
void cscan(int req[],int n,int head,int size){
int seek=0,arr[50],i;
for(i=0;i<n;i++)arr[i]=req[i];
arr[n]=head;
n++;
sort(arr,n);
int pos;
for(i=0;i<n;i++)
if(arr[i]==head)
{
    pos=i;break;
}
for(i=pos+1;i<n;i++){
if(i==pos+1)seek+=abs(head-arr[i]);
else seek+=abs(arr[i]-arr[i-1]);
}
seek+=(size-1-arr[n-1]);
seek+=(size-1);
for(i=0;i<pos;i++){
if(i==0)seek+=arr[i];
else seek+=abs(arr[i]-arr[i-1]);
}
printf("CSCAN=%d\n",seek);
}
int main(){
int req[50],n,head,size;
printf("Enter number of requests:");
scanf("%d",&n);
printf("Enter requests:");
for(int i=0;i<n;i++)scanf("%d",&req[i]);
printf("Enter initial head position:");
scanf("%d",&head);
printf("Enter disk size:");
scanf("%d",&size);
fcfs(req,n,head);
sstf(req,n,head);
scan(req,n,head,size);
cscan(req,n,head,size);
return 0;
}