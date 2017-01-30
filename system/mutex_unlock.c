#include  <xinu.h>
int test_and_set(mutex_t*, int, int);

syscall mutex_unlock(mutex_t * lock) { 
  while(test_and_set(lock, 1, 0));
  yield();
  return OK;
}
