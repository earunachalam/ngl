#ifndef SP_H
#define SP_H

#include "distance.h"
#include "Network.h"
#include "parameters.h"
#include "universal.h"


class Sp
{

public:

	// properties
	
	// object Sptype; unique object identifier
	int type;
	int id;
	
	std::array<double,2> x;														/*!< (x,y) position of cell center of mass in Cartesian coordinates in microns*/
	std::array<double,2> v;														/*!< (x,y) velocity of cell center of mass in Cartesian coordinates in m/s*/
	std::array<double,2> f;														/*!< translational force in Cartesian coordinates in N*/
	double th;																	/*!< orientation of cell with reSpect to x-axis (ccw) in radians*/
	double vth;																	/*!< angular velocity of cell in radians/sec*/
	double tth;																	/*!< torque acting on cell in N m*/

	std::array<double,2> ip_force;
	double sig_self;
	double sig_self_prev;
	double sig_nonself;
	double sig_nonself_prev;

	// radius
	double r;

	// sum of surface areas of Neighboring cells
	double sumSurfArea;

	// biochemical network
	std::shared_ptr<Network> spNetwork;
	
	bool mod;																	/*!< "modified", true for the timestep immediately after mutation */
	
	bool available; 															/*!< available to participate in consumption or division event in current timestep */


	// constructors

	// default constructor
	Sp(int Sptype, int oid, std::array<double,2> position, std::array<double,2> velocity, double orientation, double ang_velocity, double radius);
	
	// copy constructor
	Sp(const Sp& origSp, int new_id);

	// destructor
	~Sp();

public:

	// object parameters
	int gettype()
	{
		return this->type;
	}

	int getid()
	{
		return this->id;
	}

	void setr(double value)
	{
		this->r *= value;
	}

	void getr(double& container)
	{
		container = this->r;
	}



	// translational coordinates

	void setx(double added_value_0, double added_value_1)
	{
		this->x[0] += added_value_0;
		this->x[1] += added_value_1;
	}

	void getx(std::array<double,2>& container)
	{
		container = this->x;
	}
	
	void setv(double added_value_0, double added_value_1)
	{
		this->v[0] += added_value_0;
		this->v[1] += added_value_1;
	}

	void getv(std::array<double,2>& container)
	{
		container = this->v;
	}

	void setf(double added_value_0, double added_value_1)
	{
		this->f[0] += added_value_0;
		this->f[1] += added_value_1;
	}

	void getf(std::array<double,2>& container)
	{
		container = this->f;
	}

	void getIPf(std::array<double,2>& container)
	{
		container = this->ip_force;
	}


	// rotational coordinates

	void setth(double added_value)
	{
		this->th += added_value;
	}

	void getth(double& container)
	{
		container = this->th;
	}
	
	void setvth(double added_value)
	{
		this->vth += added_value;
	}

	void getvth(double& container)
	{
		container = this->vth;
	}

	void settth(double value)
	{
		this->tth = value;
	}

	void gettth(double& container)
	{
		container = this->tth;
	}

	void wrapx(parameters& sysparams)
	{
		auto orig = this->x;
		distance::wrap(sysparams, this->x[0]);
		distance::wrap(sysparams, this->x[1]);
	    if (std::abs(x[0]) > sysparams.max_x){ TRAP; }
	    if (std::abs(x[1]) > sysparams.max_x){ TRAP; }
	}


	// evaluate active force

	void setActiveForce(parameters& sysparams)
	{
		this->sig_self = this->sig_self/sysparams.sig_norm;
		this->sig_nonself = this->sig_nonself/sysparams.sig_norm;

		this->spNetwork->run(this->sig_self - this->sig_self_prev, this->sig_nonself - this->sig_nonself_prev, this->r/sysparams.radius_division_threshold);

		this->sig_self_prev = this->sig_self;
		this->sig_nonself_prev = this->sig_nonself;
	}

};

#endif

