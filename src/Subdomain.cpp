#include "Subdomain.h"


#include "parameters.h"
#include "Sp.h"
#include "universal.h"


Subdomain::Subdomain(parameters& sysparams, double arg_west, double arg_north)
{

	this->north = arg_north;
	this->south = arg_north - sysparams.subdomain_length;
	this->east = arg_west + sysparams.subdomain_length;
	this->west = arg_west;

	this->residents.reserve(100);

};

Subdomain::~Subdomain()
{

	for (auto& resident : this->residents)
	{
		resident.reset();
	}

	residents.clear();

};
