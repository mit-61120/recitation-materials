lexer grammar MITScript;
 
// Lexer Rules

// Constants
INT_CONSTANT : [0-9]+ ;
TRUE_KEY : 'true';
FALSE_KEY : 'false' ;
BOOL_CONSTANT : ( TRUE_KEY | FALSE_KEY ) ;
NONE_CONSTANT : 'None' ;

// Binary operations / values
ADD_KEY : '+' ;
SUB_KEY : '-' ;
MUL_KEY : '*' ;
EQ_KEY : '==' ;
LT_KEY : '<' ;

// Keys for stmts
ASSIGN_KEY : '=' ;
IF_KEY : 'if' ;
SCOLON_KEY : ';' ;

OPAREN_KEY : '(' ;
CPAREN_KEY : ')' ;
OBRACK_KEY : '{' ;
CBRACK_KEY : '}' ;

NAME : ([a-zA-Z_]) ([a-zA-Z_0-9])* ;
COMMENT: '//'~( '\r' | '\n' )* -> skip ;
WHITESPACE : ( '\t' | ' ' | '\r' | '\n'| '\u000C' )+ -> skip ;
// The rest of your lexical rules go here

ERROR : . ; // Must keep as last rule in grammar!
