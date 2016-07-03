#include "Domain.h"


#include "universal.h"


void Domain::updatePositions(parameters& sysparams, std::mt19937& rng)
{

    // containers for quantities at current and previous timestep, and for base force (not including)
    std::array<double,2> x, v, f, xp, vp, fp, f_existing;
    double th, vth, tth, thp, vthp, tthp, active_force, theta_existing_force;

    // constants used mutiple times; calculated once for efficiency
    double r;                                   // radius of current cell in meters
    double m;                                   // mass of current cell in kg
    double I;                                   // moment of inertia of current cell kg m2

    // constants for translational motion
    double d_trans;                             // damping constant
    double b_trans;                             // constant appearing frequently in integration
    double randamp_trans;                       // stdev of amplitude of random force
    double beta_trans_0, beta_trans_1;          // magnitude of random impulse

    // constants for rotational motion
    double d_rot;                               // damping constant
    double b_rot;                               // constant appearing frequently in integration
    double randamp_rot;                         // stdev of amplitude of random force
    double beta_rot;                            // magnitude of random impulse

    std::normal_distribution<double> nrand(0.0, 1.0);

	for (auto& op : this->all_objects)
    {

        op->getr(r); r *= 1.00e-6;

        m = sysparams.mpf * pow(r,3);
        I = 0.4*m*pow(r,2);

        // constants for translational motion
        d_trans = sysparams.dtpf * r;
        b_trans = 1/(1 + (d_trans*sysparams.dt/(2*m)));
        randamp_trans = sqrt(2*d_trans*sysparams.kbt*sysparams.dt);

        // constants for rotational motion
        d_rot = sysparams.drpf * pow(r,3);
        b_rot = 1/(1 + (d_rot*sysparams.dt/(2*I)));
        randamp_rot = sqrt(2*d_rot*sysparams.kbt*sysparams.dt);

        op->getIPf(f_existing);

        // run through innermost loop
        for (int inner_ts = 0; inner_ts < sysparams.ui1; ++inner_ts)
        {
            // random impulses
            beta_trans_0 = nrand(rng) * randamp_trans;
            beta_trans_1 = nrand(rng) * randamp_trans;
            beta_rot = nrand(rng) * randamp_rot;
// TRAP;
            // get quantities at previous timestep
            op->getx(xp); op->getv(vp); op->getf(fp);
            op->getth(thp); op->getvth(vthp); op->gettth(tthp);

            // update rotational coordinate
            op->setth(b_rot*sysparams.dt*(vthp + (sysparams.dt*tthp + beta_rot)/(2*I)));
            op->getth(th);

            // update rotational velocity
            op->setvth((0.5*sysparams.dt*(tthp + tth) - d_rot*(th - thp) + beta_rot)/I);
            op->getvth(vth);
            // update net force
            theta_existing_force = atan2(f_existing[1],f_existing[0]);
            if (std::fabs(theta_existing_force - th) > M_PI){
                active_force = op->spNetwork->nodeValue.at(3);
            } else {
                active_force = 0;
            }

            // account for changes in energy
            double energyRatioChangeNutr = std::max(pow(r,2) * (1 - op->sumSurfArea / 3.00),0.00);
            double energyRatioChangeComp = static_cast<double>(op->spNetwork->nn) / 5.00;
            double energyRatioChangeActive = active_force;

            double energyRatioNet = cbrt(
                1 + sysparams.energy_mod_scale * (5.00*energyRatioChangeNutr - 1 - 0.5*energyRatioChangeComp - energyRatioChangeActive));

            op->setr(energyRatioNet);


            active_force *= 2*randamp_trans;

            op->setf(f_existing[0] + active_force * cos(th), f_existing[1] + active_force * sin(th));
            op->getf(f);

            // update translational coordinates
            op->setx(1.00e6*(b_trans*sysparams.dt*(vp[0] + (sysparams.dt*fp[0] + beta_trans_0)/(2*m))),
                1.00e6*(b_trans*sysparams.dt*(vp[1] + (sysparams.dt*fp[1] + beta_trans_1)/(2*m))));
            op->getx(x);

            // update translational velocity
            op->setv((0.5*sysparams.dt*(fp[0] + f[0]) - d_trans*1.00e-6*(x[0] - xp[0]) + beta_trans_0)/m,
                (0.5*sysparams.dt*(fp[1] + f[1]) - d_trans*1.00e-6*(x[1] - xp[1]) + beta_trans_1)/m);

            // adjust positions to enforce periodic boundary conditions
            op->wrapx(sysparams);
            op->getx(x);

            if (std::abs(xp[0]) > sysparams.max_x){ TRAP; }
            if (std::abs(xp[1]) > sysparams.max_x){ TRAP; }
        }
	}
}
