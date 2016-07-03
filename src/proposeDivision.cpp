#include "Domain.h"


#include "distance.h"
#include "universal.h"


void Domain::proposeDivision(parameters& sysparams, int daughter_type, std::array<double,2>& daughter_x, double& daughter_r, int& index_parent, double& linear_distance_sum, bool& overlapstatus)
{

	// to hold running totals of other cells' linear distances to current cell
	std::array<double,2> ld = {{0,0}};

	double curr_dist, curr_theta;

	// loop over all LOCAL "origins" for linear distances (all objects owned by current Domain)
	for (int origin = 0; origin < this->all_objects.size(); ++origin)
	{

		// do not consider parent cell
		if (origin == index_parent)
		{
			continue;
		}

		// calculate distance between pair
		distance::edge(sysparams, daughter_x, this->all_objects.at(origin)->x, daughter_r, this->all_objects.at(origin)->r, curr_dist, curr_theta);

		// if division will cause an overlap, reject attempt
		if (curr_dist < 0)
		{
			overlapstatus = true; return;
		}

		if ((curr_dist < sysparams.subdomain_length) && (this->all_objects.at(origin)->type == daughter_type))
		{
			ld[0] += curr_dist*cos(curr_theta);
			ld[1] += curr_dist*sin(curr_theta);
		}

	}

	// loop over all NONLOCAL "origins" for linear distances (all objects owned by current Domain)
	for (int origin = 0; origin < this->Neighbors.size(); ++origin)
	{

		// calculate distance between pair
		distance::edge(sysparams, daughter_x, this->Neighbors.at(origin)->coordinates, daughter_r, this->Neighbors.at(origin)->radius, curr_dist, curr_theta);

		// if division will cause an overlap, reject attempt
		if (curr_dist < 0)
		{
			overlapstatus = true; return;
		}

		if ((curr_dist < sysparams.subdomain_length) && (this->Neighbors.at(origin)->type == daughter_type))
		{
			ld[0] += curr_dist*cos(curr_theta);
			ld[1] += curr_dist*sin(curr_theta);
		}

	}

	linear_distance_sum += sqrt(pow(ld.front(),2) + pow(ld.back(),2));

}