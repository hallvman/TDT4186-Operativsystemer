#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
 
int main(){
	int t, pid, wp, sys;

	while(1){
        printf("\nEnter number: ");
        scanf("%d", &t);

        sys = system("ps -e | grep catchTheZombies");

        do {
            wp = waitpid(-1, NULL, WNOHANG);
        } while (wp > 0);
        

        pid = fork();
        if(pid > 0){
            // Creates a new child of the number you entered
            printf("You created a new child, id: %d\n", pid);
		}
        if (pid == 0){
            sleep(t);
            printf("\nDeceased child: %d\n", getpid());
            printf("\nRING! Time: %d Child ID: %d\n", t, getpid());
            exit(0);
        }
        if (pid == -1 || sys == -1) {
            perror("Could not fork and create child ID");
            return 1;
        }
    }
    return(0);
}