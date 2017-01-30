#include <xinu.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void rand_delay1(int max) {
  int mask = disable();
  int r,i;
  r = rand() % (max+1);
  for (i = 0; i < r; i++) {

  }
  restore(mask);
}

void lightswitch(sid32 sem, sid32 mutex, int lock) {
  int counter;
  //sid32 mutex;
  mutex = semcreate(1);
  if (lock == 0) {
    wait(mutex);
    counter++;
    if (counter == 1) {
      wait(sem);
    }
    signal(mutex);
  }
  else if (lock == 1) {
    wait(mutex);
    counter--;
    if (counter == 0) {
      signal(sem);
    }
    signal(mutex);
  }

}

void writers(sid32 turnstile,sid32 room,int write_cycle,int delay) {
  int index;
  while(1) {
    rand_delay1(delay);
    if (write_cycle < index) {
      break;
    }
    wait(turnstile);
    index++;
    printf("Writer: %d\n",index);
    signal(turnstile);
    signal(room);
  }
}
void readers1(sid32 turnstile, sid32 room,sid32 mutex,int read_cycle,int delay) {
  int index1;
  while (1) {
    rand_delay1(delay);
    if (read_cycle < index1) {
      break;
    }
    wait(turnstile);
    signal(turnstile);

    lightswitch(room,mutex,0);

    index1++;
    //code goes here
    printf("Read: %d\n",index1);
    lightswitch(room,mutex,1);
  }
}
shellcmd xsh_readers_writers(int nargs, char *args[]) {
  sid32 turnstile;
  sid32 room;
  sid32 mutex;
  mutex = semcreate(1);
  turnstile = semcreate(1);
  room = semcreate(1);
  //cycle = atoi(args[3]);

  int num_writers,num_readers,write_cycles,read_cycles,delay;
  num_writers = atoi(args[1]);
  num_readers = atoi(args[2]);
  write_cycles = atoi(args[3]);
  read_cycles = atoi(args[4]);
  delay = atoi(args[5]);

  int i,j;
  //read_switch = semcreate();
  for (i = 0; i < num_readers; i++) {
    resume(create(readers1,1000,20,"reader",5,turnstile,room,mutex,read_cycles,delay));
  }
  for (j = 0; j < num_writers; j++) {
    resume(create(writers,1000,20,"writer",4,turnstile, room,write_cycles,delay));
  }
  return 0;
}
