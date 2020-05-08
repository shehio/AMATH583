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

You can see the striking difference in the numbers between this assignment and the previous one.
It stems from the fact that we have the a minute numerator where nnz compared to N ** 3 in the prev assignment.
Nonetheless, the cost of transferring and ingesting the dense matrix M to cache (inefficiently is still there).

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

We can see that the max Gflops occur in both alogirthms at around N = 16. Note that the number N is deceiving since the vector's length is (NxN)x1 and the size of the matrix is (NxN)x(NxN). That being said, most of the entries are zeros, so the only Non zeros are 1216 items. Although, the 1216 x 8 bytes for doubles = 9.5 KB, we have to add the rows and cols for COOs. This makes COO's storage = 9.5 * 3 = 28.5 KB. Although this is still less than my L1 cache (from prev assignments), there's no gurantee that the tool chain will cache the whole three vectors. This makes it a little less efficient, but still incredibly efficient when it comes to the numbers of item being processed.

The COO size should be an upper bound to CSR and CSC storage. This might be the reason CSR is 30% faster (2.66677 / 1.96086 - 1) when it comes to the roofline model.

How does the performance (in GFLOP/s) for sparse-matrix by dense matrix product (**SPMM**) compare to sparse-matrix by vector product
(**SPMV**)? The performance for SPMM should be about the same as for SPMV in the case of a 1 column dense matrix.  What is the trend with
increasing numbers of columns?  Explain, and quantify if you can, using the roofline model.


How does the performance of sparse matrix by dense matrix product (in GFLOP/s) compare to the results you got dense matrix-matrix product in
previous assignments?  Explain, and quantify if you can, using the roofline model.
Refer to the data at the top of the page for the data from dense matrix-matrix product.
N(Grid) N(Matrix)         NNZ    NRHS         COO         CSR         CSC         AOS
    128     16384       81408       1    0.625152    0.895488    0.907755    0.926799
    256     65536      326656       1     0.54267    0.704619    0.777932    0.666249


Some additional work.
 N(Grid) N(Matrix)         NNZ    NRHS         COO       COO^T         CSR       CSR^T         CSC       CSC^T         AOS       AOS^T
      64      4096       20224      10     2.30135     2.61722      3.0336     2.26235      2.9017     2.83997      3.0336      3.0336
     128     16384       81408      10     2.47131     2.51625     2.94454     2.23215     2.76787     2.82436     3.00856     3.00856
     256     65536      326656      10      2.0363     2.06309     2.27239     1.84465     2.30581     2.48881     2.34022     2.37568
     512    262144     1308672      10      1.9795     1.99628     2.22227     1.82605     2.16111     2.26501     2.22227     2.35561
    1024   1048576     5238784      10     1.95477     1.95477     2.21046      1.7009     2.14704      2.2581     2.21982     2.35981
    2048   4194304    20963328      10      1.9388      1.9569     2.21834      1.8033     2.17518     2.26325     2.16396     2.31001