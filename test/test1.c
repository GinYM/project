#include<stdio.h>
#include<linux/sched.h>
#include <linux/signal.h>
#include <linux/sched.h>
#include <linux/kernel.h>
#include <linux/errno.h>
#include <linux/string.h>
#include <linux/types.h>
#include <linux/ptrace.h>
#include <linux/mman.h>
#include<linux/module.h>

int main()
{
	int i =1;
	task_struct* task = find_process_by_pid(1);
	printf("%d\n",task->state);
	printf("%d\n",task->s);
	printf("pid: %d\n",task->pid);

	return 0;

}
