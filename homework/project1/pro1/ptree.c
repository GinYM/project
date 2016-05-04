#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/init.h>
#include<linux/sched.h>
#include<linux/slab.h>
#include<linux/uaccess.h>
MODULE_LICENSE("Dual BSD/GPL");
#define __NR_hellocall 356


//int __kernel index = -1;

DEFINE_RWLOCK(buf_lock);

struct prinfo{
	pid_t parent_pid;
	pid_t pid;
	pid_t first_child_pid;
	pid_t next_sibling_pid;
	long state;
	long uid;
	char comm[64];
};


void init_prin(struct task_struct*task,struct prinfo*kernel_buf,int*index)
{
	printk("current pid: %d\n",task->pid);
	kernel_buf[*index].pid = task->pid;
	kernel_buf[*index].state = task->state;
	kernel_buf[*index].uid = task->cred->uid;
	if(task->real_parent == NULL)
	  kernel_buf[*index].parent_pid = 0;
	else
	  kernel_buf[*index].parent_pid = task->real_parent->pid;

	get_task_comm(kernel_buf[*index].comm,task);
	if(list_empty(&task->sibling)==1 )
	{
		kernel_buf[*index].next_sibling_pid = 0;
	}
	else
	{
		kernel_buf[*index].next_sibling_pid = list_entry(task->sibling.next,struct task_struct,sibling)->pid;
	}

	if(list_empty(&task->children)==1 )
	{
		kernel_buf[*index].first_child_pid = 0;
	}
	else
	{
		kernel_buf[*index].first_child_pid = list_entry(task->children.next,struct task_struct,sibling)->pid;

	}
	++*index;
}

void dfs(struct task_struct*store,struct prinfo *kernel_buf,int*index)
{
	struct task_struct*task_tmp;
	if(store == NULL)
	{
		printk("it is empty\n");
		return;
	}

	init_prin(store,kernel_buf,index);
	if(list_empty(&(store->children))!=1)
	{
		list_for_each_entry(task_tmp,&store->children,sibling){
			dfs(task_tmp,kernel_buf,index);
		
		}
	}
	
	return;
}

static int(*oldcall)(void);
int ptree(struct prinfo __user *buf,int __user *nr)
{
	int kern_nr;
	kern_nr=0;
	struct prinfo __kernel *kern_buf;
	kern_buf = kmalloc(100*sizeof(struct prinfo),GFP_KERNEL);
	if(buf == NULL || nr == NULL)
	{
		return 0;
	}
	printk("here i come!\n");
	read_lock(&tasklist_lock);
	dfs(&init_task,kern_buf,&kern_nr);
	read_unlock(&tasklist_lock);
	printk("exit!\n ");
	copy_to_user(nr,&kern_nr,sizeof(int));
	printk("number of process: %d\n",kern_nr);
	if(copy_to_user(buf,kern_buf,kern_nr*sizeof(struct prinfo)))
	{
		printk("ERROR");
	}
	kfree(kern_buf);
	return 0;
}
static int addsyscall_init(void)
{
	long *syscall = (long*)0xc000d8c4;
	oldcall = (int(*)(void))(syscall[__NR_hellocall]);
	syscall[__NR_hellocall] = (unsigned long )ptree;
	printk(KERN_INFO "module load!\n");
	return 0;
}

static void addsyscall_exit(void)
{
	long *syscall=(long*)0xc000d8c4;
	syscall[__NR_hellocall] = (unsigned long )oldcall;
	printk(KERN_INFO "module exit!\n");
}

module_init(addsyscall_init);
module_exit(addsyscall_exit);
		
