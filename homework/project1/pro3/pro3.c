#include<stdio.h>
#include<unistd.h>


int main()
{
	pid_t pid;
	pid = fork();
	if(pid == 0)
	{
		printf("StudentIDChild:%d\n",getpid());
		execl("/data/misc/testARM","testARM",(char*)NULL);
	}
	else if(pid >0)
	{
		printf("StudentIDParent:%d\n",getpid());
	}
	else
	{
		printf("Error!!\n");
	}
	return 0;
}
