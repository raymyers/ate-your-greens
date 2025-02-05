/* -*- c -*- File generated by the BNF Converter (bnfc 2.9.6). */

/* Lexer definition for use with FLex */

%option noyywrap noinput nounput
%option reentrant bison-bridge bison-locations

/* Additional data for the lexer: a buffer for lexing string literals. */
%option extra-type="Buffer"

%top{
/* strdup was not in the ISO C standard before 6/2019 (C2x), but in POSIX 1003.1.
 * See: https://en.cppreference.com/w/c/experimental/dynamic/strdup
 * Setting _POSIX_C_SOURCE to 200809L activates strdup in string.h.
 */
#define _POSIX_C_SOURCE 200809L
}
%{
#include "Absyn.h"
#include "Bison.h"

#define initialize_lexer eyg__initialize_lexer

/* BEGIN extensible string buffer */

#include "Buffer.h"

/* The initial size of the buffer to lex string literals. */
#define LITERAL_BUFFER_INITIAL_SIZE 1024

/* The pointer to the literal buffer. */
#define literal_buffer yyextra

/* Initialize the literal buffer. */
#define LITERAL_BUFFER_CREATE() literal_buffer = newBuffer(LITERAL_BUFFER_INITIAL_SIZE)

/* Append characters at the end of the buffer. */
#define LITERAL_BUFFER_APPEND(s) bufferAppendString(literal_buffer, s)

/* Append a character at the end of the buffer. */
#define LITERAL_BUFFER_APPEND_CHAR(c) bufferAppendChar(literal_buffer, c)

/* Release the buffer, returning a pointer to its content. */
#define LITERAL_BUFFER_HARVEST() releaseBuffer(literal_buffer)

/* In exceptional cases, e.g. when reaching EOF, we have to free the buffer. */
#define LITERAL_BUFFER_FREE() freeBuffer(literal_buffer)

/* END extensible string buffer */

static void update_loc(YYLTYPE* loc, char* text)
{
  loc->first_line = loc->last_line;
  loc->first_column = loc->last_column;
  int i = 0;
  for (; text[i] != '\0'; ++i) {
      if (text[i] == '\n') {
          ++loc->last_line;
          loc->last_column = 0;
      } else {
          ++loc->last_column;
      }
  }
}
#define YY_USER_ACTION update_loc(yylloc, yytext);

%}

LETTER [a-zA-Z]
CAPITAL [A-Z]
SMALL [a-z]
DIGIT [0-9]
IDENT [a-zA-Z0-9'_]
%START CHAR CHARESC CHAREND STRING ESCAPED

%%  /* Rules. */

<INITIAL>"("      	 return _LPAREN;
<INITIAL>")"      	 return _RPAREN;
<INITIAL>"="      	 return _EQ;
<INITIAL>";"      	 return _SEMI;
<INITIAL>"["      	 return _LBRACK;
<INITIAL>"]"      	 return _RBRACK;
<INITIAL>","      	 return _COMMA;
<INITIAL>"{"      	 return _LBRACE;
<INITIAL>"}"      	 return _RBRACE;
<INITIAL>"|"      	 return _BAR;
<INITIAL>"."      	 return _DOT;
<INITIAL>"-"      	 return _MINUS;
<INITIAL>"->"      	 return _RARROW;
<INITIAL>":"      	 return _COLON;
<INITIAL>".."      	 return _DDOT;
<INITIAL>"case"      	 return _KW_case;
<INITIAL>"handle"      	 return _KW_handle;
<INITIAL>"let"      	 return _KW_let;
<INITIAL>"match"      	 return _KW_match;
<INITIAL>"perform"      	 return _KW_perform;

<INITIAL>"#"[^\n]* /* skip */; /* BNFC: comment "#" */

<INITIAL>\@(\_|({DIGIT}|{LETTER}))+\:{DIGIT}+    	 yylval->_string = strdup(yytext); return T_NamedReference;
<INITIAL>{CAPITAL}(\_|({DIGIT}|{LETTER}))*    	 yylval->_string = strdup(yytext); return T_Tag;
<INITIAL>\!?(\_|{SMALL})(\_|({DIGIT}|{LETTER}))*    	 yylval->_string = strdup(yytext); return T_Id;
<INITIAL>"\""        	 LITERAL_BUFFER_CREATE(); BEGIN STRING;
<STRING>\\             	 BEGIN ESCAPED;
<STRING>\"             	 yylval->_string = LITERAL_BUFFER_HARVEST(); BEGIN INITIAL; return _STRING_;
<STRING>.              	 LITERAL_BUFFER_APPEND_CHAR(yytext[0]);
<ESCAPED>f             	 LITERAL_BUFFER_APPEND_CHAR('\f'); BEGIN STRING;
<ESCAPED>n             	 LITERAL_BUFFER_APPEND_CHAR('\n'); BEGIN STRING;
<ESCAPED>r             	 LITERAL_BUFFER_APPEND_CHAR('\r'); BEGIN STRING;
<ESCAPED>t             	 LITERAL_BUFFER_APPEND_CHAR('\t'); BEGIN STRING;
<ESCAPED>\"            	 LITERAL_BUFFER_APPEND_CHAR('"');  BEGIN STRING;
<ESCAPED>\\            	 LITERAL_BUFFER_APPEND_CHAR('\\'); BEGIN STRING;
<ESCAPED>.             	 LITERAL_BUFFER_APPEND(yytext);    BEGIN STRING;
<STRING,ESCAPED><<EOF>>	 LITERAL_BUFFER_FREE(); return _ERROR_;
<INITIAL>{DIGIT}+      	 yylval->_int = atoi(yytext); return _INTEGER_;
<INITIAL>[ \t\r\n\f]      	 /* ignore white space. */;
<INITIAL>.      	 return _ERROR_;

%%  /* Initialization code. */

yyscan_t initialize_lexer(FILE *inp)
{
  yyscan_t scanner;
  if (yylex_init_extra(NULL, &scanner)) return 0;
  if (inp) yyrestart(inp, scanner);
  return scanner;
}

