#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define TOKEN_BUFSIZE 64
#define TOKEN_DELIM " \t\r\n\a"

char *readLine(void){

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

char **splitLine(char *line){
    int bufsize = TOKEN_BUFSIZE, position = 0;
    char **tokens = malloc(bufsize * sizeof(char*));
    char *token;

    if (!tokens)
    {
        printf("Error");
        exit(EXIT_FAILURE);
    }
    
    token = strtok(line, TOKEN_DELIM);
    while (token != NULL)
    {
        tokens[position] = token;
        position++;

        if (position >= bufsize)
        {
            bufsize += TOKEN_BUFSIZE;
            tokens = realloc(tokens, bufsize * sizeof(char*));

            if (!tokens)
            {
                printf("Error");
                exit(EXIT_FAILURE);
            }
        }
        token = strtok(NULL, TOKEN_DELIM);      
    }
    
    tokens[position] = NULL;
    return tokens;
}

// Processing each step of the line
int processString(char **tokens){
    pid_t  pid;
    int    status;

    // child process 
    if ((pid = fork()) < 0) {             
        printf("*** ERROR: forking child process failed\n");
        exit(1);
    }
    //for the child process:
    else if (pid == 0) {               
        // Execute
        if (execvp(*tokens, tokens) < 0) {   
            printf("*** ERROR: exec failed\n");
            exit(1);
        }
    }
    // Parent
    else {                                  
        while (wait(&status) != pid)     
            ;
    }

    return 1;
}


// Command to change directory
int cd(char **tokens){
    if (chdir(tokens[1]) != 0)
    {
        perror("chdir");
    }
    return 1;
}

// Command to exit
int exitCMD(char **tokens){
    return 0;
}

// Function to run the bash for scripts
int bashCMD(char **tokens){
    int status = system(tokens[1]);
}

// Points to the functions
int (*functions[]) (char **) = {
    &exitCMD,
    &cd,
    &bashCMD
};

// Execution function for the commands
int executeLine(char **tokens){
    int i;
    char* listOfCmds[3] = {
        "exit",
        "cd",
        "bash"
    };

    if(tokens[0] == NULL)
    {
        printf("Empty command: try again\n");
    }
    
    for (i = 0; i < 3; i++)
    {
        if(strcmp(tokens[0], listOfCmds[i]) == 0){
            return (*functions[i])(tokens);
        }
    }
    
    return processString(tokens);
}

int main(int argc, char **argv){

    // The terminal loop
    char *line;
    char **tokens;
    int status;

    do
    {
        printf("$ ");
        // Reads the line
        line = readLine();
        // Splits the line
        tokens = splitLine(line);
        // Execute the line
        status = executeLine(tokens);
        
        // Terminates for memory
        free(line);
        free(tokens);
    } while (status);

    return EXIT_SUCCESS;
}