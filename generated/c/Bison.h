/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_EYG_BISON_H_INCLUDED
# define YY_EYG_BISON_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int eyg_debug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    _ERROR_ = 258,                 /* _ERROR_  */
    _LPAREN = 259,                 /* _LPAREN  */
    _RPAREN = 260,                 /* _RPAREN  */
    _COMMA = 261,                  /* _COMMA  */
    _MINUS = 262,                  /* _MINUS  */
    _RARROW = 263,                 /* _RARROW  */
    _DOT = 264,                    /* _DOT  */
    _DDOT = 265,                   /* _DDOT  */
    _COLON = 266,                  /* _COLON  */
    _SEMI = 267,                   /* _SEMI  */
    _EQ = 268,                     /* _EQ  */
    _LBRACK = 269,                 /* _LBRACK  */
    _RBRACK = 270,                 /* _RBRACK  */
    _KW_case = 271,                /* _KW_case  */
    _KW_handle = 272,              /* _KW_handle  */
    _KW_let = 273,                 /* _KW_let  */
    _KW_match = 274,               /* _KW_match  */
    _KW_perform = 275,             /* _KW_perform  */
    _LBRACE = 276,                 /* _LBRACE  */
    _BAR = 277,                    /* _BAR  */
    _RBRACE = 278,                 /* _RBRACE  */
    T_Id = 279,                    /* T_Id  */
    T_NamedReference = 280,        /* T_NamedReference  */
    T_Tag = 281,                   /* T_Tag  */
    _STRING_ = 282,                /* _STRING_  */
    _INTEGER_ = 283                /* _INTEGER_  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 116 "Eyg.y"

  int    _int;
  char   _char;
  double _double;
  char*  _string;
  Program program_;
  Exp exp_;
  ListListItem listlistitem_;
  ListRecordField listrecordfield_;
  ListMatchItem listmatchitem_;
  ListExp listexp_;
  ListParam listparam_;
  MatchItem matchitem_;
  MatchPattern matchpattern_;
  RecordField recordfield_;
  Param param_;
  ListItem listitem_;

#line 111 "Bison.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif




int eyg_parse (yyscan_t scanner, YYSTYPE *result);


#endif /* !YY_EYG_BISON_H_INCLUDED  */
