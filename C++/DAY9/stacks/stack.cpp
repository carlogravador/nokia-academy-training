#include <iostream>
#include "stack.h"

using namespace std;

template <class T>
Stack<T>::Stack(){
	head = NULL;
	count = 0;
}

template <class T>
Stack<T>::~Stack(){
	while(!isEmpty()){
		pop();
	}
}

template <class T>
void Stack<T>::push(T data){
	
	if(head == NULL){
		head = new node();
		head->data = data;
		head->next = NULL;
	} else {
		node *temp = head;
		head = new node();
		head->data = data;
		head->next = temp;
	}
	count++;
}

template <class T>
T Stack<T>::pop(){
	if(head == NULL) {
		cout << "Stack is empty. Program will close with error\n";
		exit(0);
	}
	T data = head->data;
	node *temp = head;
	head = head->next;
	delete temp;
	count--;
	
	return data;
}

template <class T>
T Stack<T>::top(){
	return head->data;
}

template <class T>
int Stack<T>::size() const {
	return count;
}

template <class T>
bool Stack<T>::isEmpty() const {
	return count == 0;
}
