Deliverable 5: Optimizer
=========

# Process for Selecting Optimizations
First, we started with more broad passes (in terms of scope), and worked our way down from module passes, to function passes, to loop passes. The optimizations we chose to include were based on criteria like the reduction of code size, or increased performance.


# Optimizations Selected
### Global Dead Code Elimination
##### Description 
This optimization eliminates any globals that are unreachable, i.e. defined but not used at all in the program. It works by using an aggressive algorithm to find globals that are alive, and after it finds all needed globals, it deletes whats left.

##### Evidence
This optimization provides unique benefit in optimizing SIP programs because it can cause large reductions in code size. For example, in our ablation study we noticed a 15x reduction in number of code lines. This could give the programmer an easier time debugging and show them what code could be deleted without affecting the program's functionality.


### Merge Functions
##### Description 
This optimization merges any functions that have different identifiers, but identical function bodies. For duplicate functions, it will replace their function bodies with a call to the function that was first defined. It works by introducing a total ordering among the function set and defining a comparison that answers which of 2 functions is greater, allowing the functions to be put into a binary tree. If the function already exists in the binary tree, then fold the function.

##### Evidence
This optimization provides unique benefit in optimizing SIP programs because it can cause large reductions in code size. For example, in our ablation study we noticed a 2.25x reduction in number of code lines. This could give the programmer an easier time debugging and show them what code could be deleted without affecting the program's functionality.


### Tail Recursion Elimination
##### Description 
This optimization replaces tail recursive calls with iteration. It works by proving if a callee does not access their caller's stack frame and marking them for tail recursive elimination.

##### Evidence
This optimization provides unique benefit in optimizing SIP programs because it can cause decrease run time and "increase" programs' recursive depth, since they're being changed to iteration instead. For example, in our ablation study, we saw a 1.3x decrease in run time, meaning a better performance, and when called with higher inputs, the program would no longer have a segmentation fault, while without the optimization it would.


### Loop Unroll
##### Description
Thie optimization unrolls loops, reducing the overhead and expanding the loop body to have multiple interactions at once, increasing code length and performance.

##### Evidence
This optimization provides unique benefit in optimizing SIP programs because it can cause decrease run time in complex looop calculations. For example, in our ablation study, we saw a 6x decrease in run time, meaning a better performance.


### Loop Strength Reduction
##### Description
This optimization reduces the strength of operations by replacing expensive operations with simpler ones, enhancing performance and reducing computational overhead.

##### Evidence
This optimization provides unique benefit in optimizing SIP programs because it can cause decrease run time. For example, in our ablation study, we saw a 1.25x decrease in run time, meaning a better performance.

### GetChildren Code Coverage
After finishing this part of the project and running code coverage, we realized we forgot to add code coverage for the getChildren methods in the ASTNodes. We then added new tests into ASTNodeTests.cpp that covered these methods. For each ASTNode, we called getChildren() on it and checked the values of each child and checked if the number of children matched the expected.

### Conclusion

The optimizations implemented in this study have demonstrated improvements in both code size reduction and performance for the programs. By applying techniques such as Global Dead Code Elimination, Merge Functions, Tail Recursion Elimination, Loop Unroll, and Loop Strength Reduction, we were able to achieve notable decreases in runtime and code size, as shown in our ablation study results. These optimizations not only enhance the efficiency. Overall, the optimizations selected were beneficial in improving the performance and reducing the complexity of SIP programs.

