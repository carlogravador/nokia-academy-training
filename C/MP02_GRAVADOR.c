
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<ctype.h>

typedef struct player_info {
	char *name;
	int final_score;
	char **word;
	int *score;
	char *my_tiles;
}Player;

Player new_player(char *name){
	Player p;
	int i;

	p.name = (char*) malloc(sizeof(char) * 20);
	strcpy(p.name, name);

	p.final_score = 0;

	p.word = (char**) malloc(sizeof(char*) * 4);
	for(i = 0; i < 4; i++){
		*(p.word + i) = (char*) malloc(sizeof(char) * 8);
	}

	p.score = (int*)  malloc(sizeof(int) * 4);
	p.my_tiles = (char*) malloc(sizeof(char) * 8);

	return p;
}

void free_players(Player *p){
	int i = 0;

	free(p->name);
	for(i = 0; i < 4; i++){
		free(*((p->word) + i));
	}
	free(p->word);
	free(p->score);
	free(p->my_tiles);
}

void create_a_matrix(char ***a_matrix){
	int i;
	char temp[10][11] = {
//		  0    1    2    3    4    5    6    7    8    9   TERM
		{'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'B', '\0' },	//0
		{'B', 'B', 'C', 'C', 'C', 'D', 'D', 'D', 'D', 'E', '\0' },	//1
		{'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', '\0' },	//2
		{'F', 'F', 'G', 'G', 'G', 'H', 'H', 'H', 'I', 'I', '\0' },	//3
		{'I', 'I', 'I', 'I', 'I', 'I', 'I', 'J', 'K', 'L', '\0' },	//4
		{'L', 'L', 'L', 'M', 'M', 'N', 'N', 'N', 'N', 'N', '\0' },	//5
		{'N', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'P', 'P', '\0' },	//6
		{'P', 'Q', 'R', 'R', 'R', 'R', 'R', 'R', 'S', 'S', '\0' },	//7
		{'S', 'S', 'T', 'T', 'T', 'T', 'T', 'T', 'U', 'U', '\0' },	//8
		{'U', 'U', 'V', 'V', 'W', 'W', 'X', 'Y', 'Y', 'Z', '\0' }	//9
	};

	for(i = 0; i < 10; i++){
		strcpy(*(*a_matrix + i), temp[i]);
	}

}

void create_v_matrix(char ***v_matrix){
	int i;
	char temp[4][11] = {
//		  0    1    2    3    4    5    6    7    8    9   TERM
		{'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'E', '\0' },	//0
		{'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', '\0' },	//1
		{'I', 'I', 'I', 'I', 'I', 'I', 'I', 'I', 'I', 'O', '\0' },	//2
		{'O', 'O', 'O', 'O', 'O', 'O', 'U', 'U', 'U', 'U', '\0' },	//3
	};

	for(i = 0; i < 4; i++){
		strcpy(*(*v_matrix + i), temp[i]);
	}
}

void create_c_matrix(char ***c_matrix){
	int i;
	char temp[6][11] = {
//		  0    1    2    3    4    5    6    7    8    9   TERM
		{'B', 'B', 'B', 'C', 'C', 'C', 'D', 'D', 'D', 'D', '\0' },	//0
		{'F', 'F', 'G', 'G', 'G', 'H', 'H', 'H', 'J', 'K', '\0' },	//1
		{'L', 'L', 'L', 'L', 'M', 'M', 'N', 'N', 'N', 'N', '\0' },	//2
		{'N', 'N', 'P', 'P', 'P', 'Q', 'R', 'R', 'R', 'R', '\0' },	//3
		{'R', 'R', 'S', 'S', 'S', 'S', 'T', 'T', 'T', 'T', '\0' },	//4
		{'T', 'T', 'V', 'V', 'W', 'W', 'X', 'Y', 'Y', 'Z', '\0' },	//5
	};

	for(i = 0; i < 6; i++){
		strcpy(*(*c_matrix + i), temp[i]);
	}
}

void print_a_matrix(char **matrix){
	int i, j;
	printf("ALPHABET POOL\n");
	for(i = 0; i < 10; i++){
		for(j = 0; j < 10; j++){
			printf("%c ", *(*(matrix + i) + j));
		}
		printf("\n");
	}
	printf("\n");
}

void print_v_matrix(char **matrix){
	int i, j;
	printf("VOWEL POOL\n");
	for(i = 0; i < 4; i++){
		for(j = 0; j < 10; j++){
			printf("%c ", *(*(matrix + i) + j));
		}
		printf("\n");
	}
	printf("\n");
}

void print_c_matrix(char **matrix){
	int i, j;
	printf("CONSONANT POOL\n");
	for(i = 0; i < 6; i++){
		for(j = 0; j < 10; j++){
			printf("%c ", *(*(matrix + i) + j));
		}
		printf("\n");
	}
	printf("\n");

}

int randomizer(int range){
	return rand() % range;
}

char draw_tile_from(char ***matrix, int r_range, int c_range, int *cur_r, int *cur_c){
	char tile;
	int r, c;
	char temp;
	int empty = 1;

	//check if the matrix is empty
	for(r = 0; r < r_range; r++){
		for(c = 0; c < c_range; c++){
			temp = *(*(*matrix + r) + c);
			if(temp != '0'){
				empty = 0;
				break;
			}
		}
		if(!empty){
			break;
		}
	}

	if(empty){
		return '0';
	}


	//get a tile;
	r = randomizer(r_range);
	c = randomizer(c_range);


	tile = *(*(*matrix + r) + c);

	if(tile != '0'){
		//update the matrix and return the tile, return the position of tile;
		*cur_r = r;
		*cur_c = c;
		*(*(*matrix + r) + c) = '0';
		return tile;
	} else {
		//find another tile;
		return draw_tile_from(matrix, r_range, c_range, cur_r, cur_c);
	}
}

int appear_3_times(char c, char *my_tiles, int ctr){
	int i;
	int appearance = 0;
	for(i = 0; i < ctr; i++){
		if(*(my_tiles + i) == c){
			appearance++;
			if(appearance == 3){
				return 1;
			}
		}
	}
	return 0;
}

int get_equiv(char c){
	//	       A  B  C  D  E  F  G  H  I  J  K  L  M  N  O  P   Q  R  S  T  U  V  W  X  Y   Z
	int equiv[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10 };
	return equiv[c - 65];
}

void print_my_tiles(char *my_tiles, int count){
	int i;
	printf("MY TILES: ");
	for(i = 0; i < count; i++){
		printf("%c ", *(my_tiles + i));
	}
	printf("\nSCORES: ");
	for(i = 0; i < count; i++){
		printf("%d ", get_equiv(*(my_tiles + i)));
	}
	printf("\n\n");
}

char get_char(char **my_tiles, int range){
	char c;
	int pos;
	int empty = 1;


	for(pos = 0; pos < range; pos++){
		if(*(*my_tiles + pos) != '0'){
			empty = 0;
		}
	}

	//check if all tiles is 0;
	if(empty) return '0';


	pos = randomizer(range);
	c = *(*my_tiles + pos);
	if(c != '0'){
		*(*my_tiles + pos) = '0';
		return c;
	} else {
		return get_char(my_tiles, range);
	}

}

void shuffle(char **my_tiles, int range){
	int i;
	char *new;
	char temp;
	new = (char*) malloc(sizeof(char) * range);

	for(i = 0; i < range; i++){
		temp = get_char(my_tiles, range);
		if(temp == '0') {
			break;
		}
		*(new + i) = temp;
	}

	//copy the new to my_tiles;
	strcpy(*my_tiles, new);
	//free
	free(new);
}

void form_a_word(char *sequence, char **dest, char *src){
	char word[9];
	int i, j = 0;
	int index = 0;
	char curr;

	int len = strlen(sequence);
	for(i = 0; i < len; i+=2){
		curr = *(sequence + i);
		index = atoi(&curr);
		word[j] = *(src + (index - 1));
		j++;
	}
   	//add null terminator on last index
	word[j] = '\0';
	strcpy(*dest, word);

}

void save_word_to(Player **p, char *src, int round){
        char **temp = (*p)->word;
        strcpy(*(temp + round), src);
}

void save_score_to(Player **p, int score, int round){
	int *temp = (*p)->score + round;
	*temp = score;
}

int choose_mode(){
        int submit_mode = 0;

        printf("1) Change the word\n");
        printf("2) Proceed\n\n");
        printf("Enter mode: ");
        scanf("%d", &submit_mode);

        switch(submit_mode){
        	case 1:
        	case 2:
                	return submit_mode;
            	default:
                	printf("Invalid input\n\n");
                	return choose_mode();
        }

        //unreachable statement
        return 0;
}

int get_word_score(char *src){
	int i;
	int len = strlen(src);
	int score = 0;
	
    	for(i = 0; i < len; i++){
		score += get_equiv(*(src + i));
    	}
    	
    	return score;
}

void players_turn(Player **p, int round){
	int submit_mode;
        int temp_score;
        char sequence[18];
        char *temp_word;
        
        temp_word = (char*) malloc(sizeof(char) * 9);

        printf("%s's turn\n", (*p)->name);
	print_my_tiles((*p)->my_tiles, 8);
	while(1){
		printf("Enter sequence(1-2-3-4-5) or [S]huffle: ");
		scanf("%s", sequence);
		if(strcmp(sequence, "S") == 0 || strcmp(sequence, "s") == 0){
                	shuffle(&((*p)->my_tiles), 8);
                	print_my_tiles((*p)->my_tiles, 8);
		} else {
                	break;
		}
	}
	form_a_word(sequence, &temp_word, (*p)->my_tiles);
	temp_score = get_word_score(temp_word);
	printf("\n%s has a score of %d\n", temp_word, temp_score);

        submit_mode = choose_mode();

        switch(submit_mode){
        	case 1:
        	        players_turn(p, round);
        	        break;
            	case 2:
                	save_word_to(p, temp_word, round);
                	break;
        }
        
	//free temp_word
        free(temp_word);
}

int is_on_dictionary(FILE **file, char **word, int **score){
	int is_found = 0;
	int len, i;
	char *temp;
	char correct[4];
	char wrong[4];
	
	strcpy(correct, "(/)");
	strcpy(wrong, "(X)");
	
	len = strlen(*word);
	temp = (char*) malloc(sizeof(char) * 256);
	
	for(i = 0; i < len; i++){
		*(*word + i) = tolower(*(*word + i));
	}
	
	
	while(!feof(*file)){
		fgets(temp, 256, *file);
		len = strlen(temp) - 2;
		*(temp + len) = '\0';
		if(strcmp(temp, *word) == 0) {
			is_found = 1;
			break;
		}
	}
	
	for(i = 0; i < len + 2; i++){
		*(*word + i) = toupper(*(*word + i));
	}
	
	
	
	if(is_found){
		**score = get_word_score(*word);
		strcat(*word, correct);
	} else {
		**score = 0;
		strcat(*word, wrong);
	}
		
	rewind(*file);
	
	//free temp
	free(temp);
	
	return is_found;
}

int get_final_score(Player *p, int round){
	int *temp = p->score;
	int i;
	int final = 0;
	
	for(i = 0; i < round + 1; i++){
		final += *(temp + i);
	}
	
	return final;
}

void show_scores(Player *p, int p_count){
	
	Player *p_curr;
	
	int i, j, k, l,temp_index, ctr = 0;
	int *index;
	int temp_score = 0;
	int found = 0;
	char **words;
	
	index = (int*)malloc(sizeof(int));
	
	for(i = 0; i < p_count; i++){
		//reset
		temp_score = 0;
		for(j = 0; j < p_count; j++){	
			found = 0;
			if(temp_score <= get_final_score(p + j, 4)){		//in case of 0 score
				//search if index already stored
				for(k = 0; k < ctr; k++){
					if(*(index + k) == j){
						found = 1;	
						break;
					}
				} 
				if(!found){
					temp_score = get_final_score(p + j, 4);
					temp_index = j;
				}
			}
		}
		p_curr = p + temp_index;
		
		if(ctr == 0){
			//print the winner here
			printf("\nEND OF WORD BATTLE: CONGRATULATIONS %s\n\n", p_curr->name);
		}
		
		//print it
		words = p_curr->word;
		printf("\nTop %d\n", ctr + 1);
		printf("Player name: %s\n", p_curr->name);
		printf("Final score: %d\n", temp_score);
		for(l = 0 ; l < 4; l++){
			printf("Word%d: %s %d\n", l + 1, *(words + l), *((p_curr->score) + l));
		}	
		//store the index
		*(index + ctr) = temp_index;
		ctr++;	
	}
	
	
	//free
	free(index);
}



int main(void){

	//variables
	//FILE variable
	FILE *fPtr = NULL;
	
	//pointers to malloc
	char **a_matrix;
	char **v_matrix;
	char **c_matrix;
	char *temp;
	Player *p_players;
	
	Player *p_temp;

	char **chosen_matrix;
	char **temp_p_word;
	int *temp_word_score;

	int i, p_count, prev_r = 0, prev_c = 0;
	int regular_draw = 8, index;
	int ran_r, round = 0;
	char choice, draw;
	char name[20];

	//init dictionary
	fPtr = fopen("dictionary.txt", "r");
	if(fPtr	== NULL){
		printf("ERR: dictionary.txt not found! Program will close");
		return 0;
	}

	//declare srand
	srand(time(0));

	//malloc for matrices
	temp = (char*) malloc(sizeof(char) * 9);


	a_matrix = (char**) malloc(sizeof(char*) * 10);
	for(i = 0; i < 10; i++){
		*(a_matrix + i) = (char*) malloc(sizeof(char) * 11);
	}

	v_matrix = (char**) malloc(sizeof(char*) * 4);
	for(i = 0; i < 4; i++){
		*(v_matrix + i) = (char*) malloc(sizeof(char) * 11);
	}

	c_matrix = (char**) malloc(sizeof(char*) * 6);
	for(i = 0; i < 6; i++){
		*(c_matrix + i) = (char*) malloc(sizeof(char) * 11);
	}



	//------------------WORK HERE-------------------//

	//------------------PHASE 1---------------------//
	printf("------------PHASE 1-------------\n\n");

	while(1){
		printf("Enter number of players: ");
		scanf("%d", &p_count);
		if(p_count <= 4 && p_count >= 2) break;

		printf("Invalid number of players\n\n");
	}

	//malloc size of players
	p_players = (Player*) malloc(sizeof(Player) * p_count);
	//Enter names
	for(i = 0; i < p_count; i++){
		printf("Enter Player %d name: ", i + 1);
		scanf("%s", name);
		*(p_players + i) = new_player(name);
	}

	
	//------------------PHASE 6---------------------//
	
	//------------------PHASE 2---------------------//
	
	while(round < 4){
		printf("\n\n------------PHASE 2-------------\n\n");
		
		printf("ROUND %d\n\n", round + 1);
		//create matrix
		create_a_matrix(&a_matrix);
		create_v_matrix(&v_matrix);
		create_c_matrix(&c_matrix);
		
				
		//------------------PHASE 3---------------------//
		printf("------------PHASE 3-------------\n\n");

		for(i = 0; i < p_count; i++){
	
			regular_draw = 8;
			index = ((i + round) % 4) % p_count;
			p_temp = p_players + index;
			
	
			while(regular_draw > 0){
				printf("Player %s\n", (p_temp)->name);
				printf("Please draw %d more tiles\n", regular_draw);
				printf("[R]andom, [V]owel, [C]onsonant\n");
				printf("Hotkey: ");
				scanf(" %c", &choice);
	
				switch(choice){
					case 'r':
					case 'R':
						chosen_matrix = a_matrix;
						ran_r = 10;
						break;
					case 'v':
					case 'V':
						ran_r = 4;
						chosen_matrix = v_matrix;
						break;
					case 'c':
					case 'C':
						ran_r = 6;
						chosen_matrix = c_matrix;
						break;;
					default:
						printf("Invalid input!\n\n");
						continue;
	
				}
	
				while(1){
					draw = draw_tile_from(&chosen_matrix, ran_r, 10, &prev_r, &prev_c);				
					if(appear_3_times(draw, p_temp->my_tiles, 8 - regular_draw)) {
						//return the drawn tile from the pool
						*(*(chosen_matrix + prev_r) + prev_c) = draw;
					} else {
						break;
					}
				}
	
	/*			
				if(appear_3_times(draw, p_temp->my_tiles, 8 - regular_draw)){
					//return the drawn tile from the pool
					*(*(chosen_matrix + prev_r) + prev_c) = draw;
					printf("%c appears 3 times in your tiles\n\n", draw);
				}else {
					*(p_temp->my_tiles + (8 - regular_draw)) = draw;
					regular_draw--;
					print_my_tiles(p_temp->my_tiles, (8 - regular_draw));
				}
	*/			
				*(p_temp->my_tiles + (8 - regular_draw)) = draw;
				regular_draw--;
				print_my_tiles(p_temp->my_tiles, (8 - regular_draw));
			}
		}

		//------------------PHASE 4---------------------//
		printf("------------PHASE 4-------------\n\n");
	
    		for(i = 0; i < p_count; i++){
    			index = ((i + round) % 4) % p_count;
        		p_temp = p_players + index;
        		players_turn(&p_temp, round);
    		}

		//-----------------PHASE 5---------------------//
		printf("-----------PHASE 5-------------------\n\n");
		printf("End of round %d\n", round + 1);
		
		for(i = 0; i < p_count; i++){
			index = ((i + round) % 4) % p_count;
			p_temp = p_players + index;
			
			temp_p_word = p_temp->word;
			temp_word_score = (p_temp->score) + round;
			is_on_dictionary(&fPtr, &(*(temp_p_word + round)), &temp_word_score);	
			
			printf("\nPlayer: %s\n", p_temp->name);
			printf("Word: %s\n", *(temp_p_word + round));
			printf("Score: %d\n", *temp_word_score);
			printf("Final score: %d\n", get_final_score(p_temp, round));
		}
		
		//end of loop
		round++;
	}
	
	//--------------FINAL SCOREBOARD---------------------//
	show_scores(p_players, p_count);
	
	
	
	

	//program will exit, free resources
	printf("GOODBYE!\n");
	
	//close file
	fclose(fPtr);

	//free
	free(temp);
	for(i = 0; i < p_count; i++){
		p_temp = p_players + i;
		free_players(p_temp);
	}
	free(p_players);
	
	//free for matrices
	for(i = 0; i < 10; i++){
		free(*(a_matrix + i));
	}
	free(a_matrix);
	for(i = 0; i < 4; i++){
		free(*(v_matrix + i));
	}
	free(v_matrix);
	for(i = 0; i < 6; i++){
		free(*(c_matrix + i));
	}
	free(c_matrix);
	return 0;

}
