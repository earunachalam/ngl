#include "Network.h"


#include "universal.h"


void Network::indexNetwork()
{

	int numComputeNodes = this->computeNodes.size();
	nodeIndex.resize(numComputeNodes);

	for (int currNode = 0; currNode < numComputeNodes; ++currNode){
		nodeIndex.at(currNode) = computeNodes.at(currNode)->getSelfIndex();
	}

}