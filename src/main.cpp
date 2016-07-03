#include "Kingdom.h"
#include "universal.h"

/*! \file Stuff */

int main(int argc, char *argv[])
{
    
	int starttime = time(0);
	std::string rootdir = argv[argc - 1];

    // #pragma omp parallel for
    for (unsigned int thread = 0; thread < 1/*omp_get_num_threads()*/; ++thread)
    {
    	INITIALIZE_TIMER();
        
        auto system = Kingdom(rootdir, thread); system.populate();
        // system.printdomains();

    	// export physical and network data
        std::string timestep_str = std::to_string(0);
        std::string current_filename = system.sysparams.sub1 + "/" + timestep_str + ".csv";
        std::ofstream current_file(current_filename);
        system.export_all(current_file);
        
    	int exp_t = 0;

        bool calculateActive, attemptChange;

        for (int t = 1; t < system.sysparams.timesteps; ++t)
        { 
        	if ((t % system.sysparams.ui2 == 0) || (t == 1)){ calculateActive = true; } else { calculateActive = false; }
            if ((t % 1 == 0) || (t == 1)){ attemptChange = true; } else { attemptChange = false; }
            // (10*system.sysparams.ui2)
            system.propagate(calculateActive, attemptChange);

        	// export physical and network data

        	if (t % 1 == 0)
        	{
    	    	std::string current_filename = system.sysparams.sub1 + "/" + std::to_string(++exp_t) + ".csv"; std::ofstream current_file(current_filename);
    		    system.export_all(current_file);
                
                int nObj = 0;
                for (auto & domain : system.Domains)
                {
                    nObj += domain->all_objects.size();
                }
    		    std::cout << "thr: " << thread << "\t ts: " << exp_t << "\t or: " << nObj << "\t et: " << time(0) - starttime << std::endl;
    		}
        }
    }
}
