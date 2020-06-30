//ME03_B2_GRAVADOR.c
//calendar

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void generate_month(){
	int i;
	printf("July 2018\n");
	printf("S\tM\tT\tW\tTH\tF\tSA\n");
	for(i = 1; i <= 31; i++){
		printf("%d\t", i);
		if(i % 7 == 0){
			printf("\n");
		}

	}
	printf("\n");
}


int main(void){
	int date, i ;
	
	char **pp_days;

	pp_days = (char**) malloc(sizeof(char*) * 7);

	for(i = 0; i < 7; i++){
		*(pp_days + i) = (char*)malloc(sizeof(char) * 10);
	}
	
	strcpy(*pp_days, "Sunday");
	strcpy(*(pp_days + 1), "Monday");
	strcpy(*(pp_days + 2), "Tuesday");
	strcpy(*(pp_days + 3), "Wednesday");
	strcpy(*(pp_days + 4), "Thursday");
	strcpy(*(pp_days + 5), "Friday");
	strcpy(*(pp_days + 6), "Saturday");
	
	generate_month();

	printf("Enter a date: ");
	scanf("%d", &date);
	
	if(date > 31 || date < 1){
		printf("Invalid date\n");
		return 0;
	}
	
	i = (date - 1)% 7;
	printf("July %d is %s\n", date, *(pp_days + i));

	//free
	for(i = 0; i < 7; i++){
		free(*(pp_days + i));
	}
	
	free(pp_days);

	return 0;
}
