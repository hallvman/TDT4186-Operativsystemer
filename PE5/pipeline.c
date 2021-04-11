#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
 
 //PE5 

void unmaned_pipe() {
  
}

int main(void) {

  int child_pipe[2];
  int parent_pipe[2];
  pid_t pid;

  if (pipe(child_pipe) == -1) {
    perror("Faild to create child pipe");
  }

  if (pipe(parent_pipe) == -1) {
    perror("Faild to create parent pipe");
  }


  return EXIT_SUCCESS;
}




//Pipe example from the pipe() man page in Linux

/*
EXAMPLES
   Using a Pipe to Pass Data Between a Parent Process and a Child Process
       The following example demonstrates the use of a pipe to transfer data between a parent process and a child process. Error  handling  is  excluded,
       but  otherwise  this code demonstrates good practice when using pipes: after the fork() the two processes close the unused ends of the pipe before
       they commence transferring data.
*/

/*
#include <stdlib.h>
#include <unistd.h>
...

int fildes[2];
const int BSIZE = 100;
char buf[BSIZE];
ssize_t nbytes;
int status;

status = pipe(fildes);
if (status == -1 ) {
    // an error occurred 
    ...
}

switch (fork()) {
case -1: // Handle error 
    break;

case 0:  // Child - reads from pipe 
    close(fildes[1]);                       // Write end is unused 
    nbytes = read(fildes[0], buf, BSIZE);   // Get data from pipe 
    // At this point, a further read would see end-of-file ... 
    close(fildes[0]);                       // Finished with pipe 
    exit(EXIT_SUCCESS);

default:  // Parent - writes to pipe 
    close(fildes[0]);                       // Read end is unused 
    write(fildes[1], "Hello world\n", 12);  // Write data on pipe 
    close(fildes[1]);                       // Child will see EOF 
    exit(EXIT_SUCCESS);
}

*/