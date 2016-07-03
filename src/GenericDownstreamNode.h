#ifndef GDNODE_H
#define GDNODE_H

#include "Node.h"
#include "universal.h"

// CLASS GENERICDOWNSTREAMNODE
// derived from class Node

// used as-is for terminal nodes in network (3 terminal nodes: x, y, and k);
// other node types are derived from this type

class GenericDownstreamNode : public Node {

	public:

		// input indices
		std::vector<int> inputIndex;

		// input weights
		std::vector<double> inputWeight;

		// constructors

		//default constructor
		inline GenericDownstreamNode(int arg_selfIndex,
			std::vector<int> arg_inputIndex,
			std::vector<double> arg_inputWeight) : 
			Node(arg_selfIndex){
			
			this->type = 1;

			this->inputIndex = arg_inputIndex;
			this->inputWeight = arg_inputWeight;
		
		}

		// copy constructor
		inline GenericDownstreamNode(const GenericDownstreamNode& origNode) : Node(origNode){
			
			this->type = 1;

			this->inputIndex = origNode.inputIndex;
			this->inputWeight = origNode.inputWeight;
		
		}

		// destructor
		inline virtual ~GenericDownstreamNode() {}

		// run node (pull values from Specified input nodes, perform
		// computation, and update value of self)
		inline virtual void run(std::vector<int>* nodeIndex_ptr, std::vector<double>* nodeValue_ptr){
			
			// default, assuming no incoming signals
			this->value = 0;

			// if number of inputs to given node is nonzero
			if (this->inputIndex.size() != 0){

				// assuming that the number of inputs to a terminal node is 1,
				// as it should be

				// get position of input node within appropriate container and
				// update current node value accordingly

				double calculatedValue = nodeIndexToValue(nodeIndex_ptr, nodeValue_ptr, this->inputIndex.at(0));

				// cap absolute value of node value at 1 and return result
				this->value = std::copysign( std::min( std::abs(calculatedValue), 1.00), calculatedValue);
				nodeIndexToValue(nodeIndex_ptr, nodeValue_ptr, this->getSelfIndex(), this->value);

			}
		
		}

};




#endif