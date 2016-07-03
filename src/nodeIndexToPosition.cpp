#include "Network.h"


#include "universal.h"


int Network::nodeIndexToPosition(int arg_selfIndex)
{
	// number of non-compute nodes
	unsigned int nNonComputeNodes = rawSignalNodes.size() + terminalNodes.size();

	if ((unsigned int) arg_selfIndex < nNonComputeNodes)
	{
		// if the self index corresponds to a raw signal node or a terminal node, then the node index and position are fixed and equal

		return arg_selfIndex;

	} else {

		// if the self index corresponds to a compute node, look up the index from the node

		// number of compute nodes in network
		unsigned int nComputeNodes = this->computeNodes.size();

		for (unsigned int i = 0; i < nComputeNodes; ++i)
		{
			
			if (this->computeNodes.at(i)->getSelfIndex() == arg_selfIndex)
			{
				// return index within nodes vector
				return((int) (i + nNonComputeNodes));
			}

		}

		// return invalid index -1: unsuccessful query
		return(-1);

	}

}