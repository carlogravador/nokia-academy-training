
#ifndef BUILDING_H
#define BUILDING_H

#include<string>

#include "room.h"
#include "reservation.h"

class Building {
		
		
	public:
		/**
		*	Constructor for Building
		*	Creates room depending on txt file
		*/
		Building();
		
		/**
			Add a reservation to the best room. Handles rescheduling.
		*	@return bool if added successfully
		*	@param Reservation to be reserved.
		*/
		bool addToBestRoom(Reservation*);
		
		void reschedule(Reservation***, int, int*);
		
		/**
		*	Find all available rooms for the reservation
		*	@return All suggested rooms
		*	@param Reservation to be reserved.
		*	@param int& size of suggested rsooms
		*/
		Room** suggestedRoomsFor(Reservation*, int&);
		
		/**
		*	Getter and Setter for Room
		*	Getter returns NULL if index out of bounds
		*/
		void setRoom(Room*);
		Room* getRoomAt(int);
		
		/**
		*	Prints all room details.
		*/
		void printAllRoomDetails();
		
		/**
		*	@return roomCount
		*/
		int getRoomCount() const;
		
		/**
		*	Sort room
		*/
		void sortRoomCapacity();
		void sortRoomId();
		
		/**
		*	Clear all reservation in all rooms.
		*/
		void clearReservation();
		
		/**
		*	Ask for user input about creating reservation.
		*/
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
