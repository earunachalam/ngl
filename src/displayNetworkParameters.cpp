#include "Network.h"


#include "universal.h"


void Network::displayNetworkParameters()
{
	
	// for each terminal node
	for (int i = 0; i < this->ntn; ++i)
	{
		P2S(this->terminalNodes.at(i));
		P2S(this->terminalNodes.at(i)->getSelfIndex());
		// VI2S(this->terminalNodes.at(i)->inputIndex, 1, this->terminalNodes.at(i)->inputIndex.size());
		// VD2S(this->terminalNodes.at(i)->inputWeight, 1, this->terminalNodes.at(i)->inputWeight.size());
	}

	// for each compute node
	for (int i = 0; i < this->ncn; ++i)
	{
		P2S(this->computeNodes.at(i));
		P2S(this->computeNodes.at(i)->getSelfIndex());
		P2S(this->computeNodes.at(i)->getType());
		
		if (this->computeNodes.at(i)->getType() == 2)
		{

			// if adder-logistic node

			P2S((std::dynamic_pointer_cast<ALNode>(this->computeNodes.at(i)))->center);
			P2S((std::dynamic_pointer_cast<ALNode>(this->computeNodes.at(i)))->sharpness);

		}

		// VI2S(this->computeNodes.at(i)->inputIndex, 1, this->computeNodes.at(i)->inputIndex.size());
		// VD2S(this->computeNodes.at(i)->inputWeight, 1, this->computeNodes.at(i)->inputWeight.size());
	}

	// VD2S(this->getConnectivity(), this->nn, this->nn);
	// VI2S(this->nodeIndex,1,this->nodeIndex.size());
	M2S("------------------------------------------------------------------------------------------");
}