#include "Kingdom.h"


#include "Domain.h"
#include "parameters.h"
#include "Sp.h"
#include "universal.h"



// assign object whose pointer is located at the element of vector this->objects (with index index_curr_obj) to the Domain in which it is located

void Kingdom::assignDomain(std::shared_ptr<Sp> curr_object)
{

	std::shared_ptr<Subdomain> subdomain_cont_curr;						// initialize pointer to Subdomain containing current object
	this->findDomain(curr_object, subdomain_cont_curr);				// identify Subdomain containing current object
	subdomain_cont_curr->residents.push_back(curr_object);				// add object to Subdomain

}