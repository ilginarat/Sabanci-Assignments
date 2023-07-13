#include <iostream>
#include <vector>
#include <string>
#include "date.h"

class Sailor
{
	public:
		Sailor()
		{
			id = 0;
			name = "Jane Doe";
			age = 0;
			rank = 0;
		}
		Sailor(int i, string n, double a, double r); 

		int Id();
		string Name();
		double Age();
		double Rank();

	private:
		int id;
		string name;
		double age;
		double rank;
};

class Boat
{
	public:
		Boat()
		{
			id = 0;
			name = "Default";
			color = "Default";
		}

		Boat(int i, string n, string c);

		int Id();
		string Name();
		string Color();

	private:
		int id;
		string name;  
		string color;
};

class Reservation
{
	public:
		Reservation()
		{
			Sailor s;
			sailor = s;
			Boat b;
			boat = b;
			Date d(1,1,1900);
			resDate = d;
		}

		Reservation(Sailor sa, Boat bo, string date);

		Sailor psailor();
		Boat pboat();
		Date pdate();

		void Printer();

	private:
		Date resDate;
		Sailor sailor;
		Boat boat;
};

class Reservations
{
	public:
		
		Reservations();

		void Add(Sailor sa, Boat bo, string date);

		bool Delete(int s_id, int b_id, string date);

		bool FindDate(Date start, Date finish);

		void FindBoatDate(int b_id, string date);

		void FindSailorDate(int s_id, string date);

	private:
		vector<Reservation> reservations;
	
};