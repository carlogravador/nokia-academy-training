
#ifndef ROOM_H
#define ROOM_H

//#include "reservation.h"
class Reservation;


class Room {

	public:
		/**
		*	Constructor for room
		*/
		Room();
		
		/**
		*	Constructor for room.
			@param int as roomId;
			@param int as roomCapacity
		*/
		Room(int, int);
		
		/**
		*	Print all reservations.
		*/
		void showAllReservation();
		
		/**
		*	Getter and setter for capacity
		*/
		int getCapacity() const;
		void setCapacity(int);
		
		/**
		*	Getter and setter for id
		*/
		int getId() const;
		void setId(int);
		
		
		/**
		*	Getter and setter for reservation
		*	Getter @return NULL if index is greater than count
		*/
		void addReservation(Reservation*);
		Reservation* getReservationAt(int) const;
		
		/**
		*	Checks if reservation has conflict with other reservation in the room.
		*	@param Reservation* - reservation to be compared to all reservations in the room.
		*	@return bool
		*/
		bool hasConflict(Reservation*);
				
		/**
		*	Sort Reservation
		*/
		void sortReservation();
		
		/**
		*	@return number of reservation in the room
		*/
		int getReservationCount() const;
		
		/**
		*	Clears all reservation in the room`
		*/
		void reset();
		
		/**
		*	@return reservation** - all reservation with conflict.
		*	@param Reservation* - reservation to be compared to all reservations in the room.
		*	@param int& - count of all conflicted reservation
		*/
		Reservation** getConflictedReservation(Reservation*, int&);
		
		/**
		*	Destructor for room.
		*/
		~Room();
		
	
	private:
		int capacity;
		int id;
		Reservation *reservation[720];
		int reservationCount;
		

};

#endif
