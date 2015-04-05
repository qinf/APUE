//#include "apue.h"
#include <dirent.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    int val, dir_fd, fd;
    DIR *dirp;
    if ((dirp = opendir("/")) == NULL)
        err_sys("opendir error");

    if ((dir_fd = dirfd(dirp)) < 0)
        err_sys("dirfd error");
    if ((val = fcntl(dir_fd, F_GETFD)) < 0)    /* 获取文件描述符标志 */
        err_sys("fcntl error");

    printf("%-9s: ","[opendir]");
    if (val & FD_CLOEXEC)
        printf("close-on-exec flag is on\n");
    else
        printf("close-on-exec flag is off\n");

    if (closedir(dirp) < 0)
        err_sys("closedir error");

    if ((fd = open("/", O_DIRECTORY)) < 0)    /* 打开目录，O_DIRECTORY */
        err_sys("open error");
    if ((val = fcntl(fd, F_GETFD)) < 0)    /* 获取文件描述符标志 */
        err_sys("fcntl error");

    printf("%-9s: ","[opendir]");
    if (val & FD_CLOEXEC)
        printf("close-on-exec flag is on\n");
    else
        printf("close-on-exec flag is off\n");

    if (close(fd) < 0)
        err_sys("close error");

    exit(0);
}
