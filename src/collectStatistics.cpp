#include "Domain.h"


#include "Network.h"
#include "parameters.h"
#include "Sp.h"
#include "universal.h"


void Domain::collectStatistics(const parameters& sysparams)
{
	this->nodeCountsConnMod.clear();
	this->nodeCountsTuning.clear();

	for (auto& object : this->all_objects)
	{
		if (object->spNetwork->existenceTime > 2*(sysparams.t_mix))
		{
			if (object->spNetwork->existenceTime > 10*(sysparams.t_mix))
			{
				this->getObjectNodeCount(this->nodeCountsConnMod, object);

			} else {

				this->getObjectNodeCount(this->nodeCountsTuning, object);

			}
		}
	}
}