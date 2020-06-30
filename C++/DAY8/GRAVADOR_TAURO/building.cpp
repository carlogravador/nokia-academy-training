#include <iostream>
#include <fstream>
#include "building.h"
#include <sstream>
#include <string>
#include <istream>

using namespace std;

int main(){

	Building *building = new Building();
	bool reserve;
	int choice;
	
	while(1){
		cout << "----------------------------------------------------\n";
		cout << "Press 1 to continue: ";
		cin>>choice;
		cin.ignore();
//		system("clear");

		cout << "1. Do you want to reserve a room? "<<endl;
		cout << "2. Do you want to view room schedules?"<<endl;
		cout << "3. Do you want to clear all schedules?"<<endl;
		cout << "4. Do you want to exit?"<<endl;
		cout << "Mode: ";
		cin>>choice;
		cin.ignore();
		switch(choice){
			case 1:
				reserve = true;
				break;
			case 2:
				cout << "-----------------ALL ROOMS--------------------------\n";
				building->printAllRoomDetails();
				continue;
			case 3:
				building->clearReservation();
				continue;
			case 4:
				return 0;
		
		}
		
		if(!reserve) break;
				
		Reservation *r = building->createReservation();
		int size;
		
		Room **suggested = building->suggestedRoomsFor(r, size);
		for(int i = 0; i < size; i++){
			cout << i + 1 << ". Room: " << suggested[i]->getId() << endl;
		}
		if(size <= 0) {
			cout << "No rooms available.\n";
		} else {
			int input;
			cout << "Please enter choice: ";
			cin >> input;
			
			if(r->getPriorityType() == Reservation::PRIORITY_CLASS){
				int span = 0;
				int *size;
				Reservation ***conflicts = suggested[input - 1]->getConflictedReservation(r, span, size);
				suggested[input - 1]->addReservation(r);
				r->setRoom(suggested[input - 1]);
				building->reschedule(conflicts, span, size);
			} else {
				suggested[input - 1]->addReservation(r);
				r->setRoom(suggested[input - 1]);			
			}
			suggested[input - 1]->showAllReservation();	
			
		}
		
		
		/*
		bool success = building->addToBestRoom(r);
		if(success) {
			cout << "Room added successfully\n";
		} else {
			cout << "No Rooms available\n";
		}
		*/
				
	}
	
	cout << "-------------Thank you----------------\n";		
	
	delete building;

	return 0;
}


Building::Building(){
	ifstream input("rooms.txt");
	
	int roomCtr = 0;
	string trash;
	int t;
	char tr;
	int size;
	
	while(1) {
		input >> trash >> t >> tr >> size;	
		roomCtr++;
		if(input.eof()) break;	
	}
	
	input.clear();
	input.seekg(0);
	rooms = new Room* [roomCtr];
	roomCtr = 0;
	while(1){
		input >> trash >> t >> tr >> size;
		if(input.eof()) break;	
		rooms[roomCtr] = new Room(t, size);		
		roomCtr++;
	}
	roomCount = roomCtr;
	
	input.close();
}

void Building::reschedule(Reservation ***conflicts, int span, int *dayCount){
	for(int i = 0; i < span; i++){
		for(int j = 0; j < dayCount[i]; j++){
			addToBestRoom(conflicts[i][j]);
		}
	}
}

bool Building::addToBestRoom(Reservation *reservation){
	
	string type = reservation->getPriorityType();
	bool success = false;
	sortRoomCapacity();
	
	for(int i = 0; i < roomCount; i++) {
		Room *r = rooms[i];
		if(type == Reservation::PRIORITY_CLASS) {
			if(r->getCapacity() >= reservation->getGuestCount()) {
				if(!r->hasConflict(reservation)){
					reservation->setRoom(r);
					r->addReservation(reservation);
					success = true;
					break;
				}
			}
		} else if (type == Reservation::PRIORITY_SMALL) {
			if(r->getCapacity() >= reservation->getGuestCount() &&
					r->getCapacity() <= 20){
				if(!r->hasConflict(reservation)){
					reservation->setRoom(r);
					r->addReservation(reservation);
					success = true;
					break;
				}
				//continue to next room
			}		
		} else if (type == Reservation::PRIORITY_LARGE) {
			if(r->getCapacity() >= reservation->getGuestCount() &&
						r->getCapacity() > 20){
				if(!r->hasConflict(reservation)){
					reservation->setRoom(r);
					r->addReservation(reservation);
					success = true;
					break;
				}
				//continue to next room
			}		
		}
	}
	
	if(!success){	//adjust time
						
		Room *prevRoom = reservation->getRoom();
						
		int origStartTime = reservation->getStartTimeToInt();
		int origEndTime = reservation->getEndTimeToInt();
		int stime = origStartTime;
		int etime = origEndTime;
		
		while(1){							
			stime++;
			etime++;
			
			reservation->setStartTime(stime);
			reservation->setEndTime(etime);
							
			if(etime == 1800) break;
			if(!prevRoom->hasConflict(reservation)) {
				prevRoom->addReservation(reservation);
				success = true;
				break;
			}
		}
		
		if(success) return success;
		
		stime = origStartTime;
		etime = origEndTime;
		while(1) {
			stime--;
			etime--;
			
			reservation->setStartTime(stime);
			reservation->setEndTime(etime);
							
			if(stime == 600) break;
			if(!prevRoom->hasConflict(reservation)) {
				prevRoom->addReservation(reservation);
				success = true;
				break;
			}
		}
	
	}
	
	return success;
}

Room** Building::suggestedRoomsFor(Reservation *reservation, int &size){
	Room** suggested = new Room* [roomCount];
	int sCtr = 0;
	
	string type = reservation->getPriorityType();
	sortRoomCapacity();
	
	for(int i = 0; i < roomCount; i++) {
		Room *r = rooms[i];
		if(type == Reservation::PRIORITY_CLASS) {
			if(r->getCapacity() >= reservation->getGuestCount()) {
				if(!r->hasConflict(reservation)){
					suggested[sCtr] = r;
					sCtr++;
				}
				//continue to next room
			}
		} else if (type == Reservation::PRIORITY_SMALL) {
			if(r->getCapacity() >= reservation->getGuestCount() &&
					r->getCapacity() <= 20){
				if(!r->hasConflict(reservation)){
					suggested[sCtr] = r;
					sCtr++;
				}
				//continue to next room
			}		
		} else if (type == Reservation::PRIORITY_LARGE) {
			if(r->getCapacity() >= reservation->getGuestCount() &&
						r->getCapacity() > 20){
				if(!r->hasConflict(reservation)){
					suggested[sCtr] = r;
					sCtr++;
				}
				//continue to next room
			}		
		}
	}
	//will reach if no room return
	
	if(type == Reservation::PRIORITY_CLASS) {
		for(int i = 0; i < roomCount; i++) {
			Room *r = rooms[i];
			if(r->getCapacity() >= reservation->getGuestCount()) {
				//find if room is already in the suggested list
				bool isFound = false;
				for(int j = 0; j < sCtr; j++){
					if(suggested[j]->getId() == r->getId()){
						isFound = true;
						break;	
					}
				}
				if(!isFound) {
					if(!r->conflictWithClass(reservation)){
						suggested[sCtr] = r;
						sCtr++;
					}
				}
				
			}
		}
	} 
	size = sCtr;
	return suggested;	
}

void Building::clearReservation() {
	for(int i = 0; i < roomCount; i++){
		rooms[i]->reset();
	}
}

Room* Building::getRoomAt(int index){
	if(index <= roomCount && index >= 0) {
		return this->rooms[index];
	}
	return NULL;
}

void Building::setRoom(Room *room){
	int i = roomCount;
	this->rooms[i] = room;
}

void Building::printAllRoomDetails(){
	sortRoomId();
	for(int i = 0; i < roomCount; i++){
		rooms[i]->showAllReservation();
	}
}

int Building::getRoomCount() const {
	return roomCount;
}

void Building::sortRoomCapacity(){
	int size = roomCount;
	for(int i = 0; i < size - 1; i++){
		for(int j = 0; j < (size - i) - 1; j++){
			int t1 = rooms[j]->getCapacity();
			int t2 = rooms[j + 1]->getCapacity();
			if(t1 > t2){;
				Room *temp = rooms[j];
				rooms[j] = rooms[j + 1];
				rooms[j + 1] = temp;
			
			}			
		}	
	}	
}

void Building::sortRoomId(){
	int size = roomCount;
	for(int i = 0; i < size - 1; i++){
		for(int j = 0; j < (size - i) - 1; j++){
			int t1 = rooms[j]->getId();
			int t2 = rooms[j + 1]->getId();
			if(t1 > t2){;
				Room *temp = rooms[j];
				rooms[j] = rooms[j + 1];
				rooms[j + 1] = temp;
			
			}			
		}	
	}	
}

Reservation* Building::createReservation(){

	string type;
	string startTime;
	string endTime;
	int guestSize;
	int mode;
	
	cout << "What kind of meeting will you have?\n";
		cout << "1:Class Meeting" << endl << "2:Small Meeting" << endl << "3:Large Meeting" << endl;
		cout << "Mode: ";
		cin >> mode;
		
		Reservation *r = new Reservation();
		switch(mode){
			case 1:
				type = Reservation::PRIORITY_CLASS;				
				break;
			case 2:
				type = Reservation::PRIORITY_SMALL;
				break;
			case 3:
				type = Reservation::PRIORITY_LARGE;
				break;
		}
		r->setPriorityType(type);
		
		while(1){
			cout << "How many people will there be?: ";
			cin >> guestSize;
			cin.ignore();
			if(r->setGuestCount(guestSize)) break;
			cout << "Guest size not fit for the room\n";
		}
		
		while(1){
			cout << "What time will it be schedule? (0600-1800): ";		
			getline(cin, startTime);
			if(r->setStartTime(startTime)) break;
			cout << "Please enter a valid time\n";
		}
		while(1){
			cout << "What time will it end? (0600-1800): ";		
			getline(cin, endTime);
			if(r->setEndTime(endTime)) break;
			cout << "Please enter a valid time\n";
		}
		
//	Reservation *r = new Reservation(startTime, endTime, type, guestSize);
	
	return r;

}


Building::~Building(){
	clearReservation();
	for(int i = 0; i < roomCount; i++){
		delete rooms[i];
	}
	
}


