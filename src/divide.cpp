#include "Domain.h"


#include "force.h"
#include "universal.h"


/*! \brief Handles division of objects in Domain which exceed the energy threshold for binary fission.
 *
 *  Chooses uniformly Spaced angles at which daughter cell may bud and checks to see whether
 *  any of these options cause overlap with existing cells. The angle which results in no
 *  no overlap and minimizes repulsive interparticle forces is selected for budding.
 */

void Domain::divide(parameters& sysparams, int& oid, std::vector<std::shared_ptr<Sp> >& daughters)
{

	double trial_r;							// energy of each daughter cell, should division occur
	double trial_angle;						// angle of division being tested
	double force_sum;						// sum of forces acting on the daughter cells at a given angle of division
	double angle_min_force;					// angle of division resulting in minimum net force acting on daughter cells
	double min_force;						// minimum (sum of) forces acting on cells at this angle
	double offset_x;						// offset in x direction (from center of parent cell to center of a daughter cell)
	double offset_y;						// offset in y direction (from center of parent cell to center of a daughter cell)
	std::array<double,2> trial_pos_1;		// position of first daughter cell at given angle of division
	std::array<double,2> trial_pos_2;		// position of second daughter cell at given angle of division
	std::array<double,2> pos_1_min_force;	// position of first daughter cell (replacing parent) given division at angle of minimum force
	std::array<double,2> pos_2_min_force;	// position of second daughter cell (newly added) given division at angle of minimum force
	bool overlapstatus = false;				// current angle being tested does (true) or does not (false) cause daughter cell(s) to overlap with existing cells
	bool possible = false; 					// at least one angle possible, initialize with false

	// check all objects in Domain
	for (int i = 0; i < this->all_objects.size(); ++i)
	{
		
		// if radius of current object exceeds threshold for division
		if (this->all_objects.at(i)->r > sysparams.radius_division_threshold)
		{

			// calculate new radius of parent (= radius of daughter)
			trial_r = cbrt(0.5) * this->all_objects.at(i)->r;


			angle_min_force = std::numeric_limits<double>::quiet_NaN();
			min_force = std::numeric_limits<double>::max();

			for (int trial = 0; trial < 10; ++trial)
			{

				// calculate angle from trial number (2 * pi * trial number/total number of trials)
				trial_angle = trial * 0.1 * M_PI;

				// set coordinates of trial center for daughter cells
				offset_x = trial_r * cos(trial_angle);
				offset_y = trial_r * sin(trial_angle);

				trial_pos_1 = this->all_objects.at(i)->x;
				trial_pos_1[0] += offset_x;
				trial_pos_1[1] += offset_y;
		        trial_pos_1[0] -= (sysparams.length*static_cast<double>(static_cast<int>(trial_pos_1[0] / sysparams.max_x)));
		        trial_pos_1[1] -= (sysparams.length*static_cast<double>(static_cast<int>(trial_pos_1[1] / sysparams.max_x)));
				
				trial_pos_2 = this->all_objects.at(i)->x;
				trial_pos_2[0] -= offset_x;
				trial_pos_2[1] -= offset_y;
		        trial_pos_2[0] -= (sysparams.length*static_cast<double>(static_cast<int>(trial_pos_2[0] / sysparams.max_x)));
		        trial_pos_2[1] -= (sysparams.length*static_cast<double>(static_cast<int>(trial_pos_2[1] / sysparams.max_x)));

				overlapstatus = false; 				// true if overlap is present, initialize with false
				force_sum = 0; 						// sum of forces on trial daughter cell

				proposeDivision(sysparams, this->all_objects.at(i)->gettype(), trial_pos_1, trial_r, i, force_sum, overlapstatus);
				proposeDivision(sysparams, this->all_objects.at(i)->gettype(), trial_pos_2, trial_r, i, force_sum, overlapstatus);

				// if division at this angle causes an overlap, reject angle and proceed to next angle
				if (overlapstatus)
				{

					continue;

				// if division at this angle does not cause an overlap, record force if it is the lowest calculated thus far
				} else {

					possible = true;

					if (force_sum < min_force)
					{
						min_force = force_sum;
						angle_min_force = trial_angle;
						pos_1_min_force = trial_pos_1;
						pos_2_min_force = trial_pos_2;
						
					}
				}
			}

			// if any of the tested angles resulted in no overlap
			if (possible == true)
			{

				// reset for next object to be tested
				possible = false;

				// adjust parent cell to create first daughter cell
				this->all_objects.at(i)->r = trial_r;
				this->all_objects.at(i)->x = pos_1_min_force;
				this->all_objects.at(i)->available = false;

				// add second daughter cell to vector of pointers to new daughter cells
				daughters.push_back(std::make_shared<Sp>(*(this->all_objects.at(i)), ++oid));
				daughters.back()->x = pos_2_min_force;
				if (std::fabs(daughters.back()->f[0]) > 1.00e-5){TRAP;}

			}
		}
	}
}