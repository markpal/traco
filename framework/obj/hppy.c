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


/* Substitute the variable and function names.  */
#define yyparse         hpp_yyparse
#define yylex           hpp_yylex
#define yyerror         hpp_yyerror
#define yydebug         hpp_yydebug
#define yynerrs         hpp_yynerrs

#define yylval          hpp_yylval
#define yychar          hpp_yychar

/* Copy the first part of user declarations.  */
#line 1 "../src/hppy.y" /* yacc.c:339  */


/* 
to do to get HPP:

H   write function to create space mapping from access function
M+  figure out how to handle different distributions 
L   come up with interesting time mappings if independent?
M   allow code generation to execute things in any order (for indep. loops)
M   generation of local addresses, then interchange loops
M   generation of communication statements

*/

#ifdef __cplusplus
extern "C" {
#endif
inline int hpp_yywrap() { return 1; }
#ifdef __cplusplus
}
#endif

#include <omega.h>
#include <stdio.h>
#include <string.h>
#include <basic/Map.h>
#include <omega/AST.h>
#include <math.h>
#include <petit/tree.h>
#include <petit/hpp.h>
#include <petit/petit_args.h>
#ifdef WIN32
#include <io.h>
#define isatty _isatty
#include <malloc.h>
#define alloca _alloca
#endif

using omega::min;
using omega::negate;

extern int hpp_yylex(void);
extern int hpp_yyerror(char * );


namespace omega {

typedef List<int> IntList;
List<template_info *> templates;
Map<String,IntList*> proc_map ((IntList *)0);
Map<String,Relation*> alignment_map ((Relation *)0);
Map<String,Relation*> distribute_map ((Relation *)0);
Map<String,Relation*> whole_map ((Relation *)0);

// array -> templ name
Map<String,String> tname_map("");
//templ -> proc name
Map<String,String> pname_map("");

FILE *hpp_debug_file;
extern FILE *DebugFile;
}


int pickles=0;

void hpp_error_callback(const String &s) {
    fprintf(stderr, "%s\n", (const char *) s);
    exit(1);
}

using namespace omega;


#line 149 "hppy.c" /* yacc.c:339  */

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
   by #include "hppy.h".  */
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
#line 99 "../src/hppy.y" /* yacc.c:355  */

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

#line 260 "hppy.c" /* yacc.c:355  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE hpp_yylval;

int hpp_yyparse (void);

#endif /* !YY_HPP_YY_HPPY_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 275 "hppy.c" /* yacc.c:358  */

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
#define YYLAST   89

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  37
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  19
/* YYNRULES -- Number of rules.  */
#define YYNRULES  40
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  76

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   284

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
      18,    36,     9,     4,     2,     5,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    35,     2,
       2,     2,     2,     2,    10,     2,     2,     2,     2,     2,
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
       2,     2,     2,     2,     2,     2,     1,     2,     3,     6,
       7,     8,    11,    12,    13,    14,    15,    16,    17,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   114,   114,   114,   126,   126,   128,   128,   128,   128,
     130,   139,   151,   151,   218,   248,   249,   253,   254,   255,
     256,   261,   261,   267,   268,   272,   284,   286,   293,   295,
     300,   306,   314,   330,   333,   334,   335,   336,   337,   338,
     339
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "p1", "'+'", "'-'", "p2", "INTERSECTION",
  "p3", "'*'", "'@'", "p4", "p5", "p6", "NOT", "p7", "p8", "p9", "'('",
  "p10", "p11", "VAR", "INT", "ALIGN", "DISTRIBUTE", "PROCESSORS",
  "TEMPLATE", "WITH", "ONTO", "CYCLIC", "BLOCK", "STAR", "LPAREN",
  "RPAREN", "COMMA", "':'", "')'", "$accept", "start", "$@1", "stmt_list",
  "stmt", "template_decl", "proc_decl", "alignment", "$@2", "distribution",
  "distlist", "distinfo", "tupleDeclaration", "$@3", "tupleVarList",
  "tupleVar", "intlist", "simpleExp", "exp", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,    43,    45,   259,   260,   261,    42,
      64,   262,   263,   264,   265,   266,   267,   268,    40,   269,
     270,   271,   272,   273,   274,   275,   276,   277,   278,   279,
     280,   281,   282,   283,   284,    58,    41
};
# endif

#define YYPACT_NINF -43

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-43)))

#define YYTABLE_NINF -26

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int8 yypact[] =
{
     -43,    26,    20,   -43,    29,    30,    31,   -43,    17,   -43,
     -43,   -43,    32,   -43,    21,    22,    24,   -43,    36,    18,
      37,    37,   -43,    28,   -43,   -43,   -23,   -43,   -43,   -17,
     -14,    34,    33,    40,    35,    18,   -43,    42,   -43,    45,
       9,    25,    46,   -43,   -43,   -43,    16,   -43,    16,    -5,
      -6,     2,   -43,   -43,    -2,   -43,   -43,   -43,   -43,   -43,
      -4,   -43,   -43,     9,    16,    16,    16,    16,   -43,   -43,
      59,    59,   -43,     4,    47,   -43
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,    12,     1,     0,     0,     0,     3,     4,     6,
       7,     8,     0,     9,     0,     0,     0,     5,     0,     0,
       0,     0,    21,    18,    17,    20,     0,    16,    30,     0,
       0,     0,     0,     0,     0,     0,    11,     0,    10,     0,
       0,     0,     0,    15,    31,    21,     0,    26,     0,    32,
      34,     0,    23,    36,    27,    19,    14,    13,    32,    37,
       0,    35,    22,     0,     0,     0,     0,     0,    33,    24,
      38,    39,    40,    28,     0,    29
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -43,   -43,   -43,    62,   -43,   -43,   -43,   -43,   -43,   -43,
     -43,    38,    27,   -43,   -43,     8,    53,    39,   -42
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     1,     2,     7,     8,     9,    10,    11,    12,    13,
      26,    27,    31,    32,    51,    52,    29,    53,    54
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      64,    65,    64,    65,    59,    66,    60,    66,    64,    65,
      34,    35,    48,    66,    46,    58,    36,    37,    47,    38,
      37,    46,    70,    71,    72,    73,     3,    48,   -25,   -25,
      49,    50,    68,    67,    48,    62,    63,    58,    50,    74,
     -12,     4,     5,     6,     4,     5,     6,    23,    24,    25,
      14,    15,    16,    19,    20,    18,    21,    22,    55,    28,
      33,    39,    41,    42,    44,    40,    45,    56,    66,    75,
      17,    69,    57,    43,    30,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    61
};

static const yytype_int8 yycheck[] =
{
       4,     5,     4,     5,    46,     9,    48,     9,     4,     5,
      33,    34,    18,     9,     5,    21,    33,    34,     9,    33,
      34,     5,    64,    65,    66,    67,     0,    18,    33,    34,
      21,    22,    36,    35,    18,    33,    34,    21,    22,    35,
      23,    24,    25,    26,    24,    25,    26,    29,    30,    31,
      21,    21,    21,    32,    32,    23,    32,    21,    33,    22,
      32,    27,    22,    28,    22,    32,    21,    21,     9,    22,
       8,    63,    45,    35,    21,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    50
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    38,    39,     0,    24,    25,    26,    40,    41,    42,
      43,    44,    45,    46,    21,    21,    21,    40,    23,    32,
      32,    32,    21,    29,    30,    31,    47,    48,    22,    53,
      53,    49,    50,    32,    33,    34,    33,    34,    33,    27,
      32,    22,    28,    48,    22,    21,     5,     9,    18,    21,
      22,    51,    52,    54,    55,    33,    21,    49,    21,    55,
      55,    54,    33,    34,     4,     5,     9,    35,    36,    52,
      55,    55,    55,    55,    35,    22
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    37,    39,    38,    40,    40,    41,    41,    41,    41,
      42,    43,    45,    44,    46,    47,    47,    48,    48,    48,
      48,    50,    49,    51,    51,    52,    52,    52,    52,    52,
      53,    53,    54,    54,    55,    55,    55,    55,    55,    55,
      55
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     2,     1,     2,     1,     1,     1,     1,
       5,     5,     0,     7,     7,     3,     1,     1,     1,     4,
       1,     0,     4,     1,     3,     1,     1,     1,     3,     5,
       1,     3,     1,     3,     1,     2,     1,     2,     3,     3,
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
#line 114 "../src/hppy.y" /* yacc.c:1646  */
    { current_Declaration_Site = 0;
         hpp_debug_file = omega::DebugFile;
         current_Declaration_Site = globalDecls = 
	     new Global_Declaration_Site();
         petit_args.hpp_mode = true;
       }
#line 1408 "hppy.c" /* yacc.c:1646  */
    break;

  case 3:
#line 121 "../src/hppy.y" /* yacc.c:1646  */
    { delete globalDecls; }
#line 1414 "hppy.c" /* yacc.c:1646  */
    break;

  case 10:
#line 131 "../src/hppy.y" /* yacc.c:1646  */
    {  
       List<int> *l = (yyvsp[-1].INTEGER_LIST);
       add_template((yyvsp[-3].VAR_NAME), l);
       fprintf(hpp_debug_file,"Template %s is: ",(yyvsp[-3].VAR_NAME));
       make_bounds_relation(l).print_with_subs(hpp_debug_file,true);
   }
#line 1425 "hppy.c" /* yacc.c:1646  */
    break;

  case 11:
#line 140 "../src/hppy.y" /* yacc.c:1646  */
    {  
       add_proc((yyvsp[-3].VAR_NAME),(yyvsp[-1].INTEGER_LIST));
       assert((yyvsp[-1].INTEGER_LIST)->length() == 1 && "Only handle 1-dim processors");
#if 0
       fprintf(hpp_debug_file,"Processor declaration %s is: ",(yyvsp[-3].VAR_NAME));
       make_bounds_relation(lookup_proc((yyvsp[-3].VAR_NAME))).print_with_subs(hpp_debug_file,true);
#endif
   }
#line 1438 "hppy.c" /* yacc.c:1646  */
    break;

  case 12:
#line 151 "../src/hppy.y" /* yacc.c:1646  */
    { relationDecl = new Declaration_Site(); }
#line 1444 "hppy.c" /* yacc.c:1646  */
    break;

  case 13:
#line 153 "../src/hppy.y" /* yacc.c:1646  */
    {

    symtabentry *s = lookup_symbol((yyvsp[-4].VAR_NAME));
    s->template_name = (yyvsp[-1].VAR_NAME);

/* This chunk of code from parser.y constructs a relation from the 
   expression lists in the alignment statement */

    Relation * r = new Relation((yyvsp[-3].TUPLE_DESCRIPTOR)->size,(yyvsp[0].TUPLE_DESCRIPTOR)->size);
    resetGlobals();
    F_And *f = r->add_and();
    int i;
    for(i=1;i<=(yyvsp[-3].TUPLE_DESCRIPTOR)->size;i++) {	
	(yyvsp[-3].TUPLE_DESCRIPTOR)->vars[i]->vid = r->input_var(i);
	if (!(yyvsp[-3].TUPLE_DESCRIPTOR)->vars[i]->anonymous) 
	    r->name_input_var(i,(yyvsp[-3].TUPLE_DESCRIPTOR)->vars[i]->stripped_name);
    };
    for(i=1;i<=(yyvsp[0].TUPLE_DESCRIPTOR)->size;i++) {
	(yyvsp[0].TUPLE_DESCRIPTOR)->vars[i]->vid = r->output_var(i);
	if (!(yyvsp[0].TUPLE_DESCRIPTOR)->vars[i]->anonymous) 
	    r->name_output_var(i,(yyvsp[0].TUPLE_DESCRIPTOR)->vars[i]->stripped_name);
    };
    foreach(e,Exp*,(yyvsp[-3].TUPLE_DESCRIPTOR)->eq_constraints, install_eq(f,e,0));
    
    /*   foreach(e,Exp*,$4->geq_constraints, install_geq(f,e,0)); */
    do 
	{
	    for (Any_Iterator<Exp*> __P_x = ((yyvsp[-3].TUPLE_DESCRIPTOR)->geq_constraints).any_iterator();
		 __P_x;
		 __P_x++) 
		{
		    Exp* & e = *__P_x; 
		    install_geq(f,e,0);
		}
	} while (0);
    
    foreach(c,strideConstraint*,(yyvsp[-3].TUPLE_DESCRIPTOR)->stride_constraints, install_stride(f,c));
    foreach(e,Exp*,(yyvsp[0].TUPLE_DESCRIPTOR)->eq_constraints, install_eq(f,e,0));
    foreach(e,Exp*,(yyvsp[0].TUPLE_DESCRIPTOR)->geq_constraints, install_geq(f,e,0));
    foreach(c,strideConstraint*,(yyvsp[0].TUPLE_DESCRIPTOR)->stride_constraints, install_stride(f,c));
    delete (yyvsp[-3].TUPLE_DESCRIPTOR);
    delete (yyvsp[0].TUPLE_DESCRIPTOR);
#if 0
    fprintf(hpp_debug_file,"Alignment relation is: ");
    r->print_with_subs(hpp_debug_file,true);
#endif
    
    current_Declaration_Site = globalDecls;
    delete relationDecl; 
    
/* Finished building relation*/
    r->finalize();
    s->alignment = r; // store it

/* 
		Relation *w = new Relation;
		Relation *ddd = distribute_map[$6];
		assert(ddd && "Distribute the template before aligning anything with it");
		*w = Join(copy(*r),copy(*ddd));
		whole_map[$3] = w;
*/
		free((yyvsp[-4].VAR_NAME));
		free((yyvsp[-1].VAR_NAME));
}
#line 1513 "hppy.c" /* yacc.c:1646  */
    break;

  case 14:
#line 218 "../src/hppy.y" /* yacc.c:1646  */
    {

    template_info *ti = lookup_template((yyvsp[-5].VAR_NAME));
    ti->proc_name = (yyvsp[0].VAR_NAME);

// create a relation that maps template locations to processor locations;
    List<dist_info> *dl = (yyvsp[-3].DISTLIST);
    String template_name((yyvsp[-5].VAR_NAME)),proc_name((yyvsp[0].VAR_NAME));

    List<int> *tl = ti->bounds_list; 
    Relation tem = make_bounds_relation(tl);
    List<int> *pl = lookup_proc(proc_name);
    Relation proc = make_bounds_relation(pl);
    assert(tem.n_set() == dl->size());


#if 0
    Relation d = make_distribution_relation(*tl,*pl,*dl);

    d = Restrict_Domain(d, copy(tem));
    d = Restrict_Range(d, copy(proc));
    fprintf((hpp_debug_file),"map from template locations to processors: ");
    d.print_with_subs(hpp_debug_file);
#endif

    ti->dist_list = dl;
}
#line 1545 "hppy.c" /* yacc.c:1646  */
    break;

  case 15:
#line 248 "../src/hppy.y" /* yacc.c:1646  */
    { (yyvsp[-2].DISTLIST)->append(*(yyvsp[0].DISTINFO)); delete (yyvsp[0].DISTINFO); (yyval.DISTLIST) = (yyvsp[-2].DISTLIST); }
#line 1551 "hppy.c" /* yacc.c:1646  */
    break;

  case 16:
#line 249 "../src/hppy.y" /* yacc.c:1646  */
    { distribution_list *dl = new distribution_list;
	             dl->append(*(yyvsp[0].DISTINFO)); delete (yyvsp[0].DISTINFO); (yyval.DISTLIST) = dl; }
#line 1558 "hppy.c" /* yacc.c:1646  */
    break;

  case 17:
#line 253 "../src/hppy.y" /* yacc.c:1646  */
    { (yyval.DISTINFO) = new dist_info(block); }
#line 1564 "hppy.c" /* yacc.c:1646  */
    break;

  case 18:
#line 254 "../src/hppy.y" /* yacc.c:1646  */
    { (yyval.DISTINFO) =  new dist_info(cyclic,1); }
#line 1570 "hppy.c" /* yacc.c:1646  */
    break;

  case 19:
#line 255 "../src/hppy.y" /* yacc.c:1646  */
    { (yyval.DISTINFO) =  new dist_info(cyclic, (int)(yyvsp[-1].INT_VALUE)); }
#line 1576 "hppy.c" /* yacc.c:1646  */
    break;

  case 20:
#line 256 "../src/hppy.y" /* yacc.c:1646  */
    { (yyval.DISTINFO) =  new dist_info(star); }
#line 1582 "hppy.c" /* yacc.c:1646  */
    break;

  case 21:
#line 261 "../src/hppy.y" /* yacc.c:1646  */
    { currentTupleDescriptor = new tupleDescriptor; }
#line 1588 "hppy.c" /* yacc.c:1646  */
    break;

  case 22:
#line 263 "../src/hppy.y" /* yacc.c:1646  */
    {(yyval.TUPLE_DESCRIPTOR) = currentTupleDescriptor; }
#line 1594 "hppy.c" /* yacc.c:1646  */
    break;

  case 25:
#line 273 "../src/hppy.y" /* yacc.c:1646  */
    {         Declaration_Site *ds = defined((yyvsp[0].VAR_NAME));
	  if (!ds) 
            currentTupleDescriptor->extend((yyvsp[0].VAR_NAME));
	  else 
            currentTupleDescriptor->extend((yyvsp[0].VAR_NAME), new Exp(lookupScalar((yyvsp[0].VAR_NAME))));

	  free((yyvsp[0].VAR_NAME));

/*currentTupleDescriptor->extend($1);*/

 }
#line 1610 "hppy.c" /* yacc.c:1646  */
    break;

  case 26:
#line 285 "../src/hppy.y" /* yacc.c:1646  */
    {currentTupleDescriptor->extend(); }
#line 1616 "hppy.c" /* yacc.c:1646  */
    break;

  case 27:
#line 287 "../src/hppy.y" /* yacc.c:1646  */
    {
//	    if (!pickles)
		currentTupleDescriptor->extend((yyvsp[0].EXP)); 
	    pickles=0;
}
#line 1626 "hppy.c" /* yacc.c:1646  */
    break;

  case 28:
#line 294 "../src/hppy.y" /* yacc.c:1646  */
    {currentTupleDescriptor->extend((yyvsp[-2].EXP),(yyvsp[0].EXP)); }
#line 1632 "hppy.c" /* yacc.c:1646  */
    break;

  case 29:
#line 296 "../src/hppy.y" /* yacc.c:1646  */
    {currentTupleDescriptor->extend((yyvsp[-4].EXP),(yyvsp[-2].EXP),(yyvsp[0].INT_VALUE)); }
#line 1638 "hppy.c" /* yacc.c:1646  */
    break;

  case 30:
#line 301 "../src/hppy.y" /* yacc.c:1646  */
    { 
	List<int> *l = new List<int>;
	l->append((yyvsp[0].INT_VALUE));
	(yyval.INTEGER_LIST) = l;
    }
#line 1648 "hppy.c" /* yacc.c:1646  */
    break;

  case 31:
#line 307 "../src/hppy.y" /* yacc.c:1646  */
    {
		 (yyvsp[-2].INTEGER_LIST)->append((yyvsp[0].INT_VALUE));
		 (yyval.INTEGER_LIST) = (yyvsp[-2].INTEGER_LIST);
	     }
#line 1657 "hppy.c" /* yacc.c:1646  */
    break;

  case 32:
#line 315 "../src/hppy.y" /* yacc.c:1646  */
    { 
//fprintf(hpp_debug_file,"variable %s seen",$1);

//	    Declaration_Site *ds = defined($1);
//            if (!ds) {
//fprintf(hpp_debug_file,"...not declared, declaring",$1);

//	      currentTupleDescriptor->extend($1);
//	  }
//fprintf(hpp_debug_file,"...variable ref = %x\n",lookupScalar($1));
	  (yyval.EXP) = new Exp(lookupScalar((yyvsp[0].VAR_NAME)));
	  free((yyvsp[0].VAR_NAME));
	    pickles=1;

	}
#line 1677 "hppy.c" /* yacc.c:1646  */
    break;

  case 33:
#line 330 "../src/hppy.y" /* yacc.c:1646  */
    { (yyval.EXP) = (yyvsp[-1].EXP);}
#line 1683 "hppy.c" /* yacc.c:1646  */
    break;

  case 34:
#line 333 "../src/hppy.y" /* yacc.c:1646  */
    {(yyval.EXP) = new Exp((yyvsp[0].INT_VALUE));}
#line 1689 "hppy.c" /* yacc.c:1646  */
    break;

  case 35:
#line 334 "../src/hppy.y" /* yacc.c:1646  */
    {(yyval.EXP) = multiply((yyvsp[-1].INT_VALUE),(yyvsp[0].EXP));}
#line 1695 "hppy.c" /* yacc.c:1646  */
    break;

  case 36:
#line 335 "../src/hppy.y" /* yacc.c:1646  */
    { (yyval.EXP) = (yyvsp[0].EXP); }
#line 1701 "hppy.c" /* yacc.c:1646  */
    break;

  case 37:
#line 336 "../src/hppy.y" /* yacc.c:1646  */
    { (yyval.EXP) = ::negate((yyvsp[0].EXP));}
#line 1707 "hppy.c" /* yacc.c:1646  */
    break;

  case 38:
#line 337 "../src/hppy.y" /* yacc.c:1646  */
    { (yyval.EXP) = add((yyvsp[-2].EXP),(yyvsp[0].EXP));}
#line 1713 "hppy.c" /* yacc.c:1646  */
    break;

  case 39:
#line 338 "../src/hppy.y" /* yacc.c:1646  */
    { (yyval.EXP) = subtract((yyvsp[-2].EXP),(yyvsp[0].EXP));}
#line 1719 "hppy.c" /* yacc.c:1646  */
    break;

  case 40:
#line 339 "../src/hppy.y" /* yacc.c:1646  */
    { (yyval.EXP) = multiply((yyvsp[-2].EXP),(yyvsp[0].EXP));}
#line 1725 "hppy.c" /* yacc.c:1646  */
    break;


#line 1729 "hppy.c" /* yacc.c:1646  */
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
#line 344 "../src/hppy.y" /* yacc.c:1906  */



#include <hppl.c>

namespace omega {

symtabentry *lookup_symbol(const String &name) {

    for(nametabentry *n =NameHead; n != 0; n = n->namenext)
	if(strcmp(n->namest.symname, name) == 0)
	    return &(n->namest);
    fprintf(stderr,"\nAlignment directive found before symbol's declaration\n");
    assert(0 && "Symbol declaration not found");
    return 0;
}

template_info *lookup_template(const String &name) {
    for(List_Iterator<template_info *> i = templates; i; i++)
	if(name == (*i)->name) return (*i);
    assert(0 && "Template declaration not found");
    return 0;
}


template_info *add_template(const String &name, List<int> *l)
{ 
    template_info *ti = new template_info(name, l);
    templates.append(ti);
    return ti;
}


List<int> *lookup_proc(const String &name) {
    List<int> *l = proc_map(name);
    assert(l && "Processor declaration not found");
    return l;
}

List<int> *add_proc(const String &name, List<int> *l) {
    assert(l && "adding null processors?");
    proc_map[name] = l;
    return l;
}

Relation make_bounds_relation(List<int> *l)
{
       Relation template_rel(l->size());
       template_rel.add_and(); // allow and_with...
       for(int i = 1; i <= l->size(); i++) {
	   GEQ_Handle g = template_rel.and_with_GEQ();
	   Variable_ID v = template_rel.set_var(i);
	   g.update_coef(v,1);
	   g.update_const(-1);
	   g = template_rel.and_with_GEQ();
	   g.update_coef(v,-1);
	   g.update_const((*l)[i]);
       }
       return template_rel;
}


// Template list, processor list, distribution list
Relation make_distribution_relation(List<int> &tl, List<int> &pl,
				    distribution_list &dl) {


    Relation d(tl.length(), pl.length());
    F_Exists *ex = d.and_with()->add_exists();
    F_And *a = ex->add_and();

    int current_pdim = 1;

// Note that the following code does not really work for things like 
// block,block
    for(int dim = 1; dim <= dl.size(); dim++) {
	switch(dl[dim].type) {
	case star: continue;
	case block:
	    {
		assert(dl[dim].blocksize==0);
		int tsize = tl[dim]; // get size of template
                int psize = pl[current_pdim]; // get size of processors
		assert(tsize >= psize);
		int bsize = (int) ceil(((float)tsize)/psize);
		fprintf(hpp_debug_file,"dim %d block size: %d, tsize %d, psize %d\n",dim, bsize,tsize,psize);
		// Now constrain local elements to myproc*bsize...(mp+1)*bsize
		Variable_ID v = input_var(dim), u = output_var(current_pdim);
		
		GEQ_Handle g = a->add_GEQ();
//		Free_Var_Decl mp(String("myproc_")+itoS(dim));
		g.update_const(-1+bsize);
		g.update_coef(v,1);
		g.update_coef(u, -bsize);
//		g.update_coef(d.get_local(&mp), -bsize);
		g = a->add_GEQ();
		g.update_coef(v,-1);
		g.update_const(0);
		g.update_coef(u,bsize);
//		g.update_coef(d.get_local(&mp),bsize);
		g.finalize();
		current_pdim++;
	    }
	    break;
	case cyclic:
	    {
//		stride is  nprocs, lb is myproc, ub is ub
		int tsize = tl[dim]; // get size of template
                int psize = pl[dim]; // get size of processors
		int bsize = dl[dim].blocksize;  // get size of block
		assert(tsize >= psize);

		fprintf(hpp_debug_file,"dim %d: tsize %d, psize %d\n",dim, tsize,psize);

		GEQ_Handle g = a->add_GEQ();
		// stride: inp = outp*bsize + (bsize*nprocs)*alpha
		g.update_coef(ex->declare(), -(psize*bsize));
		g.update_coef(output_var(dim), -1);
		g.update_coef(input_var(dim), 1);
		g = a->add_GEQ();
		g.update_coef(ex->declare(), (psize*bsize));
		g.update_coef(output_var(dim), 1);
		g.update_coef(input_var(dim), -1);
		g.update_const(bsize-1);
		g = a->add_GEQ();
		g.update_coef(input_var(dim), -1);
		g.update_const(tsize);
		current_pdim++;
	    }
	}
    }
    d.finalize();
    return d;
}

} // end of namespace omega
