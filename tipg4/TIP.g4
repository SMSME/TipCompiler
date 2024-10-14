grammar TIP;
// Grammar for Moeller and Schwartzbach's Tiny Imperative Language (TIP)

////////////////////// TIP Programs ////////////////////////// 

program : (function)+
;

function : nameDeclaration 
           '(' (nameDeclaration (',' nameDeclaration)*)? ')'
           KPOLY?
           '{' (declaration*) (statement*) returnStmt '}' 
;

////////////////////// TIP Declarations ///////////////////////// 

declaration : KVAR nameDeclaration (',' nameDeclaration)* ';' ;

nameDeclaration : IDENTIFIER ;

////////////////////// TIP Expressions ////////////////////////// 

// Expressions in TIP are ordered to capture precedence.
// We adopt the C convention that orders operators as:
//   postfix, unary, multiplicative, additive, relational, and equality 
//
// NB: # creates rule label that can be accessed in visitor
//
// ANTLR4 can automatically refactor direct left-recursion so we
// place all recursive rules as options in a single rule.  This
// means that we have some complex rules here that might otherwise
// be separated out, e.g., funAppExpr, and that we can't factor out
// other useful concepts, e.g., defining a rule for the subset of
// expressions that can be used as an l-value.  We prefer a clean 
// grammar, which simplifies AST construction, and work around these
// issues elsewhere in the compiler, e.g.,  introducing an assignable expr
// weeding pass. 
//
expr : expr '(' (expr (',' expr)*)? ')' 	#funAppExpr
     | expr '.' IDENTIFIER 			#accessExpr
     | expr '[' expr ']'        #arrayIndexExpr // added
     | '*' expr 				#deRefExpr
     | SUB NUMBER				#negNumber
     | SUB expr                 #negExpr // added
     | '&' expr					#refExpr
     | KNOT expr                 #notExpr // added
     | LEN expr                 #lengthExpr // added
     | expr op=(MUL | DIV | MOD) expr 		#multiplicativeExpr // added
     | expr op=(ADD | SUB) expr 		#additiveExpr
     | expr op=(GT | LT | GTE | LTE) expr 				#relationalExpr // added
     | expr op=(EQ | NE) expr 			#equalityExpr
     | expr op=(KAND) expr          #andExpr
     | expr op=(KOR) expr          #orExpr
     | IDENTIFIER				#varExpr
     | NUMBER					#numExpr
     | KINPUT					#inputExpr
     | KALLOC expr				#allocExpr
     | KNULL					#nullExpr
     | KTRUE                    #trueExpr
     | KFALSE                   #falseExpr
     | <assoc=right> expr '?' expr ':' expr          #ternaryExpr //added
     | recordExpr				#recordRule
     | arrayExpr                #arrayRule
     | '(' expr ')'				#parenExpr
;

recordExpr : '{' (fieldExpr (',' fieldExpr)*)? '}' ;

fieldExpr : IDENTIFIER ':' expr ;

arrayExpr : '[' (expr (',' expr)*)? ']' 
    | '[' expr 'of' expr ']'; //added

////////////////////// TIP Statements ////////////////////////// 

statement : blockStmt
    | assignStmt
    | whileStmt
    | ifStmt
    | outputStmt
    | errorStmt
    | forStmt //change start
    | forRangeStmt
    | incrementStmt
;

assignStmt : expr '=' expr ';' ;

blockStmt : '{' (statement*) '}' ;

whileStmt : KWHILE '(' expr ')' statement ;

ifStmt : KIF '(' expr ')' statement (KELSE statement)? ;

outputStmt : KOUTPUT expr ';'  ;

errorStmt : KERROR expr ';'  ;

returnStmt : KRETURN expr ';'  ;

forStmt : KFOR '(' expr ':' expr ')' statement  ; // changes start

forRangeStmt : KFOR '(' expr ':' expr  '..' expr ('by' expr)? ')' statement   ;

incrementStmt : expr (INCR | DECR) ';' ;



////////////////////// TIP Lexicon ////////////////////////// 

// By convention ANTLR4 lexical elements use all caps

MUL : '*' ;
DIV : '/' ;
ADD : '+' ;
SUB : '-' ;
GT  : '>' ;
EQ  : '==' ;
NE  : '!=' ;
MOD : '%' ; // new additions below
LT  : '<' ;
GTE : '>=' ; 
LTE : '<=' ; 
INCR : '++' ;
DECR : '--' ;
LEN : '#'; 


NUMBER : [0-9]+ ;

// Placing the keyword definitions first causes ANTLR4 to prioritize
// their matching relative to IDENTIFIER (which comes later).
KALLOC  : 'alloc' ;
KINPUT  : 'input' ;
KWHILE  : 'while' ;
KIF     : 'if' ;
KELSE   : 'else' ;
KVAR    : 'var' ;
KRETURN : 'return' ;
KNULL   : 'null' ;
KOUTPUT : 'output' ;
KERROR  : 'error' ;
KFALSE  : 'false' ; // added keyword false
KTRUE   : 'true'  ; // added keyword true
KFOR    : 'for'   ; // added for
KNOT : 'not' ; 
KAND : 'and' ;
KOR  : 'or' ; 

// Keyword to declare functions as polymorphic
KPOLY   : 'poly' ;

IDENTIFIER : [a-zA-Z_][a-zA-Z0-9_]* ;

// ANTLR4 has a nice mechanism for specifying the characters that should
// skipped during parsing.  You write "-> skip" after the pattern and
// let ANTLR4s pattern matching do the rest.

// Ignore whitespace
WS : [ \t\n\r]+ -> skip ;

// This does not handle nested block comments.
BLOCKCOMMENT: '/*' .*? '*/' -> skip ;

COMMENT : '//' ~[\n\r]* -> skip ;
