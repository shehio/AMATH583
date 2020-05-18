
pnorm
-----

* What was the data race?
The double variable partial was being updated by many threads at the same time.

* What did you do to fix the data race?  Explain why the race is actually eliminated (rather than, say, just made less likely).
Inside the loop, each of the threads can update their local partials, while we lock only the operation where we update the global partial (the variable) that's being passed by value so that we minimize blocked threads.

* How much parallel speedup do you see for 1, 2, 4, and 8 threads?
For lower N = 1048576, a lot of parallelism benefits can be reaped. These benefits are squandered away when we try larger numbers.

           N  Sequential    1 thread   2 threads   4 threads   8 threads      1 thread     2 threads     4 threads     8 threads
     1048576     5.84293     5.52365     9.27364     10.6403     10.6403             0             0   1.92318e-16             0
     2097152     3.98214     3.61629     5.04143     4.43035      4.0451             0   5.43881e-16   4.07911e-16   9.51792e-16
     4194304     3.79919     3.55449     4.04856     3.42672     3.43795             0    9.6159e-16   1.92318e-16   5.76954e-16
     8388608       3.813     3.59907     3.90867     3.54065     3.59907             0    1.3595e-16   6.79751e-16             0
    16777216     3.60247     3.21755      3.7884     3.51618     3.64722             0   3.84567e-16   1.34599e-15   3.84567e-16
    33554432     3.87913      3.6873       3.813     3.65716     3.95923             0   7.20652e-15   7.61444e-15   6.66264e-15

fnorm
-----

* How much parallel speedup do you see for 1, 2, 4, and 8 threads for ``partitioned_two_norm_a``?
For small Ns like 1048576, the spead up is tremendous. It's around 2x for 2/4/8 threads. This improvement wears off after increasing the input number N. For memory bound work, parallelism doesn't seem to help much.

           N  Sequential    1 thread   2 threads   4 threads   8 threads      1 thread     2 threads     4 threads     8 threads
     1048576     5.05414     5.34829     9.91007     11.6187     11.4867             0             0   1.92318e-16             0
     2097152     4.26421     3.92111     5.06639      4.1943     3.90615             0   5.43881e-16   4.07911e-16   9.51792e-16
     4194304     3.67921     3.46065     3.98698     3.46065     3.48364             0    9.6159e-16   1.92318e-16   5.76954e-16
     8388608     3.62299     3.42931     3.78652      3.3658     3.56379             0    1.3595e-16   5.43801e-16             0
    16777216     3.65858     3.54805       3.813     3.67002     3.91468             0   3.84567e-16   1.34599e-15   3.84567e-16
    33554432     3.62751     3.41521     4.12978     3.70767     3.89037             0   7.20652e-15   7.61444e-15   6.66264e-15


* How much parallel speedup do you see for 1, 2, 4, and 8 threads for ``partitioned_two_norm_b``?
There's not much improvements after adding threads to the problem. Each row one of three (2, 4, 8) is better. No one consistently beats the others.

           N  Sequential    1 thread   2 threads   4 threads   8 threads      1 thread     2 threads     4 threads     8 threads
     1048576     4.97944     5.15728     5.26473     5.58468     5.58468             0   1.15258e-15   1.34467e-15   1.34467e-15
     2097152     4.02917      4.0451     4.06115     3.98214     3.90615             0   2.71928e-15   2.03946e-15   2.03946e-15
     4194304     3.75834     3.20665     3.50694     3.49525     3.71835             0   9.61294e-16   3.84518e-16             0
     8388608     3.68419     3.44012     3.49525     3.40787     3.09807             0   1.49582e-15   1.08787e-15   5.43933e-16
    16777216     2.83673     3.36506     3.64722     3.48488     3.52674             0   5.00099e-15   4.03926e-15   3.84691e-15
    33554432     3.69746     3.56015     3.47714     3.28965     3.46816             0   3.67179e-15   4.62374e-15   5.57568e-15


* Explain the differences you see between ``partitioned_two_norm_a`` and ``partitioned_two_norm_b``.
From cppreference.com
when specifying launch::async, a new thread is launched to execute the task asynchronously.
when specifying std::launch::deferred,  the task is executed on the calling thread the first time its result is requested (lazy evaluation).

So, for measuring perf it's probably better to launch the work right away to get the benefit of the few milliseconds from the line calling launch to the line when the data is actually needed.

cnorm
-----

* How much parallel speedup do you see for 1, 2, 4, and 8 threads?
cnorm seems like it was worse than the other ones (worse than sequential even) in almost all cases.
The speedup is around -1.5x for all the threads.

           N  Sequential    1 thread   2 threads   4 threads   8 threads      1 thread     2 threads     4 threads     8 threads
     1048576     6.82991     1.65981     2.76939     3.15884     3.96403   1.65393e-14   1.00005e-14    9.6159e-16   2.30782e-15
     2097152     4.67311     1.31375     2.36353     2.62413     3.21827   8.15822e-15    8.7021e-15   4.21508e-15   4.89493e-15
     4194304      2.7962     1.23072      2.7962     3.64089     3.21649   3.82713e-14   3.07709e-15   2.69245e-15   2.30782e-15
     8388608     3.29462     1.51461     2.48977     4.17823     3.77342   1.41388e-14   1.22355e-15    2.1752e-15   7.34131e-15
    16777216     4.06369     1.54324      2.7962     3.98103       4.092   4.74941e-14   1.17293e-14   2.26895e-14   3.84567e-15
    33554432     3.57914     1.53392     2.77883     4.01849     3.56962   1.61807e-14     2.937e-14   1.31893e-14   7.47847e-15

* How does the performance of cyclic partitioning compare to blocked?  Explain any significant differences, referring to, say, performance models or CPU architectural models.


rnorm
-----

* How much parallel speedup do you see for 1, 2, 4, and 8 threads?

* What will happen if you use ``std:::launch::deferred`` instead of ``std:::launch::async`` when launching tasks?  When will the computations happen?  Will you see any speedup?  For your convenience, the driver program will also call ``recursive_two_norm_b`` -- which you can implement as a copy of ``recursive_two_norm_a`` but with the launch policy changed.


General
-------

* For the different approaches to parallelization, were there any major differences in how much parallel speedup that you saw?

* You may have seen the speedup slowing down as the problem sizes got larger -- if you didn't keep trying larger problem sizes.  What is limiting parallel speedup for two_norm (regardless of approach)?  What would determine the problem sizes where you should see ideal speedup?  (Hint: Roofline model.)


Conundrum #1
------------

1. What is causing this behavior?

2. How could this behavior be fixed?

3. Is there a simple implementation for this fix?


make: `pnorm.exe' is up to date.
           N  Sequential    1 thread   2 threads   4 threads   8 threads      1 thread     2 threads     4 threads     8 threads
     1048576     6.39764     6.08932     10.3146     12.9593     11.7538             0             0   1.92318e-16             0
     2097152     4.78229     4.37355     4.39232     5.11705     4.67311             0   5.43881e-16   4.07911e-16   9.51792e-16
     4194304     4.12825     3.70522     4.48109     3.86928     3.43795             0    9.6159e-16   1.92318e-16   5.76954e-16
     8388608     3.95116     3.68419      4.3447     3.76041     3.67178             0    1.3595e-16   6.79751e-16    1.3595e-16
    16777216     3.90168     3.70475     4.28615       3.813     3.92778             0   3.84567e-16   1.34599e-15   3.84567e-16
    33554432     3.92449      3.7491     3.89037     3.97094     4.20745             0   7.20652e-15   7.47847e-15   6.66264e-15
shehios-MBP:ps5b shehio$ ./pnorm.exe 128 256
           N  Sequential    1 thread   2 threads   4 threads   8 threads      1 thread     2 threads     4 threads     8 threads
         128     18.1818   0.0116568  0.00820851  0.00411896  0.00222947             0             0             0             0
         256     27.7778   0.0224684   0.0166653   0.0094647  0.00455281             0             0   1.94081e-16   1.94081e-16


Parallel matvec
---------------

* Which methods did you implement?
CSR -> matvec
CSC -> t_matvec

* How much parallel speedup do you see for the methods that you implemented for 1, 2, 4, and 8 threads?
I see all the numbers detoriarating which might be because: thread overhead and threads trying to insert different portions of the array at the same time.


Conundrum #2
------------

1. What are the two "matrix vector" operations that we could use?

2. How would we use the first in pagerank?  I.e., what would we have to do differently in the rest of pagerank.cpp to use that first operation?

3. How would we use the second?
