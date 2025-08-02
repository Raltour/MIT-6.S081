#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
    int pid = fork();
    if (pid == 0) {
        exec(argv[1], argv + 1);
        printf("exec failed\n");
        exit(1);
    } else {
        wait(&pid);
        exit(0);
    }
}
