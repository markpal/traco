/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "../src/parser.y"


#define compilingParser
#include <basic/Dynamic_Array.h>
#include <code_gen/code_gen.h>
#include <code_gen/spmd.h>
#include <omega/library_version.h>
#include <omega/AST.h>
#include <omega_calc/yylex.h>
#include <omega/hull.h>
#include <omega/calc_debug.h>
#include <basic/Exit.h>
#include <omega/closure.h>
#include <omega/reach.h>
#include <code_gen/mmap-codegen.h>
#include <code_gen/mmap-util.h>
#ifndef WIN32
#include <sys/time.h>
#include <sys/resource.h>
#endif

#define CALC_VERSION_STRING "Omega Calculator v2.1"

#define DEBUG_FILE_NAME "./oc.out"

/* Can only do the following when "using namespace omega"
   is also put before the inclusion of y.tab.h in parser.l.
*/
using omega::min;
using omega::negate;
using namespace omega;

Map<Const_String,Relation*> relationMap ((Relation *)0);
static int redundant_conj_level;

#if defined BRAIN_DAMAGED_FREE
void free(void *p);
void *realloc(void *p, size_t s);
#endif

namespace omega {
#if !defined(OMIT_GETRUSAGE)
void start_clock( void );
int clock_diff( void );
bool anyTimingDone = false;
#endif

int argCount = 0;
int tuplePos = 0;
Argument_Tuple currentTuple = Input_Tuple;

Relation LexForward(int n);
} // end namespace omega

reachable_information *reachable_info;



#line 130 "y.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
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
	

#line 397 "y.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_VAR = 3,                        /* VAR  */
  YYSYMBOL_INT = 4,                        /* INT  */
  YYSYMBOL_STRING = 5,                     /* STRING  */
  YYSYMBOL_OPEN_BRACE = 6,                 /* OPEN_BRACE  */
  YYSYMBOL_CLOSE_BRACE = 7,                /* CLOSE_BRACE  */
  YYSYMBOL_SYMBOLIC = 8,                   /* SYMBOLIC  */
  YYSYMBOL_OR = 9,                         /* OR  */
  YYSYMBOL_AND = 10,                       /* AND  */
  YYSYMBOL_NOT = 11,                       /* NOT  */
  YYSYMBOL_ST = 12,                        /* ST  */
  YYSYMBOL_APPROX = 13,                    /* APPROX  */
  YYSYMBOL_IS_ASSIGNED = 14,               /* IS_ASSIGNED  */
  YYSYMBOL_FORALL = 15,                    /* FORALL  */
  YYSYMBOL_EXISTS = 16,                    /* EXISTS  */
  YYSYMBOL_OMEGA_DOMAIN = 17,              /* OMEGA_DOMAIN  */
  YYSYMBOL_RANGE = 18,                     /* RANGE  */
  YYSYMBOL_DIFFERENCE = 19,                /* DIFFERENCE  */
  YYSYMBOL_DIFFERENCE_TO_RELATION = 20,    /* DIFFERENCE_TO_RELATION  */
  YYSYMBOL_GIST = 21,                      /* GIST  */
  YYSYMBOL_GIVEN = 22,                     /* GIVEN  */
  YYSYMBOL_HULL = 23,                      /* HULL  */
  YYSYMBOL_WITHIN = 24,                    /* WITHIN  */
  YYSYMBOL_MAXIMIZE = 25,                  /* MAXIMIZE  */
  YYSYMBOL_MINIMIZE = 26,                  /* MINIMIZE  */
  YYSYMBOL_AFFINE_HULL = 27,               /* AFFINE_HULL  */
  YYSYMBOL_VENN = 28,                      /* VENN  */
  YYSYMBOL_CONVEX_COMBINATION = 29,        /* CONVEX_COMBINATION  */
  YYSYMBOL_POSITIVE_COMBINATION = 30,      /* POSITIVE_COMBINATION  */
  YYSYMBOL_CONVEX_HULL = 31,               /* CONVEX_HULL  */
  YYSYMBOL_CONIC_HULL = 32,                /* CONIC_HULL  */
  YYSYMBOL_LINEAR_HULL = 33,               /* LINEAR_HULL  */
  YYSYMBOL_PAIRWISE_CHECK = 34,            /* PAIRWISE_CHECK  */
  YYSYMBOL_CONVEX_CHECK = 35,              /* CONVEX_CHECK  */
  YYSYMBOL_MAXIMIZE_RANGE = 36,            /* MAXIMIZE_RANGE  */
  YYSYMBOL_MINIMIZE_RANGE = 37,            /* MINIMIZE_RANGE  */
  YYSYMBOL_MAXIMIZE_DOMAIN = 38,           /* MAXIMIZE_DOMAIN  */
  YYSYMBOL_MINIMIZE_DOMAIN = 39,           /* MINIMIZE_DOMAIN  */
  YYSYMBOL_LEQ = 40,                       /* LEQ  */
  YYSYMBOL_GEQ = 41,                       /* GEQ  */
  YYSYMBOL_NEQ = 42,                       /* NEQ  */
  YYSYMBOL_GOES_TO = 43,                   /* GOES_TO  */
  YYSYMBOL_COMPOSE = 44,                   /* COMPOSE  */
  YYSYMBOL_JOIN = 45,                      /* JOIN  */
  YYSYMBOL_INVERSE = 46,                   /* INVERSE  */
  YYSYMBOL_COMPLEMENT = 47,                /* COMPLEMENT  */
  YYSYMBOL_IN = 48,                        /* IN  */
  YYSYMBOL_CARRIED_BY = 49,                /* CARRIED_BY  */
  YYSYMBOL_TIME = 50,                      /* TIME  */
  YYSYMBOL_TIMECLOSURE = 51,               /* TIMECLOSURE  */
  YYSYMBOL_UNION = 52,                     /* UNION  */
  YYSYMBOL_INTERSECTION = 53,              /* INTERSECTION  */
  YYSYMBOL_VERTICAL_BAR = 54,              /* VERTICAL_BAR  */
  YYSYMBOL_SUCH_THAT = 55,                 /* SUCH_THAT  */
  YYSYMBOL_SUBSET = 56,                    /* SUBSET  */
  YYSYMBOL_ITERATIONS = 57,                /* ITERATIONS  */
  YYSYMBOL_SPMD = 58,                      /* SPMD  */
  YYSYMBOL_CODEGEN = 59,                   /* CODEGEN  */
  YYSYMBOL_DECOUPLED_FARKAS = 60,          /* DECOUPLED_FARKAS  */
  YYSYMBOL_FARKAS = 61,                    /* FARKAS  */
  YYSYMBOL_TCODEGEN = 62,                  /* TCODEGEN  */
  YYSYMBOL_TRANS_IS = 63,                  /* TRANS_IS  */
  YYSYMBOL_SET_MMAP = 64,                  /* SET_MMAP  */
  YYSYMBOL_UNROLL_IS = 65,                 /* UNROLL_IS  */
  YYSYMBOL_PEEL_IS = 66,                   /* PEEL_IS  */
  YYSYMBOL_MAKE_UPPER_BOUND = 67,          /* MAKE_UPPER_BOUND  */
  YYSYMBOL_MAKE_LOWER_BOUND = 68,          /* MAKE_LOWER_BOUND  */
  YYSYMBOL_REL_OP = 69,                    /* REL_OP  */
  YYSYMBOL_RESTRICT_DOMAIN = 70,           /* RESTRICT_DOMAIN  */
  YYSYMBOL_RESTRICT_RANGE = 71,            /* RESTRICT_RANGE  */
  YYSYMBOL_SUPERSETOF = 72,                /* SUPERSETOF  */
  YYSYMBOL_SUBSETOF = 73,                  /* SUBSETOF  */
  YYSYMBOL_SAMPLE = 74,                    /* SAMPLE  */
  YYSYMBOL_SYM_SAMPLE = 75,                /* SYM_SAMPLE  */
  YYSYMBOL_PROJECT_AWAY_SYMBOLS = 76,      /* PROJECT_AWAY_SYMBOLS  */
  YYSYMBOL_PROJECT_ON_SYMBOLS = 77,        /* PROJECT_ON_SYMBOLS  */
  YYSYMBOL_REACHABLE_FROM = 78,            /* REACHABLE_FROM  */
  YYSYMBOL_REACHABLE_OF = 79,              /* REACHABLE_OF  */
  YYSYMBOL_ASSERT_UNSAT = 80,              /* ASSERT_UNSAT  */
  YYSYMBOL_PARSE_EXPRESSION = 81,          /* PARSE_EXPRESSION  */
  YYSYMBOL_PARSE_FORMULA = 82,             /* PARSE_FORMULA  */
  YYSYMBOL_PARSE_RELATION = 83,            /* PARSE_RELATION  */
  YYSYMBOL_p1 = 84,                        /* p1  */
  YYSYMBOL_85_ = 85,                       /* '+'  */
  YYSYMBOL_86_ = 86,                       /* '-'  */
  YYSYMBOL_p2 = 87,                        /* p2  */
  YYSYMBOL_p3 = 88,                        /* p3  */
  YYSYMBOL_89_ = 89,                       /* '*'  */
  YYSYMBOL_90_ = 90,                       /* '@'  */
  YYSYMBOL_p4 = 91,                        /* p4  */
  YYSYMBOL_p5 = 92,                        /* p5  */
  YYSYMBOL_p6 = 93,                        /* p6  */
  YYSYMBOL_p7 = 94,                        /* p7  */
  YYSYMBOL_p8 = 95,                        /* p8  */
  YYSYMBOL_p9 = 96,                        /* p9  */
  YYSYMBOL_97_ = 97,                       /* '('  */
  YYSYMBOL_p10 = 98,                       /* p10  */
  YYSYMBOL_99_ = 99,                       /* ';'  */
  YYSYMBOL_100_ = 100,                     /* ','  */
  YYSYMBOL_101_ = 101,                     /* ':'  */
  YYSYMBOL_102_ = 102,                     /* '['  */
  YYSYMBOL_103_ = 103,                     /* ']'  */
  YYSYMBOL_104_ = 104,                     /* ')'  */
  YYSYMBOL_YYACCEPT = 105,                 /* $accept  */
  YYSYMBOL_start = 106,                    /* start  */
  YYSYMBOL_107_1 = 107,                    /* $@1  */
  YYSYMBOL_inputSequence = 108,            /* inputSequence  */
  YYSYMBOL_109_2 = 109,                    /* $@2  */
  YYSYMBOL_inputItem = 110,                /* inputItem  */
  YYSYMBOL_relTripList = 111,              /* relTripList  */
  YYSYMBOL_blockAndProcsAndEffort = 112,   /* blockAndProcsAndEffort  */
  YYSYMBOL_effort = 113,                   /* effort  */
  YYSYMBOL_context = 114,                  /* context  */
  YYSYMBOL_relPairList = 115,              /* relPairList  */
  YYSYMBOL_statementInfoResult = 116,      /* statementInfoResult  */
  YYSYMBOL_statementInfoList = 117,        /* statementInfoList  */
  YYSYMBOL_statementInfo = 118,            /* statementInfo  */
  YYSYMBOL_partialwrites = 119,            /* partialwrites  */
  YYSYMBOL_partialwrite = 120,             /* partialwrite  */
  YYSYMBOL_reads = 121,                    /* reads  */
  YYSYMBOL_oneread = 122,                  /* oneread  */
  YYSYMBOL_partials = 123,                 /* partials  */
  YYSYMBOL_partial = 124,                  /* partial  */
  YYSYMBOL_globVarList = 125,              /* globVarList  */
  YYSYMBOL_globVar = 126,                  /* globVar  */
  YYSYMBOL_relation = 127,                 /* relation  */
  YYSYMBOL_128_3 = 128,                    /* $@3  */
  YYSYMBOL_builtRelation = 129,            /* builtRelation  */
  YYSYMBOL_130_4 = 130,                    /* $@4  */
  YYSYMBOL_131_5 = 131,                    /* $@5  */
  YYSYMBOL_optionalFormula = 132,          /* optionalFormula  */
  YYSYMBOL_formula_sep = 133,              /* formula_sep  */
  YYSYMBOL_tupleDeclaration = 134,         /* tupleDeclaration  */
  YYSYMBOL_135_6 = 135,                    /* $@6  */
  YYSYMBOL_optionalTupleVarList = 136,     /* optionalTupleVarList  */
  YYSYMBOL_tupleVar = 137,                 /* tupleVar  */
  YYSYMBOL_varList = 138,                  /* varList  */
  YYSYMBOL_varDecl = 139,                  /* varDecl  */
  YYSYMBOL_varDeclOptBrackets = 140,       /* varDeclOptBrackets  */
  YYSYMBOL_formula = 141,                  /* formula  */
  YYSYMBOL_start_exists = 142,             /* start_exists  */
  YYSYMBOL_exists_sep = 143,               /* exists_sep  */
  YYSYMBOL_start_forall = 144,             /* start_forall  */
  YYSYMBOL_forall_sep = 145,               /* forall_sep  */
  YYSYMBOL_end_quant = 146,                /* end_quant  */
  YYSYMBOL_expList = 147,                  /* expList  */
  YYSYMBOL_constraintChain = 148,          /* constraintChain  */
  YYSYMBOL_simpleExp = 149,                /* simpleExp  */
  YYSYMBOL_150_7 = 150,                    /* $@7  */
  YYSYMBOL_argumentList = 151,             /* argumentList  */
  YYSYMBOL_exp = 152,                      /* exp  */
  YYSYMBOL_reachable = 153,                /* reachable  */
  YYSYMBOL_reachable_of = 154,             /* reachable_of  */
  YYSYMBOL_nodeNameList = 155,             /* nodeNameList  */
  YYSYMBOL_realNodeNameList = 156,         /* realNodeNameList  */
  YYSYMBOL_nodeSpecificationList = 157,    /* nodeSpecificationList  */
  YYSYMBOL_realNodeSpecificationList = 158 /* realNodeSpecificationList  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int16 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   891

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  105
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  54
/* YYNRULES -- Number of rules.  */
#define YYNRULES  180
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  372

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   348


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      97,   104,    89,    85,   100,    86,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,   101,    99,
       2,     2,     2,     2,    90,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   102,     2,   103,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      87,    88,    91,    92,    93,    94,    95,    96,    98
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   161,   161,   161,   165,   166,   166,   171,   183,   186,
     195,   203,   287,   375,   382,   390,   407,   435,   453,   463,
     476,   477,   478,   479,   482,   483,   484,   487,   489,   492,
     502,   511,   522,   534,   541,   545,   549,   551,   555,   562,
     565,   570,   576,   584,   588,   593,   599,   606,   609,   614,
     617,   620,   625,   631,   632,   635,   637,   642,   641,   653,
     664,   665,   670,   677,   683,   692,   701,   710,   719,   729,
     739,   745,   751,   756,   761,   766,   771,   776,   781,   786,
     792,   797,   802,   807,   812,   817,   822,   827,   832,   837,
     843,   848,   853,   858,   863,   869,   875,   881,   887,   893,
     899,   905,   911,   917,   923,   929,   934,   939,   944,   949,
     954,   959,   960,   974,   975,   974,  1001,  1018,  1027,  1028,
    1031,  1032,  1033,  1037,  1037,  1043,  1044,  1045,  1048,  1062,
    1064,  1066,  1068,  1073,  1074,  1078,  1088,  1089,  1092,  1093,
    1094,  1095,  1096,  1097,  1099,  1103,  1104,  1107,  1108,  1109,
    1112,  1113,  1116,  1119,  1123,  1128,  1134,  1136,  1141,  1147,
    1147,  1159,  1165,  1176,  1188,  1189,  1190,  1191,  1192,  1193,
    1194,  1199,  1208,  1223,  1231,  1234,  1240,  1291,  1299,  1310,
    1321
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "VAR", "INT", "STRING",
  "OPEN_BRACE", "CLOSE_BRACE", "SYMBOLIC", "OR", "AND", "NOT", "ST",
  "APPROX", "IS_ASSIGNED", "FORALL", "EXISTS", "OMEGA_DOMAIN", "RANGE",
  "DIFFERENCE", "DIFFERENCE_TO_RELATION", "GIST", "GIVEN", "HULL",
  "WITHIN", "MAXIMIZE", "MINIMIZE", "AFFINE_HULL", "VENN",
  "CONVEX_COMBINATION", "POSITIVE_COMBINATION", "CONVEX_HULL",
  "CONIC_HULL", "LINEAR_HULL", "PAIRWISE_CHECK", "CONVEX_CHECK",
  "MAXIMIZE_RANGE", "MINIMIZE_RANGE", "MAXIMIZE_DOMAIN", "MINIMIZE_DOMAIN",
  "LEQ", "GEQ", "NEQ", "GOES_TO", "COMPOSE", "JOIN", "INVERSE",
  "COMPLEMENT", "IN", "CARRIED_BY", "TIME", "TIMECLOSURE", "UNION",
  "INTERSECTION", "VERTICAL_BAR", "SUCH_THAT", "SUBSET", "ITERATIONS",
  "SPMD", "CODEGEN", "DECOUPLED_FARKAS", "FARKAS", "TCODEGEN", "TRANS_IS",
  "SET_MMAP", "UNROLL_IS", "PEEL_IS", "MAKE_UPPER_BOUND",
  "MAKE_LOWER_BOUND", "REL_OP", "RESTRICT_DOMAIN", "RESTRICT_RANGE",
  "SUPERSETOF", "SUBSETOF", "SAMPLE", "SYM_SAMPLE", "PROJECT_AWAY_SYMBOLS",
  "PROJECT_ON_SYMBOLS", "REACHABLE_FROM", "REACHABLE_OF", "ASSERT_UNSAT",
  "PARSE_EXPRESSION", "PARSE_FORMULA", "PARSE_RELATION", "p1", "'+'",
  "'-'", "p2", "p3", "'*'", "'@'", "p4", "p5", "p6", "p7", "p8", "p9",
  "'('", "p10", "';'", "','", "':'", "'['", "']'", "')'", "$accept",
  "start", "$@1", "inputSequence", "$@2", "inputItem", "relTripList",
  "blockAndProcsAndEffort", "effort", "context", "relPairList",
  "statementInfoResult", "statementInfoList", "statementInfo",
  "partialwrites", "partialwrite", "reads", "oneread", "partials",
  "partial", "globVarList", "globVar", "relation", "$@3", "builtRelation",
  "$@4", "$@5", "optionalFormula", "formula_sep", "tupleDeclaration",
  "$@6", "optionalTupleVarList", "tupleVar", "varList", "varDecl",
  "varDeclOptBrackets", "formula", "start_exists", "exists_sep",
  "start_forall", "forall_sep", "end_quant", "expList", "constraintChain",
  "simpleExp", "$@7", "argumentList", "exp", "reachable", "reachable_of",
  "nodeNameList", "realNodeNameList", "nodeSpecificationList",
  "realNodeSpecificationList", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-252)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-129)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -252,    64,   336,  -252,    -9,    78,  -252,    97,   164,   164,
     164,   164,   164,   164,   164,   164,   164,   164,   164,   164,
     164,   164,   164,   164,   164,   164,   164,   164,   164,   164,
     164,   164,   164,   164,   101,    42,   164,   164,    42,   164,
     164,   164,   164,   164,   164,   164,   164,    47,   143,   164,
     164,   151,  -252,   631,    60,  -252,  -252,   164,    51,    79,
     -21,  -252,  -252,    89,    89,    89,    89,    89,   205,     4,
      89,    89,    89,    35,    89,    89,    89,    89,    89,    89,
      89,    89,    89,    89,    89,    89,    89,   661,   691,   168,
     164,  -252,   184,   164,    89,    89,    33,    89,    89,   794,
     794,    89,    89,    89,    89,   201,   202,   173,   781,   218,
     336,   164,   164,   222,   164,   164,   164,   164,   164,   206,
     164,   164,  -252,   164,  -252,  -252,   721,   132,    45,    51,
     136,   145,    72,    57,   244,   180,   150,   121,    27,    27,
     191,  -252,  -252,   227,   249,  -252,    97,   164,   164,   164,
    -252,  -252,   262,   115,   466,  -252,    34,   490,   164,   264,
     268,   275,   280,   258,   186,  -252,  -252,   -11,   284,  -252,
      47,  -252,  -252,    89,    89,  -252,   794,    39,   751,   220,
     220,   164,    39,    39,   373,  -252,  -252,    72,  -252,  -252,
    -252,  -252,  -252,   136,   145,    41,    75,  -252,  -252,  -252,
    -252,  -252,  -252,    51,    66,    51,    51,  -252,   289,   193,
    -252,    26,   195,    72,    72,    72,    72,    72,   207,  -252,
      89,    89,    89,  -252,  -252,   164,   164,   164,   164,   215,
     164,   431,   300,   302,   314,   221,   225,   224,   326,  -252,
      15,    38,   202,  -252,    89,  -252,   328,   170,  -252,  -252,
    -252,   121,   -26,  -252,    53,  -252,   127,   322,  -252,   230,
     333,  -252,  -252,  -252,    51,  -252,    51,   191,  -252,   251,
     251,  -252,  -252,  -252,   513,   537,   781,   560,  -252,   781,
    -252,   -37,   182,  -252,   334,   164,   164,  -252,  -252,  -252,
     338,   164,  -252,   342,  -252,  -252,    14,  -252,    66,  -252,
      72,  -252,  -252,    43,    43,   164,   164,   164,   164,   164,
     300,  -252,    33,   403,   607,   245,   781,    48,   345,  -252,
      32,  -252,   234,  -252,  -252,  -252,   584,   781,   781,   781,
     375,  -252,  -252,   164,  -252,   300,   164,   347,   164,  -252,
    -252,   348,   164,   260,   431,    65,   781,   250,   781,  -252,
     781,   164,  -252,    22,  -252,   164,   781,   372,    71,  -252,
     781,   277,   106,  -252,   276,  -252,   164,   372,  -252,  -252,
     781,  -252
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     0,     1,     0,    59,    57,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    20,    24,     0,     0,    24,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     5,     4,     0,     0,   111,     7,     0,   123,    56,
       0,    54,    59,    90,    77,    91,    75,    76,     0,    88,
      68,    69,    85,    78,    82,    81,    80,    86,    87,    83,
      84,    65,    64,    67,    66,    92,    93,     0,     0,    21,
       0,    25,     0,     0,    71,    70,     0,   107,   108,   105,
     106,   109,   110,    73,    74,     0,     0,     0,   112,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    61,
       0,    62,    72,     0,    10,    17,     0,   158,   164,     0,
       0,     0,     0,     0,     0,   119,     0,   117,     0,     0,
       0,   140,   166,   155,     0,     8,     0,     0,     0,     0,
      11,    12,    22,     0,     0,    26,    27,    32,     0,     0,
       0,     0,     0,    27,    33,    39,   175,     0,     0,   171,
       0,    60,     6,    96,    98,    97,   103,   101,     0,   100,
      99,     0,   102,   104,     0,     9,   159,     0,   165,   142,
     151,   146,   167,   150,   145,     0,   155,    58,   113,   121,
     122,   120,   116,     0,   127,     0,     0,   134,     0,   135,
     136,     0,     0,     0,     0,     0,     0,     0,     0,    53,
      94,    89,    79,    23,    16,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   173,
       0,     0,     0,    13,    63,    95,     0,     0,   141,   161,
     123,   118,   158,   129,     0,   125,   130,   139,   138,     0,
       0,   148,   149,   147,     0,   152,     0,   156,   157,   168,
     169,   170,   154,    55,     0,     0,    28,    30,    14,    31,
      34,     0,     0,    44,     0,     0,     0,    15,    40,   174,
       0,     0,   176,     0,   172,   163,     0,   114,     0,   124,
       0,   137,   133,     0,     0,     0,     0,     0,     0,     0,
       0,    35,     0,     0,     0,     0,   180,     0,     0,   160,
     119,   126,   131,   153,   143,   144,     0,    19,    29,    46,
       0,    43,    36,     0,    37,     0,     0,     0,     0,   162,
     115,     0,     0,     0,     0,     0,   179,     0,   177,   132,
      18,     0,    38,     0,    42,     0,    45,     0,     0,    48,
     178,     0,     0,    51,     0,    41,     0,     0,    49,    47,
      52,    50
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -252,  -252,  -252,  -252,  -252,   269,  -252,  -252,   343,   217,
    -252,  -187,  -252,   147,    50,  -251,  -252,    24,  -252,    23,
    -252,   243,    -8,  -252,  -252,  -252,  -252,    73,  -252,   141,
    -252,  -252,    94,  -252,   192,   263,   -86,  -252,  -252,  -252,
    -252,    95,   -51,   188,   278,  -252,  -252,   -93,  -252,  -252,
     235,  -252,   165,  -252
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,     1,     2,    51,   110,    52,   153,    90,    93,   229,
     156,   163,   164,   165,   282,   283,   358,   359,   362,   363,
      60,    61,    53,    58,   134,   250,   320,   202,   203,   135,
     136,   254,   255,   209,   210,   211,   137,   138,   264,   139,
     266,   324,   140,   141,   142,   246,   296,   143,    54,    55,
     106,   167,   169,   241
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,   148,   281,    94,    95,
     207,    97,    98,    99,   100,   101,   102,   103,   104,   192,
     196,   108,   109,   189,   280,   292,    91,   195,   127,   126,
     205,   206,   205,   206,   127,   128,   227,   149,   290,   331,
     127,   128,   129,   308,     3,   309,   130,   131,   129,   252,
     128,   186,   193,   194,  -128,   127,   128,  -128,   145,   146,
     261,   262,   154,   111,   112,   157,   199,   200,   113,   238,
      56,   337,    57,   239,   247,   311,   158,   159,   160,   161,
      59,   123,   331,   173,   174,    89,   176,   177,   178,   179,
     180,   256,   182,   183,   318,   184,   291,   251,   319,   257,
     258,   269,   270,   271,   357,   332,   334,   263,    92,   208,
     205,   206,   123,   201,   228,   162,   123,   132,   293,   220,
     221,   222,   187,   132,   105,   248,   107,   323,   133,   338,
     231,    -3,   132,   298,   133,   253,   299,   352,   132,   125,
     214,   215,   267,   187,   216,   353,   272,    62,   354,   187,
       6,   364,   152,   244,   365,   217,   144,     8,   303,   249,
     304,     9,    10,    11,    12,    13,   123,    14,   155,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,   166,   256,   367,   322,   168,   368,
      30,    31,   214,   215,   224,   225,   216,   274,   275,   276,
     277,   170,   279,   198,    36,    37,   175,   147,   300,   186,
     181,    39,    40,   190,   199,   200,    41,    42,    43,    44,
      45,    46,   191,    48,    49,   158,   159,   160,   161,   111,
     112,   197,   204,   218,   113,   214,   215,   114,   115,   216,
     213,    50,   111,   112,   111,   112,   223,   113,   232,   113,
     114,   115,   233,   115,   249,   117,   118,   313,   314,   234,
     227,   201,   310,   316,   162,   235,   237,   240,   117,   118,
     119,   120,   207,   260,   121,   122,   265,   326,   327,   328,
     329,   330,   123,   119,   120,   281,   284,   121,   122,   121,
     122,   273,   214,   215,   278,   123,   216,   123,   285,   214,
     215,   286,   171,   216,   287,   344,   162,   217,   346,   289,
     348,   295,   206,   301,   350,   341,   302,     4,   312,     5,
     216,   315,     6,   356,     7,   317,   336,   360,   339,     8,
     347,   355,   349,     9,    10,    11,    12,    13,   370,    14,
     351,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,   361,   366,   357,   172,
     236,    96,    30,    31,   288,   345,    32,    33,   369,   219,
     371,   297,   321,   340,    34,    35,    36,    37,    38,   325,
     259,   268,   212,    39,    40,   242,   188,   294,    41,    42,
      43,    44,    45,    46,    47,    48,    49,   111,   112,   111,
     112,     0,   113,     0,   113,   114,   115,   114,   115,     0,
       0,     0,     0,    50,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   117,   118,   117,   118,   111,   112,     0,
       0,     0,   113,     0,     0,   114,   115,     0,   119,   120,
     119,   120,   121,   122,   121,   122,   158,   159,   160,   161,
     123,     0,   123,   117,   118,   111,   112,   245,   343,     0,
     113,     0,     0,   114,   115,     0,     0,     0,   119,   120,
       0,     0,   121,   122,   158,   159,   160,   161,     0,     0,
     123,   117,   118,   333,     0,   162,     0,     0,     0,     0,
     111,   112,     0,     0,     0,   113,   119,   120,   114,   115,
     121,   122,     0,     0,     0,     0,     0,     0,   123,     0,
       0,     0,     0,   162,   111,   112,   117,   118,     0,   113,
       0,     0,   114,   115,     0,     0,     0,     0,     0,     0,
       0,   119,   120,     0,     0,   121,   122,   111,   112,     0,
     117,   118,   113,   123,     0,   114,   115,   226,     0,     0,
       0,     0,     0,     0,     0,   119,   120,     0,     0,   121,
     122,   111,   112,   117,   118,     0,   113,   123,     0,   114,
     115,   230,     0,     0,     0,     0,     0,     0,   119,   120,
       0,     0,   121,   122,   111,   112,     0,   117,   118,   113,
     123,     0,   114,   115,   305,     0,     0,     0,     0,     0,
       0,     0,   119,   120,     0,     0,   121,   122,   111,   112,
     117,   118,     0,   113,   123,     0,   114,   115,   306,     0,
       0,     0,     0,     0,     0,   119,   120,     0,     0,   121,
     122,   111,   112,     0,   117,   118,   113,   123,     0,   114,
     115,   307,     0,     0,     0,     0,     0,     0,     0,   119,
     120,     0,     0,   121,   122,   111,   112,   117,   118,     0,
     113,   123,     0,   114,   115,   342,     0,   116,     0,     0,
       0,     0,   119,   120,     0,     0,   121,   122,     0,     0,
       0,   117,   118,     0,   123,   111,   112,   335,     0,     0,
     113,     0,     0,   114,   115,     0,   119,   120,     0,     0,
     121,   122,     0,     0,     0,     0,     0,     0,   123,     0,
     124,   117,   118,     0,     0,   111,   112,     0,     0,     0,
     113,     0,     0,   114,   115,     0,   119,   120,     0,     0,
     121,   122,     0,     0,     0,     0,     0,     0,   123,     0,
     150,   117,   118,     0,     0,   111,   112,     0,     0,     0,
     113,     0,     0,   114,   115,     0,   119,   120,     0,     0,
     121,   122,     0,     0,     0,     0,     0,     0,   123,     0,
     151,   117,   118,     0,     0,   111,   112,     0,     0,     0,
     113,     0,     0,   114,   115,     0,   119,   120,     0,     0,
     121,   122,     0,     0,     0,     0,     0,     0,   123,     0,
     185,   117,   118,     0,     0,   111,   112,     0,     0,     0,
     113,     0,     0,   114,   115,     0,   119,   120,   111,   112,
     121,   122,     0,   113,     0,     0,     0,   115,   123,     0,
     243,   117,   118,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   117,   118,   119,   120,     0,     0,
     121,   122,     0,     0,     0,     0,     0,     0,   123,     0,
       0,     0,     0,   121,   122,     0,     0,     0,     0,     0,
       0,   123
};

static const yytype_int16 yycheck[] =
{
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    22,     5,    36,    37,
       3,    39,    40,    41,    42,    43,    44,    45,    46,   132,
     133,    49,    50,   129,   231,     7,     4,   133,     3,    57,
       9,    10,     9,    10,     3,     4,    22,    22,    43,   310,
       3,     4,    11,   100,     0,   102,    15,    16,    11,     3,
       4,    97,    15,    16,   100,     3,     4,   103,    99,   100,
      54,    55,    90,    44,    45,    93,    54,    55,    49,   100,
      99,    43,    14,   104,   187,   282,    63,    64,    65,    66,
       3,    97,   353,   111,   112,     4,   114,   115,   116,   117,
     118,   204,   120,   121,   100,   123,   101,   203,   104,   205,
     206,   214,   215,   216,   102,   312,   313,   101,    86,   102,
       9,    10,    97,   101,   100,   102,    97,    86,   100,   147,
     148,   149,    97,    86,    97,   104,     3,   104,    97,   101,
     158,     0,    86,   100,    97,    89,   103,   344,    86,    99,
      85,    86,   213,    97,    89,   100,   217,     3,   103,    97,
       6,   100,     4,   181,   103,   100,    97,    13,   264,   104,
     266,    17,    18,    19,    20,    21,    97,    23,     4,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,     3,   298,   100,   300,     6,   103,
      46,    47,    85,    86,    99,   100,    89,   225,   226,   227,
     228,    48,   230,    43,    60,    61,     4,    22,   101,    97,
      24,    67,    68,    97,    54,    55,    72,    73,    74,    75,
      76,    77,    97,    79,    80,    63,    64,    65,    66,    44,
      45,     7,   102,     4,    49,    85,    86,    52,    53,    89,
      69,    97,    44,    45,    44,    45,     4,    49,     4,    49,
      52,    53,     4,    53,   104,    70,    71,   285,   286,     4,
      22,   101,   100,   291,   102,     5,   100,     3,    70,    71,
      85,    86,     3,   100,    89,    90,   101,   305,   306,   307,
     308,   309,    97,    85,    86,     5,     4,    89,    90,    89,
      90,   104,    85,    86,    99,    97,    89,    97,     4,    85,
      86,   100,   104,    89,    99,   333,   102,   100,   336,     3,
     338,     3,    10,   103,   342,   101,     3,     1,     4,     3,
      89,     3,     6,   351,     8,     3,   101,   355,     3,    13,
       3,   101,     4,    17,    18,    19,    20,    21,   366,    23,
     100,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,     4,   100,   102,   110,
     163,    38,    46,    47,   237,   335,    50,    51,   364,   146,
     367,   250,   298,   320,    58,    59,    60,    61,    62,   304,
     208,   213,   139,    67,    68,   170,   128,   242,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    44,    45,    44,
      45,    -1,    49,    -1,    49,    52,    53,    52,    53,    -1,
      -1,    -1,    -1,    97,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    70,    71,    70,    71,    44,    45,    -1,
      -1,    -1,    49,    -1,    -1,    52,    53,    -1,    85,    86,
      85,    86,    89,    90,    89,    90,    63,    64,    65,    66,
      97,    -1,    97,    70,    71,    44,    45,   104,   103,    -1,
      49,    -1,    -1,    52,    53,    -1,    -1,    -1,    85,    86,
      -1,    -1,    89,    90,    63,    64,    65,    66,    -1,    -1,
      97,    70,    71,   100,    -1,   102,    -1,    -1,    -1,    -1,
      44,    45,    -1,    -1,    -1,    49,    85,    86,    52,    53,
      89,    90,    -1,    -1,    -1,    -1,    -1,    -1,    97,    -1,
      -1,    -1,    -1,   102,    44,    45,    70,    71,    -1,    49,
      -1,    -1,    52,    53,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    85,    86,    -1,    -1,    89,    90,    44,    45,    -1,
      70,    71,    49,    97,    -1,    52,    53,   101,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    85,    86,    -1,    -1,    89,
      90,    44,    45,    70,    71,    -1,    49,    97,    -1,    52,
      53,   101,    -1,    -1,    -1,    -1,    -1,    -1,    85,    86,
      -1,    -1,    89,    90,    44,    45,    -1,    70,    71,    49,
      97,    -1,    52,    53,   101,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    85,    86,    -1,    -1,    89,    90,    44,    45,
      70,    71,    -1,    49,    97,    -1,    52,    53,   101,    -1,
      -1,    -1,    -1,    -1,    -1,    85,    86,    -1,    -1,    89,
      90,    44,    45,    -1,    70,    71,    49,    97,    -1,    52,
      53,   101,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    85,
      86,    -1,    -1,    89,    90,    44,    45,    70,    71,    -1,
      49,    97,    -1,    52,    53,   101,    -1,    56,    -1,    -1,
      -1,    -1,    85,    86,    -1,    -1,    89,    90,    -1,    -1,
      -1,    70,    71,    -1,    97,    44,    45,   100,    -1,    -1,
      49,    -1,    -1,    52,    53,    -1,    85,    86,    -1,    -1,
      89,    90,    -1,    -1,    -1,    -1,    -1,    -1,    97,    -1,
      99,    70,    71,    -1,    -1,    44,    45,    -1,    -1,    -1,
      49,    -1,    -1,    52,    53,    -1,    85,    86,    -1,    -1,
      89,    90,    -1,    -1,    -1,    -1,    -1,    -1,    97,    -1,
      99,    70,    71,    -1,    -1,    44,    45,    -1,    -1,    -1,
      49,    -1,    -1,    52,    53,    -1,    85,    86,    -1,    -1,
      89,    90,    -1,    -1,    -1,    -1,    -1,    -1,    97,    -1,
      99,    70,    71,    -1,    -1,    44,    45,    -1,    -1,    -1,
      49,    -1,    -1,    52,    53,    -1,    85,    86,    -1,    -1,
      89,    90,    -1,    -1,    -1,    -1,    -1,    -1,    97,    -1,
      99,    70,    71,    -1,    -1,    44,    45,    -1,    -1,    -1,
      49,    -1,    -1,    52,    53,    -1,    85,    86,    44,    45,
      89,    90,    -1,    49,    -1,    -1,    -1,    53,    97,    -1,
      99,    70,    71,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    70,    71,    85,    86,    -1,    -1,
      89,    90,    -1,    -1,    -1,    -1,    -1,    -1,    97,    -1,
      -1,    -1,    -1,    89,    90,    -1,    -1,    -1,    -1,    -1,
      -1,    97
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,   106,   107,     0,     1,     3,     6,     8,    13,    17,
      18,    19,    20,    21,    23,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      46,    47,    50,    51,    58,    59,    60,    61,    62,    67,
      68,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      97,   108,   110,   127,   153,   154,    99,    14,   128,     3,
     125,   126,     3,   127,   127,   127,   127,   127,   127,   127,
     127,   127,   127,   127,   127,   127,   127,   127,   127,   127,
     127,   127,   127,   127,   127,   127,   127,   127,   127,     4,
     112,     4,    86,   113,   127,   127,   113,   127,   127,   127,
     127,   127,   127,   127,   127,    97,   155,     3,   127,   127,
     109,    44,    45,    49,    52,    53,    56,    70,    71,    85,
      86,    89,    90,    97,    99,    99,   127,     3,     4,    11,
      15,    16,    86,    97,   129,   134,   135,   141,   142,   144,
     147,   148,   149,   152,    97,    99,   100,    22,    22,    22,
      99,    99,     4,   111,   127,     4,   115,   127,    63,    64,
      65,    66,   102,   116,   117,   118,     3,   156,     6,   157,
      48,   104,   110,   127,   127,     4,   127,   127,   127,   127,
     127,    24,   127,   127,   127,    99,    97,    97,   149,   141,
      97,    97,   152,    15,    16,   141,   152,     7,    43,    54,
      55,   101,   132,   133,   102,     9,    10,     3,   102,   138,
     139,   140,   140,    69,    85,    86,    89,   100,     4,   126,
     127,   127,   127,     4,    99,   100,   101,    22,   100,   114,
     101,   127,     4,     4,     4,     5,   114,   100,   100,   104,
       3,   158,   155,    99,   127,   104,   150,   152,   104,   104,
     130,   141,     3,    89,   136,   137,   152,   141,   141,   139,
     100,    54,    55,   101,   143,   101,   145,   147,   148,   152,
     152,   152,   147,   104,   127,   127,   127,   127,    99,   127,
     116,     5,   119,   120,     4,     4,   100,    99,   118,     3,
      43,   101,     7,   100,   157,     3,   151,   134,   100,   103,
     101,   103,     3,   141,   141,   101,   101,   101,   100,   102,
     100,   116,     4,   127,   127,     3,   127,     3,   100,   104,
     131,   137,   152,   104,   146,   146,   127,   127,   127,   127,
     127,   120,   116,   100,   116,   100,   101,    43,   101,     3,
     132,   101,   101,   103,   127,   119,   127,     3,   127,     4,
     127,   100,   116,   100,   103,   101,   127,   102,   121,   122,
     127,     4,   123,   124,   100,   103,   100,   100,   103,   122,
     127,   124
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,   105,   107,   106,   108,   109,   108,   110,   110,   110,
     110,   110,   110,   110,   110,   110,   110,   110,   111,   111,
     112,   112,   112,   112,   113,   113,   113,   114,   114,   115,
     115,   115,   115,   116,   116,   116,   116,   116,   116,   117,
     117,   118,   118,   119,   119,   120,   120,   121,   121,   122,
     123,   123,   124,   125,   125,   126,   126,   128,   127,   127,
     127,   127,   127,   127,   127,   127,   127,   127,   127,   127,
     127,   127,   127,   127,   127,   127,   127,   127,   127,   127,
     127,   127,   127,   127,   127,   127,   127,   127,   127,   127,
     127,   127,   127,   127,   127,   127,   127,   127,   127,   127,
     127,   127,   127,   127,   127,   127,   127,   127,   127,   127,
     127,   127,   127,   130,   131,   129,   129,   129,   132,   132,
     133,   133,   133,   135,   134,   136,   136,   136,   137,   137,
     137,   137,   137,   138,   138,   139,   140,   140,   141,   141,
     141,   141,   141,   141,   141,   142,   142,   143,   143,   143,
     144,   144,   145,   146,   147,   147,   148,   148,   149,   150,
     149,   149,   151,   151,   152,   152,   152,   152,   152,   152,
     152,   153,   154,   155,   156,   156,   157,   158,   158,   158,
     158
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     1,     0,     3,     2,     3,     4,
       2,     3,     3,     4,     5,     5,     4,     2,     7,     5,
       0,     1,     2,     3,     0,     1,     2,     0,     2,     5,
       3,     3,     1,     1,     3,     4,     5,     5,     7,     1,
       3,     9,     7,     3,     1,     6,     3,     3,     1,     3,
       3,     1,     3,     3,     1,     4,     1,     0,     4,     1,
       3,     2,     2,     4,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     4,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     4,
       2,     2,     2,     2,     4,     4,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     2,     2,     2,     2,     2,
       2,     1,     2,     0,     0,     6,     2,     1,     2,     0,
       1,     1,     1,     0,     4,     1,     3,     0,     1,     1,
       1,     3,     5,     3,     1,     1,     1,     3,     3,     3,
       1,     3,     2,     5,     5,     2,     2,     1,     1,     1,
       2,     2,     1,     1,     3,     1,     3,     3,     1,     0,
       5,     3,     3,     1,     1,     2,     1,     2,     3,     3,
       3,     3,     5,     3,     3,     1,     3,     5,     7,     5,
       3
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* $@1: %empty  */
#line 161 "../src/parser.y"
        { 
        }
#line 1912 "y.tab.c"
    break;

  case 5: /* $@2: %empty  */
#line 166 "../src/parser.y"
                        { assert( current_Declaration_Site == globalDecls);}
#line 1918 "y.tab.c"
    break;

  case 7: /* inputItem: error ';'  */
#line 171 "../src/parser.y"
                  {
		flushScanBuffer();
		/* Kill all the local declarations -- ejr */
		Declaration_Site *ds1, *ds2;
		for(ds1 = current_Declaration_Site; ds1 != globalDecls;) {
		    ds2 = ds1;
		    ds1=ds1->previous;
		    delete ds2;
		}
                current_Declaration_Site = globalDecls;
		yyerror("skipping to statement end");
		}
#line 1935 "y.tab.c"
    break;

  case 8: /* inputItem: SYMBOLIC globVarList ';'  */
#line 184 "../src/parser.y"
                { flushScanBuffer();
		}
#line 1942 "y.tab.c"
    break;

  case 9: /* inputItem: VAR IS_ASSIGNED relation ';'  */
#line 187 "../src/parser.y"
                        {
			  flushScanBuffer();
			  (yyvsp[-1].RELATION)->simplify(::min(2,redundant_conj_level),4);
			  Relation *r = relationMap((Const_String)(yyvsp[-3].VAR_NAME));
			  if (r) delete r;
			  relationMap[(Const_String)(yyvsp[-3].VAR_NAME)] = (yyvsp[-1].RELATION); 
			  delete (yyvsp[-3].VAR_NAME);
			}
#line 1955 "y.tab.c"
    break;

  case 10: /* inputItem: relation ';'  */
#line 195 "../src/parser.y"
                       { 
			  flushScanBuffer();
			printf("\n"); 
			(yyvsp[-1].RELATION)->simplify(redundant_conj_level,4);
			(yyvsp[-1].RELATION)->print_with_subs(stdout); 
			printf("\n"); 
			delete (yyvsp[-1].RELATION);
			}
#line 1968 "y.tab.c"
    break;

  case 11: /* inputItem: TIME relation ';'  */
#line 203 "../src/parser.y"
                            {

#if defined(OMIT_GETRUSAGE)
	    printf("'time' requires getrusage, but the omega calclator was compiled with OMIT_GETRUSAGE set!\n");

#else

			flushScanBuffer();
			printf("\n");
			int t;
			Relation R;
			bool SKIP_FULL_CHECK = getenv("OC_TIMING_SKIP_FULL_CHECK");
			((yyvsp[-1].RELATION))->and_with_GEQ();
			start_clock();
			for (t=1;t<=100;t++) {
				R = *(yyvsp[-1].RELATION);
				R.finalize();
				}
			int copyTime = clock_diff();
			start_clock();
			for (t=1;t<=100;t++) {
				R = *(yyvsp[-1].RELATION);
				R.finalize();
				R.simplify();
				}
			int simplifyTime = clock_diff() -copyTime;
			Relation R2;
			if (!SKIP_FULL_CHECK)
			  {
			    start_clock();
			    for (t=1;t<=100;t++) {
			      R2 = *(yyvsp[-1].RELATION);
			      R2.finalize();
			      R2.simplify(2,4);
			    }
			  }
			int excessiveTime = clock_diff() - copyTime;
			printf("Times (in microseconds): \n");
			printf("%5d us to copy original set of constraints\n",copyTime/100);
			printf("%5d us to do the default amount of simplification, obtaining: \n\t",
					simplifyTime/100);
			R.print_with_subs(stdout); 
		    printf("\n"); 
			if (!SKIP_FULL_CHECK)
			  {
			    printf("%5d us to do the maximum (i.e., excessive) amount of simplification, obtaining: \n\t",
				   excessiveTime/100);
			    R2.print_with_subs(stdout); 
			    printf("\n");
			  }
			if (!anyTimingDone) {
				bool warn = false;
#ifndef SPEED 
				warn =true;
#endif
#ifndef NDEBUG
				warn = true;
#endif
				if (warn) {
				   printf("WARNING: The Omega calculator was compiled with options that force\n");
				   printf("it to perform additional consistency and error checks\n");
				   printf("that may slow it down substantially\n");
				  printf("\n");
				   }
				printf("NOTE: These times relect the time of the current _implementation_\n");
				printf("of our algorithms. Performance bugs do exist. If you intend to publish or \n");
				printf("report on the performance on the Omega test, we respectfully but strongly \n");
				printf("request that send your test cases to us to allow us to determine if the \n");
				printf("times are appropriate, and if the way you are using the Omega library to \n"); 
				printf("solve your problem is the most effective way.\n");
				printf("\n");

printf("Also, please be aware that over the past two years, we have focused our \n");
printf("efforts on the expressive power of the Omega library, sometimes at the\n");
printf("expensive of raw speed. Our original implementation of the Omega test\n");
printf("was substantially faster on the limited domain it handled.\n");
				printf("\n");
				printf("	Thanks, \n");
				printf("	   the Omega Team \n");	
				}			 
			anyTimingDone = true;
			delete (yyvsp[-1].RELATION);
#endif
			}
#line 2057 "y.tab.c"
    break;

  case 12: /* inputItem: TIMECLOSURE relation ';'  */
#line 287 "../src/parser.y"
                                   {

#if defined(OMIT_GETRUSAGE)
	    printf("'timeclosure' requires getrusage, but the omega calclator was compiled with OMIT_GETRUSAGE set!\n");
#else
			flushScanBuffer();
			printf("\n");
			int t;
			Relation R;
			((yyvsp[-1].RELATION))->and_with_GEQ();
			start_clock();
			for (t=1;t<=100;t++) {
				R = *(yyvsp[-1].RELATION);
				R.finalize();
				}
			int copyTime = clock_diff();
			start_clock();
			for (t=1;t<=100;t++) {
				R = *(yyvsp[-1].RELATION);
				R.finalize();
				R.simplify();
				};
			int simplifyTime = clock_diff() -copyTime;
			Relation Rclosed;
			start_clock();
			for (t=1;t<=100;t++) {
				Rclosed = *(yyvsp[-1].RELATION);
				Rclosed.finalize();
				Rclosed = TransitiveClosure(Rclosed, 1,Relation::Null());
				};
			int closureTime = clock_diff() - copyTime;
			Relation R2;
			start_clock();
			for (t=1;t<=100;t++) {
				R2 = *(yyvsp[-1].RELATION);
				R2.finalize();
				R2.simplify(2,4);
				};
			int excessiveTime = clock_diff() - copyTime;
			printf("Times (in microseconds): \n");
			printf("%5d us to copy original set of constraints\n",copyTime/100);
			printf("%5d us to do the default amount of simplification, obtaining: \n\t",
					simplifyTime/100);
			R.print_with_subs(stdout); 
		    printf("\n"); 
			printf("%5d us to do the maximum (i.e., excessive) amount of simplification, obtaining: \n\t",
					excessiveTime/100);
			R2.print_with_subs(stdout); 
			printf("%5d us to do the transitive closure, obtaining: \n\t",
					closureTime/100);
			Rclosed.print_with_subs(stdout);
		        printf("\n");
			if (!anyTimingDone) {
				bool warn = false;
#ifndef SPEED 
				warn =true;
#endif
#ifndef NDEBUG
				warn = true;
#endif
				if (warn) {
				   printf("WARNING: The Omega calculator was compiled with options that force\n");
				   printf("it to perform additional consistency and error checks\n");
				   printf("that may slow it down substantially\n");
				  printf("\n");
				   }
				printf("NOTE: These times relect the time of the current _implementation_\n");
				printf("of our algorithms. Performance bugs do exist. If you intend to publish or \n");
				printf("report on the performance on the Omega test, we respectfully but strongly \n");
				printf("request that send your test cases to us to allow us to determine if the \n");
				printf("times are appropriate, and if the way you are using the Omega library to \n"); 
				printf("solve your problem is the most effective way.\n");
				printf("\n");

printf("Also, please be aware that over the past two years, we have focused our \n");
printf("efforts on the expressive power of the Omega library, sometimes at the\n");
printf("expensive of raw speed. Our original implementation of the Omega test\n");
printf("was substantially faster on the limited domain it handled.\n");
				printf("\n");
				printf("	Thanks, \n");
				printf("	   the Omega Team \n");	
				}			 
			anyTimingDone = true;
			delete (yyvsp[-1].RELATION);
#endif
			}
#line 2148 "y.tab.c"
    break;

  case 13: /* inputItem: relation SUBSET relation ';'  */
#line 375 "../src/parser.y"
                                       {
			  flushScanBuffer();
	                int c = Must_Be_Subset(*(yyvsp[-3].RELATION), *(yyvsp[-1].RELATION));
			printf("\n%s\n", c ? "True" : "False");
			delete (yyvsp[-3].RELATION);
			delete (yyvsp[-1].RELATION);
			}
#line 2160 "y.tab.c"
    break;

  case 14: /* inputItem: CODEGEN effort relPairList context ';'  */
#line 383 "../src/parser.y"
                       {
			  flushScanBuffer();
			  String s = MMGenerateCode((yyvsp[-2].REL_TUPLE_PAIR)->mappings, (yyvsp[-2].REL_TUPLE_PAIR)->ispaces,*(yyvsp[-1].RELATION),(yyvsp[-3].INT_VALUE));
			  delete (yyvsp[-1].RELATION);
			  delete (yyvsp[-2].REL_TUPLE_PAIR);
			  printf("%s\n", (const char *) s); 
	               }
#line 2172 "y.tab.c"
    break;

  case 15: /* inputItem: TCODEGEN effort statementInfoResult context ';'  */
#line 391 "../src/parser.y"
                        {
			  flushScanBuffer();
			  String s = tcodegen((yyvsp[-3].INT_VALUE), *((yyvsp[-2].STM_INFO_TUPLE)), *((yyvsp[-1].RELATION)));
			  delete (yyvsp[-1].RELATION);
			  delete (yyvsp[-2].STM_INFO_TUPLE);
			  printf("%s\n", (const char *) s); 
			}
#line 2184 "y.tab.c"
    break;

  case 16: /* inputItem: SPMD blockAndProcsAndEffort relTripList ';'  */
#line 408 "../src/parser.y"
            {
	    Tuple<Free_Var_Decl*> lowerBounds(0), upperBounds(0), my_procs(0);
            Tuple<spmd_stmt_info *> names(0);

	    flushScanBuffer();
	    int nr_statements = (yyvsp[-1].REL_TUPLE_TRIPLE)->space.size();

	    for (int i = 1; i<= (yyvsp[-1].REL_TUPLE_TRIPLE)->space[1].n_out(); i++)
		{
	        lowerBounds.append(new Free_Var_Decl("lb" + itoS(i)));
	        upperBounds.append(new Free_Var_Decl("ub" + itoS(i)));
	        my_procs.append(new Free_Var_Decl("my_proc" + itoS(i)));
		}

            for (int p = 1; p <= nr_statements; p++)
                names.append(new numbered_stmt_info(p-1, Identity((yyvsp[-1].REL_TUPLE_TRIPLE)->time[p].n_out()),
					            (yyvsp[-1].REL_TUPLE_TRIPLE)->space[p], 
					(char *)(const char *)("s"+itoS(p-1))));

	    String s = SPMD_GenerateCode("", (yyvsp[-1].REL_TUPLE_TRIPLE)->space, (yyvsp[-1].REL_TUPLE_TRIPLE)->time, (yyvsp[-1].REL_TUPLE_TRIPLE)->ispaces, 
					 names,
					 lowerBounds, upperBounds, my_procs,
                                         nr_statements);

	    delete (yyvsp[-1].REL_TUPLE_TRIPLE);
	    printf("%s\n", (const char *) s); 
            }
#line 2216 "y.tab.c"
    break;

  case 17: /* inputItem: reachable ';'  */
#line 436 "../src/parser.y"
        { 	flushScanBuffer();
		Dynamic_Array1<Relation> &final = *(yyvsp[-1].RELATION_ARRAY_1D);
		bool any_sat=false;
		int i,n_nodes = reachable_info->node_names.size();
		for(i = 1; i <= n_nodes; i++) if(final[i].is_upper_bound_satisfiable()) {
		  any_sat = true;
		  fprintf(stdout,"Node %s: ",
			  (const char *) (reachable_info->node_names[i]));
		  final[i].print_with_subs(stdout);
		}
		if(!any_sat)
		  fprintf(stdout,"No nodes reachable.\n");
		delete (yyvsp[-1].RELATION_ARRAY_1D);
		delete reachable_info;
	}
#line 2236 "y.tab.c"
    break;

  case 18: /* relTripList: relTripList ',' relation ':' relation ':' relation  */
#line 454 "../src/parser.y"
                {
                (yyvsp[-6].REL_TUPLE_TRIPLE)->space.append(*(yyvsp[-4].RELATION));
                (yyvsp[-6].REL_TUPLE_TRIPLE)->time.append(*(yyvsp[-2].RELATION));
                (yyvsp[-6].REL_TUPLE_TRIPLE)->ispaces.append(*(yyvsp[0].RELATION));
                delete (yyvsp[-4].RELATION);
                delete (yyvsp[-2].RELATION);
                delete (yyvsp[0].RELATION);
                (yyval.REL_TUPLE_TRIPLE) = (yyvsp[-6].REL_TUPLE_TRIPLE);
                }
#line 2250 "y.tab.c"
    break;

  case 19: /* relTripList: relation ':' relation ':' relation  */
#line 464 "../src/parser.y"
                {
                RelTupleTriple *rtt = new RelTupleTriple;
                rtt->space.append(*(yyvsp[-4].RELATION));
                rtt->time.append(*(yyvsp[-2].RELATION));
                rtt->ispaces.append(*(yyvsp[0].RELATION));
                delete (yyvsp[-4].RELATION);
                delete (yyvsp[-2].RELATION);
                delete (yyvsp[0].RELATION);
                (yyval.REL_TUPLE_TRIPLE) = rtt;
                }
#line 2265 "y.tab.c"
    break;

  case 20: /* blockAndProcsAndEffort: %empty  */
#line 476 "../src/parser.y"
                          { Block_Size = 0; Num_Procs = 0; overheadEffort=0; }
#line 2271 "y.tab.c"
    break;

  case 21: /* blockAndProcsAndEffort: INT  */
#line 477 "../src/parser.y"
                     { Block_Size = (yyvsp[0].INT_VALUE); Num_Procs = 0; overheadEffort=0;}
#line 2277 "y.tab.c"
    break;

  case 22: /* blockAndProcsAndEffort: INT INT  */
#line 478 "../src/parser.y"
                         { Block_Size = (yyvsp[-1].INT_VALUE); Num_Procs = (yyvsp[0].INT_VALUE); overheadEffort=0;}
#line 2283 "y.tab.c"
    break;

  case 23: /* blockAndProcsAndEffort: INT INT INT  */
#line 479 "../src/parser.y"
                             { Block_Size = (yyvsp[-2].INT_VALUE); Num_Procs = (yyvsp[-1].INT_VALUE); overheadEffort=(yyvsp[0].INT_VALUE);}
#line 2289 "y.tab.c"
    break;

  case 24: /* effort: %empty  */
#line 482 "../src/parser.y"
         { (yyval.INT_VALUE) = 0; }
#line 2295 "y.tab.c"
    break;

  case 25: /* effort: INT  */
#line 483 "../src/parser.y"
              { (yyval.INT_VALUE) = (yyvsp[0].INT_VALUE); }
#line 2301 "y.tab.c"
    break;

  case 26: /* effort: '-' INT  */
#line 484 "../src/parser.y"
                  { (yyval.INT_VALUE) = -(yyvsp[0].INT_VALUE); }
#line 2307 "y.tab.c"
    break;

  case 27: /* context: %empty  */
#line 487 "../src/parser.y"
          { (yyval.RELATION) = new Relation();
		*(yyval.RELATION) = Relation::Null(); }
#line 2314 "y.tab.c"
    break;

  case 28: /* context: GIVEN relation  */
#line 489 "../src/parser.y"
                         {(yyval.RELATION) = (yyvsp[0].RELATION); }
#line 2320 "y.tab.c"
    break;

  case 29: /* relPairList: relPairList ',' relation ':' relation  */
#line 493 "../src/parser.y"
                {
	        (yyvsp[-4].REL_TUPLE_PAIR)->mappings.append(*(yyvsp[-2].RELATION));
		(yyvsp[-4].REL_TUPLE_PAIR)->mappings[(yyvsp[-4].REL_TUPLE_PAIR)->mappings.size()].compress();
		(yyvsp[-4].REL_TUPLE_PAIR)->ispaces.append(*(yyvsp[0].RELATION));
		(yyvsp[-4].REL_TUPLE_PAIR)->ispaces[(yyvsp[-4].REL_TUPLE_PAIR)->ispaces.size()].compress();
		delete (yyvsp[-2].RELATION);
		delete (yyvsp[0].RELATION);
	        (yyval.REL_TUPLE_PAIR) = (yyvsp[-4].REL_TUPLE_PAIR);
                }
#line 2334 "y.tab.c"
    break;

  case 30: /* relPairList: relPairList ',' relation  */
#line 503 "../src/parser.y"
                {
	        (yyvsp[-2].REL_TUPLE_PAIR)->mappings.append(Identity((yyvsp[0].RELATION)->n_set()));
		(yyvsp[-2].REL_TUPLE_PAIR)->mappings[(yyvsp[-2].REL_TUPLE_PAIR)->mappings.size()].compress();
		(yyvsp[-2].REL_TUPLE_PAIR)->ispaces.append(*(yyvsp[0].RELATION));
		(yyvsp[-2].REL_TUPLE_PAIR)->ispaces[(yyvsp[-2].REL_TUPLE_PAIR)->ispaces.size()].compress();
		delete (yyvsp[0].RELATION);
	        (yyval.REL_TUPLE_PAIR) = (yyvsp[-2].REL_TUPLE_PAIR);
                }
#line 2347 "y.tab.c"
    break;

  case 31: /* relPairList: relation ':' relation  */
#line 512 "../src/parser.y"
                {
                RelTuplePair *rtp = new RelTuplePair;
	        rtp->mappings.append(*(yyvsp[-2].RELATION));
		rtp->mappings[rtp->mappings.size()].compress();
	        rtp->ispaces.append(*(yyvsp[0].RELATION));
		rtp->ispaces[rtp->ispaces.size()].compress();
		delete (yyvsp[-2].RELATION);
		delete (yyvsp[0].RELATION);
	        (yyval.REL_TUPLE_PAIR) = rtp;
		}
#line 2362 "y.tab.c"
    break;

  case 32: /* relPairList: relation  */
#line 523 "../src/parser.y"
                {
                RelTuplePair *rtp = new RelTuplePair;
	        rtp->mappings.append(Identity((yyvsp[0].RELATION)->n_set()));
		rtp->mappings[rtp->mappings.size()].compress();
	        rtp->ispaces.append(*(yyvsp[0].RELATION));
		rtp->ispaces[rtp->ispaces.size()].compress();
		delete (yyvsp[0].RELATION);
	        (yyval.REL_TUPLE_PAIR) = rtp;
                }
#line 2376 "y.tab.c"
    break;

  case 33: /* statementInfoResult: statementInfoList  */
#line 535 "../src/parser.y"
                { (yyval.STM_INFO_TUPLE) = (yyvsp[0].STM_INFO_TUPLE); }
#line 2382 "y.tab.c"
    break;

  case 34: /* statementInfoResult: TRANS_IS relation statementInfoResult  */
#line 542 "../src/parser.y"
                { (yyval.STM_INFO_TUPLE) = &Trans_IS(*((yyvsp[0].STM_INFO_TUPLE)), *((yyvsp[-1].RELATION)));
		  delete (yyvsp[-1].RELATION);
		}
#line 2390 "y.tab.c"
    break;

  case 35: /* statementInfoResult: SET_MMAP INT partialwrites statementInfoResult  */
#line 546 "../src/parser.y"
                { (yyval.STM_INFO_TUPLE) = &Set_MMap(*((yyvsp[0].STM_INFO_TUPLE)), (yyvsp[-2].INT_VALUE), *((yyvsp[-1].MMAP)));
		  delete (yyvsp[-1].MMAP);
		}
#line 2398 "y.tab.c"
    break;

  case 36: /* statementInfoResult: UNROLL_IS INT INT INT statementInfoResult  */
#line 550 "../src/parser.y"
                { (yyval.STM_INFO_TUPLE) = &Unroll_One_IS(*((yyvsp[0].STM_INFO_TUPLE)), (yyvsp[-3].INT_VALUE), (yyvsp[-2].INT_VALUE), (yyvsp[-1].INT_VALUE));}
#line 2404 "y.tab.c"
    break;

  case 37: /* statementInfoResult: PEEL_IS INT INT relation statementInfoResult  */
#line 552 "../src/parser.y"
                { (yyval.STM_INFO_TUPLE) = &Peel_One_IS(*((yyvsp[0].STM_INFO_TUPLE)), (yyvsp[-3].INT_VALUE), (yyvsp[-2].INT_VALUE), *((yyvsp[-1].RELATION)));
		  delete (yyvsp[-1].RELATION);
		}
#line 2412 "y.tab.c"
    break;

  case 38: /* statementInfoResult: PEEL_IS INT INT relation ',' relation statementInfoResult  */
#line 556 "../src/parser.y"
                { (yyval.STM_INFO_TUPLE) = &Peel_One_IS(*((yyvsp[0].STM_INFO_TUPLE)), (yyvsp[-5].INT_VALUE), (yyvsp[-4].INT_VALUE), *((yyvsp[-3].RELATION)), *((yyvsp[-1].RELATION)));
		  delete (yyvsp[-3].RELATION);
		  delete (yyvsp[-1].RELATION);
		}
#line 2421 "y.tab.c"
    break;

  case 39: /* statementInfoList: statementInfo  */
#line 562 "../src/parser.y"
                                                { (yyval.STM_INFO_TUPLE) = new Tuple<stm_info>;
						  (yyval.STM_INFO_TUPLE)->append(*((yyvsp[0].STM_INFO)));
						  delete (yyvsp[0].STM_INFO); }
#line 2429 "y.tab.c"
    break;

  case 40: /* statementInfoList: statementInfoList ',' statementInfo  */
#line 565 "../src/parser.y"
                                                { (yyval.STM_INFO_TUPLE) = (yyvsp[-2].STM_INFO_TUPLE);
						  (yyval.STM_INFO_TUPLE)->append(*((yyvsp[0].STM_INFO)));
						  delete (yyvsp[0].STM_INFO); }
#line 2437 "y.tab.c"
    break;

  case 41: /* statementInfo: '[' STRING ',' relation ',' partialwrites ',' reads ']'  */
#line 571 "../src/parser.y"
                { (yyval.STM_INFO) = (yyvsp[-1].STM_INFO);
		  (yyval.STM_INFO)->stm = *((yyvsp[-7].STRING_VALUE)); delete (yyvsp[-7].STRING_VALUE);
		  (yyval.STM_INFO)->IS  = *((yyvsp[-5].RELATION)); delete (yyvsp[-5].RELATION);
		  (yyval.STM_INFO)->map = *((yyvsp[-3].MMAP)); delete (yyvsp[-3].MMAP);
		  }
#line 2447 "y.tab.c"
    break;

  case 42: /* statementInfo: '[' STRING ',' relation ',' partialwrites ']'  */
#line 577 "../src/parser.y"
                { (yyval.STM_INFO) = new stm_info;
		  (yyval.STM_INFO)->stm = *((yyvsp[-5].STRING_VALUE)); delete (yyvsp[-5].STRING_VALUE);
		  (yyval.STM_INFO)->IS  = *((yyvsp[-3].RELATION)); delete (yyvsp[-3].RELATION);
		  (yyval.STM_INFO)->map = *((yyvsp[-1].MMAP)); delete (yyvsp[-1].MMAP);
		}
#line 2457 "y.tab.c"
    break;

  case 43: /* partialwrites: partialwrites ',' partialwrite  */
#line 585 "../src/parser.y"
                                { (yyval.MMAP) = (yyvsp[-2].MMAP);
				  (yyval.MMAP)->partials.append(*((yyvsp[0].PMMAP))); delete (yyvsp[0].PMMAP);
				}
#line 2465 "y.tab.c"
    break;

  case 44: /* partialwrites: partialwrite  */
#line 588 "../src/parser.y"
                                { (yyval.MMAP) = new MMap;
				  (yyval.MMAP)->partials.append(*((yyvsp[0].PMMAP))); delete (yyvsp[0].PMMAP);
				}
#line 2473 "y.tab.c"
    break;

  case 45: /* partialwrite: STRING '[' relation ']' ',' relation  */
#line 594 "../src/parser.y"
                                        { (yyval.PMMAP) = new PartialMMap;
					  (yyval.PMMAP)->mapping = *((yyvsp[0].RELATION)); delete (yyvsp[0].RELATION);
					  (yyval.PMMAP)->bounds  = *((yyvsp[-3].RELATION)); delete (yyvsp[-3].RELATION);
					  (yyval.PMMAP)->var     = *((yyvsp[-5].STRING_VALUE)); delete (yyvsp[-5].STRING_VALUE);
					}
#line 2483 "y.tab.c"
    break;

  case 46: /* partialwrite: STRING ',' relation  */
#line 599 "../src/parser.y"
                                        { (yyval.PMMAP) = new PartialMMap;
					  (yyval.PMMAP)->mapping = *((yyvsp[0].RELATION)); delete (yyvsp[0].RELATION);
					  (yyval.PMMAP)->bounds  = Relation::True(0);
					  (yyval.PMMAP)->var     = *((yyvsp[-2].STRING_VALUE)); delete (yyvsp[-2].STRING_VALUE);
					}
#line 2493 "y.tab.c"
    break;

  case 47: /* reads: reads ',' oneread  */
#line 606 "../src/parser.y"
                                { (yyval.STM_INFO) = (yyvsp[-2].STM_INFO);
				  (yyval.STM_INFO)->read.append(*((yyvsp[0].READ))); delete (yyvsp[0].READ);
				}
#line 2501 "y.tab.c"
    break;

  case 48: /* reads: oneread  */
#line 609 "../src/parser.y"
                                { (yyval.STM_INFO) = new stm_info;
				  (yyval.STM_INFO)->read.append(*((yyvsp[0].READ))); delete (yyvsp[0].READ);
				}
#line 2509 "y.tab.c"
    break;

  case 49: /* oneread: '[' partials ']'  */
#line 614 "../src/parser.y"
                            { (yyval.READ) = (yyvsp[-1].READ); }
#line 2515 "y.tab.c"
    break;

  case 50: /* partials: partials ',' partial  */
#line 617 "../src/parser.y"
                                { (yyval.READ) = (yyvsp[-2].READ);
				  (yyval.READ)->partials.append(*((yyvsp[0].PREAD))); delete (yyvsp[0].PREAD);
				}
#line 2523 "y.tab.c"
    break;

  case 51: /* partials: partial  */
#line 620 "../src/parser.y"
                                { (yyval.READ) = new Read;
				  (yyval.READ)->partials.append(*((yyvsp[0].PREAD))); delete (yyvsp[0].PREAD);
				}
#line 2531 "y.tab.c"
    break;

  case 52: /* partial: INT ',' relation  */
#line 625 "../src/parser.y"
                                { (yyval.PREAD) = new PartialRead;
				  (yyval.PREAD)->from = (yyvsp[-2].INT_VALUE);
				  (yyval.PREAD)->dataFlow = *((yyvsp[0].RELATION)); delete (yyvsp[0].RELATION);
				}
#line 2540 "y.tab.c"
    break;

  case 55: /* globVar: VAR '(' INT ')'  */
#line 636 "../src/parser.y"
                { globalDecls->extend_both_tuples((yyvsp[-3].VAR_NAME), (yyvsp[-1].INT_VALUE)); free((yyvsp[-3].VAR_NAME)); }
#line 2546 "y.tab.c"
    break;

  case 56: /* globVar: VAR  */
#line 638 "../src/parser.y"
                { globalDecls->extend((yyvsp[0].VAR_NAME)); free((yyvsp[0].VAR_NAME)); }
#line 2552 "y.tab.c"
    break;

  case 57: /* $@3: %empty  */
#line 642 "../src/parser.y"
                { relationDecl = new Declaration_Site(); }
#line 2558 "y.tab.c"
    break;

  case 58: /* relation: OPEN_BRACE $@3 builtRelation CLOSE_BRACE  */
#line 645 "../src/parser.y"
                { (yyval.RELATION) = (yyvsp[-1].RELATION); 
		  if (omega_calc_debug) {
			fprintf(DebugFile,"Built relation:\n");
			(yyval.RELATION)->prefix_print(DebugFile);
			};
		  current_Declaration_Site = globalDecls;
		  delete relationDecl;
		}
#line 2571 "y.tab.c"
    break;

  case 59: /* relation: VAR  */
#line 653 "../src/parser.y"
               {
		Const_String s = (yyvsp[0].VAR_NAME);
		if (relationMap(s) == 0) {
			fprintf(stderr,"Variable %s not declared\n",(yyvsp[0].VAR_NAME));
			free((yyvsp[0].VAR_NAME));
			YYERROR;
			assert(0);
			};
		free((yyvsp[0].VAR_NAME));
		(yyval.RELATION) = new Relation(*relationMap(s));
		}
#line 2587 "y.tab.c"
    break;

  case 60: /* relation: '(' relation ')'  */
#line 664 "../src/parser.y"
                                {(yyval.RELATION) = (yyvsp[-1].RELATION);}
#line 2593 "y.tab.c"
    break;

  case 61: /* relation: relation '+'  */
#line 666 "../src/parser.y"
                { (yyval.RELATION) = new Relation();
		  *(yyval.RELATION) = TransitiveClosure(*(yyvsp[-1].RELATION), 1,Relation::Null());
		  delete (yyvsp[-1].RELATION);
		}
#line 2602 "y.tab.c"
    break;

  case 62: /* relation: relation '*'  */
#line 671 "../src/parser.y"
                { (yyval.RELATION) = new Relation();
		  int vars = (yyvsp[-1].RELATION)->n_inp();
		  *(yyval.RELATION) = Union(Identity(vars),
			      TransitiveClosure(*(yyvsp[-1].RELATION), 1,Relation::Null()));
		  delete (yyvsp[-1].RELATION);
		}
#line 2613 "y.tab.c"
    break;

  case 63: /* relation: relation '+' WITHIN relation  */
#line 678 "../src/parser.y"
                {(yyval.RELATION) = new Relation();
                 *(yyval.RELATION)= TransitiveClosure(*(yyvsp[-3].RELATION), 1,*(yyvsp[0].RELATION));
                 delete (yyvsp[-3].RELATION);
                 delete (yyvsp[0].RELATION);
	       }
#line 2623 "y.tab.c"
    break;

  case 64: /* relation: MINIMIZE_RANGE relation  */
#line 684 "../src/parser.y"
                {
		Relation o(*(yyvsp[0].RELATION));
		Relation r(*(yyvsp[0].RELATION));
		r = Join(r,LexForward((yyvsp[0].RELATION)->n_out()));
		(yyval.RELATION) = new Relation();
		*(yyval.RELATION) = Difference(o,r);
		delete (yyvsp[0].RELATION);
		}
#line 2636 "y.tab.c"
    break;

  case 65: /* relation: MAXIMIZE_RANGE relation  */
#line 693 "../src/parser.y"
                {
		Relation o(*(yyvsp[0].RELATION));
		Relation r(*(yyvsp[0].RELATION));
		r = Join(r,Inverse(LexForward((yyvsp[0].RELATION)->n_out())));
		(yyval.RELATION) = new Relation();
		*(yyval.RELATION) = Difference(o,r);
		delete (yyvsp[0].RELATION);
		}
#line 2649 "y.tab.c"
    break;

  case 66: /* relation: MINIMIZE_DOMAIN relation  */
#line 702 "../src/parser.y"
                {
		Relation o(*(yyvsp[0].RELATION));
		Relation r(*(yyvsp[0].RELATION));
		r = Join(LexForward((yyvsp[0].RELATION)->n_inp()),r);
		(yyval.RELATION) = new Relation();
		*(yyval.RELATION) = Difference(o,r);
		delete (yyvsp[0].RELATION);
		}
#line 2662 "y.tab.c"
    break;

  case 67: /* relation: MAXIMIZE_DOMAIN relation  */
#line 711 "../src/parser.y"
                {
		Relation o(*(yyvsp[0].RELATION));
		Relation r(*(yyvsp[0].RELATION));
		r = Join(Inverse(LexForward((yyvsp[0].RELATION)->n_inp())),r);
		(yyval.RELATION) = new Relation();
		*(yyval.RELATION) = Difference(o,r);
		delete (yyvsp[0].RELATION);
		}
#line 2675 "y.tab.c"
    break;

  case 68: /* relation: MAXIMIZE relation  */
#line 720 "../src/parser.y"
                {
		Relation c(*(yyvsp[0].RELATION));
		Relation r(*(yyvsp[0].RELATION));
		(yyval.RELATION) = new Relation(); 
		*(yyval.RELATION) = Cross_Product(Relation(*(yyvsp[0].RELATION)),c);
		delete (yyvsp[0].RELATION);
		assert((yyval.RELATION)->n_inp() ==(yyval.RELATION)->n_out());
		*(yyval.RELATION) = Difference(r,Domain(Intersection(*(yyval.RELATION),LexForward((yyval.RELATION)->n_inp()))));
		}
#line 2689 "y.tab.c"
    break;

  case 69: /* relation: MINIMIZE relation  */
#line 730 "../src/parser.y"
                {
		Relation c(*(yyvsp[0].RELATION));
		Relation r(*(yyvsp[0].RELATION));
		(yyval.RELATION) = new Relation(); 
		*(yyval.RELATION) = Cross_Product(Relation(*(yyvsp[0].RELATION)),c);
		delete (yyvsp[0].RELATION);
		assert((yyval.RELATION)->n_inp() ==(yyval.RELATION)->n_out());
		*(yyval.RELATION) = Difference(r,Range(Intersection(*(yyval.RELATION),LexForward((yyval.RELATION)->n_inp()))));
		}
#line 2703 "y.tab.c"
    break;

  case 70: /* relation: FARKAS relation  */
#line 740 "../src/parser.y"
                {
		(yyval.RELATION) = new Relation();
		*(yyval.RELATION) = Farkas(*(yyvsp[0].RELATION), Basic_Farkas);
		delete (yyvsp[0].RELATION);
		}
#line 2713 "y.tab.c"
    break;

  case 71: /* relation: DECOUPLED_FARKAS relation  */
#line 746 "../src/parser.y"
                {
		(yyval.RELATION) = new Relation();
		*(yyval.RELATION) = Farkas(*(yyvsp[0].RELATION), Decoupled_Farkas);
		delete (yyvsp[0].RELATION);
		}
#line 2723 "y.tab.c"
    break;

  case 72: /* relation: relation '@'  */
#line 752 "../src/parser.y"
                { (yyval.RELATION) = new Relation();
		  *(yyval.RELATION) = ConicClosure(*(yyvsp[-1].RELATION));
		  delete (yyvsp[-1].RELATION);
		}
#line 2732 "y.tab.c"
    break;

  case 73: /* relation: PROJECT_AWAY_SYMBOLS relation  */
#line 757 "../src/parser.y"
                { (yyval.RELATION) = new Relation();
		  *(yyval.RELATION) = Project_Sym(*(yyvsp[0].RELATION));
		  delete (yyvsp[0].RELATION);
		}
#line 2741 "y.tab.c"
    break;

  case 74: /* relation: PROJECT_ON_SYMBOLS relation  */
#line 762 "../src/parser.y"
                { (yyval.RELATION) = new Relation();
		  *(yyval.RELATION) = Project_On_Sym(*(yyvsp[0].RELATION));
		  delete (yyvsp[0].RELATION);
		}
#line 2750 "y.tab.c"
    break;

  case 75: /* relation: DIFFERENCE relation  */
#line 767 "../src/parser.y"
                { (yyval.RELATION) = new Relation();
		  *(yyval.RELATION) = Deltas(*(yyvsp[0].RELATION));
		  delete (yyvsp[0].RELATION);
		}
#line 2759 "y.tab.c"
    break;

  case 76: /* relation: DIFFERENCE_TO_RELATION relation  */
#line 772 "../src/parser.y"
                { (yyval.RELATION) = new Relation();
                  *(yyval.RELATION) = DeltasToRelation(*(yyvsp[0].RELATION),(yyvsp[0].RELATION)->n_set(),(yyvsp[0].RELATION)->n_set());
                  delete (yyvsp[0].RELATION);
                }
#line 2768 "y.tab.c"
    break;

  case 77: /* relation: OMEGA_DOMAIN relation  */
#line 777 "../src/parser.y"
                { (yyval.RELATION) = new Relation();
		  *(yyval.RELATION) = Domain(*(yyvsp[0].RELATION));
		  delete (yyvsp[0].RELATION);
		}
#line 2777 "y.tab.c"
    break;

  case 78: /* relation: VENN relation  */
#line 782 "../src/parser.y"
                { (yyval.RELATION) = new Relation();
		  *(yyval.RELATION) = VennDiagramForm(*(yyvsp[0].RELATION),Relation::True(*(yyvsp[0].RELATION)));
		  delete (yyvsp[0].RELATION);
		}
#line 2786 "y.tab.c"
    break;

  case 79: /* relation: VENN relation GIVEN relation  */
#line 787 "../src/parser.y"
                { (yyval.RELATION) = new Relation();
		  *(yyval.RELATION) = VennDiagramForm(*(yyvsp[-2].RELATION),*(yyvsp[0].RELATION));
		  delete (yyvsp[-2].RELATION);
		  delete (yyvsp[0].RELATION);
		}
#line 2796 "y.tab.c"
    break;

  case 80: /* relation: CONVEX_HULL relation  */
#line 793 "../src/parser.y"
                { (yyval.RELATION) = new Relation();
		  *(yyval.RELATION) = ConvexHull(*(yyvsp[0].RELATION));
		  delete (yyvsp[0].RELATION);
		}
#line 2805 "y.tab.c"
    break;

  case 81: /* relation: POSITIVE_COMBINATION relation  */
#line 798 "../src/parser.y"
                { (yyval.RELATION) = new Relation();
		  *(yyval.RELATION) = Farkas(*(yyvsp[0].RELATION),Positive_Combination_Farkas);
		  delete (yyvsp[0].RELATION);
		}
#line 2814 "y.tab.c"
    break;

  case 82: /* relation: CONVEX_COMBINATION relation  */
#line 803 "../src/parser.y"
                { (yyval.RELATION) = new Relation();
		  *(yyval.RELATION) = Farkas(*(yyvsp[0].RELATION),Convex_Combination_Farkas);
		  delete (yyvsp[0].RELATION);
		}
#line 2823 "y.tab.c"
    break;

  case 83: /* relation: PAIRWISE_CHECK relation  */
#line 808 "../src/parser.y"
                { (yyval.RELATION) = new Relation();
		  *(yyval.RELATION) = CheckForConvexRepresentation(CheckForConvexPairs(*(yyvsp[0].RELATION)));
		  delete (yyvsp[0].RELATION);
		}
#line 2832 "y.tab.c"
    break;

  case 84: /* relation: CONVEX_CHECK relation  */
#line 813 "../src/parser.y"
                { (yyval.RELATION) = new Relation();
		  *(yyval.RELATION) = CheckForConvexRepresentation(*(yyvsp[0].RELATION));
		  delete (yyvsp[0].RELATION);
		}
#line 2841 "y.tab.c"
    break;

  case 85: /* relation: AFFINE_HULL relation  */
#line 818 "../src/parser.y"
                { (yyval.RELATION) = new Relation();
		  *(yyval.RELATION) = AffineHull(*(yyvsp[0].RELATION));
		  delete (yyvsp[0].RELATION);
		}
#line 2850 "y.tab.c"
    break;

  case 86: /* relation: CONIC_HULL relation  */
#line 823 "../src/parser.y"
                { (yyval.RELATION) = new Relation();
		  *(yyval.RELATION) = ConicHull(*(yyvsp[0].RELATION));
		  delete (yyvsp[0].RELATION);
		}
#line 2859 "y.tab.c"
    break;

  case 87: /* relation: LINEAR_HULL relation  */
#line 828 "../src/parser.y"
                { (yyval.RELATION) = new Relation();
		  *(yyval.RELATION) = LinearHull(*(yyvsp[0].RELATION));
		  delete (yyvsp[0].RELATION);
		}
#line 2868 "y.tab.c"
    break;

  case 88: /* relation: HULL relation  */
#line 833 "../src/parser.y"
                { (yyval.RELATION) = new Relation();
		  *(yyval.RELATION) = Hull(*(yyvsp[0].RELATION),false,1,Null_Relation());
		  delete (yyvsp[0].RELATION);
		}
#line 2877 "y.tab.c"
    break;

  case 89: /* relation: HULL relation GIVEN relation  */
#line 838 "../src/parser.y"
                { (yyval.RELATION) = new Relation();
		  *(yyval.RELATION) = Hull(*(yyvsp[-2].RELATION),false,1,*(yyvsp[0].RELATION));
		  delete (yyvsp[-2].RELATION);
		  delete (yyvsp[0].RELATION);
		}
#line 2887 "y.tab.c"
    break;

  case 90: /* relation: APPROX relation  */
#line 844 "../src/parser.y"
                { (yyval.RELATION) = new Relation();
		  *(yyval.RELATION) = Approximate(*(yyvsp[0].RELATION));
		  delete (yyvsp[0].RELATION);
		}
#line 2896 "y.tab.c"
    break;

  case 91: /* relation: RANGE relation  */
#line 849 "../src/parser.y"
                { (yyval.RELATION) = new Relation();
		  *(yyval.RELATION) = Range(*(yyvsp[0].RELATION));
		  delete (yyvsp[0].RELATION);
		}
#line 2905 "y.tab.c"
    break;

  case 92: /* relation: INVERSE relation  */
#line 854 "../src/parser.y"
                { (yyval.RELATION) = new Relation();
		  *(yyval.RELATION) = Inverse(*(yyvsp[0].RELATION));
		  delete (yyvsp[0].RELATION);
		}
#line 2914 "y.tab.c"
    break;

  case 93: /* relation: COMPLEMENT relation  */
#line 859 "../src/parser.y"
                { (yyval.RELATION) = new Relation();
		  *(yyval.RELATION) = Complement(*(yyvsp[0].RELATION));
		  delete (yyvsp[0].RELATION);
		}
#line 2923 "y.tab.c"
    break;

  case 94: /* relation: GIST relation GIVEN relation  */
#line 864 "../src/parser.y"
                { (yyval.RELATION) = new Relation();
		  *(yyval.RELATION) = Gist(*(yyvsp[-2].RELATION),*(yyvsp[0].RELATION),1);
		  delete (yyvsp[-2].RELATION);
		  delete (yyvsp[0].RELATION);
		}
#line 2933 "y.tab.c"
    break;

  case 95: /* relation: relation '(' relation ')'  */
#line 870 "../src/parser.y"
                { (yyval.RELATION) = new Relation();
		  *(yyval.RELATION) = Composition(*(yyvsp[-3].RELATION),*(yyvsp[-1].RELATION));
		  delete (yyvsp[-3].RELATION);
		  delete (yyvsp[-1].RELATION);
		}
#line 2943 "y.tab.c"
    break;

  case 96: /* relation: relation COMPOSE relation  */
#line 876 "../src/parser.y"
                { (yyval.RELATION) = new Relation();
		  *(yyval.RELATION) = Composition(*(yyvsp[-2].RELATION),*(yyvsp[0].RELATION));
		  delete (yyvsp[-2].RELATION);
		  delete (yyvsp[0].RELATION);
		}
#line 2953 "y.tab.c"
    break;

  case 97: /* relation: relation CARRIED_BY INT  */
#line 882 "../src/parser.y"
                { (yyval.RELATION) = new Relation();
		  *(yyval.RELATION) = After(*(yyvsp[-2].RELATION),(yyvsp[0].INT_VALUE),(yyvsp[0].INT_VALUE));
		  delete (yyvsp[-2].RELATION);
		  (*(yyval.RELATION)).prefix_print(stdout);
		}
#line 2963 "y.tab.c"
    break;

  case 98: /* relation: relation JOIN relation  */
#line 888 "../src/parser.y"
                { (yyval.RELATION) = new Relation();
		  *(yyval.RELATION) = Composition(*(yyvsp[0].RELATION),*(yyvsp[-2].RELATION));
		  delete (yyvsp[-2].RELATION);
		  delete (yyvsp[0].RELATION);
		}
#line 2973 "y.tab.c"
    break;

  case 99: /* relation: relation RESTRICT_RANGE relation  */
#line 894 "../src/parser.y"
                { (yyval.RELATION) = new Relation();
		  *(yyval.RELATION) = Restrict_Range(*(yyvsp[-2].RELATION),*(yyvsp[0].RELATION));
		  delete (yyvsp[-2].RELATION);
		  delete (yyvsp[0].RELATION);
		}
#line 2983 "y.tab.c"
    break;

  case 100: /* relation: relation RESTRICT_DOMAIN relation  */
#line 900 "../src/parser.y"
                { (yyval.RELATION) = new Relation();
		  *(yyval.RELATION) = Restrict_Domain(*(yyvsp[-2].RELATION),*(yyvsp[0].RELATION));
		  delete (yyvsp[-2].RELATION);
		  delete (yyvsp[0].RELATION);
		}
#line 2993 "y.tab.c"
    break;

  case 101: /* relation: relation INTERSECTION relation  */
#line 906 "../src/parser.y"
                { (yyval.RELATION) = new Relation();
		  *(yyval.RELATION) = Intersection(*(yyvsp[-2].RELATION),*(yyvsp[0].RELATION));
		  delete (yyvsp[-2].RELATION);
		  delete (yyvsp[0].RELATION);
		}
#line 3003 "y.tab.c"
    break;

  case 102: /* relation: relation '-' relation  */
#line 912 "../src/parser.y"
                { (yyval.RELATION) = new Relation();
                  *(yyval.RELATION) = Difference(*(yyvsp[-2].RELATION),*(yyvsp[0].RELATION));
                  delete (yyvsp[-2].RELATION);
                  delete (yyvsp[0].RELATION);
                }
#line 3013 "y.tab.c"
    break;

  case 103: /* relation: relation UNION relation  */
#line 918 "../src/parser.y"
                { (yyval.RELATION) = new Relation();
		  *(yyval.RELATION) = Union(*(yyvsp[-2].RELATION),*(yyvsp[0].RELATION));
		  delete (yyvsp[-2].RELATION);
		  delete (yyvsp[0].RELATION);
		}
#line 3023 "y.tab.c"
    break;

  case 104: /* relation: relation '*' relation  */
#line 924 "../src/parser.y"
                { (yyval.RELATION) = new Relation();
		  *(yyval.RELATION) = Cross_Product(*(yyvsp[-2].RELATION),*(yyvsp[0].RELATION));
		  delete (yyvsp[-2].RELATION);
		  delete (yyvsp[0].RELATION);
		}
#line 3033 "y.tab.c"
    break;

  case 105: /* relation: SUPERSETOF relation  */
#line 930 "../src/parser.y"
                { (yyval.RELATION) = new Relation();
                  *(yyval.RELATION) = Union(*(yyvsp[0].RELATION), Relation::Unknown(*(yyvsp[0].RELATION)));
                  delete (yyvsp[0].RELATION);
                }
#line 3042 "y.tab.c"
    break;

  case 106: /* relation: SUBSETOF relation  */
#line 935 "../src/parser.y"
                { (yyval.RELATION) = new Relation();
                  *(yyval.RELATION) = Intersection(*(yyvsp[0].RELATION), Relation::Unknown(*(yyvsp[0].RELATION)));
                  delete (yyvsp[0].RELATION);
                }
#line 3051 "y.tab.c"
    break;

  case 107: /* relation: MAKE_UPPER_BOUND relation  */
#line 940 "../src/parser.y"
                { (yyval.RELATION) = new Relation();
                  *(yyval.RELATION) = Upper_Bound(*(yyvsp[0].RELATION));
                  delete (yyvsp[0].RELATION);
                }
#line 3060 "y.tab.c"
    break;

  case 108: /* relation: MAKE_LOWER_BOUND relation  */
#line 945 "../src/parser.y"
                { (yyval.RELATION) = new Relation();
                  *(yyval.RELATION) = Lower_Bound(*(yyvsp[0].RELATION));
                  delete (yyvsp[0].RELATION);
                }
#line 3069 "y.tab.c"
    break;

  case 109: /* relation: SAMPLE relation  */
#line 950 "../src/parser.y"
                { (yyval.RELATION) = new Relation();
                  *(yyval.RELATION) = Sample_Solution(*(yyvsp[0].RELATION));
                  delete (yyvsp[0].RELATION);
                }
#line 3078 "y.tab.c"
    break;

  case 110: /* relation: SYM_SAMPLE relation  */
#line 955 "../src/parser.y"
                { (yyval.RELATION) = new Relation();
                  *(yyval.RELATION) = Symbolic_Solution(*(yyvsp[0].RELATION));
                  delete (yyvsp[0].RELATION);
                }
#line 3087 "y.tab.c"
    break;

  case 111: /* relation: reachable_of  */
#line 959 "../src/parser.y"
                        { (yyval.RELATION) = (yyvsp[0].RELATION); }
#line 3093 "y.tab.c"
    break;

  case 112: /* relation: ASSERT_UNSAT relation  */
#line 961 "../src/parser.y"
                {
		  if (((yyvsp[0].RELATION))->is_satisfiable())
			  {
			    fprintf(stderr,"assert_unsatisfiable failed on ");
			    ((yyvsp[0].RELATION))->print_with_subs(stderr);
			    Exit(1);
			  }
		  (yyval.RELATION)=(yyvsp[0].RELATION);
		}
#line 3107 "y.tab.c"
    break;

  case 113: /* $@4: %empty  */
#line 974 "../src/parser.y"
                                 {currentTuple = Output_Tuple;}
#line 3113 "y.tab.c"
    break;

  case 114: /* $@5: %empty  */
#line 975 "../src/parser.y"
                                         {currentTuple = Input_Tuple;}
#line 3119 "y.tab.c"
    break;

  case 115: /* builtRelation: tupleDeclaration GOES_TO $@4 tupleDeclaration $@5 optionalFormula  */
#line 975 "../src/parser.y"
                                                                                       {
		Relation * r = new Relation((yyvsp[-5].TUPLE_DESCRIPTOR)->size,(yyvsp[-2].TUPLE_DESCRIPTOR)->size);
		resetGlobals();
		F_And *f = r->add_and();
		int i;
		for(i=1;i<=(yyvsp[-5].TUPLE_DESCRIPTOR)->size;i++) {	
			(yyvsp[-5].TUPLE_DESCRIPTOR)->vars[i]->vid = r->input_var(i);
			if (!(yyvsp[-5].TUPLE_DESCRIPTOR)->vars[i]->anonymous) 
				r->name_input_var(i,(yyvsp[-5].TUPLE_DESCRIPTOR)->vars[i]->stripped_name);
			};
		for(i=1;i<=(yyvsp[-2].TUPLE_DESCRIPTOR)->size;i++) {
			(yyvsp[-2].TUPLE_DESCRIPTOR)->vars[i]->vid = r->output_var(i);
			if (!(yyvsp[-2].TUPLE_DESCRIPTOR)->vars[i]->anonymous) 
				r->name_output_var(i,(yyvsp[-2].TUPLE_DESCRIPTOR)->vars[i]->stripped_name);
			};
		foreach(e,Exp*,(yyvsp[-5].TUPLE_DESCRIPTOR)->eq_constraints, install_eq(f,e,0));
                foreach(e,Exp*,(yyvsp[-5].TUPLE_DESCRIPTOR)->geq_constraints, install_geq(f,e,0)); 
		foreach(c,strideConstraint*,(yyvsp[-5].TUPLE_DESCRIPTOR)->stride_constraints, install_stride(f,c));
		foreach(e,Exp*,(yyvsp[-2].TUPLE_DESCRIPTOR)->eq_constraints, install_eq(f,e,0));
		foreach(e,Exp*,(yyvsp[-2].TUPLE_DESCRIPTOR)->geq_constraints, install_geq(f,e,0));
		foreach(c,strideConstraint*,(yyvsp[-2].TUPLE_DESCRIPTOR)->stride_constraints, install_stride(f,c));
		if ((yyvsp[0].ASTP)) (yyvsp[0].ASTP)->install(f);
		delete (yyvsp[-5].TUPLE_DESCRIPTOR);
		delete (yyvsp[-2].TUPLE_DESCRIPTOR);
		delete (yyvsp[0].ASTP);
		(yyval.RELATION) = r; }
#line 3150 "y.tab.c"
    break;

  case 116: /* builtRelation: tupleDeclaration optionalFormula  */
#line 1001 "../src/parser.y"
                                           {
	        Relation * r = new Relation((yyvsp[-1].TUPLE_DESCRIPTOR)->size);
		resetGlobals();
		F_And *f = r->add_and();
		int i;
		for(i=1;i<=(yyvsp[-1].TUPLE_DESCRIPTOR)->size;i++) {	
			(yyvsp[-1].TUPLE_DESCRIPTOR)->vars[i]->vid = r->set_var(i);
			if (!(yyvsp[-1].TUPLE_DESCRIPTOR)->vars[i]->anonymous) 
				r->name_set_var(i,(yyvsp[-1].TUPLE_DESCRIPTOR)->vars[i]->stripped_name);
			};
                foreach(e,Exp*,(yyvsp[-1].TUPLE_DESCRIPTOR)->eq_constraints, install_eq(f,e,0)); 
		foreach(e,Exp*,(yyvsp[-1].TUPLE_DESCRIPTOR)->geq_constraints, install_geq(f,e,0));
		foreach(c,strideConstraint*,(yyvsp[-1].TUPLE_DESCRIPTOR)->stride_constraints, install_stride(f,c));
		if ((yyvsp[0].ASTP)) (yyvsp[0].ASTP)->install(f);
		delete (yyvsp[-1].TUPLE_DESCRIPTOR);
		delete (yyvsp[0].ASTP);
		(yyval.RELATION) = r; }
#line 3172 "y.tab.c"
    break;

  case 117: /* builtRelation: formula  */
#line 1018 "../src/parser.y"
                  {
		Relation * r = new Relation(0,0);
		F_And *f = r->add_and();
		(yyvsp[0].ASTP)->install(f);
		delete (yyvsp[0].ASTP);
		(yyval.RELATION) = r;
		}
#line 3184 "y.tab.c"
    break;

  case 118: /* optionalFormula: formula_sep formula  */
#line 1027 "../src/parser.y"
                                      { (yyval.ASTP) = (yyvsp[0].ASTP); }
#line 3190 "y.tab.c"
    break;

  case 119: /* optionalFormula: %empty  */
#line 1028 "../src/parser.y"
          {(yyval.ASTP) = 0;}
#line 3196 "y.tab.c"
    break;

  case 123: /* $@6: %empty  */
#line 1037 "../src/parser.y"
        { currentTupleDescriptor = new tupleDescriptor; tuplePos = 1; }
#line 3202 "y.tab.c"
    break;

  case 124: /* tupleDeclaration: $@6 '[' optionalTupleVarList ']'  */
#line 1039 "../src/parser.y"
        {(yyval.TUPLE_DESCRIPTOR) = currentTupleDescriptor; }
#line 3208 "y.tab.c"
    break;

  case 128: /* tupleVar: VAR  */
#line 1049 "../src/parser.y"
        { Declaration_Site *ds = defined((yyvsp[0].VAR_NAME));
	  if (!ds) currentTupleDescriptor->extend((yyvsp[0].VAR_NAME),currentTuple,tuplePos);
	  else {
	      Variable_Ref * v = lookupScalar((yyvsp[0].VAR_NAME));
	      assert(v);
	      if (ds != globalDecls) 
		currentTupleDescriptor->extend((yyvsp[0].VAR_NAME), new Exp(v));
	      else 
		currentTupleDescriptor->extend(new Exp(v));
	      }
	  free((yyvsp[0].VAR_NAME));
	  tuplePos++;
	}
#line 3226 "y.tab.c"
    break;

  case 129: /* tupleVar: '*'  */
#line 1063 "../src/parser.y"
        {currentTupleDescriptor->extend(); tuplePos++; }
#line 3232 "y.tab.c"
    break;

  case 130: /* tupleVar: exp  */
#line 1065 "../src/parser.y"
        {currentTupleDescriptor->extend((yyvsp[0].EXP)); tuplePos++; }
#line 3238 "y.tab.c"
    break;

  case 131: /* tupleVar: exp ':' exp  */
#line 1067 "../src/parser.y"
        {currentTupleDescriptor->extend((yyvsp[-2].EXP),(yyvsp[0].EXP)); tuplePos++; }
#line 3244 "y.tab.c"
    break;

  case 132: /* tupleVar: exp ':' exp ':' INT  */
#line 1069 "../src/parser.y"
        {currentTupleDescriptor->extend((yyvsp[-4].EXP),(yyvsp[-2].EXP),(yyvsp[0].INT_VALUE)); tuplePos++; }
#line 3250 "y.tab.c"
    break;

  case 133: /* varList: varList ',' VAR  */
#line 1073 "../src/parser.y"
                         {(yyval.VAR_LIST) = (yyvsp[-2].VAR_LIST); (yyval.VAR_LIST)->insert((yyvsp[0].VAR_NAME)); }
#line 3256 "y.tab.c"
    break;

  case 134: /* varList: VAR  */
#line 1074 "../src/parser.y"
              { (yyval.VAR_LIST) = new VarList;
		(yyval.VAR_LIST)->insert((yyvsp[0].VAR_NAME)); }
#line 3263 "y.tab.c"
    break;

  case 135: /* varDecl: varList  */
#line 1079 "../src/parser.y"
                {
		(yyval.DECLARATION_SITE) = current_Declaration_Site = new Declaration_Site((yyvsp[0].VAR_LIST));
		foreach(s,char *, *(yyvsp[0].VAR_LIST), delete s);
		delete (yyvsp[0].VAR_LIST);
		}
#line 3273 "y.tab.c"
    break;

  case 136: /* varDeclOptBrackets: varDecl  */
#line 1088 "../src/parser.y"
                                { (yyval.DECLARATION_SITE) = (yyvsp[0].DECLARATION_SITE); }
#line 3279 "y.tab.c"
    break;

  case 137: /* varDeclOptBrackets: '[' varDecl ']'  */
#line 1089 "../src/parser.y"
                                { (yyval.DECLARATION_SITE) = (yyvsp[-1].DECLARATION_SITE); }
#line 3285 "y.tab.c"
    break;

  case 138: /* formula: formula AND formula  */
#line 1092 "../src/parser.y"
                                { (yyval.ASTP) = new AST_And((yyvsp[-2].ASTP),(yyvsp[0].ASTP)); }
#line 3291 "y.tab.c"
    break;

  case 139: /* formula: formula OR formula  */
#line 1093 "../src/parser.y"
                                { (yyval.ASTP) = new AST_Or((yyvsp[-2].ASTP),(yyvsp[0].ASTP)); }
#line 3297 "y.tab.c"
    break;

  case 140: /* formula: constraintChain  */
#line 1094 "../src/parser.y"
                                { (yyval.ASTP) = (yyvsp[0].ASTCP); }
#line 3303 "y.tab.c"
    break;

  case 141: /* formula: '(' formula ')'  */
#line 1095 "../src/parser.y"
                                { (yyval.ASTP) = (yyvsp[-1].ASTP); }
#line 3309 "y.tab.c"
    break;

  case 142: /* formula: NOT formula  */
#line 1096 "../src/parser.y"
                                { (yyval.ASTP) = new AST_Not((yyvsp[0].ASTP)); }
#line 3315 "y.tab.c"
    break;

  case 143: /* formula: start_exists varDeclOptBrackets exists_sep formula end_quant  */
#line 1098 "../src/parser.y"
                                { (yyval.ASTP) = new AST_exists((yyvsp[-3].DECLARATION_SITE),(yyvsp[-1].ASTP)); }
#line 3321 "y.tab.c"
    break;

  case 144: /* formula: start_forall varDeclOptBrackets forall_sep formula end_quant  */
#line 1100 "../src/parser.y"
                                { (yyval.ASTP) = new AST_forall((yyvsp[-3].DECLARATION_SITE),(yyvsp[-1].ASTP)); }
#line 3327 "y.tab.c"
    break;

  case 153: /* end_quant: ')'  */
#line 1120 "../src/parser.y"
        { popScope(); }
#line 3333 "y.tab.c"
    break;

  case 154: /* expList: exp ',' expList  */
#line 1124 "../src/parser.y"
                {
		(yyval.EXP_LIST) = (yyvsp[0].EXP_LIST); 
		(yyval.EXP_LIST)->insert((yyvsp[-2].EXP));
		}
#line 3342 "y.tab.c"
    break;

  case 155: /* expList: exp  */
#line 1128 "../src/parser.y"
              {
		(yyval.EXP_LIST) = new ExpList;
		(yyval.EXP_LIST)->insert((yyvsp[0].EXP));
		}
#line 3351 "y.tab.c"
    break;

  case 156: /* constraintChain: expList REL_OP expList  */
#line 1135 "../src/parser.y"
                        { (yyval.ASTCP) = new AST_constraints((yyvsp[-2].EXP_LIST),(yyvsp[-1].REL_OPERATOR),(yyvsp[0].EXP_LIST)); }
#line 3357 "y.tab.c"
    break;

  case 157: /* constraintChain: expList REL_OP constraintChain  */
#line 1137 "../src/parser.y"
                        { (yyval.ASTCP) = new AST_constraints((yyvsp[-2].EXP_LIST),(yyvsp[-1].REL_OPERATOR),(yyvsp[0].ASTCP)); }
#line 3363 "y.tab.c"
    break;

  case 158: /* simpleExp: VAR  */
#line 1142 "../src/parser.y"
                { Variable_Ref * v = lookupScalar((yyvsp[0].VAR_NAME));
		  if (!v) YYERROR;
		  (yyval.EXP) = new Exp(v); 
		  free((yyvsp[0].VAR_NAME)); 
		  }
#line 3373 "y.tab.c"
    break;

  case 159: /* $@7: %empty  */
#line 1147 "../src/parser.y"
                  {argCount = 1;}
#line 3379 "y.tab.c"
    break;

  case 160: /* simpleExp: VAR '(' $@7 argumentList ')'  */
#line 1148 "../src/parser.y"
                {Variable_Ref *v;
		 if ((yyvsp[-1].ARGUMENT_TUPLE) == Input_Tuple) v = functionOfInput[(yyvsp[-4].VAR_NAME)];
		 else v = functionOfOutput[(yyvsp[-4].VAR_NAME)];
		 if (v == 0) {
			fprintf(stderr,"Function %s(...) not declared\n",(yyvsp[-4].VAR_NAME));
			free((yyvsp[-4].VAR_NAME));
			YYERROR;
			}
		 free((yyvsp[-4].VAR_NAME));
		 (yyval.EXP) = new Exp(v);
		}
#line 3395 "y.tab.c"
    break;

  case 161: /* simpleExp: '(' exp ')'  */
#line 1159 "../src/parser.y"
                       { (yyval.EXP) = (yyvsp[-1].EXP);}
#line 3401 "y.tab.c"
    break;

  case 162: /* argumentList: argumentList ',' VAR  */
#line 1165 "../src/parser.y"
                             {
		Variable_Ref * v = lookupScalar((yyvsp[0].VAR_NAME));
		if (!v) YYERROR;
		 free((yyvsp[0].VAR_NAME));
		 if (v->pos != argCount || v->of != (yyvsp[-2].ARGUMENT_TUPLE) || (v->of != Input_Tuple && v->of != Output_Tuple)) {
			fprintf(stderr,"arguments to function must be prefix of input or output tuple\n");
			YYERROR;
			}
		 (yyval.ARGUMENT_TUPLE) = v->of;
		 argCount++;
		}
#line 3417 "y.tab.c"
    break;

  case 163: /* argumentList: VAR  */
#line 1176 "../src/parser.y"
              { Variable_Ref * v = lookupScalar((yyvsp[0].VAR_NAME));
		if (!v) YYERROR;
		 free((yyvsp[0].VAR_NAME));
		 if (v->pos != argCount || (v->of != Input_Tuple && v->of != Output_Tuple)) {
			fprintf(stderr,"arguments to function must be prefix of input or output tuple\n");
			YYERROR;
			}
		 (yyval.ARGUMENT_TUPLE) = v->of;
		 argCount++;
		}
#line 3432 "y.tab.c"
    break;

  case 164: /* exp: INT  */
#line 1188 "../src/parser.y"
                        {(yyval.EXP) = new Exp((yyvsp[0].INT_VALUE));}
#line 3438 "y.tab.c"
    break;

  case 165: /* exp: INT simpleExp  */
#line 1189 "../src/parser.y"
                                   {(yyval.EXP) = multiply((yyvsp[-1].INT_VALUE),(yyvsp[0].EXP));}
#line 3444 "y.tab.c"
    break;

  case 166: /* exp: simpleExp  */
#line 1190 "../src/parser.y"
                        { (yyval.EXP) = (yyvsp[0].EXP); }
#line 3450 "y.tab.c"
    break;

  case 167: /* exp: '-' exp  */
#line 1191 "../src/parser.y"
                              { (yyval.EXP) = ::negate((yyvsp[0].EXP));}
#line 3456 "y.tab.c"
    break;

  case 168: /* exp: exp '+' exp  */
#line 1192 "../src/parser.y"
                       { (yyval.EXP) = add((yyvsp[-2].EXP),(yyvsp[0].EXP));}
#line 3462 "y.tab.c"
    break;

  case 169: /* exp: exp '-' exp  */
#line 1193 "../src/parser.y"
                       { (yyval.EXP) = subtract((yyvsp[-2].EXP),(yyvsp[0].EXP));}
#line 3468 "y.tab.c"
    break;

  case 170: /* exp: exp '*' exp  */
#line 1194 "../src/parser.y"
                       { (yyval.EXP) = multiply((yyvsp[-2].EXP),(yyvsp[0].EXP));}
#line 3474 "y.tab.c"
    break;

  case 171: /* reachable: REACHABLE_FROM nodeNameList nodeSpecificationList  */
#line 1200 "../src/parser.y"
                {
		  Dynamic_Array1<Relation> *final =
		    Reachable_Nodes(reachable_info);
		  (yyval.RELATION_ARRAY_1D) = final;
		}
#line 3484 "y.tab.c"
    break;

  case 172: /* reachable_of: REACHABLE_OF VAR IN nodeNameList nodeSpecificationList  */
#line 1209 "../src/parser.y"
                {
		  Dynamic_Array1<Relation> *final =
		    Reachable_Nodes(reachable_info);
		  int index = reachable_info->node_names.index(String((yyvsp[-3].VAR_NAME)));
		  assert(index != 0 && "No such node");
		  (yyval.RELATION) = new Relation; 
		  *(yyval.RELATION) = (*final)[index];
		  delete final;
		  delete reachable_info;
		  delete (yyvsp[-3].VAR_NAME);
		}
#line 3500 "y.tab.c"
    break;

  case 173: /* nodeNameList: '(' realNodeNameList ')'  */
#line 1224 "../src/parser.y"
              { int sz = reachable_info->node_names.size();
		reachable_info->node_arity.reallocate(sz);
	  	reachable_info->transitions.resize(sz+1,sz+1);
	  	reachable_info->start_nodes.resize(sz+1);
	      }
#line 3510 "y.tab.c"
    break;

  case 174: /* realNodeNameList: realNodeNameList ',' VAR  */
#line 1232 "../src/parser.y"
              { reachable_info->node_names.append(String((yyvsp[0].VAR_NAME)));
		delete (yyvsp[0].VAR_NAME); }
#line 3517 "y.tab.c"
    break;

  case 175: /* realNodeNameList: VAR  */
#line 1234 "../src/parser.y"
              { reachable_info = new reachable_information;
		reachable_info->node_names.append(String((yyvsp[0].VAR_NAME)));
		delete (yyvsp[0].VAR_NAME); }
#line 3525 "y.tab.c"
    break;

  case 176: /* nodeSpecificationList: OPEN_BRACE realNodeSpecificationList CLOSE_BRACE  */
#line 1241 "../src/parser.y"
        {  
	   int i,j;
	   int n_nodes = reachable_info->node_names.size();
	   Tuple<int> &arity = reachable_info->node_arity;
	   Dynamic_Array2<Relation> &transitions = reachable_info->transitions;

           /* fixup unspecified transitions to be false */
	   /* find arity */
	   for(i = 1; i <= n_nodes; i++) arity[i] = -1;
	   for(i = 1; i <= n_nodes; i++)
	     for(j = 1; j <= n_nodes; j++)
		if(! transitions[i][j].is_null()) {
		  int in_arity = transitions[i][j].n_inp();
		  int out_arity = transitions[i][j].n_out();
		  if(arity[i] < 0) arity[i] = in_arity;
		  if(arity[j] < 0) arity[j] = out_arity;
		  if(in_arity != arity[i] || out_arity != arity[j]) {
		    fprintf(stderr,
			    "Arity mismatch in node transition: %s -> %s",
			    (const char *) reachable_info->node_names[i],
			    (const char *) reachable_info->node_names[j]);
			assert(0);
		    YYERROR;
		  }
		}
	   for(i = 1; i <= n_nodes; i++) 
	     if(arity[i] < 0) arity[i] = 0;
	   /* Fill in false relations */
	   for(i = 1; i <= n_nodes; i++)
	     for(j = 1; j <= n_nodes; j++)
		if(transitions[i][j].is_null())
		  transitions[i][j] = Relation::False(arity[i],arity[j]);


          /* fixup unused start node positions */
	   Dynamic_Array1<Relation> &nodes = reachable_info->start_nodes;
	   for(i = 1; i <= n_nodes; i++) 
	     if(nodes[i].is_null()) 
		nodes[i] = Relation::False(arity[i]);
	     else
		if(nodes[i].n_set() != arity[i]){
		    fprintf(stderr,"Arity mismatch in start node %s",
			    (const char *) reachable_info->node_names[i]);
		assert(0);
		    YYERROR;
		}
 	}
#line 3577 "y.tab.c"
    break;

  case 177: /* realNodeSpecificationList: realNodeSpecificationList ',' VAR ':' relation  */
#line 1292 "../src/parser.y"
          {  int n_nodes = reachable_info->node_names.size();
	     int index = reachable_info->node_names.index((yyvsp[-2].VAR_NAME));
	     assert(index != 0 && index <= n_nodes);
	     reachable_info->start_nodes[index] = *(yyvsp[0].RELATION);
	     delete (yyvsp[-2].VAR_NAME);
	     delete (yyvsp[0].RELATION);
	  }
#line 3589 "y.tab.c"
    break;

  case 178: /* realNodeSpecificationList: realNodeSpecificationList ',' VAR GOES_TO VAR ':' relation  */
#line 1300 "../src/parser.y"
          {  int n_nodes = reachable_info->node_names.size();
	     int from_index = reachable_info->node_names.index((yyvsp[-4].VAR_NAME));
	     int   to_index = reachable_info->node_names.index((yyvsp[-2].VAR_NAME));
	     assert(from_index != 0 && to_index != 0);
	     assert(from_index <= n_nodes && to_index <= n_nodes);
	     reachable_info->transitions[from_index][to_index] = *(yyvsp[0].RELATION);
	     delete (yyvsp[-4].VAR_NAME);
	     delete (yyvsp[-2].VAR_NAME);
	     delete (yyvsp[0].RELATION);
	  }
#line 3604 "y.tab.c"
    break;

  case 179: /* realNodeSpecificationList: VAR GOES_TO VAR ':' relation  */
#line 1311 "../src/parser.y"
          {  int n_nodes = reachable_info->node_names.size();
	     int from_index = reachable_info->node_names.index((yyvsp[-4].VAR_NAME));
	     int   to_index = reachable_info->node_names.index((yyvsp[-2].VAR_NAME));
	     assert(from_index != 0 && to_index != 0);
	     assert(from_index <= n_nodes && to_index <= n_nodes);
	     reachable_info->transitions[from_index][to_index] = *(yyvsp[0].RELATION);
	     delete (yyvsp[-4].VAR_NAME);
	     delete (yyvsp[-2].VAR_NAME);
	     delete (yyvsp[0].RELATION);
	  }
#line 3619 "y.tab.c"
    break;

  case 180: /* realNodeSpecificationList: VAR ':' relation  */
#line 1322 "../src/parser.y"
          {  int n_nodes = reachable_info->node_names.size();
	     int index = reachable_info->node_names.index((yyvsp[-2].VAR_NAME));
	     assert(index != 0 && index <= n_nodes);
	     reachable_info->start_nodes[index] = *(yyvsp[0].RELATION);
	     delete (yyvsp[-2].VAR_NAME);
	     delete (yyvsp[0].RELATION);
	  }
#line 3631 "y.tab.c"
    break;


#line 3635 "y.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 1331 "../src/parser.y"


extern FILE *yyin;

#if ! defined(OMIT_GETRUSAGE)
#ifdef __sparc__
extern "C" int getrusage (int, struct rusage*);
#endif


namespace omega {

#if !defined(OMIT_GETRUSAGE)
#include <sys/types.h>
#include <sys/time.h>
#include <sys/resource.h>

struct rusage start_time;
#endif

#if defined BRAIN_DAMAGED_FREE
void free(void *p)
    {
    free((char *)p);
    }

void *realloc(void *p, size_t s)
    {
    return realloc((malloc_t) p, s);
    }
#endif

void start_clock( void )
    {
    getrusage(RUSAGE_SELF, &start_time);
    }

int clock_diff( void )
    {
    struct rusage current_time;
    getrusage(RUSAGE_SELF, &current_time);
    return (current_time.ru_utime.tv_sec -start_time.ru_utime.tv_sec)*1000000 +
           (current_time.ru_utime.tv_usec-start_time.ru_utime.tv_usec);
    }
#endif

void printUsage(FILE *outf, char **argv) {
    fprintf(outf, "usage: %s {-R} {-D[facility][level]...} infile\n  -R means skip redundant conjunct elimination\n  -D sets debugging level as follows:\n    a = all debugging flags\n    g = code generation\n    l = calculator\n    c = omega core\n    p = presburger functions\n    r = relational operators\n    t = transitive closure\nAll debugging output goes to %s\n",argv[0],DEBUG_FILE_NAME);
}

int omega_calc_debug;

} // end namespace omega

int main(int argc, char **argv){
  redundant_conj_level = 2;
  current_Declaration_Site = globalDecls = new Global_Declaration_Site();
#if YYDEBUG != 0
  yydebug  = 1;
#endif
  int i;
  char * fileName = 0;

  printf("# %s (based on %s, %s):\n",CALC_VERSION_STRING, Omega_Library_Version, Omega_Library_Date);

  calc_all_debugging_off();

#ifdef SPEED
  DebugFile = fopen("/dev/null","w");
  assert(DebugFile);
#else
  DebugFile = fopen(DEBUG_FILE_NAME, "w");
  if (!DebugFile) {
    fprintf(stderr, "Can't open debug file %s\n", DEBUG_FILE_NAME);
    DebugFile = stderr;
  }
  setbuf(DebugFile,0);
#endif

  closure_presburger_debug = 0;

  setOutputFile(DebugFile);

  // Process flags
  for(i=1; i<argc; i++) {
    if(argv[i][0] == '-') {
      int j = 1, c;
      while((c=argv[i][j++]) != 0) {
	switch(c) {
	case 'D':
	    if (! process_calc_debugging_flags(argv[i],j)) {
		printUsage(stderr,argv);
		Exit(1);
	    }
	    break;
	case 'G':
	    { 
	      fprintf(stderr,"Note: specifying number of GEQ's is no longer useful.\n");
	      while(argv[i][j] != 0) j++;
	    }
	    break;
	case 'E':
	    {
	      fprintf(stderr,"Note: specifying number of EQ's is no longer useful.\n");
	      while(argv[i][j] != 0) j++;
	    }
	    break;
	case 'R':
	    redundant_conj_level = 1;
	    break;
        // Other future options go here
	default:
	  fprintf(stderr, "\nUnknown flag -%c\n", c);
	  printUsage(stderr,argv);
	  Exit(1);
	}
      }
    } 
   else {
     // Make sure this is a file name
     if (fileName) {
	fprintf(stderr,"\nCan only handle a single input file\n");
	printUsage(stderr,argv);
	Exit(1);
	};
     fileName = argv[i];
     yyin = fopen(fileName, "r");
     if (!yyin) {
	    fprintf(stderr, "\nCan't open input file %s\n",fileName);
	    printUsage(stderr,argv);
	    Exit(1);
	    };
     }
   }


  initializeOmega();
  initializeScanBuffer();

  yyparse();

  delete globalDecls;
  foreach_map(cs,Const_String,r,Relation *,relationMap,
	      {delete r; relationMap[cs]=0;});

  return(0);
} /* end main */

namespace omega {

Relation LexForward(int n) {
  Relation r(n,n);
  F_Or *f = r.add_or();
  for (int i=1; i <= n; i++) {
	F_And *g = f->add_and();
	for(int j=1;j<i;j++) {
	   EQ_Handle e = g->add_EQ();
	   e.update_coef(r.input_var(j),-1);
	   e.update_coef(r.output_var(j),1);
	   e.finalize();
	   }
	GEQ_Handle e = g->add_GEQ();
	e.update_coef(r.input_var(i),-1);
	e.update_coef(r.output_var(i),1);
	e.update_const(-1);
	e.finalize();
	}
  r.finalize();
  return r;
  }

} // end of namespace omega

