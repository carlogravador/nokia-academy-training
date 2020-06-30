
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
		*	Check if room has no conflicts with the given reservation
		*/
		
		
		/**
		*	Getter and setter for reservation
		*	Getter @return NULL if index is greater than count
		*/
		void addReservation(Reservation*);
		Reservation* getReservationAt(int) const;
		
		bool hasConflict(Reservation*);
				
		/**
		*	Sort Reservation
		*/
		void sortReservation();
		int getReservationCount() const;
		
		void reset();
		
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
