Deliverable 4: Code Generation
=========

## Methodology
Our implementation was done from the easiest for hardest so we could get a grasp on the IR builder and explore before we
implemented the arrays and for-loops.

While writing the code-generation methods, we didn't initially write "actual" system tests, but instead opted for small
tests that we manually compiled and checked.

The methodology was like this:
1. Comment out code generation in the node and write base case
2. Build and test for basic functionality e.g.: 

``` 
cd bin
./cleancov.sh
./build.sh --asm --do [file_name] // For checking assembly
./build.sh [file_name] for running the file and checking values
```

3. Writing system tests to check for edge cases and adding more functionality to our methods




## Tricky Parts
The main tricky part of this was the array type implementation. Initially considering our original nodes,
we opted for three constuctors:
1. standard constructor for an array [1,2,3]
2. array of constructor [1 of true]
3. an empty constructor.

Additionally, we added two booleans, is_empty and array_of to check the details of the array. This was more difficult
as had complications in the type constraints, and some of the constructors seemed to overlap at the time. Eventually we
decided to simplify the design, and get rid of the standard constructor. We didn't consider this at first since we were
thinking that an array such as [1,2,3] wouldn't be possible since creating an "of" would create multiple of the specified
element, not allowing us to have diversity in the elements. However, we then realized that because we are only do types
that we do not need to consider that aspect.

Testing the array constraints were also difficult as we had to think of how to make the return value while indexing an
array the same type as the elements in the array without being able to directly access them. Another hard part was
checking that the return type of an empty array was alpha. We ended up settling for code coverage, as we couldn't figure
out how to use the alpha type comparison, though we did print it out and verify that it was correct.


## Design Changes
Considering everything, the main design change that we would make is how the array was constructed. Though we ended up
with something more simple in the end, we feel that it could still be improved. Additionally, since we spent so much time
on having three constructors, there may have also been a path where that worked. The other implementation were not too
difficult, so we did not consider design changes there.