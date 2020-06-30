#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h> 
#include <pthread.h>
#include <signal.h>
#include<time.h>

#define OPP_NAME "OPP_NAME"
#define HANDSHAKE "HANDSHAKE"
#define PLAYER "PLAYER"
#define YOUR_TURN "DRAWN"
#define FORM_A_WORD "ROUND"
#define FINISH "FINISH"



#define LEN 1024
#define PORT1 8080
#define PORT2 5656



typedef struct player_info {
	char *name;
	int final_score;
	char **word;
	int *score;
	char *my_tiles;
} Player;


typedef struct parameters {
	int port;
	char ip[30];
	char player_name[20];
	char p_number[2];
} Params;

//GLOBAL VARIABLES

int stop_handshake = 0;
int start;
pthread_mutex_t lock;

Player player_me;
Player player_opp;

//pointers to malloc
char **a_matrix;
char **v_matrix;
char **c_matrix;

char **chosen_matrix;

int my_turn = 0;
int regular_draw;
int round_ctr;
char choice;
int updating;

FILE *fPtr = NULL;



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
	char temp[10][11] = {
//		  0    1    2    3    4    5    6    7    8    9   TERM
		{'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', '0', '\0' },	//0
		{'0', '0', '0', '0', '0', '0', '0', '0', '0', 'E', '\0' },	//1
		{'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', '\0' },	//2
		{'0', '0', '0', '0', '0', '0', '0', '0', 'I', 'I', '\0' },	//3
		{'I', 'I', 'I', 'I', 'I', 'I', 'I', '0', '0', '0', '\0' },	//4
		{'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '\0' },	//5
		{'0', 'O', 'O', 'O', 'O', 'O', 'O', 'O', '0', '0', '\0' },	//6
		{'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '\0' },	//7
		{'0', '0', '0', '0', '0', '0', '0', '0', 'U', 'U', '\0' },	//8
		{'U', 'U', '0', '0', '0', '0', '0', '0', '0', '0', '\0' }	//9
	};

	for(i = 0; i < 10; i++){
		strcpy(*(*v_matrix + i), temp[i]);
	}
}

void create_c_matrix(char ***c_matrix){
	int i;
	char temp[10][11] = {
//		  0    1    2    3    4    5    6    7    8    9   TERM
		{'0', '0', '0', '0', '0', '0', '0', '0', '0', 'B', '\0' },	//0
		{'B', 'B', 'C', 'C', 'C', 'D', 'D', 'D', 'D', '0', '\0' },	//1
		{'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '\0' },	//2
		{'F', 'F', 'G', 'G', 'G', 'H', 'H', 'H', '0', '0', '\0' },	//3
		{'0', '0', '0', '0', '0', '0', '0', 'J', 'K', 'L', '\0' },	//4
		{'L', 'L', 'L', 'M', 'M', 'N', 'N', 'N', 'N', 'N', '\0' },	//5
		{'N', '0', '0', '0', '0', '0', '0', '0', '0', 'P', '\0' },	//6
		{'P', 'Q', 'R', 'R', 'R', 'R', 'R', 'R', 'S', 'S', '\0' },	//7
		{'S', 'S', 'T', 'T', 'T', 'T', 'T', 'T', '0', '0', '\0' },	//8
		{'0', '0', 'V', 'V', 'W', 'W', 'X', 'Y', 'Y', 'Z', '\0' }	//9
	};
	for(i = 0; i < 10; i++){
		strcpy(*(*c_matrix + i), temp[i]);
	}
}


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

void timer_countdown(int seconds){
	int mili_sec = 1000000 * seconds;
	
	clock_t start_time = clock();
	
	//blocking statemnts
	while(clock() < start_time + mili_sec);
}

void remove_new_line(char **command){
	int i = strlen(*command) - 1;
	
	*(*command + i) = '\0';
}

int get_equiv(char c){
	//	       A  B  C  D  E  F  G  H  I  J  K  L  M  N  O  P   Q  R  S  T  U  V  W  X  Y   Z
	int equiv[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10 };
	return equiv[c - 65];
}

int randomizer(int range){
	return rand() % range;
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

int get_word_score(char *src){
	int i;
	int len = strlen(src);
	int score = 0;
	
    	for(i = 0; i < len; i++){
		score += get_equiv(*(src + i));
    	}
    	
    	return score;
}


void print_my_tiles(char *my_tiles, int count){
	int i;
	printf("TILES: ");
	for(i = 0; i < count; i++){
		printf("%c ", *(my_tiles + i));
	}
	printf("\nSCORES: ");
	for(i = 0; i < count; i++){
		printf("%d ", get_equiv(*(my_tiles + i)));
	}
	printf("\n\n");
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

void save_word_to(Player p, char *src, int round){
        char **temp = p.word;
        strcpy(*(temp + round), src);
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
		*(*(a_matrix + r) + c) = '0';
		*(*(v_matrix + r) + c) = '0';
		*(*(c_matrix + r) + c) = '0';
		return tile;
	} else {
		//find another tile;
		return draw_tile_from(matrix, r_range, c_range, cur_r, cur_c);
	}
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

void players_turn(Player p, int round){
	int submit_mode;
        int temp_score;
        char sequence[18];
        char *temp_word;
        char *temp_tiles = p.my_tiles;
        
        temp_word = (char*) malloc(sizeof(char) * 9);

        printf("%s's turn\n", p.name);
	print_my_tiles(temp_tiles, 8);
	while(1){
		printf("Enter sequence(1-2-3-4-5) or [S]huffle: ");
		scanf("%s", sequence);
		if(strcmp(sequence, "S") == 0 || strcmp(sequence, "s") == 0){
                	shuffle((&temp_tiles), 8);
                	print_my_tiles(temp_tiles, 8);
		} else {
                	break;
		}
	}
	form_a_word(sequence, &temp_word, temp_tiles);
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

void update_pool(char *tile){
	int found = 0;
	int i, j;
	for( i = 0; i < 10; i++){
		for(j = 0; j < 10; j++){
			//printf("%c == %c\n", *tile, *(*(a_matrix + i) + j) );
			if(*tile == *(*(a_matrix + i) + j)){
				*(*(a_matrix + i) + j) = '0';
				*(*(v_matrix + i) + j) = '0';
				*(*(c_matrix + i) + j) = '0';
				found = 1;
				break;
			}
		}
		if(found) break;
	}
}

int is_on_dictionary(char **word, int **score){
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
	
	
	while(!feof(fPtr)){
		fgets(temp, 256, fPtr);
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
		
	rewind(fPtr);
	
	//free temp
	free(temp);
	
	return is_found;
}




int get_final_score(Player p, int round){
	int *temp = p.score;
	int i;
	int final = 0;
	
	for(i = 0; i < round + 1; i++){
		final += *(temp + i);
	}
	
	return final;
}

char int_to_char(int val){
	return (char) 48 + val;

}


void server_thread_callback(Params *p){
	//ALL OPPONENTS DATA	
	
	char *message_recv;
	char *command_tok;
	char *name_tok;
	int message_len;
	int turn_num;

	int i;
	
	int handshake_ctr = 0;
	
	char *temp_char_tok;
	int temp_round;
	
	
	//server variables
	int server_socket;
	struct sockaddr_in myAddr;
	struct sockaddr_storage server_storage;
	socklen_t addr_size;
	
	int connect_ctr = 3;
	
	struct timeval timeout = {5, 0};
	
	//server's port number
	int port = p->port;
	
	if((server_socket = socket(PF_INET, SOCK_DGRAM, 0)) < 0) {
		printf("Error in socket creation\n");
		return;
	}
	
	char *temp_opp_word;
	
	
	message_recv = (char*) malloc(sizeof(char) * LEN);
	
	memset(&myAddr, '\0', sizeof(myAddr));
	myAddr.sin_family = AF_INET;
	myAddr.sin_port = htons(port);
	myAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	if((bind(server_socket, (struct sockaddr *) &myAddr,
			sizeof(myAddr))) < 0 ) {
		printf("Error in Binding\n");
		return;
	}	
	addr_size = sizeof(server_storage);
	
	printf("SERVER THREAD STARTED PORT: %d\n", port);
	printf("WAITING FOR PLAYERS TO CONNECT!\n");
	
	//set recv timeout
	setsockopt(server_socket, SOL_SOCKET,SO_RCVTIMEO,(char*)&timeout,sizeof(struct timeval));
	
	while(1){
		message_len = recvfrom(server_socket, message_recv,
				LEN, 0, (struct sockaddr *)&server_storage, &addr_size);
		if(message_len < 0) {
			//timeout has happened
			connect_ctr--;
			if(connect_ctr == 0){
				printf("The program will now exit\n");
				pthread_mutex_lock(&lock);
				stop_handshake = 5;
				pthread_mutex_unlock(&lock);
				return;
			}
			printf("Error connecting.... Reconnecting with %d attempts....\n", connect_ctr);
			continue;
		}
		
		
		//if you reach here, somebody is connected, handle the message	
		if(strcmp(message_recv, HANDSHAKE) == 0){		//handshake first
			if(handshake_ctr == 0){
				printf("CONNECTION STABLISHED!\n");	
				pthread_mutex_lock(&lock);
				stop_handshake = 1;			//to stop the sending loop
				pthread_mutex_unlock(&lock);
				handshake_ctr = 1;
				timeout.tv_sec = 9999999999;			//set another timeout
				setsockopt(server_socket, SOL_SOCKET,SO_RCVTIMEO,(char*)&timeout,sizeof(struct timeval));
			} 
		} else {
			//printf("MESSAGE RECV: %s\n", message_recv);
			//printf("WHOLE MESSAGE: %s\n", message_recv);
			command_tok = strtok(message_recv, " ");
			//printf("TOKEN: %s\n", command_tok);
			if(strcmp(command_tok, PLAYER) == 0){
				name_tok = strtok(NULL, " ");
				turn_num = atoi(strtok(NULL, " "));
				printf("Your Opponent: %s, turn: %d\n", name_tok, turn_num);
				player_opp = new_player(name_tok);
				pthread_mutex_lock(&lock);
				if(turn_num == 1){
					my_turn = 0;
				} else {
					my_turn = 1;	
				}
				start = 1;
				pthread_mutex_unlock(&lock);
			} else if(strcmp(command_tok, YOUR_TURN) == 0){
				for(i = 0; i < 8; i++){
					temp_char_tok = strtok(NULL, ",");
					*(player_opp.my_tiles + i) = *temp_char_tok;
					//remove the tiles from the pool
					update_pool(temp_char_tok);
				}
				printf("\nOpponents tiles\nPlayer %s\n", player_opp.name);
				print_my_tiles(player_opp.my_tiles, 8);
				
				pthread_mutex_lock(&lock);
				my_turn = 1;	
				pthread_mutex_unlock(&lock);
			} else if(strcmp(command_tok, FORM_A_WORD) == 0){
				//parse the message
				temp_round = atoi(strtok(NULL, " "));
				temp_round--;
				temp_opp_word = strtok(NULL, " ");
				strcpy(*(player_opp.word + temp_round), temp_opp_word);
				*(player_opp.score + temp_round) = get_word_score(*(player_opp.word + temp_round));
		//		printf("WORD ON ROUND %d: %s %d \n", 
	//					temp_round + 1, *(player_opp.word + temp_round), 
	//						*(player_opp.score + temp_round));
				pthread_mutex_lock(&lock);
				my_turn = 1;	
				updating = 0;
				pthread_mutex_unlock(&lock);
			} else if( strcmp(command_tok, FINISH) == 0){
				break;	
			}
		}
	}
	if((close(server_socket)) < 0) {
		printf("Error in closing\n");
	}
	
	printf("SERVER is closing\n");
	free(message_recv);
}

void client_thread_callback(Params *p){
	//ALL YOUR DATA
	int i;
	int ran_r;
	int prev_r, prev_c;
	char *temp_char;
	char draw;
	
	int drawing_phase;
	int form_phase;
	

	
	char *message_send;
	int message_len;
	char your_name[20];
	strcpy(your_name, p->player_name);
	
	char **temp_p_word;
	int *temp_word_score;
	
	
	//malloc
	temp_char = (char*) malloc(sizeof(char));
		
	//socket variables
	int client_socket;
	struct sockaddr_in myAddr;
	socklen_t addr_size;
	
	int port = p->port;		//port of server you want to connect
	char ip[30];			//ip of server you want to connect
	strcpy(ip, p->ip);
	
	if((client_socket = socket(PF_INET, SOCK_DGRAM, 0)) < 0) {
		printf("Error in socket creation\n");
		return;
	}
	
	message_send = (char*) malloc(sizeof(char) * LEN);
	
	
	memset(&myAddr, '\0', sizeof(myAddr));
	myAddr.sin_family = AF_INET;
	myAddr.sin_port = htons(port);
	myAddr.sin_addr.s_addr = inet_addr(ip);
	addr_size = sizeof(myAddr);
	
	strcpy(message_send, HANDSHAKE);
	message_len = strlen(message_send) + 1;

	printf("CLIENT THREAD STARTED\n");
	printf("SERVERS ADDRESS: %s/%d\n", ip, port);
	//for handshake only
	while(1){	
		if((sendto(client_socket, message_send, message_len, 0,
					(struct sockaddr *) &myAddr, addr_size)) < 0) {
				printf("Error sending data\n");
		}
		if(stop_handshake) break;
	}
	
	if(stop_handshake == 5) {		//connection failed 3 times, Exit
		free(message_send);
		return;
	}
	
	//you are already connected

	//form the message = PLAYER <NAME>
	strcpy(message_send, PLAYER);
	strcat(message_send, " ");
	strcat(message_send, your_name);
	strcat(message_send, " ");
	strcat(message_send, p->p_number);
	
	
	message_len = strlen(message_send) + 1;
//	printf("MESSAGE: %s\n", message_send);
	
	//send it
	if((sendto(client_socket, message_send, message_len, 0,
					(struct sockaddr *) &myAddr, addr_size)) < 0) {
				printf("Error sending data\n");
	}
	
	
	 	
	//start the round
	while(round_ctr < 4) {
		//blocking statement
		while(1){
			if(start) break; 
		}
		
		printf("\n\nSTART OF ROUND %d\n\n", round_ctr + 1);
		
		
		
		create_a_matrix(&a_matrix);
		create_v_matrix(&v_matrix);
		create_c_matrix(&c_matrix);	
		
		drawing_phase = 1;
		updating = 1;
		
		//check who's turn
		if(atoi(p->p_number) == 1) {
			if(round_ctr == 0 || round_ctr == 2 ){
				my_turn = 1;
			} else {
				my_turn = 0;
			}	
		} else if (atoi(p->p_number) == 2) {
			if(round_ctr == 0 || round_ctr == 2 ){
				my_turn = 0;
			} else {
				my_turn = 1;
			}
		}
		memset(player_me.my_tiles, 0, 8);	//empty the tiles
		while(drawing_phase){
			if(my_turn){		
				regular_draw = 8;	
				while(regular_draw > 0){
					printf("Player %s\n", player_me.name);
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
							ran_r = 10;
							chosen_matrix = v_matrix;
							break;
						case 'c':
						case 'C':
							ran_r = 10;
							chosen_matrix = c_matrix;
							break;;
						default:
							printf("Invalid input!\n\n");
							continue;
	
					}
	
					while(1){
			//			printf("BUG IS HERE\n");
						draw = draw_tile_from(&chosen_matrix, ran_r, 10,&prev_r,&prev_c);		
						if(appear_3_times(draw, player_me.my_tiles, 8 - regular_draw)) {
							//return the drawn tile from the pool
							*(*(chosen_matrix + prev_r) + prev_c) = draw;
							*(*(a_matrix + prev_r) + prev_c) = draw;
							*(*(v_matrix + prev_r) + prev_c) = draw;
							*(*(c_matrix + prev_r) + prev_c) = draw;
						} else {
							break;
						}
					}
					
					*(player_me.my_tiles + (8 - regular_draw)) = draw;
					regular_draw--;
					print_my_tiles(player_me.my_tiles, (8 - regular_draw));
					
				}
			
				//finish my turn here
				my_turn = 0;
				strcpy(message_send, YOUR_TURN);
				strcat(message_send, " ");
				
				//add the characters;
				for(i = 0; i < 8; i++){
					*temp_char = *(player_me.my_tiles + i);
					strcat(message_send, temp_char);
					if(i != 7){
						strcat(message_send, ",");
					}
					
				}
				
				message_len = strlen(message_send) + 1;
				
			//	printf("MESSAGE: %s\n", message_send);
			
				//inform the opponent that it's his turn to draw tiles'		
				if((sendto(client_socket, message_send, message_len, 0,
						(struct sockaddr *) &myAddr, addr_size)) < 0) {
					printf("Error sending data\n");
				}
				
				if(atoi(p->p_number) == 2){
					if(round_ctr == 0 || round_ctr == 2){
						drawing_phase = 0;
					}
				}
				
				if(atoi(p->p_number) == 1){
					if(round_ctr == 1 || round_ctr == 3){
						drawing_phase = 0;
					}
				}
				
				
			} else {
				printf("Waiting for %s to finish his turn\n", player_opp.name);
				while(1) {
					if(my_turn) break;
				}
				if(strlen(player_me.my_tiles) != 0){
					drawing_phase = 0;
				}
			}
		}
		//drawing phase loop end
		printf("\nDrawing phase END\n");
		printf("\nFORM A WORD PHASE\n");
		
		form_phase = 1;
		while(form_phase){
			
			//printf("MY TURN: %d\n", my_turn);	
			if(my_turn){
				players_turn(player_me, round_ctr);
				if(atoi(p->p_number) == 2){
					form_phase = 0;
				}
				
				//check if it's on dictionary
				

				//finish my turn here
				my_turn = 0;
				//form a message
				*temp_char = int_to_char(round_ctr + 1);
				strcpy(message_send, FORM_A_WORD);
				strcat(message_send, " ");
				strcat(message_send, temp_char);
				strcat(message_send, " ");
				strcat(message_send, *(player_me.word + round_ctr));				
				
				message_len = strlen(message_send) + 1;
				
				//printf("MESSAGE: %s\n", message_send);
			
				//inform the opponent that it's his turn to draw tiles'		
				if((sendto(client_socket, message_send, message_len, 0,
						(struct sockaddr *) &myAddr, addr_size)) < 0) {
					printf("Error sending data\n");
				}
				
				if(atoi(p->p_number) == 2){
					if(round_ctr == 0 || round_ctr == 2){
						form_phase = 0;
					} else {
						printf("Waiting for %s to form a word\n", player_opp.name);
					//	printf("Cheat\n");
					}
					
				}
				
				if(atoi(p->p_number) == 1){
					if(round_ctr == 1 || round_ctr == 3){
						form_phase = 0;
					}
				}
				
			} else {
				printf("Waiting for %s to form a word\n", player_opp.name);
				while(1){
					if(my_turn) break;
				}
				if(strlen(*(player_me.word + round_ctr)) != 0){
					form_phase = 0;
				}
			}
			
//			printf("LOOPING\n");
//			printf("VAL MY_TURN: %d\n", my_turn);
		}
		//END OF FORM A WORD PHASE
		//SHOW SCORES AT EVERY ROUND
		while(updating);
		
		//YOU
		printf("END OF ROUND %d\n", round_ctr + 1);
		
		temp_p_word = player_me.word;
		temp_word_score = player_me.score + round_ctr;
		is_on_dictionary(&(*(temp_p_word + round_ctr)), &temp_word_score);	
		
		printf("\nYOU\n");
		printf("\nPlayer: %s\n", player_me.name);
		printf("Word: %s\n", *(temp_p_word + round_ctr));
		printf("Score: %d\n", *temp_word_score);
		printf("Final score: %d\n", get_final_score(player_me, round_ctr));
		
		temp_p_word = player_opp.word;
		temp_word_score = player_opp.score + round_ctr;
		is_on_dictionary(&(*(temp_p_word + round_ctr)), &temp_word_score);	
		
		//OPPONENT	
		printf("\nOPPONENT\n");
		printf("\nPlayer: %s\n", player_opp.name);
		printf("Word: %s\n", *(temp_p_word + round_ctr));
		printf("Score: %d\n", *temp_word_score);
		printf("Final score: %d\n", get_final_score(player_opp, round_ctr));
				
		round_ctr++;
	}
	
	
	if(get_final_score(player_me, 4) < get_final_score(player_opp, 4)){	//opponent win
		printf("\nYOU LOSE!\n");
		printf("CONGRATULATIONS: %s WON THE GAME!\n", player_opp.name);
		
		printf("\nTop 1\n");
		printf("Player name: %s\n", player_opp.name);
		printf("Final score: %d\n", get_final_score(player_opp, 4));
		for(i = 0 ; i < 4; i++){
			printf("Word%d: %s %d\n", i + 1, *(player_opp.word + i), *(player_opp.score + i));
		}	
		
		printf("\nTop 2\n");
		printf("Player name: %s\n", player_me.name);
		printf("Final score: %d\n", get_final_score(player_me, 4));
		for(i = 0 ; i < 4; i++){
			printf("Word%d: %s %d\n", i + 1, *(player_me.word + i), *(player_me.score + i));
		}
		
		
	} else if(get_final_score(player_me, 4) > get_final_score(player_opp, 4)) {	//you win
		printf("\nYOU WIN\n");
		printf("CONGRATULATIONS: %s WON THE GAME!\n\n", player_me.name);
		
		printf("\nTop 1\n");
		printf("Player name: %s\n", player_me.name);
		printf("Final score: %d\n", get_final_score(player_me, 4));
		for(i = 0 ; i < 4; i++){
			printf("Word%d: %s %d\n", i + 1, *(player_me.word + i), *(player_me.score + i));
		}
		
		printf("\nTop 2\n");
		printf("Player name: %s\n", player_opp.name);
		printf("Final score: %d\n", get_final_score(player_opp, 4));
		for(i = 0 ; i < 4; i++){
			printf("Word%d: %s %d\n", i + 1, *(player_opp.word + i), *(player_opp.score + i));
		}
	} else {	//we have a tie
		printf("\nWE HAVE A TIE\n");
		
		printf("Player name: %s\n", player_me.name);
		printf("Final score: %d\n", get_final_score(player_me, 4));
		for(i = 0 ; i < 4; i++){
			printf("Word%d: %s %d\n", i + 1, *(player_me.word + i), *(player_me.score + i));
		}
		
		printf("Player name: %s\n", player_opp.name);
		printf("Final score: %d\n", get_final_score(player_opp, 4));
		for(i = 0 ; i < 4; i++){
			printf("Word%d: %s %d\n", i + 1, *(player_opp.word + i), *(player_opp.score + i));
		}
	}
	
	strcpy(message_send, FINISH);
	message_len = strlen(message_send) + 1;
				
	printf("MESSAGE: %s\n", message_send);
			
	//inform the opponent that it's his turn to draw tiles'		
	if((sendto(client_socket, message_send, message_len, 0,
			(struct sockaddr *) &myAddr, addr_size)) < 0) {
		printf("Error sending data\n");
	}
	
	//always close the socket
	if((close(client_socket)) < 0){
		printf("Error closing socket!\n");
	}
	
	printf("CLIENt SIDE WILL CLOSE!\n");
	free(temp_char);
	free(message_send);
}

int main(int argc, char *argv[]){
	int i;
	//variables
	
	//pointer to a function
	void (*server_pointer_callback)(Params *) = &server_thread_callback;
	void (*client_pointer_callback)(Params *) = &client_thread_callback;

	pthread_t server_thread;
	pthread_t client_thread;

	int opp_port;
	int host_port;
	
	Params *s_params;
	Params *c_params;
	
	char opp_ip[30];
	
	if(argc != 5){
		printf("INVALID PARAMETERS!\n");
		return 0;
	}
	
	s_params = (Params*) malloc(sizeof(Params));
	c_params = (Params*) malloc(sizeof(Params));
	
	if(pthread_mutex_init(&lock, NULL) != 0){
		printf("MUTEXT INIT FAILED\n");
		return 0;
	}
	
	//get opponent''s ip and port
	opp_port = atoi(argv[1]);
	strcpy(opp_ip, argv[2]);
	
	//declare srand
	srand(time(0));
	
	
	//assign host port number
	switch(opp_port){
		case PORT1:
			host_port = PORT2;
			break;
		case PORT2:
			host_port = PORT1;
			break;
	}
	
	player_me = new_player(argv[3]);
	
	s_params->port = host_port;
	c_params->port = opp_port;
	strcpy(c_params->ip, opp_ip);
	strcpy(c_params->player_name, argv[3]);
	strcpy(c_params->p_number, argv[4]);
	
	printf("WELCOME TO THE WORLD BATTLE\n\n");
	
	fPtr = fopen("dictionary.txt", "r");
	if(fPtr	== NULL){
		printf("ERR: dictionary.txt not found! Program will close");
		return 0;
	}
	
	a_matrix = (char**) malloc(sizeof(char*) * 10);
	for(i = 0; i < 10; i++){
		*(a_matrix + i) = (char*) malloc(sizeof(char) * 11);
	}

	v_matrix = (char**) malloc(sizeof(char*) * 10);
	for(i = 0; i < 10; i++){
		*(v_matrix + i) = (char*) malloc(sizeof(char) * 11);
	}

	c_matrix = (char**) malloc(sizeof(char*) * 10);
	for(i = 0; i < 10; i++){
		*(c_matrix + i) = (char*) malloc(sizeof(char) * 11);
	}
	

	
	//create thread
	pthread_create(&server_thread, NULL, (void *) server_pointer_callback, (void *) s_params);
	pthread_create(&client_thread, NULL, (void *) client_pointer_callback, (void *) c_params);
	
	pthread_join(server_thread, NULL);
	pthread_join(client_thread, NULL);

	printf("\nTHANKS FOR PLAYING! GOODBYE\n");
	printf("END OF PROGRAM\n");

	pthread_mutex_destroy(&lock);
	
	
	
	//free for matrices
	for(i = 0; i < 10; i++){
		free(*(a_matrix + i));
	}
	free(a_matrix);
	for(i = 0; i < 10; i++){
		free(*(v_matrix + i));
	}
	free(v_matrix);
	for(i = 0; i < 10; i++){
		free(*(c_matrix + i));
	}
	free(c_matrix);	
	free(s_params);
	free(c_params);

	return 0;
}


