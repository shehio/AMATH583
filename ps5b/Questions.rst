
pnorm
-----

* What was the data race?

* What did you do to fix the data race?  Explain why the race is actually eliminated (rather than, say, just made less likely).

* How much parallel speedup do you see for 1, 2, 4, and 8 threads?


fnorm
-----

* How much parallel speedup do you see for 1, 2, 4, and 8 threads for ``partitioned_two_norm_a``?

* How much parallel speedup do you see for 1, 2, 4, and 8 threads for ``partitioned_two_norm_b``?  

* Explain the differences you see between ``partitioned_two_norm_a`` and ``partitioned_two_norm_b``.


cnorm
-----

* How much parallel speedup do you see for 1, 2, 4, and 8 threads?

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

* How much parallel speedup do you see for the methods that you implemented for 1, 2, 4, and 8 threads?



Conundrum #2
------------

1. What are the two "matrix vector" operations that we could use?

2. How would we use the first in pagerank?  I.e., what would we have to do differently in the rest of pagerank.cpp to use that first operation?

3. How would we use the second?
