//ME07_1.c

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define BY_NAME 1
#define BY_SCORE 2

typedef struct s_player_info{
	char name[20];
	int score;
	struct s_player_info *next;
	struct s_player_info *prev;
} player_info;


player_info *get_start(player_info *p){
	if(p == NULL) return NULL;
	while(p->prev != NULL){
		p = p->prev;
	}
	return p;
}

player_info *get_last(player_info *p){
	if(p == NULL) return NULL;
	while(p->next != NULL){
		p = p->next;
	}
	return p;
}

player_info *search_player(player_info *start, char name[20]){
	player_info *result = NULL;
	start = get_start(start);
	while(start != NULL){
		if(strcmp(start->name, name) == 0){
			result = start;
			break;
		}
		start = start->next;
	}
	return result;
}

void update_player(player_info **update_me, int new_score){
	(*update_me)->score = new_score;
}

void create_player(player_info **p_head, char name[20]){

	player_info *last;
	player_info *new_player = (player_info*) malloc(sizeof(player_info));

	strcpy(new_player->name, name);
	new_player->score = 0;
	new_player->next = NULL;	
	
	if(*p_head == NULL){	
		new_player->prev = NULL;
		*p_head = new_player;
	} else {
		last = get_last(*p_head);
		last->next = new_player;
		new_player->prev = last;
	}
	
	printf("%s successfully added.\n\n", new_player->name);
}

void clean_players(player_info **p){
	player_info *current = *p;
	player_info *next;
	while(current != NULL){
		next = current->next;
		free(current);
		current = next;
	}
}

void print_players(player_info **head_p){
	player_info *start = get_start(*head_p);
	printf("Name \t Score\n");
	while(start != NULL){
		printf("%s \t %d\n", start->name, start->score);
		start = start->next;
	}
	printf("\n");	
}

void sorted_insert_score(player_info **head_p, player_info *to_insert){
	
	player_info *current;
	if(*head_p == NULL){
		*head_p = to_insert;
	} else if ((*head_p)->score <= to_insert->score) {
		//insert where the highest is
		to_insert->next = *head_p;
		to_insert->next->prev = to_insert;
		*head_p = to_insert;
	} else {
		current = *head_p;
		//find where to insert
		while(current->next != NULL && 
				current->next->score > to_insert->score){
			current = current->next;			
		}
		to_insert->next = current->next;
		//if not at the end, point the previous of the next element to self
		if(current->next != NULL){
			to_insert->next->prev = to_insert;
		}
		current->next = to_insert;
		to_insert->prev = current;
	}
}


void sorted_insert_name(player_info **head_p, player_info *to_insert){
	
	player_info *current;
	if(*head_p == NULL){
		*head_p = to_insert;
	} else if (strcmp((*head_p)->name, to_insert->name) >= 0 ){
		//insert where the lowest is
		to_insert->next = *head_p;
		to_insert->next->prev = to_insert;
		*head_p = to_insert;
	} else {
		current = *head_p;
		//find where to insert
		while(current->next != NULL && 
				(strcmp(current->next->name, to_insert->name) < 0)){
			current = current->next;			
		}
		to_insert->next = current->next;
		//if not at the end, point the previous of the next element to self
		if(current->next != NULL){
			to_insert->next->prev = to_insert;
		}
		current->next = to_insert;
		to_insert->prev = current;
	}
}


void sort(player_info **head_p, int type){
	player_info *sorted = NULL;
	player_info *current = get_start(*head_p);
	player_info *next;
	

	while(current != NULL){
		//remove links
		next = current->next;
		current->prev = NULL;
		current->next = NULL;
		switch(type){
			case BY_NAME:
				sorted_insert_name(&sorted, current);
				break;
			case BY_SCORE:
				sorted_insert_score(&sorted, current);
				break;
		}
		current = next;
	}
	*head_p = sorted;
}

int prompt_exit(){
	char input;
	int exit = 0;
	printf("Are you sure you want to exit? [Y]es or [No]: ");
	scanf("%c", &input);
	if(input == 'Y' || input == 'y'){
		exit = 1;
	} else if (input == 'N' || input == 'n'){
		exit = 0;
	} else {
		exit = prompt_exit();
	}

	return exit;
}


int select_mode(){

	int mode;
	
	printf("1. Add a player\n");
	printf("2. Update score\n");
	printf("3. Print players score\n");
	printf("4. Print players name\n");
	printf("5. Exit program\n\n");

	printf("Enter mode: ");
	scanf("%d", &mode);

	return mode;	

}

int main(void){
	int mode, new_score, exit;
	char player_name[22];	
	player_info *p_head = NULL;
	player_info *result;


	while(1){
		mode = select_mode();
		switch(mode){
			case 1:
				printf("\n\nEnter player name: ");
				scanf("%s", player_name);
				create_player(&p_head, player_name);
				break;
			case 2:
				printf("\n\nEnter player name:");
				scanf("%s", player_name);
				result = search_player(p_head, player_name);
				if(result == NULL) {
					printf("Result not found\n");
					continue;
				}
				printf("Enter new score: ");
				scanf("%d", &new_score);
				if(new_score < 0){
					printf("Invalid score\n");
					continue;
				}
				update_player(&result, new_score);
				printf("%s updated succesfully. New score: %d\n", result->name, result->score);
				break;
			case 3:
				printf("\nSorted by score\n");
				sort(&p_head, BY_SCORE);
				print_players(&p_head);
				break;
			case 4:
				printf("Sorted by name\n");
				sort(&p_head, BY_NAME);
				print_players(&p_head);
				break;
			case 5:
				exit = prompt_exit();
				if(exit){
					clean_players(&p_head);
					p_head = NULL;
					return 0;
				}
				break;	
		}
	}
	return 0;
}
