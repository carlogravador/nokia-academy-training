#ifndef LINE_H
#define LINE_H

#include "linkedlist.h"
#include "queue.h"
#include "person.h"

class Line {
    
    public:
        Line();
        void insert(Person*);
        Person* next();
        Queue<Person*> *findGroup(int);
        ~Line();
    private:
        LinkedList<Queue<Person*>*> *line;

};

#include "line.cpp"

#endif