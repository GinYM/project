#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/init.h>
#include<linux/sched.h>
#include<stdio.h>

int main(int argc,char*argv[])
{
	struct task_struct *store;
	store = pid_task(find_get_pid(0),PIDTYPE_PID);
	if(store == NULL)
	  printf("NULL\n");
	return 0;
}
