
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
		*/		
		void setStartTime(string);
		string getStartTime() const;
		int getStartTimeToInt() const;
		
		/**
		*	Getter and setter for endTime.
		*/		
		void setEndTime(string);
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
		void setGuestCount(int);
		int getGuestCount() const;
		
			
		void setRoom(Room*);
		Room* getRoom() const;
		
		/**
		*
		*/
		bool isConflictWith(Reservation*) const;

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
