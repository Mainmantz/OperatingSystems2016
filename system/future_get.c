
#include <xinu.h>

syscall	future_get(future_t* f, int * value) {
  //	intmask mask
  pid32 res;
  //future exclusive

  printf("top of future get\n");
  if(f->mode == FUTURE_EXCLUSIVE) {
    if(f->state == FUTURE_EMPTY) {
      //      enqueue(f->get_queue, getpid());
      f->state = FUTURE_WAITING;
      printf("about to suspend at future get\n");
      printf("here is what i am suspending: %d\n", getpid());
      suspend(getpid());
    }

    printf("just before future get ready check\n");    
    if(f->state == FUTURE_READY){
      printf("pass future get ready check\n");
      printf("here is the value in the future get %d\n", f->value);
      *value = f->value;
      f->state = FUTURE_EMPTY;
      printf("bottom of future get ready check\n");
      return 1;
    }
  }
  return 0;
}
  /*
	pid32 res;
	if (f->state == FUTURE_EMPTY || isempty(f->set_queue) == 1) {
          enqueue(f->get_queue, curr);
	  suspend(curr);
	} else if (isempty(f->set_queue) == 0) {
	  //res = dequeue(f->set_queue);
	  resume(res);
	  enqueue(f->get_queue, curr);
	  suspend(curr);
	}

	if(f->state == FUTURE_READY) {
	  if(f->mode != FUTURE_SHARED){
	    f->state = FUTURE_EMPTY;
	  }
	  value = f->value;

	  if(f->mode == FUTURE_SHARED) {
	    if(isempty(f->get_queue) == 0) {
	      res = dequeue(f->get_queue);
	      resume(res);
	    }
	  }

	  return OK;	

	} else {
	  return SYSERR;
	}
}

  */
