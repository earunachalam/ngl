#include "Kingdom.h"

#include "Neighbor.h"
#include "Sp.h"
#include "universal.h"

// populate Neighbor list for each Domain so that propagation calculations can
// be performed independently

void Kingdom::trade(){

	int linear_north, linear_south, linear_east, linear_west;
	int linear_northeast, linear_northwest, linear_southeast, linear_southwest;

	// consider each Domain
	for (auto& currDomain : this->Domains){

		// clear previously existing list of Neighbors
		for (auto& Neighbor : currDomain->Neighbors) { Neighbor.reset(); }
		currDomain->Neighbors.clear();

		linear_north = currDomain->linear_north;
		linear_south = currDomain->linear_south;
		linear_east = currDomain->linear_east;
		linear_west = currDomain->linear_west;
		linear_northeast = currDomain->linear_northeast;
		linear_northwest = currDomain->linear_northwest;
		linear_southeast = currDomain->linear_southeast;
		linear_southwest = currDomain->linear_southwest;

		for (int subdLocation = 0; subdLocation < sysparams.subd_per_dlength_side; ++subdLocation){

			// north
			for (auto& resident : this->Domains.at(linear_north)->subdomains_south.at(subdLocation)->residents){
				currDomain->Neighbors.push_back(std::make_shared<Neighbor>(resident));
			}

			// south
			for (auto& resident : this->Domains.at(linear_south)->subdomains_north.at(subdLocation)->residents){
				currDomain->Neighbors.push_back(std::make_shared<Neighbor>(resident));
			}

			// east
			for (auto& resident : this->Domains.at(linear_east)->subdomains_west.at(subdLocation)->residents){
				currDomain->Neighbors.push_back(std::make_shared<Neighbor>(resident));
			}

			// west
			for (auto& resident : this->Domains.at(linear_west)->subdomains_east.at(subdLocation)->residents){
				currDomain->Neighbors.push_back(std::make_shared<Neighbor>(resident));
			}
		}

		// consider each Subdomain not in a set

		// north (corners)
		for (auto& resident : this->Domains.at(linear_north)->subdomain_southeast->residents){
			currDomain->Neighbors.push_back(std::make_shared<Neighbor>(resident));
		}
		for (auto& resident : this->Domains.at(linear_north)->subdomain_southwest->residents){
			currDomain->Neighbors.push_back(std::make_shared<Neighbor>(resident));
		}

		// south (corners)
		for (auto& resident : this->Domains.at(linear_south)->subdomain_northeast->residents){
			currDomain->Neighbors.push_back(std::make_shared<Neighbor>(resident));
		}
		for (auto& resident : this->Domains.at(linear_south)->subdomain_northwest->residents){
			currDomain->Neighbors.push_back(std::make_shared<Neighbor>(resident));
		}

		// east (corners)
		for (auto& resident : this->Domains.at(linear_east)->subdomain_northwest->residents){
			currDomain->Neighbors.push_back(std::make_shared<Neighbor>(resident));
		}
		for (auto& resident : this->Domains.at(linear_east)->subdomain_southwest->residents){
			currDomain->Neighbors.push_back(std::make_shared<Neighbor>(resident));
		}

		// west (corners)
		for (auto& resident : this->Domains.at(linear_west)->subdomain_northeast->residents){
			currDomain->Neighbors.push_back(std::make_shared<Neighbor>(resident));
		}
		for (auto& resident : this->Domains.at(linear_west)->subdomain_southeast->residents){
			currDomain->Neighbors.push_back(std::make_shared<Neighbor>(resident));
		}

		// northeast
		for (auto& resident : this->Domains.at(linear_northeast)->subdomain_southwest->residents){
			currDomain->Neighbors.push_back(std::make_shared<Neighbor>(resident));
		}

		// northwest
		for (auto& resident : this->Domains.at(linear_northwest)->subdomain_southeast->residents){
			currDomain->Neighbors.push_back(std::make_shared<Neighbor>(resident));
		}

		// southeast
		for (auto& resident : this->Domains.at(linear_southeast)->subdomain_northwest->residents){
			currDomain->Neighbors.push_back(std::make_shared<Neighbor>(resident));
		}

		// southwest
		for (auto& resident : this->Domains.at(linear_southwest)->subdomain_northeast->residents){
			currDomain->Neighbors.push_back(std::make_shared<Neighbor>(resident));
		}

	}
}
