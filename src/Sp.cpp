#include "Sp.h"


#include "Network.h"
#include "universal.h"


// default constructor
Sp::Sp(int Sptype, int identifier, std::array<double,2> position, std::array<double,2> velocity, double orientation, double ang_velocity, double radius)
{

	// object Sptype: may be 1 (active/dynamic) or 2 (passive/static)
	this->type = Sptype;

	// object identifier: every object created in the simulation has a unique
	// identifier; this number is never reused even when an object is destroyed
	this->id = identifier;

	// position, velocity, and force/torque data
	
	//translational
	this->x = position;
	this->v = velocity;
	this->f = {{0,0}};
	
	// rotational
	this->th = 0;
	this->vth = 0;
	this->tth = 0;

	this->sumSurfArea = 0;
	
	this->ip_force = {{0,0}};
	this->sig_self = 0;
	this->sig_self_prev = 0;
	this->sig_nonself = 0;
	this->sig_nonself_prev = 0;

	// radius of object in microns; need to convert to meters for integrating
	// equations of motion
	this->r = radius;

	// initialize network
	this->spNetwork = std::make_shared<Network>();

	this->mod = false;
	this->available = false;

};

// copy constructor
Sp::Sp(const Sp& origSp, int new_id){
	
	// object Sptype: may be 1 (active/dynamic) or 2 (passive/static)
	this->type = origSp.type;

	// object identifier: every object created in the simulation has a unique
	// identifier; this number is never reused even when an object is destroyed
	this->id = new_id;

	//translational
	this->x = origSp.x;
	this->v = origSp.v;
	this->f = origSp.f;
	
	// rotational
	this->th = origSp.th;
	this->vth = origSp.vth;
	this->tth = origSp.tth;

	this->sumSurfArea = origSp.sumSurfArea;

	this->ip_force = {{0,0}};
	this->sig_self = 0;
	this->sig_self_prev = 0;
	this->sig_nonself = 0;
	this->sig_nonself_prev = 0;

	// radius of object in microns; need to convert to meters for integrating equations of motion
	this->r = origSp.r;

	// initialize network
	this->spNetwork = std::make_shared<Network>(*(origSp.spNetwork));
	
	this->mod = false;
	this->available = false;
};

// destructor
Sp::~Sp() {

	// free memory associated with network

	spNetwork.reset();

};
