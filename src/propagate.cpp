#include "Kingdom.h"


#include "ConsumptionEvent.h"
#include "Domain.h"
#include "universal.h"


void Kingdom::propagate(bool calculateActive, bool attemptChange)
{

	// ADVANCE POSITIONS  //////////////////////////////////////////////////////////////////////////////////

    for (int i = 0; i < this->Domains.size(); ++i)
	{
		auto currDomain = this->Domains.at(i);
		currDomain->interparticle(this->sysparams, calculateActive);
		currDomain->updatePositions(this->sysparams, this->rng);
	}

	// move objects outside the bounds of their assigned domain to the domain in which they currently reside
	this->evict();

    // exchange information about objects located in Neighboring subdomains
    // (populate Neighbor list vector for each Domain)
    this->trade();


    // INTERSPECIES INTERACTIONS //////////////////////////////////////////////////////////////////////////

    // create vectors to hold data for division and consumption events (prepare for new round)
    std::vector<std::shared_ptr<Sp> > daughters;
    std::vector<std::shared_ptr<ConsumptionEvent> > consumptionEvents;
    std::vector< std::shared_ptr<Sp> > carcasses;

    for (int i = 0; i < this->Domains.size(); ++i)
	{
		auto currDomain = this->Domains.at(i);

	    std::vector<std::shared_ptr<Sp> > Domain_daughters;
	    std::vector<std::shared_ptr<ConsumptionEvent> > Domain_consumptionEvents;

		// update vector containing pointer to all objects in Domain
		currDomain->collectAllObjects(this->sysparams);
		
		// reset all objects' availability status to make them eligible to
		// participate in consumption and division events
		currDomain->resetAllObjects();

		// carry out division of all objects with energy exceeding threshold
		currDomain->divide(this->sysparams, this->oid, Domain_daughters);

		// create consumption events
		currDomain->createConsumptionEvents(this->sysparams, Domain_consumptionEvents);

		// #pragma omp critical
		{
			auto it_d = std::end(daughters);
			daughters.insert(it_d,Domain_daughters.begin(),Domain_daughters.end());

			auto it_ce = std::end(consumptionEvents);
			consumptionEvents.insert(it_ce,Domain_consumptionEvents.begin(),Domain_consumptionEvents.end());
		}

	}

	// assign newly Spawned daughter cells to Domains, then delete
	this->assignDomains(daughters);
	for (auto& daughter : daughters){ daughter.reset(); } daughters.clear();

	// collect all proposed consumption events, then order them by initial predator(s)-to-prey energy ratio
	std::sort(consumptionEvents.begin(), consumptionEvents.end(),
		[](std::shared_ptr<ConsumptionEvent> a, std::shared_ptr<ConsumptionEvent> b)
		{
        	return ((b->energy_ratio_init) < (a->energy_ratio_init));
    	});

	// evaluate all proposed consumption events, then delete
	for (auto& event : consumptionEvents)
	{
		event->processEvent(this, carcasses);
		event.reset();
	}

	consumptionEvents.clear();

	for (auto& carcass : carcasses){ carcass.reset(); }	carcasses.clear();

    for (int i = 0; i < this->Domains.size(); ++i)
	{
		auto currDomain = this->Domains.at(i);
    	currDomain->cleanup(this);
    }


    // UPDATE DOMAIN ASSIGNMENTS ////////////////////////////////////////////////////////////////////////

	// exchange information about objects located in Neighboring subdomains
    // (populate Neighbor list vector for each Domain)

    for (int i = 0; i < this->Domains.size(); ++i)
	{
		auto currDomain = this->Domains.at(i);
    	currDomain->collectAllObjects(this->sysparams);

    	if (attemptChange)
    	{
    		currDomain->collectStatistics(this->sysparams);
    		// currDomain->attemptMutation(this->rng);
    	}
    }
    
    this->trade();

}