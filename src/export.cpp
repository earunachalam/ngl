#include "Kingdom.h"


#include "Sp.h"
#include "universal.h"


void export_single(std::ofstream& current_file, std::shared_ptr<Sp> object){

    // export physical data
    current_file << object->type << "," << object->id << "," << object->r << "," << object->mod << "," << object->x[0] << "," << object->x[1] << "," << object->v[0] << "," << object->v[1] << "," << object->f[0] << "," << object->f[1];

    // export network structure
    object->spNetwork->nwx_concatenate(current_file);
    
    // terminate sequence for current object
    current_file << std::endl;
}


void Kingdom::export_all(std::ofstream& current_file){

    for (int i = 0; i < this->Domains.size(); ++i){

        // consider all center subdomains
        for (int j = 0; j < this->Domains.at(i)->subdomains_center.size(); ++j){
            
            std::for_each(this->Domains.at(i)->subdomains_center.at(j)->residents.begin(), this->Domains.at(i)->subdomains_center.at(j)->residents.end(),[&current_file](std::shared_ptr<Sp>& object){export_single(current_file, object);});

        }

        // consider all edge subdomains
        for (int j = 0; j < this->Domains.at(i)->subdomains_north.size(); ++j){
            
            std::for_each(this->Domains.at(i)->subdomains_north.at(j)->residents.begin(), this->Domains.at(i)->subdomains_north.at(j)->residents.end(),[&current_file](std::shared_ptr<Sp>& object){export_single(current_file, object);});
            std::for_each(this->Domains.at(i)->subdomains_south.at(j)->residents.begin(), this->Domains.at(i)->subdomains_south.at(j)->residents.end(),[&current_file](std::shared_ptr<Sp>& object){export_single(current_file, object);});
            std::for_each(this->Domains.at(i)->subdomains_east.at(j)->residents.begin(), this->Domains.at(i)->subdomains_east.at(j)->residents.end(),[&current_file](std::shared_ptr<Sp>& object){export_single(current_file, object);});
            std::for_each(this->Domains.at(i)->subdomains_west.at(j)->residents.begin(), this->Domains.at(i)->subdomains_west.at(j)->residents.end(),[&current_file](std::shared_ptr<Sp>& object){export_single(current_file, object);});

        }

        // consider all corner subdomains
        std::for_each(this->Domains.at(i)->subdomain_northeast->residents.begin(), this->Domains.at(i)->subdomain_northeast->residents.end(),[&current_file](std::shared_ptr<Sp>& object){export_single(current_file, object);});
        std::for_each(this->Domains.at(i)->subdomain_southeast->residents.begin(), this->Domains.at(i)->subdomain_southeast->residents.end(),[&current_file](std::shared_ptr<Sp>& object){export_single(current_file, object);});
        std::for_each(this->Domains.at(i)->subdomain_northwest->residents.begin(), this->Domains.at(i)->subdomain_northwest->residents.end(),[&current_file](std::shared_ptr<Sp>& object){export_single(current_file, object);});
        std::for_each(this->Domains.at(i)->subdomain_southwest->residents.begin(), this->Domains.at(i)->subdomain_southwest->residents.end(),[&current_file](std::shared_ptr<Sp>& object){export_single(current_file, object);});

    }

    current_file << "NaN,NaN,NaN,-2" << std::endl;
}