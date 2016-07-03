#include "Kingdom.h"


#include "Domain.h"
#include "mkdir.h"
#include "parameters.h"
#include "universal.h"


Kingdom::Kingdom(std::string rootdir, unsigned int thread)
{

	// import simulation parameters
	this->sysparams = import_parameters(rootdir);
	currDirectory = mkdir(sysparams, thread);

	// initialize random number generator
	srand(time(NULL));
	std::random_device rd;
	rng.seed(rd());

	defineDomains();

}


Kingdom::~Kingdom()
{
	// free all memory

	for (size_t i = 0; i < this->Domains.size(); ++i)
	{
		this->Domains.at(i).reset();
	}

}
