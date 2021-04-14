#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
 
 //PE5 

int isAlarm = 0;

void signalHandler(int signum){
  alarm(1);
  isAlarm = 1;
}

int main(int argc, char *argv[]) {

  char *a = argv[1];
  int blockSize = atoi(a);

  int fd[2];
  int nbytes, bytes = 0;
  char *data = (char *)malloc(sizeof(char) * blockSize);
  free(data);
  char *buffer = (char *)malloc(sizeof(char) * blockSize);

  pipe(fd);

  // Child Process
  if (fork()==0) {
    close(fd[0]);
      
    while(1){
      write(fd[1], data, blockSize);
    }
    exit(EXIT_SUCCESS);
  }
  // Parent Process
  else {
    close(fd[1]);

    signal(SIGALRM, signalHandler);
    alarm(1);

    while(1){
      nbytes+=read(fd[0], buffer, blockSize);
      //printf("Bytes read: %d\n", nbytes);
      if(isAlarm == 1){
        printf("Bandwidth: %d\n\n", nbytes-bytes);
        bytes = nbytes;
        isAlarm = 0;
      }
    }
  }
  return EXIT_SUCCESS;
}