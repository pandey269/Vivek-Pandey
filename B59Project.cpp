//Preemtive Priority Scheduling using time slice and Context Switching
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
int main()
{
int n;
int i,j;
printf("Enter the no of processes : ");
scanf("%d",&n);
int pid[n],arr[n],burst[n],tat[n],waiting[n],comp[n],prior[n];
int dup_burst[n];
int least_arr,high_prior;
for(i=0;i<n;i++)
{
printf("Enter Process ID : ");
scanf("%d",&pid[i]);
printf("Enter arrival time of process %d : ",pid[i]);
scanf("%d",&arr[i]);
printf("Enter burst time of process %d : ",pid[i]);
scanf("%d",&burst[i]);
printf("Enter priority of process %d : ",pid[i]);
scanf("%d",&prior[i]);
}
int priority[n];
for(i=0;i<n;i++)
priority[i] = prior[i];
least_arr = arr[0];
for(i=0;i<n;i++)
{
if(least_arr>arr[i])
least_arr = arr[i];
comp[i] = 0; // Setting zero to all Completion Time values
dup_burst[i] = burst[i]; // Creating a duplicate Burst Time Array
}
int time_slice = least_arr;
int new_val;
for(i=0;i<n;i++)
{
if(arr[i] == least_arr)
{
if(dup_burst[i]>0)
prior[i] = prior[i] - 1;
new_val = prior[i];
time_slice = time_slice + 1;
if(dup_burst[i]>0)
dup_burst[i] = dup_burst[i] - 1; // remaining burst  time is decremented by 1
for(j=0;j<n;j++)
{
if(arr[j]<=time_slice && j!=i && dup_burst[j]>0)
prior[j] = prior[j] - 2;
}
for(j=0;j<n;j++)
{
if(dup_burst[j]>0)
comp[j] = comp[j] + 1 + least_arr;
}
break;
}
}
high_prior = prior[0];
for(i=0;i<n;i++)
{
if(high_prior>prior[i])
high_prior = prior[i];
}
//context switching
//Adds 2 to completion time of all the processes whose remaining burst time is greater than 0
if(high_prior!=new_val)
{
for(i=0;i<n;i++)
{
if(dup_burst[i]>0)
comp[i] = comp[i]+2;
}
}
while(1)
{
int count=0;
for(i=0;i<n;i++)
{
if(dup_burst[i] == 0)
count++;
}
if(count == n)
break;
else
{
int checksum = 0;
for(i=0;i<n;i++)
{
if(high_prior == prior[i])
{
//Time Slice increments by 1
time_slice = time_slice + 1;
if(dup_burst[i]>0)
prior[i] = prior[i] - 1;
else
checksum = -1;
 //priority of the process is incremented by 1 (subtraction since lowest number is highest priority)
for(j=0;j<n;j++)
{
if(arr[j]<=time_slice && j!=i && dup_burst[j]>0)
prior[j] = prior[j] - 2; // Priority of waiting processes is incremented by 2
if(dup_burst[j]>0)
comp[j] = comp[j]+1; // Completion time of all processes whose remaning burst time is greater than 0 is incremented by 1
}
if(dup_burst[i]>0)
dup_burst[i] = dup_burst[i] - 1; // Remaining Burst time is decremented by 1
}
int cnt = 0;
int new_dup_burst;
for(j=0;j<n;j++)
{
if(high_prior>prior[j])
{
high_prior = prior[j];
new_dup_burst = dup_burst[j];
}
if(dup_burst[j] == 0)
cnt++;
}
if(high_prior == prior[i] && dup_burst[i] == 0 && checksum == -1 )
{
for(j=0;j<n;j++)
{
if(dup_burst[j]>0 && j!=i)
comp[j] = comp[j] - 1; //Completion Time of all processes whose burst time is greater than 0 is incremented by 1
}
}
//Context Switching
if(high_prior != prior[i])
{
for(j=0;j<n;j++)
{
if(dup_burst[j]>0)
comp[j] = comp[j] + 2; //Due to context switching completion of all the processes whose remaining burst time is greater than 0 is incremented by 2
// Since Context_Switching_Time = 2 Time Units
}
}
if(cnt == n)
break;
}
}
}
for(i=0;i<n;i++)
{
tat[i] = comp[i] - arr[i];
}
for(i=0;i<n;i++)
waiting[i] = tat[i] - burst[i];
printf("\n");
printf("Process ID\tBurst Time\tPriority\tArrival Time\tCompletion Time\t\tTurn Around Time \t\t Waiting Time\n");
for(int i=0;i<n;i++)
printf("%d\t\t%d\t\t\t%d\t\t%d\t\t\t%d\t\t\t\%d\t\t\t\t\%d\t\t\t\t\n",pid[i],burst[i],priority[i],arr[i],comp[i],tat[i],waiting[i]);
printf("\n");
float avg_wait = 0;
for(i=0;i<n;i++)
avg_wait = avg_wait + waiting[i];
avg_wait = avg_wait/(float)n;
printf("The average waiting time is : %f\n",avg_wait);
float avg_tat = 0;
for(i=0;i<n;i++)
avg_tat = avg_tat + tat[i];
avg_tat = avg_tat/(float)n;
printf("Average Turn Around Time of Process is : %f\n",avg_tat);
}
