#include "Kingdom.h"


#include "Domain.h"


void Kingdom::evict(){

    // consider each Domain

	for (std::size_t i = 0; i < this->Domains.size(); ++i){
		
        // consider center subdomains

    	for (std::size_t j = 0; j < this->Domains.at(i)->subdomains_center.size(); ++j){

    		for (int k = 0; k < this->Domains.at(i)->subdomains_center.at(j)->residents.size(); ++k){

    			if (this->Domains.at(i)->subdomains_center.at(j)->outOfBounds(k)){
    			
    				this->assignDomain(this->Domains.at(i)->subdomains_center.at(j)->residents.at(k));
    				this->Domains.at(i)->subdomains_center.at(j)->residents.at(k).reset();
    				this->Domains.at(i)->subdomains_center.at(j)->residents.erase(this->Domains.at(i)->subdomains_center.at(j)->residents.begin() + k);
    			
    			}

    		}
    	}

        // consider cardinal subdomains

    	for (std::size_t j = 0; j < this->Domains.at(i)->subdomains_north.size(); ++j){

    		for (int k = 0; k < this->Domains.at(i)->subdomains_north.at(j)->residents.size(); ++k){

    			if (this->Domains.at(i)->subdomains_north.at(j)->outOfBounds(k)){
    			
    				this->assignDomain(this->Domains.at(i)->subdomains_north.at(j)->residents.at(k));
    				this->Domains.at(i)->subdomains_north.at(j)->residents.at(k).reset();
    				this->Domains.at(i)->subdomains_north.at(j)->residents.erase(this->Domains.at(i)->subdomains_north.at(j)->residents.begin() + k);
    			
    			}

    		}

    		for (int k = 0; k < this->Domains.at(i)->subdomains_south.at(j)->residents.size(); ++k){

    			if (this->Domains.at(i)->subdomains_south.at(j)->outOfBounds(k)){
    			
    				this->assignDomain(this->Domains.at(i)->subdomains_south.at(j)->residents.at(k));
    				this->Domains.at(i)->subdomains_south.at(j)->residents.at(k).reset();
    				this->Domains.at(i)->subdomains_south.at(j)->residents.erase(this->Domains.at(i)->subdomains_south.at(j)->residents.begin() + k);
    			
    			}

    		}

    		for (int k = 0; k < this->Domains.at(i)->subdomains_east.at(j)->residents.size(); ++k){

    			if (this->Domains.at(i)->subdomains_east.at(j)->outOfBounds(k)){
    			
    				this->assignDomain(this->Domains.at(i)->subdomains_east.at(j)->residents.at(k));
    				this->Domains.at(i)->subdomains_east.at(j)->residents.at(k).reset();
    				this->Domains.at(i)->subdomains_east.at(j)->residents.erase(this->Domains.at(i)->subdomains_east.at(j)->residents.begin() + k);
    			
    			}

    		}

    		for (int k = 0; k < this->Domains.at(i)->subdomains_west.at(j)->residents.size(); ++k){

    			if (this->Domains.at(i)->subdomains_west.at(j)->outOfBounds(k)){
    			
    				this->assignDomain(this->Domains.at(i)->subdomains_west.at(j)->residents.at(k));
    				this->Domains.at(i)->subdomains_west.at(j)->residents.at(k).reset();
    				this->Domains.at(i)->subdomains_west.at(j)->residents.erase(this->Domains.at(i)->subdomains_west.at(j)->residents.begin() + k);
    			
    			}

    		}

    	}

        // consider intercardinal subdomains

        for (int k = 0; k < this->Domains.at(i)->subdomain_northeast->residents.size(); ++k){

            if (this->Domains.at(i)->subdomain_northeast->outOfBounds(k)){
            
                this->assignDomain(this->Domains.at(i)->subdomain_northeast->residents.at(k));
                this->Domains.at(i)->subdomain_northeast->residents.at(k).reset();
                this->Domains.at(i)->subdomain_northeast->residents.erase(this->Domains.at(i)->subdomain_northeast->residents.begin() + k);
            
            }

        }

        for (int k = 0; k < this->Domains.at(i)->subdomain_northwest->residents.size(); ++k){

            if (this->Domains.at(i)->subdomain_northwest->outOfBounds(k)){
            
                this->assignDomain(this->Domains.at(i)->subdomain_northwest->residents.at(k));
                this->Domains.at(i)->subdomain_northwest->residents.at(k).reset();
                this->Domains.at(i)->subdomain_northwest->residents.erase(this->Domains.at(i)->subdomain_northwest->residents.begin() + k);
            
            }

        }

        for (int k = 0; k < this->Domains.at(i)->subdomain_southeast->residents.size(); ++k){

            if (this->Domains.at(i)->subdomain_southeast->outOfBounds(k)){
            
                this->assignDomain(this->Domains.at(i)->subdomain_southeast->residents.at(k));
                this->Domains.at(i)->subdomain_southeast->residents.at(k).reset();
                this->Domains.at(i)->subdomain_southeast->residents.erase(this->Domains.at(i)->subdomain_southeast->residents.begin() + k);
            
            }

        }

        for (int k = 0; k < this->Domains.at(i)->subdomain_southwest->residents.size(); ++k){

            if (this->Domains.at(i)->subdomain_southwest->outOfBounds(k)){
            
                this->assignDomain(this->Domains.at(i)->subdomain_southwest->residents.at(k));
                this->Domains.at(i)->subdomain_southwest->residents.at(k).reset();
                this->Domains.at(i)->subdomain_southwest->residents.erase(this->Domains.at(i)->subdomain_southwest->residents.begin() + k);
            
            }

        }

	}

}