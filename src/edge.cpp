#include "distance.h"


#include "parameters.h"
#include "universal.h"

// In a two-dimensional system with periodic boundary conditions, compute the
// Euclidean distance between two objects "0" and "1".

void distance::edge(const parameters& sysparams, const std::array<double,2>& obj0_pos, const std::array<double,2>& obj1_pos, const double& obj0_r, const double& obj1_r, double& dist, double& theta)
{

	// calculate center-to-center distance and subtract sum of radii

	distance::center(sysparams, obj0_pos, obj1_pos, dist, theta);

	dist -= (obj0_r + obj1_r);

}
