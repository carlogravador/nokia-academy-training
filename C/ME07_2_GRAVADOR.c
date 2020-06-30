//ME07_2.c


#include<stdio.h>
#include<stdlib.h>
#include<string.h>


typedef struct menu_item {
	char name[20];
	int price;
	struct menu_item *leftPtr;
	struct menu_item *rightPtr;
} menu;

menu *new_menu(char *name, int price){
	menu *new_menu = (menu*)malloc(sizeof(menu));

	strcpy(new_menu->name, name);
	new_menu->price = price;
	new_menu->leftPtr = NULL;
	new_menu->rightPtr = NULL;

	return new_menu;
}

void print_menu(menu *root){
	if(root != NULL){
		//print all left of the parent
		print_menu(root->leftPtr);
		//print the parent
		printf("Menu name: %s\n", root->name);
		printf("Menu price: %d\n", root->price);
		//print all right of the parent
		print_menu(root->rightPtr);
	}
}

menu *insert_by_price(menu *parent, char* name, int price){
	//if it reach a leaf node
	if(parent == NULL) {
		return new_menu(name, price);
	}
	
	if(parent->price <= price){	//move to the left
		parent->leftPtr = insert_by_price(parent->leftPtr, name, price);
	} else if (parent->price > price) {	//move to the right
		parent->rightPtr = insert_by_price(parent->rightPtr, name, price);
	}
	
	return parent;
}

menu *insert_by_name(menu *parent, char* name, int price){
	//if it reach a leaf node
	if(parent == NULL) {
		return new_menu(name, price);
	}
	
	if(strcmp(parent->name, name) >= 0){	//move to the left
		parent->leftPtr = insert_by_name(parent->leftPtr, name, price);
	} else if (strcmp(parent->name, name ) < 0) {	//move to the right
		parent->rightPtr = insert_by_name(parent->rightPtr, name, price);
	}

	return parent;
}



menu *search_menu(menu *root, char *name){
	menu *result = NULL;
	while(root != NULL){
		if(strcmp(root->name, name) == 0){	//break the loop
			result = root;
			break;
		}
		else if(strcmp(root->name, name) >= 0){	//move to the left
			root = root->leftPtr;
		} else if (strcmp(root->name, name ) <= 0) {	//move to the right
			root = root->rightPtr;
		}
	}

	return result;
} 

menu *min_val_menu(menu *root){
	while(root->leftPtr != NULL){
		root = root->leftPtr;
	}
	return root;
}

menu *delete_node(menu *root, menu *to_delete){
	
	menu *temp;

	if(root == NULL) return root;
	

	if(to_delete->price < root->price){	//find it on the left side
		root->leftPtr = delete_node(root->leftPtr, to_delete);
	} else if(to_delete->price > root->price) {		//find it on the right side
		root->rightPtr = delete_node(root->rightPtr, to_delete);
	} else {		//found the menu to be deleted
		if(root->leftPtr == NULL) {	
			temp = root->rightPtr;
			free(root);
			return temp;
		} else if(root->rightPtr == NULL) {
			temp = root->leftPtr;
			free(root);
			return temp;
		}

		//menu to be deleted has two childs
		//find the smallest value; -> on the right side
		temp = min_val_menu(root->rightPtr);

		//copy value to the root
		strcpy(root->name, temp->name);
		root->price = temp->price;
		
		root->rightPtr = delete_node(root->rightPtr, temp);
	}
	return root;
}



void update_menu(menu **root_name, menu **root_price, menu *to_update, int new_price){
	char temp_name[20];
	strcpy(temp_name, to_update->name);

	*root_name = delete_node(*root_name, to_update);
	*root_price = delete_node(*root_price, to_update);

	printf("To update name: %s\n", temp_name);
	
	*root_name = insert_by_name(*root_name, temp_name, new_price);
	*root_price = insert_by_price(*root_price, temp_name, new_price);	
}



int display_menu(){
	int choice;

	printf("Main Menu\n");
	printf("1. Add a dish from the menu\n");
	printf("2. Search a dish from the menu\n");
	printf("3. Change dish price\n");
	printf("4. Print menu by name\n");
	printf("5. Print menu by price\n");
	printf("6. Exit program\n\n");

	printf("Enter mode: ");
	scanf("%d", &choice);
	printf("\n");
	return choice;

}

void free_root(menu *root){
	if(root != NULL){
		//free left
		free_root(root->leftPtr);
		//free self
		free(root);
		//free the right
		free_root(root->rightPtr);
	}
}


int main(void){

	int mode, price;

	char menu_name[20];
	menu *root_name = NULL;
	menu *root_price = NULL;
	menu *result;

	do {
		mode = display_menu();
		
		switch(mode){
			case 1:
				printf("Add a menu\n");
				printf("Enter menu name: ");
				scanf("%s", menu_name);
				printf("Enter price: ");
				scanf("%d", &price);
				
				if(root_name == NULL && root_price == NULL){	//assign root to each tree
					root_name = insert_by_name(root_name, menu_name, price);
					root_price = insert_by_price(root_price, menu_name, price);
				} else {
					result = search_menu(root_name, menu_name);
					if(result != NULL){
						printf("Menu already in the list\n");
						continue;
					}
					insert_by_name(root_name, menu_name, price);
					insert_by_price(root_price, menu_name, price);
				}
				printf("Added succesully. %s: P%d\n\n", menu_name, price);
				break;
			case 2:
				printf("Search for menu\n");
				printf("Enter menu name: ");
				scanf("%s", menu_name);
				result = search_menu(root_name, menu_name);
				if(result == NULL){
					printf("Menu not found\n\n");
					continue;
				}
				printf("Menu name: %s\n", result->name);
				printf("Menu price: %d\n\n", result->price);
				break;
			case 3:
				printf("Update menu price\n");
				printf("Enter menu name: ");
				scanf("%s", menu_name);
				result = search_menu(root_name, menu_name);
				if(result == NULL){
					printf("Menu not found\n\n");
					continue;
				}
				printf("Enter new price: ");
				scanf("%d", &price);
				update_menu(&root_name, &root_price, result, price);
				break;
			case 4:
				print_menu(root_name);
				break;
			case 5:
				print_menu(root_price);
				break;
		} 
	} while(mode != 6);	

	free_root(root_name);
	free_root(root_price);

	return 0;
}
