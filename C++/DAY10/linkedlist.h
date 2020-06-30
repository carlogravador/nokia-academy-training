#ifndef LINKEDLIST_H
#define LINKEDLIST_H

template<class T>
class LinkedList{

	struct node {
		node *next;
		T data;
	};

	public:
		LinkedList();
		void add(T);
		void rewind();
		bool endOfList();
		T get();
		T get(T);
		T pull(T);
		int size() const;
		bool isEmpty() const;
		~LinkedList();
	
	private:
		node* current;
		node* head;
		node* tail;
		int count;

};

#include "linkedlist.cpp"

#endif
