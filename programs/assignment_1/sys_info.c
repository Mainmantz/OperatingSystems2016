#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//James Mantz
//P436
//9/8/16

int main(int argc, char *args[]){ 
  pid_t parent = getpid();
  pid_t pid = fork();
  int fd[2];
  char *cmd = args[1];
  pipe(fd); 
  char bin[5];
  char location[30];
  
  strcpy(bin,"/bin/");
  strcpy(location, cmd);
  strncat(bin,location,30);
  // strcpy(bin, cmd);
  if (pid > 0)
    {
      printf("Parent ID %d\n", getpid());
      
      write(fd[1],cmd,sizeof(cmd));
      close(fd[1]);
      // wait(NULL);
    }
  else if (pid == 0) 
    {
      close(fd[1]);
      // we are the child
      printf("Child ID %d\n", getpid());
      
      read(fd[0],cmd,sizeof(cmd));
      close(fd[0]);
      //char* args[] = {"/bin/date", NULL};
      if (strcmp(cmd,"echo") == 0) {
	execl("/bin/echo", "echo","Hello World !!");
	 }
	 else {
	   execl(bin,cmd, (char *) NULL);
	}
    }
  wait(NULL);
}
