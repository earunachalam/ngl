#ifndef FORCE_H
#define FORCE_H

#include "parameters.h"
#include "universal.h"


namespace force
{

	void ipAttraction(parameters& sysparams, double& dist, double& theta, double& sum_Spring_const, std::array<double,2>& f);

	void ipRepulsion(parameters& sysparams, double& dist, double& theta, std::array<double,2>& f);

};

#endif
