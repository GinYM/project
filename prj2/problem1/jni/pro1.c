#include<sched.h>
#include<stdio.h>

int main(int argc,char *argv[])
{
	struct sched_param param;
	int maxpri_FIFO,maxpri_NORMAL,maxpri_RR;
	maxpri_FIFO = sched_get_priority_max(SCHED_FIFO);
	maxpri_NORMAL = sched_get_priority_max(SCHED_NORMAL);
	maxpri_RR = sched_get_priority_max(SCHED_RR);
	int current_type;
	if(maxpri_NORMAL == -1 || maxpri_FIFO == -1 || maxpri_RR == -1)
	{
		perror("sched_get_priority_max() failed!\n");
	}
	int pid;
	int type;
	for(;;)
	{
		printf("Please input the pid(-1 to quit):");
		scanf("%d",&pid);
		if(pid == -1)
		{
			break;
		}

		current_type = sched_getscheduler(pid);
		printf("Current scheduler policy: %d\n",current_type);
		printf("Please input the priority type\n");
		printf("0:Normal 1:FIFO 2:RR\n");
		scanf("%d",&type);
		if(type ==0 )
		{
			param.sched_priority=maxpri_NORMAL;
			if(sched_setscheduler(pid,SCHED_NORMAL,&param) ==-1)
			{
				perror("sched_setscheduler() failed!\n");
			}

		}
		else if(type == 1)
		{
			param.sched_priority=maxpri_FIFO;
			if(sched_setscheduler(pid,SCHED_FIFO,&param) ==-1)
			{
				perror("sched_setscheduler() failed!\n");
			}

		}
		else
		{
			param.sched_priority=maxpri_RR;
			if(sched_setscheduler(pid,SCHED_RR,&param) ==-1)
			{
				perror("sched_setscheduler() failed!\n");
			}
		}
		printf("New policy: %d\n",sched_getscheduler(pid));
	}
	return 0;
}
