#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>

int main(){
    int pipefds[2];
    pid_t pid;
    char write_msg[]="Hello from parent";
    char read_msg[100];

    if(pipe(pipefds)==-1){
        perror("pipe");
        return 1;
    }
    pid = fork();
    
    if(pid==-1){
        perror("fork");
        return 1;
    }
    if(pid==0){
        close(pipefds[1]);
        read(pipefds[0],read_msg,sizeof(read_msg));
        printf("Child process received: %s\n",read_msg);
        close(pipefds[0]);
    }
    else{
        close(pipefds[0]);
        write(pipefds[1],write_msg,strlen(write_msg)+1);
        printf("Parent process sent the message\n");
        close(pipefds[1]);
    }
    return 0;
}