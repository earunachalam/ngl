#ifndef NI2V_H
#define NI2V_H

#include "Node.h"
#include "universal.h"

double Node::nodeIndexToValue(std::vector<int>* nodeIndex_ptr, std::vector<double>* nodeValue_ptr, int arg_selfIndex){

	if (arg_selfIndex < 8){

		// if the node is a raw signal node or a terminal node

		return (*nodeValue_ptr)[arg_selfIndex];

	} else {

		auto position = std::find(nodeIndex_ptr->begin(), nodeIndex_ptr->end(), arg_selfIndex);

		return((*nodeValue_ptr)[position - nodeIndex_ptr->begin() + 8]);

	}	

}

void Node::nodeIndexToValue(std::vector<int>* nodeIndex_ptr, std::vector<double>* nodeValue_ptr, int arg_selfIndex, double updatedValue){

	if (arg_selfIndex < 8){

		// if the node is a raw signal node or a terminal node

		(*nodeValue_ptr)[arg_selfIndex] = updatedValue;

	} else {

		auto position = std::find(nodeIndex_ptr->begin(), nodeIndex_ptr->end(), arg_selfIndex);

		(*nodeValue_ptr)[position - nodeIndex_ptr->begin() + 8] = updatedValue;

	}	

}

#endif