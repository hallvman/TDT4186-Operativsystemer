#include <unistd.h> 
#include <stdio.h> 
 
int main(){
	
	while(1){
		int t;
		printf("Enter number:\n");
		scanf("%d", &t);

		sleep(t);
		printf("RING! RING!\n");
	}
}