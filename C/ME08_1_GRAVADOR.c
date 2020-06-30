#include<stdio.h>
#include<time.h>
#include<pthread.h>
#include<signal.h>
#include<string.h>

char answers[5][256];
int ans_ctr = 0;

void delay(int seconds){
	int mili_sec = 1000000 * seconds;
	
	clock_t start_time = clock();
	
	//blocking statemnts
	while(clock() < start_time + mili_sec);
}

void *count_down(){
	int i, j;
	int score = 0;
	char correct[5][256] = {
		"swimming",
		"eating",
		"vacation",
		"hiking",
		"sleeping",
	};
	
	int ctr = 0;
	char wrong[5][256];
	
	for(i = 20; i > 0; i--){
		delay(1);
	}
	printf("\nTIMES UP!\n\n");
	//check answers
	
	printf("Player's answers\n");
	for(i = 0; i < ans_ctr; i++){
		printf("%s\n", answers[i]);
	}
	 
	printf("\nCorrect answers\n");
	for(i = 0; i < 5; i++){
		printf("%s\n", correct[i]);
	}
	
	//count correct
	for(i = 0; i < 5; i++){
		for(j = 0; j < 5; j++){
			if(strcmp(answers[i], correct[j]) == 0){
				score++;
				break;
			}
			
			if(j == 4){
				strcpy(wrong[ctr], answers[i]);
				ctr++;
			}
		}
	}
	
	printf("\nIncorrect answers\n");
	for(i = 0; i < ctr; i++){
		printf("%s\n", wrong[i]);
	}
	
	
	printf("You got %d/5\n", score);
	
	return NULL;
}

void *input_answers(){
	int i;
	for(i = 0; i < 5; i++){
		printf("Enter answer: ");
		scanf("%s", answers[i]);
		ans_ctr++;
	}
	printf("DONE!\n");
	
	return NULL;
}

int main(void){
	int i;
	
	pthread_t timer_thread;
	pthread_t input_thread;
	

	printf("Welcome to the Family Feud\n");
	printf("Question: According to survey,\nWhat are the top 5 activities pepople do during summer?\n");
	
	for(i = 3; i > 0; i--){
		printf("%d...\n", i);
		delay(1);
	}
	printf("GO!\n");

	
	pthread_create(&timer_thread, NULL, count_down, NULL);
	pthread_create(&input_thread, NULL, input_answers, NULL);
	
	pthread_join(timer_thread, NULL);
	pthread_join(input_thread, NULL);
	
	
	

	return 0;
}
