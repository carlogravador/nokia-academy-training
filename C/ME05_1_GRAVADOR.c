//ME05_1.c
//sort

#include<stdio.h>
#include<stdlib.h>

void sort(int *p_num){
	int i, j, swapper;
	for(i = 0; i < 5; i++){
		for(j = 0; j < (5 - i) - 1; j++){
			if(*(p_num + j) > *(p_num + (j + 1)) ){
				swapper = *(p_num + j);
				*(p_num + j) = *(p_num + (j + 1));
				*(p_num + (j + 1)) = swapper;
			}
		}
	}
		
}

void print(int *p_num){
	int i = 0;
	for(i = 0; i < 5; i++){
		printf("%d, ", *(p_num + i));
	}
	printf("\n");
}



int main(void){
	
	int *number;
	int i;
	number = (int*) malloc(sizeof(int) * 5);
	
	printf("Enter 5 numbers\n\n");
	for(i = 0; i < 5; i++){
		printf("Enter number %d: ", i + 1);
		scanf("%d", number + i);
	}

	sort(number);	
	print(number);
	
	free(number);
	
	return 0;
}
