#include<stdio.h>

struct prinfo{
	pid_t parent_pid;
	pid_t pid;
	pid_t first_child_pid;
	pid_t next_sibling_id;
	long state;
	long uid;
	char comm[64];
};


int main(int argc,char*argv[])
{
	pid_t pid;
	pid = fork();
	if(pid == 0)
	{
		printf("StudentIDChild:%d\n",getpid());
	    struct prinfo store[100];
		int a = 100;
		int *size = &a;
		execl("./testArm",356,store,size);
	}
	else if(pid >0)
	{
		printf("StudentIDParent:%d\n",getpid());
	}
	else
	{
		printf("Error!!\n");
	}
	return;
}
