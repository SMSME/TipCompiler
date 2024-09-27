Deliverable 1:
=========

## Grammar Changes
**True and False**
- Added 'KTRUE' and 'KFALSE' keyword definitions 

**Unary Operator**
- KNOT : 'not' ..added under lexicon
- KNOT expr  //added

**Non-short Cicruit Binary  Operators**
- KAND and KOR // added under keywords
- expr op=(KAND | KOR) expr        #orExpr // added under expressions

**Array Type**
- arrayExpr : '[' (expr (',' expr)*)? ']' 
    | '[' expr 'of' expr ']'; //added

**Arithmetic Operator Extension**
- expr op=(MUL | DIV | MOD) expr - modulo addeded to multiplicative
- SUB expr                 #negExpr // added

**Relational Operator Extension**
- LT  : '<' ; //  added in lexicon
- GTE : '>=' ; 
- LTE : '<=' ; 
- expr op=(GT | LT | GTE | LTE) expr  // added in expressions

**Increment and Decrement Statements**
- INCR : '++' ;
- DECR : '--' ; // added in lexicon
- incrementStmt : expr INCR ';' ; // statements added
- decrementStmt : expr DECR ';' ;

**Ternary Conditional Expression**
- <assoc=right> expr '?' expr ':' expr  // expression added

**For Loop Iterator**
- forStmt : KFOR '(' expr ':' expr ')' statement  ; // statement added

**For Loop Range**
- forRangeStmt : KFOR '(' expr ':' expr  '..' expr ('by' expr)? ')' statement   ; // statement added

## Testing
For each new addition, we decided that we would write base test cases and then after ensuring that these don't fail, we would write more. For example in the for array creation, we had a basic test for an empty array, one item, and then multiple items. Then we extended the tests, adding new test cases that tried statements within the array instead of using expressions to ensure that it failed. Afterwards we tested the additional functionality such as indexing our base cases with the '#' operator. 

After we established tests for all of our new code, we went through it again with more failing test cases to ensure that there wasn't anything weird that could possibly pass such as the multitude of failing tests for the ternary expression where we considered taking away each of the parts until it became redundant.

In terms of the actual style for test cases, we first wrote them individually. For example, there was one test case for passing relational operators "<", "<=", ">=", but after going through the TIP tests again we thought we should consolidate them, making them easier to find and read since there was significantly less text. So this lead to us having larger test cases, covering more. However, we primarily left failing test cases by themselves for the sake of finding bugs more easily in cases where our grammar should not pass.

## Tricky Parts
There was a lot of back and forth on where certain elements should go. For example, reference and dereference were used as literals within the expression, and similarly the length operator, #, could have also been put as a literal in the expression. The same could be said for the increments and decrements. We also implemented "and" and "or" as keywords specifically, but expressed them such as "expr op=(KAND | KOR) expr" to show how they are used as operators as well. This was to clarify they shouldn't be used as identifiers, but also that they are logical operators.

Finally, after class discussions about left recursions and associativity we also contemplated how to write the ternary expression such that no problems would occur.


## Design Changes
We considering grouping the increment and decrement statements as well as the booleans together. For example, we considered having the increment and decrement statements similar to how expressions were set up like incrementStmt : expr (DECR | INCR) ';' ; and the booleans under a condtional expression and have them as two options as well. However, we decided against this to make the divide more clear between the two options, but in the future there if structuring the grammar like this has errors when it comes to typing them, then we will deal with it then. 