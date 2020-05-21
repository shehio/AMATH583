
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
For only 1 thread, that is, I removed all the others from the run, I can see that the thread creation takes around 80% of the time. So, the speed down is understandable. After profiling for only threads=8, starting threads is actually taking 92.5% of the time.
Another speed-down reason might because different strides require page faults. This is less common when the thread count is small, but will def increase with with adding more and more threads.

rnorm
-----

* How much parallel speedup do you see for 1, 2, 4, and 8 threads?
           N  Sequential    1 thread   2 threads   4 threads   8 threads      1 thread     2 threads     4 threads     8 threads
     1048576     6.47966     10.6403     11.7538     8.35394     4.26509             0   1.92318e-16             0   1.92318e-16
     2097152     5.24826     7.63739     6.20249     5.27531     5.19498   5.43881e-16   4.07911e-16   9.51792e-16   5.43881e-16
     4194304     4.68114     6.16809     4.63972       4.096     4.03298    9.6159e-16   1.92318e-16   5.76954e-16   3.84636e-16
     8388608     3.88085     5.02543     4.58201     3.34515     3.55218    1.3595e-16   5.43801e-16             0             0
    16777216     3.06633     5.31405     3.96758     3.94096     3.61355   3.84567e-16   1.34599e-15   1.92284e-16             0
    33554432     4.42963       5.084     4.07957     3.73866     3.77016   7.20652e-15   7.61444e-15   6.66264e-15   6.93458e-15

           N  Sequential    1 thread   2 threads   4 threads   8 threads      1 thread     2 threads     4 threads     8 threads
     1048576     3.06311      6.3574     5.91127     3.57183     5.37674   1.15258e-15   1.53677e-15   1.34467e-15   1.34467e-15
     2097152     4.01337     4.35494     4.65186     4.71618     4.54849   2.71928e-15   2.03946e-15   2.03946e-15    1.9035e-15
     4194304     3.37163     3.26659     2.95374     3.40447     4.08006   9.61294e-16   1.92259e-16             0   3.84518e-16
     8388608       4.433     3.74749     4.00926     4.52498     4.36208   1.49582e-15   1.08787e-15   5.43933e-16   1.35983e-16
    16777216     4.12072      4.3336     3.61355     4.25509      4.1943   5.00099e-15   4.03926e-15   3.84691e-15    4.2316e-15
    33554432     4.27445       4.234     4.30185     4.34362      4.1943   3.67179e-15   4.62374e-15   5.57568e-15   4.35175e-15

* What will happen if you use ``std:::launch::deferred`` instead of ``std:::launch::async`` when launching tasks?  When will the computations happen?  Will you see any speedup?  For your convenience, the driver program will also call ``recursive_two_norm_b`` -- which you can implement as a copy of ``recursive_two_norm_a`` but with the launch policy changed.
The computation happens using lazy evaluation, i.e., only when the data is needed, the thread is started and not right away. I see some small speedup when N=1048576 for threads=8. But that's mostly it.

General
-------

* For the different approaches to parallelization, were there any major differences in how much parallel speedup that you saw?
Not really, in all the ones that I profiled, it seems that for memory-bound work, threads aren't really useful. Maybe with the increase of computational complexity, and the increase of page faults; memory accesses, we can see an improvement in the work. 

* You may have seen the speedup slowing down as the problem sizes got larger -- if you didn't keep trying larger problem sizes.  What is limiting parallel speedup for two_norm (regardless of approach)?  What would determine the problem sizes where you should see ideal speedup?  (Hint: Roofline model.)

For my machine almost all the speedups are in the range of 32K to 512K (incredibly consistent with my l1 and L2 cache sizes):
       32768     13.1624     12.5043     12.5043     13.5181     8.47747             0    1.3567e-16    1.3567e-16   2.71341e-16
       65536     11.9135     12.6675     14.0949     12.2041     10.9971             0   1.92632e-16   1.92632e-16             0
      131072     11.6441     13.5323     14.5129     13.1762     12.2121             0   4.07686e-16   2.71791e-16   4.07686e-16
      262144     11.7996     10.9018     13.5536     14.7495       13.93             0   1.92302e-16   1.92302e-16   1.92302e-16
      524288     9.85867     10.0558     10.0558     13.4078     13.4078             0   5.43733e-16             0             0

Conundrum #1
------------

1. What is causing this behavior?
Many many thread creation and disposal without enough work justifying their creation.

2. How could this behavior be fixed?
Well we can recycle the threads. So that we have them running across multiple runs of the norm calculations.

3. Is there a simple implementation for this fix?
That will involve changing the structure of the whole program, so no, not really.
Another simple fix would be to determine whether to execute the sequential or the muti-threaded algorithm based on the size of the problem. So, if the problem is small execute the serial implementation to avoid the overhead of thread creation and if the problem is sufficiently large then determine the number of threads based on a regression model or something.


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
1 threads   
 N(Grid) N(Matrix)         NNZ         COO       COO^T         CSR       CSR^T         CSC       CSC^T
      64      4096       20224     1.31669     1.43983    0.676138     1.64046     1.60109    0.680737
     128     16384       81408     1.26955     1.80711     1.38337     2.15687     2.25381     1.46416
     256     65536      326656     1.09474     1.11278     1.33241     1.48917     1.84115      1.5579
     512    262144     1308672    0.894818     1.01153      1.1897     1.12574     1.07932     1.21033
    1024   1048576     5238784    0.866849    0.963936     1.21098    0.956286    0.869979    0.948756
    2048   4194304    20963328    0.794818    0.931703     0.91643     0.98074    0.860034    0.939533
2 threads   
 N(Grid) N(Matrix)         NNZ         COO       COO^T         CSR       CSR^T         CSC       CSC^T
      64      4096       20224      1.3432     1.56357    0.772729     1.77112     1.80303    0.966844
     128     16384       81408     1.19398     1.79098     2.04683     2.15687     2.22877     2.20428
     256     65536      326656     1.05483     1.29825     2.73685     1.84115     1.44662     2.13186
     512    262144     1308672    0.918366     0.98304     1.97535     1.07378     1.11376     1.88637
    1024   1048576     5238784    0.892534    0.912818     2.04224     1.05695     1.05233     2.04224
    2048   4194304    20963328    0.963831    0.998254     1.96148     1.12555     1.13699     2.07045
4 threads   
 N(Grid) N(Matrix)         NNZ         COO       COO^T         CSR       CSR^T         CSC       CSC^T
      64      4096       20224     1.33424     1.92439    0.772729     2.22374     2.30042    0.760976
     128     16384       81408     1.36455     1.91037     2.53911     2.18032     2.25381     2.53911
     256     65536      326656     1.19133     1.34124     4.21931     1.92883     2.00522     4.50059
     512    262144     1308672    0.969387     1.07378     2.58503     1.11972     1.17633     2.61734
    1024   1048576     5238784     0.97961      1.0041     2.33965     1.10038     1.15303     2.19076
    2048   4194304    20963328    0.942172     1.00123     2.36207     1.10697     1.13699     2.32926
8 threads   
 N(Grid) N(Matrix)         NNZ         COO       COO^T         CSR       CSR^T         CSC       CSC^T
      64      4096       20224     1.57588     2.15201     0.43698     2.44069     2.47082    0.443762
     128     16384       81408     1.34624     1.84027     1.59198     2.20428     2.18032     1.64417
     256     65536      326656     1.09474     1.37773     4.40275     1.96628     1.92883      3.5531
     512    262144     1308672     1.00667      1.0522     2.43474     1.15684     1.16326     2.40675
    1024   1048576     5238784    0.941344     1.01681     2.15164     1.08551     1.09538     2.36259
    2048   4194304    20963328    0.952879     1.01028     2.19224     1.05476     1.07161     2.37882

The speedup seems to be around 2.2x in both CSR and CSC^T. Note that there's not much difference between 4 threads and 8 threads when it comes to GFlops.
I've also implemented async implementation beside the submitted implementation that uses threads. The one with threads is way better. You can check the performance below aside with COO as the benchmark. 

async:
1 thread
       N          COO        CSR
      64      1.29959    1.04238
     128      1.31967    1.57944
     256     0.869213    1.07157
     512      0.82436    1.15684
    1024     0.945036    1.20492
    2048     0.894435     1.0648
2 threads         COO        CSR
      64      1.48249    0.71223
     128      1.25368    1.26157
     256     0.959842    1.48917
     512      0.81792    1.04173
    1024     0.892534    1.21709
    2048     0.800509    1.18941
4 threads         COO        CSR
      64       1.0877   0.395527
     128      1.29412    1.03397
     256      1.05483    1.15072
     512     0.891011    1.11972
    1024     0.945036    1.08065
    2048     0.961069   0.822091
8 threads         COO        CSR
      64      1.58839   0.251744
     128       1.4126     0.7063
     256      1.06035   0.830028
     512     0.814737     1.0214
    1024     0.991704    1.26834
    2048      0.88969    1.22414


threads:
1 thread    
       N          COO        CSR
      64      1.25872   0.939609
     128      1.07267    1.55496
     256      1.07727    1.44662
     512     0.938957     1.1965
    1024      0.93044    1.18711
    2048     0.868946    1.12934
2 threads         COO        CSR
      64      1.30808    1.08182
     128      1.27764    2.20428
     256     0.964413    2.41103
     512     0.930611    2.05282
    1024     0.912818     1.9916
    2048     0.899231    2.02056
4 thread          COO        CSR
      64      1.24309   0.563765
     128      1.35533    2.50737
     256     0.896136    3.49184
     512     0.943187    2.46338
    1024     0.762608    1.72131
    2048     0.820081    2.20667
8 thread          COO        CSR
      64      1.65402   0.427643
     128      1.07844    1.57944
     256       1.0386    4.05053
     512     0.902532    2.15863
    1024     0.876306    2.33965
    2048      0.81411    2.15008


Conundrum #2
------------

1. What are the two "matrix vector" operations that we could use?
CSR -> matvec
CSC -> t_matvec

2. How would we use the first in pagerank?  I.e., what would we have to do differently in the rest of pagerank.cpp to use that first operation?
Change the implementation of page rank to use a CSC matrix rather than a CSR, the rest of the code stays intact.

3. How would we use the second?
 A better approach is to have the method templated which is what we submit. We can pass both CSR and CSC matrices and they shall find the correct implementation for the other methods inside of pagerank.