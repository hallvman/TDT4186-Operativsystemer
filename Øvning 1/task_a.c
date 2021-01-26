#include <stdio.h>
#include <string.h>

int c = 5;
//int sum = 1;
int d = 5910968;
int e = 5910969;

int sum_n(int n){
	int sum = 1;
	for(int i = 2; i <= n; i++){
		sum += i;
	}
return sum;
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