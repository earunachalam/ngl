#ifndef MNODE_H
#define MNODE_H

#include "GenericDownstreamNode.h"
#include "universal.h"

// CLASS MNODE
// MULTIPLIER NODE derived from class GenericDownstreamNode
// multiplies all inputs together to obtain output

class MNode : public GenericDownstreamNode {

	public:

		// constructors

		// default constructor
		inline MNode(int arg_selfIndex, std::vector<int> arg_inputIndex, std::vector<double> arg_inputWeight) :
			GenericDownstreamNode(arg_selfIndex, arg_inputIndex, arg_inputWeight) {

			this->type = 3;
		
		}

		// copy constructor
		inline MNode(const MNode& origNode) :
			GenericDownstreamNode(origNode) {

			this->type = 3;
		
		}

		inline virtual void run(std::vector<int>* nodeIndex_ptr, std::vector<double>* nodeValue_ptr){

			// default, assuming no incoming signals
			this->value = 0;

			int numInputs = this->inputIndex.size();

			// if number of inputs to given node is nonzero
			if (numInputs > 0){

				double calculatedValue = nodeIndexToValue(nodeIndex_ptr, nodeValue_ptr, this->inputIndex.at(0));

				if (numInputs > 1){
					for (int currInput = 1; currInput < numInputs; ++currInput){
				
						// update value of adder node
						calculatedValue *= nodeIndexToValue(nodeIndex_ptr, nodeValue_ptr, this->inputIndex.at(currInput));
				
					}
				}

				// assign calculated value to property
				this->value = calculatedValue;

				nodeIndexToValue(nodeIndex_ptr, nodeValue_ptr, this->getSelfIndex(), this->value);
			
			}
		
		}

};

#endif