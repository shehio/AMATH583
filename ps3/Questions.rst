
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

5.  What is the difference (ratio) in execution times 
between single and double precision for    *construction with no optimization*? Explain.
The difference is around 10%. This is understandable since the program asks for a contiguous amount of memory to store the vector.
It happens that this amount of memory for the double type is 64xN while for the float type is 32xN where N is the length of the vector.
Finding and allocating this amount of memory obviously take more time for the bigger amount of memory.

6.  What is the difference (ratio) in execution times
between single and double precision for    *multiplication with no optimization*? Explain.
It's around 10% higher for the double data type. I attribute that to the operation (the multiplication)
having to deal with 64 bits for doubles rather than 32 bits for floats.

7.  What is the difference (ratio) in execution times 
between single and double precision for    *construction with optimization*? Explain.
It's the double for the double type.

8.  What is the difference (ratio) in execution times 
between single and double precision for    *multiplication with optimization*? Explain. 
The speedup is 2x between doubles and floats.

9.  What is the difference (ratio) in execution times 
for double precision    multiplication with and without optimization? Explain. 
It's a little north of 3x. This might be due to loop unrolling in O3.

Efficiency
----------

10.  If you double the problem size for matrix-matrix product, how many more operations will matrix-matrix product perform?
Since the complexity of the algorithm is O(n *** 3), if you double n, the operations will increase eightfolds.

11.  If the time to perform a given operation is constant, when you double the problem size for matrix-matrix product, how much more time will be required to compute the answer?
Assuming the operation takes a constant time, then the runtime will also increase eightfolds.

12.  What ratio did you see when doubling the problem size when mmtime called `mult_0`?  (Hint, it may be larger than what pure operation count would predict.)  Explain.
For all the number of iterations that I tried, the number was between 9 and 13. The reason the ratio is more than 8 is that theoritical bounds generally don't take into account memory operations and processes swaps from the OS. These operations are extremely expensive.

13.  What ratio did you see when doubling the problem size when mmtime called `mult_3`?  Was this the same for `mult_0`?  Referring to the function in amath583.cpp, what optimizations are implemented and what kinds of performance benefits might they provide?
The numbers are between 8 and 9. No, they're way less than `mul_0`.

14. (Extra credit.)  Try also with `mult_1` and `mult_2`.


All-Pairs
---------

15. What do you observe about the different approaches to doing the similarity computation?  Which algorithm (optimizations) are most effective?  Does it pay to make a transpose of A vs a copy of A vs just passing in A itself.  What about passing in A twice vs passing it in once (mult_trans_3 vs mult_trans_4)?

16. What is the best performance over all the algorithms that you observed for the case of 1024 images?  What would the execution time be for 10 times as many images?  For 60 times as many images?  (Hint: the answer is not cubic but still potentially a problem.)  What if we wanted to do, say 56 by 56 images instead of 28 by 28?



About PS3
---------


17. The most important thing I learned from this assignment was ...


18. One thing I am still not clear on is ...
