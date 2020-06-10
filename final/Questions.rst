

Final Questions
===============

Norm
----

* Per our discussions in lectures past about weak vs strong scaling, do
  the plots look like what you would expect? Describe any (significant)
  differences (if any).

For strong scaling, it's like I would expect yes. It seems that most sizes, the maximum GFLOPS is around 18.
Increasing as we increase the number of processors.

For weak scaling, it's a little surprising.
I'm not sure why for the same size of the problem per node, we would see performance regression.
That being said, it's at least consistent with the behavior from weak scaling in Grid.

* For strong scaling, at what problem size (and what number of nodes) does
  parallelization stop being useful?  Explain.
I don't think in the examples given we were able to hit the roof of the performance we can get using strong scaling.
We might have needed even more sizes (iterations) to learn where we can stop.
I even tried to increase the number N, and then I began to see some perf-regression at N=30.


Grid
----

* Per our discussions in lectures past about weak vs strong scaling, do
  the plots look like what you would expect? Describe any (significant)
  differences (if any).

For strong scaling, it's like I would expect yes. Parallelism is more useful for bigger problems, alas with a limit.
That is when the work to do work (setting up environments on different nodes) exceeds the actual work.

For weak scaling, it doesn't make much sense to me, as with the addition of extra nodes, we're regressing in performance.
This is consistent across different sizes of the problem. So, not a one off phenomenon.

* For strong scaling, at what problem size (and what number of nodes) does
  parallelization stop being useful?

It depends on the problem's size. So, for N=1024, it stops at 8 processes. For N=2048, it stops at 16.
And for N=4096, it stops at 32, might be even not stopping there.


Useful commands:
make pingpong.exe && srun -n 2 mpirun -np 2 pingpong.exe 1
make pingpong.exe && srun -N 2 -n 4 pingpong.exe 1
sbatch -N 4 -n 4 mpi_norm.bash
srun -N 8 hostname