#include <xinu.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

future_t* f_exclusive, * f_shared,
          * f_queue;

shellcmd xsh_prodcons(int nargs, char * args[]) {
  
  f_exclusive = future_alloc(FUTURE_EXCLUSIVE);
  // f_shared    = future_alloc(FUTURE_SHARED);
  // f_queue     = future_alloc(FUTURE_QUEUE);
  
  printf("top of future ex\n");
  // Test FUTURE_EXCLUSIVE
  resume( create(future_cons, 1024, 20, "fcons1", 1, f_exclusive) );
  printf("resumed first cons\n");
  resume( create(future_prod, 1024, 20, "fprod1", 1, f_exclusive) );
  printf("resumed second prod\n");
  /*
  // Test FUTURE_SHARED
  resume( create(future_cons, 1024, 20, "fcons2", 1, f_shared) );
  resume( create(future_cons, 1024, 20, "fcons3", 1, f_shared) );
  resume( create(future_cons, 1024, 20, "fcons4", 1, f_shared) ); 
  resume( create(future_cons, 1024, 20, "fcons5", 1, f_shared) );
  resume( create(future_prod, 1024, 20, "fprod2", 1, f_shared) );

  // Test FUTURE_QUEUE
  resume( create(future_cons, 1024, 20, "fcons6", 1, f_queue) );
  resume( create(future_cons, 1024, 20, "fcons7", 1, f_queue) );
  resume( create(future_cons, 1024, 20, "fcons7", 1, f_queue) );
  resume( create(future_cons, 1024, 20, "fcons7", 1, f_queue) );
  resume( create(future_prod, 1024, 20, "fprod3", 1, f_queue) );
  resume( create(future_prod, 1024, 20, "fprod4", 1, f_queue) );
  resume( create(future_prod, 1024, 20, "fprod5", 1, f_queue) );
  resume( create(future_prod, 1024, 20, "fprod6", 1, f_queue) );
  */

  return 0;

}
