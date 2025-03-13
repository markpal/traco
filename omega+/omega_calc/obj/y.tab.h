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
    COEF = 260,                    /* COEF  */
    STRING = 261,                  /* STRING  */
    OPEN_BRACE = 262,              /* OPEN_BRACE  */
    CLOSE_BRACE = 263,             /* CLOSE_BRACE  */
    SYMBOLIC = 264,                /* SYMBOLIC  */
    OR = 265,                      /* OR  */
    AND = 266,                     /* AND  */
    NOT = 267,                     /* NOT  */
    ST = 268,                      /* ST  */
    APPROX = 269,                  /* APPROX  */
    IS_ASSIGNED = 270,             /* IS_ASSIGNED  */
    FORALL = 271,                  /* FORALL  */
    EXISTS = 272,                  /* EXISTS  */
    DOMAIN = 273,                  /* DOMAIN  */
    RANGE = 274,                   /* RANGE  */
    DIFFERENCE = 275,              /* DIFFERENCE  */
    DIFFERENCE_TO_RELATION = 276,  /* DIFFERENCE_TO_RELATION  */
    GIST = 277,                    /* GIST  */
    GIVEN = 278,                   /* GIVEN  */
    HULL = 279,                    /* HULL  */
    WITHIN = 280,                  /* WITHIN  */
    MAXIMIZE = 281,                /* MAXIMIZE  */
    MINIMIZE = 282,                /* MINIMIZE  */
    AFFINE_HULL = 283,             /* AFFINE_HULL  */
    VENN = 284,                    /* VENN  */
    CONVEX_COMBINATION = 285,      /* CONVEX_COMBINATION  */
    POSITIVE_COMBINATION = 286,    /* POSITIVE_COMBINATION  */
    LINEAR_COMBINATION = 287,      /* LINEAR_COMBINATION  */
    AFFINE_COMBINATION = 288,      /* AFFINE_COMBINATION  */
    CONVEX_HULL = 289,             /* CONVEX_HULL  */
    CONIC_HULL = 290,              /* CONIC_HULL  */
    LINEAR_HULL = 291,             /* LINEAR_HULL  */
    QUICK_HULL = 292,              /* QUICK_HULL  */
    PAIRWISE_CHECK = 293,          /* PAIRWISE_CHECK  */
    CONVEX_CHECK = 294,            /* CONVEX_CHECK  */
    CONVEX_REPRESENTATION = 295,   /* CONVEX_REPRESENTATION  */
    RECT_HULL = 296,               /* RECT_HULL  */
    DECOUPLED_CONVEX_HULL = 297,   /* DECOUPLED_CONVEX_HULL  */
    MAXIMIZE_RANGE = 298,          /* MAXIMIZE_RANGE  */
    MINIMIZE_RANGE = 299,          /* MINIMIZE_RANGE  */
    MAXIMIZE_DOMAIN = 300,         /* MAXIMIZE_DOMAIN  */
    MINIMIZE_DOMAIN = 301,         /* MINIMIZE_DOMAIN  */
    LEQ = 302,                     /* LEQ  */
    GEQ = 303,                     /* GEQ  */
    NEQ = 304,                     /* NEQ  */
    GOES_TO = 305,                 /* GOES_TO  */
    COMPOSE = 306,                 /* COMPOSE  */
    JOIN = 307,                    /* JOIN  */
    INVERSE = 308,                 /* INVERSE  */
    COMPLEMENT = 309,              /* COMPLEMENT  */
    IN = 310,                      /* IN  */
    CARRIED_BY = 311,              /* CARRIED_BY  */
    TIME = 312,                    /* TIME  */
    TIMECLOSURE = 313,             /* TIMECLOSURE  */
    UNION = 314,                   /* UNION  */
    INTERSECTION = 315,            /* INTERSECTION  */
    VERTICAL_BAR = 316,            /* VERTICAL_BAR  */
    SUCH_THAT = 317,               /* SUCH_THAT  */
    SUBSET = 318,                  /* SUBSET  */
    ITERATIONS = 319,              /* ITERATIONS  */
    SPMD = 320,                    /* SPMD  */
    CODEGEN = 321,                 /* CODEGEN  */
    DECOUPLED_FARKAS = 322,        /* DECOUPLED_FARKAS  */
    FARKAS = 323,                  /* FARKAS  */
    TCODEGEN = 324,                /* TCODEGEN  */
    TRANS_IS = 325,                /* TRANS_IS  */
    SET_MMAP = 326,                /* SET_MMAP  */
    UNROLL_IS = 327,               /* UNROLL_IS  */
    PEEL_IS = 328,                 /* PEEL_IS  */
    MAKE_UPPER_BOUND = 329,        /* MAKE_UPPER_BOUND  */
    MAKE_LOWER_BOUND = 330,        /* MAKE_LOWER_BOUND  */
    REL_OP = 331,                  /* REL_OP  */
    RESTRICT_DOMAIN = 332,         /* RESTRICT_DOMAIN  */
    RESTRICT_RANGE = 333,          /* RESTRICT_RANGE  */
    SUPERSETOF = 334,              /* SUPERSETOF  */
    SUBSETOF = 335,                /* SUBSETOF  */
    SAMPLE = 336,                  /* SAMPLE  */
    SYM_SAMPLE = 337,              /* SYM_SAMPLE  */
    PROJECT_AWAY_SYMBOLS = 338,    /* PROJECT_AWAY_SYMBOLS  */
    PROJECT_ON_SYMBOLS = 339,      /* PROJECT_ON_SYMBOLS  */
    REACHABLE_FROM = 340,          /* REACHABLE_FROM  */
    REACHABLE_OF = 341,            /* REACHABLE_OF  */
    ASSERT_UNSAT = 342,            /* ASSERT_UNSAT  */
    PARSE_EXPRESSION = 343,        /* PARSE_EXPRESSION  */
    PARSE_FORMULA = 344,           /* PARSE_FORMULA  */
    PARSE_RELATION = 345,          /* PARSE_RELATION  */
    ITERATE_CLOSURE = 346,         /* ITERATE_CLOSURE  */
    APPROX_CLOSURE = 347,          /* APPROX_CLOSURE  */
    TRANSITIVE_REDUCTION = 348,    /* TRANSITIVE_REDUCTION  */
    APPROX_TO_UNIFORM = 349,       /* APPROX_TO_UNIFORM  */
    RK = 350,                      /* RK  */
    TC = 351,                      /* TC  */
    SEMI_NAIVE_CLOSURE = 352,      /* SEMI_NAIVE_CLOSURE  */
    ADVANCED_ITERATE_CLOSURE = 353, /* ADVANCED_ITERATE_CLOSURE  */
    ALL_IN_REGION = 354,           /* ALL_IN_REGION  */
    MIN_DEPENDENCE_DIST = 355,     /* MIN_DEPENDENCE_DIST  */
    TEST = 356,                    /* TEST  */
    p1 = 357,                      /* p1  */
    p2 = 358,                      /* p2  */
    p3 = 359,                      /* p3  */
    p4 = 360,                      /* p4  */
    p5 = 361,                      /* p5  */
    p6 = 362,                      /* p6  */
    p7 = 363,                      /* p7  */
    p8 = 364,                      /* p8  */
    p9 = 365,                      /* p9  */
    p10 = 366                      /* p10  */
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
#define COEF 260
#define STRING 261
#define OPEN_BRACE 262
#define CLOSE_BRACE 263
#define SYMBOLIC 264
#define OR 265
#define AND 266
#define NOT 267
#define ST 268
#define APPROX 269
#define IS_ASSIGNED 270
#define FORALL 271
#define EXISTS 272
#define DOMAIN 273
#define RANGE 274
#define DIFFERENCE 275
#define DIFFERENCE_TO_RELATION 276
#define GIST 277
#define GIVEN 278
#define HULL 279
#define WITHIN 280
#define MAXIMIZE 281
#define MINIMIZE 282
#define AFFINE_HULL 283
#define VENN 284
#define CONVEX_COMBINATION 285
#define POSITIVE_COMBINATION 286
#define LINEAR_COMBINATION 287
#define AFFINE_COMBINATION 288
#define CONVEX_HULL 289
#define CONIC_HULL 290
#define LINEAR_HULL 291
#define QUICK_HULL 292
#define PAIRWISE_CHECK 293
#define CONVEX_CHECK 294
#define CONVEX_REPRESENTATION 295
#define RECT_HULL 296
#define DECOUPLED_CONVEX_HULL 297
#define MAXIMIZE_RANGE 298
#define MINIMIZE_RANGE 299
#define MAXIMIZE_DOMAIN 300
#define MINIMIZE_DOMAIN 301
#define LEQ 302
#define GEQ 303
#define NEQ 304
#define GOES_TO 305
#define COMPOSE 306
#define JOIN 307
#define INVERSE 308
#define COMPLEMENT 309
#define IN 310
#define CARRIED_BY 311
#define TIME 312
#define TIMECLOSURE 313
#define UNION 314
#define INTERSECTION 315
#define VERTICAL_BAR 316
#define SUCH_THAT 317
#define SUBSET 318
#define ITERATIONS 319
#define SPMD 320
#define CODEGEN 321
#define DECOUPLED_FARKAS 322
#define FARKAS 323
#define TCODEGEN 324
#define TRANS_IS 325
#define SET_MMAP 326
#define UNROLL_IS 327
#define PEEL_IS 328
#define MAKE_UPPER_BOUND 329
#define MAKE_LOWER_BOUND 330
#define REL_OP 331
#define RESTRICT_DOMAIN 332
#define RESTRICT_RANGE 333
#define SUPERSETOF 334
#define SUBSETOF 335
#define SAMPLE 336
#define SYM_SAMPLE 337
#define PROJECT_AWAY_SYMBOLS 338
#define PROJECT_ON_SYMBOLS 339
#define REACHABLE_FROM 340
#define REACHABLE_OF 341
#define ASSERT_UNSAT 342
#define PARSE_EXPRESSION 343
#define PARSE_FORMULA 344
#define PARSE_RELATION 345
#define ITERATE_CLOSURE 346
#define APPROX_CLOSURE 347
#define TRANSITIVE_REDUCTION 348
#define APPROX_TO_UNIFORM 349
#define RK 350
#define TC 351
#define SEMI_NAIVE_CLOSURE 352
#define ADVANCED_ITERATE_CLOSURE 353
#define ALL_IN_REGION 354
#define MIN_DEPENDENCE_DIST 355
#define TEST 356
#define p1 357
#define p2 358
#define p3 359
#define p4 360
#define p5 361
#define p6 362
#define p7 363
#define p8 364
#define p9 365
#define p10 366

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 94 "../src/parser.y"

  int INT_VALUE;
  coef_t COEF_VALUE;
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
  Tuple<std::string> *STRING_TUPLE;
  std::string *STRING_VALUE;
  Tuple<stm_info> *STM_INFO_TUPLE;
  stm_info *STM_INFO;
  Read *READ;
  PartialRead *PREAD;
  MMap *MMAP;
  PartialMMap *PMMAP;

#line 317 "y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
