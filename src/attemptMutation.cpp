#include "Domain.h"


#include "Network.h"
#include "Sp.h"
#include "universal.h"


void Domain::attemptMutation(std::mt19937& rng)
{

	// try to change network connectivity
	if (this->nodeCountsConnMod.size() != 0)
	{
		std::vector<int> objCounts(this->nodeCountsConnMod.size());

		for (int count = 0; count < objCounts.size(); ++count)
		{
			objCounts.at(count) = this->nodeCountsConnMod.at(count).size();

			if (count != 0)
			{
				objCounts.at(count) += objCounts.at(count - 1);
			}
		}

		int randomObjNum = rand() % objCounts.back();
		int randomNodeNum;

		for (int count = 0; count < objCounts.size(); ++count)
		{
			if (randomObjNum < objCounts.at(count))
			{
				randomNodeNum = count;
				break;
			}
		}

		std::random_shuffle(this->nodeCountsConnMod.at(randomNodeNum).begin(), this->nodeCountsConnMod.at(randomNodeNum).end());
		bool modified = this->nodeCountsConnMod.at(randomNodeNum).front()->spNetwork->modifyConnectivity();

		if (modified)
		{
			this->nodeCountsConnMod.at(randomNodeNum).front()->mod = true;
			this->nodeCountsConnMod.at(randomNodeNum).front()->spNetwork->existenceTime = 0;
		}


	// try to adjust parameter values
	} else if (this->nodeCountsTuning.size() != 0) {

		std::vector<int> objCounts(this->nodeCountsTuning.size());

		for (int count = 0; count < objCounts.size(); ++count)
		{
			objCounts.at(count) = this->nodeCountsTuning.at(count).size();

			if (count != 0)
			{
				objCounts.at(count) += objCounts.at(count - 1);
			}
		}

		int randomObjNum = rand() % objCounts.back();
		int randomNodeNum;

		for (int count = 0; count < objCounts.size(); ++count)
		{
			if (randomObjNum < objCounts.at(count))
			{
				randomNodeNum = count;
				break;
			}
		}

		std::random_shuffle(this->nodeCountsTuning.at(randomNodeNum).begin(), this->nodeCountsTuning.at(randomNodeNum).end());
		bool modified = this->nodeCountsConnMod.at(randomNodeNum).front()->spNetwork->modulateInteractionStrength();

		if (modified)
		{
			this->nodeCountsConnMod.at(randomNodeNum).front()->mod = true;
			this->nodeCountsConnMod.at(randomNodeNum).front()->spNetwork->existenceTime = 0;
		}
	}

	std::uniform_real_distribution<double> urd(0.0,1.0);

	if (urd(rng) < 0.01)
	{
		std::random_shuffle(std::begin(this->all_objects), std::end(this->all_objects));
		double deltaType = urd(rng);
		this->all_objects.front()->type += static_cast<int>(deltaType/std::abs(deltaType));
	}
}