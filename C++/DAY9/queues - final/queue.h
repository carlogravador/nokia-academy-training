#ifndef QUEUE_H
#define QUEUE_H

template <class T>
class Queue {

	struct node {
		node *next;
		T data;
	};
	
	public:
		Queue();
		void enqueue(T);
		T dequeue();
		T getFront();
		int size() const;
		bool isEmpty() const;
		~Queue();
	
	private:
		node *head;
		node *tail;
		int count;
};

#include "queue.cpp"


#endif
