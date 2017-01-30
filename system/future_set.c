#include <xinu.h>

int future_set(future_t* f, int value){
  //  pid32 res;

  //future exclusive 
  printf("top of future set\n");
  if(f->mode == FUTURE_EXCLUSIVE) {
    printf("passed future exclusive check\n");
    if(f->state == FUTURE_EMPTY) { 
      printf("passed future empty check\n");
      printf("this is the value %d\n", value);
      f->value = value;
      printf("this should be the same as the number above %d\n", f->value);
      f->state = FUTURE_READY;
      printf("in future empty claus set value set ready returning now\n");
      return 1;
    }
    if(f->state == FUTURE_WAITING){
      printf("passed future waiting check\n");
      printf("this is the value %d\n", value);
      f->value = value;
      f->state = FUTURE_READY;
      printf("this should be the same as the number above %d\n", f->value);

      //res = dequeue(f->get_queue);
      // printf("here is what i am resuming: %d\n", res);
      resume(4);
      printf("set value and resumed returning now\n");
      return 1;
    }
    if(f->state == FUTURE_READY) {
      printf("future set shouldnt be here\n");
      return -1;
    }
  }
  return 0;
}
// if(f->mode != FUTURE_SHARED) {
    







    /*if(isempty(f->get_queue) == 0) {
      f->value = value;
      res = dequeue(f->get_queue);
      resume(res);
      suspend(getpid());
    } else {
      enqueue(f->set_queue, getpid());
      suspend(getpid());
    }
  } else {
    return SYSERR;
    }
} else {
  return SYSERR;
 }
} 
    */
