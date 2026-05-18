#include<stdio.h>

int main(){
int choice;

while(1){
printf("\n1.Paging\n2.Segmentation\n3.Exit\nEnter choice:");
scanf("%d",&choice);

if(choice==1){
int pt[50],n,ps,la,page,offset,frame,pa;

printf("Enter number of pages:");
scanf("%d",&n);

printf("Enter page table:");
for(int i=0;i<n;i++)
scanf("%d",&pt[i]);

printf("Enter page size:");
scanf("%d",&ps);

printf("Enter logical address:");
scanf("%d",&la);

page=la/ps;
offset=la%ps;

if(page>=n)
{
    printf("Invalid\n");
    continue;
}

frame=pt[page];
pa=frame*ps+offset;
printf("Physical Address=%d\n",pa);
}
else if(choice==2){
int base[50],limit[50],n,seg,offset,pa;
printf("Enter number of segments:");
scanf("%d",&n);
printf("Enter base:");
for(int i=0;i<n;i++)scanf("%d",&base[i]);
printf("Enter limit:");
for(int i=0;i<n;i++)scanf("%d",&limit[i]);
printf("Enter segment:");
scanf("%d",&seg);
printf("Enter offset:");
scanf("%d",&offset);
if(seg>=n||offset>=limit[seg]){printf("Invalid\n");continue;}
pa=base[seg]+offset;
printf("Physical Address=%d\n",pa);
}
else if(choice==3)break;
else printf("Invalid choice\n");
}
return 0;
}