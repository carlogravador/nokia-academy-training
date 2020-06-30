//ME04_2.c
//pointers

#include<stdio.h>

void swap(int *num1, int *num2){
	//swap
	int swapper;

	swapper = *num1;
	*num1 = *num2;
	*num2 = swapper;

}

int main(void){
	int a, b;
	
	printf("Enter num1: ");
	scanf("%d", &a);
	printf("Enter num2: ");
	scanf("%d", &b);
	
	swap(&a, &b);
	printf("Exchanged: A = %d, B = %d \n", a, b);
	
	return 0;
}
