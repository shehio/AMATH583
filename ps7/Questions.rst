
Questions
=========


AXPY CUDA
---------

* How many more threads are run in version 2 compared to version 1? How much speedup might you expect as a result? How much speedup do you see in your plot?
There are 256 threads per threadblock in version 2, while there's only ONE thread per threadblock in version 1.
The speedup that I'm seeing (look at the pdf) is: 230x which is great!

* How many more threads are run in version 3 compared to version 2? How much speedup might you expect as a result? How much speedup do you see in your plot? (Hint: Is the speedup a function of the number of threads launched or the number of available cores, or both?)
The thread per block is the same for both versions: v2 and v3. However, the thread blocks in version 3 is a function of the total input N:  int num_blocks = (N + block_size - 1) / block_size;
The speedup is fascinating in itself, it's around 10x.

* (AMATH 583) The cu_axpy_t also accepts as a second command line argument the size of the blocks to be used. Experiment with different block sizes with, a few different problem sizes (around :math:`2^{24}` plus or minus).  What block size seems to give the best performance?  Are there any aspects of the GPU as reported in deviceQuery that might point to why this would make sense?
The device vector time dips a little for N=25. However, nothing significant for all other aspects. I'm not sure what device property could indicate which block size should be used.

(13) Multiprocessors, (192) CUDA Cores/MP:     2496 CUDA Cores
Maximum number of threads per multiprocessor:  2048
Maximum number of threads per block:           1024
 
yassers@ip-172-31-41-96:~/AMATH583/ps7/axpy_cuda$ ./cu_axpy_t.exe 23
# elapsed time [host_vector]: 46 ms
# elapsed time [device_vector]: 191 ms
# elapsed time [copy]: 10 ms
# elapsed time [thrust_call]: 518 ms
# gflops / sec [ madd ]: 25.9108
# elapsed time [copy_back]: 3 ms

yassers@ip-172-31-41-96:~/AMATH583/ps7/axpy_cuda$ ./cu_axpy_t.exe 24
# elapsed time [host_vector]: 92 ms
# elapsed time [device_vector]: 185 ms
# elapsed time [copy]: 22 ms
# elapsed time [thrust_call]: 267 ms
# gflops / sec [ madd ]: 25.1344
# elapsed time [copy_back]: 7 ms

yassers@ip-172-31-41-96:~/AMATH583/ps7/axpy_cuda$ ./cu_axpy_t.exe 25
# elapsed time [host_vector]: 185 ms
# elapsed time [device_vector]: 168 ms
# elapsed time [copy]: 45 ms
# elapsed time [thrust_call]: 508 ms
# gflops / sec [ madd ]: 26.4208
# elapsed time [copy_back]: 11 ms

yassers@ip-172-31-41-96:~/AMATH583/ps7/axpy_cuda$ ./cu_axpy_t.exe 26
# elapsed time [host_vector]: 372 ms
# elapsed time [device_vector]: 171 ms
# elapsed time [copy]: 87 ms
# elapsed time [thrust_call]: 507 ms
# gflops / sec [ madd ]: 26.4729
# elapsed time [copy_back]: 23 ms
yassers@ip-172-31-41-96:~/AMATH583/ps7/axpy_cuda$ ./cu_axpy_t.exe 27
# elapsed time [host_vector]: 740 ms
# elapsed time [device_vector]: 193 ms
# elapsed time [copy]: 178 ms
# elapsed time [thrust_call]: 506 ms
# gflops / sec [ madd ]: 26.5252
# elapsed time [copy_back]: 46 ms



nvprof
------

* Looking at some of the metrics reported by nvprof, how do metrics such as occupancy and efficiency compare to the ratio of threads launched between versions 1, 2, and 3?
Looking at the average achieved occupancy, it's 1.5% for v1, 11% for v2 and 63% for v3. So, v3 certainly dominates that aspect.
Now, looking at the average global memory load efficiency, it's 12.5% for v1, and 91.67% for both v2 and v3. So, no gains coming from v3 over v2.

Invocations                               Metric Name                        Metric Description         Min         Max         Avg
          6                        achieved_occupancy                        Achieved Occupancy    0.015616    0.015625    0.015623
          6                            gst_efficiency            Global Memory Store Efficiency      12.50%      12.50%      12.50%
          6                             sm_efficiency                   Multiprocessor Activity       2.27%       7.65%       6.74%
          6                            gld_efficiency             Global Memory Load Efficiency      12.50%      12.50%      12.50%

Invocations                               Metric Name                        Metric Description         Min         Max         Avg
          6                        achieved_occupancy                        Achieved Occupancy    0.087804    0.124812    0.118601
          6                            gst_efficiency            Global Memory Store Efficiency      50.00%     100.00%      91.67%
          6                             sm_efficiency                   Multiprocessor Activity       1.43%       7.25%       6.28%
          6                            gld_efficiency             Global Memory Load Efficiency      50.00%     100.00%      91.67%

Invocations                               Metric Name                        Metric Description         Min         Max         Avg
          6                        achieved_occupancy                        Achieved Occupancy    0.090628    0.764906    0.638949
          6                            gst_efficiency            Global Memory Store Efficiency      50.00%     100.00%      91.67%
          6                             sm_efficiency                   Multiprocessor Activity       1.46%      38.99%      31.23%
          6                            gld_efficiency             Global Memory Load Efficiency      50.00%     100.00%      91.67%


norm
----
* Consider just the Second column for single and double.  Why might there be a difference in performance between the two?
copying and stuff like that.

* Consider just the First and Second columns for single precision.  Why might there be a difference in performance between the two?
(Hint:  What data structure are we starting with in the driver?  Our own ``Vector`` type.  What are its element types as compared to what we are sending to the GPU?)

* Compare and contrast strided partitioning for task-based parallelism (e.g., OpenMP or C++ tasks) with strided partitioning for GPU.  Why is it bad in the former case but good (if it is) in the latter case?

Float      
           N  Sequential       First      Second       First      Second
     1048576     1.78771     6.18821     6.18821    2.7595e-08    2.7595e-08
     2097152     1.74582     11.2942     11.3576   4.51044e-08   4.51044e-08
     4194304     1.46725      18.952     19.3096   2.15465e-08   2.15465e-08
     8388608     1.40654      27.962     29.9593   3.51608e-08   3.51608e-08
    16777216     1.39186     33.5544     41.1517   4.24208e-08   4.24208e-08
    33554432      1.4006     32.6224     51.0611   8.84264e-09   8.84264e-09
    67108864     1.39519     27.6738     62.4269   2.65331e-09   2.65331e-09
   134217728     1.39419     27.9173     72.7013   7.77251e-08   7.77251e-08

Double     
           N  Sequential       First      Second       First      Second
     1048576      1.7893     6.48764     6.48764   2.09287e-08   2.09287e-08
     2097152     1.73235      11.108      11.108   2.38849e-08   2.38849e-08
     4194304     1.45889     17.3459     17.3459   2.78014e-08   2.78014e-08
     8388608     1.40938     24.1052     24.1052   2.83637e-08   2.83637e-08
    16777216     1.39363     29.8772     29.8772   3.67339e-09   3.67339e-09
    33554432      1.3841     34.0407     33.5544   3.71015e-08   3.71015e-08
    67108864     1.40542     36.2751     36.2751   2.39604e-08   2.39604e-08
   134217728     1.41626     37.5232     37.5232   1.08505e-09   1.08505e-09


Float      
           N  Sequential       First      Second       First      Second
     1048576     1.75801     6.13161     6.13161    2.7595e-08    2.7595e-08
     2097152     1.52348     11.2314     11.2314   4.51044e-08   4.51044e-08
     4194304     1.39334      18.952     19.3096   2.15465e-08   2.15465e-08
     8388608      1.3981     28.3399     29.9593   3.51608e-08   3.51608e-08
    16777216      1.3892     35.7547     41.1517   4.24208e-08   4.24208e-08
    33554432     1.39313     35.0569     51.0611   8.84264e-09   8.84264e-09
    67108864     1.40175     31.2134     63.9132   2.65331e-09   2.65331e-09
   134217728     1.41339     28.8402     72.7013   7.77251e-08   7.77251e-08

Double     
           N  Sequential       First      Second       First      Second
     1048576     1.76418       6.405       6.405   2.09287e-08   2.09287e-08
     2097152      1.6096     10.9873     10.9873   2.38849e-08   2.38849e-08
     4194304     1.41257     16.9159     16.6408   2.78014e-08   2.78014e-08
     8388608      1.4056     23.8313     24.1052   2.83637e-08   2.83637e-08
    16777216     1.39363     29.4735     29.8772   3.67339e-09   3.67339e-09
    33554432     1.39395     33.5544     34.0407   3.71015e-08   3.71015e-08
    67108864     1.39883     35.7914     36.2751   2.39604e-08   2.39604e-08
   134217728     1.40147     37.1241     37.1241   1.08505e-09   1.08505e-09


About PS7
---------

* The most important thing I learned from this assignment was: writing my first CUDA program! This was awesome.

* One thing I am still not clear on is: I won't be able to optimize code for specific GPU architecture. I'm not sure how threadblocks and multiprocessors fit in one unifying framework.