#include <stdio.h>
#include <string.h>

int c = 5;
int sum = 1;

int sum_n(int n){	
	if(n != 0)
		return n + sum_n(n-1);
	else
		return n;
}

int main(void){
	int a = sum_n(c);

	printf("The sum of numbers from 1 to %d: %d\n", c, a);
	printf("The adress of c = %p\n", &c);
	printf("The adress of a = %p\n", &a);
	printf("The adress of sum = %p\n", &sum);
}