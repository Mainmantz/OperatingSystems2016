#include <xinu.h>
#include <string.h>
#include <stdio.h>

shellcmd xsh_91(int nargs, char *args[]) {

  struct memblk *fuck;
  fuck = &memlist;

  
  while(fuck != NULL) {
    printf("location = %x \n", fuck);
    printf("size = %u\n", fuck->mlength);
    fuck = fuck->mnext;
  } 
  
  return 0;

}
