/*
 * 线程清理处理程序(thread cleanup handler)
 * #include <pthread.h>
 * void pthread_cleanup_push(void (*rtn)(void *), void *arg);
 * void pthread_cleanup_pop(int execute);
 * 当线程执行以下动作是调用清理函数，调用参数为arg，清理函数rtn的调用顺序是由
 * pthread_cleanup_push函数来安排的。
 *  - 调用pthread_exit时。
 *  - 响应取消请求时。
 *  - 用非零execute参数调用pthead_cleanup_pop时。
 *  如果execute为0时，清理函数不被调用。无论何时，phtread_cleanup_pop都将删除上次pthread_cleanup_push调用建立的处理程序。
 *
 */

#include "apue.h"
#include <pthread.h>

void cleanup(void *s) {
    printf("cleanup: %s\n", (char*)s);
}

void *thr_fn1(void *arg) {
    printf("thread 1 start\n");
    pthread_cleanup_push(cleanup, "thread 1 first handler");
    pthread_cleanup_push(cleanup, "thread 1 second handler");
    printf("thread 1 push complete\n");
    if (arg)
        return ((void*)1);
    pthread_cleanup_pop(0);
    pthread_cleanup_pop(0);
    return ((void*)1);
}

void *thr_fn2(void *arg) {
    printf("thread 2 start\n");
    pthread_cleanup_push(cleanup, "thread 2 first handler");
    pthread_cleanup_push(cleanup, "thread 2 second handler");
    printf("thread 2 push complete\n");
    if (arg)
        pthread_exit((void*)2);
    pthread_cleanup_pop(0);
    pthread_cleanup_pop(0);
    pthread_exit((void*)2);
}

int main(void) {
    int err;
    pthread_t tid1, tid2;
    void *tret;

    err = pthread_create(&tid1, NULL, thr_fn1, (void*)1);
    if (err != 0)
        err_quit("can't create thread 1: %s\n", strerror(err));
    err = pthread_create(&tid2, NULL, thr_fn2, (void*)2);
    if (err != 0)
        err_quit("can't create thread 2: %s\n", strerror(err));
    err = pthread_join(tid1, &tret);
    if (err != 0)
        err_quit("can't join with thread 1: %s\n", strerror(err));
    printf("thread 1 exit code %d\n", (int)tret);
    err = pthread_join(tid2, &tret);
    if (err != 0)
        err_quit("can't join with thread 2: %s\n", strerror(err));
    printf("thread 2 exit code %d\n", (int)tret);
    exit(0);
}
