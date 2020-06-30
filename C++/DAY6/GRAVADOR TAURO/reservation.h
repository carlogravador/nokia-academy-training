
#ifndef RESERVATION_H
#define RESERVATION_H

#include<string>

using std::string;
class Room;

class Reservation {

	public:
		static const string PRIORITY_CLASS;
		static const string PRIORITY_LARGE;
		static const string PRIORITY_SMALL;
		
		/**
		*	Constructor for reservation
		*/
		Reservation();
		
		/**
		*
		*/
		Reservation(string, string, string, int);
		
		/**
		*	Getter and setter for startTime.
		*	@return if true or false for setter
		*/		
		bool setStartTime(string);
		string getStartTime() const;
		int getStartTimeToInt() const;
		
		/**
		*	@return if true or false for setter
		*	Getter and setter for endTime.
		*/		
		bool setEndTime(string);
		string getEndTime() const;
		int getEndTimeToInt() const;
		
		/**
		*	Getter and setter for priorityType.
		*/		
		void setPriorityType(string);
		string getPriorityType() const;

		/**
		*	Getter and setter for guestCount.
		*/				
		bool setGuestCount(int);
		int getGuestCount() const;
		
		/**
		*	Getter and setter for the room of a reservation
		*/	
		void setRoom(Room*);
		Room* getRoom() const;
		
		/**
		*	@return bool - Checks if has conflict with other reservation
		*/
		bool isConflictWith(Reservation*) const;
		
		/**
		*	Prints reservation detail
		*/
		void printDetails() const;
		
		~Reservation();
		
	
	private:
		string startTime;
		string endTime;
		string priorityType;
		Room *room;

		int guestCount;
};

#endif
