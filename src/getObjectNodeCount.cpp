#include "Domain.h"

#include "Sp.h"
#include "universal.h"

void Domain::getObjectNodeCount(std::vector<std::vector<std::shared_ptr<Sp> > >& nodeCounts, const std::shared_ptr<Sp>& object)
{
	// number of objects in current object's network
	int currNumNodes = object->spNetwork->nn;

	// index within nodeCounts vector
	int idxCumulativeDist = currNumNodes - 5;

	if (idxCumulativeDist >= nodeCounts.size())
	{
		
		// resize vector as necessary
		do { nodeCounts.resize(nodeCounts.size() + 1);
		} while (idxCumulativeDist >= nodeCounts.size());

		nodeCounts.back().push_back(object);

	} else {

		nodeCounts.at(idxCumulativeDist).push_back(object);

	}
}