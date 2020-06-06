
Questions
=========


AXPY CUDA
---------

* How many more threads are run in version 2 compared to version 1? How much speedup might you expect as a result? How much speedup do you see in your plot?

* How many more threads are run in version 3 compared to version 2? How much speedup might you expect as a result? How much speedup do you see in your plot? (Hint: Is the speedup a function of the number of threads launched or the number of available cores, or both?)


* (AMATH 583) The cu_axpy_t also accepts as a second command line argument the size of the blocks to be used. Experiment with different block sizes with, a few different problem sizes (around :math:`2^{24}` plus or minus).  What block size seems to give the best performance?  Are there any aspects of the GPU as reported in deviceQuery that might point to why this would make sense?


nvprof
------

* Looking at some of the metrics reported by nvprof, how do metrics such as occupancy and efficiency compare to the ratio of threads launched between versions 1, 2, and 3?

Invocations                               Metric Name                        Metric Description         Min         Max         Avg
Device "Tesla K80 (0)"
    Kernel: madd(int, float, float*, float*)
          6                        achieved_occupancy                        Achieved Occupancy    0.015616    0.015625    0.015623
          6                    sysmem_read_throughput             System Memory Read Throughput  0.00000B/s  0.00000B/s  0.00000B/s
          6                      dram_read_throughput             Device Memory Read Throughput  0.00000B/s  0.00000B/s  0.00000B/s
          6                  gld_requested_throughput          Requested Global Load Throughput  4.5038MB/s  19.270MB/s  19.214MB/s
          6                            gst_throughput                   Global Store Throughput  18.015MB/s  77.082MB/s  76.855MB/s
          6                            gst_efficiency            Global Memory Store Efficiency      12.50%      12.50%      12.50%
          6                             sm_efficiency                   Multiprocessor Activity       2.27%       7.65%       6.74%
          6                         shared_efficiency                  Shared Memory Efficiency       0.00%       0.00%       0.00%
          6                            gld_efficiency             Global Memory Load Efficiency      12.50%      12.50%      12.50%

Invocations                               Metric Name                        Metric Description         Min         Max         AvgDevice "Tesla K80 (0)"    Kernel: madd(int, float, float*, float*)
          6                        achieved_occupancy                        Achieved Occupancy    0.087804    0.124812    0.118601
          6                    sysmem_read_throughput             System Memory Read Throughput  0.00000B/s  0.00000B/s  0.00000B/s
          6                      dram_read_throughput             Device Memory Read Throughput  0.00000B/s  0.00000B/s  0.00000B/s
          6                  gld_requested_throughput          Requested Global Load Throughput  5.5934MB/s  3.6458GB/s  3.6093GB/s
          6                            gst_throughput                   Global Store Throughput  5.5934MB/s  1.8229GB/s  1.8047GB/s
          6                            gst_efficiency            Global Memory Store Efficiency      50.00%     100.00%      91.67%
          6                             sm_efficiency                   Multiprocessor Activity       1.43%       7.25%       6.28%
          6                         shared_efficiency                  Shared Memory Efficiency       0.00%       0.00%       0.00%
          6                            gld_efficiency             Global Memory Load Efficiency      50.00%     100.00%      91.67%

Invocations                               Metric Name                        Metric Description         Min         Max         Avg
Device "Tesla K80 (0)"
    Kernel: madd(int, float, float*, float*)
          6                        achieved_occupancy                        Achieved Occupancy    0.090628    0.764906    0.638949
          6                    sysmem_read_throughput             System Memory Read Throughput  0.00000B/s  0.00000B/s  0.00000B/s
          6                      dram_read_throughput             Device Memory Read Throughput  0.00000B/s  10.274GB/s  3.3211GB/s
          6                  gld_requested_throughput          Requested Global Load Throughput  5.4652MB/s  55.791GB/s  48.749GB/s
          6                            gst_throughput                   Global Store Throughput  5.4652MB/s  27.895GB/s  24.375GB/s
          6                            gst_efficiency            Global Memory Store Efficiency      50.00%     100.00%      91.67%
          6                             sm_efficiency                   Multiprocessor Activity       1.46%      38.99%      31.23%
          6                         shared_efficiency                  Shared Memory Efficiency       0.00%       0.00%       0.00%
          6                            gld_efficiency             Global Memory Load Efficiency      50.00%     100.00%      91.67%

Invocations                               Metric Name                        Metric Description         Min         Max         Avg
Device "Tesla K80 (0)"
    Kernel: _ZN6thrust8cuda_cub4core13_kernel_agentINS0_14__parallel_for16ParallelForAgentINS0_11__transform18binary_transform_fINS_6detail15normal_iteratorINS_10device_ptrIfEEEESB_SB_NS5_14no_stencil_tagEZ4mainEUlffE_NS5_21always_true_predicateEEElEESF_lEEvT0_T1_
          5                        achieved_occupancy                        Achieved Occupancy    0.725889    0.757126    0.742563
          5                    sysmem_read_throughput             System Memory Read Throughput  0.00000B/s  0.00000B/s  0.00000B/s
          5                      dram_read_throughput             Device Memory Read Throughput  1.4144GB/s  8.8445GB/s  4.7792GB/s
          5                  gld_requested_throughput          Requested Global Load Throughput  50.359GB/s  54.789GB/s  52.454GB/s
          5                            gst_throughput                   Global Store Throughput  25.180GB/s  27.395GB/s  26.227GB/s
          5                            gst_efficiency            Global Memory Store Efficiency     100.00%     100.00%     100.00%
          5                             sm_efficiency                   Multiprocessor Activity      37.19%      43.57%      40.86%
          5                         shared_efficiency                  Shared Memory Efficiency       0.00%       0.00%       0.00%
          5                            gld_efficiency             Global Memory Load Efficiency     100.00%     100.00%     100.00%
    Kernel: _ZN6thrust8cuda_cub4core13_kernel_agentINS0_14__parallel_for16ParallelForAgentINS0_11__transform18binary_transform_fINS_6detail15normal_iteratorINS_10device_ptrIfEEEESB_SB_NS5_14no_stencil_tagEZ14find_10ms_sizevEUlffE_NS5_21always_true_predicateEEElEESF_lEEvT0_T1_
          1                        achieved_occupancy                        Achieved Occupancy    0.086217    0.086217    0.086217
          1                    sysmem_read_throughput             System Memory Read Throughput  0.00000B/s  0.00000B/s  0.00000B/s
          1                      dram_read_throughput             Device Memory Read Throughput  0.00000B/s  0.00000B/s  0.00000B/s
          1                  gld_requested_throughput          Requested Global Load Throughput  5.2835MB/s  5.2835MB/s  5.2833MB/s
          1                            gst_throughput                   Global Store Throughput  5.2835MB/s  5.2835MB/s  5.2833MB/s
          1                            gst_efficiency            Global Memory Store Efficiency      50.00%      50.00%      50.00%
          1                             sm_efficiency                   Multiprocessor Activity       1.81%       1.81%       1.81%
          1                         shared_efficiency                  Shared Memory Efficiency       0.00%       0.00%       0.00%
          1                            gld_efficiency             Global Memory Load Efficiency      50.00%      50.00%      50.00%
    Kernel: void thrust::cuda_cub::core::_kernel_agent<thrust::cuda_cub::__parallel_for::ParallelForAgent<thrust::cuda_cub::__uninitialized_fill::functor<thrust::device_ptr<float>, float>, unsigned long>, thrust::cuda_cub::__uninitialized_fill::functor<thrust::device_ptr<float>, float>, unsigned long>(thrust::device_ptr<float>, float)
          4                        achieved_occupancy                        Achieved Occupancy    0.109904    0.756937    0.431581
          4                    sysmem_read_throughput             System Memory Read Throughput  0.00000B/s  0.00000B/s  0.00000B/s
          4                      dram_read_throughput             Device Memory Read Throughput  0.00000B/s  33.758MB/s  9.7097MB/s
          4                  gld_requested_throughput          Requested Global Load Throughput  0.00000B/s  0.00000B/s  0.00000B/s
          4                            gst_throughput                   Global Store Throughput  5.5366MB/s  34.679GB/s  19.422GB/s
          4                            gst_efficiency            Global Memory Store Efficiency      50.00%     100.00%      75.00%
          4                             sm_efficiency                   Multiprocessor Activity       1.06%      30.17%      15.69%
          4                         shared_efficiency                  Shared Memory Efficiency       0.00%       0.00%       0.00%
          4                            gld_efficiency             Global Memory Load Efficiency       0.00%       0.00%       0.00%


norm
----

* Consider just the Second column for single and double.  Why might there be a difference in performance between the two?

* Consider just the First and Second columns for single precision.  Why might there be a difference in performance between the two?
(Hint:  What data structure are we starting with in the driver?  Our own ``Vector`` type.  What are its element types as compared to what we are sending to the GPU?)

* Compare and contrast strided partitioning for task-based parallelism (e.g., OpenMP or C++ tasks) with strided partitioning for GPU.  Why is it bad in the former case but good (if it is) in the latter case?


About PS7
---------

* The most important thing I learned from this assignment was ...


* One thing I am still not clear on is ...

