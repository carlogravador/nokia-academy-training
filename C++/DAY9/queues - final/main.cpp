#include <iostream>
#include<cstdlib>
#include<cstring>
#include<fstream>
#include "queue.h"
#include "person.h"
#include "line.h"

#define LEN 1024

using namespace std;

Person ***generateGroups(ifstream &file, int &groupCtr, int *&memCtr){
    char buffer[LEN] = {0};
    int groupCount = 0;
    file.getline(buffer, LEN);
    groupCount = atoi(buffer);
    groupCtr = groupCount;
    memCtr = new int[groupCount];
    Person ***groups = new Person** [groupCount];
    for(int i = 0; i < groupCount; i++){
        file.getline(buffer, LEN);
        int null = strlen(buffer) - 1;
        char *copy = new char[LEN];
        int memCount = 0;
        buffer[null] = '\0';
        strcpy(copy, buffer);
        char *tok = strtok(buffer, ", ");
        while(tok != NULL){
            tok = strtok(NULL, ", ");
            memCount ++;
        }
        memCtr[i] = memCount;
        groups[i] = new Person* [memCount];
        tok = strtok(copy, ", ");
        memCount = 0;
        while(tok != NULL) {
            string name(tok);
            groups[i][memCount] = new Person(i + 1, name);
            memCount++;
            tok = strtok(NULL, ", ");
        }
        delete copy;
    }

    return groups;
}

Person *findPerson(Person ***group, string name, int size, int *groupSize){
    for(int i = 0; i < size; i++){
        for(int j = 0; j < groupSize[i]; j++){
            Person *p = group[i][j];
            if(p->getName() == name){
                return p;
            }
        }
    }
    return NULL;
}

string* parseOperations(ifstream &file, int &operationCount){
    string *operations;
    char buffer[LEN] = {0};
    file.getline(buffer, LEN);
    operationCount = atoi(buffer);
    operations = new string [operationCount];
    for(int i = 0; i < operationCount; i++){
        file.getline(buffer, LEN);
        int null = strlen(buffer) - 1;
        buffer[null] = '\0';
        string op(buffer);
        operations[i] = op;
    }

    return operations;
}


int main(){
    
    Line *line = new Line();
    ifstream input("friends.txt");
    int operationsCtr;
    int noOfGroups;
    int *memberPerGroup;
    Person ***groups = generateGroups(input, noOfGroups, memberPerGroup);
    string *operations = parseOperations(input, operationsCtr);
    LinkedList<Person*> *nonMember = new LinkedList<Person*>();
    
    for(int i = 0; i < operationsCtr; i++){
        Person *p;
        string op = operations[i];
        if(op == "*"){
            p = line->next();
            p->print();
        } else {
            p = findPerson(groups, operations[i], noOfGroups, memberPerGroup);
            if(p == NULL){
                p = new Person(-1, operations[i]);
                nonMember->add(p);
                line->insert(p);
            } else {
                line->insert(p);
            }
        }
    }

    
    
    input.close();
    for(int i = 0; i < noOfGroups; i++){
        for(int j = 0; j < memberPerGroup[i]; j++){
            delete groups[i][j];
        }
        delete groups[i];
    }
    delete groups;
    delete memberPerGroup;
    delete operations;
    for(int i = 0; i < nonMember->size(); i++){
        Person *ps = nonMember->get();
        delete ps;
    }
    delete nonMember;
    delete line;
    return 0;
}
