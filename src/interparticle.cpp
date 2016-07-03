#include "Domain.h"


#include "distance.h"
#include "force.h"
#include "universal.h"

/*! \brief Calculates interparticle forces between all objects within Domain and Neighboring subdomains
 *
 *  Calculates pairwise forces between objects, considering each pair only once. Only forces acting on
 *  objects within the current Domain are considered. Information about objects in Neighboring subdomains
 *  is used only to determine their contribution to the field affecting the objects within the current
 *  Domain. ReSponsibility for these Neighbor objects falls to their reSpective Domains.
 */

void Domain::interparticle(parameters& sysparams, bool calculateActive)
{

	for (auto& object : this->all_objects)
	{
		object->sumSurfArea = 0;
		object->ip_force = {0,0};
		
		if (calculateActive)
		{
			object->sig_self_prev = object->sig_self;
			object->sig_self = 0;
			object->sig_nonself_prev = object->sig_nonself;
			object->sig_nonself = 0;
		}
	}

	double curr_dist, curr_theta, curr_pair_index;

	// loop over all "destinations" for forces (all objects owned by current Domain)
	for (int destination = 0; destination < this->all_objects.size(); ++destination)
	{

		// loop over all LOCAL "origins" for forces (all objects owned by current Domain)
		for (int origin = 0; origin < destination; ++origin)
		{

			// if origin and destination objects have a different chemical identity, interparticle force is 0
			if ((this->all_objects.at(destination)->type) != (this->all_objects.at(origin)->type))
			{

				if (curr_dist < (sysparams.sig_threshold*sysparams.interaction_length))
				{
					if (calculateActive)
					{
						this->all_objects.at(destination)->sig_nonself += exp(-1.00*pow(curr_dist,2));
						this->all_objects.at(origin)->sig_nonself += exp(-1.00*pow(curr_dist,2));
					}

					this->all_objects.at(destination)->sumSurfArea += pow(this->all_objects.at(origin)->r,2);
					this->all_objects.at(origin)->sumSurfArea += pow(this->all_objects.at(destination)->r,2);
				}

				continue;

			// if origin and destination objects have the same chemical identity, interaction is possible
			} else {

				// calculate distance between pair
				distance::edge(sysparams, this->all_objects.at(destination)->x, this->all_objects.at(origin)->x, this->all_objects.at(destination)->r, this->all_objects.at(origin)->r, curr_dist, curr_theta);

				// assign force to destination object
				std::array<double,2> curr_force = {0,0};

				// if objects are close together, repulsive forces will dominate to enforce excluded volume of cells
				// exponentially decaying force used
				if (curr_dist < 5*sysparams.interaction_length)
				{
				
					force::ipRepulsion(sysparams, curr_dist, curr_theta, curr_force);

				// if objects are slightly further apart, but still close enough to interact, then adhesion molecules may cause attraction
				// adhesion is modeled as a Hooke's law interaction
				} else if (curr_dist < (10*sysparams.interaction_length)) {

					// sum Spring constants (dependent on network-set adhesion molecule production levels)
					double sum_Spring_const = (this->all_objects.at(destination)->spNetwork->nodeValue.at(4)) + (this->all_objects.at(origin)->spNetwork->nodeValue.at(4));
					
					force::ipAttraction(sysparams, curr_dist, curr_theta, sum_Spring_const, curr_force);

				}


				if (curr_dist < (sysparams.sig_threshold*sysparams.interaction_length))
				{
					if (calculateActive)
					{
						this->all_objects.at(destination)->sig_self += exp(-1.00*pow(curr_dist,2));
						this->all_objects.at(origin)->sig_self += exp(-1.00*pow(curr_dist,2));
					}

					this->all_objects.at(destination)->sumSurfArea += pow(this->all_objects.at(origin)->r,2);
					this->all_objects.at(origin)->sumSurfArea += pow(this->all_objects.at(destination)->r,2);
				}

				this->all_objects.at(destination)->ip_force[0] += curr_force[0];
				this->all_objects.at(destination)->ip_force[1] += curr_force[1];

				// assign opposite force to origin object
				this->all_objects.at(origin)->ip_force[0] -= curr_force[0];
				this->all_objects.at(origin)->ip_force[1] -= curr_force[1];

			}
		}

		// loop over all NONLOCAL "origins" for forces (all objects owned by current Domain)
		for (int origin = 0; origin < this->Neighbors.size(); ++origin)
		{

			// if origin and destination objects have a different chemical identity, interparticle force is 0
			if ((this->all_objects.at(destination)->type) != (this->Neighbors.at(origin)->type))
			{

				if (curr_dist < (sysparams.sig_threshold*sysparams.interaction_length))
				{
					if (calculateActive)
					{
						this->all_objects.at(destination)->sig_nonself += exp(-1.00*pow(curr_dist,2));
					}

					this->all_objects.at(destination)->sumSurfArea += pow(this->Neighbors.at(origin)->radius,2);
				}

				continue;

			// if origin and destination objects have the same chemical identity, interaction is possible
			} else {

				std::array<double,2> curr_force = {0,0};

				// calculate distance between pair
				distance::edge(sysparams,
					this->all_objects.at(destination)->x, this->Neighbors.at(origin)->coordinates,
					this->all_objects.at(destination)->r, this->Neighbors.at(origin)->radius,
					curr_dist, curr_theta);

				// assign force to destination object

				// if objects are close together, repulsive forces will dominate to enforce excluded volume of cells
				// exponentially decaying force used
				if (curr_dist < sysparams.interaction_length)
				{
				
					force::ipRepulsion(sysparams, curr_dist, curr_theta, curr_force);			

				// if objects are slightly further apart, but still close enough to interact, then adhesion molecules may cause attraction
				// adhesion is modeled as a Hooke's law interaction
				} else if (curr_dist < (5 * sysparams.interaction_length)) {

					// sum Spring constants (dependent on network-set adhesion molecule production levels)
					double sum_Spring_const = (this->all_objects.at(destination)->spNetwork->nodeValue.at(4)) + (this->Neighbors.at(origin)->Spring_const);

					force::ipAttraction(sysparams, curr_dist, curr_theta, sum_Spring_const, curr_force);

				}


				if (curr_dist < (sysparams.sig_threshold*sysparams.interaction_length))
				{
					if (calculateActive)
					{
						this->all_objects.at(destination)->sig_self += exp(-1.00*pow(curr_dist,2));
					}

					this->all_objects.at(destination)->sumSurfArea += pow(this->Neighbors.at(origin)->radius,2);
				}

				this->all_objects.at(destination)->ip_force[0] += curr_force[0];
				this->all_objects.at(destination)->ip_force[1] += curr_force[1];

			}
		}
	}

	for (auto& object : this->all_objects)
	{
		object->setActiveForce(sysparams);
	}
}