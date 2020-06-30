#include "linkedlist.h"
#include <iostream>

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
T LinkedList<T>::get(){
	if(head == NULL){
		cout << "Underflow\n";
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
T LinkedList<T>::pull(T data){
	node *curr = head;
	node *prevToDel = NULL;
	T tempData;
	while(curr != NULL){
		if(head->data == data){
			prevToDel = head;
			break;
		} else if (curr->next->data == data){
			prevToDel = curr->next;
			break;
		} else {
			curr = curr->next;
		}
	}
	node *temp;
	if(head == NULL){
		cout << "Underflow\n";
	} else if(prevToDel == head){
		temp = head;
		tempData = head->data;
		head = head->next;
		delete temp;
	} else if(prevToDel != NULL){
		temp = prevToDel->next;
		tempData = temp->data;
		prevToDel->next = temp->next;
		delete temp;
	} 
	count--;
	return tempData;
}

template<class T>
int LinkedList<T>::size() const {
	return count;
}

template<class T>
bool LinkedList<T>::isEmpty() const {
	return count == 0;
}
