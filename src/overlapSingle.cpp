#include "distance.h"
#include "parameters.h"
#include "Sp.h"
#include "universal.h"

// compares all members of the vector of objects 'objects' with the current
// object (with index in 'objects' given by 'curridx') to determine if an
// overlap exists

// returns true if an overlap exists, and false if one does not

bool overlapSingle(parameters& sysparams, std::vector<std::shared_ptr<Sp> >& objects, std::shared_ptr<Sp>& curr_obj)
{

	// initialize components of difference vector in polar coordinates
	double dist = std::numeric_limits<double>::quiet_NaN(), theta = std::numeric_limits<double>::quiet_NaN();

	for (int i = 0; i < objects.size(); ++i){
		
		if (objects.at(i) == curr_obj)
		{

			// do not compare current object to itself

			continue;

		}
		
		distance::edge(sysparams, curr_obj->x, objects.at(i)->x, curr_obj->r, objects.at(i)->r, dist, theta);

		if (dist < 0)
		{

			// if sum of objects' radii exceeds interobject distance

			return true;

		}
	}

	return false;

}