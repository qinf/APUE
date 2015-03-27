/*
 * 描述下面两条命令的区别
 * ./a.out > outfile 2>&1
 * ./a.out 2>&1 > outfile
 *
 */
#include "apue.h"
#include <stdio.h>
#include <iostream>
int main() {
    printf("output to stdout\n");
    fflush(stdout);
    fprintf(stderr, "output to stderr\n");
    //std::cout << "output to stdio" << std::endl;
    //std::cerr << "output to stderr" << std::endl;
    return 0;
}
