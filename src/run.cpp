#include "Network.h"

#include "universal.h"

// run network (i.e. perform node-wise computation and extract final results)
// accepts references to values of raw input signals (input arguments 1-5) and
// references to values of terminal nodes (input arguments 6-8), which are
// updated with the results of the run

void Network::run(double v_0, double v_1, double v_2)
{

	// import values of raw signals into correSponding nodes
	this->rawSignalNodes.at(0)->value = v_0;
	this->rawSignalNodes.at(1)->value = v_1;
	this->rawSignalNodes.at(2)->value = v_2;

	// update all node values
	this->updateValues();

	// process all computation nodes
	if (this->ncn > 0){
		for (int cn = 0; cn < this->ncn; ++cn){

			this->computeNodes.at(cn)->run(this->nodeIndex_ptr, this->nodeValue_ptr);	

		}
	}

	// process all terminal nodes
	for (int cn = 0; cn < this->ntn; ++cn){
		
		this->terminalNodes.at(cn)->run(this->nodeIndex_ptr, this->nodeValue_ptr);
		
	}
}