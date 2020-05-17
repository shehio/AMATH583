line 56: std::cout << "Double checking Clyde's deposit " << clyde.get() << std::endl;
A future can only be queried once. Preventing it from being queried twice because it might give the consumer of it th efalse impression that the task has run twice.

- At what problem size do the answers between the computed norms start to differ?
The number on my machine is 86

shehios-MBP:ps5a shehio$ make norm_order.exe && ./norm_order.exe 86
make: `norm_order.exe' is up to date.
Calling two_norm first time: 10.8287
Calling two_norm second time: 10.8287
Calling two_norm with reversed values: 10.8287
Calling two_norm with sorted values: 10.8287
# Norms differ!
# Absolute difference: 1.77636e-15
# Relative difference: 1.64041e-16

- How do the absolute and relative errors change as a function of problem size?

1000
# Absolute difference: 7.10543e-15
# Relative difference: 1.9274e-16

1000000
# Absolute difference: 2.27374e-13
# Relative difference: 1.96935e-16
# Absolute difference: 1.13687e-12
# Relative difference: 9.84674e-16

100000000
# Absolute difference: 2.67391e-10
# Relative difference: 2.31571e-14
# Absolute difference: 1.27329e-10
# Relative difference: 1.10272e-14
- Does the Vector class behave strictly like a member of an abstract vector class?


- Do you have any concerns about this kind of behavior?
Def, I think the most accurate one would be the sorted one. Although it comes with the penality of sorting, which is O(n * log(n))


