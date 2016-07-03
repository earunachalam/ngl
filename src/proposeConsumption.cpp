#include "ConsumptionEvent.h"


#include "distance.h"
#include "Neighbor.h"
#include "universal.h"


void ConsumptionEvent::proposeConsumption(parameters& sysparams, std::shared_ptr<Sp>& curr_pred, std::shared_ptr<Sp>& prey, std::vector<std::shared_ptr<Sp> >& objects_local, std::vector<std::shared_ptr<Neighbor> >& objects_nonlocal, bool& overlap_status)
{

	double curr_dist, curr_theta; // dummy variables required as input to distance calculation function

	for (int i = 0; i < objects_local.size(); ++i)
	{
	
		// do not compare with itself
		if ((objects_local.at(i) == curr_pred) || (objects_local.at(i) == prey))
		{
			continue;
		}

		// calculate distance between pair
		distance::edge(sysparams, curr_pred->x, objects_local.at(i)->x, curr_pred->r, objects_local.at(i)->r, curr_dist, curr_theta);

		// if consumption will cause an overlap with dissimilar Species, reject attempt
		if ((curr_dist < 0) && (objects_local.at(i)->type != curr_pred->type))
		{
			overlap_status = true; return;
		}

	}


	for (int i = 0; i < objects_nonlocal.size(); ++i)
	{

		// calculate distance between pair
		distance::edge(sysparams, curr_pred->x, objects_nonlocal.at(i)->coordinates, curr_pred->r, objects_nonlocal.at(i)->radius, curr_dist, curr_theta);

		// if consumption will cause an overlap with dissimilar Species, reject attempt
		if ((curr_dist < 0) && (objects_nonlocal.at(i)->type != curr_pred->type))
		{
			overlap_status = true; return;
		}

	}

}