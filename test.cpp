#include <algorithm>
#include <array>
#include <cmath>
#include <iostream>
#include <fstream>
#include <omp.h>
#include <random>
#include "./src/universal.h"

using namespace std;

int main(int argc, char* argv[])
{

	double rawdt = 1e-8;											// "raw" timestep size (before scaling)

	const int num_obj = 80000;                       				// number of random walkers
	const int num_ts = 100000;                         				// number of timesteps
	double sf = 1e5;                              					// scaling factor for mass and timestep
	double dt = rawdt * sf;											// effective timestep size

	double r = 0.50e-6;                              				// radius of spherical cell in meters
	double m = sf * 1100 * (4*M_PI/3) * pow(r,3);   			 	// mass of cell in kg
	double I = 0.4*m*pow(r,2);										// moment of inertia of spherical cell
	double kbt = 298 * 1.38e-23;                     				// (Boltzmann's constant * temperature) in J
P2S(I);
	// constants for translational motion
	double alpha_trans = 6.00 * M_PI * 8.94e-4 * r;        			// friction coefficient
	double b_trans = 1/(1 + (alpha_trans*dt/(2*m)));				// constant that appears frequently in integration
	double randamp_trans = sqrt(2) * sqrt(2*alpha_trans*kbt*dt);	// stdev of amplitude of random force
	double trans_diff_const = kbt/(alpha_trans);					// translational diffusion constant
P2S(randamp_trans);
	// constants for rotational motion
	double alpha_rot = 8.00 * M_PI * 8.94e-4 * pow(r,3);  			// rotational friction coefficient
	double b_rot = 1/(1 + (alpha_rot*dt/(2*I)));					// constant that appears frequently in integration
	double randamp_rot = sqrt(2*alpha_rot*kbt*dt);					// stdev of amplitude of random force
	double rot_diff_const = kbt/(alpha_rot);						// translational diffusion constant

	// magnitude of random impulse
	double beta_trans;
	double beta_rot;

	// hold running totals (before dividing by total number of objects to get average)
	double sum_square_displacement_trans = 0, sum_square_displacement_rot = 0, sum_square_vel_trans = 0, sum_square_vel_rot = 0;

	// cout << rot_diff_const << endl;
	ofstream rec("rec.csv");

	normal_distribution<double> nrand(0.0, 1.0);
	uniform_real_distribution<double> urand(0, 2*M_PI);
	srand(time(NULL)); std::random_device rd;
	mt19937 rng; rng.seed(rd());

	// translational motion - initialization

		// position
		array<double,num_obj> pos_trans;
		fill(pos_trans.begin(), pos_trans.end(), 0);
		auto pos_trans_prev = pos_trans;

		// velocity
		array<double,num_obj> vel_trans;
		fill(vel_trans.begin(), vel_trans.end(), 0);
		auto vel_trans_prev = vel_trans;
		for (size_t i = 0; i < vel_trans_prev.size(); ++i)
		{
			vel_trans_prev[i] = nrand(rng) * sqrt(2*kbt/m);
			sum_square_vel_trans += pow(vel_trans_prev[i],2);
		}

		// cout << (0.5*m*sum_square_vel_trans)/num_obj << endl;
		
		// force
		array<double,num_obj> f_trans;
		fill(f_trans.begin(), f_trans.end(), 0);
		auto f_trans_prev = f_trans;



	// rotational motion - initialization

		// position
		array<double,num_obj> pos_rot;
		fill(pos_rot.begin(), pos_rot.end(), 0);
		auto pos_rot_prev = pos_rot;
		// for (size_t i = 0; i < pos_rot_prev.size(); ++i)
		// {
		// 	pos_rot_prev[i] = urand(rng);
		// }

		// angular velocity
		array<double,num_obj> vel_rot;
		fill(vel_rot.begin(), vel_rot.end(), 0);
		auto vel_rot_prev = vel_rot;
		for (size_t i = 0; i < vel_rot_prev.size(); ++i)
		{
			vel_rot_prev[i] = 0;//nrand(rng) * sqrt(kbt/I);
			sum_square_vel_rot += pow(vel_rot_prev[i],2);
		}

		// cout << (0.5*m*sum_square_vel_rot)/num_obj << endl;
		
		// torque
		array<double,num_obj> t_rot;
		fill(t_rot.begin(), t_rot.end(), 0);
		auto t_rot_prev = t_rot;


	// propagate

	for (int i = 1; i < num_ts; ++i)
	{

		sum_square_displacement_trans = 0;
		sum_square_displacement_rot = 0;
		sum_square_vel_trans = 0;
		sum_square_vel_rot = 0;

     	
		// #pragma omp parallel for reduction(+:sum_square_vel_trans,sum_square_displacement_trans,sum_square_vel_rot,sum_square_displacement_rot)
		for (size_t j = 0; j < num_obj; ++j)
		{
			
			// translational motion

				// select impulse
				beta_trans = nrand(rng) * randamp_trans;

				// update position
				pos_trans[j] = pos_trans_prev[j] + b_trans*dt*(vel_trans_prev[j] + (dt*f_trans_prev[j] + beta_trans)/(2*m));
//				std::cout << (b_trans*dt*(vel_trans_prev[j] + (dt*f_trans_prev[j] + beta_trans)/(2*m))) << std::endl;
				// update velocity
				vel_trans[j] = vel_trans_prev[j] + (0.5*dt*(f_trans_prev[j] + f_trans[j]) - alpha_trans*(pos_trans[j] - pos_trans_prev[j]) + beta_trans)/m;

				// get squared displacement
				sum_square_displacement_trans += pow(pos_trans[j],2);
				sum_square_vel_trans += pow(vel_trans_prev[j],2);

				// shift containers (current -> previous) in preparation for next timestep
				pos_trans_prev[j] = pos_trans[j];
				vel_trans_prev[j] = vel_trans[j];
				f_trans_prev[j] = f_trans[j];


			//rotational motion

				// select impulse
				beta_rot = nrand(rng) * randamp_rot;

				// update position
				pos_rot[j] = pos_rot_prev[j] + b_rot*dt*(vel_rot_prev[j] + (dt*t_rot_prev[j] + beta_rot)/(2*I));
				// pos_rot[j] = fmod(pos_rot[j], 2*M_PI);

				// update velocity
				vel_rot[j] = vel_rot_prev[j] + (0.5*dt*(t_rot_prev[j] + t_rot[j]) - alpha_rot*(pos_rot[j] - pos_rot_prev[j]) + beta_rot)/I;

				// get squared displacement
				sum_square_displacement_rot += pow(pos_rot[j],2);
				sum_square_vel_rot += pow(vel_rot_prev[j],2);

				// shift containers (current -> previous) in preparation for next timestep
				pos_rot_prev[j] = pos_rot[j];
				vel_rot_prev[j] = vel_rot[j];
				t_rot_prev[j] = t_rot[j];

		}


		// take average of statistics and export to csv with columns C0-C6
		rec << (i*dt) << "," 										// C0: time
			<< (i*dt*4*trans_diff_const) << ","						// C1: expected MSD_trans
			<< (sum_square_displacement_trans/num_obj) << "," 		// C2: experimental MSD_trans
			<< (i*dt*2*rot_diff_const) << ","						// C3: expected MSD_rot
			<< (sum_square_displacement_rot/num_obj) << "," 		// C4: experimental MSD_rot
			<< (0.5*m*sum_square_vel_trans)/num_obj << ","			// C5: translational kinetic energy
			<< (0.5*I*sum_square_vel_rot)/num_obj << endl;			// C6: rotational kinetic energy
	}

	return 0;

}

/* rm test.out; g++ test.cpp -I /usr/local/include/eigen -fopenmp -std=c++11 -ggdb -O0 -o test.out; gdb test.out */
