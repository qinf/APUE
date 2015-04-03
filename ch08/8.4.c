#include "apue.h"
#include "pr_exit.h"
#include <sys/wait.h>

int main(void) {
    pid_t pid;
    int status;

    if ((pid = fork()) < 0)
        err_sys("fork error");
    else if (pid == 0)
        exit(7);                /* child */
    if (wait(&status) != pid)   /* wait for child */
        err_sys("wait error");
     pr_exit(status);

     if ((pid = fork()) < 0)
         err_sys("fork error");
     else if (pid == 0)          /* child */
         abort();                /* generates SIGABRT */

     if (wait(&status) != pid)   /* wait for child */
         err_sys("wait error");
     pr_exit(status);            /* print its status */

     if ((pid = fork()) < 0)
         err_sys("fork error");
     else if (pid == 0)          /* child */
         status /= 0;            /* divide by 0 generates SIGFPE */

     if (wait(&status) != pid)   /* wait for child */
         err_sys("wait error");
     pr_exit(status);            /* print its status */
    exit(0);
}
