
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



Parallel matvec
---------------

* Which methods did you implement?

* How much parallel speedup do you see for the methods that you implemented for 1, 2, 4, and 8 threads?



Conundrum #2
------------

1. What are the two "matrix vector" operations that we could use?

2. How would we use the first in pagerank?  I.e., what would we have to do differently in the rest of pagerank.cpp to use that first operation?

3. How would we use the second?
