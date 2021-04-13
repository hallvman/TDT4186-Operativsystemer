#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
 
 //PE5 

 char readBuffer[100];

 void signalHandler(int signum){
  printf("Bandwidth: %s bytes/second\n", readBuffer);
  alarm(1);
}

int main(void) {

  int fd[2];
  int nbytes;
  pid_t childpid;
  char string[] = "Hello world, I can't wait for covid-19 to be over!";

  pipe(fd);
  
  if ((childpid = fork()) == -1)
  {
    perror("Fork");
    exit(1);
  }

  /// Child Process ///
  if (childpid == 0)
  {
    close(fd[0]);

    // Write from outside int the pipeline
    nbytes = write(fd[1], string, strlen(string));
    if (nbytes != strlen(string))
    {
      printf("Write did not return expected value");
      exit(2);
    }
    
  }
  /// Parent Process ///
  else
  {
    close(fd[1]);

    // Read the string from pipe
    while (1)
    {
      nbytes = read(fd[0], readBuffer, sizeof(readBuffer));
      signal(SIGALRM, signalHandler);
      alarm(1);
    }
    
    if (nbytes != strlen(string))
    {
      printf("Read did not return epected value!\n");
    }

    /* PE 5a
    printf("String from pipeline: %s Length: %d bytes\n", readBuffer, nbytes);
    */
  }
  sleep(20);
  return(0);
}