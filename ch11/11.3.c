/*
 * #include <pthread.h>
 * void pthread_exit(void *rval_ptr);
 * rval_ret是一个无类型指针，与传给启动例程的单个参数类似。进程的其他线程可以通过调用
 * pthread_join函数访问到这个指针。
 *
 * int pthread_join(pthread_t thread, void **rval_ptr);
 * return value: ture 0, false errno
 * 调用线程将被阻塞知道指定的线程调用pthread_exit、或从启动例程中返回或者被取消。
 *
 */

#include "apue.h"
#include <pthread.h>

struct foo {
    int a, b, c, d;
};

void printfoo(const char *s, const struct foo *fp) {
    printf(s);
    printf(" structure at 0x%x\n", (unsigned)fp);
    printf(" foo.a = %d\n", fp->a);
    printf(" foo.b = %d\n", fp->b);
    printf(" foo.c = %d\n", fp->c);
    printf(" foo.d = %d\n", fp->d);
}

void *thr_fn1(void *arg) {
    struct foo foo = {1, 2, 3, 4};
    printfoo("thread 1:\n", &foo);
    pthread_exit((void*)&foo);
}

void *thr_fn2(void *arg) {
    printf("thread 2: ID is %d\n", pthread_self());
    pthread_exit((void*)0);
}

int main(void) {
    int err;
    pthread_t tid1, tid2;
    struct foo *fp;

    err = pthread_create(&tid1, NULL, thr_fn1, NULL);
    if (err !=0)
        err_quit("can't create thread 1: %s\n", strerror(err));
    err = pthread_join(tid1, (void*)&fp);
    if (err != 0)
        err_quit("can't join with thread 1: %s\n", strerror(err));
    sleep(1);
    printf("parent starting second thread\n");
    err = pthread_create(&tid2, NULL, thr_fn2, NULL);
    if (err != 0)
        err_quit("can't create thread 2: %s\n", strerror(err));
    sleep(1);
    printfoo("parent:\n", fp);
    exit(0);
}
