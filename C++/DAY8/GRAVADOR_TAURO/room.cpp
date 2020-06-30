#include <iostream>
#include <string>
#include "room.h"
#include "reservation.h"

using namespace std;

Room::Room(){
	capacity = 0;
	id = 0;
	reservationCount = 0;
	for(int i = 0; i < 7; i++){
		resCountDay[i] = 0;
	}
}

Room::Room(int id, int capacity){
	this->id = id;
	this->capacity = capacity;
	reservationCount = 0;
	for(int i = 0; i < 7; i++){
		resCountDay[i] = 0;
	}
}

void Room::showAllReservation(){
	string days[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
	cout << "Room " << getId() << endl;
	cout << "\tCapacity: " << getCapacity() << endl;
	cout << "\t--------------------\n";
	for(int i = 0; i < 7; i++){
		cout << "--------------" << days[i] << "------------------\n";
		for(int j = 0; j < resCountDay[i]; j++){
			reservation[i][j]->printDetails();
			cout << "\t--------------------\n";
		}
	}
	
}

void Room::reset(){
	for(int i = 0; i < 7; i++){
		for(int j = 0; j < resCountDay[i]; i++){
			delete reservation[i][j];
		}	
	}
	for(int i = 0; i < 7; i++){
		resCountDay[i] = 0;
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


void Room::addReservation(Reservation *res) {
	int startDay = res->getStartDay();
	int endDay = res->getEndDay();
	for(int i = startDay; i <= endDay; i++){
		int j = resCountDay[i];
		reservation[i][j] = res;
		resCountDay[i]++;
		reservationCount++;	
	}	
	sortReservation();
}

bool Room::hasConflict(Reservation *toRes){
	bool conflict = false;

	int start = toRes->getStartDay();
	int end = toRes->getEndDay();
	
	for(int i = start; i < end; i++){
		for(int j = 0; j < resCountDay[i]; j++){
			Reservation *curr = reservation[i][j];
			conflict = toRes->isConflictWith(curr);
			if(conflict) return conflict;
		}
	}
		
	return conflict;
}

bool Room::conflictWithClass(Reservation *prio) {
	bool flag = false;

	int span = prio->getSpan();
	int startDay = prio->getStartDay();
	int endDay = prio->getEndDay();

	for(int i = startDay; i < endDay; i++){
		for(int j = 0; j < resCountDay[i]; j++){
			Reservation *dayRes = reservation[i][j];
			if(prio->isConflictWith(dayRes)) {
				if(dayRes->getPriorityType() == Reservation::PRIORITY_CLASS) flag = true;
			}
		}
	}
	
	return flag;
}

Reservation*** Room::getConflictedReservation(Reservation *prio, int &sp, int *&size){

	int span = prio->getSpan();
	int startDay = prio->getStartDay();
	int endDay = prio->getEndDay();
	int conflictCount;
	Reservation ***conflictRes = new Reservation** [span];
	for(int i = 0; i < span; i++){
		int size = resCountDay[i];
		conflictRes[i] = new Reservation* [size];
	}

	int d = 0;
	for(int i = startDay; i < endDay; i++){
		conflictCount = 0;
		size[d] = 0;
		for(int j = 0; j < resCountDay[i]; j++){
			if(prio->isConflictWith(reservation[i][j])) {
				conflictRes[d][conflictCount] = reservation[i][j];
				resCountDay[i]--;
				for(int k = j; k < resCountDay[i]; k++){
					reservation[i][k] = reservation[i][k + 1];
					j--;
				}
				conflictCount++;
			}
		}
		sp = d;
		size[d] = conflictCount;
		d++;
	}	
	return conflictRes;
}

int Room::getReservationCount() const {
	return reservationCount;
}

Reservation* Room::getReservationAt(int day, int i) const{
	if(i >= reservationCount && i <= 0) return NULL;
	return reservation[day][i];
}

void Room::sortReservation(){
	for(int h = 0; h < 7; h++) {
		int size = resCountDay[h];
		for(int i = 0; i < size - 1; i++){
			for(int j = 0; j < (size - i) - 1; j++){
				int t1 = reservation[h][j]->getStartTimeToInt();
				int t2 = reservation[h][j + 1]->getStartTimeToInt();
				if(t1 > t2){;
					Reservation *temp = reservation[h][j];
					reservation[h][j] = reservation[h][j + 1];
					reservation[h][j + 1] = temp;
				}			
			}	
		}	
	}
}

/**************************************************************************************************/

Reservation** Room::getAllReservationsAtDay(int day, int &size){
	
}
	
int Room::getReservationCountAtDay(int day) const{
	return resCountDay[day];
}
		

Room::~Room(){

}



