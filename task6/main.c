#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <stdio.h>

int main(int argc, char** argv){
    int type;
    struct stat st;
    struct tm* timeinfo;
    char buf[15];
    if (argc != 2){
        fprintf(stderr, "expected amount of arguments: 2\n");
    }
    const char* name = argv[1];
    if (stat(name, &st) < 0){
        printf("%s does not exist", name);
        return 0;
    }

    type = (st.st_mode & __S_IFMT);
    if (type != __S_IFREG)
        fprintf(stderr, "input is not a regular file\n");

    printf("inode: %ld\n", st.st_ino);

    printf("File: %s\n", argv[1]);
    printf("Size: %ld bytes\n", st.st_size);
    printf("Blocks: %ld\n", st.st_blocks);

    // last read/access to the file
    timeinfo = localtime(&st.st_atime);
    strftime(buf, 15, "%b %d %H:%M", timeinfo);
    printf("Time of last access: %s\n", buf);

    // last change of the file
    timeinfo = localtime(&st.st_mtime);
    strftime(buf, 15, "%b %d %H:%M", timeinfo);
    printf("Time of last modification: %s\n", buf);

    // last inode change (chmod, chown, etc)
    timeinfo = localtime(&st.st_ctime);
    strftime(buf, 15, "%b %d %H:%M", timeinfo);
    printf("Time of last changing: %s\n", buf);

    printf("Amount of hard links: %ld\n", st.st_nlink);

}