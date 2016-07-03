#include "Network.h"


#include "universal.h"


// default constructor

Network::Network(){
	
	// initialize existence time of network to 0 (creating network)
	existenceTime = 0;

	// create raw signal nodes (self signal change, nonself signal change, self energy)
	for (int crsn = 0; crsn < 3; ++crsn){
		this->rawSignalNodes.push_back(std::make_shared<Node>(crsn));
	}

	// create terminal nodes (f and k terminals)
	for (int ctn = 0; ctn < 2; ++ctn){
		
		std::vector<int> inputIndex; std::vector<double> inputWeight;

		if (ctn == 0){ 
			inputIndex.push_back(0);
			inputWeight.push_back(1.00);
		}

		// if terminal node == 1 (k terminal), then initialize without input
		// indices

		this->terminalNodes.push_back(
			std::make_shared<GenericDownstreamNode>
			(ctn + this->rawSignalNodes.size(), inputIndex, inputWeight));
		
	}

	// update all network structure - dependent properties
	this->updateProperties();

	// update property nodecount to reflect the creation of 10 nodes (i.e.
	// selfIndex up to 10 - 1 = 9 have been used up)
	this->nodecount = this->nn - 1;

}


// copy constructor

Network::Network(const Network& orignw){

	// create raw signal nodes
	for (int crsn = 0; crsn < orignw.nrsn; ++crsn){
		this->rawSignalNodes.push_back(std::make_shared<Node>(crsn));
	}

	// create terminal nodes (F and k terminals)
	for (int ctn = 0; ctn < orignw.ntn; ++ctn){
		
		this->terminalNodes.push_back(std::make_shared<GenericDownstreamNode>(  *(orignw.terminalNodes.at(ctn))  ));

	}

	// create compute nodes
	for (int ccn = 0; ccn < orignw.ncn; ++ccn){

		if ((orignw.computeNodes.at(ccn))->getType() == 2){

			// if the current compute node is an adder-logistic node
			this->computeNodes.push_back(std::make_shared<ALNode>(*(std::dynamic_pointer_cast<ALNode>(orignw.computeNodes.at(ccn)))));
		
		} else {

			// if the current compute node is a multiplicative node
			this->computeNodes.push_back(std::make_shared<MNode>(*(std::dynamic_pointer_cast<MNode>(orignw.computeNodes.at(ccn)))));

		}
		
	}

	// update all network structure - dependent properties
	this->updateProperties();

	// update property nodecount to reflect the creation of 10 nodes (i.e.
	// selfIndex up to 10 - 1 = 9 have been used up)
	this->nodecount = orignw.nodecount;

}
// network destructor

Network::~Network(){
	
	// free memory allocated to nodes by resetting pointer, then erase nodes

	for (auto& node : this->rawSignalNodes){ node.reset(); }
	for (auto& node : this->terminalNodes){ node.reset(); }
	for (auto& node : this->computeNodes){ node.reset(); }

	this->rawSignalNodes.clear(); this->terminalNodes.clear(); this->computeNodes.clear();

}
