Deliverable 3:
=========

## Weeding Pass

**Array Index Expression**

**For Statement**
* For range
* General for loop

**Increment and Decrement Statements**


In general, we looked for statements with assignable positions to choose what to include in the weeding pass.
Everything that we thought had an L-value was included. Specifically we addded the for-loops when considering
the "i" in the loops that are assignable.


## Type System
**Boolean Type**
* We added two files, under the concrete types: TipBoolean.cpp and TipBoolean.h. 
This was to establish the "true" and "false" values in the system.

**Array Type**
- This also had two files, TipArray.cpp and TipArray.h. Specifically we 
implemented the array with 2 constructors, one considering the general array
and the other considering an empty array.

In total we created 4 new files in src/semantic/types/concrete. These were TipBoolean.h, TipBoolean.cpp, TipArray.h, and
TipArray.cpp. At first, we implemented TipBoolean because we thought it would be a good idea to figure out what exactly 
we needed to do for a new type before tackling TipArray, which we believed to be harder. To fully implement everything, 
we modified TipCons, TypeVisitor, and TypeConstraintVisitor.

## Type Constraints
We added type constraints to all the new features we have previously implemented in the first
couple of deliverables. This includes:
1. Binary Operators: >, >=, <, <=, %, and, or
2. Not and Negative expressions
3. Arrays (including array length and index)
4. Booleans
5. Increment and Decrement
6. Ternary

During this section we had to consider all the parts of the nodes (as previously implemented), and checked
to ensure that their types were followed properly, e.g. the index of an array must be an int.

## Methodology
Our implementation was in order of:
1. Implementing the type system --> testing
2. Implementing the weeding pass --> testing
3. Implementing type constraints --> testing

However, we realized with array that even though our tests for the type passed, the way we constructed the type
led to a lot of errors when trying to deal with the constraints. Because of that, we went back and forth with altering 
the implementation of the type, and then checking the results that it had on the constraints. The general idea was that
we write some code for a specific node, and then we test that node.

In our testing, we modified the substitutor and additionally though we did alter the TypeHelpher, we did not end up 
using the implementations and instead just created the concrete types ourselves. After finishing each section we ran the 
code coverage tests to check what we could have possibly missed, ensuring that everything was covered.


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