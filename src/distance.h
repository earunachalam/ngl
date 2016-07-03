#ifndef DISTANCE_H
#define DISTANCE_H

#include "parameters.h"
#include "universal.h"


namespace distance
{

	void edge(const parameters& sysparams, const std::array<double,2>& obj0_pos, const std::array<double,2>& obj1_pos, const double& obj0_r, const double& obj1_r, double& dist, double& theta);
	
	void center(const parameters& sysparams, const std::array<double,2>& obj0_pos, const std::array<double,2>& obj1_pos, double& dist, double& theta);

	void wrap(const parameters& sysparams, double& value);

};



#endif