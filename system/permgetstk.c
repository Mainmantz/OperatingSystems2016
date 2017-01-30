#include <xinu.h>

char *permgetstk(uint32 nbytes)
{
                  
  struct  memblk  *prev, *curr;   
  struct  memblk  *fits, *fitsprev; 

  intmask mask; 
  mask = disable();
  if (nbytes == 0) {
    restore(mask);
    return (char *)SYSERR;
  }

  nbytes = (uint32) roundmb(nbytes); 

  prev = &memlist;
  curr = memlist.mnext;
  fits = NULL;
  fitsprev = NULL;  

  while (curr != NULL) {                
    if (curr->mlength >= nbytes) {  
      fits = curr;           
      fitsprev = prev;
    }
    prev = curr;
    curr = curr->mnext;
  }

  if (fits == NULL) {                    
    restore(mask);
    return (char *)SYSERR;
  }
  if (nbytes == fits->mlength) {          
    fitsprev->mnext = fits->mnext;
  } else {                               
    fits->mlength -= nbytes;
    fits = (struct memblk *)((uint32)fits + fits->mlength);
  }

  memlist.mlength -= nbytes;
  restore(mask);
  return (char *)((uint32) fits + nbytes - sizeof(uint32));

}


