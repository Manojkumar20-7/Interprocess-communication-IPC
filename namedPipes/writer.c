#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

int main() {
    int fd;
    char *fifo = "/tmp/my_fifo";
    char message[] = "Hello from writer process!";

    mkfifo(fifo, 0666);
    fd = open(fifo, O_WRONLY);
    write(fd, message, strlen(message) + 1);
    close(fd);

    return 0;
}
