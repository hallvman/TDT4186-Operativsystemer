#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <signal.h>
#include <fcntl.h>
#include <math.h>

 //PE5 

// Boolean for handling functions
int isAlarm = 0;
int print = 0;

// The signal handler for SIGALRM
void signalHandler(int signum){
  alarm(1);
  isAlarm = 1;
}

int main(int argc, char *argv[]) {

  // Converts the string from command line to an int
  char *a = argv[1];
  size_t blockSize = atoi(a);

  // Bytes and file 
  int fd[2];
  size_t nbytes, bytes, rBytes = 0;

  // The data for the write and read functions
  char *data = (char *)malloc(sizeof(char) * blockSize);
  free(data);
  char *buffer = (char *)malloc(sizeof(char) * blockSize);

  // Make pipe
  unlink("myFifo");
  char * myFifo = "myFifo";
  mkfifo(myFifo, 0666);

  // Child Process
  if (fork()==0) {
    close(fd[0]);

    fd[1] = open(myFifo, O_WRONLY);
    // Writes data of the the given blocksize
    while(1){
      write(fd[1], data, blockSize);
    }
    return(EXIT_SUCCESS);
  }
  // Parent Process
  else {
    close(fd[1]);
    
    // SIGALRM signal
    signal(SIGALRM, signalHandler);
    alarm(1);

    fd[0] = open(myFifo, O_RDONLY);

    printf("This is the parent pid id: %d\n", getpid());
    do{
      // Reads of the given blocksize
      nbytes += read(fd[0], buffer, blockSize);

      // Commented out for task b
      // printf("Bytes read: %d\n", nbytes);
      // This if wont be there for 5A, but is needed for 5B

      if(isAlarm == 1){
        printf("Bandwidth: %.*f MB/s\n", 2, (nbytes - bytes) / pow(10, 6));
        bytes = nbytes;
        isAlarm = 0;
      }
    }while(nbytes >0);
  }
  return(0);
}
