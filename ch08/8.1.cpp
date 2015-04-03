/*
 * #include <unistd.h>
 * pid_t fork(void);
 * return value: chlid process return 0, parent process return child's gid, error return -1
 */

/*
 * if redirect the output to a temp file by uisng `./a.out > temp.out`
 * look the output result: `cat temp.out`
 * ---- temp.out ----
 * a write to stdout
 * before fork
 * pid = 2889, glob = 7, var = 89
 * before fork
 * pid = 2888, glob = 6, var = 88
 * ---- end temp.out ----
 *
 * why there are two `before fork`?
 * Note that the write function is not buffered. Because write is called
 * before the fork, its data is written once to standard output. The standard I/O library,
 * however, is buffered. Recall from Section 5.12 that standard output is line buffered if it’s
 * connected to a terminal device; otherwise, it’s fully buffered. When we run the
 * program interactively, we get only a single copy of the first printf line, because the
 * standard output buffer is flushed by the newline. When we redirect standard output to
 * a file, however, we get two copies of the printf line. In this second case, the printf
 * before the fork is called once, but the line remains in the buffer when fork is called.
 * This buffer is then copied into the child when the parent’s data space is copied to the
 * child. Both the parent and the child now have a standard I/O buffer with this line in it.
 * The second printf, right before the exit, just appends its data to the existing buffer.
 * When each process terminates, its copy of the buffer is finally flushed.
 */

#include "apue.h"

int glob = 6;   /* external variable in initialized data */
char buf[] = "a write to stdout\n";

int main(void) {
    int var;    /* auto variable on the satck */
    pid_t pid;
    var = 88;
    if (write(STDOUT_FILENO, buf, sizeof(buf) - 1) != sizeof(buf) - 1)
        err_sys("write error");
    printf("before fork\n");    /* we don't flush stdout */

    if ((pid = fork()) < 0) {
        err_sys("fork error");
    } else if (pid == 0) {  /* child */
        glob++;             /* modify variables */
        var++;
    } else {
        sleep(2);
    }

    printf("pid = %d, glob = %d, var = %d\n", getpid(), glob, var);
    exit(0);
}
