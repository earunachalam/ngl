#ifndef PARAMETERS_H
#define PARAMETERS_H

#include "universal.h"

// STRUCT PARAMETERS
// data structure to hold all simulation parameter values

struct parameters {
int temp;

	// values of simulation parameters

	int timesteps;						/**< number of milliseconds to run (for testing purposes)*/
	int batch_save_size; 				/**< number of milliseconds per batch (to save trajectory records)*/
	std::string sub1, sub2, sub3;		/**< subdirectories to hold physical state, network state, and simulation frame images, reSpectively*/
	std::string rootdir;				/**< parent directory from which program is executed*/


	// physical constants

	double kb = 1.38e-23;						/**< J/K (Boltzmann's constant)*/
	double T = 298.15;							/**< K (system temperature)*/
	double kbt = (kb * T);						/**< J (inverse of thermodynamic beta)*/
	double visc_h2o = 8.94e-4;					/**< Pa*s (viscosity of water)*/
	double diffusion_constant_max;				/**< diffusion constant of smallest cell possible*/
	double mpf;									/**< prefactor by which volume must be multiplied in order to obtain mass of spherical cell*/
	double dtpf = 6.00 * M_PI * 8.94e-4;		/**< prefactor by which radius must be multiplied in order to obtain the translational damping constant for the spherical cell*/
	double drpf = 8.00 * M_PI * 8.94e-4;		/**< prefactor by which radius must be multiplied in order to obtain the rotational damping constant for the spherical cell*/


	// values of system parameters

	double interaction_length;			/**< characteristic length scale, in microns*/
	double subdomain_length;			/**< side length of square/cubic Subdomain, in microns*/
	int subd_per_dlength;				/**< ratio of Domain side length to Subdomain side length*/
	int subd_per_dlength_side;			/**< number of subdomains along each side of a Domain, excluding corner subdomains*/
	double Domain_length;				/**< side length of square/cubic Domain, in microns*/
	int nBoxes;							/**< number of characteristic length scales from origin that the simulation box extends in each direction (+x, -x, +y, ... )*/
	int domains_per_syslength;			/**< ratio of length of side of system to Domain length*/
	double length;						/**< distance that simulation box extends from the origin in each direction in each dimension, in units of microns*/
	double min_x, max_x;				/**< abs(min_x) + abs(max_x) = length; defines upper/lower bound in each dimension, in units of microns*/
	double dt;							/**< timestep length in seconds*/
	double sf;							/**< mass and timestep scaling factor*/
	double sf_interparticle; 			/**< scaling factor for interparticle forces*/
	double vdistance_threshold; 		/**< distance threshold beyond which interparticle potentials are zero*/
	int nCells_init;					/**< number of each Species for seeding*/
	int ui1; 							/**< update intervals (uis) in units of dt * sf for forces due to interparticle potentials*/
	int ui2; 							/**< update intervals (uis) in units of ui1 for active forces*/
	int t_mix; 							/**< characteristic timescale for mutation in units of dt * sf*/
	double sig_threshold;


	// energy values

	double radius_dist_center; 			/**< center of distribution from which initial radii correSponding to cell energies are drawn, in units of microns*/
	double radius_dist_sd; 				/**< standard deviation of distribution from which initial radii correSponding to cell energies are drawn, in units of microns*/
	double radius_division_threshold;	/**< energy threshold above which division may occur, in units of microns (giving the radius which correSponds to this energy)*/
	double radius_min;					/**< radius correSponding to energy threshold below which objects will be destroyed*/
	double penalty_basic;				/**< energy penalty for (fraction of current energy required to) carry out essential biochemical processes, given per dt * sf*/
	double penalty_active;				/**< energy penalty for (fraction of current energy required to) carry out active movement (exerting maximum force; actual penalty is a fraction of this quantity)*/
	double penalty_computation;			/**< energy penalty for (fraction of current energy required to) carry out biochemical computation*/

	double rep_coeff = 0;//0.5e-15;
	double att_coeff = 0;//0.5e-15;
	double sig_norm;
	double energy_mod_scale = 1.00e-5;

};

// FUNCTION IMPORT_PARAMETERS
// read contents of file sysparamsfile and populate parameters data structure
// with values of simulation parameters

inline parameters import_parameters(std::string arg_rootdir){

	std::string sysparamsfile = arg_rootdir + "/cfg/parameters.csv";

	std::vector<double> values; // vector to temporarily hold imported values

	std::string line;
	std::string::size_type sz;

	// open filestream
	std::ifstream file(sysparamsfile);

	if (file.is_open())
	{
		while ( getline(file, line) )
		{
			values.push_back(std::stod(line.substr(0,line.size()-1), &sz));
			// P2S(values.back());
		} file.close();
	}

	// create structure

	parameters sysparams;
	sysparams.rootdir = arg_rootdir;


	// independent values

	sysparams.timesteps = values.at(0);
	sysparams.batch_save_size = values.at(1);
	sysparams.nBoxes = static_cast<int>(values.at(2));
	sysparams.domains_per_syslength = sysparams.nBoxes * 2;
	sysparams.radius_dist_center = values.at(3);
	sysparams.radius_dist_sd = values.at(4);
	sysparams.radius_division_threshold = values.at(5);
	sysparams.radius_min = values.at(6);
	sysparams.penalty_basic = values.at(7);
	sysparams.penalty_active = values.at(8);
	sysparams.penalty_computation = values.at(9);
	sysparams.sf = values.at(10);
	sysparams.sf_interparticle = values.at(11);
	sysparams.vdistance_threshold = values.at(12);
	sysparams.nCells_init = values.at(13);
	sysparams.ui1 = values.at(14);
	sysparams.ui2 = values.at(15);
	sysparams.sig_threshold = 20.0;
	sysparams.sig_norm = 2.00;


	// dependent values

	sysparams.dt = 1.00e-8 * sysparams.sf;
	sysparams.diffusion_constant_max = (sysparams.T * sysparams.kb) / (6.00 * M_PI * sysparams.visc_h2o * sysparams.radius_min * 1.00e-6);
	sysparams.interaction_length = 0.20 /*1.00e6 * sqrt(4.00 * sysparams.diffusion_constant_max * sysparams.ui1 * sysparams.dt)*/;
	sysparams.subdomain_length = sysparams.interaction_length * 20.0;
	sysparams.subd_per_dlength = 10;
	sysparams.subd_per_dlength_side = sysparams.subd_per_dlength - 2;
	sysparams.Domain_length = sysparams.subdomain_length * sysparams.subd_per_dlength;
	sysparams.max_x = static_cast<double>(sysparams.nBoxes) * sysparams.subdomain_length * sysparams.subd_per_dlength;
	sysparams.min_x = -1.00 * sysparams.max_x;
	sysparams.length = sysparams.max_x - sysparams.min_x;
	sysparams.mpf = 1.1e3 * (4*M_PI/3) * sysparams.sf;


	sysparams.t_mix = 10000; //static_cast<int>((1.00/sysparams.dt) * pow(0.5*sysparams.Domain_length, 2) / (4.00 * sysparams.diffusion_constant_max * 0.50 / sysparams.radius_min));

	P2S(sysparams.diffusion_constant_max);
	P2S(sysparams.interaction_length);
	P2S(sysparams.Domain_length);
	P2S(sysparams.t_mix);

	return sysparams;
};

#endif


	// double remaining_basic;				// proportion of energy remaining after applying penalty_basic
	// double remaining_active;			// proportion of energy remaining after applying penalty_active
	// double remaining_computation;		// proportion of energy remaining after applying penalty_computation
