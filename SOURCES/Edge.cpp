#include "Edge.h"

Edge::Edge (int orig, int dest, int capacity):
origin(orig),
destination(dest),
capacity(capacity),
flow(0)
{}

Edge::~Edge ()
{

}

int Edge::getOrigin () const
{
	return origin;
}

int Edge::getDestination () const
{
	return destination;
}

int Edge::getCapacity () const
{
	return capacity;
}

int Edge::getFlow () const
{
	return flow;
}

void Edge::setFlow (int new_flow)
{
	flow = new_flow;
}
