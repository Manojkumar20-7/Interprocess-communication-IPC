#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

int main() {
    int fd;
    char *fifo = "/tmp/my_fifo";
    char buffer[100];

    fd = open(fifo, O_RDONLY);
    read(fd, buffer, sizeof(buffer));
    printf("Reader process received: %s\n", buffer);
    close(fd);
    unlink(fifo);
    return 0;
}
