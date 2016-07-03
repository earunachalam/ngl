#ifndef CONSUMPTION_EVENT_H
#define CONSUMPTION_EVENT_H

#include "Neighbor.h"
#include "parameters.h"
#include "Sp.h"
#include "universal.h"

class Domain;											// forward declaration (circular reference)

class Kingdom;											// forward declaration (circular reference)

class ConsumptionEvent
{

public:

	int location;										/*!< index of Domain in which consumption event may take place*/

	std::shared_ptr<Sp> prey;							/*!< object which may be consumed in the event*/
	double prey_energy;									/*!< energy of object which may be consumed in the event*/
	double energy_ratio_init;							/*!< predator(s)-to-prey energy ratio before any consumption has occurred, i.e. assuming all potential predators are available to participate in THIS event (used for ranking priority of events)*/

	std::vector<std::shared_ptr<Sp> > predators;		/*!< objects which may prey on another object during the event*/
	std::vector<double> predators_energy;				/*!< energies of objects which may prey on another object during the event*/
	std::vector<double> predators_orig_radius;			/*!< contains original radii of potential predators participating in consumption event */
	std::vector<double> predators_orig_x0;				/*!< contains original x-component of position of potential predators participating in consumption event */
	std::vector<double> predators_orig_x1;				/*!< contains original y-component of position of potential predators participating in consumption event */

	// bool operator< (const std::shared_ptr<ConsumptionEvent>& other) const {
	// 	P2S(this->energy_ratio_init); P2S(other->energy_ratio_init);
	// 	P2S(this->energy_ratio_init < other->energy_ratio_init);
	// 	return (this->energy_ratio_init < other->energy_ratio_init);
	// }

	// constructor
	ConsumptionEvent(int current_Domain, std::shared_ptr<Sp>& arg_prey, std::vector<std::shared_ptr<Sp> >& arg_predators);

	// consumption attempt assessment and execution
	void processEvent(Kingdom* system, std::vector<std::shared_ptr<Sp> >& carcasses);

	// determine whether changing the position and radius of a predator during a consumption event causes overlap with existing cells
	void proposeConsumption(parameters& sysparams, std::shared_ptr<Sp>& curr_object, std::shared_ptr<Sp>& prey, std::vector<std::shared_ptr<Sp> >& objects_local, std::vector<std::shared_ptr<Neighbor> >& objects_nonlocal, bool& overlap_status);

};

#endif