#!/bin/bash
#----------------------------------------------------
# Example SLURM job script to run applications on 
# TACC's Lonestar 5 system.
#
# Example of OMP job submission to normal queue
#----------------------------------------------------
#SBATCH -J omp_job6								# Job name
#SBATCH -o omp_job6.o%j		 						# Name of stdout output file
#SBATCH -e omp_job6.o%job							# Name of stderr output file
#SBATCH -p normal								# Queue name
#SBATCH -N 4									# Total number of nodes requested
#SBATCH -n 96									# Total number of mpi tasks requested
#SBATCH -t 48:00:00								# Run time (hh:mm:ss) - 48 hours
#SBATCH --mail-user=earunachalam@berkeley.edu					# Address email notifications
#SBATCH --mail-type=all								# Email at begin and end of job

# This example will run on 1 node with 24 OpenMP threads

# Please do set the number of threads by yourself!
export OMP_NUM_THREADS=48

# Launch the pure OpenMP application directly
/home1/04048/easun/ngl/bin/ngl.x /home1/04048/easun/ngl

#Note:  ibrun does not bind tasks or threads by default
#       To bind task/threads to sockets or cores, you must use
#       ibrun with tacc_affinity.
