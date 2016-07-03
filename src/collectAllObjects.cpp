#include "Domain.h"

#include "parameters.h"
#include "Subdomain.h"
#include "universal.h"

void Domain::collectAllObjects(parameters& sysparams){

	// clear vector from previous round
	this->all_objects.clear();

	// collect all objects in center subdomains
	for (int i = 0; i < pow(sysparams.subd_per_dlength_side, 2); ++i){
		this->all_objects.insert(this->all_objects.end(), this->subdomains_center.at(i)->residents.begin(), this->subdomains_center.at(i)->residents.end());
	}

	// collect all objects in cardinal subdomains
	for (int i = 0; i < sysparams.subd_per_dlength_side; ++i){
		this->all_objects.insert(this->all_objects.end(), this->subdomains_north.at(i)->residents.begin(), this->subdomains_north.at(i)->residents.end());
		this->all_objects.insert(this->all_objects.end(), this->subdomains_south.at(i)->residents.begin(), this->subdomains_south.at(i)->residents.end());
		this->all_objects.insert(this->all_objects.end(), this->subdomains_east.at(i)->residents.begin(), this->subdomains_east.at(i)->residents.end());
		this->all_objects.insert(this->all_objects.end(), this->subdomains_west.at(i)->residents.begin(), this->subdomains_west.at(i)->residents.end());
	}

	// collect all objects in intercardinal subdomains
	this->all_objects.insert(this->all_objects.end(), this->subdomain_northeast->residents.begin(), this->subdomain_northeast->residents.end());
	this->all_objects.insert(this->all_objects.end(), this->subdomain_northwest->residents.begin(), this->subdomain_northwest->residents.end());
	this->all_objects.insert(this->all_objects.end(), this->subdomain_southeast->residents.begin(), this->subdomain_southeast->residents.end());
	this->all_objects.insert(this->all_objects.end(), this->subdomain_southwest->residents.begin(), this->subdomain_southwest->residents.end());

}