
#include<stdio.h>
#include<stdlib.h>
#include<string.h>


struct s_contact_info{
	char *name;
	char *phone;
	char *email;
};


void malloc_for_struct(struct s_contact_info *p_contacts){
	int i;

	for(i = 0; i < 5; i++){
		(p_contacts + i)->name = (char*)malloc(sizeof(char) * 10);
		(p_contacts + i)->phone = (char*)malloc(sizeof(char) * 12);
		(p_contacts + i)->email = (char*)malloc(sizeof(char) * 25);
	}
}

void free_for_struct(struct s_contact_info *p_contacts){
	int i;	
	for(i = 0; i < 5; i++){
		free((p_contacts + i)->name);
		free((p_contacts + i)->phone);
		free((p_contacts + i)->email);		
	}

	free(p_contacts);	

}

//return index of contact
int search_contact(struct s_contact_info *p_contacts, char *name){
	int i = 0, index = -1;
	char *temp = (p_contacts + i)->name;;

	for(i = 0; i < 5; i++){
		if(strcmp(temp, name) == 0){
			index = i;
			break;			
		}		
	}

	return index;	
}
//
void create_contact(struct s_contact_info *contact, char *name, char *phone, char *email){
	strcpy(contact->name, name);
	strcpy(contact->phone, phone);
	strcpy(contact->email, email);
}

void print_contact(struct s_contact_info *s){
	printf("Contact name: %s\n", s->name);
	printf("Contact phone: %s\n", s->phone);
	printf("Contact email: %s\n\n", s->email);
}


void print_all_contact(struct s_contact_info *s){
	int i;	
	printf("\n\nPrint contacts\n");
	for(i = 0; i < 5; i++){
		print_contact(s + i);
	}
	
}

int main(void){

	struct s_contact_info *p_contacts;
	char *name;
	char *phone;
	char *email;
	char *input;
	int i, index;

	p_contacts = (struct s_contact_info*) malloc(sizeof(struct s_contact_info) * 5);
	
	name = (char*)malloc(sizeof(char) * 10);
	phone = (char*)malloc(sizeof(char) * 12);
	email = (char*)malloc(sizeof(char) * 25);
	input = (char*)malloc(sizeof(char) * 10);
	
	malloc_for_struct(p_contacts);
	for(i = 0; i < 5; i++){
		printf("Enter name: ");
		scanf("%s", name);
		printf("Enter contact: ");
		scanf("%s", phone);
		printf("Enter email: ");
		scanf("%s", email);
		create_contact(p_contacts + i, name, phone, email);
	}
	print_all_contact(p_contacts);
	printf("Search contact, enter name: ");
	printf("\n");
	scanf("%s", input);

	index = search_contact(p_contacts, input);
	if(index < 0){
		printf("Contact not available\n");
		return 0;
	}
	print_contact(p_contacts + index);
	

	
	free(name);
	free(input);
	free(phone);
	free(email);	
	free_for_struct(p_contacts);
	return 0;
}
