/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

#ifndef YY_HPP_YY_HPPY_H_INCLUDED
# define YY_HPP_YY_HPPY_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int hpp_yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    p1 = 258,
    p2 = 259,
    INTERSECTION = 260,
    p3 = 261,
    p4 = 262,
    p5 = 263,
    p6 = 264,
    NOT = 265,
    p7 = 266,
    p8 = 267,
    p9 = 268,
    p10 = 269,
    p11 = 270,
    VAR = 271,
    INT = 272,
    ALIGN = 273,
    DISTRIBUTE = 274,
    PROCESSORS = 275,
    TEMPLATE = 276,
    WITH = 277,
    ONTO = 278,
    CYCLIC = 279,
    BLOCK = 280,
    STAR = 281,
    LPAREN = 282,
    RPAREN = 283,
    COMMA = 284
  };
#endif
/* Tokens.  */
#define p1 258
#define p2 259
#define INTERSECTION 260
#define p3 261
#define p4 262
#define p5 263
#define p6 264
#define NOT 265
#define p7 266
#define p8 267
#define p9 268
#define p10 269
#define p11 270
#define VAR 271
#define INT 272
#define ALIGN 273
#define DISTRIBUTE 274
#define PROCESSORS 275
#define TEMPLATE 276
#define WITH 277
#define ONTO 278
#define CYCLIC 279
#define BLOCK 280
#define STAR 281
#define LPAREN 282
#define RPAREN 283
#define COMMA 284

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 99 "../src/hppy.y" /* yacc.c:1909  */

    List<int> *INTEGER_LIST;
    char *VAR_NAME;
    int INT_VALUE;
    List<Variable_ID> *VAR_LIST;
    List<dist_info> *DISTLIST;
    dist_info *DISTINFO;
    Relation * RELATION;
    Exp *EXP;
    ExpList *EXP_LIST;
    tupleDescriptor * TUPLE_DESCRIPTOR;

#line 125 "hppy.h" /* yacc.c:1909  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE hpp_yylval;

int hpp_yyparse (void);

#endif /* !YY_HPP_YY_HPPY_H_INCLUDED  */
