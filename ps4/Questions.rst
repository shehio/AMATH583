


What level of SIMD/vector support does the CPU your computer provide?



What is the maximum operand size that your computer will support?



What is the maximum operand size that your computer will support?




What is the clock speed of your CPU?  (You may need to look this up via "About this Mac" or "lscpu").


Based on the output from bandwidth.exe on your computer, what do you expect L1 cache and L2 cache sizes to be?  What are the corresponding bandwidths?   How do the cache sizes compare to what "about this mac" (or equivalent) tells you about your CPU?  (There is no "right" answer for this question -- but I do want you to do the experiment.)

What is the (potential) maximum compute performance of your computer?  (The horizontal line.)  What are the L1, L2, and RAM bandwidths?  How do those bandwidths correspond to  what was measured above with the bandwidth program?


Based on the clock speed of your CPU and its maximum Glop rate, what is the (potential) maximum number of *double precision* floating point operations that can be done per clock cycle?  (Hint: Glops / sec :math:`\div` GHz = flops / cycle.)  There are several hardware capabilities that can contribute to supporting more than one operation per cycle: fused multiply add (FMA) and AVX registers.  Assuming FMA contributes a factor of two, SSE contributes a factor of two,  AVX/AVX2 contribute a factor of four, and AVX contributes a factor of eight of eight, what is the expected maximum number of floating point operations your CPU could perform per cycle, based on the capabilities your CPU advertises via cpuinfo (equiv. lscpu)?  Would your answer change for single precision (would any of the previous assumptions change)?  

What is the maximum compute performance of your computer?  (The horizontal line.)  What are the L1, L2, and DRAM bandwidths?  How do those bandwidths correspond to what was measured above?

Referring to the figures about how data are stored in memory, what is it about the best performing pair of loops that is so advantageous?

What will the data access pattern be when we are executing ``mult_trans`` in i,j,k order?  What data are accessed in each if the matrices at step (i,j,k) and what data are accessed at step (i, j, k+1)? Are these accesses advantageous in any way?


Referring again to how data are stored in memory, explain why hoisting  ``C(i,j)`` out of the inner loop is so beneficial in mult_trans with the "ijk" loop ordering.

What optimization is applied in going from ``mult_2`` to ``mult_3``?

How does your maximum achieved performance for ``mult`` (any version) compare to what bandwidth and roofline predicted?





