#ifndef QUEUES_H
#define QUEUES_H

template <class T>
class Queue {

	struct node {
		node *next;
		T data;
	}
	
	public:
		Queue();
		void enqueue(T);
		T dequeue();
		int size() const;
		bool isEmpty() const;
		~Queue();
	
	private:
		node *head;
		node *tail;
		int count;



};


#endif
