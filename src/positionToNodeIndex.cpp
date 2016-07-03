#include "Network.h"


#include "universal.h"


int Network::positionToNodeIndex(int position)
{
	// number of non-compute nodes
	unsigned int nNonComputeNodes = this->rawSignalNodes.size() + this->terminalNodes.size();

	if ((unsigned int) position < nNonComputeNodes)
	{
		// if the position corresponds to a raw signal node or a terminal node, then the node index and position are fixed and equal

		return position;

	} else {

		// if the self index corresponds to a compute node, look up the index from the node
		return this->nodeIndex.at((unsigned int) position - nNonComputeNodes);

	}

}