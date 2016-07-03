#include "Neighbor.h"


#include "Sp.h"
#include "universal.h"

// constructor
Neighbor::Neighbor(std::shared_ptr<Sp> arg_address)
{

	this->address = arg_address;
	this->id = arg_address->id;
	this->type = arg_address->type;
	this->coordinates = arg_address->x;
	this->radius = arg_address->r;
	this->Spring_const = arg_address->spNetwork->nodeValue.at(4);

};


// destructor
Neighbor::~Neighbor(){};
