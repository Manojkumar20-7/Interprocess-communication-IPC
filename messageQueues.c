#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<sys/wait.h>


struct message{
    long msg_type;
    char msg_text[100];
};

int main(){
    key_t key;
    int msg_id;

    key=ftok("/temp",65);
    msg_id=msgget(key,0666|IPC_CREAT);
    struct message msg;

    if(fork()==0){
        msg.msg_type=1;
        strcpy(msg.msg_text,"Hello from child");
        msgsnd(msg_id,&msg,sizeof(msg.msg_text),0);
        printf("Child process sent message\n");
    }
    else{
        wait(NULL);
        msgrcv(msg_id,&msg,sizeof(msg.msg_text),1,0);
        printf("Parent process received message: %s\n",msg.msg_text);
        msgctl(msg_id,IPC_RMID,NULL);
    }
    return 0;
}