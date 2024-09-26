Deliverable 1:
=========

## Changes
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

## Tricky Parts
There was a lot of back and forth on where certain elements should go. For example, reference and dereference were used as literals within the expression, and similarly the length operator, #, could have also been put as a literal in the expression. The same could be said for the increments and decrements. We also implemented "and" and "or" as keywords specifically, but expressed them such as "expr op=(KAND | KOR) expr" to show how they are used as operators as well. This was to clarify they shouldn't be used as identifiers, but also that they are logical operators.

Finally, after class discussions about left recursions and associativity we also contemplated how to write the ternary expression such that no problems would occur.


## Design Changes
We considering grouping the increment and decrement statements as well as the booleans together. For example, we considered having the increment and decrement statements similar to how expressions were set up like incrementStmt : expr (DECR | INCR) ';' ; and the booleans under a condtional expression and have them as two options as well. However, we decided against this to make the divide more clear between the two options, but in the future there if structuring the grammar like this has errors when it comes to typing them, then we will deal with it then. 