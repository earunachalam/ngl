#ifndef DOMAIN_H
#define DOMAIN_H

#include "ConsumptionEvent.h"
#include "Neighbor.h"
#include "parameters.h"
#include "Subdomain.h"
#include "universal.h"

class Kingdom;											// forward declaration (circular reference)

class Domain
{

public:

	int index;																	/*!< index of Domain within Kingdom */
	
	// global position (row and column) of current Domain
	
	int r;
	int c;
	
	int r_north;
	int r_south;
	int c_east;
	int c_west;
	
	// global positions (row and column; linear) of Neighboring Domains

	int linear_north;
	int linear_south;
	int linear_east;
	int linear_west;

	int linear_northeast;
	int linear_northwest;
	int linear_southeast;
	int linear_southwest;
	
	double north;																/*!< latitude of northern boundary */
	double south;																/*!< latitude of southern boundary */
	double east;																/*!< longitude of eastern boundary */
	double west;																/*!< longitude of western boundary */

	std::vector<std::shared_ptr<Subdomain> > subdomains_center;					/*!< container for subdomains in center of Domain*/
	std::vector<std::shared_ptr<Subdomain> > subdomains_north;					/*!< container for subdomains in northern region of Domain*/
	std::vector<std::shared_ptr<Subdomain> > subdomains_south;					/*!< container for subdomains in southern region of Domain*/
	std::vector<std::shared_ptr<Subdomain> > subdomains_east;
	std::vector<std::shared_ptr<Subdomain> > subdomains_west;
	std::shared_ptr<Subdomain> subdomain_northwest;
	std::shared_ptr<Subdomain> subdomain_northeast;
	std::shared_ptr<Subdomain> subdomain_southwest;
	std::shared_ptr<Subdomain> subdomain_southeast;
	
	std::vector<std::shared_ptr<Neighbor> > Neighbors;							/*!< arrays of coordinates of cells in Neighboring subdomains*/
	std::vector<std::shared_ptr<Sp> > all_objects;								/*!< transient container for all objects in Domain irreSpective of location*/

	std::vector<std::vector<std::shared_ptr<Sp> > > nodeCountsTuning;
	std::vector<std::vector<std::shared_ptr<Sp> > > nodeCountsConnMod;

	// constructor

	Domain(parameters& sysparams, int index, double arg_west, double arg_north);

	~Domain();

	// given the northwest corner for a Specific Domain, creates subdomains to populate said Domain
	void defineSubdomains(parameters& sysparams);

	void attemptMutation(std::mt19937& rng);

	void cleanup(Kingdom* system);

	// populate transient container for all objects in Domain irreSpective of location
	void collectAllObjects(parameters& sysparams);

	void collectStatistics(const parameters& sysparams);

	void createConsumptionEvents(const parameters& sysparams, std::vector<std::shared_ptr<ConsumptionEvent> >& consumptionEvents);

	// make all objects available for consumption or division (set "available" property to TRUE)
	void resetAllObjects();

	// move all objects (timestep = sysparams.ui1)
	void updatePositions(parameters& sysparams, std::mt19937& rng);

	// handle division of sufficiently large objects
	void divide(parameters& sysparams, int& oid, std::vector<std::shared_ptr<Sp> >& daughters);

	void getObjectNodeCount(std::vector<std::vector<std::shared_ptr<Sp> > >& nodeCounts, const std::shared_ptr<Sp>& object);

	// calculate interparticle potentials
	void interparticle(parameters& sysparams, bool calculateActive);

	void proposeDivision(parameters& sysparams, int daughter_type, std::array<double,2>& daughter_x, double& daughter_r, int& index_parent, double& force_sum, bool& overlapstatus);


};


#endif