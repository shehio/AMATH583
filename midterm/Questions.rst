Dense:
       N      mult_0      mult_1      mult_2      mult_3     mul_t_0     mul_t_1     mul_t_2     mul_t_3
     128     1.84105     2.19316     7.13865     19.7786     2.28135     17.3861     29.1334     21.5587
     256     1.14924     1.34708      4.5012     18.9281     2.06971     13.4218     21.7117     20.6971

Combinations:
       N    GF/s ijk    GF/s ikj    GF/s jik    GF/s jki    GF/s kij    GF/s kji
     128     23.4334     15.7363     1.69487    0.724907     2.17765    0.716713
     256     15.7063     10.5457     1.09796    0.438533     2.21017    0.426868

Transpose Combinations:
       N    GF/s ijk    GF/s ikj    GF/s jik    GF/s jki    GF/s kij    GF/s kji
     128     2.27653     2.89768     2.22714    0.758576       2.642    0.791727
     256     2.02246     1.30963     1.99873    0.462337      1.1786     0.46311

How does the performance (in GFLOP/s) for sparse-matrix by vector product compare to what you previously achieved for dense-matrix by
dense-matrix product?  Explain, and quantify if you can, (e.g., using the roofline model).

Sparse:
 N(Grid) N(Matrix)         NNZ         COO       COO^T         CSR       CSR^T         CSC       CSC^T         AOS       AOS^T
     128     16384       81408     1.44309     1.82354     2.20428     2.38797     1.89235     2.22877     1.12061     1.60471
     256     65536      326656     1.01772     1.25016     1.70191     1.68772     1.66006      2.5965     1.07157     1.12515

We can see that sparse multiplication multiplications barely surpass inefficient dense matrix multiplications (like mult_0 and mult_t_0) among with (jik, jki, kij and kij). Now let's inspect that a little closer.

This is the Gflops for this assignment.
double Gflops = static_cast<double>(trials)*(2.0 * nnz)/1.e9;

Compare it with the Gflops from the previous assignments.
double Gflops = static_cast<double>(trials)*(2.0 * N * N * N)/1.e9;

You can see the striking difference in the numbers between this assignment and the previous one. It stems from the fact that we have the a minute numerator, nnz, compared to N ** 3 in the prev assignment. Nonetheless, the cost of transferring and ingesting different datastructures to the registers and cache (inefficiently is still there).

How does the performance (in GFLOP/s) for sparse-matrix by vector product for COO compare to CSR?  Explain, and quantify if you can,
(e.g., using the roofline model).
 N(Grid) N(Matrix)         NNZ         COO         CSR
       2         4          12     1.49254     1.75439
       4        16          64     2.12766     2.17392
       8        64         288     1.75441      2.6667
      16       256        1216     1.96086     2.66677
      32      1024        4992     1.49283      2.2993
      64      4096       20224     1.46085     2.24873
     128     16384       81408     1.44309     2.22877
     256     65536      326656    0.992778     1.51139
     512    262144     1308672    0.902532     1.45408
    1024   1048576     5238784    0.960096     1.38497
    2048   4194304    20963328    0.936909     1.37464

We can see that the max Gflops occur in both alogirthms at around N = 16. Note that the number N is deceiving since the vector's length is (NxN)x1 and the size of the matrix is (NxN)x(NxN). That being said, since most entries are zeros, we only have 1216 items.

Now, let's caculate the storage for that. For COOs, there are three arrays, for values, rows, and cols. This becomes 3 x 1216 x 8 bytes for doubles = 28.5 KB. Although this is still less than my L1 cache (from prev assignments), there's no gurantee that the tool chain will cache the whole three vectors. This makes it a little less efficient, but still incredibly efficient when it comes to the numbers of item being processed.

The COO size should be an upper bound to CSR and CSC storage. This might be the reason CSR is 30% faster (2.66677 / 1.96086 - 1) when it comes to the roofline model.

How does the performance (in GFLOP/s) for sparse-matrix by dense matrix product (**SPMM**) compare to sparse-matrix by vector product
(**SPMV**)? The performance for SPMM should be about the same as for SPMV in the case of a 1 column dense matrix.  What is the trend with
increasing numbers of columns?  Explain, and quantify if you can, using the roofline model.
Note that I added the transpose methods in matmat too in this experiment.

  N(Grid) N(Matrix)         NNZ    NRHS         COO       COO^T         CSR       CSR^T         CSC       CSC^T         AOS       AOS^T
      64      4096       20224       1    0.730075    0.768277    0.815701    0.768277    0.805754    0.730075    0.937189    0.964552
     128     16384       81408       1    0.761679    0.770536    0.833536    0.775042    0.828326    0.784214    0.939945    0.953469
     256     65536      326656       1    0.712076    0.727472    0.796345    0.751856    0.796345    0.760352    0.715863    0.719691
     512    262144     1308672       1    0.586459    0.622628    0.657379    0.642439    0.606595    0.636651    0.636651    0.645372
    1024   1048576     5238784       1    0.594472    0.607395    0.662613    0.611829    0.637419    0.574113    0.546062    0.537311
    2048   4194304    20963328       1    0.533612    0.494918    0.625771    0.617867    0.652192    0.600177    0.590516    0.625771

The Gflops seem to be slightly less than the corresponding ones in matvec. We can probably see that the most efficient ones are CSR and AOS^T.
If we focus on AOS (since it's easy to analyz; 3 entries per non zero element). We can see that for N = 64. There's a dense matrix of 4096x1 and a sparse one which is of capacity = 3x20224 (again 3 for row, col, and value). Now, putting all the memory usage together: 84992. Each of these, take 8 bytes. So 84992 * 8 = 679936 = 664K, which is already more than the L1 cache on my machine (32K).

The Gflops for this problem peaks at 1, which shows that this problem is memory-bound and not cpu-bound. It seems that a lot of work is being done to get the data ready for the CPU.

Comparing it with cols = 10
 N(Grid) N(Matrix)         NNZ    NRHS         COO         CSR         CSC         AOS
      64      4096       20224      10     2.22464      3.0336     2.83997     3.10415
     128     16384       81408      10     2.51625     2.94454     2.82436     3.07541
     256     65536      326656      10     2.23993     2.48881     2.48881     2.34022
     512    262144     1308672      10     2.01334     2.26501     2.18112       2.287
    1024   1048576     5238784      10     1.91196     2.19196     2.12959     2.27773
    2048   4194304    20963328      10      1.9569     2.24207     2.09372     2.21834

And cols = 100
N(Grid) N(Matrix)         NNZ    NRHS         COO         CSR         CSC         AOS
      64      4096       20224     100     6.61876     8.56546     8.56546     9.70752
     128     16384       81408     100     5.92058     5.92058     5.58226      6.1056
     256     65536      326656     100     5.59982     5.59982     5.36969     5.85056
     512    262144     1308672     100     5.28756     5.65912     5.28756     5.88167
    1024   1048576     5238784     100     5.21272     5.52906     5.15502     5.74901
    2048   4194304    20963328     100     4.16766     5.10522      4.5523     4.05578

We can see the increase in efficiency with the increase in number of columns (before it decreases again for higher columns). This might be because for smaller columns, there's more overhead then there's computations. While for an adquate number of columns, say 100, the overhead can becomes small compared to all the computations. When we speak of overhead, we mean memory, and how compiler deals with it.

How does the performance of sparse matrix by dense matrix product (in GFLOP/s) compare to the results you got dense matrix-matrix product in
previous assignments?  Explain, and quantify if you can, using the roofline model.
Refer to the data at the top of the page for the data from dense matrix-matrix product.
 N(Grid) N(Matrix)         NNZ    NRHS         COO         CSR         CSC         AOS
     128     16384       81408     100     5.92058     5.92058     5.58226      6.1056
     256     65536      326656     100     5.59982     5.59982     5.36969     5.85056

It seems that the maximum of Gflops we're getting from sparse matrices is 6. This doesn't fare well with the denses' numbers we've shown in the top of the file. It seems that, even though it's a great idea to not store zeros, we will have to store additional indexing information. This information makes computation less efficient due to the slow nature of memory. I think our toolbox needs an additional metric: How many useful computation can we get when we compare dense matrix to sparse ones; meaning how many real multiplication do we need to do in dense matrices, i.e. ones that are not zeros to begin with.

Any additonal check will have the perf monitoring go up so, we have to do this manually without relyin on the code to count the number of zero entries for us in the dense matrix.

Experiment with some of the optimizations we developed previously in the course for matrix-matrix product and apply them to sparse-matrix by dense-matrix product.
Added the transpose methods in matmat too. As I tried them, they didn't give a great improvement.

Answer the following questions:
a) The most important thing I learned from this assignment was implementing sparse matrices.
b) One thing I am still not clear on is what are we going to do with them? Not clear on the big picture. I also would have imagined that sparse matrices would do better than dense matrices.