#include <xinu.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int inc = 0x0;

void rand_delay(int max) {
  int mask = disable();
  int r,i;
  r = rand() % (max+1);
  for (i = 0; i < r; i++) {
  
  }
  restore(mask);
}

void prod(int time, sid32 mutex, sid32 spaces, sid32 items, int bytes) {
  int index = 0x0;
  int inc = 0x0;
  while(inc < bytes) {
    rand_delay(time);
    wait(spaces);
    wait(mutex);
    if(index > 0xff) {
      index = 0x0;
    } else {
      index = index + 0x8;
    }
    inc = inc + 0x8;

    printf("Count value is 0x%x\n", index);
    signal(mutex);
    signal(items);
  }
}

void cons(int time, sid32 mutex, sid32 spaces, sid32 items, int bytes) {
  int inc = 0;
  while(inc < bytes) {
    rand_delay(time);
    wait(items);
    wait(mutex);
    printf("Buffer value 0x%x\n", inc);
    inc = inc + 0x8;
    signal(mutex);
    signal(spaces);
  }
}

shellcmd xsh_producer_consumer(int nargs, char *args[]) {
  sid32 mutex;
  sid32 items;
  sid32 spaces;
  int space = atoi(args[1]);
  int timed = atoi(args[3]);
  int bytes = atoi(args[2]);

  items = semcreate(0);
  mutex = semcreate(1);
  spaces = semcreate(space);

  resume(create(prod, 1024, 20, "prodd", 5, timed, mutex, spaces, items, bytes));
  resume(create(cons, 1024, 20, "conss", 5, timed, mutex, spaces, items, bytes));
  return 0;

}








