#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

void find(char *path, char *name);

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("use three arguments.");
        exit(-1);
    }
    find(argv[1], argv[2]);
    exit(0);
}

void find(char *path, char *name) {
    char buf[512];
    int fd;
    struct dirent de;
    struct stat st;

    if((fd = open(path, 0)) < 0){
        fprintf(2, "cannot open %s\n", path);
        return;
    }

    strcpy(buf, path);
    char *p = buf + strlen(buf);
    *p++ = '/';

    while(read(fd, &de, sizeof(de))) {
        if(de.inum == 0)
            continue;
        if(!strcmp(".", de.name))
            continue;
        if(!strcmp("..", de.name))
            continue;

        memcpy(p, de.name, DIRSIZ);
        p[DIRSIZ] = 0;
        stat(buf, &st);
        switch (st.type) {
            case T_DIR:
                find(buf, name);
                break;
            case T_FILE:
                if (strcmp(name, de.name) == 0) {
                    printf("%s\n", buf);
                }
                break;
        }
    }
}