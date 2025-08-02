#include "kernel/types.h"
#include "user.h"

#define MAX 35
#define SIZE 34

void pipeline(int curr_pipe[2], int n) {
    close(curr_pipe[1]);
    int p;
    read(curr_pipe[0], &p, 4);
    printf("prime %d\n", p);

    int num[n];
    int cnt = 0;
    int read_num;
    while (read(curr_pipe[0], &read_num, 4) != 0) {
        if (read_num % p != 0) {
            num[cnt++] = read_num;
        }
    }

    close(curr_pipe[0]);

    int next_pipe[2];
    pipe(next_pipe);

    int pid = fork();
    if (pid == 0) {
        if (cnt != 0) {
            pipeline(next_pipe, cnt);
        }
        exit(0);
    } else {
        close(next_pipe[0]);
        for (int i = 0; i < cnt; i++) {
            write(next_pipe[1], &num[i], 4);
        }
        close(next_pipe[1]);
        wait(&pid);
    }
}

int main() {
    int next_pipe[2];
    pipe(next_pipe);

    int pid = fork();
    if (pid == 0) {
        pipeline(next_pipe, MAX);
        exit(0);
    } else {
        close(next_pipe[0]);
        for (int i = 2; i <= MAX; i++) {
            write(next_pipe[1], &i, 4);
        }
        close(next_pipe[1]);
        wait(&pid);
        exit(0);
    }
}