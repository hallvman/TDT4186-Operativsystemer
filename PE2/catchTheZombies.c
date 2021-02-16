#include <unistd.h> 
#include <stdio.h> 
#include <stdlib.h>
 
int main(){
	int t, pid;

	while(1){
        printf("\nEnter number: ");
        scanf("%d", &t);

        pid = fork();
        if(pid > 0){
            printf("You created a new child, id: %d\n", pid);
		}
        if (pid == 0){
            sleep(t);
            printf("\nRING! Time: %d Child ID: %d\n", t, getpid());
            exit(0);
        }
    }
    return(0);
}