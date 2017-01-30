#include <xinu.h>
#include <stdio.h>

int procs[100];

mutex_t wormlock = 0;
int worms = 10;
int currworm = 10;


int baby(int id, mutex_t *t, int eat) {
  int tummy = eat;
  while(1) {
    mutex_lock(t);
    if((currworm > 0) && (tummy > 0)) {
      currworm--;
      tummy--;
      printf("Process id: %d, baby eating\n", id);
    }
    mutex_unlock(t);
    sleep(1);
    
  }
}

int parent(mutex_t *t, int k) {
  int reset = k;  
  while(1) {
    mutex_lock(t);
    if(currworm == 0) {
      if(reset > 0) {
	currworm = worms;
	reset--;
	printf("parent reset\n");
      }
    }
    mutex_unlock(t);
    sleep(1);
  }
}

shellcmd xsh_babybird(int nargs, char * args[]) {
  int i;
  int babies = 4;
  int eat = 16;
  int refill = 4;
  for(i = 1; i <= nargs; i++) {
    if((strncmp(args[i], "-b", 2) == 0) || (strncmp(args[i], "--babies", 8) == 0)) {
      babies = atoi(args[i + 1]);
      if(babies > 20 || babies < 1) {
	printf("Error with babies input\n");
	break;
      }
    }

    if((strncmp(args[i], "-f", 2) == 0) || (strncmp(args[i], "--fetch", 7) == 0)) {
      currworm = atoi(args[i + 1]);
      worms = atoi(args[i + 1]);

      if(currworm > 100 || currworm < 1) {
	printf("Error with worms input\n");
      }
    }

    if((strncmp(args[i], "-e", 2) == 0) || (strncmp(args[i], "--eat", 5) == 0)) {
      eat = atoi(args[i + 1]);
      if(eat > 100 || eat < 1) {
	printf("error with eat input\n");
      }
    }

    if(strncmp(args[i], "--help", 6) == 0) {
	printf("Keep babies less than 20 keep worms less than 100 keep eat less than 100 besides that youre on youre own\n");
      }
  }
      

  resume(create(parent, 1024, 20, "function", 2, &wormlock, refill));

  // printf("before second restume\n");

  for(i = 0; i < babies; i++) {
    resume(create(baby, 1024, 20, "function", 3, i, &wormlock, eat));
  }  

 
  return 0;
}
