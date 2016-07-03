#ifndef NETWORK_H
#define NETWORK_H


#include "AdderLogisticNode.h"
#include "GenericDownstreamNode.h"
#include "MultiplierNode.h"
#include "Node.h"


#include "universal.h"

// CLASS NETWORK
// biochemical network used by active egents to calculate active forces

class Network {

public:

	// container for raw signal nodes
	std::vector<std::shared_ptr<Node>> rawSignalNodes;
	// pointer to container
	std::vector<std::shared_ptr<Node>>* rawSignalNodes_ptr = &rawSignalNodes;
	// number of raw signal nodes
	unsigned int nrsn;


	// container for terminal nodes
	std::vector<std::shared_ptr<GenericDownstreamNode>> terminalNodes;
	// pointer to container
	std::vector<std::shared_ptr<GenericDownstreamNode>>* terminalNodes_ptr = &terminalNodes;
	// number of terminal nodes
	unsigned int ntn;

	// container for compute nodes
	std::vector<std::shared_ptr<GenericDownstreamNode>> computeNodes;
	// pointer to container
	std::vector<std::shared_ptr<GenericDownstreamNode>>* computeNodes_ptr = &computeNodes;
	// number of compute nodes
	unsigned int ncn;

	// total number of nodes
	unsigned int nn;

	// node indices (contains property self_index of each compute node)
	// property self_index is fixed for raw signal and terminal nodes
	std::vector<int> nodeIndex;
	// pointer to container
	std::vector<int>* nodeIndex_ptr = &nodeIndex;

	// node values (contains value property of each node)
	std::vector<double> nodeValue;
	// pointer to container
	std::vector<double>* nodeValue_ptr = &nodeValue;

	// number of nodes that have ever been created in a Specific instance of
	// this network; used for assigning to each node its self_index property, a
	// unique identifier that is never reused)
	int nodecount = 0;

	// number of timesteps that the Network.has persisted unchanged (i.e. no
	// change in either connectivity or interaction strengths)
	unsigned int existenceTime;

	// energy penalty rate associated with network computation; dependent on
	// number of connections in digraph of network structure
	double nwep;

	// network constructors
	Network(); // default constructor
	Network(const Network& obj); // copy constructor

	// network destructor
	~Network();

	// print all information about current structure of network
	void displayNetworkParameters();

	void indexNetwork();

	// export Sparse array representing digraph to file current_file
	void nwx(std::ofstream& current_file);

	// export Sparse array representing digraph to file current_file
	// designed to add onto file containing physical data
	void nwx_concatenate(std::ofstream& current_file);

	// get position of node that has property selfIndex equal to the input
	// argument of this function, assuming a pseudo contiguous vector of nodes
	// formed by concatenating vectors rawSignalNodes, terminalNodes, and
	// computeNodes (in that order)
	int nodeIndexToPosition(int arg_selfIndex);

	// convert position of node within pseudo contiguous vector of nodes to
	// self index of node
	int positionToNodeIndex(int position);

	// update all network structure - related properties
	void updateProperties();

	// update values of all nodes
	void updateValues();

	// produce directed connectivity graph (DCG) of network, in vector form
	std::vector<double> getConnectivity();

	// run network (i.e. perform node-wise computation and extract final
	// results) accepts references to values of raw input signals (input
	// arguments 1-5) and references to values of terminal nodes (input
	// arguments 6-8), which are updated with the results of the run
	void run(double v_0, double v_1, double v_2);

	// Network Mutation

	// change parameters for existing connections
	bool modulateInteractionStrength();

	// change connections by either creating/deleting connections between
	// existing nodes or creating deleting nodes themselves
	bool modifyConnectivity();

	// modifyConnectivity calls the below functions, both of which return true
	// if a modification has been made to network structure, and false
	// otherwise
	bool singleInputNodeSwitch(std::vector<std::shared_ptr<GenericDownstreamNode>>* pointerToNodeContainer,	int& targetNodePosition, int& numNodes);
	bool multipleInputNodeInsertNew(std::vector<std::shared_ptr<GenericDownstreamNode>>* pointerToNodeContainer, int& targetNodePosition, int& numNodes);

};

#endif
