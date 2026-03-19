#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_SIZE 1000

typedef struct {
  int* a;
  int size;
} thread_s;

void* sorting(void* arr){
  thread_s* packet = (thread_s*)arr;
  for (int i = 0; i < packet->size; ++i){
    for (int j = 0; j < packet->size - 1; ++j){
      if (packet->a[i] < packet->a[j]){
        int tmp = packet->a[i];
        packet->a[i] = packet->a[j];
        packet->a[j] = tmp;
      }
    }
  }
}

int main(int argc, char** argv){
  if (argc != 2){
    fprintf(stderr, "wrong usage\n");
    return -1;
  }
  if (atoi(argv[1]) < 0){
    fprintf(stderr, "wrong number of threads\n");
    return -1;
  }
  int n = atoi(argv[1]);

  int* a = malloc(MAX_SIZE * sizeof(int));
  int actual_size = 0;
  while(scanf("%d", &a[actual_size])){
    actual_size++;
  }

  pthread_t* threads = (pthread_t*)malloc(n * sizeof(pthread_t));
  thread_s* data = (thread_s*)malloc(n * sizeof(thread_s));

  int block = actual_size / n;

  for (int i = 0; i < n; ++i){
    data[i].a = a;
    data[i].size = actual_size;

    pthread_create(&(threads[i]), NULL, sorting, &data[i]);
  }

  for (int j = 0; j < n; ++j){
    pthread_join(threads[j], NULL);
  }

  for (int j = 0; j < actual_size; ++j){
    printf("%d ", a[j]);
  }
  printf("\n");

  free(threads);
  free(data);
  free(a);
  return 0;
}
