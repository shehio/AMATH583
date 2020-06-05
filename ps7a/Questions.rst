
Questions
=========

Norm
----

* Look through the code for ``run()`` in ``norm_utils.hpp``.  How are we setting the number of threads for OpenMP to use?
#ifdef _OPENMP
    omp_set_num_threads(nthreads);
#endif

* Which version of ``norm`` provides the best parallel performance?  How do the results compare to the parallelized versions of ``norm`` from ps5?
srun norm_block_critical.exe
           N  Sequential    1 thread   2 threads   4 threads   8 threads      1 thread     2 threads     4 threads     8 threads
     1048576     6.57245     6.55104     13.0595     25.7842     51.5684             0   5.19496e-15   5.00255e-15   4.04052e-15
     2097152     5.72707     5.64708     12.2525     24.0673     47.0152             0   6.80033e-16   1.08805e-15   2.58412e-15
     4194304     3.67472     3.76254     8.60009     17.9546     37.9041             0   4.80808e-15   5.57737e-15   3.84646e-15
     8388608     3.14416     3.13008     6.70017      13.981     27.2357             0   1.11505e-14   9.92669e-15   9.65473e-15
    16777216     3.07622     3.08492     6.21378     12.3222      23.452             0   9.61626e-15   7.88533e-15   4.23115e-15
    33554432     3.09054     3.09869       6.085     11.9229     21.7482             0   9.65326e-15   1.12848e-14   9.78922e-15

srun norm_block_reduction.exe
          N  Sequential    1 thread   2 threads   4 threads   8 threads      1 thread     2 threads     4 threads     8 threads
     1048576     6.57245     6.55104     13.0595     25.4578     52.9255             0   5.19496e-15   5.00255e-15   4.04052e-15
     2097152     5.89404     6.01683     12.5569     25.2707     48.1346             0   6.80033e-16   1.08805e-15   2.58412e-15
     4194304     3.71474     3.76947      8.5641     17.9546     37.9041             0   4.80808e-15   5.57737e-15   3.84646e-15
     8388608      3.1775     3.16313      6.7869     14.0748     27.5941             0   1.11505e-14   9.92669e-15   9.65473e-15
    16777216     3.09367     3.08492     6.19613     12.3923     23.2025             0   9.61626e-15   7.88533e-15   4.23115e-15
    33554432     3.10689     3.09869       6.085     11.8031     21.3528             0   9.65326e-15   1.12848e-14   9.78922e-15

srun norm_cyclic_critical.exe
           N  Sequential    1 thread   2 threads   4 threads   8 threads      1 thread     2 threads     4 threads     8 threads
     1048576     6.57245     1.77508     3.54703     6.03955     7.03206   2.13571e-14   1.03899e-14             0   7.11902e-15
     2097152      5.8769     1.66941     3.28724     5.89404     7.06872   1.08805e-14   1.18326e-14             0   2.72013e-15
     4194304     3.89871     1.59534     2.61407     3.68796     3.87655   3.57721e-14   5.19273e-15             0   5.19273e-15
     8388608     3.19201     1.59966      2.5575     2.94958     2.87281   8.71645e-14   1.15585e-14             0   7.07107e-15
    16777216     3.07188       1.592     2.57502      2.9674     2.93545   9.03928e-15   2.82718e-14             0   9.42393e-15
    33554432     3.10689     1.60001     2.65103     3.04645     2.97695   3.17062e-13   7.35551e-14             0     3.535e-15

srun norm_cyclic_reduction.exe
           N  Sequential    1 thread   2 threads   4 threads   8 threads      1 thread     2 threads     4 threads     8 threads
     1048576       6.594     1.77508      3.5533     6.22653     7.15718   2.13571e-14   1.03899e-14             0   7.11902e-15
     2097152     5.94604     1.67494     3.28724     5.98123      7.1185   1.08805e-14   1.18326e-14             0   2.85614e-15
     4194304     3.82583     1.61167      2.6826     3.75563     3.79041   3.57721e-14   5.19273e-15             0   5.19273e-15
     8388608     3.22143      1.6021     2.60516     2.94544     2.90867   8.71645e-14   1.15585e-14             0   7.07107e-15
    16777216     3.06756     1.59549     2.63093     3.01665     2.98364   9.03928e-15   2.82718e-14             0   9.42393e-15
    33554432     3.09869     1.60548     2.69978      3.0425     3.00359   3.17062e-13   7.35551e-14             0     3.535e-15

./norm_parfor.exe 
           N  Sequential    1 thread   2 threads   4 threads   8 threads      1 thread     2 threads     4 threads     8 threads
     1048576     6.15036     6.11297     12.1889     24.2309     23.6608             0   5.19496e-15   5.00255e-15   4.04052e-15
     2097152      5.6948      5.6788     11.7538     23.5076     23.5076             0   6.80033e-16   1.08805e-15   2.58412e-15
     4194304     4.30004     4.46904     9.01683     17.3459     20.0669             0   4.80808e-15   5.57737e-15   3.84646e-15
     8388608     3.57266     3.57266     7.46317     14.7687      16.257             0   1.11505e-14   9.92669e-15   9.65473e-15
    16777216     3.24559     3.22162     6.60921     12.9824     13.5468             0   9.61626e-15   7.88533e-15   4.23115e-15
    33554432     3.18267     3.17836     6.31401     12.3622     12.6963             0   9.65326e-15   1.12848e-14   9.78922e-15

 srun norm_parfor.exe
     N  Sequential    1 thread   2 threads   4 threads   8 threads      1 thread     2 threads     4 threads     8 threads
     1048576       6.594     6.55104     12.8921     25.4578     52.9255             0   5.19496e-15   5.00255e-15   4.04052e-15
     2097152     5.98123     5.98123     12.3272     25.2707     47.0152             0   6.80033e-16   1.08805e-15   2.72013e-15
     4194304     3.92864     3.93619     8.60009     18.4398     38.6193             0   4.80808e-15   5.57737e-15   3.84646e-15
     8388608     3.20665      3.1727     6.65763     14.0748     27.2357             0   1.11505e-14   9.92669e-15   9.65473e-15
    16777216     3.07188     3.05896     6.10935     12.1846     23.2025             0   9.61626e-15   7.88533e-15   4.23115e-15
    33554432     3.09869     3.09869       6.085     11.8031     21.3528             0   9.65326e-15   1.12848e-14   9.65326e-15

* Which version of ``norm`` provides the best parallel performance for larger problems (i.e., problems at the top end of the default sizes in the drivers or larger)?  How do the results compare to the parallelized versions of ``norm`` from ps5?


* Which version of ``norm`` provides the best parallel performance for small problems (i.e., problems smller than the low end of the default sizes in the drivers)?  How do the results compare to the parallelized versions of ``norm`` from ps5?  


Sparse Matrix-Vector Product
----------------------------

* How does ``pmatvec.cpp`` set the number of OpenMP threads to use?
#ifdef _OPENMP
    omp_set_num_threads(nthreads);
#endif

* (For discussion on Piazza.) What characteristics of a matrix would make it more or less likely to exhibit an error  if improperly parallelized?  Meaning, if, say, you parallelized ``CSCMatrix::matvec`` with just basic  columnwise partitioning -- there would be potential races with the same locations in ``y`` being read and written by multiple threads.  But what characteristics of the matrix give rise to that kind of problem?  Are there ways to maybe work around / fix that if we knew some things in advance about the (sparse) matrix?

* Which methods did you parallelize?  What directives did you use?  How much parallel speedup did you see for 1, 2, 4, and 8 threads?


1 threads   
 N(Grid) N(Matrix)         NNZ         COO       COO^T         CSR       CSR^T         CSC       CSC^T
      64      4096       20224     1.71057     1.77112     2.00137     2.06326     2.04221     2.00137
     128     16384       81408     1.55496     1.63081     1.98603     1.94747     1.94747     2.00589
     256     65536      326656      1.5002     1.56997     2.00522     1.92883     1.92883     2.00522
     512    262144     1308672    0.969387     1.01153     1.40529     1.30054     1.27675     1.41478
    1024   1048576     5238784    0.863742    0.879504     1.11053     1.07104      1.0663     1.10543
    2048   4194304    20963328    0.851303    0.864467     1.08198     1.03523     1.05476     1.07504
2 threads   
 N(Grid) N(Matrix)         NNZ         COO       COO^T         CSR       CSR^T         CSC       CSC^T
      64      4096       20224     1.87044     1.78693     4.08442     2.44069     2.44069     4.08442
     128     16384       81408     1.55496     1.64417     3.85749     1.92874     1.92874     3.93312
     256     65536      326656     1.54601     1.63328     3.82126     1.85804     1.87525     3.89474
     512    262144     1308672     0.98304     1.02641      3.0346     1.27675     1.28459     3.07923
    1024   1048576     5238784    0.866849    0.882726     2.23133     1.07582      1.0616     2.19076
    2048   4194304    20963328    0.849147    0.862245     2.15008     1.05145     1.03843     2.13639
4 threads   
 N(Grid) N(Matrix)         NNZ         COO       COO^T         CSR       CSR^T         CSC       CSC^T
      64      4096       20224     1.85312     1.78693     6.90127     2.38258     2.47082     7.14774
     128     16384       81408     1.57944     1.64417     7.71497     1.94747     1.89235     7.71497
     256     65536      326656     1.54601     1.63328     7.78949     1.89277     1.87525     7.78949
     512    262144     1308672     1.01153     1.04173     6.54336     1.30867     1.30054     6.54336
    1024   1048576     5238784    0.866849    0.879504     4.38153      1.0616      1.0616     4.38153
    2048   4194304    20963328    0.849147    0.864467      4.1409     1.05145     1.03523      4.1409
8 threads   
 N(Grid) N(Matrix)         NNZ         COO       COO^T         CSR       CSR^T         CSC       CSC^T
      64      4096       20224     1.87044     1.78693     7.41247     2.44069     2.41129     7.69757
     128     16384       81408     1.57944     1.64417     9.55187     1.96656     1.91037     9.55187
     256     65536      326656      1.5579     1.63328     8.43861     1.91063     1.87525     9.20576
     512    262144     1308672     1.00185      1.0214      8.3755     1.32524     1.30054     12.3169
    1024   1048576     5238784    0.866849    0.873131      8.0328      1.0663      1.0616      8.0328
    2048   4194304    20963328    0.847003    0.860034     7.29159     1.05145     1.03523     7.13645

Sparse Matrix Dense Matrix Product (AMATH583 Only)
--------------------------------------------------

* Which methods did you parallelize?  What directives did you use?  How much parallel speedup did you see for 1, 2, 4, and 8 threads?  How does the parallel speedup compare to sparse matrix by vector product?

srun pmatmat.exe
1 omp threads
 N(Grid) N(Matrix)         NNZ    NRHS         COO         CSR         CSC
      64      4096       20224       1    0.695493     1.88777      1.6518
     128     16384       81408       1    0.701229     1.84073      1.6362
     256     65536      326656       1    0.686644      1.8692     1.68228
     512    262144     1308672       1    0.630967     1.41337     1.38565
    1024   1048576     5238784       1    0.603025     1.12511     1.26046
    2048   4194304    20963328       1    0.603882     1.07899      1.0334
2 omp threads
 N(Grid) N(Matrix)         NNZ    NRHS         COO         CSR         CSC
      64      4096       20224       1    0.702892     3.77553     1.71615
     128     16384       81408       1    0.683156     3.68145     1.65665
     256     65536      326656       1    0.697317     4.07825     1.84359
     512    262144     1308672       1    0.648333     2.94451     1.35901
    1024   1048576     5238784       1    0.598718      2.2058     1.23266
    2048   4194304    20963328       1    0.607633     2.11141      1.0334
4 omp threads
 N(Grid) N(Matrix)         NNZ    NRHS         COO         CSR         CSC
      64      4096       20224       1    0.699173     6.00653     1.57314
     128     16384       81408       1    0.701229      7.3629     1.65665
     256     65536      326656       1    0.700949      7.9166     1.84359
     512    262144     1308672       1    0.660451     6.42439      1.3722
    1024   1048576     5238784       1    0.607395     4.53084     1.25105
    2048   4194304    20963328       1    0.607633      4.0762      1.0334
8 omp threads
 N(Grid) N(Matrix)         NNZ    NRHS         COO         CSR         CSC
      64      4096       20224       1    0.702892     6.60718     1.57314
     128     16384       81408       1    0.697538     13.2532      1.6362
     256     65536      326656       1    0.697317     16.8228     1.81868
     512    262144     1308672       1    0.660451     12.8488     1.35901
    1024   1048576     5238784       1    0.605202     7.98291     1.24179
    2048   4194304    20963328       1    0.602642     7.15821     1.02978

srun pmatmat.exe 8
1 omp threads
 N(Grid) N(Matrix)         NNZ    NRHS         COO         CSR         CSC
      64      4096       20224       8     4.15603     4.15603     1.30385
     128     16384       81408       8     4.02251     4.02251     1.15903
     256     65536      326656       8     3.78921     3.88637     1.13961
     512    262144     1308672       8     3.22135     3.61013    0.675444
    1024   1048576     5238784       8     3.12763     3.40734     0.64083
    2048   4194304    20963328       8     2.97484     3.29644    0.620561
2 omp threads
 N(Grid) N(Matrix)         NNZ    NRHS         COO         CSR         CSC
      64      4096       20224       8     4.03009     7.82312    0.596381
     128     16384       81408       8     4.88448     9.76896    0.828881
     256     65536      326656       8     3.88637     7.57842     1.47154
     512    262144     1308672       8     3.37722     6.97958    0.947455
    1024   1048576     5238784       8     3.12763     6.87054      1.2548
    2048   4194304    20963328       8     2.97484     6.48142     1.16971
4 omp threads
 N(Grid) N(Matrix)         NNZ    NRHS         COO         CSR         CSC
      64      4096       20224       8     4.03009      14.777    0.386608
     128     16384       81408       8     4.88448     19.5379     0.61056
     256     65536      326656       8     3.88637     15.1568     1.48596
     512    262144     1308672       8     3.32361     13.9592     1.85299
    1024   1048576     5238784       8     3.15115     13.5194     1.94931
    2048   4194304    20963328       8     2.98145     12.5388     1.99354
8 omp threads
 N(Grid) N(Matrix)         NNZ    NRHS         COO         CSR         CSC
      64      4096       20224       8     4.03009     26.5986    0.509552
     128     16384       81408       8     4.88448     45.5885    0.790552
     256     65536      326656       8     3.78921     30.3137     1.91859
     512    262144     1308672       8     3.27168     26.1734     2.99125
    1024   1048576     5238784       8     3.17502     23.2835     3.35282
    2048   4194304    20963328       8     2.97484     20.6408     3.38801

PageRank Reprise
----------------

* Describe any changes you made to pagerank.cpp to get parallel speedup.  How much parallel speedup did you get for 1, 2, 4, and 8 threads?

Local machine:
shehios-MBP:pagerank shehio$ make pagerank.exe && ./pagerank.exe  ./../data/cit-Patents_adj.mtx -n 8
# elapsed time [read]: 33332 ms
Converged in 37 iterations
# elapsed time [pagerank]: 7200 ms
# elapsed time [rank]: 358 ms

srun pagerank.exe  /efs/home/public/data/cit-Patents_adj.mtx -n 2
# elapsed time [read]: 15184 ms
Converged in 37 iterations
# elapsed time [pagerank]: 17940 ms
# elapsed time [rank]: 367 ms

srun pagerank.exe  /efs/home/public/data/cit-Patents_adj.mtx -n 4
# elapsed time [read]: 15197 ms
Converged in 37 iterations
# elapsed time [pagerank]: 17817 ms
# elapsed time [rank]: 368 ms

srun pagerank.exe  /efs/home/public/data/cit-Patents_adj.mtx -n 8
# elapsed time [read]: 15554 ms
Converged in 37 iterations
# elapsed time [pagerank]: 17947 ms
# elapsed time [rank]: 368 ms

srun pagerank.exe  /efs/home/public/data/cit-Patents_adj.mtx -n 32
# elapsed time [read]: 15211 ms
Converged in 37 iterations
# elapsed time [pagerank]: 17779 ms
# elapsed time [rank]: 368 ms


* (EC) Which functions did you parallelize?  How much additional speedup did you achieve?



Load Balanced Partitioning with OpenMP (Extra Credit)
-----------------------------------------------------

* Are there any choices for scheduling that make an improvement in the parallel performance (most importantly, scalability) of pagerank?

