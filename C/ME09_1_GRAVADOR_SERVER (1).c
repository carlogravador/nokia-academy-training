// server.c
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

#define PRINT "PRINT"
#define ADD "ADD"
#define SEARCH "SEARCH"
#define UPDATE "CHANGE"
#define DELETE "DELETE"
#define EXIT "EXIT"

#define LEN 1024

typedef struct menu_item {
	char name[22];
	int price;
} Menu;

Menu create_menu(char *name, int price) {
	Menu m;
	strcpy(m.name, name);
	m.price = price;
	
	return m;
}


int search_menu(Menu *m_list, char *name, int ctr){
	int i;
	int index = -1;
	
	for(i = 0; i < ctr + 1; i++){
		if((m_list + i)->price == -1) continue;
		if(strcmp(name, (m_list + i)->name) == 0){
			//menu is found
			index = i;
			break;
			
		}			
	}
	return index;
}

void update_menu(Menu **m, int new_price) {
	(*m)->price = new_price;
}

void delete_menu(Menu **m) {
	(*m)->price = -1;
}
void print_menu_list(Menu *m_list, int ctr){

	int i;
	printf("List of menu\n\n");

	for(i = 0; i < ctr; i++){
		if((m_list + i)->price == -1) continue;
		printf("Menu name: %s\n", (m_list + i)->name);
		printf("Menu price: %d\n", (m_list + i)->price);
	}
	printf("\n");
}




int main(int argc, char const *argv[]){

	Menu *menu_list;
	Menu *temp;
	int menu_count = 0;

	int server_socket, command_size, port;
	char command[LEN];
	char *command_tok;
	char *name;
	int len_tok, price, search_index;
	memset(&command, '\0', sizeof(command));
	
	
	struct sockaddr_in myAddr;
	struct sockaddr_storage server_storage;
	socklen_t addr_size;
	
	if(argc != 2){
		printf("Invalid number of arguments\n");
	}
	
	port = atoi(argv[1]);
	if((server_socket = socket(PF_INET, SOCK_DGRAM, 0)) < 0) {
		printf("Error in socket creation\n");
		return 0;
	}
	
	memset(&myAddr, '\0', sizeof(myAddr));
	myAddr.sin_family = AF_INET;
	myAddr.sin_port = htons(port);
	myAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	
	if((bind(server_socket, (struct sockaddr *) &myAddr,
			sizeof(myAddr))) < 0 ) {
		printf("Error in Binding\n");
		return 0;
	}
	addr_size = sizeof(server_storage);
	
	//accept connection from incoming client_socket
	menu_list = (Menu*) malloc(sizeof(Menu) * 20);
	
	while(1) {
		printf("Server waiting for message: \n");
		
		if((command_size = recvfrom(server_socket, command,
				LEN, 0, (struct sockaddr *)&server_storage, &addr_size)) < 0) {
			printf("Error receiving message\n");
			break;
		}
		//printf("ORIGINAL COMMAND FORMAT: %s\n", command);
		
		//test command format
		len_tok = atoi(strtok(command, " "));
		if( (len_tok - (command_size - strlen(command) - 2 ) ) != 0 ) {
			printf("COMMAND FORMAT NOT CORRECT!\n");
			continue;
		}
		
		command_tok = strtok(NULL, " ");
		printf("COMMAND: %s\n", command_tok);
		//printf("COMMAND LEN: %ld\n CONSTANT PRINT LEN %ld", strlen(command_tok), strlen(PRINT));
		
		
		if(strcmp(command_tok, PRINT) == 0) {
			print_menu_list(menu_list, menu_count);
		} else if (strcmp(command_tok, ADD) == 0) {
			name = strtok(NULL, " ");
			price = atoi(strtok(NULL, " "));
			search_index = search_menu(menu_list, name, menu_count);
			if(search_index != -1){
				printf("Menu already in the list\n");
				continue;
			}
			*(menu_list + menu_count) = create_menu(name, price);
			printf("New menu added\n");
			printf("Menu name: %s\n", name);
			printf("Menu name: %d\n", price);
			menu_count++;
		} else if (strcmp(command_tok, SEARCH) == 0) {
			name = strtok(NULL, " ");
			search_index = search_menu(menu_list, name, menu_count);
			if(search_index == -1){
				printf("Menu not found!\n");
				continue;
			}
			printf("Menu name: %s\n", (menu_list + search_index)->name);
			printf("Menu price: %d\n", (menu_list + search_index)->price);
		} else if (strcmp(command_tok, UPDATE) == 0) {
			name = strtok(NULL, " ");
			search_index = search_menu(menu_list, name, menu_count);
			if(search_index == -1){
				printf("Menu not found!\n");
				continue;
			}
			temp = menu_list + search_index;
			price = atoi(strtok(NULL, " "));
			update_menu(&temp, price);
			printf("Menu successfuly updated\n");
			printf("Menu name: %s\n", (menu_list + search_index)->name);
			printf("Menu price: %d\n", (menu_list + search_index)->price);	
		} else if (strcmp(command_tok, DELETE) == 0) {
			name = strtok(NULL, " ");
			search_index = search_menu(menu_list, name, menu_count);
			if(search_index == -1){
				printf("Menu not found!\n");
				continue;
			}
			temp = menu_list + search_index;
			delete_menu(&temp);
			if(temp->price == -1) printf("DELETED\n");
			else printf("NOT DELETED\n");
			printf("%s deleted on the menu\n", name);
		} else if (strcmp(command_tok, EXIT) == 0) {
			printf("Exiting Program\n");
			break;		
		} else {
			printf("Invalid command!\n");
		}
	}
	
	if((close(server_socket)) < 0) {
		printf("Error in closing\n");
		return 0;
	}
	
	printf("Socket closed\n");
	free(menu_list);


	return 0;
}
