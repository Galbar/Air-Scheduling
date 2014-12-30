#ifndef FLIGHT_H
#define FLIGHT_H


class Flight
{
	int origin, destination, time_start, time_end;
public:
	Flight(int orig, int dest, int time_start, int time_end);
	~Flight();

	int getOrigin() const;
	int getDestination() const;
	int getTakeoffTime() const;
	int getArrivalTime() const;
	
};
#endif