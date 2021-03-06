#include "apue.h"
#include "system.h"
#include "pr_exit.h"

int main(int argc, char *argv[]) {
    int status;
    if (argc < 2) {
        err_sys("command-line argument required");
    }

    if ((status = system(argv[1])) < 0)
        err_sys("system() error");
    pr_exit(status);
    exit(0);
}
