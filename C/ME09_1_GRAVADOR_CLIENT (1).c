// client.c
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

#define EXIT "4 EXIT"
#define LEN 1024

void remove_new_line(char **command){
	int i = strlen(*command) - 1;
	
	*(*command + i) = '\0';
}

int main(int argc, char const *argv[]) {
	
	//to malloc
	char *command;
	

	char ip[30];
	int port;
	
	int command_size;
	int client_socket;
	
	struct sockaddr_in myAddr;
	socklen_t addr_size;
	
	//checker
	if(argc != 3){
		printf("Invalid number of arguments\n");
		return 0;
	}
	

	//get ip and port number of the server you want to connect to.
	strcpy(ip, argv[1]);
	port = atoi(argv[2]);
	
	if((client_socket = socket(PF_INET, SOCK_DGRAM, 0)) < 0) {
		printf("Error in socket creation\n");
		return 0;
	}
	memset(&myAddr, '\0', sizeof(myAddr));
	myAddr.sin_family = AF_INET;
	myAddr.sin_port = htons(port);
	myAddr.sin_addr.s_addr = inet_addr(ip);
	addr_size = sizeof(myAddr);

	command = (char*) malloc(sizeof(char) * LEN);	
	while(1){
		printf("Enter command: ");
		fgets(command, LEN, stdin);
		remove_new_line(&command);
		printf("COMMAND VAL: %s\n", command);
		command_size = strlen(command) + 1;		
		if((sendto(client_socket, command, command_size, 0,
				(struct sockaddr *) &myAddr, addr_size)) < 0) {
			printf("Error sending data\n");
			break;
		
		}
		//if it reach here send successful
		if(strcmp(command, EXIT) == 0){
			printf("Exiting program\n");
			break;
		
		}
	}
	
	//always close the socket
	if((close(client_socket)) < 0){
		printf("Error closing socket!\n");
		return 0;
	}

		
	printf("Socket closed\n");
	free(command);	
	
	return 0;
}

