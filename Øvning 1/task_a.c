#include <stdio.h>
#include <string.h>

int c = 5;
int d = 65536; //Last correct number

int sum_n(int n){	
	if(n != 0)
		return n + sum_n(n-1);
	else
		return n;
}

int main(void){
	int a = sum_n(c);
	int b = sum_n(d);

	printf("The sum of numbers from 1 to %d: %d\n", c, a);
	printf("The sum of numbers from 1 to %d: %d\n", d, b);
	printf("The adress of c = %p\n", &c);
	printf("The adress of large = %p\n", &d);
	//printf("The adress of sum = %p\n", &sum);
}