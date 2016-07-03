#include "Kingdom.h"


#include "Domain.h"
#include "parameters.h"
#include "universal.h"

// in each quadrant of the x-y plane, create a set of square Domains that
// Spans a Space of nBoxes by nBoxes and populate these Domains with
// subdomains

void Kingdom::defineDomains()
{

	// reserve Space for all Domains
	this->Domains.reserve((2 * sysparams.nBoxes) * (2 * sysparams.nBoxes));

	// declare coordinates for northwest corner of Domain (i.e. the northwest
	// corner of the most northwesterly Subdomain within said Domain)
	double west_coord, north_coord;
	int curr_Domain_index;

	// assign northwest corner to each Domain
	for (int i = 0; i < (2*sysparams.nBoxes); ++i){

		west_coord = sysparams.min_x + (i*sysparams.Domain_length);

		for (int j = 0; j < (2*sysparams.nBoxes); ++j){
		
			north_coord = sysparams.max_x - (j*sysparams.Domain_length);

			// assign northwest corner coordinates for current Domain
			curr_Domain_index = j + i*2*sysparams.nBoxes;
			this->Domains.push_back(std::make_shared<Domain>(sysparams, curr_Domain_index, west_coord, north_coord));
			
		}
	}
}