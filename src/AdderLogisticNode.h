#ifndef ALNODE_H
#define ALNODE_H

#include "GenericDownstreamNode.h"
#include "universal.h"

// CLASS ALNODE
// ADDER-LOGISTIC NODE derived from class GenericDownstreamNode
// multiplies inputs by correSponding weights, sums all products, and feeds into logistic curve to obtain output

class ALNode : public GenericDownstreamNode {

	public:

		// sharpness and value about which the logistic reSponse curve is centered
		double sharpness, center;

		// constructors

		// default constructor
		inline ALNode(int arg_selfIndex,
			std::vector<int> arg_inputIndex,
			std::vector<double> arg_inputWeight,
			double arg_center, double arg_sharpness) :
			GenericDownstreamNode(arg_selfIndex, arg_inputIndex, arg_inputWeight) {

			this->type = 2;
			
			// set logistic dose-reSponse curve parameters
			this->sharpness = arg_sharpness;
			this->center = arg_center;
		
		}

		// copy constructor
		inline ALNode(const ALNode& origNode) :
			GenericDownstreamNode(origNode){

			this->type = 2;
			
			// set logistic dose-reSponse curve parameters
			this->sharpness = origNode.sharpness;
			this->center = origNode.center;

		}

		inline virtual void run(std::vector<int>* nodeIndex_ptr, std::vector<double>* nodeValue_ptr){
			
			// default, assuming no incoming signals
			this->value = 0;

			// number of inputs to current node
			int numInputs = this->inputIndex.size();

			// initialize calculated value of node to 0
			double calculatedValue = 0;

			// if the number of inputs to current node is nonzero
			if (numInputs > 0){

				// loop through input nodes
				for (int currInput = 0; currInput < numInputs; ++currInput){

					// update value of adder node, multiplying current input
					// by associated weight and adding to running total
					calculatedValue += nodeIndexToValue(nodeIndex_ptr, nodeValue_ptr, this->inputIndex.at(0)) * inputWeight.at(currInput);

				}

				// feed sum of value-weight products into logistic dose-
				// reSponse curve - the ordinate returned is the final value
				// of the node
				this->value = -1 + 
					pow(1 + exp(-1 * this->sharpness * (calculatedValue + this->center)), (-1)) + 
					pow(1 + exp(-1 * this->sharpness * (calculatedValue - this->center)), (-1));
				
				nodeIndexToValue(nodeIndex_ptr, nodeValue_ptr, this->getSelfIndex(), this->value);

			}
		
		}

};


#endif