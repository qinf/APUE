/*
 * vfork用于创建一个新的进程,而该进程的目的是exec一个新程序。
 * vfork创建一个子进程，但它不将父进程的地址空间完全复制到子进程，因为子进程会立即调用exec。
 * 在子进程调用exec或者exit之前，它在父进程的空间中运行。
 * 另外，vfork保证子进程先运行，在它调用exec或者exit之后父进程才可能被调度运行。
 *
 */

#include "apue.h"
int glob = 6;
int main(void) {
    int var;
    pid_t pid;

    var = 88;
    printf("before vfork\n");
    if ((pid = (vfork())) < 0) {
        err_sys("vfork error");
    } else if (pid == 0) {
        glob++; // 更改父进程地址空间中的变量
        var++;
        _exit(0);
    }

    printf("pid = %d, glob = %d, var = %d\n", getpid(), glob, var);
    exit(0);
}
