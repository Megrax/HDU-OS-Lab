#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

char *option[4] = {"cmd1", "cmd2", "cmd3", "exit"};

int toNum(char *str)
{
    for (int i = 0; i < 4; i++)
    {
        if (strcmp(str, option[i]) == 0)
        {
            return i;
        }
    }
    return -1;
}

int create_child(int opNum)
{
    int status = -1;
    pid_t fpid;
    fpid = fork();
    if (fpid < 0)
    {
        printf("Error: Cannot Create Process.\n");
        return -1;
    }
    //子进程
    else if (fpid == 0)
    {
        switch (opNum)
        {
        case 0:
            status = execl("./cmd1", "cmd1", NULL);
            break;
        case 1:
            status = execl("./cmd2", "cmd2", NULL);
            break;
        case 2:
            status = execl("./cmd3", "cmd3", NULL);
            break;
        case 3:
            printf("\nExited Successfully.\n");
            exit(1);
            exit(1);
            break;
        default:
            printf("\nError: Command Not Found.\n");
            break;
        }
    }
    //父进程
    else
    { //返回子进程pid
        wait(&status);
        printf("*********************************************************\n");
    }
}

int main(int argc, char *argv[])
{
    char op[5];
    int opNum;
    printf("Welcome to this simple shell!\n\n");
    while (opNum != 3)
    {
        printf("root@simple-shell $ ");
        scanf("%s", op);
        opNum = toNum(op);
        create_child(opNum);
    }
    return 0;
}
