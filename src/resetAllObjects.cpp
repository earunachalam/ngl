#include "Domain.h"

#include "Sp.h"


void Domain::resetAllObjects()
{
	for (size_t i = 0; i < this->all_objects.size(); ++i)
	{
		this->all_objects.at(i)->available = true;
	}

}
