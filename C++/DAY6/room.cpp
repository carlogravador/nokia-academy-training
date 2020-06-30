#include <iostream>
#include <string>
#include "room.h"
#include "reservation.h"

using namespace std;

Room::Room(){
	capacity = 0;
	id = 0;
	reservationCount = 0;
}

Room::Room(int id, int capacity){
	this->id = id;
	this->capacity = capacity;
	reservationCount = 0;
}

void Room::showAllReservation(){
	cout << "Room " << getId() << endl;
	cout << "\tCapacity: " << getCapacity() << endl;
	cout << "\t--------------------\n";
	for(int i = 0; i < reservationCount; i++){
		reservation[i]->printDetails();
		cout << "\t--------------------\n";
	}
}

void Room::reset(){
	for(int i = 0; i < reservationCount; i++){
		delete reservation[i];
	}
	reservationCount = 0;
}

int Room::getCapacity() const {
	return capacity;
}

void Room::setCapacity(int capacity) {
	this->capacity = capacity;
	reservationCount++;
}

int Room::getId() const {
	return id;
}

void Room::setId(int id) {
	this->id = id;
}


void Room::addReservation(Reservation *reservation) {
	int i = reservationCount;
	this->reservation[i] = reservation;
	reservationCount++;	
	sortReservation();
}

bool Room::hasConflict(Reservation *toRes){
	bool conflict = false;
	for(int i = 0; i < reservationCount; i++){
		Reservation *curr = reservation[i];
		conflict = toRes->isConflictWith(curr);
		if(conflict) return conflict;
	}
		
	return conflict;
}

Reservation** Room::getConflictedReservation(Reservation *prio, int &size){
	bool flag = false;
	Reservation **conflictRes = new Reservation* [reservationCount];
	int conflictCount = 0;
	for(int i = 0; i < reservationCount; i++){
		if(prio->isConflictWith(reservation[i])) {
			if(reservation[i]->getPriorityType() == Reservation::PRIORITY_CLASS) flag = true;
		}
	}
	
	if(flag) return NULL;
	
	for(int i = 0; i < reservationCount; i++){
		if(prio->isConflictWith(reservation[i])) {
			conflictRes[conflictCount] = reservation[i];
			reservationCount--;
			for(int j = i; j < reservationCount; j++){
				reservation[j] = reservation[j + 1];
				i--;
			}
			conflictCount++;
		}
	
	}
	size = conflictCount;
	return conflictRes;
}

int Room::getReservationCount() const {
	return reservationCount;
}

Reservation* Room::getReservationAt(int i) const{
	if(i >= reservationCount && i <= 0) return NULL;
	return reservation[i];
}

void Room::sortReservation(){
	int size = reservationCount;
	for(int i = 0; i < size - 1; i++){
		for(int j = 0; j < (size - i) - 1; j++){
			int t1 = reservation[j]->getStartTimeToInt();
			int t2 = reservation[j + 1]->getStartTimeToInt();
			if(t1 > t2){;
				Reservation *temp = reservation[j];
				reservation[j] = reservation[j + 1];
				reservation[j + 1] = temp;
			}			
		}	
	}	
}

Room::~Room(){

}



