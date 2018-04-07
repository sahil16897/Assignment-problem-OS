#include<stdio.h>
#include<pthread.h>

void *student(void *arg);
void *teacher(void *arg);
int n;

int main()
{
  int choice;
  printf("Enter 1, if you want to handle students queries.\n");
  printf("Enter 2, if you want to handle teachers queries.\n");
  printf("Please enter a choice:");
  scanf("%d", &choice);
  printf("Please enter number of queries to handle:");
  scanf("%d", &n);
  pthread_t thread1[n];
  pthread_t thread2[n];

  switch(choice){
	  	case 1:for(int i=0; i < n; i++){
					for(int i=0; i < n; i++){
					pthread_create(&thread1[i], NULL, student, NULL);
					}
					for(int i=0; i < n; i++){
					pthread_join(thread1[i], NULL);
					}
				}
	  			break;
	  	case 2: for(int i=0; i < n; i++){
					for(int i=0; i < n; i++){
					pthread_create(&thread2[i], NULL, teacher, NULL);
					}
					for(int i=0; i < n; i++){
					pthread_join(thread2[i] , NULL);
					}
				}
	  			break;
	  	default : printf("Attention! Please enter correct option");
  }
  return 0;
}


void *student(void *arg){
	int count,j,time,remain,flag=0,time_quantum;
  	int wait_time=0,turnaround_time=0,at[10],bt[10],rt[10];
     remain=n;
	for(count=0;count<n;count++)
	{
		printf("Enter Arrival Time for %d query:",count+1);
		scanf("%d",&at[count]);
		printf("Enter Burst time for %d query:", count+1);
		scanf("%d",&bt[count]);
		rt[count]=bt[count];
	}
	printf("Enter Time Quantum:");
	scanf("%d",&time_quantum);
	printf("\n\nProcess\t|Turnaround Time|Waiting Time\n\n");
	for(time=0,count=0;remain!=0;)
	{
		if(rt[count]<=time_quantum && rt[count]>0)
		{
		  time+=rt[count];
		  rt[count]=0;
		  flag=1;
		}
		else if(rt[count]>0)
		{
		  rt[count]-=time_quantum;
		  time+=time_quantum;
		}
		if(rt[count]==0 && flag==1)
		{
		  remain--;
		  printf("P[%d]\t|\t%d\t|\t%d\n",count+1,time-at[count],time-at[count]-bt[count]);
		  wait_time+=time-at[count]-bt[count];
		  turnaround_time+=time-at[count];
		  flag=0;
		}
		if(count==n-1)
		  count=0;
		else if(at[count+1]<=time)
		  count++;
		else
		  count=0;
	}
	printf("\nAverage Waiting Time= %.2f\n",wait_time*1.0/n);
	printf("Avg Turnaround Time = %.2f",turnaround_time*1.0/n);
	return 0;
}
void *teacher(void *arg){
	int count,j,time,remain,flag=0,time_quantum;
  	int wait_time=0,turnaround_time=0,at[10],bt[10],rt[10];
	remain=n;
	for(count=0;count<n;count++)
	{
		printf("Enter Arrival Time for %d query:",count+1);
		scanf("%d",&at[count]);
		printf("Enter Burst time for %d query:", count+1);
		scanf("%d",&bt[count]);
		rt[count]=bt[count];
	}
	printf("Enter Time Quantum:");
	scanf("%d",&time_quantum);
	printf("\n\nProcess\t|Turnaround Time|Waiting Time\n\n");
	for(time=0,count=0;remain!=0;)
	{
		if(rt[count]<=time_quantum && rt[count]>0)
		{
			  time+=rt[count];
			  rt[count]=0;
			  flag=1;
		}
		else if(rt[count]>0)
		{
			  rt[count]-=time_quantum;
			  time+=time_quantum;
		}
		if(rt[count]==0 && flag==1)
		{
			  remain--;
			  printf("P[%d]\t|\t%d\t|\t%d\n",count+1,time-at[count],time-at[count]-bt[count]);
			  wait_time+=time-at[count]-bt[count];
			  turnaround_time+=time-at[count];
			  flag=0;
		}
		if(count==n-1)
			count=0;
		else if(at[count+1]<=time)
			count++;
		else
			count=0;
	}
	printf("\nAverage Waiting Time= %.2f\n",wait_time*1.0/n);
    printf("Avg Turnaround Time = %.2f",turnaround_time*1.0/n);
    return 0;

}