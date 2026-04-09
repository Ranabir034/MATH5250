# make all        -> build both
# make run_openmp -> test OpenMP  (10M samples, 4 threads)
# make run_mpi    -> test MPI     (10M samples, 4 procs)
# make clean      -> remove executables

CC    = gcc
MPICC = mpicc

all: mc_openmp mc_mpi

mc_openmp: mc_openmp.c
	$(CC) -O2 -fopenmp -o mc_openmp mc_openmp.c -lm

mc_mpi: mc_mpi.c
	$(MPICC) -O2 -o mc_mpi mc_mpi.c -lm

run_openmp: mc_openmp
	./mc_openmp 10000000 4

run_mpi: mc_mpi
	mpirun -np 4 ./mc_mpi 10000000

clean:
	rm -f mc_openmp mc_mpi

.PHONY: all run_openmp run_mpi clean