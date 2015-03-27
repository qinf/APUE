#include "apue.h"
#include <fcntl.h>
#include <iostream>
int main(int argc, char *argv[]) {
    struct stat buf;
    int i = 0, n;
    char ch;
    if (argc != 3)
        err_sys("wrong arguments");
    stat(argv[1], &buf);
    int fd_rd = open(argv[1], O_RDONLY);
    int fd_wr = open(argv[2], O_RDWR|O_CREAT|O_TRUNC, 777);
    off_t len = buf.st_size;
    for (i = 0; i < len; ++i) {
        if ((n = read(fd_rd, &ch, 1)) == -1) {
            err_sys("read error");
            return -1;
        }
        if (ch == '\0')
            continue;
        else if ((n = write(fd_wr, &ch, n)) == -1) {
            err_sys("write error");
            return -1;
        }
    }
    close(fd_wr);
    close(fd_rd);
    exit(0);
}
