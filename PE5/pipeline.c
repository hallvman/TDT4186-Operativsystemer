#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>


 
 //PE5 

int main(int argc, char *argv[]) {
  int pipefd[2];
  pid_t cpid;
  char buf;

  if (argc != 2) {
      fprintf(stderr, "Usage: %s <string>\n", argv[0]);
      exit(EXIT_FAILURE);
  }

  if (pipe(pipefd) == -1) {
      perror("pipe");
      exit(EXIT_FAILURE);
  }

  cpid = fork();

  switch (cpid) {
    case -1:
      perror("Faild to fork");
      exit(EXIT_FAILURE);

    case 0: // Child - reads from pipe 
      close(pipefd[1]);          //Close unused write end 

      while (read(pipefd[0], &buf, 1) > 0)
          write(STDOUT_FILENO, &buf, 1);
      write(STDOUT_FILENO, "\n", 1);
      printf("%d\n", pipefd[0]);
      close(pipefd[0]);
      _exit(EXIT_SUCCESS);

    default: // Parant - reads from pipe
      close(pipefd[0]);          // Close unused read end 
      write(pipefd[1], argv[1], strlen(argv[1]));
      close(pipefd[1]);          // Reader will see EOF 
      wait(NULL);                // Wait for child 
      exit(EXIT_SUCCESS);
    
  }
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