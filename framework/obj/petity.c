/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 4 "../src/petity.y" /* yacc.c:339  */

#include <string.h>
#include <stdlib.h>
#include <basic/assert.h>
#include <basic/Exit.h>
#include <petit/lang-interf.h>
#include <petit/make.h>
#include <petit/tree.h>
#include <petit/vutil.h>
#include <petit/petity.h>
#include "../obj/petity.h"   /* Bison-generated file with tokens, *** NOT *** our unfortunately-named ../include/petit/petity.h */

#ifdef WIN32
#include <io.h>
#define isatty _isatty
#include <malloc.h>
#define alloca _alloca
#endif

#define AllowComments 1

namespace omega {

static void parse_die();
static int parse_intval();
static void parse_linknode( node *new_node );
static void parse_unlinknode();
static void parse_linknodeto( node *old, node *new_node );
static void parse_pushscope( node *n );
static void parse_popscope();
static node *parse_binaryop( node *left, optype op, node *right );
static void parse_forloop(optype op, symtabentry *index,
			       node *lower, node *upper, node *inc);
static void parse_endforloop();

static void parse_stmt_index( node *n );
static void parse_check_stmt_number();
static void parse_init();
static void yyerror( char *s);
symtabentry *add_symbol(const char *name, int new_int,
			symboltype symtype, exprtype exptype,
			nametabentry *onam);
static void CheckEnd();
static symtabentry *parse_doid_symbol();

/* global variables: */
/* line number */
unsigned long int Lines;

/* Entry node */
node *Entry;

/* Exit node */
node *ExitNode;

/* List of assertions */
node *Assertions = NULL;

/* Current head of name table */
nametabentry *NameHead;

/* communication from lexer */
/* name of ID */
char P_IDname[MAXIDLENGTH], P_INTname[MAXIDLENGTH];

/* line number of next token */
unsigned long int P_Lines;
} // end of namespace omega

#ifdef WIN32
#include <io.h>
#define isatty _isatty
#endif
#include "petit/petitl.c"

namespace omega {
/* current nest level in loops */
unsigned long int P_LoopNest;

#include <petit/ddutil.h>
char *loopsyms[maxnest];

/* current statement number */
unsigned long int P_StmtNumber;

/* A node pointer */
node *P_Node;

/* A symbol table entry pointer */
symtabentry *P_Sym, *P_Sym1, *P_DeclSym;

/* type of symbol being declared */
symboltype P_SaveType;

var_class SaveClass;

/* What to use for 'prev' of next node, 'parent' of next node */
node *P_NextPrev, *P_NextParent;

/* To allow undeclared variables appear in array bounds */
int NoNewOldCheck = 0;

/* to prohibit RETURN statements from appearing not at the end */
int ShouldBeEnd;

} // end of namespace omega

using namespace omega;

/* end of declarations section */

#line 178 "petity.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "petity.h".  */
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
#line 116 "../src/petity.y" /* yacc.c:355  */

    int iv;
    node *np;
    symtabentry *stp;
    optype op;
    

#line 356 "petity.c" /* yacc.c:355  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PETITY_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 371 "petity.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

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

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
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


#if ! defined yyoverflow || YYERROR_VERBOSE

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
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
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
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
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
#define YYLAST   532

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  66
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  58
/* YYNRULES -- Number of rules.  */
#define YYNRULES  140
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  264

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   320

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
      65
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   172,   172,   172,   186,   188,   191,   192,   193,   194,
     195,   196,   197,   198,   199,   200,   201,   202,   203,   206,
     207,   210,   223,   239,   262,   290,   291,   292,   293,   298,
     326,   325,   373,   377,   379,   383,   400,   399,   405,   404,
     410,   409,   416,   417,   423,   422,   434,   433,   445,   444,
     455,   457,   459,   463,   465,   467,   472,   471,   495,   494,
     501,   504,   504,   507,   508,   509,   510,   511,   512,   513,
     514,   515,   516,   519,   520,   525,   527,   532,   531,   558,
     569,   569,   570,   557,   597,   598,   599,   602,   603,   605,
     610,   611,   612,   616,   631,   647,   652,   657,   668,   671,
     674,   677,   680,   683,   686,   691,   696,   714,   713,   754,
     762,   771,   774,   777,   780,   783,   786,   789,   792,   795,
     798,   801,   804,   807,   810,   813,   816,   819,   822,   825,
     828,   831,   834,   839,   844,   850,   849,   872,   875,   880,
     883
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "TCOMMENT", "TASSERT", "TBY", "TCEILING",
  "TCOLON", "TCOMMA", "TCONST", "TDO", "TDOANY", "TELSE", "TENDFOR",
  "TENDIF", "TEQ", "TEQUAL", "TEXP", "TFLOAT", "TFLOOR", "TFOR", "TGE",
  "TGT", "TRAND", "TID", "TIF", "TINT", "TINTEGER", "TLE", "TLT", "TLP",
  "TMAX", "TMIN", "TMINUS", "TMOD", "TNE", "TAND", "TOR", "TNOT",
  "TPARFOR", "TPLUS", "TREAL", "TRP", "TSEMI", "TSLASH", "TSQRT", "TSTAR",
  "TTHEN", "TTO", "TVECFOR", "TLCB", "TRCB", "TFORMAL", "TCOMMON",
  "TSTATIC", "TAUTO", "TPRIVATE", "TBUILTIN", "TIN", "TOUT", "TINOUT",
  "TRETURN", "TPLUSEQUAL", "TSTAREQUAL", "TMAXEQUAL", "TMINEQUAL",
  "$accept", "pgm", "$@1", "stlist", "stmt", "streturn", "stassert",
  "stcomment", "stasgn", "stasgnoper", "asgnoper", "lhs", "@2", "stconst",
  "constlist", "constdecl", "stfor", "$@3", "$@4", "$@5", "optforby",
  "stforall", "$@6", "stparfor", "$@7", "stdoany", "$@8", "forto", "forby",
  "stif", "$@9", "elsepart", "$@10", "stdecl", "$@11", "class", "type",
  "decllist", "decl", "$@12", "$@13", "$@14", "$@15", "$@16", "init",
  "initlist", "init1", "boundlist", "bound", "newid", "doid", "cexpr",
  "oldid", "expr", "$@17", "$@18", "assocop", "list", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320
};
# endif

#define YYPACT_NINF -177

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-177)))

#define YYTABLE_NINF -108

#define yytable_value_is_error(Yytable_value) \
  (!!((Yytable_value) == (-108)))

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -177,    11,   128,  -177,  -177,   -12,    -1,    38,    38,    38,
      39,    95,    38,    38,  -177,  -177,  -177,  -177,  -177,  -177,
    -177,  -177,  -177,    95,    31,  -177,  -177,  -177,  -177,  -177,
    -177,   -10,  -177,  -177,  -177,  -177,  -177,  -177,  -177,   -13,
      95,  -177,    73,  -177,    88,  -177,    94,   104,   108,   100,
     106,  -177,   115,   119,  -177,  -177,    95,  -177,  -177,    95,
      95,    95,   124,   127,   358,  -177,   126,   147,   358,   128,
      95,  -177,  -177,  -177,  -177,    95,  -177,  -177,  -177,   280,
      -1,   174,    95,    95,    95,    95,    95,    95,   130,   306,
     112,   462,   112,    95,   144,    95,    95,    95,    95,    95,
      95,    95,    95,    95,    95,    95,    95,    95,    95,    95,
      95,   131,   164,    95,    95,  -177,   358,   358,    -1,  -177,
    -177,  -177,  -177,   174,   174,   174,   101,   188,   188,   188,
     358,    -5,   384,   410,  -177,  -177,   332,    95,   483,   180,
     483,   483,   483,   483,    -8,    -8,   112,    83,   483,   462,
     436,   112,    46,    46,   128,    95,   188,   188,   194,  -177,
     176,   133,   166,   166,   174,   174,   174,  -177,  -177,  -177,
      95,    95,    95,    95,  -177,    95,    95,  -177,     0,    -7,
       2,    95,    95,    -1,   197,   185,  -177,   166,   166,  -177,
     222,   222,   222,   358,   159,   490,  -177,  -177,   204,  -177,
     222,   222,  -177,     1,  -177,  -177,  -177,  -177,  -177,   183,
      95,  -177,  -177,  -177,  -177,   128,  -177,  -177,  -177,    95,
    -177,   358,    95,  -177,   190,   358,   228,   231,    31,   232,
     235,    -4,  -177,   238,  -177,   254,   128,   128,   128,   128,
     128,   128,    95,  -177,    95,   205,    95,  -177,   -30,    17,
      22,    25,    27,  -177,  -177,  -177,   358,  -177,  -177,  -177,
    -177,  -177,   197,  -177
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     6,     1,    22,     0,     0,     0,     0,     0,
      29,     0,     0,     0,    67,    65,    66,    64,    71,    72,
      68,    69,    70,    19,     3,     4,    18,     7,     8,     9,
      10,     0,    11,    12,    13,    15,    16,    14,    17,     0,
       0,    95,    32,    33,     0,    96,     0,     0,     0,     0,
       0,   110,     0,     0,   105,   109,     0,   137,   138,     0,
       0,     0,     0,   106,    56,   135,     0,     0,    20,     6,
       0,    25,    26,    27,    28,     0,    73,    74,    61,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     115,   127,   114,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     5,    23,    24,     0,    21,
      34,    97,    98,     0,     0,     0,    35,     0,     0,     0,
     139,     0,     0,     0,   132,   111,     0,     0,   121,   118,
     123,   124,   120,   119,   129,   130,   113,   128,   122,   125,
     126,   112,   117,   116,     6,     0,     0,     0,    62,    75,
      77,     0,   101,   102,     0,     0,     0,    52,    51,    50,
       0,     0,     0,     0,    31,     0,     0,   131,     0,    60,
       0,     0,     0,     0,    84,     0,   104,   100,    99,   103,
      42,    42,    42,   140,   117,   117,   108,    58,     0,   136,
      42,    42,    76,     0,    78,    80,    53,    55,    54,    38,
       0,    48,    40,   134,   133,     6,    57,    46,    44,     0,
      85,    89,    90,    36,     0,    43,     0,     0,    59,     0,
       0,     0,    87,    81,    91,    93,     6,     6,     6,     6,
       6,     6,     0,    86,     0,     0,     0,    37,     0,     0,
       0,     0,     0,    88,    92,    82,    94,    39,    49,    41,
      47,    45,    84,    83
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -177,  -177,  -177,  -132,   -68,  -177,  -177,  -177,  -177,  -177,
    -177,  -177,  -177,  -177,  -177,   168,  -177,  -177,  -177,  -177,
      72,  -177,  -177,  -177,  -177,  -177,  -177,    -6,  -177,  -177,
    -177,  -177,  -177,  -177,  -177,  -177,  -177,  -177,    66,  -177,
    -177,  -177,  -177,  -177,    -2,  -177,  -176,  -177,     8,  -116,
     103,  -108,  -177,   -11,  -177,  -177,  -177,   -76
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,    24,    25,    26,    27,    28,    29,    30,
      75,    31,    49,    32,    42,    43,    33,   236,   224,   227,
     209,    34,   230,    35,   229,    36,   226,   170,   210,    37,
     111,   198,   215,    38,   118,    39,    78,   158,   159,   184,
     185,   222,   245,   262,   204,   231,   220,   233,   234,    44,
      46,   126,    63,   130,    94,   112,    65,   131
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      64,   115,   160,   173,   242,   197,    70,    50,   173,    96,
     173,     3,    68,    69,    76,   161,   162,   163,    40,    51,
      52,   257,   179,    41,    53,    54,   104,    55,    77,    79,
     258,    56,    57,    58,    59,   259,    69,   174,   260,    60,
     261,    61,   196,   232,   199,    89,    62,   243,    90,    91,
      92,   219,    71,    72,    73,    74,   187,   188,   189,   116,
      69,   178,    45,    96,   117,    69,   253,   160,    69,   -30,
      69,   127,   128,   129,    69,   132,   133,   101,   102,   180,
     104,    80,   136,   228,   138,   139,   140,   141,   142,   143,
     144,   145,   146,   147,   148,   149,   150,   151,   152,   153,
      96,    50,   156,   157,    81,   248,   249,   250,   251,   252,
      82,    47,    48,    51,    52,    66,    67,  -108,    53,    54,
      83,    55,   171,   172,    84,    56,    57,    58,    59,    96,
      85,     4,     5,    60,   164,    61,    86,     6,     7,     8,
      62,   165,   113,   101,   102,    87,   104,   166,     9,    88,
     181,   182,    10,    11,    93,   -63,   109,  -107,   110,   190,
     191,   192,   193,   114,   194,   195,   164,    12,   247,   -63,
     200,   201,   134,   165,   137,   186,    96,    13,   154,   166,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
     101,   102,   221,   104,   155,   167,   168,    96,   121,   225,
     122,   213,   183,    95,   123,    96,   -79,   124,   221,    97,
      98,   235,   166,   203,   125,   205,    99,   100,   216,   101,
     102,   103,   104,   105,   106,   107,   223,   206,   108,   207,
     208,   221,   109,   235,   110,   256,   169,    95,   238,    96,
     237,   239,   240,    97,    98,   241,   244,   255,   120,   202,
      99,   100,   254,   101,   102,   103,   104,   105,   106,   107,
     263,   246,   108,   211,   212,     0,   109,     0,   110,    95,
       0,    96,   217,   218,     0,    97,    98,     0,     0,     0,
       0,     0,    99,   100,     0,   101,   102,   103,   104,   105,
     106,   107,     0,     0,   108,    95,     0,    96,   109,     0,
     110,    97,    98,     0,     0,     0,     0,     0,    99,   100,
       0,   101,   102,   103,   104,   105,   106,   107,     0,     0,
     108,    95,   119,    96,   109,     0,   110,    97,    98,     0,
       0,     0,     0,     0,    99,   100,     0,   101,   102,   103,
     104,   105,   106,   107,     0,     0,   108,    95,   135,    96,
     109,     0,   110,    97,    98,     0,     0,     0,     0,     0,
      99,   100,     0,   101,   102,   103,   104,   105,   106,   107,
       0,     0,   108,    95,   177,    96,   109,     0,   110,    97,
      98,     0,     0,     0,     0,     0,    99,   100,     0,   101,
     102,   103,   104,   105,   106,   107,     0,     0,   108,    95,
       0,    96,   109,     0,   110,    97,    98,     0,     0,     0,
       0,     0,    99,   100,     0,   101,   102,   103,   104,   105,
     106,   107,     0,     0,   108,    95,     0,    96,   175,     0,
     110,    97,    98,     0,     0,     0,     0,     0,    99,   100,
       0,   101,   102,   103,   104,   105,   106,   107,     0,     0,
     108,    95,     0,    96,   176,     0,   110,    97,    98,     0,
       0,     0,     0,     0,    99,   100,     0,   101,   102,   103,
     104,   105,   106,     0,     0,     0,   108,    95,     0,    96,
     109,     0,   110,    97,    98,     0,     0,     0,     0,     0,
      99,   100,     0,   101,   102,   103,   104,   105,  -108,     0,
      96,     0,   108,     0,  -108,  -108,   109,    96,   110,     0,
       0,  -108,  -108,     0,   101,   102,   103,   104,  -108,     0,
       0,   101,   102,   108,   104,     0,     0,   109,     0,   110,
       0,     0,   214
};

static const yytype_int16 yycheck[] =
{
      11,    69,   118,     8,     8,    12,    16,     6,     8,    17,
       8,     0,    23,    43,    27,   123,   124,   125,    30,    18,
      19,    51,   154,    24,    23,    24,    34,    26,    41,    40,
      13,    30,    31,    32,    33,    13,    43,    42,    13,    38,
      13,    40,    42,   219,    42,    56,    45,    51,    59,    60,
      61,    50,    62,    63,    64,    65,   164,   165,   166,    70,
      43,   137,    24,    17,    75,    43,   242,   183,    43,    30,
      43,    82,    83,    84,    43,    86,    87,    31,    32,   155,
      34,     8,    93,   215,    95,    96,    97,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
      17,     6,   113,   114,    16,   237,   238,   239,   240,   241,
      16,     8,     9,    18,    19,    12,    13,    34,    23,    24,
      16,    26,   128,   129,    16,    30,    31,    32,    33,    17,
      30,     3,     4,    38,    33,    40,    30,     9,    10,    11,
      45,    40,    16,    31,    32,    30,    34,    46,    20,    30,
     156,   157,    24,    25,    30,    27,    44,    30,    46,   170,
     171,   172,   173,    16,   175,   176,    33,    39,   236,    41,
     181,   182,    42,    40,    30,    42,    17,    49,    47,    46,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      31,    32,   203,    34,    30,     7,     8,    17,    24,   210,
      26,    42,     8,    15,    30,    17,    30,    33,   219,    21,
      22,   222,    46,    16,    40,    30,    28,    29,    14,    31,
      32,    33,    34,    35,    36,    37,    43,     5,    40,     7,
       8,   242,    44,   244,    46,   246,    48,    15,    10,    17,
      50,    10,    10,    21,    22,    10,     8,    42,    80,   183,
      28,    29,   244,    31,    32,    33,    34,    35,    36,    37,
     262,     7,    40,   191,   192,    -1,    44,    -1,    46,    15,
      -1,    17,   200,   201,    -1,    21,    22,    -1,    -1,    -1,
      -1,    -1,    28,    29,    -1,    31,    32,    33,    34,    35,
      36,    37,    -1,    -1,    40,    15,    -1,    17,    44,    -1,
      46,    21,    22,    -1,    -1,    -1,    -1,    -1,    28,    29,
      -1,    31,    32,    33,    34,    35,    36,    37,    -1,    -1,
      40,    15,    42,    17,    44,    -1,    46,    21,    22,    -1,
      -1,    -1,    -1,    -1,    28,    29,    -1,    31,    32,    33,
      34,    35,    36,    37,    -1,    -1,    40,    15,    42,    17,
      44,    -1,    46,    21,    22,    -1,    -1,    -1,    -1,    -1,
      28,    29,    -1,    31,    32,    33,    34,    35,    36,    37,
      -1,    -1,    40,    15,    42,    17,    44,    -1,    46,    21,
      22,    -1,    -1,    -1,    -1,    -1,    28,    29,    -1,    31,
      32,    33,    34,    35,    36,    37,    -1,    -1,    40,    15,
      -1,    17,    44,    -1,    46,    21,    22,    -1,    -1,    -1,
      -1,    -1,    28,    29,    -1,    31,    32,    33,    34,    35,
      36,    37,    -1,    -1,    40,    15,    -1,    17,    44,    -1,
      46,    21,    22,    -1,    -1,    -1,    -1,    -1,    28,    29,
      -1,    31,    32,    33,    34,    35,    36,    37,    -1,    -1,
      40,    15,    -1,    17,    44,    -1,    46,    21,    22,    -1,
      -1,    -1,    -1,    -1,    28,    29,    -1,    31,    32,    33,
      34,    35,    36,    -1,    -1,    -1,    40,    15,    -1,    17,
      44,    -1,    46,    21,    22,    -1,    -1,    -1,    -1,    -1,
      28,    29,    -1,    31,    32,    33,    34,    35,    15,    -1,
      17,    -1,    40,    -1,    21,    22,    44,    17,    46,    -1,
      -1,    28,    29,    -1,    31,    32,    33,    34,    35,    -1,
      -1,    31,    32,    40,    34,    -1,    -1,    44,    -1,    46,
      -1,    -1,    42
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    67,    68,     0,     3,     4,     9,    10,    11,    20,
      24,    25,    39,    49,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    69,    70,    71,    72,    73,    74,
      75,    77,    79,    82,    87,    89,    91,    95,    99,   101,
      30,    24,    80,    81,   115,    24,   116,   116,   116,    78,
       6,    18,    19,    23,    24,    26,    30,    31,    32,    33,
      38,    40,    45,   118,   119,   122,   116,   116,   119,    43,
      16,    62,    63,    64,    65,    76,    27,    41,   102,   119,
       8,    16,    16,    16,    16,    30,    30,    30,    30,   119,
     119,   119,   119,    30,   120,    15,    17,    21,    22,    28,
      29,    31,    32,    33,    34,    35,    36,    37,    40,    44,
      46,    96,   121,    16,    16,    70,   119,   119,   100,    42,
      81,    24,    26,    30,    33,    40,   117,   119,   119,   119,
     119,   123,   119,   119,    42,    42,   119,    30,   119,   119,
     119,   119,   119,   119,   119,   119,   119,   119,   119,   119,
     119,   119,   119,   119,    47,    30,   119,   119,   103,   104,
     115,   117,   117,   117,    33,    40,    46,     7,     8,    48,
      93,    93,    93,     8,    42,    44,    44,    42,   123,    69,
     123,    93,    93,     8,   105,   106,    42,   117,   117,   117,
     119,   119,   119,   119,   119,   119,    42,    12,    97,    42,
     119,   119,   104,    16,   110,    30,     5,     7,     8,    86,
      94,    86,    86,    42,    42,    98,    14,    86,    86,    50,
     112,   119,   107,    43,    84,   119,    92,    85,    69,    90,
      88,   111,   112,   113,   114,   119,    83,    50,    10,    10,
      10,    10,     8,    51,     8,   108,     7,    70,    69,    69,
      69,    69,    69,   112,   114,    42,   119,    51,    13,    13,
      13,    13,   109,   110
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    66,    68,    67,    69,    69,    70,    70,    70,    70,
      70,    70,    70,    70,    70,    70,    70,    70,    70,    71,
      71,    72,    73,    74,    75,    76,    76,    76,    76,    77,
      78,    77,    79,    80,    80,    81,    83,    82,    84,    82,
      85,    82,    86,    86,    88,    87,    90,    89,    92,    91,
      93,    93,    93,    94,    94,    94,    96,    95,    98,    97,
      97,   100,    99,   101,   101,   101,   101,   101,   101,   101,
     101,   101,   101,   102,   102,   103,   103,   105,   104,   106,
     107,   108,   109,   104,   110,   110,   110,   111,   111,   112,
     113,   113,   113,   114,   114,   115,   116,   117,   117,   117,
     117,   117,   117,   117,   117,   118,   119,   120,   119,   119,
     119,   119,   119,   119,   119,   119,   119,   119,   119,   119,
     119,   119,   119,   119,   119,   119,   119,   119,   119,   119,
     119,   119,   119,   119,   119,   121,   119,   122,   122,   123,
     123
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     2,     1,     3,     0,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       2,     4,     1,     3,     3,     1,     1,     1,     1,     1,
       0,     5,     2,     1,     3,     3,     0,    10,     0,    11,
       0,    11,     0,     2,     0,    11,     0,    11,     0,    11,
       1,     1,     1,     1,     1,     1,     0,     7,     0,     3,
       0,     0,     4,     0,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     0,     3,     0,
       0,     0,     0,     9,     0,     2,     4,     1,     3,     1,
       0,     1,     3,     1,     3,     1,     1,     1,     1,     3,
       3,     2,     2,     3,     3,     1,     1,     0,     5,     1,
       1,     3,     3,     3,     2,     2,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     2,     3,     3,
       3,     4,     3,     6,     6,     0,     5,     1,     1,     1,
       3
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
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

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



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

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
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
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
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


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
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
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
| yyreduce -- Do a reduction.  |
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
        case 2:
#line 172 "../src/petity.y" /* yacc.c:1646  */
    {
	  parse_init();
	  ShouldBeEnd = 0;
	}
#line 1703 "petity.c" /* yacc.c:1646  */
    break;

  case 3:
#line 177 "../src/petity.y" /* yacc.c:1646  */
    {
	  P_Node = make_node(op_exit);
	  ExitNode = P_Node;
	  parse_linknode(P_Node);
	}
#line 1713 "petity.c" /* yacc.c:1646  */
    break;

  case 9:
#line 194 "../src/petity.y" /* yacc.c:1646  */
    {CheckEnd();}
#line 1719 "petity.c" /* yacc.c:1646  */
    break;

  case 10:
#line 195 "../src/petity.y" /* yacc.c:1646  */
    {CheckEnd();}
#line 1725 "petity.c" /* yacc.c:1646  */
    break;

  case 12:
#line 197 "../src/petity.y" /* yacc.c:1646  */
    {CheckEnd();}
#line 1731 "petity.c" /* yacc.c:1646  */
    break;

  case 13:
#line 198 "../src/petity.y" /* yacc.c:1646  */
    {CheckEnd();}
#line 1737 "petity.c" /* yacc.c:1646  */
    break;

  case 14:
#line 199 "../src/petity.y" /* yacc.c:1646  */
    {CheckEnd();}
#line 1743 "petity.c" /* yacc.c:1646  */
    break;

  case 15:
#line 200 "../src/petity.y" /* yacc.c:1646  */
    {CheckEnd();}
#line 1749 "petity.c" /* yacc.c:1646  */
    break;

  case 16:
#line 201 "../src/petity.y" /* yacc.c:1646  */
    {CheckEnd();}
#line 1755 "petity.c" /* yacc.c:1646  */
    break;

  case 18:
#line 203 "../src/petity.y" /* yacc.c:1646  */
    {ShouldBeEnd=1;}
#line 1761 "petity.c" /* yacc.c:1646  */
    break;

  case 19:
#line 206 "../src/petity.y" /* yacc.c:1646  */
    {}
#line 1767 "petity.c" /* yacc.c:1646  */
    break;

  case 20:
#line 207 "../src/petity.y" /* yacc.c:1646  */
    {free_node((yyvsp[0].np));}
#line 1773 "petity.c" /* yacc.c:1646  */
    break;

  case 21:
#line 211 "../src/petity.y" /* yacc.c:1646  */
    {
		    parse_check_stmt_number();   /* what the heck... */
		    P_Node = make_node( op_assert );
		    P_Node->nodelink = Assertions;
		    Assertions = P_Node;
		    parse_linknode( P_Node );
		    parse_pushscope( P_Node );
		    parse_linknode( (yyvsp[-1].np) );
		    parse_popscope();
		}
#line 1788 "petity.c" /* yacc.c:1646  */
    break;

  case 22:
#line 223 "../src/petity.y" /* yacc.c:1646  */
    {
                if(1) {
		    P_Sym = parse_symbol(-1);
		    P_Node = make_node( op_comment );
		    P_Node->nodevalue = (unsigned long int)P_Sym;
		    parse_linknode( P_Node );
		    P_Sym->symtype = symcomment;
		    P_Sym->symdims = (unsigned) -1;
		    P_Sym->symdecl = P_Node;

		    P_Sym->exptype = exprint; /* cexpr's are only integers */
		  }
		}
#line 1806 "petity.c" /* yacc.c:1646  */
    break;

  case 23:
#line 240 "../src/petity.y" /* yacc.c:1646  */
    {
		  node *rp = (yyvsp[0].np);

		  parse_check_stmt_number();
		  P_Node = make_node( op_assign );
		  
		  /* make sure types are compatible */
		  /* note: refreal can accept any type */
		  if( (yyvsp[-2].np)->exptype == exprrefint && rp->exptype != exprint ) {
		    rp = make_node(op_rtoi);
		    rp->exptype = exprrefint;
		    rp->nodechild = (yyvsp[0].np);
		    ((yyvsp[0].np))->nodeparent = rp;
		  }
		  
		  parse_linknodeto( P_Node, rp );
		  parse_linknodeto( P_Node, (yyvsp[-2].np) );
		  parse_linknode( P_Node );
		}
#line 1830 "petity.c" /* yacc.c:1646  */
    break;

  case 24:
#line 263 "../src/petity.y" /* yacc.c:1646  */
    {
		  optype *pop;
		  
		  parse_check_stmt_number();
		  P_Node = make_node((yyvsp[-1].op));
		  
		  /* make sure types are compatible */
		  /* note: refreal can accept any type */
		  if( (yyvsp[-2].np)->exptype == exprrefint && (yyvsp[0].np)->exptype != exprint ) {
		    fprintf(stderr, "*** can't assign real to integer\n");
		    parse_die();
		  }

		  parse_linknodeto( P_Node, (yyvsp[0].np) );
		  parse_linknodeto( P_Node, (yyvsp[-2].np) );
		  parse_linknode( P_Node );

		  pop = &P_Node->nodechild->nodenext->nodeop;
		  if(*pop==op_store) {
		    *pop = op_update;
		  } else if(*pop==op_store_array) {
		    *pop = op_update_array;
		  }
                }
#line 1859 "petity.c" /* yacc.c:1646  */
    break;

  case 25:
#line 290 "../src/petity.y" /* yacc.c:1646  */
    {(yyval.op) = op_add_assign;}
#line 1865 "petity.c" /* yacc.c:1646  */
    break;

  case 26:
#line 291 "../src/petity.y" /* yacc.c:1646  */
    {(yyval.op) = op_mul_assign;}
#line 1871 "petity.c" /* yacc.c:1646  */
    break;

  case 27:
#line 292 "../src/petity.y" /* yacc.c:1646  */
    {(yyval.op) = op_max_assign;}
#line 1877 "petity.c" /* yacc.c:1646  */
    break;

  case 28:
#line 293 "../src/petity.y" /* yacc.c:1646  */
    {(yyval.op) = op_min_assign;}
#line 1883 "petity.c" /* yacc.c:1646  */
    break;

  case 29:
#line 299 "../src/petity.y" /* yacc.c:1646  */
    {
		    P_Sym = parse_symbol(0);
		    if( P_Sym->symdims > 0 ){
			fprintf(stderr, "*** lhs array must have %d subscripts: %s\n", 
				P_Sym->symdims, P_Sym->symname );
			parse_die();
		    }
		    if( P_Sym->symtype == symconst ){
			fprintf(stderr, "*** lhs must be variable: %s\n",
				P_Sym->symname );
			parse_die();
		    }
		    if( P_Sym->symtype == symindex ){
			fprintf(stderr, "*** lhs cannot be loop index: %s\n",
				P_Sym->symname );
			parse_die();
		    }

		    P_Node = make_node( op_store );
		    P_Node->nodevalue = (unsigned long int)P_Sym->symdecl;

		    P_Node->exptype = P_Sym->exptype; /* refint or refreal */

		    (yyval.np) = P_Node;
		}
#line 1913 "petity.c" /* yacc.c:1646  */
    break;

  case 30:
#line 326 "../src/petity.y" /* yacc.c:1646  */
    {
		    P_Sym = parse_symbol(0);
		    if( P_Sym->symdims <= 0 ){
			fprintf(stderr, "*** not an array: %s\n", P_Sym->symname );
			parse_die();
		    }
		    P_Node = make_node( op_store_array );
		    P_Node->nodevalue = (unsigned long int)P_Sym->symdecl;

		    if( P_Sym->exptype == exprintarray )
			P_Node->exptype = exprrefint;
		    else
		    if( P_Sym->exptype == exprrealarray )
			P_Node->exptype = exprrefreal;
		    else
			P_Node->exptype = exprunknown;

		    parse_linknode( P_Node );
		    parse_pushscope( P_Node ); 
		    (yyval.np) = P_Node;
		    /* save it because it can be reassigned down there */
		    P_Sym1 = P_Sym; 
		}
#line 1941 "petity.c" /* yacc.c:1646  */
    break;

  case 31:
#line 350 "../src/petity.y" /* yacc.c:1646  */
    {
		    /* make sure all subscripts are integer expressions */
		    int count = 0;
		    for( P_Node = ((yyvsp[-3].np))->nodechild; P_Node != NULL;
				      P_Node = P_Node->nodenext ){
		        count++;
			if( P_Node->exptype != exprint ) {
			    fprintf(stderr, "*** All subscripts must be integer\n" );
			    parse_die();
			}
		    }
		    if(count != (int)P_Sym1->symdims) {
			fprintf(stderr, "*** Wrong number of subscripts in %s (store)\n", P_Sym1->symname );
			parse_die();
		    }

		    parse_popscope();
		    parse_unlinknode();
		    (yyval.np) = (yyvsp[-3].np);
		}
#line 1966 "petity.c" /* yacc.c:1646  */
    break;

  case 32:
#line 373 "../src/petity.y" /* yacc.c:1646  */
    {}
#line 1972 "petity.c" /* yacc.c:1646  */
    break;

  case 35:
#line 384 "../src/petity.y" /* yacc.c:1646  */
    {
		    P_Sym = (yyvsp[-2].stp);
		    P_Node = make_node( op_declare );
		    P_Node->nodevalue = (unsigned long int)P_Sym;
		    parse_linknode( P_Node );
		    P_Sym->symtype = symconst;
		    P_Sym->symdims = (unsigned) -1;
		    P_Sym->symvalue = (yyvsp[0].iv);
		    P_Sym->symdecl = P_Node;

		    P_Sym->exptype = exprint; /* cexpr's are only integers */
		}
#line 1989 "petity.c" /* yacc.c:1646  */
    break;

  case 36:
#line 400 "../src/petity.y" /* yacc.c:1646  */
    { parse_forloop( op_do, (yyvsp[-6].stp), (yyvsp[-4].np), (yyvsp[-2].np), (yyvsp[-1].np) ); }
#line 1995 "petity.c" /* yacc.c:1646  */
    break;

  case 37:
#line 402 "../src/petity.y" /* yacc.c:1646  */
    { parse_endforloop(); }
#line 2001 "petity.c" /* yacc.c:1646  */
    break;

  case 38:
#line 405 "../src/petity.y" /* yacc.c:1646  */
    { parse_forloop( op_do, (yyvsp[-5].stp), (yyvsp[-3].np), (yyvsp[-1].np), (yyvsp[0].np) ); }
#line 2007 "petity.c" /* yacc.c:1646  */
    break;

  case 39:
#line 407 "../src/petity.y" /* yacc.c:1646  */
    { parse_endforloop(); }
#line 2013 "petity.c" /* yacc.c:1646  */
    break;

  case 40:
#line 410 "../src/petity.y" /* yacc.c:1646  */
    { parse_forloop( op_do, (yyvsp[-5].stp), (yyvsp[-3].np), (yyvsp[-1].np), (yyvsp[0].np) ); }
#line 2019 "petity.c" /* yacc.c:1646  */
    break;

  case 41:
#line 412 "../src/petity.y" /* yacc.c:1646  */
    { parse_endforloop(); }
#line 2025 "petity.c" /* yacc.c:1646  */
    break;

  case 42:
#line 416 "../src/petity.y" /* yacc.c:1646  */
    {(yyval.np) = NULL;}
#line 2031 "petity.c" /* yacc.c:1646  */
    break;

  case 43:
#line 417 "../src/petity.y" /* yacc.c:1646  */
    {(yyval.np) = (yyvsp[0].np);}
#line 2037 "petity.c" /* yacc.c:1646  */
    break;

  case 44:
#line 423 "../src/petity.y" /* yacc.c:1646  */
    {
		    parse_forloop( op_dovec, (yyvsp[-5].stp), (yyvsp[-3].np), (yyvsp[-1].np), (yyvsp[0].np) );
		}
#line 2045 "petity.c" /* yacc.c:1646  */
    break;

  case 45:
#line 427 "../src/petity.y" /* yacc.c:1646  */
    {
		    parse_endforloop();
		}
#line 2053 "petity.c" /* yacc.c:1646  */
    break;

  case 46:
#line 434 "../src/petity.y" /* yacc.c:1646  */
    {
		    parse_forloop( op_dopar, (yyvsp[-5].stp), (yyvsp[-3].np), (yyvsp[-1].np), (yyvsp[0].np) );
		}
#line 2061 "petity.c" /* yacc.c:1646  */
    break;

  case 47:
#line 438 "../src/petity.y" /* yacc.c:1646  */
    {
		    parse_endforloop();
		}
#line 2069 "petity.c" /* yacc.c:1646  */
    break;

  case 48:
#line 445 "../src/petity.y" /* yacc.c:1646  */
    {
		    parse_forloop( op_doany, (yyvsp[-5].stp), (yyvsp[-3].np), (yyvsp[-1].np), (yyvsp[0].np) );
		}
#line 2077 "petity.c" /* yacc.c:1646  */
    break;

  case 49:
#line 449 "../src/petity.y" /* yacc.c:1646  */
    {
		    parse_endforloop();
		}
#line 2085 "petity.c" /* yacc.c:1646  */
    break;

  case 50:
#line 455 "../src/petity.y" /* yacc.c:1646  */
    {}
#line 2091 "petity.c" /* yacc.c:1646  */
    break;

  case 51:
#line 457 "../src/petity.y" /* yacc.c:1646  */
    {}
#line 2097 "petity.c" /* yacc.c:1646  */
    break;

  case 52:
#line 459 "../src/petity.y" /* yacc.c:1646  */
    {}
#line 2103 "petity.c" /* yacc.c:1646  */
    break;

  case 53:
#line 463 "../src/petity.y" /* yacc.c:1646  */
    {}
#line 2109 "petity.c" /* yacc.c:1646  */
    break;

  case 54:
#line 465 "../src/petity.y" /* yacc.c:1646  */
    {}
#line 2115 "petity.c" /* yacc.c:1646  */
    break;

  case 55:
#line 467 "../src/petity.y" /* yacc.c:1646  */
    {}
#line 2121 "petity.c" /* yacc.c:1646  */
    break;

  case 56:
#line 472 "../src/petity.y" /* yacc.c:1646  */
    {
		    parse_check_stmt_number();
		    P_Node = make_node( op_if );

		    parse_linknode( P_Node );
		    parse_pushscope( P_Node );
		    parse_linknode( (yyvsp[0].np) );
		    P_Node = make_node( op_then );
		    parse_linknode( P_Node );
		    parse_pushscope( P_Node );
		}
#line 2137 "petity.c" /* yacc.c:1646  */
    break;

  case 57:
#line 486 "../src/petity.y" /* yacc.c:1646  */
    {
		    parse_popscope();
		    parse_popscope();
		}
#line 2146 "petity.c" /* yacc.c:1646  */
    break;

  case 58:
#line 495 "../src/petity.y" /* yacc.c:1646  */
    {   parse_popscope();
		    P_Node = make_node( op_else );
		    parse_linknode( P_Node );
		    parse_pushscope( P_Node );
		}
#line 2156 "petity.c" /* yacc.c:1646  */
    break;

  case 61:
#line 504 "../src/petity.y" /* yacc.c:1646  */
    {SaveClass=(var_class) (yyvsp[-1].iv); P_SaveType=(symboltype) (yyvsp[0].iv);}
#line 2162 "petity.c" /* yacc.c:1646  */
    break;

  case 63:
#line 507 "../src/petity.y" /* yacc.c:1646  */
    {(yyval.iv) = CLunknown;}
#line 2168 "petity.c" /* yacc.c:1646  */
    break;

  case 64:
#line 508 "../src/petity.y" /* yacc.c:1646  */
    {(yyval.iv) = CLAUTO;}
#line 2174 "petity.c" /* yacc.c:1646  */
    break;

  case 65:
#line 509 "../src/petity.y" /* yacc.c:1646  */
    {(yyval.iv) = CLCOMMON;}
#line 2180 "petity.c" /* yacc.c:1646  */
    break;

  case 66:
#line 510 "../src/petity.y" /* yacc.c:1646  */
    {(yyval.iv) = CLSTATIC;}
#line 2186 "petity.c" /* yacc.c:1646  */
    break;

  case 67:
#line 511 "../src/petity.y" /* yacc.c:1646  */
    {(yyval.iv) = CLFORMAL;}
#line 2192 "petity.c" /* yacc.c:1646  */
    break;

  case 68:
#line 512 "../src/petity.y" /* yacc.c:1646  */
    {(yyval.iv) = CLIN;}
#line 2198 "petity.c" /* yacc.c:1646  */
    break;

  case 69:
#line 513 "../src/petity.y" /* yacc.c:1646  */
    {(yyval.iv) = CLOUT;}
#line 2204 "petity.c" /* yacc.c:1646  */
    break;

  case 70:
#line 514 "../src/petity.y" /* yacc.c:1646  */
    {(yyval.iv) = CLINOUT;}
#line 2210 "petity.c" /* yacc.c:1646  */
    break;

  case 71:
#line 515 "../src/petity.y" /* yacc.c:1646  */
    {(yyval.iv) = CLPRIVATE;}
#line 2216 "petity.c" /* yacc.c:1646  */
    break;

  case 72:
#line 516 "../src/petity.y" /* yacc.c:1646  */
    {(yyval.iv) = CLBUILTIN;}
#line 2222 "petity.c" /* yacc.c:1646  */
    break;

  case 73:
#line 519 "../src/petity.y" /* yacc.c:1646  */
    {(yyval.iv)=syminteger;}
#line 2228 "petity.c" /* yacc.c:1646  */
    break;

  case 74:
#line 520 "../src/petity.y" /* yacc.c:1646  */
    {(yyval.iv)=symreal;}
#line 2234 "petity.c" /* yacc.c:1646  */
    break;

  case 77:
#line 532 "../src/petity.y" /* yacc.c:1646  */
    {
		    P_DeclSym = (yyvsp[0].stp);
		    P_Node = make_node( op_declare );
		    P_Node->nodevalue = (unsigned long int)P_DeclSym;
		    parse_linknode( P_Node );
		    P_DeclSym->symtype = P_SaveType;
		    P_DeclSym->symdims = 0;
		    P_DeclSym->symdecl = P_Node;
		    if(SaveClass == CLBUILTIN) {
		      fprintf(stderr, "Not function %s\n", (yyvsp[0].stp)->symname);
		      parse_die();
		    }
		    P_DeclSym->symclass =
		      SaveClass==CLunknown ? CLAUTO : SaveClass;

		    /* determine the type based on declaration */
		    if( P_SaveType == syminteger )
			P_DeclSym->exptype = exprrefint;
		    else if( P_SaveType == symreal )
			P_DeclSym->exptype = exprrefreal;
		    else
			P_DeclSym->exptype = exprunknown;
		}
#line 2262 "petity.c" /* yacc.c:1646  */
    break;

  case 79:
#line 558 "../src/petity.y" /* yacc.c:1646  */
    {
		    P_DeclSym = (yyvsp[0].stp);
		    P_Node = make_node( op_declare );
		    P_Node->nodevalue = (unsigned long int)P_DeclSym;
		    parse_linknode( P_Node );
		    parse_pushscope( P_Node );
		    P_DeclSym->symtype = P_SaveType;
		    P_DeclSym->symdecl = P_Node;
		    P_DeclSym->symclass = SaveClass==CLunknown ?
		      (1 ? CLINOUT : CLAUTO) : SaveClass;
		}
#line 2278 "petity.c" /* yacc.c:1646  */
    break;

  case 80:
#line 569 "../src/petity.y" /* yacc.c:1646  */
    {NoNewOldCheck=1;}
#line 2284 "petity.c" /* yacc.c:1646  */
    break;

  case 81:
#line 569 "../src/petity.y" /* yacc.c:1646  */
    {NoNewOldCheck=0;}
#line 2290 "petity.c" /* yacc.c:1646  */
    break;

  case 82:
#line 570 "../src/petity.y" /* yacc.c:1646  */
    {
		    /* determine the type based on declaration */
		    if(P_DeclSym->symdims!=DIMSFUN || SaveClass!=CLBUILTIN) {
		      if(P_DeclSym->symdims==DIMSFUN) {
			P_DeclSym->symdims = 1;
		      }
		      if( P_SaveType == syminteger )
			P_DeclSym->exptype = exprintarray;
		      else if( P_SaveType == symreal )
			P_DeclSym->exptype = exprrealarray;
		      else
			P_DeclSym->exptype = exprunknown;
		    } else {
		      if( P_SaveType == syminteger )
			P_DeclSym->exptype = exprintfun;
		      else if( P_SaveType == symreal )
			P_DeclSym->exptype = exprrealfun;
		      else
			P_DeclSym->exptype = exprunknown;
		    }

		    parse_popscope();
		}
#line 2318 "petity.c" /* yacc.c:1646  */
    break;

  case 85:
#line 598 "../src/petity.y" /* yacc.c:1646  */
    {}
#line 2324 "petity.c" /* yacc.c:1646  */
    break;

  case 86:
#line 599 "../src/petity.y" /* yacc.c:1646  */
    {}
#line 2330 "petity.c" /* yacc.c:1646  */
    break;

  case 89:
#line 605 "../src/petity.y" /* yacc.c:1646  */
    {free_node((yyvsp[0].np));}
#line 2336 "petity.c" /* yacc.c:1646  */
    break;

  case 90:
#line 610 "../src/petity.y" /* yacc.c:1646  */
    {   P_DeclSym->symdims = DIMSFUN; }
#line 2342 "petity.c" /* yacc.c:1646  */
    break;

  case 91:
#line 611 "../src/petity.y" /* yacc.c:1646  */
    {   P_DeclSym->symdims = 1; }
#line 2348 "petity.c" /* yacc.c:1646  */
    break;

  case 92:
#line 612 "../src/petity.y" /* yacc.c:1646  */
    {   P_DeclSym->symdims++; }
#line 2354 "petity.c" /* yacc.c:1646  */
    break;

  case 93:
#line 617 "../src/petity.y" /* yacc.c:1646  */
    {
		    P_Node = make_node( op_bounds );
		    parse_linknode( P_Node );
		    parse_pushscope( P_Node );

		    P_Node = make_node( op_constant );
		    P_Node->nodevalue = 1;
		    parse_linknode( P_Node );

		    P_Node = (yyvsp[0].np);
		    parse_linknode( P_Node );
		    parse_popscope();
		}
#line 2372 "petity.c" /* yacc.c:1646  */
    break;

  case 94:
#line 632 "../src/petity.y" /* yacc.c:1646  */
    {
		    P_Node = make_node( op_bounds );
		    parse_linknode( P_Node );
		    parse_pushscope( P_Node );

		    P_Node = (yyvsp[-2].np);
		    parse_linknode( P_Node );

		    P_Node = (yyvsp[0].np);
		    parse_linknode( P_Node );
		    parse_popscope();
		}
#line 2389 "petity.c" /* yacc.c:1646  */
    break;

  case 95:
#line 648 "../src/petity.y" /* yacc.c:1646  */
    {   (yyval.stp) = parse_symbol(1); }
#line 2395 "petity.c" /* yacc.c:1646  */
    break;

  case 96:
#line 653 "../src/petity.y" /* yacc.c:1646  */
    {   (yyval.stp) = parse_doid_symbol(); }
#line 2401 "petity.c" /* yacc.c:1646  */
    break;

  case 97:
#line 658 "../src/petity.y" /* yacc.c:1646  */
    {   
		    P_Sym = parse_symbol(0);
		    (yyval.iv) = P_Sym->symvalue;
		    /* don't allow variables in constant expressions */
		    if( P_Sym->symtype != symconst ){
			fprintf(stderr, "*** not a constant: %s\n", P_Sym->symname );
			parse_die();
		    }
		}
#line 2415 "petity.c" /* yacc.c:1646  */
    break;

  case 98:
#line 669 "../src/petity.y" /* yacc.c:1646  */
    {   (yyval.iv) = parse_intval(); }
#line 2421 "petity.c" /* yacc.c:1646  */
    break;

  case 99:
#line 672 "../src/petity.y" /* yacc.c:1646  */
    {   (yyval.iv) = (yyvsp[-2].iv) + (yyvsp[0].iv); }
#line 2427 "petity.c" /* yacc.c:1646  */
    break;

  case 100:
#line 675 "../src/petity.y" /* yacc.c:1646  */
    {   (yyval.iv) = (yyvsp[-2].iv) - (yyvsp[0].iv); }
#line 2433 "petity.c" /* yacc.c:1646  */
    break;

  case 101:
#line 678 "../src/petity.y" /* yacc.c:1646  */
    {   (yyval.iv) = - (yyvsp[0].iv); }
#line 2439 "petity.c" /* yacc.c:1646  */
    break;

  case 102:
#line 681 "../src/petity.y" /* yacc.c:1646  */
    {   (yyval.iv) = (yyvsp[0].iv); }
#line 2445 "petity.c" /* yacc.c:1646  */
    break;

  case 103:
#line 684 "../src/petity.y" /* yacc.c:1646  */
    {   (yyval.iv) = (yyvsp[-2].iv) * (yyvsp[0].iv); }
#line 2451 "petity.c" /* yacc.c:1646  */
    break;

  case 104:
#line 687 "../src/petity.y" /* yacc.c:1646  */
    {   (yyval.iv) = (yyvsp[-1].iv); }
#line 2457 "petity.c" /* yacc.c:1646  */
    break;

  case 105:
#line 692 "../src/petity.y" /* yacc.c:1646  */
    {   (yyval.np) = parse_symbolnode(); }
#line 2463 "petity.c" /* yacc.c:1646  */
    break;

  case 106:
#line 697 "../src/petity.y" /* yacc.c:1646  */
    {
		    (yyval.np) = (yyvsp[0].np);
		    if((yyvsp[0].np)->nodeop == op_fetch_array) {
		        P_Node = (node*)(yyvsp[0].np)->nodevalue;
			P_Sym = (symtabentry*)P_Node->nodevalue;
			fprintf(stderr,
				"*** array must have %d subscripts: %s\n",
				P_Sym->symdims, P_Sym->symname );
			parse_die();
		    }
		    if((yyvsp[0].np)->nodevalue == 0) {
		        fprintf(stderr,	"*** You use variable (loop index) which is not completely declared ***\n");
			parse_die();
		    }
		}
#line 2483 "petity.c" /* yacc.c:1646  */
    break;

  case 107:
#line 714 "../src/petity.y" /* yacc.c:1646  */
    {
	            P_Node = (node*)(yyvsp[0].np)->nodevalue;
		    P_Sym = (symtabentry*)P_Node->nodevalue;
		    if( (yyvsp[0].np)->nodeop == op_fetch ){
			fprintf(stderr, "*** not an array or function call: %s\n", P_Sym->symname );
			parse_die();
		    }
		    else if( (yyvsp[0].np)->nodeop == op_index ){
			fprintf(stderr, "*** not an array or function call: %s\n", P_Sym->symname );
			parse_die();
		    }
		    parse_linknode( (yyvsp[0].np) );
		    parse_pushscope( (yyvsp[0].np) );
		}
#line 2502 "petity.c" /* yacc.c:1646  */
    break;

  case 108:
#line 729 "../src/petity.y" /* yacc.c:1646  */
    {   parse_popscope();
		    parse_unlinknode();

	            P_Node = (node*)(yyvsp[-4].np)->nodevalue;
		    P_Sym = (symtabentry*)P_Node->nodevalue;
		    if((yyvsp[-4].np)->nodeop != op_call) {
		      int count = 0;
		      /* make sure all subscripts are integer expressions */
		      for( P_Node = (yyvsp[-4].np)->nodechild; P_Node != NULL;
			  P_Node = P_Node->nodenext ) {
			count++;
			if( P_Node->exptype != exprint ) {
			  fprintf(stderr, "*** All subscripts must be integer\n" );
			  parse_die();
			}
		      }
		      if(count != (int)P_Sym->symdims) {
			fprintf(stderr, "*** Wrong number of subscripts in %s (load)\n", P_Sym->symname );
			parse_die();
		      }
		    }

		    (yyval.np) = (yyvsp[-4].np);
		}
#line 2531 "petity.c" /* yacc.c:1646  */
    break;

  case 109:
#line 755 "../src/petity.y" /* yacc.c:1646  */
    {
		    P_Node = make_node( op_constant );
		    P_Node->nodevalue = parse_intval();
		    P_Node->exptype = exprint;
		    (yyval.np) = P_Node;
		}
#line 2542 "petity.c" /* yacc.c:1646  */
    break;

  case 110:
#line 763 "../src/petity.y" /* yacc.c:1646  */
    {
		    P_Sym = parse_symbol(-1);
		    P_Node = make_node( op_real );
		    P_Node->nodevalue = (unsigned long int)P_Sym;
		    P_Node->exptype = exprreal;
		    (yyval.np) = P_Node;
		}
#line 2554 "petity.c" /* yacc.c:1646  */
    break;

  case 111:
#line 772 "../src/petity.y" /* yacc.c:1646  */
    {   (yyval.np) = (yyvsp[-1].np); }
#line 2560 "petity.c" /* yacc.c:1646  */
    break;

  case 112:
#line 775 "../src/petity.y" /* yacc.c:1646  */
    {   (yyval.np) = parse_binaryop((yyvsp[-2].np),op_add,(yyvsp[0].np)); }
#line 2566 "petity.c" /* yacc.c:1646  */
    break;

  case 113:
#line 778 "../src/petity.y" /* yacc.c:1646  */
    {   (yyval.np) = parse_binaryop((yyvsp[-2].np),op_subtract,(yyvsp[0].np)); }
#line 2572 "petity.c" /* yacc.c:1646  */
    break;

  case 114:
#line 781 "../src/petity.y" /* yacc.c:1646  */
    {   (yyval.np) = (yyvsp[0].np); }
#line 2578 "petity.c" /* yacc.c:1646  */
    break;

  case 115:
#line 784 "../src/petity.y" /* yacc.c:1646  */
    {   (yyval.np) = parse_binaryop(make_const(0),op_subtract,(yyvsp[0].np)); }
#line 2584 "petity.c" /* yacc.c:1646  */
    break;

  case 116:
#line 787 "../src/petity.y" /* yacc.c:1646  */
    {   (yyval.np) = parse_binaryop((yyvsp[-2].np),op_multiply,(yyvsp[0].np)); }
#line 2590 "petity.c" /* yacc.c:1646  */
    break;

  case 117:
#line 790 "../src/petity.y" /* yacc.c:1646  */
    {   (yyval.np) = parse_binaryop((yyvsp[-2].np),op_divide,(yyvsp[0].np)); }
#line 2596 "petity.c" /* yacc.c:1646  */
    break;

  case 118:
#line 793 "../src/petity.y" /* yacc.c:1646  */
    {   (yyval.np) = parse_binaryop((yyvsp[-2].np),op_exp,(yyvsp[0].np)); }
#line 2602 "petity.c" /* yacc.c:1646  */
    break;

  case 119:
#line 796 "../src/petity.y" /* yacc.c:1646  */
    {   (yyval.np) = parse_binaryop((yyvsp[-2].np),op_lt,(yyvsp[0].np)); }
#line 2608 "petity.c" /* yacc.c:1646  */
    break;

  case 120:
#line 799 "../src/petity.y" /* yacc.c:1646  */
    {   (yyval.np) = parse_binaryop((yyvsp[-2].np),op_le,(yyvsp[0].np)); }
#line 2614 "petity.c" /* yacc.c:1646  */
    break;

  case 121:
#line 802 "../src/petity.y" /* yacc.c:1646  */
    {   (yyval.np) = parse_binaryop((yyvsp[-2].np),op_eq,(yyvsp[0].np)); }
#line 2620 "petity.c" /* yacc.c:1646  */
    break;

  case 122:
#line 805 "../src/petity.y" /* yacc.c:1646  */
    {   (yyval.np) = parse_binaryop((yyvsp[-2].np),op_ne,(yyvsp[0].np)); }
#line 2626 "petity.c" /* yacc.c:1646  */
    break;

  case 123:
#line 808 "../src/petity.y" /* yacc.c:1646  */
    {   (yyval.np) = parse_binaryop((yyvsp[-2].np),op_ge,(yyvsp[0].np)); }
#line 2632 "petity.c" /* yacc.c:1646  */
    break;

  case 124:
#line 811 "../src/petity.y" /* yacc.c:1646  */
    {   (yyval.np) = parse_binaryop((yyvsp[-2].np),op_gt,(yyvsp[0].np)); }
#line 2638 "petity.c" /* yacc.c:1646  */
    break;

  case 125:
#line 814 "../src/petity.y" /* yacc.c:1646  */
    {   (yyval.np) = parse_binaryop((yyvsp[-2].np),op_and,(yyvsp[0].np)); }
#line 2644 "petity.c" /* yacc.c:1646  */
    break;

  case 126:
#line 817 "../src/petity.y" /* yacc.c:1646  */
    {   (yyval.np) = parse_binaryop((yyvsp[-2].np),op_or,(yyvsp[0].np)); }
#line 2650 "petity.c" /* yacc.c:1646  */
    break;

  case 127:
#line 820 "../src/petity.y" /* yacc.c:1646  */
    {   (yyval.np) = parse_binaryop((yyvsp[0].np),op_not,NULL); }
#line 2656 "petity.c" /* yacc.c:1646  */
    break;

  case 128:
#line 823 "../src/petity.y" /* yacc.c:1646  */
    {   (yyval.np) = parse_binaryop((yyvsp[-2].np),op_mod,(yyvsp[0].np)); }
#line 2662 "petity.c" /* yacc.c:1646  */
    break;

  case 129:
#line 826 "../src/petity.y" /* yacc.c:1646  */
    {   (yyval.np) = parse_binaryop((yyvsp[-2].np),op_max,(yyvsp[0].np)); }
#line 2668 "petity.c" /* yacc.c:1646  */
    break;

  case 130:
#line 829 "../src/petity.y" /* yacc.c:1646  */
    {   (yyval.np) = parse_binaryop((yyvsp[-2].np),op_min,(yyvsp[0].np)); }
#line 2674 "petity.c" /* yacc.c:1646  */
    break;

  case 131:
#line 832 "../src/petity.y" /* yacc.c:1646  */
    {   (yyval.np) = parse_binaryop(NULL,op_sqrt,(yyvsp[-1].np)); }
#line 2680 "petity.c" /* yacc.c:1646  */
    break;

  case 132:
#line 835 "../src/petity.y" /* yacc.c:1646  */
    {   (yyval.np) = make_node( op_rand );
                    (yyval.np)->exptype = exprint;
                }
#line 2688 "petity.c" /* yacc.c:1646  */
    break;

  case 133:
#line 840 "../src/petity.y" /* yacc.c:1646  */
    {   (yyval.np) = parse_binaryop((yyvsp[-3].np),op_floor_divide,(yyvsp[-1].np));
		    (yyval.np)->exptype = exprint;
		}
#line 2696 "petity.c" /* yacc.c:1646  */
    break;

  case 134:
#line 845 "../src/petity.y" /* yacc.c:1646  */
    {   (yyval.np) = parse_binaryop((yyvsp[-3].np),op_ceiling_divide,(yyvsp[-1].np));
		    (yyval.np)->exptype = exprint;
		}
#line 2704 "petity.c" /* yacc.c:1646  */
    break;

  case 135:
#line 850 "../src/petity.y" /* yacc.c:1646  */
    {
		    parse_linknode( (yyvsp[0].np) );
		    parse_pushscope( (yyvsp[0].np) );
		}
#line 2713 "petity.c" /* yacc.c:1646  */
    break;

  case 136:
#line 855 "../src/petity.y" /* yacc.c:1646  */
    {
		    parse_popscope();
		    parse_unlinknode();

		    /* if any of the list's expressions is real, so is this */
		    (yyvsp[-4].np)->exptype = exprint;
		    for( P_Node = (yyvsp[-4].np)->nodechild;
			 P_Node != NULL; P_Node = P_Node->nodenext ) {
			if( P_Node->exptype != exprint ) {
			    (yyvsp[-4].np)->exptype = exprreal;
			}
		    }
		    (yyval.np) = (yyvsp[-4].np);
		}
#line 2732 "petity.c" /* yacc.c:1646  */
    break;

  case 137:
#line 873 "../src/petity.y" /* yacc.c:1646  */
    { (yyval.np) = make_node( op_max ); }
#line 2738 "petity.c" /* yacc.c:1646  */
    break;

  case 138:
#line 876 "../src/petity.y" /* yacc.c:1646  */
    { (yyval.np) = make_node( op_min ); }
#line 2744 "petity.c" /* yacc.c:1646  */
    break;

  case 139:
#line 881 "../src/petity.y" /* yacc.c:1646  */
    {   parse_linknode( (yyvsp[0].np) ); }
#line 2750 "petity.c" /* yacc.c:1646  */
    break;

  case 140:
#line 884 "../src/petity.y" /* yacc.c:1646  */
    {   parse_linknode( (yyvsp[0].np) ); }
#line 2756 "petity.c" /* yacc.c:1646  */
    break;


#line 2760 "petity.c" /* yacc.c:1646  */
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
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

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

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
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
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
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
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 887 "../src/petity.y" /* yacc.c:1906  */

/* program section */

namespace omega {

static 
void CheckEnd() {
  if(ShouldBeEnd) {
    Error("RETURN statement at the middle of a program");
  }
}


/* parse_die */
static void parse_die()
{
    fprintf(stderr, "Ended on line %ld at %s\n", Lines, yytext );
    Exit(1);
}/* parse_die */

/* Utility routine ... get the integer */
static int parse_intval()
{
int val, p;
char ch;

    p = 0;
    val = 0;
    while( (ch=P_INTname[p]) >= '0' && ch <= '9' ){
	val = val * 10 + (ch - '0');
	p = p + 1;
    }
    return val;
}/* parse_intval */

/* Link in a new node at this point. */
static void parse_linknode( node *new_node )
{
    new_node->nodeprev = P_NextPrev;
    new_node->nodeparent = P_NextParent;

    if( P_NextPrev != NULL )
	P_NextPrev->nodenext = new_node;
    if( P_NextParent != NULL && P_NextParent->nodechild == NULL )
	P_NextParent->nodechild = new_node;

    P_NextPrev = new_node;
}/* parse_linknode */

/* unlink node, when it doesn't really belong */
static void parse_unlinknode()
{
node *old;
    old = P_NextPrev;

    P_NextPrev = old->nodeprev;

    if( P_NextParent != NULL && P_NextParent->nodechild == old )
	P_NextParent->nodechild = NULL;
    if( P_NextPrev != NULL )
	P_NextPrev->nodenext = NULL;

    old->nodeprev = NULL;
    old->nodeparent = NULL;
}/* parse_unlinknode */

static void parse_linknodeto( node *old, node *new_node )
{
node *last;
    for(last = old->nodechild;
	last != NULL && last->nodenext != NULL;
	last = last->nodenext ) ;

    new_node->nodeprev = last;
    new_node->nodeparent = old;

    if( last != NULL )
	last->nodenext = new_node;
    if( old->nodechild == NULL )
	old->nodechild = new_node;
}/* parse_linknodeto */

/* Push and Pop scopes */
static void parse_pushscope( node *n )
{
    if( n == 0 ){
	P_NextParent = P_NextPrev;
    } else {
	P_NextParent = n;
    }
    P_NextPrev = NULL;
}/* parse_pushscope */

static void parse_popscope()
{
    P_NextPrev = P_NextParent;
    P_NextParent = P_NextPrev->nodeparent;
}/* parse_popscope */


static exprtype expression_type( node *left, optype op, node *right )
{
exprtype result;

    /* assume the expression's type is integer until proven otherwise */
    result = exprint;

    switch( op ) {
    case op_add:
    case op_subtract:
    case op_multiply:
    case op_divide:
    case op_exp:
    case op_mod:
    case op_max:
    case op_min:
    case op_floor_divide:
    case op_ceiling_divide:
      /* if either expression is real, the result is real */
      if( left != NULL ) {
	  if( left->exptype != exprint && left->exptype != exprrefint ) {
	      result = exprreal;
	  }
      }
      if( right != NULL ) {
	  if( right->exptype != exprint && right->exptype != exprrefint ) {
	      result = exprreal;
	  }
      }
      break;

    case op_lt:
    case op_le:
    case op_eq:
    case op_ne:
    case op_ge:
    case op_gt:
      /* type already set to integer, which these are */
      break;

    case op_sqrt:
      /* type is always real in this case */
      result = exprreal;
      break;

    default:
      /* default is unknown, which had better not happen! */
      result = exprunknown;
      break;
    }

    return( result );
}/* expression_type */

static node *parse_binaryop( node *left, optype op, node *right )
{
node *n;

    n = make_node( op );

    /* get the expression's type */
    n->exptype = expression_type( left, op, right );

    if( left  != NULL ) parse_linknodeto( n, left  );
    if( right != NULL ) parse_linknodeto( n, right );
    return n;
}/* parse_binaryop */

static void parse_forloop(optype op, symtabentry *index,
			node *lower, node *upper, node *inc) {
    node *donode, *doindex;
    int i;

    if(!(P_LoopNest<maxnest))
      ErrAssert("parse_forloop: too deep loop nesting level");
    for(i=0; i<(int)P_LoopNest; i++) {
      if(strcmp(loopsyms[i],index->symname)==0) {
	fprintf(stderr,
		"Loop parameter `%s' is already used in outside loop\n",
		index->symname);
	parse_die();
      }
    }
    loopsyms[P_LoopNest]=index->symname;

    donode = make_node( op );
    parse_linknode( donode );
    ++P_LoopNest;
    donode->nodevalue = P_LoopNest;
    parse_pushscope( donode );

    doindex = make_node( op_dolimit );
    doindex->nodevalue = (unsigned long int)index;
    parse_linknode( doindex );

    parse_linknode( lower );
    parse_linknode( upper );
    if( inc != NULL ) parse_linknode( inc );

    parse_pushscope( doindex );

    index->symtype = symindex;
    index->symdecl = doindex;
    index->exptype = exprrefint; /* we only allow integer index variables */

    /* make sure the lower and upper loop bounds are integer expressions */
    if( lower->exptype != exprint ) {
	fprintf(stderr, "*** lower bound not integer expression\n" );
	parse_die();
    }
    else
    if( upper->exptype != exprint ) {
	fprintf(stderr, "*** upper bound not integer expression\n" );
	parse_die();
    }
    else
    if( inc != NULL ) {
	if( inc->exptype != exprint ) {
	    fprintf(stderr, "*** increment not integer expression\n" );
	    parse_die();
	}
    }
}/* parse_forloop */

static void parse_endforloop()
{
symtabentry *index;

    index = (symtabentry*)P_NextParent->nodevalue;
    index->symtype = symoldindex;
    parse_popscope();
    parse_popscope();
    --P_LoopNest;
}/* parse_endforloop */

nametabentry *parse_findsym()
{
nametabentry *f;

    for( f = NameHead; f != NULL; f = f->namenext ){
	if( strcmp( f->namest.symname, P_IDname ) == 0 &&
	    f->namest.symtype != symoldindex ){
	     return f;
	}
    }
    return NULL;
}/* parse_findsym */

symtabentry *add_symbol(const char *name, int new_int,
			symboltype symtype, exprtype exptype,
			nametabentry *onam)
{
  nametabentry *nam;

#if 0  
  fprintf(stderr, "At line %ld, adding symbol %s to name table\n", Lines, name);
  for (nam = NameHead; nam; nam = nam->namenext)
  {
      fprintf(stderr, "   %s\n", nam->namest.symname);
  }
#endif

  nam = new nametabentry;
  if (!nam) out_of_memory();
  nam->namenext = NameHead;
  NameHead = nam;
  nam->namest.symtype = symtype;
  nam->namest.symdims = 0;
  nam->namest.symdecl = NULL;
  nam->namest.def_node = NULL;
  nam->namest.symname = (char*)calloc( strlen( name )+1, 1 );
  if (!nam->namest.symname) out_of_memory();
  strcpy( nam->namest.symname, name );
  nam->namest.nte = nam;
  nam->namest.original = NULL;
  nam->namest.exptype = exptype;
  nam->namest.symoffset = 0;	  /* set later if needs memory */
  nam->namest.symtag = UNTAGGED;
  nam->namest.omega_vars = 0;
  if(new_int==0 && onam==NULL) {
    node *n = make_node( op_declare );
    n->nodevalue = (unsigned long int)(&nam->namest);
    nam->namest.symdecl = n;
    nam->namest.symclass = CLFORMAL;
    PlaceNodeBefore(n,Entry->nodechild);
  }
  return &(nam->namest);
}

/*
 * Find/create symbol table entry.
 * new_int : 0 - name should already exist or you'll get error message,
 *       1 - name should not exist or get error message,
 *       2 - create new name even if the entry with this name exists already
 */
symtabentry *parse_symbol(int new_int) {
  nametabentry *nam = parse_findsym();
  nametabentry *onam = nam;
  
  if(NoNewOldCheck) {
    if(nam)
      return &(nam->namest);
  } else {
    if( new_int == 0 ){
      if( nam == NULL ){
	fprintf(stderr, "*** `%s' is undeclared variable ***\n", P_IDname);
	parse_die();
      }
      return &(nam->namest);
    }
    if( new_int == 1 ) {
      if( nam != NULL ){
	fprintf(stderr, "Warning: variable `%s' declared twice, 2nd declaration on line %ld\n", P_IDname, Lines);
	return &(nam->namest);
      }
    }
  }

  return add_symbol(P_IDname, new_int, syminteger, exprrefint, onam);
       /* we'll set the type later */
}/* parse_symbol */

/*
 * create symbol table entry for loop, and for loop step count
 * (the latter is needed so that we can have a var_id for the omega test)
 */

static symtabentry *parse_doid_symbol()
{
    symtabentry *id, *stepsym;
    char loop_step_name[256];
    sprintf(loop_step_name, "<%s-trip>", P_IDname);
    stepsym = add_symbol(loop_step_name, 1, symloopstep, exprrefint, 0);
    id = parse_symbol(2);
    assert(&(id->nte->namenext->namest) == stepsym);
    return id;
}
							      
/*
 * Make node referencing already existing variable
 */
node *parse_symbolnode()
{
node *nod;
symtabentry *sym;

    sym = parse_symbol( 0 );

    if( sym->symtype == symindex ){
	nod = make_node( op_index );
	nod->nodevalue = (unsigned long int)sym->symdecl;
	nod->exptype = exprint;	       /* all index expressions are integer */
    } else if( sym->symtype == symconst ) {
	nod = make_node( op_constant );
	nod->nodevalue = (unsigned long int)sym->symvalue;
	nod->exptype = exprint;	       /* all constants are integers */
    } else if( sym->symdims == 0 ) {   /* determine type of scalar var */
	nod = make_node( op_fetch );
	nod->nodevalue = (unsigned long int)sym->symdecl;
	if( sym->exptype == exprrefint )
	    nod->exptype = exprint;
	else if( sym->exptype == exprrefreal )
	    nod->exptype = exprreal;
	else
	    nod->exptype = exprunknown;
    } else if(sym->symdims == DIMSFUN) {   /* builtin function */
	nod = make_node( op_call );
	nod->nodevalue = (unsigned long int)sym->symdecl;
	if( sym->exptype == exprintfun )
	    nod->exptype = exprint;
	else if( sym->exptype == exprrealfun )
	    nod->exptype = exprreal;
	else
	    nod->exptype = exprunknown;
    } else if( sym->symdims > 0 ) {
	nod = make_node( op_fetch_array );
	nod->nodevalue = (unsigned long int)sym->symdecl;
	if( sym->exptype == exprintarray )
	    nod->exptype = exprint;     /* if int array, then just int */
	else
	if( sym->exptype == exprrealarray )
	    nod->exptype = exprreal;    /* if real array, then just real */
	else
	    nod->exptype = exprunknown;
    } else {
	fprintf(stderr, "unknown symbol %s\n", sym->symname );
	parse_die();
	nod = 0;  // make g++ calm down about initialization
    }
    return nod;
}/* parse_symbolnode */

static void parse_stmt_index( node *n )
{
node *index;

    if( n == NULL ) return;
    parse_stmt_index( n->nodeparent );
    if( n->nodeop == op_dolimit ){
	index = make_node( op_index );
	index->nodevalue = (unsigned long int)n;
	parse_linknode( index );
    }
}/* parse_stmt_index */

static void parse_check_stmt_number()
/* Put an op_stmt_number here. */
{
node *stmt_number;

    if( P_NextParent != NULL && P_NextParent->nodeop == op_dolimit ){
	++P_StmtNumber;
	stmt_number = make_node( op_stmt_number );
	stmt_number->nodevalue = P_StmtNumber;
	parse_linknode( stmt_number );
	parse_pushscope( stmt_number );
	parse_stmt_index( stmt_number->nodeparent );
	parse_popscope();
    }
}/* parse_check_stmt_number */

/* Initialize everything. */
static void parse_init()
{
    Lines = 1;
    P_Lines = 1;
    P_LoopNest = 0;
    P_StmtNumber = 0;

    /* Initialize entry point. */
    Entry = make_node( op_entry );

    /* Initialize node links. */
    P_NextPrev = NULL;
    P_NextParent = Entry;

    NameHead = NULL;
}/* parse_init */

void yyerror( char *s)
{
    fprintf(stderr, "%s\n", s );
    parse_die();
}/* yyerror */

} // end of namespace omega
