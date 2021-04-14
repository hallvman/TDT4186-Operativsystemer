#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
 
 //PE5 

// Boolean for handling functions
int isAlarm = 0;
int print = 0;

// The signal handler for SIGALRM
void signalHandler(int signum){
  alarm(1);
  isAlarm = 1;
}

// The Signal handler for SIGUSR1
void usrHandler(int signum){
  print = 1;
}

int main(int argc, char *argv[]) {

  // Converts the string from command line to an int
  char *a = argv[1];
  int blockSize = atoi(a);

  // Bytes and file 
  int fd[2];
  long long nbytes, bytes = 0;

  // The data for the write and read functions
  char *data = (char *)malloc(sizeof(char) * blockSize);
  free(data);
  char *buffer = (char *)malloc(sizeof(char) * blockSize);

  // Make pipe
  pipe(fd);

  // Child Process
  if (fork()==0) {
    close(fd[0]);

    // Writes data of the the given blocksize
    while(1){
      write(fd[1], data, blockSize);
    }
    return(EXIT_SUCCESS);
  }
  // Parent Process
  else {
    close(fd[1]);

    // SIGUSR1 signal
    signal(SIGUSR1, usrHandler);
    
    // SIGALRM signal
    signal(SIGALRM, signalHandler);
    alarm(1);

    printf("This is the parent pid id: %d\n", getpid());
    while(1){
      // Reads of the given blocksize
      nbytes+=read(fd[0], buffer, blockSize);
      // Commented out for task b
      // printf("Bytes read: %d\n", nbytes);
      // This if wont be there for 5A, but is needed for 5B
      if(isAlarm == 1){
        printf("Bandwidth: %lld\n\n", nbytes-bytes);
        bytes = nbytes;
        isAlarm = 0;
      }

      // The handler for SIGUSR1 gives 1 and reads the bytes
      if(print == 1){
        printf("Bytes read: %lld\n\n", nbytes);
        print = 0;
      }
    }
  }
  return EXIT_SUCCESS;
}
