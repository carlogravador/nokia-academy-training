#ifndef PERSON_H
#define PERSON_H

#include<string>

using namespace std;

class Person {
   
    public:
        /**
         * @brief Construct a new Person object
         * 
         */
        Person(int, string);
        /**
         * @brief Get the Name object
         * 
         * @return string 
         */
        string getName() const;
        /**
         * @brief Get the Group object
         * 
         * @return int 
         */
        int getGroup() const;
        /**
         * @brief 
         * Print person details
         */
        void print() const;
        /**
         * @brief Destroy the Person object
         * 
         */
        ~Person();

    private:
        string name;    
        int group;
};

#include "person.cpp"

#endif