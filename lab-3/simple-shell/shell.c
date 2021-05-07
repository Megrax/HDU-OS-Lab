#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

char* option[4] = {"cmd1", "cmd2", "cmd3", "exit"};

int toNum(char *str){
    for (int i=0; i<5; i++){
        if(strcmp(str, option[i]) == 0){
            return i;
        }
    }
    return -1;
}

int create_child(int opNum){
    int status = -1;
    pid_t fpid;
    fpid=fork();
    if(fpid<0){
        printf("Error: Cannot Create Process.");
        return -1;
    }
    //子进程
    else if(fpid==0){
        switch(opNum){
            case 0:
            status = execl("./cmd1", "cmd1",  NULL);
            break;
            case 1:
            status = execl("./cmd2", "cmd2",  NULL);
            break;
            case 2:
            status = execl("./cmd3", "cmd3",  NULL);
            break;
            case 3:
            printf("exit\n");
            break;
            default:
            printf("Error: Command Not Found.");
            break;
        }
    }
    //父进程
    else{            //返回子进程pid
        wait(&status);
        printf("Returning...\n");
	printf("*********************************************************\n");
    }
}

int main()
{
    char op[5];
    int opNum;
    while(opNum!=3){
        printf("Welcome to this simple shell!\n simple-shell>");
        scanf("%s", op);
        opNum = toNum(op);
        create_child(opNum);
    }
    return 0;
}
