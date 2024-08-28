/*
写一个用户程序，调用sleep system call实现，执行sleep 10，表示程序等待10个时钟周期。
*/
#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[]){
    if(argc != 2){
        fprintf(2, "must 1 arguments for sleep\n");
        exit(1);    
    }
    int sleepNum = atoi(argv[1]);
    printf("(nothing happens for a little while)\n");
    sleep(sleepNum);
    exit(0);
}