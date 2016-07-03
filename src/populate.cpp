#include "Kingdom.h"


#include "Domain.h"
#include "Sp.h"
#include "universal.h"

void Kingdom::populate(){

	// vector containing pointers to all cells in Kingdom
	std::vector<std::shared_ptr<Sp> > objects = initialize_objects();
	
	// assign each created object to the Domain in which it is located
	this->assignDomains(objects);

}