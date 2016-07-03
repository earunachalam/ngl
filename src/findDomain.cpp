#include "Kingdom.h"


#include "Domain.h"
#include "parameters.h"
#include "universal.h"


void Kingdom::findDomain(std::shared_ptr<Sp>& curr_object, std::shared_ptr<Subdomain>& subdomain_cont_curr)
{
	
	// position of current object
	double id_Domain_north, id_Domain_west;									// number of Domain lengths south/east with reSpect to northwest corner
	int id_Domain_invec, round_id_Domain_north, round_id_Domain_west;		// indices of Domain containing this object
	int	round_id_subdomain_north, round_id_subdomain_west;					// indices of Subdomain containing this object
	
	id_Domain_west = (curr_object->x[0] - this->sysparams.min_x) / this->sysparams.Domain_length;
	id_Domain_north = (this->sysparams.max_x - curr_object->x[1]) / this->sysparams.Domain_length;
	
	round_id_Domain_west = static_cast<int>(id_Domain_west);
	round_id_Domain_north = static_cast<int>(id_Domain_north);
	id_Domain_invec = round_id_Domain_north +round_id_Domain_west * 2 * this->sysparams.nBoxes;

	auto currDomain = this->Domains.at(id_Domain_invec);

	round_id_subdomain_west = static_cast<int>(fmod(id_Domain_west, 1) * this->sysparams.subd_per_dlength);
	round_id_subdomain_north = static_cast<int>(fmod(id_Domain_north, 1) * this->sysparams.subd_per_dlength);

	bool corner = ((round_id_subdomain_west == (this->sysparams.subd_per_dlength - 1)) || (round_id_subdomain_west == 0)) &&
		((round_id_subdomain_north == (this->sysparams.subd_per_dlength - 1)) || (round_id_subdomain_north == 0));

	if (round_id_subdomain_north == 0)
	{

		if (round_id_subdomain_west == 0)
		{
			subdomain_cont_curr = currDomain->subdomain_northwest;
		} else if (round_id_subdomain_west == (this->sysparams.subd_per_dlength - 1)){
			subdomain_cont_curr = currDomain->subdomain_northeast;
		} else {
			subdomain_cont_curr = currDomain->subdomains_north.at(round_id_subdomain_west - 1);
		}

	} else if (round_id_subdomain_north == (this->sysparams.subd_per_dlength - 1)){

		if (round_id_subdomain_west == 0){
			subdomain_cont_curr = currDomain->subdomain_southwest;
		} else if (round_id_subdomain_west == (this->sysparams.subd_per_dlength - 1)) {
			subdomain_cont_curr = currDomain->subdomain_southeast;
		} else {
			subdomain_cont_curr = currDomain->subdomains_south.at(round_id_subdomain_west - 1);
		}

	} else if ((round_id_subdomain_west == 0) && !corner){

		subdomain_cont_curr = currDomain->subdomains_west.at(round_id_subdomain_north - 1);

	} else if ((round_id_subdomain_west == (this->sysparams.subd_per_dlength - 1)) && !corner){

		subdomain_cont_curr = currDomain->subdomains_east.at(round_id_subdomain_north - 1);
		
	} else {

		int round_id_subdomain_center = (round_id_subdomain_north - 1) + static_cast<int>(this->sysparams.subd_per_dlength - 2) * (round_id_subdomain_west - 1);
		subdomain_cont_curr = currDomain->subdomains_center.at(round_id_subdomain_center);

	}

}
