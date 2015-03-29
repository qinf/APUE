/*
 *  utime修改文件的访问和修改时间
 *  #include <uinstd.h>
 *
 *  int utime(const char *pathname, const struct utimebuf *times);
 *  return value: ture 0, false -1
 *
 *  struct utimebuf {
 *      time_t actime;  // access time
 *      time_t modtime; // modification time
 *  }
 *
 *  stat函数获取此文件的信息结构
 *  #include <sys/stat.h>
 *
 *  int stat(const char *restrict pathname, struct stat *restrict buf);
 *  int fstat(int fields, struct *buf); // 打开文件描述符的有关信息
 *  int lstat(const char *restrict pathname, struct stat *restrict buf); // lstat返回符号连接的有关信息，不是链接引用的信息
 *  return value: true 0, false -1
 *  struct stat {
 *  mode_t st_mode; // file type & mode (permissions)
 *      ino_t st_ino; // i-node number (serial number)
 *      dev_t st_dev; // device number (file system)
 *      dev_t st_rdev; // device number for special files
 *      nlink_t st_nlink; // number of links
 *      uid_t st_uid; // user ID of owner
 *      gid_t st_gid; // group ID of owner
 *      off_t st_size; // size in bytes, for regular files
 *      struct timespec st_atim; // time of last access
 *      struct timespec st_mtim; // time of last modification
 *      struct timespec st_ctim; // time of last file status change
 *      blksize_t st_blksize; // best I/O block size
 *      blkcnt_t st_blocks; // number of disk blocks allocated
 *  };
 *
 */

#include "apue.h"
#include <fcntl.h>
#include <utime.h>

int main(int argc, char *argv[]) {
    int i, fd;
    struct stat statbuf;
    struct utimbuf timebuf;

    for (i = 1; i < argc; ++i) {
        if (stat(argv[1], &statbuf) < 0) {  // 返回与文件有关的信息结构
            err_ret("%s: stat error", argv[i]);
            continue;
        }
        if ((fd = open(argv[i], O_RDWR | O_TRUNC)) < 0) {   // 截断文件
            err_ret("%s: open error", argv[i]);
            continue;
        }
        close(fd);
        timebuf.actime = statbuf.st_atime;  // 访问时间
        timebuf.modtime = statbuf.st_mtime; // 修改时间
        if (utime(argv[i], &timebuf) < 0) {
            err_ret("%s: utime error", argv[i]);
            continue;
        }
    }
    exit(0);
}
