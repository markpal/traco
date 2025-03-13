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

#ifndef YY_YY_PETITY_H_INCLUDED
# define YY_YY_PETITY_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    TCOMMENT = 258,
    TASSERT = 259,
    TBY = 260,
    TCEILING = 261,
    TCOLON = 262,
    TCOMMA = 263,
    TCONST = 264,
    TDO = 265,
    TDOANY = 266,
    TELSE = 267,
    TENDFOR = 268,
    TENDIF = 269,
    TEQ = 270,
    TEQUAL = 271,
    TEXP = 272,
    TFLOAT = 273,
    TFLOOR = 274,
    TFOR = 275,
    TGE = 276,
    TGT = 277,
    TRAND = 278,
    TID = 279,
    TIF = 280,
    TINT = 281,
    TINTEGER = 282,
    TLE = 283,
    TLT = 284,
    TLP = 285,
    TMAX = 286,
    TMIN = 287,
    TMINUS = 288,
    TMOD = 289,
    TNE = 290,
    TAND = 291,
    TOR = 292,
    TNOT = 293,
    TPARFOR = 294,
    TPLUS = 295,
    TREAL = 296,
    TRP = 297,
    TSEMI = 298,
    TSLASH = 299,
    TSQRT = 300,
    TSTAR = 301,
    TTHEN = 302,
    TTO = 303,
    TVECFOR = 304,
    TLCB = 305,
    TRCB = 306,
    TFORMAL = 307,
    TCOMMON = 308,
    TSTATIC = 309,
    TAUTO = 310,
    TPRIVATE = 311,
    TBUILTIN = 312,
    TIN = 313,
    TOUT = 314,
    TINOUT = 315,
    TRETURN = 316,
    TPLUSEQUAL = 317,
    TSTAREQUAL = 318,
    TMAXEQUAL = 319,
    TMINEQUAL = 320
  };
#endif
/* Tokens.  */
#define TCOMMENT 258
#define TASSERT 259
#define TBY 260
#define TCEILING 261
#define TCOLON 262
#define TCOMMA 263
#define TCONST 264
#define TDO 265
#define TDOANY 266
#define TELSE 267
#define TENDFOR 268
#define TENDIF 269
#define TEQ 270
#define TEQUAL 271
#define TEXP 272
#define TFLOAT 273
#define TFLOOR 274
#define TFOR 275
#define TGE 276
#define TGT 277
#define TRAND 278
#define TID 279
#define TIF 280
#define TINT 281
#define TINTEGER 282
#define TLE 283
#define TLT 284
#define TLP 285
#define TMAX 286
#define TMIN 287
#define TMINUS 288
#define TMOD 289
#define TNE 290
#define TAND 291
#define TOR 292
#define TNOT 293
#define TPARFOR 294
#define TPLUS 295
#define TREAL 296
#define TRP 297
#define TSEMI 298
#define TSLASH 299
#define TSQRT 300
#define TSTAR 301
#define TTHEN 302
#define TTO 303
#define TVECFOR 304
#define TLCB 305
#define TRCB 306
#define TFORMAL 307
#define TCOMMON 308
#define TSTATIC 309
#define TAUTO 310
#define TPRIVATE 311
#define TBUILTIN 312
#define TIN 313
#define TOUT 314
#define TINOUT 315
#define TRETURN 316
#define TPLUSEQUAL 317
#define TSTAREQUAL 318
#define TMAXEQUAL 319
#define TMINEQUAL 320

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 116 "../src/petity.y" /* yacc.c:1909  */

    int iv;
    node *np;
    symtabentry *stp;
    optype op;
    

#line 192 "petity.h" /* yacc.c:1909  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PETITY_H_INCLUDED  */
