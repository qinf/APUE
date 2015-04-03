#include "apue.h"
#include <errno.h>
#include <unistd.h>

int system(const char* cmd) {   /* version without signal handling */
    pid_t pid;
    int status;

    if (cmd == NULL)
        return(1);
    if ((pid = fork()) < 0) {
        status = -1;    /* probably out of processes */
    } else if (pid == 0) {
        execl("/bin/sh", "sh", "-c", cmd, (char*)0);
        _exit(127);     /* execl error */
    } else {
        while (waitpid(pid, &status, 0) < 0) {
            if (errno != EINTR) {
                status = -1;    /* error other than EINTR from waitpid() */
                break;
            }
        }
    }
    return (status);
}
