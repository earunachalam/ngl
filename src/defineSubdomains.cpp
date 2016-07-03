#include "Domain.h"


#include "Neighbor.h"
#include "parameters.h"
#include "Subdomain.h"
#include "universal.h"


void Domain::defineSubdomains(parameters& sysparams){

	// declare
	double west_subd, north_subd;

	// assign northwest corner for each Subdomain and assign to appropriate container
	for (int i = 0; i < sysparams.subd_per_dlength; ++i){ // longitude

		for (int j = 0; j < sysparams.subd_per_dlength; ++j){ // latitude
		
			// assign northwest corner coordinates for current Subdomain
			west_subd = this->west + (i*sysparams.subdomain_length);
			north_subd = this->north - (j*sysparams.subdomain_length);
			
			// true if the Subdomain is located at a corner of the Domain
			bool corner = ((i == 0) || (i == (sysparams.subd_per_dlength - 1))) && 
				((j == 0)  || (j == (sysparams.subd_per_dlength - 1)));

			// place in appropriate container; note that the corners appear
			// ONLY in the corner variables, and not in the cardinal direction
			// containers

			if (j == 0){

				if (i == 0){
					this->subdomain_northwest = std::make_shared<Subdomain>(sysparams, west_subd, north_subd);
				} else if (i == (sysparams.subd_per_dlength - 1)) {
					this->subdomain_northeast = std::make_shared<Subdomain>(sysparams, west_subd, north_subd);
				} else {
					this->subdomains_north.push_back(std::make_shared<Subdomain>(sysparams, west_subd, north_subd));
				}

			} else if (j == (sysparams.subd_per_dlength - 1)){

				if (i == 0){
					this->subdomain_southwest = std::make_shared<Subdomain>(sysparams, west_subd, north_subd);
				} else if (i == (sysparams.subd_per_dlength - 1)) {
					this->subdomain_southeast = std::make_shared<Subdomain>(sysparams, west_subd, north_subd);
				} else {
					this->subdomains_south.push_back(std::make_shared<Subdomain>(sysparams, west_subd, north_subd));
				}

			} else if ((i == 0) && !corner){

				this->subdomains_west.push_back(std::make_shared<Subdomain>(sysparams, west_subd, north_subd));

			} else if ((i == (sysparams.subd_per_dlength - 1)) && !corner){

				this->subdomains_east.push_back(std::make_shared<Subdomain>(sysparams, west_subd, north_subd));
				
			} else {

				this->subdomains_center.push_back(std::make_shared<Subdomain>(sysparams, west_subd, north_subd));

			}
		}
	}
};
