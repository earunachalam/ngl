#ifndef SUBDOMAIN_H
#define SUBDOMAIN_H

#include "parameters.h"
#include "Sp.h"
#include "universal.h"

class Subdomain
{

	public:

		// properties

		double west, north; 									// coordinates of northwest corner
		double east, south;										// coordinates of southeast corner
		std::vector<std::shared_ptr<Sp> > residents;			// pointers to cells within Subdomain

		// constructor

		Subdomain(parameters& sysparams, double arg_west, double arg_north);

		// destructor

		~Subdomain();


		// returns true if the resident with index indexResident is out of bounds in any direction

		bool outOfBounds(int& indexResident);
};


#endif