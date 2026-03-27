#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

void read_(FILE* in, FILE* out){
    char c;
    while ((c = fgetc(in)) != EOF){
        fputc(c, out);
    }
    fclose(out);
}

void print_(const char* filename, const char* type){
    char c;
    printf("%s:\n", type);
    FILE* f = fopen(filename, "r");
    while ((c = fgetc(f)) != EOF){
        printf("%c", c);
    }
    fclose(f);
}

int main(int argc, char** argv){
    if (argc != 2){
        fprintf(stderr, "expected amount of arguments: 2");
    }
    pid_t pid;
    FILE* file = fopen(argv[1], "r");
    if (file == NULL){
        perror("can not use this file");
        exit(1);
    }
    switch (pid = fork()){
        case -1:
            perror("fork");
            exit(1);
        case 0: {
            // child process
            FILE* child_file = fopen("child_copy.txt", "w");
            rewind(file);
            read_(file, child_file);
            print_("child_copy.txt", "Child");
            exit(0);
        }
        default: {
            // parent process
            FILE* parent_file = fopen("parent_copy.txt", "w");
            rewind(file);
            read_(file, parent_file);
            wait(NULL);
            print_("parent_copy.txt","Parent");
            break;
        }
    }
    fclose(file);
    return 0;
}