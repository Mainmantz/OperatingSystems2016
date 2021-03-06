#include <xinu.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <future.h>

int future_prod(future_t* fut) {
  int i, j;
  printf("top of future prod\n");
  j = (int)fut;
  printf("fut = %d\n", j);
  for (i = 0; i < 1000; ++i) {
    j += i;
  }
  printf("after for loop\n");
  printf("value after loop is %d\n", j);
  future_set(fut, j);
  printf("after future set, returning now\n");
  return 1;
}

int future_cons(future_t* fut) {
  int i, status;
  printf("top of future consumer\n");
  status = future_get(fut, &i);
  printf("I returned correctly\n");
  if (status != OK) {
    printf("future_get failed\n");
    return -1;
  }
  printf("it produced %d\n", i);
  return 1;
}
