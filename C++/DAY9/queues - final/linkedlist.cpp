#include <iostream>
#include <cstdlib>
#include "linkedlist.h"

using namespace std;

template<class T>
LinkedList<T>::LinkedList(){
	head = NULL;
	tail = NULL;
	current = head;
	count = 0;
}

template<class T>
LinkedList<T>::~LinkedList(){
	rewind();
	while(!endOfList()){
		remove(get());
	}
	rewind();
}

template<class T>
void LinkedList<T>::add(T data){
	if(head == NULL) {
		head = new node();
		current = head;
		head->data = data;
		head->next = NULL;
		tail = head;
	} else if(tail == head) {
		tail = new node;
		head->next = tail;
		tail->data = data;
		tail->next = NULL;
	} else {
		tail->next = new node();
		tail = tail->next;
		tail->data = data;
		tail->next = NULL;
	}
	count++;
}

template<class T>
void LinkedList<T>::rewind(){
	current = head;
}

template<class T>
bool LinkedList<T>::endOfList(){
	return current == NULL;
}

template<class T>
T LinkedList<T>::getRandom(){
	if(head == NULL){
		cout << "Underflow\n";
	}
	srand(time(0));
	int ctr = 0;
	int pos = rand() % count;
	T data;
	while (ctr <= pos){
		data = get();
		ctr++;
	}
	rewind();
	return data;
}

template<class T>
T LinkedList<T>::get(){
	if(head == NULL){
		cout << "Linkedlist Underflow\n";
	}
	T data = current->data;
	current = current->next;
	return data;
}

template<class T>
T LinkedList<T>::get(T data){
	node *curr = head;
	
	if(head == NULL){
		return data;
	}
	
	while(curr != NULL){
		if (curr->data == data){
			return curr->data;
		} 
		curr = curr->next;
	}
	return data;
}

template<class T>
void LinkedList<T>::remove(T data){
	node *curr = head;
	node *prev;
	node *temp;
	node *toRemove = NULL;
	while(curr != NULL){
		if(head->data == data){
			toRemove = head;
			break;
		} else if (curr->data == data){
			toRemove = curr;
			break;
		} else {
			prev = curr;
			curr = curr->next;
		}
	}

	if(head == NULL){
		cout << "Linkedlist Underflow\n";
	} else if(toRemove == head){
		temp = head;
		head = head->next;
		delete temp;
	} else if(toRemove != NULL){
		temp = toRemove;
		prev->next = temp->next;
		delete temp;
	} 
	count--;
}

template<class T>
int LinkedList<T>::size() const {
	return count;
}

template<class T>
bool LinkedList<T>::isEmpty() const {
	return count == 0;
}
