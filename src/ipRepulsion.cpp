#include "force.h"


#include "parameters.h"
#include "universal.h"

void force::ipRepulsion(parameters& sysparams, double& dist, double& theta, std::array<double,2>& f)
{
	f[0] += sysparams.rep_coeff*exp(-1.00 * std::fabs(dist)) * cos(theta);
	f[1] += sysparams.rep_coeff*exp(-1.00 * std::fabs(dist)) * sin(theta);
}