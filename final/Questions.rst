

Final Questions
===============

Norm
----

* Per our discussions in lectures past about weak vs strong scaling, do
  the plots look like what you would expect? Describe any (significant)
  differences (if any).


* For strong scaling, at what problem size (and what number of nodes) does
  parallelization stop being useful?  Explain.


Grid
----

* Per our discussions in lectures past about weak vs strong scaling, do
  the plots look like what you would expect? Describe any (significant)
  differences (if any).

* For strong scaling, at what problem size (and what number of nodes) does
  parallelization stop being useful?


Useful commands:
make pingpong.exe && srun -n 2 mpirun -np 2 pingpong.exe 1
make pingpong.exe && srun -N 2 -n 4 pingpong.exe 1
sbatch -N 4 -n 4 mpi_norm.bash
srun -N 8 hostname