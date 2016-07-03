#include "distance.h"

#include "universal.h"


void distance::wrap(const parameters& sysparams, double& value)
{
	value -= (sysparams.length*std::trunc(value / sysparams.max_x));
}