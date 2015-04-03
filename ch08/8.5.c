/*
 *  通过调用fork两次来避免僵尸进程
 */

#include "apue.h"
#include <sys/wait.h>

int main(void) {
    pid_t pid;

    if ((pid = fork()) < 0) {
        err_sys("fork error");
    } else if (pid == 0) {
        if ((pid = fork()) < 0) {
            err_sys("fork error");
        } else if (pid > 0) {
            exit(0);
        }
        sleep(2);
        printf("second child, parent pid = %d\n", getppid());
        exit(0);
    }
    if (waitpid(pid, NULL, 0) != pid)
        err_sys("pid error");

    exit(0);
}