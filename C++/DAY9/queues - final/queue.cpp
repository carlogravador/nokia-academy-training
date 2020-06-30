#include <iostream>
#include "queue.h"

using namespace std;

template <class T>
Queue<T>::Queue(){
	head = NULL;
	tail = NULL;
	count = 0;
}

template <class T>
Queue<T>::~Queue(){
	while(!isEmpty()){
		dequeue();
	}
}

template <class T>
void Queue<T>::enqueue(T data){
	if(head == NULL){
		head = new node();
		head->data = data;
		head->next = NULL;
		tail = head;
	} else if (head == tail){
		tail = new node();
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

template <class T>
T Queue<T>::dequeue(){
	node *temp;
	T tempData;
	if(head == NULL){
		cout << "Underflow\n";
	} else {
		tempData = head->data;
		temp = head;
		head = head->next;
		delete temp;
	}
	count--;
	return tempData;
}

template <class T>
T Queue<T>::getFront(){
	T tempData;
	if(head == NULL){
		cout << "Queue Undeflow\n";
	} else {
		tempData = head->data;
	}
	return tempData;
}

template <class T>
int Queue<T>::size() const {
	return count;
}

template <class T>
bool Queue<T>::isEmpty() const {
	return count == 0;
}
