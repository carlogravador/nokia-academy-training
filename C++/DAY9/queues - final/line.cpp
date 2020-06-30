#include "line.h"
#include <iostream>

using namespace std;

Line::Line(){
    line = new LinkedList<Queue<Person*>*>();
}

void Line::insert(Person *p){
    Queue<Person*> *group;  
    if(line->isEmpty()){    //first entry
        group = new Queue<Person*>();
        group->enqueue(p);
        line->add(group);
    } else {
        group = findGroup(p->getGroup());
        if(group == NULL || p->getGroup() == -1) {
            group = new Queue<Person*>();
            group->enqueue(p);
            line->add(group);
        } else {
            group->enqueue(p);
        }
    }
}

Person* Line::next(){
    Person *p = NULL;
    while(!line->endOfList()){
        Queue<Person*> *group = line->get();
        if(!group->isEmpty()){
            p = group->dequeue();
            break;
        }
    }
    line->rewind();
    return p;
}

Queue<Person*>* Line:: findGroup(int groupName) {
    Queue<Person*> *group;
    line->rewind();
    while(!line->endOfList()){
        group = line->get();
        if(group->isEmpty()){
            line->remove(group);
            delete group;
            continue;
        }
        Person *p = group->getFront();
        if(p->getGroup() == groupName){
            line->rewind();
            return group;
        } 
    }
    line->rewind();
    return NULL;
}

Line::~Line(){
    while(!line->endOfList()){
        Queue<Person*> *group = line->get();
        delete group;
    }
    delete line;
}