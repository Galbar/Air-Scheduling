#include "Flight.h"

Flight::Flight(int orig, int dest, int time_start, int time_end):
origin(orig),
destination(dest),
time_start(time_start),
time_end(time_end)
{}

Flight::~Flight()
{

}

int Flight::getOrigin() const
{
	return origin;
}

int Flight::getDestination() const
{
	return destination;
}

int Flight::getTakeoffTime() const
{
	return time_start;
}

int Flight::getArrivalTime() const
{
	return time_end;
}
