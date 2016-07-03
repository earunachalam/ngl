#include "parameters.h"
#include "Sp.h"
#include "Subdomain.h"
#include "universal.h"

bool Subdomain::outOfBounds(int& indexResident)
{

	bool out_north, out_south, out_west, out_east;				// true if the resident is out of bounds wrt the Specified direction
	out_north = (residents.at(indexResident)->x[1] > north);
	out_south = (residents.at(indexResident)->x[1] < south);
	out_east = (residents.at(indexResident)->x[0] > east);
	out_west = (residents.at(indexResident)->x[0] < west);

	if (out_north || out_south || out_east || out_west){
		return true;
	}

	return false;
}