## OS LAB 1
1.添加系统调用：
  
  335     64      mysetnice            __x64_sys_sys_mysetnice


2.声明系统调用原型：

  asmlinkage long sys_mysetnice(pid_t pid, int flag, int nicevalue, void __user* prio, void __user* nice);

3.实现系统调用服务：

  ```
  SYSCALL_DEFINE5(mysetnice, pid_t, pid, int, flag, int, nicevalue, void __user*, prio, void __user*, nice)
{
        struct pid * ppid;
        struct task_struct * task;
        int curr_nice, curr_prio;

        ppid = find_get_pid(pid);
        task = pid_task(ppid, PIDTYPE_PID);

        curr_nice = task_nice(task);
        curr_prio = task_prio(task);

        if (flag == 1) {
                set_user_nice(task, nicevalue);
                curr_nice = task_nice(task);
                curr_prio = task_prio(task);
        } else if (flag != 0) {
                return EFAULT;
        }

        (void)copy_to_user(nice, &curr_nice, sizeof(curr_nice));
        (void)copy_to_user(prio, &curr_prio, sizeof(curr_prio));

        return 0;
}
  ```

4.测试用例：
```
#include <unistd.h>
#include <sys/syscall.h>
#include <stdio.h>
#define _SYSCALL_MYSETNICE_ 335
#define EFALUT 14

int main()
{
    int pid, flag, nicevalue;
    int prev_prio, prev_nice, cur_prio, cur_nice;
    int result;

    printf("Please input variable(pid, flag, nicevalue): ");
    scanf("%d%d%d", &pid, &flag, &nicevalue);

    result = syscall(_SYSCALL_MYSETNICE_, pid, 0, nicevalue, &prev_prio,
                     &prev_nice);
    if (result == EFALUT)
    {
        printf("ERROR!");
        return 1;
    }

    if (flag == 1)
    {
        syscall(_SYSCALL_MYSETNICE_, pid, 1, nicevalue, &cur_prio, &cur_nice);
        printf("Original priority is: [%d], original nice is [%d]\n", prev_prio,
               prev_nice);
        printf("Current priority is : [%d], current nice is [%d]\n", cur_prio,
               cur_nice);
    }
    else if (flag == 0)
    {
        printf("Current priority is : [%d], current nice is [%d]\n", prev_prio,
               prev_nice);
    }

    return 0;
} 
```