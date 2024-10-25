Deliverable 2:
=========

## AST Node Implementation (AST[].cpp and .h files)

In summary we added the following nodes:
1. ASTTernaryExpr
2. ASTArrayOfExpr
3. ASTArrayMulExpr
4. ASTArrayIndexExpr
5. ASTLengthExpr
6. ASTNotExpr
7. ASTNegExpr
8. ASTBooleanExpr
9. ASTIncrementStmt
10. ASTDecrementStmt
11. ASTForStmt
12. ASTForRangeStmt

**True and False --> Boolean Expression**
- Added Boolean node to handle true and false keywords
    - ASTBooleanExpr.cpp
    - ASTBooleanExpr.h

**Not and Negative Expressions**
- Two files and headers added to handle new node type not and "-" (negative) expressions
    - ASTNegExpr.cpp
    - ASTNegExpr.h
    - ASTNotExpr.cpp
    - ASTNotExpr.h

**And, Or, and Mod, Relational Exprs**
- And, or, and mod were added under vistBinaryExpr in builder.cpp
- Relational operators were added similarly, no new files created

**Array Type**
- split into Array Of and Array Mul (more than one expr)
    - ASTArrayOfExpr.cpp
    - ASTArrayOfExpr.h
    - ASTArrayMulExpr.cpp
    - ASTArrayMulExpr.h
- array operator nodes were also added:
    - ASTArrayIndexExpr.cpp
    - ASTArrayIndexExpr.h
    - ASTLengthExpr.cpp
    - ASTLengthExpr.h


**Increment and Decrement Statements**
- These were implemented as two separate nodes for ease
    - ASTIncrementStmt.cpp
    - ASTIncrementStmt.h
    - ASTDecrementStmt.cpp
    - ASTDecrementStmt.h

**Ternary Expression**
- Single node implemented
    - ASTTernaryExpr.cpp
    - ASTTernaryExpr.h

**For Loops**
- Separated into two types: for range and traditional 
    - ASTForStmt.cpp
    - ASTForStmt.h
    - ASTForRangeStmt.cpp
    - ASTForRangeStmt.h

## Pretty Printer Implementation (endVisit and visits)
Implementations 
1. ASTTernaryExpr :: endVisit
2. ASTArrayOfExpr :: endVisit
3. ASTArrayMulExpr :: endVisit
4. ASTArrayIndexExpr :: endVisit
5. ASTLengthExpr :: endVisit
6. ASTNotExpr :: endVisit
7. ASTNegExpr :: endVisit
8. ASTBooleanExpr :: endVisit
9. ASTIncrementStmt :: endVisit
10. ASTDecrementStmt :: endVisit
11. ASTForStmt :: endVisit + visit
12. ASTForRangeStmt :: endVisit + visit
Visit methods were for nodes that needed some type of extra formatting/ indentation such as the for loops. The rest do not have visit methods since they did not need the formatting additions.

## Methodology 
There were 2 main parts that we considered: creating the nodes themselves, creating the pretty printer methods, and then their respective tests. Our idea was to start with the more difficult parts, and then ease our way down, going from nodes -> testing -> pretty printer -> testing and more testing. 

We initially planned to create and test incrementally, tackling each node one at a time. However, we found that our approach to creating the nodes improved as time went on. This led us to realize that our earlier nodes could benefit from modifications and so testing each node as we went would have required constantly updating all our previous tests to align with these changes, which was rather complicated due to the number of files involved. 

After we finished the majority of the more difficult nodes to tackle (arrays and for loops), we began testing them starting with base cases for each type, and then adding more for cases that weren't covered originally such as writing an array empty array vs a filled array. 

We then moved onto to the pretty printer, but this time incrementally testing as they were implemented as this section was easier to implement.

The last part was just ensuring that our code had sufficient coverage, adding tests for each nodes print methods in ASTNodeTests.cpp, and in general adding tests where we thought were necessary. For every new node we added, we exlcluded the get children and codegen methods, and we added tests for the accept and print methods in ASTNodeTests.cpp.

## Tricky Parts
Though we started with pair programming, we did split off for the sake of efficiency. Testing someone else's code was a little tricky and implementing pretty printer methods on nodes that were not self implemented created some complications since there was a slight lack of understanding. 

Additionally, simply deciding the nature of the nodes was rather difficult. For example the boolean was implemented similar to a number expression, but there was debate on how it should be implemented and why as well. We ultimately had to decide what was feasible for now, and accept the consequences of difficulties later (such as putting increment and decrement separately). Some nodes were also split into two, while others were condensed after much contemplation.


## Design Changes
The main design changes dealt with node implementation. Attempts were made to create one node for the for loop statement, however this ended being too complex and so we split them up. The same goes for the arrays as well. Boolean was the main special case that we debated the design of. Unlike the rest of the nodes, true and false had special meaning in the language as they were types themselves so the implementation was tricky. Ultimately we decided that having one node for the sake of types and later ease would be best.
