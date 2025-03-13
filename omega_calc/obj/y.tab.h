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

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
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
    VAR = 258,                     /* VAR  */
    INT = 259,                     /* INT  */
    STRING = 260,                  /* STRING  */
    OPEN_BRACE = 261,              /* OPEN_BRACE  */
    CLOSE_BRACE = 262,             /* CLOSE_BRACE  */
    SYMBOLIC = 263,                /* SYMBOLIC  */
    OR = 264,                      /* OR  */
    AND = 265,                     /* AND  */
    NOT = 266,                     /* NOT  */
    ST = 267,                      /* ST  */
    APPROX = 268,                  /* APPROX  */
    IS_ASSIGNED = 269,             /* IS_ASSIGNED  */
    FORALL = 270,                  /* FORALL  */
    EXISTS = 271,                  /* EXISTS  */
    OMEGA_DOMAIN = 272,            /* OMEGA_DOMAIN  */
    RANGE = 273,                   /* RANGE  */
    DIFFERENCE = 274,              /* DIFFERENCE  */
    DIFFERENCE_TO_RELATION = 275,  /* DIFFERENCE_TO_RELATION  */
    GIST = 276,                    /* GIST  */
    GIVEN = 277,                   /* GIVEN  */
    HULL = 278,                    /* HULL  */
    WITHIN = 279,                  /* WITHIN  */
    MAXIMIZE = 280,                /* MAXIMIZE  */
    MINIMIZE = 281,                /* MINIMIZE  */
    AFFINE_HULL = 282,             /* AFFINE_HULL  */
    VENN = 283,                    /* VENN  */
    CONVEX_COMBINATION = 284,      /* CONVEX_COMBINATION  */
    POSITIVE_COMBINATION = 285,    /* POSITIVE_COMBINATION  */
    CONVEX_HULL = 286,             /* CONVEX_HULL  */
    CONIC_HULL = 287,              /* CONIC_HULL  */
    LINEAR_HULL = 288,             /* LINEAR_HULL  */
    PAIRWISE_CHECK = 289,          /* PAIRWISE_CHECK  */
    CONVEX_CHECK = 290,            /* CONVEX_CHECK  */
    MAXIMIZE_RANGE = 291,          /* MAXIMIZE_RANGE  */
    MINIMIZE_RANGE = 292,          /* MINIMIZE_RANGE  */
    MAXIMIZE_DOMAIN = 293,         /* MAXIMIZE_DOMAIN  */
    MINIMIZE_DOMAIN = 294,         /* MINIMIZE_DOMAIN  */
    LEQ = 295,                     /* LEQ  */
    GEQ = 296,                     /* GEQ  */
    NEQ = 297,                     /* NEQ  */
    GOES_TO = 298,                 /* GOES_TO  */
    COMPOSE = 299,                 /* COMPOSE  */
    JOIN = 300,                    /* JOIN  */
    INVERSE = 301,                 /* INVERSE  */
    COMPLEMENT = 302,              /* COMPLEMENT  */
    IN = 303,                      /* IN  */
    CARRIED_BY = 304,              /* CARRIED_BY  */
    TIME = 305,                    /* TIME  */
    TIMECLOSURE = 306,             /* TIMECLOSURE  */
    UNION = 307,                   /* UNION  */
    INTERSECTION = 308,            /* INTERSECTION  */
    VERTICAL_BAR = 309,            /* VERTICAL_BAR  */
    SUCH_THAT = 310,               /* SUCH_THAT  */
    SUBSET = 311,                  /* SUBSET  */
    ITERATIONS = 312,              /* ITERATIONS  */
    SPMD = 313,                    /* SPMD  */
    CODEGEN = 314,                 /* CODEGEN  */
    DECOUPLED_FARKAS = 315,        /* DECOUPLED_FARKAS  */
    FARKAS = 316,                  /* FARKAS  */
    TCODEGEN = 317,                /* TCODEGEN  */
    TRANS_IS = 318,                /* TRANS_IS  */
    SET_MMAP = 319,                /* SET_MMAP  */
    UNROLL_IS = 320,               /* UNROLL_IS  */
    PEEL_IS = 321,                 /* PEEL_IS  */
    MAKE_UPPER_BOUND = 322,        /* MAKE_UPPER_BOUND  */
    MAKE_LOWER_BOUND = 323,        /* MAKE_LOWER_BOUND  */
    REL_OP = 324,                  /* REL_OP  */
    RESTRICT_DOMAIN = 325,         /* RESTRICT_DOMAIN  */
    RESTRICT_RANGE = 326,          /* RESTRICT_RANGE  */
    SUPERSETOF = 327,              /* SUPERSETOF  */
    SUBSETOF = 328,                /* SUBSETOF  */
    SAMPLE = 329,                  /* SAMPLE  */
    SYM_SAMPLE = 330,              /* SYM_SAMPLE  */
    PROJECT_AWAY_SYMBOLS = 331,    /* PROJECT_AWAY_SYMBOLS  */
    PROJECT_ON_SYMBOLS = 332,      /* PROJECT_ON_SYMBOLS  */
    REACHABLE_FROM = 333,          /* REACHABLE_FROM  */
    REACHABLE_OF = 334,            /* REACHABLE_OF  */
    ASSERT_UNSAT = 335,            /* ASSERT_UNSAT  */
    PARSE_EXPRESSION = 336,        /* PARSE_EXPRESSION  */
    PARSE_FORMULA = 337,           /* PARSE_FORMULA  */
    PARSE_RELATION = 338,          /* PARSE_RELATION  */
    p1 = 339,                      /* p1  */
    p2 = 340,                      /* p2  */
    p3 = 341,                      /* p3  */
    p4 = 342,                      /* p4  */
    p5 = 343,                      /* p5  */
    p6 = 344,                      /* p6  */
    p7 = 345,                      /* p7  */
    p8 = 346,                      /* p8  */
    p9 = 347,                      /* p9  */
    p10 = 348                      /* p10  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define VAR 258
#define INT 259
#define STRING 260
#define OPEN_BRACE 261
#define CLOSE_BRACE 262
#define SYMBOLIC 263
#define OR 264
#define AND 265
#define NOT 266
#define ST 267
#define APPROX 268
#define IS_ASSIGNED 269
#define FORALL 270
#define EXISTS 271
#define OMEGA_DOMAIN 272
#define RANGE 273
#define DIFFERENCE 274
#define DIFFERENCE_TO_RELATION 275
#define GIST 276
#define GIVEN 277
#define HULL 278
#define WITHIN 279
#define MAXIMIZE 280
#define MINIMIZE 281
#define AFFINE_HULL 282
#define VENN 283
#define CONVEX_COMBINATION 284
#define POSITIVE_COMBINATION 285
#define CONVEX_HULL 286
#define CONIC_HULL 287
#define LINEAR_HULL 288
#define PAIRWISE_CHECK 289
#define CONVEX_CHECK 290
#define MAXIMIZE_RANGE 291
#define MINIMIZE_RANGE 292
#define MAXIMIZE_DOMAIN 293
#define MINIMIZE_DOMAIN 294
#define LEQ 295
#define GEQ 296
#define NEQ 297
#define GOES_TO 298
#define COMPOSE 299
#define JOIN 300
#define INVERSE 301
#define COMPLEMENT 302
#define IN 303
#define CARRIED_BY 304
#define TIME 305
#define TIMECLOSURE 306
#define UNION 307
#define INTERSECTION 308
#define VERTICAL_BAR 309
#define SUCH_THAT 310
#define SUBSET 311
#define ITERATIONS 312
#define SPMD 313
#define CODEGEN 314
#define DECOUPLED_FARKAS 315
#define FARKAS 316
#define TCODEGEN 317
#define TRANS_IS 318
#define SET_MMAP 319
#define UNROLL_IS 320
#define PEEL_IS 321
#define MAKE_UPPER_BOUND 322
#define MAKE_LOWER_BOUND 323
#define REL_OP 324
#define RESTRICT_DOMAIN 325
#define RESTRICT_RANGE 326
#define SUPERSETOF 327
#define SUBSETOF 328
#define SAMPLE 329
#define SYM_SAMPLE 330
#define PROJECT_AWAY_SYMBOLS 331
#define PROJECT_ON_SYMBOLS 332
#define REACHABLE_FROM 333
#define REACHABLE_OF 334
#define ASSERT_UNSAT 335
#define PARSE_EXPRESSION 336
#define PARSE_FORMULA 337
#define PARSE_RELATION 338
#define p1 339
#define p2 340
#define p3 341
#define p4 342
#define p5 343
#define p6 344
#define p7 345
#define p8 346
#define p9 347
#define p10 348

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 130 "../src/parser.y"

	int INT_VALUE;
	Rel_Op REL_OPERATOR;
	char *VAR_NAME;
	VarList *VAR_LIST;
	Exp *EXP;
	ExpList *EXP_LIST;
	AST *ASTP;
	Argument_Tuple ARGUMENT_TUPLE;
	AST_constraints *ASTCP;
	Declaration_Site * DECLARATION_SITE;
	Relation * RELATION;
	tupleDescriptor * TUPLE_DESCRIPTOR;
	RelTuplePair * REL_TUPLE_PAIR;
        RelTupleTriple * REL_TUPLE_TRIPLE;
	Dynamic_Array2<Relation> * RELATION_ARRAY_2D;
	Dynamic_Array1<Relation> * RELATION_ARRAY_1D;
	Tuple<String> *STRING_TUPLE;
	String *STRING_VALUE;
  	Tuple<stm_info> *STM_INFO_TUPLE;
  	stm_info *STM_INFO;
	Read *READ;
	PartialRead *PREAD;
	MMap *MMAP;
	PartialMMap *PMMAP;
	

#line 281 "y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
