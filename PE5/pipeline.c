#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
 
 //PE5 

int main(int argc, char *argv[]) {

  char *a = argv[1];
  int blockSize = atoi(a);

  int fd[2];
  int nbytes = 0;
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

    do{
      nbytes+=read(fd[0], buffer, blockSize);
      printf("Bytes read: %d\n", nbytes);
    }while(nbytes > 0);
  }
  return EXIT_SUCCESS;
}