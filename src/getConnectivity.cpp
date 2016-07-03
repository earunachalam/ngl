#include "Network.h"


#include "universal.h"


// generate digraph representing network structure

std::vector<double> Network::getConnectivity()
{
	
	// number of non-compute nodes in network
	int numNonComputeNodes = this->nrsn + this->ntn;

	// total number of nodes in network
	int numNodes = this->ncn + numNonComputeNodes;

	std::vector<double> dcg(numNodes*numNodes); // generate empty matrix

	int inputNode_selfIndex, inputNode_position;
	

	for (int ctn = 0; ctn < this->ntn; ++ctn)
	{
		
		// number of inputs to given terminal node
		int numInputNodes = this->terminalNodes.at(ctn)->inputIndex.size();

		if (numInputNodes != 0)
		{

			inputNode_selfIndex = terminalNodes.at(ctn)->inputIndex.at(0);
			inputNode_position = this->nodeIndexToPosition(inputNode_selfIndex);
			dcg.at((this->nrsn + ctn)*numNodes + inputNode_position) = 1;

		}
	
	}


	for (int ccn = 0; ccn < this->ncn; ++ccn)
	{

		// number of inputs to given compute node
		int numInputNodes = this->computeNodes.at(ccn)->inputIndex.size();

		if (numInputNodes != 0)
		{

			for (int currInputNode = 0; currInputNode < numInputNodes; ++currInputNode)
			{

				inputNode_selfIndex = this->computeNodes.at(ccn)->inputIndex.at(currInputNode);
				inputNode_position = this->nodeIndexToPosition(inputNode_selfIndex);

				dcg.at((numNonComputeNodes + ccn)*numNodes + inputNode_position) = this->computeNodes.at(ccn)->inputWeight.at(currInputNode);

			}
		}
	}

	return dcg;

}