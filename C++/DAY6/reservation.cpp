#include <sstream>
#include <iostream>
#include "reservation.h"
#include "room.h"

using std::cout;
using std::endl;
using std::stringstream;

const string Reservation::PRIORITY_CLASS = "Class meeting";
const string Reservation::PRIORITY_LARGE = "Large meeting";
const string Reservation::PRIORITY_SMALL = "Small meeting";

Reservation::Reservation(){
	startTime = "";
	endTime = "";
	priorityType = "";
	guestCount = 0;
}

Reservation::Reservation(string st, string et, string pt, int count){
	startTime = st;
	endTime = et;
	priorityType = pt;
	guestCount = count;
}

void Reservation::setRoom(Room* r){
	room = r;
}
Room* Reservation::getRoom() const {
	return room;
}

void Reservation::setStartTime(string st){
	startTime = st;
}

string Reservation::getStartTime() const {
	return startTime;
}

int Reservation::getStartTimeToInt() const {
	int time = 0;
	stringstream converter(startTime);
	converter >> time;
	return time;
}

void Reservation::setEndTime(string st){
	endTime = st;
}

string Reservation::getEndTime() const {
	return endTime;
}

int Reservation::getEndTimeToInt() const {
	int time = 0;
	stringstream converter(endTime);
	converter >> time;
	return time;
}

void Reservation::setPriorityType(string type){
	priorityType = type;
}

string Reservation::getPriorityType() const{
	return priorityType;
}

bool Reservation::isConflictWith(Reservation *curr) const{
	bool conflict = false;
	if(curr->getStartTimeToInt() <= this->getStartTimeToInt() && 
				curr->getEndTimeToInt() > this->getStartTimeToInt()) {
		conflict = true;
	}
	if(curr->getStartTimeToInt() < this->getEndTimeToInt() && 
			curr->getEndTimeToInt() >= this->getEndTimeToInt()) {
		conflict = true;
	}	
	return conflict;
}

void Reservation::setGuestCount(int count){
	guestCount = count;
}

int Reservation::getGuestCount() const{
	return guestCount;
}

void Reservation::printDetails() const{
	cout << "\tMeeting type: " << priorityType << endl;
	cout << "\tSchedule :" << startTime << "-" << endTime << endl;
	cout << "\tNumber of Guest: " << guestCount << endl;
}

Reservation::~Reservation(){

}

