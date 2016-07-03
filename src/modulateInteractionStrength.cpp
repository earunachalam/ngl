#include "Network.h"


#include "universal.h"


bool Network::modulateInteractionStrength()
{
	
	std::mt19937 rng;

	// function returns true if network is modified
	bool networkModified = false;

	std::uniform_real_distribution<double> dist(0, 1);
	std::uniform_real_distribution<double> changeDist(-0.15, 0.15);

	// calculate number of nodes
	int numRawSignalNodes = this->rawSignalNodes.size();
	int numTerminalNodes = this->terminalNodes.size();
	int numComputeNodes = this->computeNodes.size();
	int numNonComputeNodes = numRawSignalNodes + numTerminalNodes;
	int numNodes = numNonComputeNodes + numComputeNodes;

	std::vector<double> dcg = this->getConnectivity();

	// create vector holding indices of existing connections
	std::vector<int> connectionIndex(dcg.size()); std::fill(connectionIndex.begin(), connectionIndex.end(), -1);

	for (int currInteraction = (numNonComputeNodes*numNodes); currInteraction < dcg.size(); ++currInteraction)
	{

		if (dcg.at(currInteraction) != 0){

			if (this->computeNodes.at((currInteraction / numNodes) - numNonComputeNodes)->getType() == 2)
			{

				connectionIndex.at(currInteraction) = currInteraction;
			}

		}

	}

	if (std::any_of(connectionIndex.begin(), connectionIndex.end(), [](int index){return(index >= 0);})) {

		// if any valid connections to be modified

		// shuffle so as to select connection randomly
		std::shuffle(connectionIndex.begin(), connectionIndex.end(), std::mt19937{std::random_device{}()});

		int selectedConnection = *(std::find_if(connectionIndex.begin(), connectionIndex.end(), [](int index){return(index >= 0);}));

		// get position of target destination node within vector of compute nodes
		int positionSelectedTargetNode = (selectedConnection / numNodes) - numNonComputeNodes;
		
		if (dist(rng) > 0.5)
		{

			// change logistic curve properties

			if (dist(rng) > 0.5)
			{

				// change center

				if ((std::dynamic_pointer_cast<ALNode>(this->computeNodes.at(positionSelectedTargetNode)))->center == 0.00)
				{

					// if value is at lower limit, force addition

					(std::dynamic_pointer_cast<ALNode>(this->computeNodes.at(positionSelectedTargetNode)))->center += std::abs(changeDist(rng));
				
				} else if ((std::dynamic_pointer_cast<ALNode>(this->computeNodes.at(positionSelectedTargetNode)))->center == 1.00)
				{

					// if value is at upper limit, force subtraction

					(std::dynamic_pointer_cast<ALNode>(this->computeNodes.at(positionSelectedTargetNode)))->center -= std::abs(changeDist(rng));
				
				} else {

					// if value is not on edges

					(std::dynamic_pointer_cast<ALNode>(this->computeNodes.at(positionSelectedTargetNode)))->center += changeDist(rng);

					// values must be between 0 and 1
					if ((std::dynamic_pointer_cast<ALNode>(this->computeNodes.at(positionSelectedTargetNode)))->center > 1.00)
					{

						(std::dynamic_pointer_cast<ALNode>(this->computeNodes.at(positionSelectedTargetNode)))->center = 1.00;

					} else if ((std::dynamic_pointer_cast<ALNode>(this->computeNodes.at(positionSelectedTargetNode)))->center < 0)
					{

						(std::dynamic_pointer_cast<ALNode>(this->computeNodes.at(positionSelectedTargetNode)))->center = 0.00;

					}

				}

			} else {

				// change sharpness

				if ((std::dynamic_pointer_cast<ALNode>(this->computeNodes.at(positionSelectedTargetNode)))->sharpness == -100.00)
				{

					// if value is at lower limit, force addition

					(std::dynamic_pointer_cast<ALNode>(this->computeNodes.at(positionSelectedTargetNode)))->sharpness += (100.00 * std::abs(changeDist(rng)));
				
				} else if ((std::dynamic_pointer_cast<ALNode>(this->computeNodes.at(positionSelectedTargetNode)))->sharpness == 100.00)
				{

					// if value is at upper limit, force subtraction

					(std::dynamic_pointer_cast<ALNode>(this->computeNodes.at(positionSelectedTargetNode)))->sharpness -= (100.00 * std::abs(changeDist(rng)));
				
				} else {

					// if value is not on edges

					(std::dynamic_pointer_cast<ALNode>(this->computeNodes.at(positionSelectedTargetNode)))->sharpness += (100.00 * changeDist(rng));

					// cap magnitude at 100
					if (std::abs((std::dynamic_pointer_cast<ALNode>(this->computeNodes.at(positionSelectedTargetNode)))->sharpness) > 100.00)
					{

						(std::dynamic_pointer_cast<ALNode>(this->computeNodes.at(positionSelectedTargetNode)))->sharpness =
							std::copysign(100.00, (std::dynamic_pointer_cast<ALNode>(this->computeNodes.at(positionSelectedTargetNode)))->sharpness);

					}

				}

			}

			networkModified = true;

		} else {

			// change input weights

			if (this->computeNodes.at(positionSelectedTargetNode)->inputIndex.size() > 1){
				int inputToSelectedTargetNode = this->positionToNodeIndex(selectedConnection % numNodes);

				int locationSelectedInput = std::find(this->computeNodes.at(positionSelectedTargetNode)->inputIndex.begin(),
					this->computeNodes.at(positionSelectedTargetNode)->inputIndex.end(), inputToSelectedTargetNode)
					- this->computeNodes.at(positionSelectedTargetNode)->inputIndex.begin();

				double origWeightSelected = this->computeNodes.at(positionSelectedTargetNode)->inputWeight.at(locationSelectedInput);

				double weightChange = changeDist(rng);
				
				double newWeightSelected = origWeightSelected + weightChange;

				if (newWeightSelected < 0){

					newWeightSelected += (0.01 - (origWeightSelected + weightChange));

				} else if ((origWeightSelected + weightChange) > 1){

					newWeightSelected -= (1.01 - (origWeightSelected + weightChange));

				} 

				std::transform(this->computeNodes.at(positionSelectedTargetNode)->inputWeight.begin(), 
					this->computeNodes.at(positionSelectedTargetNode)->inputWeight.end(),
					this->computeNodes.at(positionSelectedTargetNode)->inputWeight.begin(), 
					[newWeightSelected, origWeightSelected](double origWeight) 
					{return ((1 - newWeightSelected)/(1 - origWeightSelected) * origWeight);});

				this->computeNodes.at(positionSelectedTargetNode)->inputWeight.at(locationSelectedInput) = newWeightSelected;
			
				networkModified = true;

			}

		}

	}

	return networkModified;

}