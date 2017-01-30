#include <xinu.h>

future_t * future_alloc(future_mode_t mode){
  future_t * f = (future_t *)getmem(sizeof(future_t));
  f->mode = mode;
  f->state = FUTURE_EMPTY;
  f->get_queue = newqueue();
  f->set_queue = newqueue();
  return f;
}
  
