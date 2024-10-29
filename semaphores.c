#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <unistd.h>

int main() {
    sem_t *sem = sem_open("/semaphore", O_CREAT, 0644, 1);
    
    int shm_fd = shm_open("/shm", O_CREAT | O_RDWR, 0666);
    ftruncate(shm_fd, 1024);

    char *shared_mem = (char *) mmap(0, 1024, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

    if (fork() == 0) {
        sprintf(shared_mem, "Hello from child process!");
        printf("Child wrote to shared memory.\n");
        sem_post(sem);
        exit(0);
    } 
    else {
        sem_wait(sem);
        sleep(1);
        printf("Parent reads from shared memory: %s\n", shared_mem);
        // sem_post(sem);
        wait(NULL);
        munmap(shared_mem, 1024);
        shm_unlink("/my_shm");
        sem_close(sem);
        sem_unlink("/my_semaphore");
    }
    return 0;
}
