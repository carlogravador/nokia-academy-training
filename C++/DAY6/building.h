
#ifndef BUILDING_H
#define BUILDING_H

#include<string>

#include "room.h"
#include "reservation.h"

class Building {
		
		
	public:
		/**
		*	Constructor for Building
		*/
		Building();
		
		/**
		*	@return bool if added successfully
			@param Reservation to be reserved.
		*/
		bool addToBestRoom(Reservation*);
		
		
		/**
		*	Getter and setter for Room
		*/
		void setRoom(Room*);
		
		void printAllRoomDetails();
		
		/**
		*	@return roomCount
		*/
		int getRoomCount() const;
		
		void sortRoomCapacity();
		void sortRoomId();
		void clearReservation();
		
		Reservation* createReservation();
		
		/**
		*	Destructor for Building
		*/
		~Building();
	
	private:
		Room **rooms;
		int roomCount;

};


#endif
