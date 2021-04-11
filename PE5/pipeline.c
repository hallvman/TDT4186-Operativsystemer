#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
 
 //PE5 

void unmaned_pipe() {
  
}

int main(void) {

  int child_pipe[2];
  int parent_pipe[2];

  if (pipe(child_pipe) != 0 || pipe(parent_pipe) != 0) {
    perror("Faild to create pipe one or more pipe");
  }
  

  return EXIT_SUCCESS;
}
