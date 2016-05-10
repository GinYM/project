#include<sched.h>
#include<stdio.h>

int main(int argc,char *argv[])
{
	struct sched_param param;
	int maxpri;
	maxpri = sched_get_priority_max(SCHED_FIFO);
	if(maxpri == -1)
	{
		perror("sched_get_priority_max() failed!\n");
	}
	param.sched_priority=maxpri;
	int pid;
	printf("Please input the pid:");
	scanf("%d",&pid);
	if(sched_setscheduler(pid,SCHED_FIFO,&param) ==-1)
	{
		perror("sched_setscheduler() failed!\n");
	}
	return 0;
}
