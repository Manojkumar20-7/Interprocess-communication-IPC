#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/ipc.h>
#include<sys/wait.h>
#include<sys/shm.h>

int main(){
    key_t key=ftok("/sharedMemory",'A');
    int shmid=shmget(key,1024,0666|IPC_CREAT);
    
    if(fork()==0){
        char *str=(char *)shmat(shmid,(void *)0,0);
        printf("Child process reads: %s\n",str);
        shmdt(str);
    }
    else{
        char *str=(char *)shmat(shmid,(void *)0,0);
        strcpy(str,"Hello from parent");
        wait(NULL);
        shmdt(str);
        shmctl(shmid,IPC_RMID,NULL);
    }
}