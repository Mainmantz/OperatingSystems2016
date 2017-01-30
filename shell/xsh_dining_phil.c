#include <xinu.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

sid32 semarray[10];

void rand_delay2(int max) {
  int mask = disable();
  int r,i;
  r = rand() % (max+1);
  for (i = 0; i < r; i++) {

  }
  restore(mask);
}


void phil(sid32 left, sid32 right, int cycle, sid32 footman, int i, int delay){
  int index = 0; 
  while(1) {
    rand_delay2(delay);
    if(index > cycle) {
      break;
    }
    wait(footman);
    wait(left);
    wait(right);
    printf("Philosopher %d eating, cycle %d\n", i, index);
    index++;
    signal(right);
    signal(left);
    signal(footman);
    printf("Philosopher %d thinking\n", i);
  }
}
shellcmd xsh_dining_phil(int nargs, char *args[]) {
  int i;
  for(i = 0; i < 10; i++) {
    semarray[i] = semcreate(1);  
  }
  sid32 footman = semcreate(1);
  int phill = atoi(args[1]);
  int cycle = atoi(args[2]);
  int delay = atoi(args[3]);
  for(i = 0; i <= phill; i++) {
    int next = i + 1;
    if (i == (phill - 1)) {
      next = 0;
    }
    resume(create(phil, 1024, 20, "phil1", 5, semarray[i], semarray[next], cycle, footman, i, delay));
  }

  return 0;
}

