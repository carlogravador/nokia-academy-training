#include<stdio.h>
#include<stdlib.h>

float get_row_average(float **m, int row){
	int sum = 0, i;
	float ave;
	for(i = 0; i < 5; i++){
		 sum += *(*(m + row) + i);
	}
	ave = sum / 5;
	return ave;
}


float get_col_average(float **m, int col){
	int sum = 0, i;
	float ave;
	for(i = 0; i < 5; i++){
		 sum += *(*(m + i) + col);
	}
	ave = sum / 5;
	return ave;
}


void print_matrix(float **m){
	int i, j;
	printf("\n Matrix \n");
	for(i = 0; i < 5; i++){
		for(j = 0; j < 5; j++){
			printf("%.2f\t", *(*(m + i) + j));
		}
		printf("\n");
	}
}


int main(void){

	float **matrix;
	int i, j;
	int n = 1;
	float ans;
	//malloc for rows
	matrix = (float**) malloc(sizeof(float*) * 5);

	printf("Input 25 numbers for the matrix\n");
	for(i = 0; i < 5; i++){
		//malloc for columns in a row;
		*(matrix + i) = (float*) malloc(sizeof(float) * 5);
		for(j = 0; j < 5; j++){
			printf("Enter number %d :", n);
			scanf("%f", *(matrix + i) + j);
			n++;	
			printf("\n");
		}
	}
	print_matrix(matrix);
	//for printing of columns
	printf("\nAverage for columns\n");
	for(i = 0; i < 5; i++){
		ans = get_col_average(matrix, i);
		printf("The average of column %d is %.2f\n", i + 1, ans);
	}
	//for printing of rows
	printf("\nAverage for rows\n");
	for(i = 0; i < 5; i++){
		ans = get_row_average(matrix, i);
		printf("The average of row %d is %.2f\n", i + 1, ans);
	}

	//free memory
	for(i = 0; i < 5; i++){
		free(*(matrix + i));	
	}

	free(matrix);

	return 0;	
}
