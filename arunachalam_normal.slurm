#!/bin/bash
#----------------------------------------------------
# Example SLURM job script to run applications on 
# TACC's Lonestar 5 system.
#
# Example of serial job submission to normal queue
#----------------------------------------------------

#SBATCH -J normal_queue_job                     # Job name
#SBATCH -o normal_job.%j.out                    # Name of stdout output file (%j expands to jobId)
#SBATCH -p normal                               # Queue name
#SBATCH -N 1                                    # Total number of nodes requested
#SBATCH -n 1                                    # Total number of mpi tasks requested
#SBATCH -t 01:30:00                             # Run time (hh:mm:ss) - 1.5 hours
#SBATCH --mail-user=earunachalam@berkeley.edu   # Address email notifications
#SBATCH --mail-type=all                         # Email at begin and end of job
#SBATCH -A A-yourproject                        # <-- Allocation name to charge job against

# Launch the executable named "a.out"

./a.out