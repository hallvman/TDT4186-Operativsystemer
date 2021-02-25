#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
 
int main(){
    // Variables
	int t, pid, wp, sys;

	while(1){
        // Takes the time
        printf("\nEnter number: ");
        scanf("%d", &t);

        sys = system("ps -e | grep catchTheZombies");

        // WNOHANG return immediately if no child has exited
        do {
            wp = waitpid(-1, NULL, WNOHANG);
        } while (wp > 0);
        

        pid = fork();
        if(pid > 0){
            // Creates a new child of the number you entered
            printf("You created a new child, id: %d\n", pid);
		}
        // Waits the given time
        if (pid == 0){
            sleep(t);
            printf("\nDeceased child: %d", getpid());
            printf("\nRING! Time: %d Child ID: %d\n", t, getpid());
            exit(0);
        }
        // No child processes
        if (pid == -1 || sys == -1) {
            perror("Could not fork or create child ID");
            return 1;
        }
    }
    return(0);
}