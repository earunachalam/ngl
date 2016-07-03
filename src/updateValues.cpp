#include "Network.h"
#include "universal.h"

// update values of all nodes

void Network::updateValues()
{

	this->nodeValue.resize(this->nrsn + this->ntn + this->ncn);

	//update values

	for (int cn = 0; cn < this->nrsn; ++cn){

		this->nodeValue.at(cn) = this->rawSignalNodes.at(cn)->value;

	}

	for (int cn = 0; cn < this->ntn; ++cn){

		this->nodeValue.at(cn + this->nrsn) = this->terminalNodes.at(cn)->value;

	}

	for (int cn = 0; cn < this->ncn; ++cn){

		this->nodeValue.at(cn + this->nrsn + this->ntn) = this->computeNodes.at(cn)->value;

	}

}