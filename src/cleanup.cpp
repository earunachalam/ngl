#include "Domain.h"

#include "Kingdom.h"
#include "parameters.h"
#include "Sp.h"
#include "Subdomain.h"
#include "universal.h"


void Domain::cleanup(Kingdom* system)
{
	for (auto& object : this->all_objects)
	{
		if (object->available && object->r < system->sysparams.radius_min)
		{
			std::shared_ptr<Subdomain> subdomain_cont_curr;					// initialize pointer to Subdomain containing current object
			system->findDomain(object, subdomain_cont_curr);				// identify Subdomain containing current object

			for (auto resident = subdomain_cont_curr->residents.begin(); resident != subdomain_cont_curr->residents.end(); ++resident)
			{
				if (object->id == (*resident)->id)
				{
					object.reset();
					subdomain_cont_curr->residents.erase(resident);
					break;
				}
			}

			// auto resident = std::begin(subdomain_cont_curr->residents);

			// while (resident != std::end(subdomain_cont_curr->residents))
			// {
			// 	if (object == *resident)
			// 	{
			// 		object.reset();
			// 		subdomain_cont_curr->residents.erase(resident);
			// 		break;
			// 	}

			// 	++resident;
			// }
		}
	}
}