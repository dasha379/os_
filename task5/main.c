#include <sys/types.h>
#include <sys/fcntl.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
    // open syscall
    int fd = open("b.txt", O_RDONLY);
    if (fd == -1){
        // using perror
        perror("Can't open file");

        // using errno
        switch (errno){
            case EEXIST: printf("Errno = EEXIST\n"); break;
            case EISDIR: printf("Errno = EISDIR\n"); break;
            case EACCES: printf("Errno = EACCES\n"); break;
            case ENAMETOOLONG: printf("Errno = ENAMETOOLONG\n"); break;
            case ENOENT: printf("Errno = ENOENT\n"); break;
            case ENOTDIR: printf("Errno = ENOTDIR\n"); break;
            case ENXIO: printf("Errno = ENXIO\n"); break;
            case ENODEV: printf("Errno = ENODEV\n"); break;
            case EROFS: printf("Errno = EROFS\n"); break;
            case ETXTBSY: printf("Errno = ETXTBSY\n"); break;
            case EFAULT: printf("Errno = EFAULT\n"); break;
            case ELOOP: printf("Errno = ELOOP\n"); break;
            case ENOSPC: printf("Errno = ENOSPC\n"); break;
            case ENOMEM: printf("Errno = ENOMEM\n"); break;
            case EMFILE: printf("Errno = EMFILE\n"); break;
            case ENFILE: printf("Errno = ENFILE\n"); break;
        }
    }

    // stat syscall
    struct stat st;
    const char* name = "../dir";
    if (stat(name, &st) == -1){
        perror("Error");
    }

}
