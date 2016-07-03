#ifndef KINGDOM_H
#define KINGDOM_H

#include "ConsumptionEvent.h"
#include "Domain.h"
#include "parameters.h"
#include "Sp.h"
#include "universal.h"

class Kingdom
{

public:

	parameters sysparams;												// simulation parameters

	std::string currDirectory, current_filename;						// create directory to store trajectories

	std::vector<std::shared_ptr<Domain> > Domains;						// vector containing pointers to all Domains in Kingdom

	//std::vector<std::shared_ptr<Sp> > daughters;						// newly created daughter cells to be introduced into system (awaiting Domain assignment)

	//std::vector<std::shared_ptr<ConsumptionEvent> > consumptionEvents;	// container for all proposed consumption events
	
	int oid = 0;														// unique object identifier; count starts at 0

	std::mt19937 rng;													// global RNG

	Kingdom(std::string rootdir, unsigned int thread);

	~Kingdom();

	// create all objects and assign them to the Domain in which they are presently located
	void populate();

	// assign an objects to the Domain in which it is presently located
	void assignDomain(std::shared_ptr<Sp> curr_object);

	void assignDomains(std::vector<std::shared_ptr<Sp> > objects);

	void defineDomains();

	void evict();

	void export_all(std::ofstream& current_file);

	// inline static void export_single(std::ofstream& current_file, std::shared_ptr<Sp> object);

	void findDomain(std::shared_ptr<Sp>& curr_object, std::shared_ptr<Subdomain>& subdomain_cont_curr);

	std::vector<std::shared_ptr<Sp> > initialize_objects();

	// print the coordinates of the northwest corner of every Domain in tke Kingdom
	void printDomains();

	void propagate(bool calculateActive, bool attemptChange);

	void resetTempContainers();

	void trade();

};


#endif
