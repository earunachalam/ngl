#include "Domain.h"


#include "force.h"
#include "Neighbor.h"
#include "parameters.h"
#include "Subdomain.h"
#include "universal.h"


Domain::Domain(parameters& sysparams, int arg_index, double arg_west, double arg_north){

	this->index = arg_index;

	// get position of current Domain
	this->c = arg_index/sysparams.domains_per_syslength;
	this->r = arg_index % sysparams.domains_per_syslength;
	
	// r,c positions of Neighboring Domains
	this->r_north = (r - 1 + sysparams.domains_per_syslength) % sysparams.domains_per_syslength;
	this->r_south = (r + 1 + sysparams.domains_per_syslength) % sysparams.domains_per_syslength;
	this->c_east = (c + 1 + sysparams.domains_per_syslength) % sysparams.domains_per_syslength;
	this->c_west = (c - 1 + sysparams.domains_per_syslength) % sysparams.domains_per_syslength;
	
	// linear positions of Neighboring Domains
	// cardinal directions
	this->linear_north = r_north + c*sysparams.domains_per_syslength;
	this->linear_south = r_south + c*sysparams.domains_per_syslength;
	this->linear_east = r + c_east*sysparams.domains_per_syslength;
	this->linear_west = r + c_west*sysparams.domains_per_syslength;
	// intercardinal directions
	this->linear_northwest = r_north + c_west*sysparams.domains_per_syslength;
	this->linear_northeast = r_north + c_east*sysparams.domains_per_syslength;
	this->linear_southwest = r_south + c_west*sysparams.domains_per_syslength;
	this->linear_southeast = r_south + c_east*sysparams.domains_per_syslength;

	// coordinates for current Domain boundaries
	this->north = arg_north;
	this->south = arg_north - sysparams.Domain_length;
	this->east = arg_west + sysparams.Domain_length;
	this->west = arg_west;

	// length of sides of Domain (not including corners) in units of subdomains
	int subd_per_dlength_side = sysparams.subd_per_dlength - 2;

	// reserve Space in vectors
	this->subdomains_center.reserve(pow(subd_per_dlength_side, 2));
	this->subdomains_north.reserve(subd_per_dlength_side);
	this->subdomains_south.reserve(subd_per_dlength_side);
	this->subdomains_east.reserve(subd_per_dlength_side);
	this->subdomains_west.reserve(subd_per_dlength_side);

	this->defineSubdomains(sysparams);

	this->Neighbors.reserve(200);
	this->all_objects.reserve(1000);

};


Domain::~Domain()
{
	for (size_t i = 0; i < this->subdomains_center.size(); ++i)
	{
		this->subdomains_center.at(i).reset();
	}

	this->subdomains_center.clear();

	for (size_t i = 0; i < this->subdomains_north.size(); ++i)
	{
		this->subdomains_north.at(i).reset();
	}

	this->subdomains_north.clear();

	for (size_t i = 0; i < this->subdomains_south.size(); ++i)
	{
		this->subdomains_south.at(i).reset();
	}

	this->subdomains_south.clear();

	for (size_t i = 0; i < this->subdomains_east.size(); ++i)
	{
		this->subdomains_east.at(i).reset();
	}

	this->subdomains_east.clear();

	for (size_t i = 0; i < this->subdomains_west.size(); ++i)
	{
		this->subdomains_west.at(i).reset();
	}

	this->subdomains_west.clear();

	this->subdomain_northeast.reset();
	this->subdomain_northwest.reset();
	this->subdomain_southeast.reset();
	this->subdomain_southwest.reset();
}