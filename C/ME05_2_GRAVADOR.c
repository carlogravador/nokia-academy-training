//ME05_1.c
//sort

#include<stdio.h>
#include<stdlib.h>

void addition(int *p_a, int *p_b){
	int i, ans;
	printf("---------For addition-------\n");
	for(i = 0;  i < 5; i++){
		ans = *(p_a + i) + *(p_b + i);
		printf("%d + %d = %d \n", *(p_a + i), *(p_b + i), ans);
	}
}

void subtraction(int *p_a, int *p_b){
	int i, ans;
	printf("---------For subtraction-------\n");
	for(i = 0;  i < 5; i++){
		ans = *(p_a + i) - *(p_b + i);
		printf("%d - %d = %d \n", *(p_a + i), *(p_b + i), ans);
	}
}

void multiplication(int *p_a, int *p_b){
	int i, ans;
	printf("---------For multiplication-------\n");
	for(i = 0;  i < 5; i++){
		ans = *(p_a + i) * *(p_b + i);
		printf("%d * %d = %d \n", *(p_a + i), *(p_b + i), ans);
	}
}

void division(int *p_a, int *p_b){
	int i;
	float ans;
	printf("---------For division-------\n");
	for(i = 0;  i < 5; i++){
		ans = (float) *(p_a + i) / *(p_b + i);
		printf("%d / %d = %.2f \n", *(p_a + i), *(p_b + i), ans);
	}
}

void modulo(int *p_a, int *p_b){
	int i, ans;
	printf("---------For modulo-------\n");
	for(i = 0;  i < 5; i++){
		ans = *(p_a + i) % *(p_b + i);
		printf("%d / %d has a remainder of %d \n", *(p_a + i), *(p_b + i), ans);
	}
}

void print_array(int *p_a, int *p_b){
	int i;
	printf("\nArray A \t Array B\n");
	for(i = 0; i < 5; i++){
		printf("%d \t \t %d\n", *(p_a + i), *(p_b + i));
	}
}




int main(void){
	int i;
	int *p_a;
	int *p_b;

	p_a = (int*) malloc(sizeof(int) * 5);
	p_b = (int*) malloc(sizeof(int) * 5);

	//input first array;	
	printf("Enter 5 numbers for first array\n\n");
	for(i = 0; i < 5; i++){
		printf("Enter number %d: ", i + 1);
		scanf("%d", p_a + i);
	}

	//input second array;
	printf("\n\nEnter 5 numbers for second array\n\n");
	for(i = 0; i < 5; i++){
		printf("Enter number %d: ", i + 1);
		scanf("%d", p_b + i);
	}
	
	print_array(p_a, p_b);
	addition(p_a, p_b);
	subtraction(p_a, p_b);	
	multiplication(p_a, p_b);
	division(p_a, p_b);
	modulo(p_a, p_b);

	free(p_a);
	free(p_b);
	
	return 0;
}
