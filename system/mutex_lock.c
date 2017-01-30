#include <xinu.h>
int currworms;

syscall test_and_set(mutex_t *lock, int val, int set) {
  intmask mask;
  mask = disable();
  int prev = *lock;
  if(*lock == val) {
    *lock = set;
  }
  restore(mask);
  return prev;
}

syscall mutex_lock(mutex_t *lock){
  while(!test_and_set(lock, 0, 1));
  return OK;
}


