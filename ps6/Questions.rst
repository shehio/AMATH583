
Questions
=========

Norm
----

shehios-MBP:norm shehio$ ls
Makefile                        norm_block_critical.cpp         norm_cyclic_critical.cpp        norm_parfor.cpp
amath583.o                      norm_block_critical.exe         norm_cyclic_critical.exe        norm_seq.cpp
amath583IO.o                    norm_block_critical.o           norm_cyclic_critical.o          norm_seq.exe
amath583sparse.o                norm_block_reduction.cpp        norm_cyclic_reduction.cpp       norm_seq.o
shehios-MBP:norm shehio$ ./norm_block_critical.exe
           N  Sequential    1 thread   2 threads   4 threads   8 threads      1 thread     2 threads     4 threads     8 threads
     1048576      5.1701     5.48002     11.2987     20.7337      28.731             0   5.19496e-15   5.00255e-15   4.04052e-15
     2097152     4.69061     4.76805     7.22019     6.60671     5.34829             0   6.80033e-16   1.08805e-15   2.72013e-15
     4194304     4.29103     4.39232     5.15572     4.12665     4.20292             0   4.80808e-15   5.57737e-15   3.84646e-15
     8388608     4.51972     4.35998     4.55903     3.94202     3.97942             0   1.11505e-14   9.92669e-15   9.51874e-15
    16777216     4.39725     4.30185     4.38841     3.65333     3.95833             0   9.61626e-15   7.88533e-15   4.23115e-15
    33554432      4.0778     3.80682     3.96089      3.8192     4.20934             0   9.65326e-15   1.12848e-14   9.78922e-15
shehios-MBP:norm shehio$ make norm_block_reduction.exe && ./norm_block_reduction.exe
g++-9 -c  -fopenmp -Ofast -march=native -DNDEBUG   -std=c++11 -Wall -I../include  norm_block_reduction.cpp -o norm_block_reduction.o
g++-9  -fopenmp -Ofast -march=native -DNDEBUG   -std=c++11 -Wall -I../include  norm_block_reduction.o amath583.o amath583IO.o amath583sparse.o -o norm_block_reduction.exe -L/usr/local/lib -lomp
           N  Sequential    1 thread   2 threads   4 threads   8 threads      1 thread     2 threads     4 threads     8 threads
     1048576     5.13053     4.52966     7.34003     11.6928     11.6253             0   5.19496e-15   5.00255e-15   4.23293e-15
     2097152     4.12583     2.78465      5.1311     6.31767     4.52272             0   6.80033e-16   1.08805e-15   2.58412e-15
     4194304     4.29103     4.51837     5.73339     4.63082     4.40176             0   4.80808e-15   5.57737e-15   3.84646e-15
     8388608     4.17759     4.25386      4.8771     3.97188     3.54249             0   1.11505e-14   9.92669e-15   9.65473e-15
    16777216     3.46197     4.22682     4.82531     3.94401     4.21864             0   9.61626e-15   7.88533e-15   4.23115e-15
.    33554432     4.13523     4.50827     6.34814     4.27056     4.01506             0   9.65326e-15   1.12848e-14   9.78922e-15
shehios-MBP:norm shehio$ make norm_cyclic_critical.exe && ./norm_cyclic_critical.exe
g++-9 -c  -fopenmp -Ofast -march=native -DNDEBUG   -std=c++11 -Wall -I../include  norm_cyclic_critical.cpp -o norm_cyclic_critical.o
g++-9  -fopenmp -Ofast -march=native -DNDEBUG   -std=c++11 -Wall -I../include  norm_cyclic_critical.o amath583.o amath583IO.o amath583sparse.o -o norm_cyclic_critical.exe -L/usr/local/lib -lomp
           N  Sequential    1 thread   2 threads   4 threads   8 threads      1 thread     2 threads     4 threads     8 threads
     1048576     5.04052     5.32055     3.97464     2.88133     5.33467             0      0.414213      0.999999       1.82842
     2097152     3.43819     4.67976      3.4092     3.67574       3.553             0      0.414214             1       1.82842
     4194304     4.06115     4.60996     4.34569     4.29103     2.85869             0      0.414214             1       1.82843
     8388608     2.52365     2.61817     4.28865     3.62829     3.76508             0      0.414214             1       1.82843
    16777216     3.77342     4.15436     4.14646      4.0019     3.76041             0      0.414214             1       1.82843
    33554432     3.42392     3.72827     4.40677     4.02194     3.51618             0      0.414214             1       1.82843
shehios-MBP:norm shehio$ make norm_cyclic_reduction.exe && ./norm_cyclic_reduction.exe
g++-9 -c  -fopenmp -Ofast -march=native -DNDEBUG   -std=c++11 -Wall -I../include  norm_cyclic_reduction.cpp -o norm_cyclic_reduction.o
g++-9  -fopenmp -Ofast -march=native -DNDEBUG   -std=c++11 -Wall -I../include  norm_cyclic_reduction.o amath583.o amath583IO.o amath583sparse.o -o norm_cyclic_reduction.exe -L/usr/local/lib -lomp
           N  Sequential    1 thread   2 threads   4 threads   8 threads      1 thread     2 threads     4 threads     8 threads
     1048576     2.52659     3.01073     3.44969     4.45935     5.84642             0      0.414213      0.999999       1.82842
     2097152     4.42375     4.79065      4.4432     4.05955     3.34711             0      0.414214             1       1.82842
     4194304     4.67311      4.4593     3.44583     4.22025       3.833             0      0.414214             1       1.82843
     8388608     4.21962     4.40578     4.51972     4.39655     3.86216             0      0.414214             1       1.82843
    16777216     4.01664     4.27655     4.53438     4.37082     3.89471             0      0.414214             1       1.82843
    33554432     3.99458     4.30974     4.52565     4.41506     3.84421             0      0.414214             1       1.82843
shehios-MBP:norm shehio$ make norm_parfor.exe && ./norm_parfor.exe
g++-9 -c  -fopenmp -Ofast -march=native -DNDEBUG   -std=c++11 -Wall -I../include  norm_parfor.cpp -o norm_parfor.o
g++-9  -fopenmp -Ofast -march=native -DNDEBUG   -std=c++11 -Wall -I../include  norm_parfor.o amath583.o amath583IO.o amath583sparse.o -o norm_parfor.exe -L/usr/local/lib -lomp
           N  Sequential    1 thread   2 threads   4 threads   8 threads      1 thread     2 threads     4 threads     8 threads
     1048576      4.8579     4.52966     4.67714     4.33442     4.84619             0             0             0             0
     2097152     4.85975     4.99174     4.96721     4.97944     4.84809             0             0             0             0
     4194304     4.57902     4.60996     4.63082     4.57902     4.50841             0             0             0             0
     8388608     4.22813     4.33296     4.32402     4.43373     4.48109             0             0             0             0
    16777216     4.14646     4.31035     4.37959     4.21864     4.33606             0             0             0             0
    33554432     4.20181     4.00138     4.14984     4.23209     4.28615             0             0             0             0

* Look through the code for ``run()`` in ``norm_utils.hpp``.  How are we setting the number of threads for OpenMP to use?

* Which version of ``norm`` provides the best parallel performance?  How do the results compare to the parallelized versions of ``norm`` from ps5?


* Which version of ``norm`` provides the best parallel performance for larger problems (i.e., problems at the top end of the default sizes in the drivers or larger)?  How do the results compare to the parallelized versions of ``norm`` from ps5?


* Which version of ``norm`` provides the best parallel performance for small problems (i.e., problems smller than the low end of the default sizes in the drivers)?  How do the results compare to the parallelized versions of ``norm`` from ps5?  


Sparse Matrix-Vector Product
----------------------------

* How does ``pmatvec.cpp`` set the number of OpenMP threads to use?
#ifdef _OPENMP
    omp_set_num_threads(nthreads);
#endif

* (For discussion on Piazza.)
What characteristics of a matrix would make it more or less likely to exhibit an error 
if improperly parallelized?  Meaning, if, say, you parallelized ``CSCMatrix::matvec`` with just basic  columnwise partitioning -- there would be potential races with the same locations in ``y`` being read and written by multiple threads.  But what characteristics of the matrix give rise to that kind of problem?  Are there ways to maybe work around / fix that if we knew some things in advance about the (sparse) matrix?

* Which methods did you parallelize?  What directives did you use?  How much parallel speedup did you see for 1, 2, 4, and 8 threads?


Sparse Matrix Dense Matrix Product (AMATH583 Only)
--------------------------------------------------


* Which methods did you parallelize?  What directives did you use?  How much parallel speedup did you see for 1, 2, 4, and 8 threads?  How does the parallel speedup compare to sparse matrix by vector product?


BEFORE!

shehios-MBP:matvec shehio$ make pmatmat.exe && ./pmatmat.exe
g++-9 -c  -fopenmp -Ofast -march=native -DNDEBUG   -std=c++11 -Wall -I../include  pmatmat.cpp -o pmatmat.o
g++-9 -c  -fopenmp -Ofast -march=native -DNDEBUG   -std=c++11 -Wall -I../include  ../src/amath583IO.cpp -o amath583IO.o
g++-9 -c  -fopenmp -Ofast -march=native -DNDEBUG   -std=c++11 -Wall -I../include  ../src/amath583sparse.cpp -o amath583sparse.o
g++-9  -fopenmp -Ofast -march=native -DNDEBUG   -std=c++11 -Wall -I../include  pmatmat.o amath583.o amath583IO.o amath583sparse.o -o pmatmat.exe -L/usr/local/lib -lomp
1 threads   
 N(Grid) N(Matrix)         NNZ    NRHS         COO         CSR         CSC
      64      4096       20224       1    0.681153    0.614621    0.449468
     128     16384       81408       1    0.625152    0.686695    0.480189
     256     65536      326656       1    0.504053    0.666249    0.453139
     512    262144     1308672       1    0.523469    0.558643    0.429594
    1024   1048576     5238784       1    0.537311    0.544289    0.376722
    2048   4194304    20963328       1    0.523149    0.539497    0.375303
2 threads   
 N(Grid) N(Matrix)         NNZ    NRHS         COO         CSR         CSC
      64      4096       20224       1    0.623319    0.691851    0.460431
     128     16384       81408       1    0.662661    0.693886    0.466663
     256     65536      326656       1    0.598143    0.676293    0.457763
     512    262144     1308672       1    0.552096    0.525415    0.414477
    1024   1048576     5238784       1    0.547847    0.542528    0.385382
    2048   4194304    20963328       1    0.378204    0.467335    0.389756
4 threads   
 N(Grid) N(Matrix)         NNZ    NRHS         COO         CSR         CSC
      64      4096       20224       1    0.641474    0.699173    0.475337
     128     16384       81408       1    0.622217    0.634125    0.360142
     256     65536      326656       1    0.544867    0.653312    0.459325
     512    262144     1308672       1    0.554261    0.611847    0.432222
    1024   1048576     5238784       1    0.480347     0.46567    0.391685
    2048   4194304    20963328       1    0.588149    0.466592    0.390275
8 threads   
 N(Grid) N(Matrix)         NNZ    NRHS         COO         CSR         CSC
      64      4096       20224       1    0.451002    0.427649    0.337963
     128     16384       81408       1    0.509739    0.665991    0.473329
     256     65536      326656       1    0.580096    0.656499    0.371774
     512    262144     1308672       1    0.466457    0.484029    0.327927
    1024   1048576     5238784       1    0.441161    0.442325    0.390772
    2048   4194304    20963328       1    0.478771    0.498279    0.365488


PageRank Reprise
----------------

* Describe any changes you made to pagerank.cpp to get parallel speedup.  How much parallel speedup did you get for 1, 2, 4, and 8 threads?

* (EC) Which functions did you parallelize?  How much additional speedup did you achieve?

Parallel norm2 and norm1.
sort can be but too complicated.
std::swap can't be.

shehios-MBP:pagerank shehio$ make pagerank.exe && ./pagerank.exe  ./../data/cit-Patents_adj.mtx -n 8
make: `pagerank.exe' is up to date.
# elapsed time [read]: 30314 ms
Converged in 37 iterations
# elapsed time [pagerank]: 7483 ms

g++-9  -fopenmp -Ofast -march=native -DNDEBUG   -std=c++11 -Wall -I../include  pagerank.o amath583.o amath583IO.o amath583sparse.o -o pagerank.exe -L/usr/local/lib -lomp
# elapsed time [read]: 33332 ms
Converged in 37 iterations
# elapsed time [pagerank]: 7200 ms
# elapsed time [rank]: 358 ms

Load Balanced Partitioning with OpenMP (Extra Credit)
-----------------------------------------------------

* Are there any choices for scheduling that make an improvement in the parallel performance (most importantly, scalability) of pagerank?


STATIC == BETTER?

g++-9 -c  -fopenmp -Ofast -march=native -DNDEBUG   -std=c++11 -Wall -I../include  pagerank.cpp -o pagerank.o
g++-9  -fopenmp -Ofast -march=native -DNDEBUG   -std=c++11 -Wall -I../include  pagerank.o amath583.o amath583IO.o amath583sparse.o -o pagerank.exe -L/usr/local/lib -lomp
# elapsed time [read]: 30035 ms
Converged in 37 iterations
# elapsed time [pagerank]: 6868 ms
# elapsed time [rank]: 330 ms


DYNAMIC == BEST

shehios-MBP:pagerank shehio$ make pagerank.exe && ./pagerank.exe  ./../data/cit-Patents_adj.mtx -n 8
g++-9 -c  -fopenmp -Ofast -march=native -DNDEBUG   -std=c++11 -Wall -I../include  pagerank.cpp -o pagerank.o
g++-9  -fopenmp -Ofast -march=native -DNDEBUG   -std=c++11 -Wall -I../include  pagerank.o amath583.o amath583IO.o amath583sparse.o -o pagerank.exe -L/usr/local/lib -lomp
# elapsed time [read]: 28747 ms
Converged in 37 iterations
# elapsed time [pagerank]: 6386 ms
# elapsed time [rank]: 333 ms


GUIDED === BAD
++-9  -fopenmp -Ofast -march=native -DNDEBUG   -std=c++11 -Wall -I../include  pagerank.o amath583.o amath583IO.o amath583sparse.o -o pagerank.exe -L/usr/local/lib -lomp
# elapsed time [read]: 32660 ms
Converged in 37 iterations
# elapsed time [pagerank]: 8797 ms
# elapsed time [rank]: 391 ms



REPROING THESE NUMBERS too

