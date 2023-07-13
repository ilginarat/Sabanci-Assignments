#include "Reservation.h"
#include "strutils.h"
#include "date.h"
#include <string>
#include <iostream>
using namespace std;


Sailor::Sailor(int i, string n, double a, double r)
{
    id=i;
    name=n;
    age=a;
    rank=r;
}

int Sailor::Id()
{
    return id;
}

string Sailor::Name()
{
    return name;
}

double Sailor::Age()
{
    return age;
}

double Sailor::Rank()
{
    return rank;
}



Boat::Boat(int i, string n, string c)
{
    id=i;
    name=n;
    color=c;
}


int Boat::Id()
{
    return id;
}

string Boat::Name()
{
    return name;
}

string Boat::Color()
{
    return color;
}

Reservation::Reservation(Sailor sa, Boat bo, string date)
{
    string y=date.substr(0,4);
    string m=date.substr(5,2);
    string d=date.substr(8,2);

    int Y=atoi(y);
    int M=atoi(m);
    int D=atoi(d);

    Date Date(M, D, Y);

    sailor=sa;
    boat=bo;
    resDate=Date;
}

Sailor Reservation::psailor()
{
    return sailor;
}

Boat Reservation::pboat()
{
    return boat;
}

Date Reservation::pdate()
{
    return resDate;
}


void Reservation::Printer()
{
    cout << resDate.MonthName() << " " << resDate.Day() << " " << resDate.Year() << " -> " << sailor.Name() << "(" << sailor.Rank() << "," << sailor.Age() << ")" << " has reserved " << boat.Name() << "(" << boat.Color() << ")" << endl;
}

Reservations::Reservations()
{
    vector<Reservation> reservations;
}

void Reservations::Add(Sailor sa, Boat bo, string date)
{
    reservations.push_back(Reservation(sa, bo, date));
    int size=reservations.size();
	int j, k, minIndex;
	Reservation temp;
	for(k=0; k < size - 1; k++) {
		minIndex = k; // min element index
		for(j=k+1; j < size; j++)
			{ if (reservations[j].pdate() < reservations[minIndex].pdate())
				{ minIndex = j; // new min index
				 }
					}
				 temp = reservations[k]; // swap min and k-th
				reservations[k] = reservations[minIndex];
				reservations[minIndex] = temp;
				 }
}


bool Reservations::Delete(int s_id, int b_id, string date)
{
    bool found=true;
    
        if (s_id != 0 && b_id != 0) {
            for(unsigned int i=0; i<reservations.size(); i++) {
            if (s_id == reservations[i].psailor().Id() && b_id == reservations[i].pboat().Id()) //cokiyi
            {

                    
                string y=date.substr(0,4);
                string m=date.substr(5,2);
                string d=date.substr(8,2);

                int Y=atoi(y);
                int M=atoi(m);
                int D=atoi(d);

                Date DaTe(M, D, Y);
                if (DaTe == reservations[i].pdate()) {
                    found=false;
				for (int x = i; x < reservations.size()-1; x++) {
					reservations[x] = reservations[x+1];
        }
        reservations.pop_back();

                }
                
            }
        }
        }
        else if (b_id == 0) {
            for(unsigned int i=0; i<reservations.size(); i++) {
				if (s_id  == reservations[i].psailor().Id()) //cokiyi
				{
                    found=false;
                    for (int x = i; x < reservations.size()-1; x++) {
						reservations[x] = reservations[x+1];
					}
            reservations.pop_back();

                }
			}
        }
        else {
            for(unsigned int i=0; i<reservations.size(); i++) {
                if (b_id  == reservations[i].pboat().Id()) //cokiyi
                {
                            found=false;
for (unsigned int x = i; x < reservations.size()-1; x++) {
                reservations[x] = reservations[x+1];
            }
            reservations.pop_back();

                    }
            }
        } 
	return found;
}

bool Reservations::FindDate(Date start, Date finish)
{
    bool found=true;
    cout << "Find Results:" << endl;

    
    for (unsigned int i=0; i<reservations.size();i++) {
        if (reservations[i].pdate().Absolute()>=start.Absolute() && reservations[i].pdate().Absolute()<=finish.Absolute()) {
            found=false;
            reservations[i].Printer();
        }
    }
   
   
	if (!found) {
		 cout << endl;
	}
	return found;
}
void Reservations::FindBoatDate(int b_id, string date) {
    bool found=true;
    cout << "Find Results:" << endl;
    for (unsigned int i=0; i<reservations.size();i++) {
        if (b_id==reservations[i].pboat().Id()) {
            string y=date.substr(0,4);
            string m=date.substr(5,2);
            string d=date.substr(8,2);

            int Y=atoi(y);
            int M=atoi(m);
            int D=atoi(d);

            Date DaTe(M, D, Y);
            if (DaTe==reservations[i].pdate()) {
                found=false;
                reservations[i].Printer();
            }
        }
    }
    if (found) {
        cout << "Error: No matching reservation found for boat id " << b_id << " on " << date << endl << endl;
    }
	else {
		 cout << endl;
	}
}

void Reservations::FindSailorDate(int s_id, string date) {
    bool found=true;
    cout << "Find Results:" << endl;
    for (unsigned int i=0; i<reservations.size();i++) {
        if (s_id==reservations[i].psailor().Id()) {
            string y=date.substr(0,4);
            string m=date.substr(5,2);
            string d=date.substr(8,2);

            int Y=atoi(y);
            int M=atoi(m);
            int D=atoi(d);

            Date DaTe(M, D, Y);
            if (DaTe==reservations[i].pdate()) {
                found=false;
                reservations[i].Printer();
            }
        }
    }
    if (found) {
        cout << "Error: No matching reservation found for sailor id " << s_id << " on " << date << endl << endl;
    }
	else {
		 cout << endl;
	}
}