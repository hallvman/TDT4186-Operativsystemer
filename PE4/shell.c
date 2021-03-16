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

int executeLine(char **tokens){

    pid_t pid;
    int status;

    if (tokens[0] == NULL)
    {
        printf("ERROR: Invalid commando");
        return 1;
    }

    
}

int main(int argc, char **argv){

    // The terminal loop
    char *line;
    char **tokens;
    int status;

    do
    {
        printf("€ ");
        line = readLine();
        tokens = splitLine(line);
        status = executeLine(tokens);
        
        // Terminates for memory
        free(line);
        free(tokens);
    } while (status);

    return EXIT_SUCCESS;
}