#!/bin/bash
#PBS -V
#PBS -M email@cinvestav.mx
#PBS -m a
#PBS -N SOLVE
#PBS -q cpar
#PBS -l nodes=4:ppn=8
#PBS -o /home/cpar/armando/ProyectoMPI/Code/Tiempos/MPI/o
#PBS -e /home/cpar/armando/ProyectoMPI/Code/Tiempos/MPI/e
#PBS -t 1-50
cd $PBS_O_WORKDIR

mpirun -n 1 ./VCA_mpi 2000 2 9
mpirun -n 1 ./VCA_mpi 2000 2 9
mpirun -n 1 ./VCA_mpi 2000 2 9
mpirun -n 1 ./VCA_mpi 2000 2 9
mpirun -n 1 ./VCA_mpi 2000 2 9

mpirun -n 2 ./VCA_mpi 2000 2 9
mpirun -n 2 ./VCA_mpi 2000 2 9
mpirun -n 2 ./VCA_mpi 2000 2 9
mpirun -n 2 ./VCA_mpi 2000 2 9
mpirun -n 2 ./VCA_mpi 2000 2 9

mpirun -n 4 ./VCA_mpi 2000 2 9
mpirun -n 4 ./VCA_mpi 2000 2 9
mpirun -n 4 ./VCA_mpi 2000 2 9
mpirun -n 4 ./VCA_mpi 2000 2 9
mpirun -n 4 ./VCA_mpi 2000 2 9

mpirun -n 8 ./VCA_mpi 2000 2 9
mpirun -n 8 ./VCA_mpi 2000 2 9
mpirun -n 8 ./VCA_mpi 2000 2 9
mpirun -n 8 ./VCA_mpi 2000 2 9
mpirun -n 8 ./VCA_mpi 2000 2 9

mpirun -n 16 ./VCA_mpi 2000 2 9
mpirun -n 16 ./VCA_mpi 2000 2 9
mpirun -n 16 ./VCA_mpi 2000 2 9
mpirun -n 16 ./VCA_mpi 2000 2 9
mpirun -n 16 ./VCA_mpi 2000 2 9

mpirun -n 32 ./VCA_mpi 2000 2 9
mpirun -n 32 ./VCA_mpi 2000 2 9
mpirun -n 32 ./VCA_mpi 2000 2 9
mpirun -n 32 ./VCA_mpi 2000 2 9
mpirun -n 32 ./VCA_mpi 2000 2 9