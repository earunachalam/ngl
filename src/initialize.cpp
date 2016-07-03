#include "Kingdom.h"


#include "overlapSingle.h"
#include "parameters.h"
#include "Sp.h"
#include "universal.h"

// FUNCTION INITIALIZE_OBJECTS
// create objects to populate simulation box

std::vector<std::shared_ptr<Sp> > Kingdom::initialize_objects(){

	// vector containing pointers to all cells in Kingdom
	std::vector<std::shared_ptr<Sp> > objects;

	// initialize variables to hold agent data
	double th, vth, r, m; 								// orientation, angular velocity, radius and mass
	std::array<double,2> x, v;							// position, velocity

	// create distributions for random number generation
	std::uniform_real_distribution<double> urand(0.0, 1.0);
	std::normal_distribution<double> nrand(0.0, 1.0);

	// r = 0.50; x = {0.50050,2.00}; m = sysparams.mpf * pow(r*1e-6,3); std::generate(v.begin(), v.end(), 
	// 	[&]{return nrand(this->rng) * sqrt(sysparams.kbt/m);}); objects.push_back(std::make_shared<Sp>(1, 1, x, v, 0, 0, r));
	// r = 0.50; x = {-0.5005,2.00}; m = sysparams.mpf * pow(r*1e-6,3); std::generate(v.begin(), v.end(), 
	// 	[&]{return nrand(this->rng) * sqrt(sysparams.kbt/m);}); objects.push_back(std::make_shared<Sp>(1, 2, x, v, 0, 0, r));

	for (int i = 0; i < sysparams.nCells_init; ++i){

		// assign radius
		r = sysparams.radius_dist_center + nrand(this->rng)*sysparams.radius_dist_sd;

		// calculate correSponding mass
		m = sysparams.mpf * pow(r*1.00e-6,3);

		// populate position/orientation and velocity/angular velocity arrays
		std::generate(x.begin(), x.end(), [&]{return sysparams.min_x + urand(this->rng)*sysparams.length;});
		std::generate(v.begin(), v.end(), [&]{return nrand(this->rng) * sqrt(sysparams.kbt/m);});

		th = urand(this->rng)*2*M_PI;
		vth = nrand(this->rng)*sqrt(sysparams.kbt/m)/(r*1.00e-6);

		// create new Sp object
		objects.push_back(std::make_shared<Sp>(1 + rand()%2, ++(this->oid), x, v, th, vth, r));

		// ensure that no overlap with existing objects occurs
		while(overlapSingle(sysparams, objects, objects.back())){

			std::generate(x.begin(), x.end(), [&]{return sysparams.min_x + urand(this->rng)*sysparams.length;});
			objects.back()->x = x;

		}
	}

	// update count to reflect the last identifier used
	this->oid = objects.size();

	return objects;
	
}