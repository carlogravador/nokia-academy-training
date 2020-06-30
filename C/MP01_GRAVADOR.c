
//MP01.c

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>


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
	printf("ALPHABET POOL\n\n");
	for(i = 0; i < 10; i++){
		for(j = 0; j < 10; j++){
			printf("%c ", *(*(matrix + i) + j));
		}
		printf("\n");
	}

}

void print_v_matrix(char **matrix){
	int i, j;
	printf("VOWEL POOL\n\n");
	for(i = 0; i < 4; i++){
		for(j = 0; j < 10; j++){
			printf("%c ", *(*(matrix + i) + j));
		}
		printf("\n");
	}

}

void print_c_matrix(char **matrix){
	int i, j;
	printf("CONSONANT POOL\n\n");
	for(i = 0; i < 6; i++){
		for(j = 0; j < 10; j++){
			printf("%c ", *(*(matrix + i) + j));
		}
		printf("\n");
	}

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
	printf("Position of %c on matrix %d,%d\n",tile, r, c);	

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

void print_my_tiles(char *my_tiles, int count){
	int i;
	printf("\n-----MY TILES-----\n");
	for(i = 0; i < count; i++){
		printf("%c ", *(my_tiles + i));
	}
	printf("\n\n");
}

int main(void){

	//variables
	char **a_matrix;
	char **v_matrix;
	char **c_matrix;

	char **chosen_matrix;
	
	int regular_draw = 8;
	int bonus_draw = 5;

	char *my_tiles;

	char choice, draw, trash;
	int i, ran_r, prev_r = 0, prev_c = 0;

	//declare srand
	srand(time(0));

	my_tiles = (char*) malloc(sizeof(char) * 13);

	//malloc for matrices
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



	//work here

	//create matrix
	create_a_matrix(&a_matrix);
	create_v_matrix(&v_matrix);
	create_c_matrix(&c_matrix);

	printf("--------PHASE 1---------\n\n");

	while(regular_draw > 0){
		printf("Please draw %d more tiles\n", regular_draw);
		printf("[R]andom, [V]owel, [C]onsonant\n");		
		printf("Hotkey: ");
		scanf("%c", &choice);
		scanf("%c", &trash);

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
		
		draw = draw_tile_from(&chosen_matrix, ran_r, 10, &prev_r, &prev_c);
		if(appear_3_times(draw, my_tiles, 13 - (regular_draw + bonus_draw))){
			//return the drawn tile from the pool
			*(*(chosen_matrix + prev_r) + prev_c) = draw;
			printf("%c appears 3 times in your tiles\n\n", draw);
		}else {
			*(my_tiles + (13 - (regular_draw + bonus_draw))) = draw;	
			regular_draw--;
			print_my_tiles(my_tiles, (13 - (regular_draw + bonus_draw)));
		}
	}	

	printf("--------PHASE 2---------\n\n");
	while(1) {
		printf("[S] - RANDOMLY SHUFFLE TILES\n");
		printf("[A] - RANDOMLY DRAW ANOTHER LETTER FROM THE ALPHABET\n");
		printf("[E] - EXIT PROGRAM\n");
		printf("Enter choice: ");
		scanf("%c", &choice);
		scanf("%c", &trash);

		switch(choice){
			case 'a':
			case 'A':
				if(bonus_draw == 0) {
					printf("You've already use all your bonus draw\n\n");
					continue;
				}
				draw = draw_tile_from(&a_matrix, ran_r, 10, &prev_r, &prev_c);
				if(appear_3_times(draw, my_tiles, 13 - (regular_draw + bonus_draw))){
				//return the drawn tile from the pool
					*(*(a_matrix + prev_r) + prev_c) = draw;
					printf("%c appears 3 times in your tiles\n\n", draw);
				}else {
					*(my_tiles + (13 - (regular_draw + bonus_draw))) = draw;	
					bonus_draw--;
					print_my_tiles(my_tiles, (13 - (regular_draw + bonus_draw)));
				}
				printf("REMAINING BONUS DRAW: %d\n\n", bonus_draw);
				break;
			case 's':
			case 'S':
				shuffle(&my_tiles, 13 - (regular_draw + bonus_draw));
				print_my_tiles(my_tiles, (13 - (regular_draw + bonus_draw)));	
				break;
			case 'e':
			case 'E':
				//program will exit, free resources
				printf("GOODBYE!\n");
				free(my_tiles);

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
			default:
				printf("Invalid input\n\n");
				break;
		}
	}
	

	return 0;

}	
