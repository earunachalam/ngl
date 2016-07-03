#ifndef NODE_H
#define NODE_H


#include "universal.h"


// CLASS NODE
// single data processing unit in biochemical network

// used as-is for 'raw signal' nodes (1-5); other node types are derived from
// this base type

class Node {

	private:

		// self index (unique node identifier)
		int selfIndex;

	protected:

		// node type (0 = raw signal node)
		int type = 0;

	public:

		// node value
		double value = 0;

		// constructor

		// default constructor
		inline Node(int arg_selfIndex){

			this->selfIndex = arg_selfIndex;
			this->value = 0;

		};

		// copy constructor
		inline Node(const Node& origNode){

			*this = origNode;
			this->value = 0;

		}

		// destructor
		inline virtual ~Node() {}

		// self-index getter
		// (to avoid unintentional modification of unique node identifier (selfIndex)
		inline int getSelfIndex(){

			return this->selfIndex;

		}

		// self-type getter
		// (to avoid unintentional modification of unique node identifier (selfIndex)
		inline int getType(){

			return this->type;

		}

		double nodeIndexToValue(std::vector<int>* nodeIndex_ptr, std::vector<double>* nodeValue_ptr, int arg_selfIndex);
		void nodeIndexToValue(std::vector<int>* nodeIndex_ptr, std::vector<double>* nodeValue_ptr, int arg_selfIndex, double updatedValue);

};

#endif
