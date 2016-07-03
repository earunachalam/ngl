#include "ConsumptionEvent.h"

#include "Domain.h"
#include "universal.h"


ConsumptionEvent::ConsumptionEvent(int current_Domain, std::shared_ptr<Sp>& arg_prey, std::vector<std::shared_ptr<Sp> >& arg_predators)
{

	this->location = current_Domain;

	this->prey = arg_prey;
	this->prey_energy = pow(arg_prey->r,3);

	this->predators = arg_predators;


	this->predators_energy.resize(this->predators.size(),0);

	double predators_energy_curr, predators_energy_total = 0;

	for (int i = 0; i < this->predators.size(); ++i)
	{
		predators_energy_curr = pow(arg_predators.at(i)->r,3);
		this->predators_energy.at(i) = predators_energy_curr;
		predators_energy_total += predators_energy_curr;
	}

	this->energy_ratio_init = predators_energy_total/this->prey_energy;

}