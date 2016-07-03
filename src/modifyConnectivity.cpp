#include "Network.h"


#include "universal.h"


bool Network::modifyConnectivity(){

	std::mt19937 rng;

	// should return true when something has been modified
	bool networkModified = false;

	// calculate number of nodes
	int numRawSignalNodes = this->rawSignalNodes.size();
	int numTerminalNodes = this->terminalNodes.size();
	int numComputeNodes = this->computeNodes.size();
	int numNodes = numRawSignalNodes + numTerminalNodes + numComputeNodes;

	std::uniform_real_distribution<double> dist(0, 1);
	
	double modificationChoice = dist(rng); double modificationChoice2 = dist(rng);

	if (dist(rng) > 0.25){ // proceed with creation of new connections or nodes

		if (dist(rng) > 0.01){ // create a new connection with existing nodes

			// select target node (whose inputs will be modified)
			int selectedNode = std::rand() % (numTerminalNodes + numComputeNodes);

			if (selectedNode < numTerminalNodes){

				// i.e. the selected node is a terminal node
				
				networkModified = singleInputNodeSwitch(terminalNodes_ptr, selectedNode, numNodes);

			} else {

				// if the selected node is a compute node

				// convert selectedNode to the index of the selected node within the vector of compute nodes
				selectedNode -= numTerminalNodes;

				networkModified = multipleInputNodeInsertNew(computeNodes_ptr, selectedNode, numNodes);

			}

		} else { // create a new adder or logistic node

			// setup for input index vector initialization
			std::vector<int> rawSignalNodeIndex(5);
			std::iota(rawSignalNodeIndex.begin(), rawSignalNodeIndex.end(), 0);
			std::random_shuffle(rawSignalNodeIndex.begin(), rawSignalNodeIndex.end());

			if (dist(rng) > 0.5){

				// create new adder node (type 2)
				
				// initialize input index vector with any raw signal node
				std::vector<int> inputIndex(1); inputIndex.at(0) = rawSignalNodeIndex.at(0);

				// only one input, so weight = 1.00
				std::vector<double> inputWeight(1); inputWeight.at(0) = 1.00;

				computeNodes.push_back(std::make_shared<ALNode>(++nodecount, inputIndex, inputWeight, 0.2, 5));

			} else {

				// create new multiplier node (type 3)

				// initialize input index vector with any raw signal node
				std::vector<int> inputIndex(1); inputIndex.at(0) = rawSignalNodeIndex.at(0);

				// only one input, so weight = 1.00
				std::vector<double> inputWeight(1); inputWeight.at(0) = 1.00;
				
				computeNodes.push_back(std::make_shared<MNode>(++nodecount, inputIndex, inputWeight));

			}

			networkModified = true;

		}

	} else { // delete an existing connection or node
			
		if (dist(rng) > 0.03){ // delete an existing connection
			
			// get directed connectivity graph of network in current state (pre-modification)
			std::vector<double> dcg = this->getConnectivity();

			// create vector holding indices of existing connections
			std::vector<int> connectionIndex(dcg.size());
			int index = -1; std::generate(connectionIndex.begin(), connectionIndex.end(),
				[&index, dcg]{++index; if (dcg.at(index) != 0){return(index);} else {return(-1);}});
			// -1 is an invalid index, ensuring that undesired accession attempts will result in an error

			// shuffle to pick connection randomly
			std::random_shuffle(connectionIndex.begin(), connectionIndex.end());

			if (std::any_of(connectionIndex.begin(), connectionIndex.end(), [](int index){return(index > 0);})){

				// if the Network.has a nonzero number of connections

				// get position of target node, assuming a pseudo
				// contiguous vector of nodes formed by concatenating
				// vectors rawSignalNodes, terminalNodes, and computeNodes
				// (in that order)

					// position (of connection to be severed) within dcg
					// (vector with dimensions numNodes*numNodes)
					int targetConnectionPosition = *(std::find_if(connectionIndex.begin(), connectionIndex.end(), [](int index){return(index >= 0);}));
					

					// position (of 'destination' member of the node pair with
					// which the connection is associated) within a pseudo
					// contiguous vector of nodes formed by concatenating
					// vectors rawSignalNodes, terminalNodes, and computeNodes
					// (in that order)
					int targetNodePosition = (int) targetConnectionPosition / numNodes;

				if (targetNodePosition < (numRawSignalNodes + numTerminalNodes)){

					// if the node to be modified is a terminal node

					// convert targetNodePosition to the index of the selected node within the vector of terminal nodes
					targetNodePosition -= numRawSignalNodes;

					networkModified = singleInputNodeSwitch(terminalNodes_ptr, targetNodePosition, numNodes);

				} else {

					// if the node to be modified is a compute node

					// convert targetNodePosition to position within vector of compute nodes
					targetNodePosition -= (numRawSignalNodes + numTerminalNodes);

						int selectedInputToTargetNodePosition = (int) targetConnectionPosition % numNodes;

						int selfIndexSelectedInputToTargetNode;

						if (selectedInputToTargetNodePosition < (numRawSignalNodes + numTerminalNodes)){

							// if selected input to target node is a raw signal node or a terminal node

							selfIndexSelectedInputToTargetNode = selectedInputToTargetNodePosition;

						} else {

							// if selected input to target node is a compute node

							selfIndexSelectedInputToTargetNode = this->nodeIndex.at(selectedInputToTargetNodePosition - numRawSignalNodes - numTerminalNodes);

						}


						if (this->computeNodes.at(targetNodePosition)->inputIndex.size() > 1){

							// if the target node has multiple inputs

							// position (of 'origin' member of the node pair with which
							// the connection is associated) within vector of input
							// indices associated with the 'destination' member of the
							// node pair
							int locationSelectedInputToTargetNode = std::find(this->computeNodes.at(targetNodePosition)->inputIndex.begin(), this->computeNodes.at(targetNodePosition)->inputIndex.end(), selfIndexSelectedInputToTargetNode) - 
																	this->computeNodes.at(targetNodePosition)->inputIndex.begin();

							// compute and assign new weights
							double newWeightScaling = 1.00/(1 - this->computeNodes.at(targetNodePosition)->inputWeight.at(locationSelectedInputToTargetNode));

							std::transform(this->computeNodes.at(targetNodePosition)->inputWeight.begin(), this->computeNodes.at(targetNodePosition)->inputWeight.end(),
								this->computeNodes.at(targetNodePosition)->inputWeight.begin(), [newWeightScaling](double origWeight) {return (newWeightScaling * origWeight);});


							// erase selected node
							this->computeNodes.at(targetNodePosition)->inputIndex.erase(this->computeNodes.at(targetNodePosition)->inputIndex.begin() + locationSelectedInputToTargetNode);
							this->computeNodes.at(targetNodePosition)->inputWeight.erase(this->computeNodes.at(targetNodePosition)->inputWeight.begin() + locationSelectedInputToTargetNode);

						} else if (this->computeNodes.at(targetNodePosition)->inputIndex.size() == 1){

							// if the target node has only one input

							this->computeNodes.at(targetNodePosition)->inputIndex.erase(this->computeNodes.at(targetNodePosition)->inputIndex.begin());
							this->computeNodes.at(targetNodePosition)->inputWeight.erase(this->computeNodes.at(targetNodePosition)->inputWeight.begin());

						}


						networkModified = true;
					
				}
			}

		} else { // delete a node

			if (numComputeNodes > 0){ // if there are at least 8 nodes, then there are available nodes to delete

				// get random position within vector of compute nodes
				int positionWithinCompute = rand() % numComputeNodes;

				// get self index of this node
				int selfIndexOfCandidate = this->nodeIndex.at(positionWithinCompute);

				// get position of this node within concatenated vector of nodes
				int positionWithinOverall = positionWithinCompute + numRawSignalNodes + numTerminalNodes;

				// get directed connectivity graph of network in current state (pre-modification)
				std::vector<double> dcg = this->getConnectivity();

				for (int connectionIndex = 0; connectionIndex < dcg.size(); ++connectionIndex){

					if (dcg.at(connectionIndex) != 0){

						// if a connection is present

						if ((connectionIndex % numNodes) == positionWithinOverall){

							// if this node is downstream of the deletion candidate

							// position of downstream node within concatenated vector of nodes
							int downstreamNodePosition = (int) (connectionIndex / numNodes);

							if (downstreamNodePosition < (numRawSignalNodes + numTerminalNodes)){

								// if affected node is a terminal node

								// convert targetNodePosition to the index of the selected node within the vector of terminal nodes
								downstreamNodePosition -= numRawSignalNodes;

								this->terminalNodes.at(downstreamNodePosition)->inputIndex.erase(this->terminalNodes.at(downstreamNodePosition)->inputIndex.begin());
								this->terminalNodes.at(downstreamNodePosition)->inputWeight.erase(this->terminalNodes.at(downstreamNodePosition)->inputWeight.begin());

							} else {

								// if affected node is a compute node

								// convert downstreamNodePosition to position within vector of compute nodes
								downstreamNodePosition -= (numRawSignalNodes + numTerminalNodes);

								if (this->computeNodes.at(downstreamNodePosition)->inputIndex.size() > 1){

									// if the target node has multiple inputs

									// position (of 'origin' member of the node pair with which
									// the connection is associated) within vector of input
									// indices associated with the 'destination' member of the
									// node pair


									auto targetInputIterator = std::find(this->computeNodes.at(downstreamNodePosition)->inputIndex.begin(), this->computeNodes.at(downstreamNodePosition)->inputIndex.end(), selfIndexOfCandidate);
									int locationSelectedInputToTargetNode = targetInputIterator - this->computeNodes.at(downstreamNodePosition)->inputIndex.begin();

									// compute and assign new weights
									double newWeightScaling = 1.00/(1 - this->computeNodes.at(downstreamNodePosition)->inputWeight.at(locationSelectedInputToTargetNode));

									std::transform(this->computeNodes.at(downstreamNodePosition)->inputWeight.begin(), this->computeNodes.at(downstreamNodePosition)->inputWeight.end(),
										this->computeNodes.at(downstreamNodePosition)->inputWeight.begin(), [newWeightScaling](double origWeight) {return (newWeightScaling * origWeight);});

									this->computeNodes.at(downstreamNodePosition)->inputIndex.erase(this->computeNodes.at(downstreamNodePosition)->inputIndex.begin() + locationSelectedInputToTargetNode);
									this->computeNodes.at(downstreamNodePosition)->inputWeight.erase(this->computeNodes.at(downstreamNodePosition)->inputWeight.begin() + locationSelectedInputToTargetNode);

								} else if (this->computeNodes.at(downstreamNodePosition)->inputIndex.size() == 1){

									// if the target node has only one input
	
									this->computeNodes.at(downstreamNodePosition)->inputIndex.erase(this->computeNodes.at(downstreamNodePosition)->inputIndex.begin());
									this->computeNodes.at(downstreamNodePosition)->inputWeight.erase(this->computeNodes.at(downstreamNodePosition)->inputWeight.begin());

								} // if no inputs, then nothing to adjust prior to deletion

							}

						}

					}
				
				}

				// reset pointer to destroy node
				this->computeNodes.at(positionWithinCompute).reset();

				// erase node
				this->computeNodes.erase(this->computeNodes.begin() + positionWithinCompute);

				networkModified = true;

			}
		}
	}


	// refresh structure-dependent network properties
	this->updateProperties();

	return(networkModified);
}



bool Network::multipleInputNodeInsertNew(std::vector<std::shared_ptr<GenericDownstreamNode>>* pointerToNodeContainer, int& targetNodePosition, int& numNodes){

	//find new input index that is not currently an input index

	//reserve Space for vector of possible inputs
	std::vector<int> possibleInputs(numNodes);

	if (((*pointerToNodeContainer)[targetNodePosition])->inputIndex.size() != 0){

		//if an input node currently exists
		
		//populate with valid indices, marking invalid indices with -1, which will
		//throw an error if an undesired accession attempt is made
		int i = -1;
		
		for (auto it = possibleInputs.begin(); it != possibleInputs.end(); ++it){
			int currInputSelfIdx = this->positionToNodeIndex(it - possibleInputs.begin());

			bool isMatch = std::any_of(((*pointerToNodeContainer)[targetNodePosition])->inputIndex.begin(),
		       ((*pointerToNodeContainer)[targetNodePosition])->inputIndex.end(),
		       [&currInputSelfIdx](int elem){return (currInputSelfIdx == elem);});

			if (isMatch){
				*it = -1; //this input index is invalid, so return -1
		 	} else {
		 		*it = currInputSelfIdx; //return this input index; it is valid
		 	}

		}

	} else {

		//if currently no input nodes

		//populate with all indices
		for (auto it = possibleInputs.begin(); it != possibleInputs.end(); ++it){
			*it = this->positionToNodeIndex(it - possibleInputs.begin());
		}
	}

	//attempt to create new connection

	if (std::all_of(possibleInputs.begin(), possibleInputs.end(),[](int currInput){return(currInput == -1);})){

		//if no connections can be made (current node has already established connections with ALL OTHER nodes)

		return false; //mutation has not been made

	} else {

		//if a new connection can be made, select one randomly
		std::shuffle(possibleInputs.begin(), possibleInputs.end(), std::mt19937{std::random_device{}()});
		int selfIndexNewInputNode = *(std::find_if(possibleInputs.begin(), possibleInputs.end(), [](int index){return(index >= 0);}));
		
		//add new node to vector of input indices
		((*pointerToNodeContainer)[targetNodePosition])->inputIndex.push_back(selfIndexNewInputNode);

		//compute and assign new weights
		double newWeight = 1.00/(((*pointerToNodeContainer)[targetNodePosition])->inputIndex.size());

		std::transform(((*pointerToNodeContainer)[targetNodePosition])->inputWeight.begin(), ((*pointerToNodeContainer)[targetNodePosition])->inputWeight.end(),
			((*pointerToNodeContainer)[targetNodePosition])->inputWeight.begin(), [newWeight](double origWeight) {return ((1-newWeight) * origWeight);});

		((*pointerToNodeContainer)[targetNodePosition])->inputWeight.push_back(newWeight);

		return(true); //mutation has been made

	}

}



bool Network::singleInputNodeSwitch(std::vector<std::shared_ptr<GenericDownstreamNode>>* pointerToNodeContainer,	int& targetNodePosition, int& numNodes){

	//find new input index that is not currently an input index

	//reserve Space for vector of possible inputs
	std::vector<int> possibleInputs(numNodes);

	if (((*pointerToNodeContainer)[targetNodePosition])->inputIndex.size() != 0){

		//if an input node currently exists
		
		//populate with valid indices, marking invalid indices with -1, which will
		//throw an error if an undesired accession attempt is made
		int i = -1;
		std::generate(possibleInputs.begin(), possibleInputs.end(),
		
			[&i, &targetNodePosition, pointerToNodeContainer]{
				
				//returns true if any of the current input indices are equal to the proposed input, i (i.e. i is invalid)
				bool isMatch = std::any_of(((*pointerToNodeContainer)[targetNodePosition])->inputIndex.begin(),
									       ((*pointerToNodeContainer)[targetNodePosition])->inputIndex.end(),
									       [&i](int currInput){return (currInput == (++i));});

				if(isMatch){
					return (-1); //this input index is invalid, so return -1
			 	} else {
			 		return i; //return this input index; it is valid
			 	}
			}
		);

	} else {

		//if currently no input nodes

		//populate with all indices
		std::iota(possibleInputs.begin(), possibleInputs.end(), 0);
	}
	
	
	std::random_shuffle(possibleInputs.begin(), possibleInputs.end());

	int positionNewInputNode = *(std::find_if(possibleInputs.begin(), possibleInputs.end(), [](int index){return(index >= 0);}));

	int selfIndexNewInputNode = this->positionToNodeIndex(positionNewInputNode);

	//make or switch connection

	if (((*pointerToNodeContainer)[targetNodePosition])->inputIndex.size() == 0){

		//if selected target node currently does not currently have any inputs

		((*pointerToNodeContainer)[targetNodePosition])->inputIndex.push_back(selfIndexNewInputNode);
		((*pointerToNodeContainer)[targetNodePosition])->inputWeight.push_back(1.00);

	} else {

		//if selected target node currently has a nonzero number of inputs

		((*pointerToNodeContainer)[targetNodePosition])->inputIndex.at(0) = selfIndexNewInputNode;

	}

	return(true); //mutation has been made

}