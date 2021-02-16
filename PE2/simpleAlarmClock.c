#include <unistd.h> 
#include <stdio.h> 
 
int main(){
	int t;

	while(1){
		printf("Enter number:\n");
		scanf("%d", &t);

		sleep(t);
		printf("RING! RING!\n");
	}
}