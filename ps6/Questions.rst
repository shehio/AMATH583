
Questions
=========

Norm
----

* Look through the code for ``run()`` in ``norm_utils.hpp``.  How are we setting the number of threads for OpenMP to use?

* Which version of ``norm`` provides the best parallel performance?  How do the results compare to the parallelized versions of ``norm`` from ps5?


* Which version of ``norm`` provides the best parallel performance for larger problems (i.e., problems at the top end of the default sizes in the drivers or larger)?  How do the results compare to the parallelized versions of ``norm`` from ps5?


* Which version of ``norm`` provides the best parallel performance for small problems (i.e., problems smller than the low end of the default sizes in the drivers)?  How do the results compare to the parallelized versions of ``norm`` from ps5?  


Sparse Matrix-Vector Product
----------------------------

* How does ``pmatvec.cpp`` set the number of OpenMP threads to use?

* (For discussion on Piazza.)
What characteristics of a matrix would make it more or less likely to exhibit an error 
if improperly parallelized?  Meaning, if, say, you parallelized ``CSCMatrix::matvec`` with just basic  columnwise partitioning -- there would be potential races with the same locations in ``y`` being read and written by multiple threads.  But what characteristics of the matrix give rise to that kind of problem?  Are there ways to maybe work around / fix that if we knew some things in advance about the (sparse) matrix?

* Which methods did you parallelize?  What directives did you use?  How much parallel speedup did you see for 1, 2, 4, and 8 threads?


Sparse Matrix Dense Matrix Product (AMATH583 Only)
--------------------------------------------------


* Which methods did you parallelize?  What directives did you use?  How much parallel speedup did you see for 1, 2, 4, and 8 threads?  How does the parallel speedup compare to sparse matrix by vector product?


PageRank Reprise
----------------

* Describe any changes you made to pagerank.cpp to get parallel speedup.  How much parallel speedup did you get for 1, 2, 4, and 8 threads?

* (EC) Which functions did you parallelize?  How much additional speedup did you achieve?


Load Balanced Partitioning with OpenMP (Extra Credit)
-----------------------------------------------------

* Are there any choices for scheduling that make an improvement in the parallel performance (most importantly, scalability) of pagerank?