#ifndef NEIGHBOR_H
#define NEIGHBOR_H

#include "Sp.h"
#include "universal.h"

class Neighbor
{

public:

	// properties
	std::shared_ptr<Sp> address;
	int id, type;
	std::array<double,2> coordinates;
	double radius;
	double Spring_const;

	Neighbor(std::shared_ptr<Sp> arg_address);

	~Neighbor();

};

#endif
