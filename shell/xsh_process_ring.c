//code
#include <xinu.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//decrement
int dec;
//pid array with max processes being 400
int array[400];
//number of rounds, in incremented by 1 everytime the array is looped through
int r;
//is multiplied by rounds to get dec
int total_proc;
//number of rounds inputted
int input_rounds;

shellcmd xsh_process_ring(int nargs, char * args[]) {
  //defaul values
  r = 0;
  total_proc = 3;
  int mult_proc = 4;
  input_rounds = 5;
  int i = 0;
  int vers = 0;

  // checking user input
 
  for(i = 1; i <= nargs; i++) {
    //checking for number of processes
    if((strncmp(args[i], "-p", 2) == 0) || (strncmp(args[i], "--processes", 9) ==0)) {
      total_proc = atoi(args[i + 1]) - 1;
      mult_proc = atoi(args[i + 1]);
      if((total_proc < 0) || (total_proc > 400)) {
	printf("Number of Processes error, defaulting to four \n");
	total_proc = 3;
      }
    }

    //checking for number of rounds, cannot exceed number of processes
    if((strncmp(args[i], "-r", 2) == 0) || (strncmp(args[i], "--rounds", 8) == 0)) {
      input_rounds = atoi(args[i +1]);
      if((input_rounds > total_proc) || (input_rounds < 0)) {
	printf("Number of rounds error\n");
	input_rounds = 5;
      }
    }
    //checking for version because create cant just be handed a string for the version
    if((strncmp(args[i], "-v", 2) == 0) || (strncmp(args[i], "--version", 9) == 0)) {
      if(strncmp(args[i + 1], "work", 4) == 0) {
	vers = 0;
      } 

      if(strncmp(args[i + 1], "hang", 4) == 0) {
	vers = 1;
      }

      if(strncmp(args[i + 1], "loop", 4) == 0) {
	vers = 2;
      }

      if(strncmp(args[i + 1], "chaos", 5) == 0) {
	vers = 3;
      }
    }
    // help message
    if(strncmp(args[i], "--help", 4) == 0) {
      printf("Max procs allowed = 400\nNumber of rounds cannot exceed number of procs\nbesides that youre on your own\nIf something besides a number or a version after the correct fields the default values will be used");
    } 
  }
  //creating dec by multiplying the inputted number of processes by the inputted number of rounds
  dec = mult_proc * input_rounds;
  // checking the version inputted, if theres an error "work" will be used
  if(vers == 3) {
    for (i = 0; i <= total_proc; i++) {
      array[i] = create(chaos, 1024, 20, "function", 1, i);
    }
  } else if (vers == 1) {
    for(i = 0; i <= total_proc; i++) {
      array[i] = create(hang, 1024, 20, "function", 1, i);
    }
  } else if (vers == 2) {
    for(i = 0; i<= total_proc; i++) {
      array[i] = create(loop, 1024, 20, "function", 1, i);
    }
  } else {
    for(i = 0; i <= total_proc; i++) {
      array[i] = create(work, 1024, 20, "function", 1, i);
    }
  }
  //resuming the first process on the array, starting the cycle
  resume(array[0]);
  return 0;
  
}



 
