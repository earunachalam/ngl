#include "Network.h"


#include "universal.h"


void Network::nwx_concatenate(std::ofstream& current_file){

	// for each terminal node
	for (int i = 0; i < this->ntn; ++i){
		
		current_file << "," << nodeIndexToPosition(this->terminalNodes.at(i)->getSelfIndex());
		
		// for each input
		for (int j = 0; j < this->terminalNodes.at(i)->inputIndex.size(); ++j){
		
			current_file << "," << nodeIndexToPosition(this->terminalNodes.at(i)->inputIndex.at(j));
			current_file << "," << this->terminalNodes.at(i)->inputWeight.at(j);
		
		}

		// terminate sequence for current node
		current_file << ",NaN";
	}

	// for each compute node
	for (int i = 0; i < this->ncn; ++i){

		current_file << "," << nodeIndexToPosition(this->computeNodes.at(i)->getSelfIndex());

		if (this->computeNodes.at(i)->getType() == 2){

			// if adder-logistic node

			current_file << "," << 1;
			current_file << "," << (std::dynamic_pointer_cast<ALNode>(this->computeNodes.at(i)))->center;
			current_file << "," << (std::dynamic_pointer_cast<ALNode>(this->computeNodes.at(i)))->sharpness;

		} else {

			// if multiplier node

			current_file << "," << 2;

		}

		// for each input
		for (int j = 0; j < this->computeNodes.at(i)->inputIndex.size(); ++j){
		
			current_file << "," << nodeIndexToPosition(this->computeNodes.at(i)->inputIndex.at(j));
			current_file << "," << this->computeNodes.at(i)->inputWeight.at(j);
		
		}

		// terminate sequence for current node
		current_file << ",NaN";

	}

	// terminate sequence for current network
	// note that endline character added in calling function
	current_file << ",Inf";
}


// export Sparse array representing matrix digraph to CSV file pointed to by
// currCSV

void Network::nwx(std::ofstream& currCSV){
	
	// number of non-compute nodes in network
	int numNonComputeNodes = this->nrsn + this->ntn;

	// total number of nodes in network
	int numNodes = this->nn;

	std::vector<double> dcg(numNodes*numNodes); // generate empty matrix

	int inSelfIndex, inPosition;
	

	for (int ctn = 0; ctn < this->ntn; ++ctn){
		
		currCSV << 1;

		// number of inputs to given terminal node
		int numInputNodes = this->terminalNodes.at(ctn)->inputIndex.size();

		if (numInputNodes != 0){

			inSelfIndex = terminalNodes.at(ctn)->inputIndex.at(0);
			inPosition = this->nodeIndexToPosition(inSelfIndex);
			currCSV << "," << inPosition;

		}
		
		currCSV << ",NaN,NaN,NaN,-1" << std::endl;
	}


	for (int ccn = 0; ccn < this->ncn; ++ccn){

		if (this->computeNodes.at(ccn)->getType() == 2){

			// if adder-logistic node

			currCSV << 2 << "," 
				<< std::dynamic_pointer_cast<ALNode>(this->computeNodes.at(ccn))->center << ","
				<< std::dynamic_pointer_cast<ALNode>(this->computeNodes.at(ccn))->sharpness;

		} else {

			// if multiplier node

			currCSV << 3;

		}

		// number of inputs to given compute node
		int numInputNodes = this->computeNodes.at(ccn)->inputIndex.size();

		if (numInputNodes != 0){

			for (int ci = 0; ci < numInputNodes; ++ci){

				inSelfIndex = this->computeNodes.at(ccn)->inputIndex.at(ci);
				inPosition = this->nodeIndexToPosition(inSelfIndex);

				currCSV << "," << inPosition;

			}
		}

		currCSV << ",NaN,NaN,NaN,-1" << std::endl;

	}
}