#ifndef MKDIR_H
#define MKDIR_H

#include "parameters.h"
#include "universal.h"

// FUNCTION MKDIR
// create directory to store trajectories for current simulation
// name of directory within ./data/ is timestamp

inline std::string mkdir(parameters& sysparams, unsigned int thread)
{

	std::string str = std::to_string(time(0));

	str += ("_" + std::to_string(thread));

	// main directory
	std::string filename = sysparams.rootdir + "/data/" + str;

	// subdirectories
	sysparams.sub1 = filename + "/state", sysparams.sub2 = filename + "/img";

	int warning; // return type assigned to avoid warning when compiling with optimization flag -O2

	// create main directory
	std::string syscmd_mkdir = "mkdir " + filename;
	warning = system(syscmd_mkdir.c_str());

	// create position sub-directory
	std::string syscmd_mkdir_sub1 = "mkdir " + sysparams.sub1;
	warning = system(syscmd_mkdir_sub1.c_str());

	// create image sub-directory
	std::string syscmd_mkdir_sub2 = "mkdir " + sysparams.sub2;
	warning = system(syscmd_mkdir_sub2.c_str());

	// copy parameter initialization file to current directory for reference
	std::string syscmd_cp_parameters = "cp " + sysparams.rootdir + "/cfg/parameters.csv " + filename;
	warning = system(syscmd_cp_parameters.c_str());


	return filename;
}

#endif
