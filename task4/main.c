#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>

#define OPTS 20
#define SIZE 100

int valid_opt(const char* opt){
  const char* possible_args[] = {"1c+", "2c+", "2c3", "4c", "8c", "16c"};
  for (int i = 0; i < 6; ++i)
    if (strcmp(opt, possible_args[i]) == 0)
      return 1;
  return 0;
}

int main(int argc, char** argv)
{
  int res = 0;
  char dict_short[SIZE];
  char dict_long[OPTS][SIZE];
  char non_options[SIZE];

  const struct option long_options[] = {
    {"elbrus", required_argument, NULL, 0},
    {NULL, 0, NULL, 0}
  };

  int i = 0;
  int j = 0;
  int k = 0;
  int option_index = -1;
  while ((res = getopt_long(argc, argv, "mcst", long_options, &option_index)) != -1){
    switch(res){
      case 0:
          if (!valid_opt(optarg)){
            printf("Incorrect option: 'key=%s'\n", optarg);
          }
          else{
            snprintf(dict_long[j], 256, "elbrus=%s", optarg);
            j++;
          }
          break;
      case 'm':
      case 'c':
      case 's':
      case 't':
          dict_short[i] = res;
          i++;
          break;
      case '?':
        printf("Incorrect option: '%s'\n", optarg); i++; break;
      default:
          return 1;
    };
    option_index = -1;
  }

  while (optind < argc){
    strcpy(non_options[k], argv[optind]);
    k++;
    optind++;
  }

  printf("Short options: ");
  for (int size = 0; size < i; ++size){
    printf("'%c' ", dict_short[size]);
  }
  printf("\n");

  printf("Long options: ");
  for (int size = 0; size < j; ++size){
    printf("'%s' ", dict_long[size]);
  }
  printf("\n");

  printf("Non options: ");
  for (int size = 0; size < k; ++size){
    printf("'%s' ", non_options[size]);
  }
  printf("\n");

  return 0;
}