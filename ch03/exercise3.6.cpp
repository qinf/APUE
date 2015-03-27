/*
 *  习题3.6
 *  If you open a file for read–write with the append flag, can you still read from anywhere in
 *  the file using lseek? Can you use lseek to replace existing data in the file? Write a
 *  program to verify this.
 *
 *  可以通过lseek函数从文件的任意位置读取，但是write只能在文件末尾。
 */

#include "apue.h"
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
int main() {
    char buf[1024] = {0};
    char buf_w[] = "WRITE";
    int n;
    int fd;
    if ((fd= open("./outfile", O_RDWR | O_APPEND)) == -1)
        err_sys("open error");
    if ((lseek(fd, 0, SEEK_SET)) == -1)
        err_sys("leek error");
    if ((n = read(fd, buf, 3)) < 0)
       err_sys("read error:");
    printf("%s\n", buf);
//    if ((lseek(fd, 0, SEEK_SET)) == -1)
//        err_sys("leek error");
//    if ((write(fd, buf_w, 4)) == -1)
//        err_sys("write error");
//    exit(0);
}
