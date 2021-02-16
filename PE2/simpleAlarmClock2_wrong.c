#include <unistd.h> 
#include <stdio.h> 
#include "stdbool.h"
 
void alarmClock();

int main(){
	bool startFork = false;
	int t,pid;
	int i = 0;

	printf("%d", pid);
	printf("\nEnter number:\n");
	scanf("%d", &t);
	
	pid = fork();
	while (1) {
		if (pid == 0 && startFork == false) {
			printf("%d", pid);
			printf("\nEnter number:\n");
			scanf("%d", &t);
			startFork = true;
			sleep(t);
			printf("RING! RING!\n");
		}
		else if (!startFork) {
			sleep(t);
			printf("RING! RING!\n");
			startFork = true;
		}
		else {
			printf("%d", pid);
			printf("\nEnter number:\n");
			scanf("%d", &t);
			sleep(t);
			printf("RING! RING!\n");
		}
	}	
}

void alarmClock() {
	int t;
	
	
	printf("Enter number:\n");
	scanf("%d", &t);
	

	sleep(t);
	printf("RING! RING!\n");
}
