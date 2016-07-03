#include "Domain.h"


#include "ConsumptionEvent.h"
#include "distance.h"
#include "universal.h"

/*! \brief Examines overlaps in system to create a list of potential consumption events
 *
 *  Identifies overlaps within Domain, considering both local objects and nonlocal objects (objects in Neighboring subdomains). 
 *	All overlaps lead to the proposal of a consumption event, each of which has a prey object and a list of predator objects. 
 *	The valifdity of the proposals is not considered by this function.
 */

void Domain::createConsumptionEvents(const parameters& sysparams, std::vector<std::shared_ptr<ConsumptionEvent> >& consumptionEvents)
{

	// vectors to hold distances and angles for difference vectors between pairs of local objects
	std::vector<double> dist_local(this->all_objects.size() * this->all_objects.size());
	std::fill(dist_local.begin(), dist_local.end(), std::numeric_limits<double>::max());

	// vectors to hold distances and angles for difference vectors between pairs of nonlocal objects
	std::vector<double> dist_nonlocal(this->Neighbors.size() * this->all_objects.size());
	std::fill(dist_nonlocal.begin(), dist_nonlocal.end(), std::numeric_limits<double>::max());

	std::vector<std::shared_ptr<Sp> > curr_predators;

	double curr_dist, curr_theta, curr_pair_index;

	// loop over all "prey" for forces (all objects owned by current Domain)
	for (int prey = 0; prey < this->all_objects.size(); ++prey)
	{
		curr_predators.clear(); 

		// loop over all LOCAL "preds" for forces (all objects owned by current Domain)
		for (int pred = 0; pred < this->all_objects.size(); ++pred)
		{

			// if pred and prey objects have a different chemical identity, interparticle force is 0
			if ((this->all_objects.at(prey)->type) == (this->all_objects.at(pred)->type))
			{

				continue;

			// if pred and prey objects have the same chemical identity, interaction is possible
			} else {

				// calculate distance between pair
				distance::edge(sysparams,
					this->all_objects.at(prey)->x, this->all_objects.at(pred)->x,
					this->all_objects.at(prey)->r, this->all_objects.at(pred)->r,
					curr_dist, curr_theta);

				// get index (within result vectors dist_local and theta_local) of the pair of interest
				curr_pair_index = pred + prey*this->all_objects.size();
				dist_local.at(curr_pair_index) = curr_dist;

				// assign force to prey object

				// if objects are close together, repulsive forces will dominate to enforce excluded volume of cells
				// exponentially decaying force used
				if (curr_dist < 0)
				{
					curr_predators.push_back(this->all_objects.at(pred));
				}

			}
		}

		// loop over all NONLOCAL "preds" for forces (all objects owned by current Domain)
		for (int pred = 0; pred < this->Neighbors.size(); ++pred)
		{

			// if pred and prey objects have a different chemical identity, interparticle force is 0
			if ((this->all_objects.at(prey)->type) == (this->Neighbors.at(pred)->type))
			{

				continue;

			// if pred and prey objects have the same chemical identity, interaction is possible
			} else {

				// calculate distance between pair
				distance::edge(sysparams,
					this->all_objects.at(prey)->x, this->Neighbors.at(pred)->coordinates,
					this->all_objects.at(prey)->r, this->Neighbors.at(pred)->radius,
					curr_dist, curr_theta);

				// get index (within result vectors dist_nonlocal and theta_nonlocal) of the pair of interest
				curr_pair_index = pred + prey*this->Neighbors.size();
				dist_nonlocal.at(curr_pair_index) = curr_dist;

				// assign force to prey object

				// if objects are close together, repulsive forces will dominate to enforce excluded volume of cells
				// exponentially decaying force used
				if (curr_dist < 0)
				{
					curr_predators.push_back(this->Neighbors.at(pred)->address);
				}
			}
		}

		if (!curr_predators.empty())
		{
			consumptionEvents.push_back(std::make_shared<ConsumptionEvent>(this->index, this->all_objects.at(prey), curr_predators));
		}
	}
}