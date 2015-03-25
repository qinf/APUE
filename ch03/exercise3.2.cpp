/*
 * 3.2 编写一个与3.12节中dup2功能相同的函数，要求不调用fcntl函数，并且要有正确的出错处理。
 */
#include "apue.h"
#include <unistd.h>
#include <fcntl.h>
#include <vector>
using std::vector;
int mydup2(int old_fd, int new_fd) {
    long max_fd = sysconf(_SC_OPEN_MAX);
    printf("max fd number: %d\n", max_fd);
    vector<int> vec(max_fd, 0);
    if (-1 == lseek(old_fd, 0, SEEK_CUR)) {
        err_sys("old_fd is not available");
        return -1;
    }
    if (new_fd < 0 || new_fd > max_fd)
        return -1;
    if (new_fd == old_fd)
        return new_fd;
    for (int i = 0; i < max_fd; ++i) {
        int fd = dup(old_fd);
        vec[fd] = 1;
        if (fd == new_fd)
            break;
    }
    for (int i = 0; i < max_fd; ++i) {
        if (vec[i] && i != new_fd) {
            close(i);
        }
    }
    return new_fd;
}
int main() {
    int old_fd = open("./a.txt", O_RDONLY);
    printf("old_fd %d\n", old_fd);
    int new_fd = mydup2(old_fd, 100);
    printf("new_fd %d\n", new_fd);
    exit(0);
}
