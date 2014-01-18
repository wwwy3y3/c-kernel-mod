#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/module.h>

MODULE_LICENSE("GPL");  

int init_func(void)
{
	struct task_struct *task;
	for_each_process(task)
	{
		printk("%s [%d]\n",task->comm , task->pid);
	}

	return 0;
}

void cleanup_func(void)
{
	printk(KERN_INFO "goodbye!.\n");
}

  
module_init(init_func);
module_exit(cleanup_func);