
grammar Eyg;

program
    : expr EOF
    ;

listExpr
    : '[' (items+=listItem (',' items+=listItem)*)? ']'
    ;

listItem
    : '..' IDENTIFIER # LISpread
    | expr2 # LIExpr
    ;

recordField
    : '..' IDENTIFIER # RFSpread
    | IDENTIFIER ':' expr2 # RFKeyVal
    ;

expr
    : expr2 # EInner
    | letExpr # ELet
    ;

letExpr
    : matchPattern '=' letVal=expr body=expr
    {
        $letVal.ctx.getStop().getLine() != $body.ctx.getStart().getLine()
 	}?
    | matchPattern '=' letVal=expr ';' body=expr
    ;

expr2
    : expr3 # E2Inner
    | left=expr3 op=binOp1 right=expr3 # E2BinOp
    ;

binOp1
    : '<'
    | '>'
    ;

binOp2
    : '+'
    | '-'
    ;

binOp3
    : '*'
    | '/'
    ;

expr3
    : expr4 # E3Inner
    | left=expr3 op=binOp2 right=expr4 # E3BinOp
    ;

expr4
    : term # E4Term
    | left=expr4 op=binOp3 right=term # E4BinOp
    ;

matchExpr
    : 'match' expr '{' matchCase+ '}'
    ;

matchCase
    : matchPattern '->' expr
    ;

matchPattern
    : tag=IDENTIFIER matchPattern # MPTagged
    | id=IDENTIFIER # MPId
    | '(' matchPattern ')' # MPParen
    | '{' fields+=matchRecordField (',' fields+=matchRecordField)* '}' # MPRecord
    ;

matchRecordField
    : key=IDENTIFIER ':' matchPattern
    ;

term
    : id_ # TId
    | '@' IDENTIFIER ':' INT # TNamedReference
    | integer # TInt
    | STRING # TStr
    | func # TFunc
    | term '.' field=IDENTIFIER # TSelect
    | matchExpr # TMatch
    | obj=term openPar='(' args+=expr2 (',' args+=expr2)* ')'
          {
              $obj.ctx.getStop().getLine() == $openPar.getLine()
       	}? # TApply
    | id_ args+=expr2
          {
                $id_.ctx.getStart().getCharPositionInLine() < $args.get(0).getStart().getCharPositionInLine()
          }? # TTagged
    | '(' expr ')' # TParen
    | listExpr # TList
    | '{' expr '}' # TBlock
    | '{' (fields+=recordField (',' fields+=recordField)* )? '}'? # TRecord
    | 'perform' expr2 # TPerform
    ;

func
    : '|' (params+=matchPattern (',' params+=matchPattern)*)? '|' body=expr2
    ;

id_
    : '!'? IDENTIFIER
    ;

MATCH : 'match';


IDENTIFIER : [a-zA-Z_] [a-zA-Z0-9_]*;

integer
    : neg='-'? INT
    ;

STRING
    : '"' ~["]* '"'
    ;

LT: '<';
GT: '>';

INT
    : [0-9]+
    ;

WS
    : [ \r\n\t] -> skip
    ;

LINE_COMMENT
    : '#' ~[\r\n]* -> skip
    ;