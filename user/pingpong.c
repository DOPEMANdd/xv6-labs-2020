/*
写一个程序，使用unix system calls在两个进程间”ping-pong“一个字节，
使用一对pipe，一个pipe对应一个方向，另外一个pipe对应另外一个方向。
*/
#include <kernel/types.h>
#include <user/user.h>

int main()
{
    // pipe1(p1): 写端父进程，读端子进程(0为读，1为写)
    // pipe2(p2): 写端子进程，读端父进程

    int p1[2], p2[2];
    // 来回传输的字符数组：一个字节
    char buffer[] = {'X'};
    // 传输字符数组的长度
    long length = sizeof(buffer);
    // 父进程写，子进程读的pipe
    pipe(p1);
    // 子进程写，父进程读的pipe
    pipe(p2);
    // 子进程
    if (fork() == 0)
    {
        // 关掉不用的p1[1],p2[0];
        close(p1[1]);
        close(p2[0]);
        // 子进程从pipe1的读端，读取字符串
        if (read(p1[0], buffer, length) != length)
        {
            printf("a--->b read error!");
            exit(1);
        }
        // 打印读取到的字符数组
        printf("%d: received ping\n", getpid());
        // 子进程向pipe2的写端，写入字符数组
        if (write(p2[1], buffer, length) != length)
        {
            printf("a<---b write error!");
            exit(1);
        }
        exit(0);
    }

    // 父进程
    close(p1[1]);
    close(p2[0]);
    // 父进程从pipe1的写端，写入字符串
    if (write(p1[1], buffer, length) != length)
    {
        printf("a--->b write error!");
        exit(1);
    }

    // 父进程从pipe2的读端，读取字符串
    if (read(p2[0], buffer, length) != length)
    {
        printf("a<---b read error!");
        exit(1);
    }
    // 打印读取的字符数组
    printf("%d: received pong\n", getpid());
    // 等待子进程退出
    wait(0);
    exit(0);
}