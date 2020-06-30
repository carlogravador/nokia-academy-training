#include "queues.h"

template <class T>
Queue<T>::Queue(){
	head = NULL;
	tail = NULL;
	count = 0;
}

template <class T>
Queue<T>::~Queue(){

}

template <class T>
void Queue<T>::enqueue(T data){
	if(hed == NULL){
		head = new node();
		head->data = data;
	} else {
	
	}
	count++;
}

template <class T>
T Queue<T>::dequeue(){
	

}

template <class T>
int Queue<T>::size() const {
	return count;
}

template <class T>
bool Queue<T>::isEmpty() const {
	return count == 0;
}
