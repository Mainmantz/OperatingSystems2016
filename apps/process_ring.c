#include <xinu.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <process_ring.h>

//imported values from our header file
int array[400];
int dec;
int r;
int total_proc;
int input_rounds;
int dec_max;

//default work function
void work(int i) {
  int next;
  if(i == total_proc) {
    next = 0;
  } else {
    next = i + 1;
  }
  while(dec > 0) {
    printf("Process =  %d, Round = %d, Value = %d\n", i, r, dec);
    dec = dec - 1;
    if(next == 0) {
      r = r + 1;
    }
    resume(array[next]);
    suspend(getpid());
  }
  printf("ZERO! \n");
}

//hang function, hangs on one process, this process is never suspended
void hang(int i) {
  printf("Process = %d, Round = %d, Value = %d\n", i, r, dec);
  while(dec > 0) {
    // dec = dec - 1;
    resume(array[i + 1]);
    //suspend(getpid());
  }
}

//loops dec back to its max value when dec reaches zero
//max of dec is stored in the integer dec max
void loop(int i) {
  dec_max = dec;
  int next;
  if(i == total_proc) {
    next = 0;
    r = r + 1;
  } else {
    next = i + 1;
  }
  while(dec > 0) {
    printf("Process = %d, Round = %d , Value = %d\n", i, r, dec);
    if(dec == 1) {
      dec = dec_max;
    }
    dec = dec - 1;
     resume(array[next]);
    // suspend(getpid());
  }
}

//chaos, the only way i could get this work was with random values, I could have used an array probably to cycle through
void chaos(int i) {
  int next;
  int j;
  if(i == total_proc) {
    next = 0;
    r = r + 1;
  } else {
    next = i + 1;
  }
  while(dec > 0) {
    j = rand() % dec;
    printf("Process = %d, Round = %d , Value = %d\n", i, r, j);
    dec = dec - 1;
    resume(array[next]);
    suspend(getpid());
  }
  printf("ZERO! \n");
}


