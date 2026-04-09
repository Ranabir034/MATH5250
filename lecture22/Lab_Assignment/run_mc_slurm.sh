#!/bin/bash

# Submit with:  sbatch run_monte_carlo.sh
# Output goes to: slurm-%j.out

#SBATCH --nodes=2
#SBATCH --ntasks-per-node=32
#SBATCH --time=0-8:0:0
#SBATCH --mem=2G
#SBATCH --mail-user=ranabir@iastate.edu
#SBATCH --mail-type=BEGIN,END,FAIL
#SBATCH --job-name=monte_carlo_pi

module load openmpi

# Number of samples
N=100000000

echo "========================================"
echo "  Monte Carlo pi -- OpenMP vs MPI"
echo "  Samples = $N"
echo "========================================"

# --- Build both programs ---
make all

echo ""
echo "--- OpenMP: 1 thread ---"
./mc_openmp $N 1

echo "--- OpenMP: 4 threads ---"
./mc_openmp $N 4

echo "--- OpenMP: 8 threads ---"
./mc_openmp $N 8

echo "--- OpenMP: 16 threads ---"
./mc_openmp $N 16

echo "--- MPI: 1 process ---"
mpirun -np 1 ./mc_mpi $N

echo "--- MPI: 4 processes ---"
mpirun -np 4 ./mc_mpi $N

echo "--- MPI: 8 processes ---"
mpirun -np 8 ./mc_mpi $N

echo "--- MPI: 16 processes ---"
mpirun -np 16 ./mc_mpi $N

echo ""
echo "========================================"
echo "  Done"
echo "========================================"