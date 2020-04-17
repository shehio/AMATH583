
PS3 Questions
=============

Add your answers to this file in plain text after each question.  Leave a blank line between the text of the question and the text of your answer.

argv
----

1. What does `argv[0]` always contain?


2. Which entry of `argv` holds the first argument passed to the program?


3. Which entry of `argv` holds the second argument passed to the program?


4. How would you print just the last argument passed to a program?

float vs double
----------------

5.  What is the difference (ratio) in execution times 
between single and double precision for    *construction with no optimization*? Explain.

6.  What is the difference (ratio) in execution times
between single and double precision for    *multiplication with no optimization*? Explain.

7.  What is the difference (ratio) in execution times 
between single and double precision for    *construction with optimization*? Explain.

8.  What is the difference (ratio) in execution times 
between single and double precision for    *multiplication with optimization*? Explain. 

9.  What is the difference (ratio) in execution times 
for double precision    multiplication with and without optimization? Explain. 


Efficiency
----------

10.  If you double the problem size for matrix-matrix product, how many more operations will matrix-matrix product perform?

11.  If the time to perform a given operation is constant, when you double the problem size for matrix-matrix product, how much more time will be required to compute the answer?

12.  What ratio did you see when doubling the problem size when mmtime called `mult_0`?  (Hint, it may be larger than what pure operation count would predict.)  Explain.

13.  What raio did you see when doubling the problem size when mmtime called `mult_3`?  Was this the same for `mult_0`?  Referring to the function in amath583.cpp, what optimizations are implemented and what kinds of performance benefits might they provide?

14. (Extra credit.)  Try also with `mult_1` and `mult_2`.



All-Pairs
---------

15. What do you observe about the different approaches to doing the similarity computation?  Which algorithm (optimizations) are most effective?  Does it pay to make a transpose of A vs a copy of A vs just passing in A itself.  What about passing in A twice vs passing it in once (mult_trans_3 vs mult_trans_4)?

16. What is the best performance over all the algorithms that you observed for the case of 1024 images?  What would the execution time be for 10 times as many images?  For 60 times as many images?  (Hint: the answer is not cubic but still potentially a problem.)  What if we wanted to do, say 56 by 56 images instead of 28 by 28?



About PS3
---------


17. The most important thing I learned from this assignment was ...


18. One thing I am still not clear on is ...
