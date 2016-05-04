#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>

struct prinfo{
	pid_t parent_pid;
	pid_t pid;
	pid_t first_child_pid;
	pid_t next_sibling_pid;
	long state;
	long uid;
	char comm[64];
};

int stack[100];
int lastIndex = -1;

int top()
{
	if(lastIndex != -1)
	  return stack[lastIndex];
	else
	  return -1;
}

void push(int num)
{
	stack[++lastIndex] = num;
}

int pop()
{
	if(lastIndex != -1)
	  return stack[lastIndex--];
	else
	  return -1;
}


int main(){
	struct prinfo*store;
	store = malloc(100*sizeof(struct prinfo));
	printf("This is a test:\n\n");
	int size = 0;;
	syscall(356,store,&size);
	int index;
	for(index=0;index<size;index++)
	{
		if(lastIndex == -1)
		  push(store[index].pid);
		else
		{
			while(lastIndex != -1 && store[index].parent_pid != top())
			{
				pop();
			}
			if(lastIndex == -1)
			{
				push(store[index].pid);
			}
			else
			{
			int i;
			for(i=0;i<=lastIndex;i++)
			{
				printf("      ");
			}
			push(store[index].pid);
			}
			
		}
			printf("%s,%d,%ld,%d,%d,%d,%d\n",store[index].comm,store[index].pid,store[index].state,store[index].parent_pid,store[index].first_child_pid,store[index].next_sibling_pid,store[index].uid);
	}
	printf("Test End!:\n\n");
	free(store);
	return 0;
}
