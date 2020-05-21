- At what problem size do the answers between the computed norms start to differ?
The number on my machine is 86.

$ make norm_order.exe && ./norm_order.exe 86
make: `norm_order.exe' is up to date.
Calling two_norm first time: 10.8287
Calling two_norm second time: 10.8287
Calling two_norm with reversed values: 10.8287
Calling two_norm with sorted values: 10.8287
# Norms differ!
# Absolute difference: 1.77636e-15
# Relative difference: 1.64041e-16

- How do the absolute and relative errors change as a function of problem size?

sorted

    N       10      100     1000        10000       100000      1000000
Abs Diff    0       0       0           2.2e-13     1.1e-12     1.3e-12
Rel Diff    0       0       0           6.2e-16     9.8e-16     3.7e-16

Reversed

    N       10      100         1000        10000       100000      1000000
Abs Diff    0       1.7e-15     7.1e-15     0           2.2e-13     5.9e-12
Rel Diff    0       1.5e-16     1.9e-16     0           1.9e-16     1.6e-15

$ ./norm_order.exe 10
Calling two_norm first time: 4.3383
Calling two_norm second time: 4.3383
Calling two_norm with reversed values: 4.3383
Calling two_norm with sorted values: 4.3383


$ ./norm_order.exe 100
Calling two_norm first time: 11.7739
Calling two_norm second time: 11.7739
Calling two_norm with reversed values: 11.7739
# Norms differ!
# Absolute difference: 1.77636e-15
# Relative difference: 1.50872e-16
Calling two_norm with sorted values: 11.7739


$ ./norm_order.exe 1000
Calling two_norm first time: 36.8653
Calling two_norm second time: 36.8653
Calling two_norm with reversed values: 36.8653
# Norms differ!
# Absolute difference: 7.10543e-15
# Relative difference: 1.9274e-16
Calling two_norm with sorted values: 36.8653


$ ./norm_order.exe 10000
Calling two_norm first time: 116.015
Calling two_norm second time: 116.015
Calling two_norm with reversed values: 116.015
Calling two_norm with sorted values: 116.015


$ ./norm_order.exe 100000
Calling two_norm first time: 365.378
Calling two_norm second time: 365.378
Calling two_norm with reversed values: 365.378
Calling two_norm with sorted values: 365.378
# Norms differ!
# Absolute difference: 2.27374e-13
# Relative difference: 6.22297e-16


$ ./norm_order.exe 1000000
Calling two_norm first time: 1154.56
Calling two_norm second time: 1154.56
Calling two_norm with reversed values: 1154.56
# Norms differ!
# Absolute difference: 2.27374e-13
# Relative difference: 1.96935e-16
Calling two_norm with sorted values: 1154.56
# Norms differ!
# Absolute difference: 1.13687e-12
# Relative difference: 9.84674e-16

$ ./norm_order.exe 10000000
Calling two_norm first time: 3650.83
Calling two_norm second time: 3650.83
Calling two_norm with reversed values: 3650.83
# Norms differ!
# Absolute difference: 5.91172e-12
# Relative difference: 1.61928e-15
Calling two_norm with sorted values: 3650.83
# Norms differ!
# Absolute difference: 1.36424e-12
# Relative difference: 3.73679e-16

- Does the Vector class behave strictly like a member of an abstract vector class?
Abstract vector can mean the vector class in c++ or the abstract vector as a concept in linear algebra.

For the abstract vector in c++, our vector class restricts access to some methods of the vector class in c++ which is a good practice in general, exihibiting a facade design pattern. On the other hand, it adds some methods like norm, that are not native to the c++ vector class.

For the abstract vector as a concept in linear algebra, we define norms in the abstract sense. These mathematical concepts live on their own, but they're hardly found in real life. Can you really create an equilateral triangle? Without getting much more philosophical, we believe that numerical approximations are necessary for any pragmatic and useful implementation and in this assignment, we've experienced first hand different approximations.

- Do you have any concerns about this kind of behavior?
Def, I think the most accurate one would be the sorted one. Although it comes with the penality of sorting, which is O(n * log(n))


