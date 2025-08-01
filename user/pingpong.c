#include "kernel/types.h"
#include "user.h"

int main() {
    int parent_to_child[2];
    int child_to_parent[2];
    pipe(parent_to_child);
    pipe(child_to_parent);

    int pid = fork();
    if (pid == 0) {
        char b;
        read(parent_to_child[0], &b, 1);
        printf("%d: received ping\n", getpid());
        write(child_to_parent[1], &b, 1);

        close(child_to_parent[0]);
        close(child_to_parent[1]);
        close(parent_to_child[0]);
        close(parent_to_child[1]);

        exit(0);
    } else {
        write(parent_to_child[1], "r", 1);
        close(parent_to_child[0]);
        close(parent_to_child[1]);

        char buf;
        read(child_to_parent[0], &buf, 1);
        close(child_to_parent[0]);
        close(child_to_parent[1]);

        printf("%d: received pong\n", getpid());

        exit(0);
    }
}