#include "distance.h"


#include "parameters.h"
#include "universal.h"

// In a two-dimensional system with periodic boundary conditions, compute the
// Euclidean distance between a point with coordinates specified by array
// obj0_pos and the closest image of a point with coordinates Specified by
// array obj1_pos.

void distance::center(const parameters& sysparams, const std::array<double,2>& obj0_pos, const std::array<double,2>& obj1_pos, double& dist, double& theta)
{

	std::array<double,2> min_dx;	// holds minimum absolute value of position difference vector for each dimension

	// iterate over dimensions
	for (int dimension = 0; dimension < 2; ++dimension)
	{

		min_dx.at(dimension) = obj0_pos.at(dimension) - obj1_pos.at(dimension);

		min_dx.at(dimension) -= std::round(min_dx.at(dimension)/sysparams.length);

	}

	std::array<double,2> zeroArray = {0,0};

	if (min_dx == zeroArray)
	{

		dist = 0; theta = 0; M2S("WTF is goin on");

	} else {

		// calculate center-to-center distance and subtract sum of radii
		dist = sqrt(pow(min_dx.front(),2) + pow(min_dx.back(),2));

		// calculate angle
		theta = atan2(min_dx.at(1), min_dx.at(0));
	}

}