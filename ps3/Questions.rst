
PS3 Questions
=============

Add your answers to this file in plain text after each question.  Leave a blank line between the text of the question and the text of your answer.

argv
----

1. What does `argv[0]` always contain?
The name of the program.


2. Which entry of `argv` holds the first argument passed to the program?
The second one, that is argv[1].

3. Which entry of `argv` holds the second argument passed to the program?
The third one, that is argv[2].

4. How would you print just the last argument passed to a program?
std::cout << argv[argc - 1] << std::endl;

float vs double
----------------

5.  What is the difference (ratio) in execution times between single and double precision for    *construction with no optimization*? Explain.
It is around the same; the ratio is around 90%. The hypothesis here is that the compiler is using doubles for both types.

6.  What is the difference (ratio) in execution times between single and double precision for    *multiplication with no optimization*? Explain.
Again, it's around 90%, pretty much the same. Again, seems like the compiler is using doubles for both operations.

7.  What is the difference (ratio) in execution times between single and double precision for    *construction with optimization*? Explain.
The ratio is around the double for the double data type. Float uses 4 bytes while double uses 8 bytes on a regular machine. The way, the process (a program in execution) works is that when it's trying to allocate new memory it looks for 4xN contiguous bytes in memory for float and 8xN contiguous bytes in memory for double, where N is the lenght of the vector. Finding and allocating this amount of memory obviously take more time for the bigger amount of memory.

8.  What is the difference (ratio) in execution times between single and double precision for    *multiplication with optimization*? Explain. 
The speedup is 2x between doubles and floats. The hypothesis here is that maybe the non-optimized code has the CPU deal with float as a whole double While the optimized version of it doesn't have to deal with that and has the CPU perform the operation on just one word, i.e. 32 bits and thus comes the speed up.

9.  What is the difference (ratio) in execution times for double precision    multiplication with and without optimization? Explain. 
It's a little north of 3x. This might be due to loop unrolling in O3 among other micro-optimizations.

Efficiency
----------

10.  If you double the problem size for matrix-matrix product, how many more operations will matrix-matrix product perform?
Since the complexity of the algorithm is O(n *** 3), if you double n, the operations will increase eightfolds.

11.  If the time to perform a given operation is constant, when you double the problem size for matrix-matrix product, how much more time will be required to compute the answer?
Assuming the operation takes a constant time, then the runtime will also increase eightfolds.

12.  What ratio did you see when doubling the problem size when mmtime called `mult_0`?  (Hint, it may be larger than what pure operation count would predict.)  Explain.
For all the number of iterations that I tried, the number was between 9 and 13. The reason the ratio is more than 8 is that theoritical bounds generally don't take into account memory operations and processes swaps from the OS (if the  process is taking too long to execute). These operations are extremely expensive.

13.  What ratio did you see when doubling the problem size when mmtime called `mult_3`?  Was this the same for `mult_0`?  Referring to the function in amath583.cpp, what optimizations are implemented and what kinds of performance benefits might they provide?
The numbers are between 8 and 9. No, they're way less than `mul_0`.  mult_3 implements three techniques: Hoisting and Tiling and Blocking keep us close to the theoritical maximum.

14. (Extra credit.)  Try also with `mult_1` and `mult_2`.
For mult_1: The number is still between 9 and 13 jumping to 35 when taking the ratio of time when n = 2048 / time  n = 1024 (like seen in prev algorithms).
For mult_2: The number is more like mult_3 and less like mult_1, closer to 9.

Here's the table for all the numbers.

Number	Mult_3	Mult_2	Mult_1	    Mult_0
128       0       0        2         3
264	      7       9        30        24
512	      57      76       214       296
1024	 398	  827      2759      4166
2048	 3403	 25048     112150	 110125
4096	 32402	 352181    1.25e+06	 1.30e+06



All-Pairs
---------

15. What do you observe about the different approaches to doing the similarity computation?  Which algorithm (optimizations) are most effective?  Does it pay to make a transpose of A vs a copy of A vs just passing in A itself.  What about passing in A twice vs passing it in once (mult_trans_3 vs mult_trans_4)?
Different approaches result in different performance. The most effective appears to be m_t_4. Passing only A beats passing the transpose of A which beats the vanila algorithm. The algorithm mult_trans_4 slightly beats mult_trans_3. In mult_trans_5, I implemented strassen's algorithm which has a theoritical bound of O(n **  2.8..), it was awfully slower due to the matrices creation (and their associated memory  operations). If we were to try strassen's for an extremely big n, then it will triumph since O(n ** 2.83 + C) < O(n ** 3), for a sufficiently big n and any C.

16. What is the best performance over all the algorithms that you observed for the case of 1024 images?  What would the execution time be for 10 times as many images?  For 60 times as many images?  (Hint: the answer is not cubic but still potentially a problem.)  What if we wanted to do, say 56 by 56 images instead of 28 by 28?
The fastest of them all is m_t_4. After running it for a while the GFLOPS of that algorithm stablize at 16.4135 (it will be different on each machine). The runtime of the algorithm is O((m * n) ** 3) where m is the number of images and n is the image size that is m_rows * n_cols. Multiplying number of images (m) by 10 will take 1000 more times, for 60, it will take 60 ** 3 more times. While multiplying the dimensions (n) by 2, i.e. from 28 to 56, will take 8 more times.


About PS3
---------


17. The most important thing I learned from this assignment was writing strassen's algorithm. It was a lot of fun.


18. One thing I am still not clear on is why we are making hypotheses and testing them while we can look at assembly code and CPU perf metrics.
