#include<stdio.h>
struct process{
	int at,bt,wt,tat,ft,st;
	char name[20];
};
int main(){
	int n,i,j;
	float awt=0;
	float atat=0;
	printf("enter no of processes: ");
	scanf("%d",&n);
	struct process p[n];
	for(i=0;i<n;i++){
	printf("enter processname , arrival time, burst time: ");
	scanf("%s %d %d",p[i].name,&p[i].at,&p[i].bt);
		}
	struct process temp;
	for(i=0;i<n-1;i++){
		for(j=i+1;j<n;j++){
			if(p[i].at>p[j].at){
				temp=p[i];
				p[i]=p[j];
				p[j]=temp;
			}
		}
	}
	
	for(i=0;i<n;i++){
		if(i==0){
		p[i].st=p[i].at;
	}	
	else{
	p[i].st=p[i-1].ft;	
	}
	p[i].wt=p[i].st-p[i].at;
	p[i].ft=p[i].st+p[i].bt;
	p[i].tat=p[i].ft-p[i].at;
	awt+= p[i].wt;
	atat+=p[i].tat;
	
	}
	printf("Process\t AT\tBT\tST\tFT\tTAT\tWT\n");
	for(i=0;i<n;i++){
		printf("%s\t%d\t%d\t%d\t%d\t%d\t%d\t\n",p[i].name,p[i].at,p[i].bt,p[i].st,p[i].ft,p[i].tat,p[i].wt);
	}
	printf("AWT: %f\n",awt/n);
	printf("ATAT: %f",atat/n);
}
