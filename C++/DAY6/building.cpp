#include <iostream>
#include <fstream>
#include "building.h"
#include <sstream>
#include <string>

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
		system("clear");

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
		
		bool success = building->addToBestRoom(r);
		if(success) {
			cout << "Room added successfully\n";
		} else {
			cout << "No Rooms available\n";
		}
				
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

bool Building::addToBestRoom(Reservation *reservation){
	
	string type = reservation->getPriorityType();
	sortRoomCapacity();
	
	for(int i = 0; i < roomCount; i++) {
		Room *r = rooms[i];
		if(type == Reservation::PRIORITY_CLASS) {
			if(r->getCapacity() >= reservation->getGuestCount()) {
				if(!r->hasConflict(reservation)){
					reservation->setRoom(r);
					r->addReservation(reservation);
					return true;
				}
			}
		} else if (type == Reservation::PRIORITY_SMALL) {
			if(r->getCapacity() >= reservation->getGuestCount() &&
					r->getCapacity() <= 20){
				if(!r->hasConflict(reservation)){
					reservation->setRoom(r);
					r->addReservation(reservation);
					return true;
				}
				//continue to next room
			}		
		} else if (type == Reservation::PRIORITY_LARGE) {
			if(r->getCapacity() >= reservation->getGuestCount() &&
						r->getCapacity() > 20){
				if(!r->hasConflict(reservation)){
					reservation->setRoom(r);
					r->addReservation(reservation);
					return true;
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
				int size = 0;
				Reservation **conflicts = r->getConflictedReservation(reservation, size);
				if(conflicts == NULL) continue;
				r->addReservation(reservation);
				reservation->setRoom(r);
				for(int j = 0; j < size; j++){
					bool success = addToBestRoom(conflicts[j]);
					if(success){
						cout << "Reservation rescheduled successfully\n";
					} else {
						//adjust time
						bool possible = false;
						
						Room *prevRoom = conflicts[j]->getRoom();
						
						int origStartTime = conflicts[j]->getStartTimeToInt();
						int origEndTime = conflicts[j]->getEndTimeToInt();
						int stime = origStartTime;
						int etime = origEndTime;
						while(1){							
							stime++;
							etime++;
							string newst = to_string(stime);
							string newet = to_string(etime);
							conflicts[j]->setStartTime(newst);
							conflicts[j]->setEndTime(newet);
							
							if(etime == 1800) break;
							if(!prevRoom->hasConflict(conflicts[j])) {
								r->addReservation(conflicts[j]);
								possible = true;
								break;
							}
						}
						if(possible) continue;
						stime = origStartTime;
						etime = origEndTime;
						while(1) {
							stime--;
							etime--;
							string newst = to_string(stime);
							string newet = to_string(etime);
							conflicts[j]->setStartTime(newst);
							conflicts[j]->setEndTime(newet);
							
							if(stime == 600) break;
							if(!prevRoom->hasConflict(conflicts[j])) {
								r->addReservation(conflicts[j]);
								possible = true;
								break;
							}
						}
						if(possible) cout << "Reservation rescheduled successfully\n";
						else cout << "Sorry we can't reschedule your resservation\n";
					}
				}
				delete conflicts;
				return true;
			}
		}
	} 
	return false;	
}

void Building::clearReservation() {
	for(int i = 0; i < roomCount; i++){
		rooms[i]->reset();
	}
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
		
		cout << "How many people will there be?: ";
		cin >> guestSize;

		cout << "What time will it be schedule? ";		
		cin >> startTime;
		
		cout << "What time will it end? ";		
		cin >> endTime;
		
	Reservation *r = new Reservation(startTime, endTime, type, guestSize);
	
	return r;

}

Building::~Building(){
	clearReservation();
	for(int i = 0; i < roomCount; i++){
		delete rooms[i];
	}
	
}


