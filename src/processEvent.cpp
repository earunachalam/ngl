#include "ConsumptionEvent.h"


#include "Domain.h"
#include "Kingdom.h"
#include "universal.h"


// check event validity and execute if possible
void ConsumptionEvent::processEvent(Kingdom* system, std::vector<std::shared_ptr<Sp> >& carcasses)
{

	double sum_valid_pred_energy = 0;
	double f_curr_total_pred;		// fraction of total predator energy coming from current predator
	double e_curr_prey;				// amount of energy current predator takes from prey
	double e_curr_sum;				// sum of energy current predator takes from prey and existing energy of current predator

	double x_diff_0;
	double x_diff_1;
	double m_frac_pair;
	bool overlap_status = false;

	for (int i = 0; i < this->predators.size(); ++i)
	{
		if (this->predators.at(i)->available)
		{
			sum_valid_pred_energy += this->predators_energy.at(i);
		}
	}

	if (sum_valid_pred_energy > this->prey_energy)
	{
		// clear backup vectors and resize for current run
		this->predators_orig_radius.clear(); this->predators_orig_radius.resize(this->predators.size());
		this->predators_orig_x0.clear(); this->predators_orig_x0.resize(this->predators.size());
		this->predators_orig_x1.clear(); this->predators_orig_x1.resize(this->predators.size());

		for (int i = 0; i < this->predators.size(); ++i)
		{

			if (this->predators.at(i)->available){

				f_curr_total_pred = this->predators_energy.at(i)/sum_valid_pred_energy;

				e_curr_prey = f_curr_total_pred * this->prey_energy;

				// (m1 + m2)^-1 * m1*x1 + m2*x2 = x1'
				// m2 * (m1 + m2)^-1 * (x2 - x1) = dx1

				x_diff_0 = this->prey->x[0] - this->predators.at(i)->x[0];
				x_diff_1 = this->prey->x[1] - this->predators.at(i)->x[1];

				e_curr_sum = e_curr_prey + this->predators_energy.at(i);
				m_frac_pair = e_curr_prey / e_curr_sum;

				// make a backup of original radii and positions
				this->predators_orig_radius.at(i) = this->predators.at(i)->r;
				this->predators_orig_x0.at(i) = this->predators.at(i)->x[0];
				this->predators_orig_x1.at(i) = this->predators.at(i)->x[1];

				this->predators.at(i)->x[0] += (m_frac_pair * x_diff_0);
				this->predators.at(i)->x[1] += (m_frac_pair * x_diff_1);
		        this->predators.at(i)->x[0] -= (system->sysparams.length*static_cast<double>(static_cast<int>(this->predators.at(i)->x[0] / system->sysparams.max_x)));
		        this->predators.at(i)->x[1] -= (system->sysparams.length*static_cast<double>(static_cast<int>(this->predators.at(i)->x[1] / system->sysparams.max_x)));

				this->predators.at(i)->r *= cbrt(e_curr_sum/(this->predators_energy.at(i)));

				this->predators.at(i)->available = false;

				overlap_status = false;
				this->proposeConsumption(system->sysparams, this->predators.at(i), this->prey, system->Domains.at(this->location)->all_objects, system->Domains.at(this->location)->Neighbors, overlap_status);

				// if overlap exists, then restore original radii and positions and abandon consumption attempt
				if (overlap_status)
				{
					for (int j = i; j > -1; --j)
					{
						this->predators.at(j)->r = this->predators_orig_radius.at(j);
						this->predators.at(j)->x[0] = this->predators_orig_x0.at(j);
						this->predators.at(j)->x[1] = this->predators_orig_x1.at(j);
						this->predators.at(j)->available = true;
					}

					return;

				}

			}
	
		}

		// if no overlap has occurred during any of the checks

		for (int i = 0; i < system->Domains.at(this->location)->all_objects.size(); ++i)
		{

			if (this->prey == system->Domains.at(this->location)->all_objects.at(i))
			{
				system->Domains.at(this->location)->all_objects.erase(system->Domains.at(this->location)->all_objects.begin() + i);	
				break;
			}
		}

		std::shared_ptr<Subdomain> subdomain_cont_curr;					// initialize pointer to Subdomain containing current object
		system->findDomain(this->prey, subdomain_cont_curr);				// identify Subdomain containing current object

		for (int i = 0; i < subdomain_cont_curr->residents.size(); ++i)
		{

			if (this->prey == subdomain_cont_curr->residents.at(i))
			{
				subdomain_cont_curr->residents.erase(subdomain_cont_curr->residents.begin() + i);
				break;
			}
		}

		this->prey->available = false;

		this->prey.reset();

	}

}