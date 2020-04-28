What level of SIMD/vector support does the CPU your computer provide?
CPUID_EBX_AVX2:     256-bit operations.
CPUID_ECX_AVX:      256-bit operations.

CPUID_ECX_SSE3:     128-bit operations.
CPUID_ECX_SSSE3:    128-bit operations.
CPUID_ECX_SSE41:    128-bit operations.
CPUID_ECX_SSE42:    128-bit operations.
CPUID_EDX_SSE2:     128-bit operations.

What is the maximum operand size that your computer will support?
The maximum operand size is still 8-bytes for arithmatic operations, while 32-bytes for other operations.


What is the maximum operand size that your computer will support?
## Redundant?



What is the clock speed of your CPU?  (You may need to look this up via "About this Mac" or "lscpu").
2.2 GHz

Based on the output from bandwidth.exe on your computer, what do you expect L1 cache and L2 cache sizes to be?  What are the corresponding bandwidths?   How do the cache sizes compare to what "about this mac" (or equivalent) tells you about your CPU?  (There is no "right" answer for this question -- but I do want you to do the experiment.)
32K -> 64K
32768       2.14752e+11
65536       8.5902e+10
           
256K -> 512K
262144      8.76631e+10
524288      6.50911e+10
        

8M -> 16M
8388608   2.42233e+10
16777216  1.8498e+10

sysctl -n machdep.cpu.brand_string
Intel(R) Core(TM) i7-8750H CPU @ 2.20GHz

L1 Cache is 32K
L2 Cache is 256K
L3 Cache (shared among 6 cores) is 9M

What is the (potential) maximum compute performance of your computer?  (The horizontal line.)  What are the L1, L2, and RAM bandwidths?  How do those bandwidths correspond to  what was measured above with the bandwidth program?
kernel sz   res_bytes   ntrials        usecs      ttl_bytes         ttl_flops         intensity      flops/sec      bytes/sec
    8        32768      32769          21000     2147549184        1073774592            0.5        5.11321e+10    1.02264e+11
    8        262144     4097           31000     2148007936        1074003968            0.5        3.46453e+10    6.92906e+10
    8        9437184    114            70000     2151677952        1075838976            0.5        1.53691e+10    3.07383e+10
    8        16777216   65             87000     2181038080        1090519040            0.5        1.25347e+10    2.50694e+10

Consistent degradation with the numbers above.


Based on the clock speed of your CPU and its maximum Glop rate, what is the (potential) maximum number of *double precision* floating point operations that can be done per clock cycle?  (Hint: Glops / sec :math:`\div` GHz = flops / cycle.)  There are several hardware capabilities that can contribute to supporting more than one operation per cycle: fused multiply add (FMA) and AVX registers.  Assuming FMA contributes a factor of two, SSE contributes a factor of two,  AVX/AVX2 contribute a factor of four, and AVX contributes a factor of eight of eight, what is the expected maximum number of floating point operations your CPU could perform per cycle, based on the capabilities your CPU advertises via cpuinfo (equiv. lscpu)?  Would your answer change for single precision (would any of the previous assumptions change)?

flops / cycle = Gflops / sec / GHz

res_bytes       Gflops/sec      bytes/sec       flops / cycle
32768           51.1321         1.02264e+11         23
262144          34.6453         6.92906e+10         16
9437184         15.3691         3.07383e+10         8
16777216        12.5347         2.50694e+10         6


Since my machine support AVX registers flops / cycle could be multiplied by 4 (256-bit registers / 8 bits to bytes / 8 bytes to double).


What is the maximum compute performance of your computer?  (The horizontal line.)  What are the L1, L2, and DRAM bandwidths?  How do those bandwidths correspond to what was measured above?
Redundant?

Referring to the figures about how data are stored in memory, what is it about the best performing pair of loops that is so advantageous?

What will the data access pattern be when we are executing ``mult_trans`` in i,j,k order?  What data are accessed in each if the matrices at step (i,j,k) and what data are accessed at step (i, j, k+1)? Are these accesses advantageous in any way?


Referring again to how data are stored in memory, explain why hoisting  ``C(i,j)`` out of the inner loop is so beneficial in mult_trans with the "ijk" loop ordering.

What optimization is applied in going from ``mult_2`` to ``mult_3``?

How does your maximum achieved performance for ``mult`` (any version) compare to what bandwidth and roofline predicted?





