#include "force.h"


#include "parameters.h"
#include "universal.h"

void force::ipAttraction(parameters& sysparams, double& dist, double& theta, double& sum_Spring_const, std::array<double,2>& f)
{

	f[0] -= sysparams.att_coeff * sum_Spring_const * dist * cos(theta);
	f[1] -= sysparams.att_coeff * sum_Spring_const * dist * sin(theta);
}