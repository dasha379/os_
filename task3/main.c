#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100
#define MAX_LENGTH 128

int plain_sort(const char* s1, const char* s2){
  int n = strlen(s1);
  int m = strlen(s2);
  int eq = 0;
  int less = 0;
  if (n > m)
    return 1;
  else if (n < m)
    return -1;
  else{
    for (int i = 0; i < n; ++i){
      if (s1[i] > s2[i]){
        return 1;
      }
      else if (s1[i] == s2[i])
        eq += 1;
    }
    if (eq == n)
      return 0;
    return -1;
  }
}

int main(int argc, char** argv){
  if (argc != 4){
    fprintf(stderr, "wrong usage\n");
    return -1;
  }
  char* sort_type = argv[3];
  if (!(strcmp(sort_type, "plain") == 0 || strcmp(sort_type, "lex") == 0 || strcmp(sort_type, "rplain") == 0 || strcmp(sort_type, "rlex") == 0)){
    fprintf(stderr, "unsupported type of sorting =(\n");
    return -1;
  }

  FILE* in_file = fopen(argv[1], "r");
  if (in_file == NULL) {
        printf("can not open the file %s\n", argv[1]);
        return -1;
  }
  char** arr_char = malloc(MAX_SIZE * sizeof(char*));
  char line[MAX_LENGTH];
  int count = 0;
  while (fgets(line, sizeof(line), in_file)){
    size_t len = strlen(line);
    if (line[0] == '\n'){
      continue;
    } else {
      arr_char[count] = malloc((len + 1)*sizeof(char));
      strcpy(arr_char[count], line);
    }
    count++;
  }
  if (count == 0){
    fprintf(stderr, "empty file\n");
    return -1;
  }
}