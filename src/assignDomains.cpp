#include "Kingdom.h"


#include "Domain.h"
#include "Sp.h"
#include "universal.h"


void Kingdom::assignDomains(std::vector<std::shared_ptr<Sp> > objects){
	
	// assign each object to the Subdomain in which it is located
	for (int i = 0; i < objects.size(); ++i){
		
		this->assignDomain(objects.at(i));

	}

}