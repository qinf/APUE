#include "apue.h"

static void charatatime(char *);

int main(void) {
    pid_t pid;

    if ((pid = fork()) < 0) {
        err_sys("fork error");
    } else if (pid == 0) {
        charatatime("output from child, and I have a dog, and I have a balabala\n");
    } else {
        charatatime("output from parent, and I have a dog, and I have a balabala\n");
    }
    exit(0);
}

static void charatatime(char *str) {
    char *ptr;
    int c;
    setbuf(stdout, NULL);   /* set unbuffered */
    for (ptr = str; (c = *ptr++) != 0; )
        putc(c, stdout);
}
