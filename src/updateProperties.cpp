#include "Network.h"
#include "universal.h"


// update all network structure - related properties

void Network::updateProperties()
{

	// update number of each type of node
	this->nrsn = this->rawSignalNodes.size();
	this->ntn = this->terminalNodes.size();
	this->ncn = this->computeNodes.size();
	this->nn = this->nrsn + this->ntn + this->ncn;

	this->nodeValue.resize(this->nn);


	// update vector containing property selfIndex of each compute node

	this->nodeIndex.resize(this->ncn);

	for (unsigned int cn = 0; cn < this->ncn; ++cn)
	{
		nodeIndex.at(cn) = computeNodes.at(cn)->getSelfIndex();
	}


	// get digraph
	std::vector<double> dcg = getConnectivity();

	int numConnections = 0;

	std::for_each(dcg.begin(), dcg.end(),[&numConnections](double currConnection)
		{if (currConnection > 0) {++numConnections;} });

	this->nwep = numConnections;

}