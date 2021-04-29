show_all_kt.c:

```c
#include "linux/init.h"
#include "linux/module.h"
#include "linux/kernel.h"
#include "linux/sched/signal.h"
#include "linux/sched.h"
MODULE_LICENSE("GPL");
static int __init show_all_kernel_thread_init(void)
{
        struct task_struct *p;
        printk("%-20s%-6s%-6s%-6s%-6s", "Name", "PID", "State", "Prio", "PPID");
        printk("--------------------------------------------");
        for_each_process(p)
        {
                if (p->mm == NULL)
                {
                        printk("%-20s%-6d%-6d%-6d%-6d", p->comm, p->pid, p->state, p->prio,
                                        p->parent->pid);
                }
        }
        return 0;
}
static void __exit show_all_kernel_thread_exit(void)
{
        printk("[ShowAllKernelThread] Module Uninstalled.");
}
module_init(show_all_kernel_thread_init);
module_exit(show_all_kernel_thread_exit);
```

Makefile:

```makefile
obj-m := show_all_kt.o
KDIR := /lib/modules/$(shell uname -r)/build
# 当前路径
PWD := $(shell pwd)
default:
        make -C $(KDIR) M=$(PWD) modules
clean:
        make -C $(KDIR) M=$(PWD) clean
```

show_task_family.c:

```c
#include "linux/init.h"
#include "linux/module.h"
#include "linux/kernel.h"
#include "linux/moduleparam.h"
#include "linux/pid.h"
#include "linux/list.h"
#include "linux/sched.h"
MODULE_LICENSE("GPL");
static int pid;
module_param(pid, int, 0644);
static int __init show_task_family_init(void)
{
struct pid *ppid;
struct task_struct *p;
struct task_struct *pos;
char *ptype[4] = {"[I]", "[P]", "[S]", "[C]"};

ppid = find_get_pid(pid);
if (ppid == NULL)
{
printk("[ShowTaskFamily] Error, PID not exists.\n");
return -1;
}
p = pid_task(ppid, PIDTYPE_PID);

printk("%-10s%-20s%-6s%-6s\n", "Type", "Name", "PID", "State");
printk("------------------------------------------\n");
printk("%-10s%-20s%-6d%-6d\n", ptype[0], p->comm, p->pid, p->state);
printk("%-10s%-20s%-6d%-6d\n", ptype[1], p->real_parent->comm,
p->real_parent->pid, p->real_parent->state);
list_for_each_entry(pos, &(p->real_parent->children), sibling)
{
if (pos->pid == pid)
continue;
printk("%-10s%-20s%-6d%-6d\n", ptype[2], pos->comm, pos->pid,
pos->state);
}
list_for_each_entry(pos, &(p->children), sibling)
{
printk("%-10s%-20s%-6d%-6d\n", ptype[3], pos->comm, pos->pid,
pos->state);
}

return 0;
}

static void __exit show_task_family_exit(void)
{
printk("[ShowTaskFamily] Module Uninstalled.\n");
}

module_init(show_task_family_init);
module_exit(show_task_family_exit);
```

Makefile:

```makefile
obj-m := show_task_family.o
KDIR := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)
default:
                make -C $(KDIR) M=$(PWD) modules
clean:
                make -C $(KDIR) M=$(PWD) clean
```

