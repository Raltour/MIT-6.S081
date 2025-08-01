#include "kernel/types.h"
#include "user.h"

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Usage: sleep <time>\n");
        exit(1);
    }

    const int sleep_time = atoi(argv[1]);
    sleep(sleep_time);

    exit(0);
}
