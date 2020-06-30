#include "person.h"
#include<iostream>

using namespace std;

Person::Person(int g, string n){
    name = n;
    group = g;
}

string Person::getName() const {
    return name;
}

int Person::getGroup() const {
    return group;
}

void Person::print() const {
    cout << "Name: " << name << " Group: " << group << endl;
}

Person::~Person(){

}