//ME04_1.c
//structs

#include<stdio.h>
#include<string.h>

struct menu_item {
	char name[20];
	int price;
};


struct menu_item update_menu(struct menu_item m, char name[20], int price){
	strcpy(m.name, name);
	m.price = price;

	return m;	
}

int display_main_menu(){
	int choice;

	printf("Main Menu\n");
	printf("1. Add a dish from the menu\n");
	printf("2. Search a dish from the menu\n");
	printf("3. Change dish price\n");
	printf("4. Print menu\n");
	printf("5. Exit program\n\n");

	printf("Enter mode: ");
	scanf("%d", &choice);
	printf("\n");
	return choice;

}


//returns -1 if no index found
int search_menu(struct menu_item m[20], char name[20], int ctr){

	int i;
	int index = -1;
	
	for(i = 0; i < ctr + 1; i++){
		if(strcmp(name, m[i].name) == 0){
			//menu is found
			index = i;
			break;
			
		}			
	}

	return index;
}

//return 1 if the add is successful;
int add_menu(struct menu_item m[20], int ctr){
	
	char name[20];
	int price, index;
	int success;

	printf("Enter name of menu: ");
	scanf("%s", name);
	printf("Enter price of menu: ");
	scanf("%d", &price);		

	//search for exisiting menu
	index = search_menu(m, name, ctr);

	if(index == -1){
		m[ctr] = update_menu(m[ctr], name, price);
		printf("Menu added: %s\n", m[ctr].name);
		printf("Menu price: %d\n\n", m[ctr].price);
		success = 1;
	} else {
		success = 0;
	}

	return success;
}

void print_menu_list(struct menu_item m[20], int ctr){

	int i;
	printf("List of menu\n\n");

	for(i = 0; i < ctr; i++){
		printf("Menu name: %s\n", m[i].name);
		printf("Menu price: %d\n", m[i].price);
	}
	printf("\n");
}




int main(void){
	
	struct menu_item menu[20];
	int i, choice, menu_ctr = 0;
	int success, index, new_price;
	char search_name[20];

	//initialize menu
	for(i = 0; i < 20; i++){
		//set default values
		menu[i] = update_menu(menu[i], "", -1);
		
	}

	do {
		choice = display_main_menu();

		switch(choice){
			case 1:
				//add menu
				success = add_menu(menu, menu_ctr);
				if(success){
					menu_ctr++;	//no of menu + 1
				} else {
					printf("\nThere's already a duplicate\n\n");
				}		
				break;
			case 2:
				//search
				printf("Enter name of menu: ");
				scanf("%s", search_name);
				index = search_menu(menu, search_name, menu_ctr);
				if(index != -1){
					printf("\nMenu name: %s", menu[index].name);
					printf("\nMenu price: %d\n\n", menu[index].price);
				} else {	
					
					printf("\nMenu not found. \n\n");	
				}
				break;
			case 3:
				//update price
				printf("Enter name of menu: ");
				scanf("%s", search_name);
				index = search_menu(menu, search_name, menu_ctr);
				if(index != -1){
					printf("Enter new price: ");
					scanf("%d", &new_price);
					menu[index] = update_menu(menu[index], search_name, new_price);
					printf("\n\n%s price updated: %d\n\n", menu[index].name, menu[index].price);
				} else {	
					printf("\nMenu not found. \n\n");	
				}
				break;
			case 4:
				print_menu_list(menu, menu_ctr);
				break;	
		}
	} while (choice != 5);	

	return 0;
}
