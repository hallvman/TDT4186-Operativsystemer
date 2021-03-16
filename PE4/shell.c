#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void loop(void);

void readLine(void){

    char *line = NULL;
    // Buffer
    ssize_t bufsize = 0; 

    if (getline(&line, &bufsize, stdin) == -1){
        if (feof(stdin)) {
            exit(EXIT_SUCCESS); 
        } else  {
            perror("readline");
            exit(EXIT_FAILURE);
        }
    }
  return line;
}

int main(int argc, char **argv){

    // The terminal loop
    loop();

    return 0;
}

void loop(void){

    char *line;
    //char **args;
    //int status;

    do
    {

        printf("€ ");
        line = readLine();
        

        //free(line);
        //free(args);
    } while (1);
    
}

