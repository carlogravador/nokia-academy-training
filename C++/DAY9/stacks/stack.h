#ifndef STACK_H
#define STACK_H

template<class T>
class Stack {
	
	struct node {
		node *next;
		T data;
	};

	public :
		Stack();
		void push(T data);
		T pop();
		T top();
		~Stack();
		
		int size() const;
		bool isEmpty() const;

	private:
		node *head;
		int count;

};

#include "stack.cpp"

#endif
