#include<stdio.h>
struct process{
int at,st,bt,wt,ft,tat,pri;
char name[2];
};
int main(){
int i,j,n;
float awt,atat;
printf("enter the number of process :");
scanf("%d",&n);
struct process p[n+1];
for(i=0;i<n;i++){
printf("enter the name,arrival time, burst time and priority of process %d  :",i+1);
scanf("%s %d %d %d",p[i].name,&p[i].at,&p[i].bt,&p[i].pri);
}

for(i=0;i<n-1;i++){
for(j=i+1;j<n;j++){
if(p[i].at>p[j].at){
p[n]=p[i];
p[i]=p[j];
p[j]=p[n];
}
}
}

for(i=0;i<n-1;i++){
for(j=i+1;j<n;j++){
if(p[j].at==p[i].ft && p[j].pri<p[i].pri){
p[n]=p[i];
p[i]=p[j];
p[j]=p[n];
}
}
}

awt=0;
atat=0;
for(i=0;i<n;i++){

if(i==0){
p[i].st=p[i].at;
}
else{
int min=i;
for(j=i;j<n;j++){
if(p[j].pri<p[min].pri && p[j].at<=p[i-1].ft){
min=j;
}
}
p[n]=p[i];
p[i]=p[min];
p[min]=p[n];

if(p[i].at<=p[i-1].ft)
 p[i].st=p[i-1].ft;
else
 p[i].st=p[i].at;
}
p[i].wt=p[i].st-p[i].at;
p[i].ft=p[i].st+p[i].bt;
p[i].tat=p[i].ft-p[i].at;
awt+=p[i].wt;
atat+=p[i].tat;

}

printf("name	at	bt	wt	ft	tat	pri\n");
for(i=0;i<n;i++){
printf("%s	%d	%d	%d	%d	%d	%d\n",p[i].name,p[i].at,p[i].bt,p[i].wt,p[i].ft,p[i].tat,p[i].pri);
}
printf("average waiting time	=	%f\n",awt/n);
printf("average turn around time	=	%f\n",atat/n);
}
