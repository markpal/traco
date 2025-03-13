/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2011 Free Software Foundation, Inc.
   
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
#define YYBISON_VERSION "2.5"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 268 of yacc.c  */
#line 46 "parser.y"

   #include <stdio.h>
   #include <stdlib.h>
   #include <string.h>
   #include <assert.h>
   
   #include <osl/macros.h>
   #include <osl/int.h>
   #include <osl/vector.h>
   #include <osl/relation.h>
   #include <osl/statement.h>
   #include <osl/strings.h>
   #include <osl/generic.h>
   #include <osl/body.h>
   #include <osl/extensions/arrays.h>
   #include <osl/extensions/extbody.h>
   #include <osl/scop.h>
   #include <clan/macros.h>
   #include <clan/vector.h>
   #include <clan/relation.h>
   #include <clan/relation_list.h>
   #include <clan/scop.h>
   #include <clan/symbol.h>
   #include <clan/statement.h>
   #include <clan/options.h>

   int  yylex(void);
   void yyerror(char*);
   void yyrestart(FILE*);
   void clan_scanner_initialize();
   void clan_scanner_reinitialize(int, int, int);
   void clan_scanner_free();

   void clan_parser_add_ld();
   int  clan_parser_nb_ld();
   void clan_parser_log(char*);
   void clan_parser_increment_loop_depth();
   void clan_parser_state_initialize(clan_options_p);
   osl_scop_p clan_parse(FILE*, clan_options_p);

   extern FILE*   yyin;                 /**< File to be read by Lex */
   extern int     scanner_parsing;      /**< Do we parse or not? */
   extern char*   scanner_latest_text;  /**< Latest text read by Lex */
   extern char*   scanner_clay;         /**< Data for the Clay software */
   extern int     scanner_line;         /**< Current scanned line */
   extern int     scanner_column;       /**< Scanned column (current) */
   extern int     scanner_column_LALR;  /**< Scanned column (before token) */
   extern int     scanner_scop_start;   /**< Scanned SCoP starting line */
   extern int     scanner_scop_end;     /**< Scanned SCoP ending line */
   extern int     scanner_pragma;       /**< Between SCoP pragmas or not? */

   // This is the "parser state", a collection of variables that vary
   // during the parsing and thanks to we can extract all SCoP informations.
   osl_scop_p     parser_scop;          /**< SCoP in construction */
   clan_symbol_p  parser_symbol;        /**< Top of the symbol table */
   int            parser_recording;     /**< Boolean: do we record or not? */
   char*          parser_record;        /**< What we record (statement body)*/
   int            parser_loop_depth;    /**< Current loop depth */
   int            parser_if_depth;      /**< Current if depth */
   int*           parser_scattering;    /**< Current statement scattering */
   clan_symbol_p* parser_iterators;     /**< Current iterator list */
   osl_relation_list_p parser_stack;    /**< Iteration domain stack */
   int*           parser_nb_local_dims; /**< Nb of local dims per depth */
   int            parser_nb_parameters; /**< Nb of parameter symbols */
   int*           parser_valid_else;    /**< Boolean: OK for else per depth */
   int            parser_indent;        /**< SCoP indentation */
   int            parser_error;         /**< Boolean: parse error */

   int            parser_ceild;         /**< Boolean: ceild used */
   int            parser_floord;        /**< Boolean: floord used */
   int            parser_min;           /**< Boolean: min used */
   int            parser_max;           /**< Boolean: max used */

   // Autoscop-relative variables.
   int            parser_autoscop;      /**< Boolean: autoscop in progress */
   int            parser_line_start;    /**< Autoscop start line, inclusive */
   int            parser_line_end;      /**< Autoscop end line, inclusive */
   int            parser_column_start;  /**< Autoscop start column, inclus. */
   int            parser_column_end;    /**< Autoscop end column, exclusive */

   // Ugly global variable to keep/read Clan options during parsing.
   clan_options_p  parser_options;

   // Variables to generate the extbody
   osl_extbody_p  parser_access_extbody; /**< The extbody struct */
   int            parser_access_start;   /**< Start coordinates */
   int            parser_access_length;  /**< Length of the access string*/


/* Line 268 of yacc.c  */
#line 161 "parser.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     CONSTANT = 258,
     STRING_LITERAL = 259,
     SIZEOF = 260,
     PTR_OP = 261,
     INC_OP = 262,
     DEC_OP = 263,
     LEFT_OP = 264,
     RIGHT_OP = 265,
     LE_OP = 266,
     GE_OP = 267,
     EQ_OP = 268,
     NE_OP = 269,
     AND_OP = 270,
     OR_OP = 271,
     MUL_ASSIGN = 272,
     DIV_ASSIGN = 273,
     MOD_ASSIGN = 274,
     ADD_ASSIGN = 275,
     SUB_ASSIGN = 276,
     LEFT_ASSIGN = 277,
     RIGHT_ASSIGN = 278,
     AND_ASSIGN = 279,
     XOR_ASSIGN = 280,
     OR_ASSIGN = 281,
     TYPE_NAME = 282,
     TYPEDEF = 283,
     EXTERN = 284,
     STATIC = 285,
     AUTO = 286,
     REGISTER = 287,
     INLINE = 288,
     RESTRICT = 289,
     CHAR = 290,
     SHORT = 291,
     INT = 292,
     LONG = 293,
     SIGNED = 294,
     UNSIGNED = 295,
     FLOAT = 296,
     DOUBLE = 297,
     CONST = 298,
     VOLATILE = 299,
     VOID = 300,
     BOOL = 301,
     COMPLEX = 302,
     IMAGINARY = 303,
     STRUCT = 304,
     UNION = 305,
     ENUM = 306,
     ELLIPSIS = 307,
     CASE = 308,
     DEFAULT = 309,
     IF = 310,
     ELSE = 311,
     SWITCH = 312,
     WHILE = 313,
     DO = 314,
     FOR = 315,
     GOTO = 316,
     CONTINUE = 317,
     BREAK = 318,
     RETURN = 319,
     IGNORE = 320,
     PRAGMA = 321,
     MIN = 322,
     MAX = 323,
     CEILD = 324,
     FLOORD = 325,
     ID = 326,
     INTEGER = 327
   };
#endif
/* Tokens.  */
#define CONSTANT 258
#define STRING_LITERAL 259
#define SIZEOF 260
#define PTR_OP 261
#define INC_OP 262
#define DEC_OP 263
#define LEFT_OP 264
#define RIGHT_OP 265
#define LE_OP 266
#define GE_OP 267
#define EQ_OP 268
#define NE_OP 269
#define AND_OP 270
#define OR_OP 271
#define MUL_ASSIGN 272
#define DIV_ASSIGN 273
#define MOD_ASSIGN 274
#define ADD_ASSIGN 275
#define SUB_ASSIGN 276
#define LEFT_ASSIGN 277
#define RIGHT_ASSIGN 278
#define AND_ASSIGN 279
#define XOR_ASSIGN 280
#define OR_ASSIGN 281
#define TYPE_NAME 282
#define TYPEDEF 283
#define EXTERN 284
#define STATIC 285
#define AUTO 286
#define REGISTER 287
#define INLINE 288
#define RESTRICT 289
#define CHAR 290
#define SHORT 291
#define INT 292
#define LONG 293
#define SIGNED 294
#define UNSIGNED 295
#define FLOAT 296
#define DOUBLE 297
#define CONST 298
#define VOLATILE 299
#define VOID 300
#define BOOL 301
#define COMPLEX 302
#define IMAGINARY 303
#define STRUCT 304
#define UNION 305
#define ENUM 306
#define ELLIPSIS 307
#define CASE 308
#define DEFAULT 309
#define IF 310
#define ELSE 311
#define SWITCH 312
#define WHILE 313
#define DO 314
#define FOR 315
#define GOTO 316
#define CONTINUE 317
#define BREAK 318
#define RETURN 319
#define IGNORE 320
#define PRAGMA 321
#define MIN 322
#define MAX 323
#define CEILD 324
#define FLOORD 325
#define ID 326
#define INTEGER 327




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 293 of yacc.c  */
#line 138 "parser.y"
 int value;                      /**< An integer value for integers */
         char* symbol;                   /**< A string for identifiers */
         osl_vector_p affex;             /**< An affine expression */
         osl_relation_p setex;           /**< A set of affine expressions */
         osl_relation_list_p list;       /**< List of array accesses */
         osl_statement_p stmt;           /**< List of statements */
       


/* Line 293 of yacc.c  */
#line 351 "parser.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 343 of yacc.c  */
#line 363 "parser.c"

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
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
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
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  7
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   740

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  97
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  91
/* YYNRULES -- Number of rules.  */
#define YYNRULES  252
/* YYNRULES -- Number of states.  */
#define YYNSTATES  426

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   327

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    84,     2,     2,     2,    85,    91,     2,
      75,    76,    86,    79,    81,    80,    90,    87,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    96,    78,
      82,    77,    83,    95,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    88,     2,    89,    93,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    73,    94,    74,    92,     2,     2,     2,
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
      65,    66,    67,    68,    69,    70,    71,    72
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     8,    11,    13,    16,    18,    21,
      22,    25,    27,    29,    31,    32,    35,    38,    42,    43,
      47,    48,    49,    50,    59,    60,    69,    70,    74,    75,
      82,    84,    85,    88,    91,    94,    97,   100,   106,   112,
     116,   120,   122,   126,   131,   137,   139,   141,   148,   150,
     152,   154,   161,   163,   170,   174,   178,   182,   186,   190,
     194,   199,   205,   207,   211,   213,   217,   219,   221,   225,
     227,   230,   233,   235,   239,   243,   245,   249,   253,   255,
     262,   264,   266,   268,   275,   277,   284,   286,   288,   290,
     292,   296,   298,   303,   307,   308,   314,   318,   322,   325,
     327,   331,   333,   336,   339,   342,   347,   349,   351,   353,
     355,   357,   359,   361,   363,   365,   370,   372,   376,   380,
     384,   386,   390,   394,   396,   400,   404,   406,   410,   414,
     418,   422,   424,   428,   432,   434,   438,   440,   444,   446,
     450,   452,   456,   458,   462,   464,   470,   472,   476,   478,
     480,   482,   484,   486,   488,   490,   492,   494,   496,   498,
     500,   502,   506,   508,   509,   513,   515,   517,   520,   522,
     525,   527,   530,   532,   534,   536,   538,   540,   542,   544,
     546,   548,   550,   552,   554,   556,   558,   560,   562,   564,
     570,   575,   578,   580,   582,   584,   587,   591,   594,   596,
     599,   601,   603,   607,   609,   612,   616,   621,   627,   630,
     632,   636,   638,   642,   644,   646,   649,   651,   653,   657,
     662,   666,   671,   676,   680,   682,   685,   688,   692,   694,
     697,   699,   703,   705,   709,   712,   715,   717,   719,   723,
     725,   728,   730,   732,   735,   739,   742,   746,   750,   755,
     758,   762,   766
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
      98,     0,    -1,    99,    -1,    98,    99,    -1,    98,    65,
      -1,    65,    -1,   100,    65,    -1,   101,    -1,   100,   101,
      -1,    -1,   102,   103,    -1,   105,    -1,   160,    -1,   108,
      -1,    -1,   104,   111,    -1,    73,    74,    -1,    73,   100,
      74,    -1,    -1,    56,   107,   103,    -1,    -1,    -1,    -1,
      55,    75,   128,    76,   109,   103,   110,   106,    -1,    -1,
      60,    75,   114,   117,   118,    76,   112,   121,    -1,    -1,
     120,   113,   121,    -1,    -1,   116,    71,   115,    77,   122,
      78,    -1,    37,    -1,    -1,   128,    78,    -1,   119,     7,
      -1,   119,     8,    -1,     7,   119,    -1,     8,   119,    -1,
     119,    77,   119,    79,    72,    -1,   119,    77,   119,    80,
      72,    -1,   119,    20,    72,    -1,   119,    21,    72,    -1,
      71,    -1,    75,   119,    76,    -1,    58,    75,    72,    76,
      -1,    60,    75,    78,    78,    76,    -1,   103,    -1,   133,
      -1,   123,    75,   122,    81,   122,    76,    -1,    67,    -1,
      68,    -1,   136,    -1,    67,    75,   124,    81,   124,    76,
      -1,   135,    -1,    68,    75,   125,    81,   125,    76,    -1,
     125,    82,   124,    -1,   124,    83,   125,    -1,   125,    11,
     124,    -1,   124,    12,   125,    -1,   132,    13,   132,    -1,
      75,   128,    76,    -1,    84,    75,   128,    76,    -1,   132,
      85,    72,    13,    72,    -1,   126,    -1,   127,    15,   126,
      -1,   127,    -1,   128,    16,   127,    -1,    71,    -1,    72,
      -1,    75,   132,    76,    -1,   129,    -1,    79,   129,    -1,
      80,   129,    -1,   130,    -1,   131,    86,   130,    -1,   131,
      87,   130,    -1,   131,    -1,   132,    79,   131,    -1,   132,
      80,   131,    -1,   132,    -1,   134,    75,   132,    81,    72,
      76,    -1,    69,    -1,    70,    -1,   132,    -1,    69,    75,
     132,    81,    72,    76,    -1,   132,    -1,    70,    75,   132,
      81,    72,    76,    -1,    71,    -1,     3,    -1,    72,    -1,
       4,    -1,    75,   159,    76,    -1,   137,    -1,   138,    88,
     132,    89,    -1,   138,    75,    76,    -1,    -1,   138,    75,
     139,   140,    76,    -1,   138,    90,    71,    -1,   138,     6,
      71,    -1,   138,   143,    -1,   156,    -1,   140,    81,   156,
      -1,   138,    -1,   143,   141,    -1,   142,   144,    -1,     5,
     141,    -1,     5,    75,   185,    76,    -1,    91,    -1,    86,
      -1,    79,    -1,    80,    -1,    92,    -1,    84,    -1,     7,
      -1,     8,    -1,   141,    -1,    75,   185,    76,   144,    -1,
     144,    -1,   145,    86,   144,    -1,   145,    87,   144,    -1,
     145,    85,   144,    -1,   145,    -1,   146,    79,   145,    -1,
     146,    80,   145,    -1,   146,    -1,   147,     9,   146,    -1,
     147,    10,   146,    -1,   147,    -1,   148,    82,   147,    -1,
     148,    83,   147,    -1,   148,    11,   147,    -1,   148,    12,
     147,    -1,   148,    -1,   149,    13,   148,    -1,   149,    14,
     148,    -1,   149,    -1,   150,    91,   149,    -1,   150,    -1,
     151,    93,   150,    -1,   151,    -1,   152,    94,   151,    -1,
     152,    -1,   153,    15,   152,    -1,   153,    -1,   154,    16,
     153,    -1,   154,    -1,   154,    95,   159,    96,   155,    -1,
     155,    -1,   141,   157,   156,    -1,    77,    -1,   158,    -1,
      17,    -1,    18,    -1,    19,    -1,    20,    -1,    21,    -1,
      22,    -1,    23,    -1,    24,    -1,    25,    -1,    26,    -1,
     156,    -1,   159,    81,   156,    -1,    78,    -1,    -1,   161,
     159,    78,    -1,   155,    -1,   164,    -1,   164,   163,    -1,
     165,    -1,   165,   163,    -1,   176,    -1,   176,   163,    -1,
      28,    -1,    29,    -1,    30,    -1,    31,    -1,    32,    -1,
      45,    -1,    35,    -1,    36,    -1,    37,    -1,    38,    -1,
      41,    -1,    42,    -1,    39,    -1,    40,    -1,   166,    -1,
     173,    -1,    27,    -1,   167,    71,    73,   168,    74,    -1,
     167,    73,   168,    74,    -1,   167,    71,    -1,    49,    -1,
      50,    -1,   169,    -1,   168,   169,    -1,   170,   171,    78,
      -1,   165,   170,    -1,   165,    -1,   176,   170,    -1,   176,
      -1,   172,    -1,   171,    81,   172,    -1,   177,    -1,    96,
     162,    -1,   177,    96,   162,    -1,    51,    73,   174,    74,
      -1,    51,    71,    73,   174,    74,    -1,    51,    71,    -1,
     175,    -1,   174,    81,   175,    -1,    71,    -1,    71,    77,
     162,    -1,    43,    -1,    44,    -1,   179,   178,    -1,   178,
      -1,    71,    -1,    75,   177,    76,    -1,   178,    88,   162,
      89,    -1,   178,    88,    89,    -1,   178,    75,   181,    76,
      -1,   178,    75,   184,    76,    -1,   178,    75,    76,    -1,
      86,    -1,    86,   180,    -1,    86,   179,    -1,    86,   180,
     179,    -1,   176,    -1,   180,   176,    -1,   182,    -1,   182,
      81,    52,    -1,   183,    -1,   182,    81,   183,    -1,   163,
     177,    -1,   163,   186,    -1,   163,    -1,    71,    -1,   184,
      81,    71,    -1,   170,    -1,   170,   186,    -1,   179,    -1,
     187,    -1,   179,   187,    -1,    75,   186,    76,    -1,    88,
      89,    -1,    88,   162,    89,    -1,   187,    88,    89,    -1,
     187,    88,   162,    89,    -1,    75,    76,    -1,    75,   181,
      76,    -1,   187,    75,    76,    -1,   187,    75,   181,    76,
      -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   228,   228,   229,   230,   231,   237,   293,   294,   302,
     302,   316,   317,   318,   319,   319,   349,   350,   361,   360,
     374,   383,   392,   382,   424,   423,   496,   495,   534,   533,
     550,   551,   556,   573,   574,   575,   576,   577,   578,   579,
     580,   584,   585,   590,   591,   596,   616,   623,   636,   637,
     649,   659,   679,   689,   712,   723,   734,   745,   756,   779,
     788,   803,   820,   826,   839,   845,   857,   887,   893,   904,
     910,   916,   927,   934,   958,   982,   989,   998,  1011,  1017,
    1029,  1030,  1035,  1041,  1053,  1059,  1076,  1111,  1113,  1115,
    1117,  1123,  1125,  1138,  1152,  1151,  1166,  1182,  1198,  1225,
    1227,  1235,  1237,  1261,  1263,  1265,  1270,  1271,  1272,  1273,
    1274,  1275,  1279,  1280,  1284,  1286,  1291,  1293,  1298,  1303,
    1311,  1313,  1318,  1326,  1328,  1333,  1341,  1343,  1348,  1353,
    1358,  1366,  1368,  1373,  1381,  1383,  1391,  1393,  1401,  1403,
    1411,  1413,  1421,  1423,  1431,  1433,  1442,  1449,  1479,  1481,
    1486,  1487,  1488,  1489,  1490,  1491,  1492,  1493,  1494,  1495,
    1499,  1501,  1509,  1516,  1516,  1587,  1591,  1592,  1593,  1594,
    1595,  1596,  1600,  1601,  1602,  1603,  1604,  1608,  1609,  1610,
    1611,  1612,  1613,  1614,  1615,  1616,  1617,  1618,  1619,  1623,
    1624,  1625,  1629,  1630,  1634,  1635,  1639,  1643,  1644,  1645,
    1646,  1650,  1651,  1655,  1656,  1657,  1661,  1662,  1663,  1667,
    1668,  1672,  1673,  1677,  1678,  1682,  1683,  1687,  1688,  1689,
    1690,  1691,  1692,  1693,  1697,  1698,  1699,  1700,  1704,  1705,
    1710,  1711,  1715,  1716,  1720,  1721,  1722,  1726,  1727,  1731,
    1732,  1736,  1737,  1738,  1742,  1743,  1744,  1745,  1746,  1747,
    1748,  1749,  1750
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "CONSTANT", "STRING_LITERAL", "SIZEOF",
  "PTR_OP", "INC_OP", "DEC_OP", "LEFT_OP", "RIGHT_OP", "LE_OP", "GE_OP",
  "EQ_OP", "NE_OP", "AND_OP", "OR_OP", "MUL_ASSIGN", "DIV_ASSIGN",
  "MOD_ASSIGN", "ADD_ASSIGN", "SUB_ASSIGN", "LEFT_ASSIGN", "RIGHT_ASSIGN",
  "AND_ASSIGN", "XOR_ASSIGN", "OR_ASSIGN", "TYPE_NAME", "TYPEDEF",
  "EXTERN", "STATIC", "AUTO", "REGISTER", "INLINE", "RESTRICT", "CHAR",
  "SHORT", "INT", "LONG", "SIGNED", "UNSIGNED", "FLOAT", "DOUBLE", "CONST",
  "VOLATILE", "VOID", "BOOL", "COMPLEX", "IMAGINARY", "STRUCT", "UNION",
  "ENUM", "ELLIPSIS", "CASE", "DEFAULT", "IF", "ELSE", "SWITCH", "WHILE",
  "DO", "FOR", "GOTO", "CONTINUE", "BREAK", "RETURN", "IGNORE", "PRAGMA",
  "MIN", "MAX", "CEILD", "FLOORD", "ID", "INTEGER", "'{'", "'}'", "'('",
  "')'", "'='", "';'", "'+'", "'-'", "','", "'<'", "'>'", "'!'", "'%'",
  "'*'", "'/'", "'['", "']'", "'.'", "'&'", "'~'", "'^'", "'|'", "'?'",
  "':'", "$accept", "scop_list", "scop", "statement_list",
  "statement_indented", "$@1", "statement", "$@2", "compound_statement",
  "selection_else_statement", "$@3", "selection_statement", "$@4", "$@5",
  "iteration_statement", "$@6", "$@7", "loop_initialization", "$@8",
  "loop_declaration", "loop_condition", "loop_stride", "idparent",
  "loop_infinite", "loop_body", "affine_minmax_expression", "minmax",
  "affine_min_expression", "affine_max_expression", "affine_relation",
  "affine_logical_and_expression", "affine_condition",
  "affine_primary_expression", "affine_unary_expression",
  "affine_multiplicative_expression", "affine_expression",
  "affine_ceildfloord_expression", "ceildfloord",
  "affine_ceild_expression", "affine_floord_expression",
  "primary_expression", "postfix_expression", "$@9",
  "argument_expression_list", "unary_expression", "unary_operator",
  "unary_increment_operator", "cast_expression",
  "multiplicative_expression", "additive_expression", "shift_expression",
  "relational_expression", "equality_expression", "and_expression",
  "exclusive_or_expression", "inclusive_or_expression",
  "logical_and_expression", "logical_or_expression",
  "conditional_expression", "assignment_expression", "assignment_operator",
  "assignment_rdwr_operator", "expression", "expression_statement", "$@10",
  "constant_expression", "declaration_specifiers",
  "storage_class_specifier", "type_specifier", "struct_or_union_specifier",
  "struct_or_union", "struct_declaration_list", "struct_declaration",
  "specifier_qualifier_list", "struct_declarator_list",
  "struct_declarator", "enum_specifier", "enumerator_list", "enumerator",
  "type_qualifier", "declarator", "direct_declarator", "pointer",
  "type_qualifier_list", "parameter_type_list", "parameter_list",
  "parameter_declaration", "identifier_list", "type_name",
  "abstract_declarator", "direct_abstract_declarator", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   123,   125,    40,    41,    61,    59,    43,
      45,    44,    60,    62,    33,    37,    42,    47,    91,    93,
      46,    38,   126,    94,   124,    63,    58
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    97,    98,    98,    98,    98,    99,   100,   100,   102,
     101,   103,   103,   103,   104,   103,   105,   105,   107,   106,
     106,   109,   110,   108,   112,   111,   113,   111,   115,   114,
     116,   116,   117,   118,   118,   118,   118,   118,   118,   118,
     118,   119,   119,   120,   120,   121,   122,   122,   123,   123,
     124,   124,   125,   125,   126,   126,   126,   126,   126,   126,
     126,   126,   127,   127,   128,   128,   129,   129,   129,   130,
     130,   130,   131,   131,   131,   132,   132,   132,   133,   133,
     134,   134,   135,   135,   136,   136,   137,   137,   137,   137,
     137,   138,   138,   138,   139,   138,   138,   138,   138,   140,
     140,   141,   141,   141,   141,   141,   142,   142,   142,   142,
     142,   142,   143,   143,   144,   144,   145,   145,   145,   145,
     146,   146,   146,   147,   147,   147,   148,   148,   148,   148,
     148,   149,   149,   149,   150,   150,   151,   151,   152,   152,
     153,   153,   154,   154,   155,   155,   156,   156,   157,   157,
     158,   158,   158,   158,   158,   158,   158,   158,   158,   158,
     159,   159,   160,   161,   160,   162,   163,   163,   163,   163,
     163,   163,   164,   164,   164,   164,   164,   165,   165,   165,
     165,   165,   165,   165,   165,   165,   165,   165,   165,   166,
     166,   166,   167,   167,   168,   168,   169,   170,   170,   170,
     170,   171,   171,   172,   172,   172,   173,   173,   173,   174,
     174,   175,   175,   176,   176,   177,   177,   178,   178,   178,
     178,   178,   178,   178,   179,   179,   179,   179,   180,   180,
     181,   181,   182,   182,   183,   183,   183,   184,   184,   185,
     185,   186,   186,   186,   187,   187,   187,   187,   187,   187,
     187,   187,   187
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     2,     1,     2,     1,     2,     0,
       2,     1,     1,     1,     0,     2,     2,     3,     0,     3,
       0,     0,     0,     8,     0,     8,     0,     3,     0,     6,
       1,     0,     2,     2,     2,     2,     2,     5,     5,     3,
       3,     1,     3,     4,     5,     1,     1,     6,     1,     1,
       1,     6,     1,     6,     3,     3,     3,     3,     3,     3,
       4,     5,     1,     3,     1,     3,     1,     1,     3,     1,
       2,     2,     1,     3,     3,     1,     3,     3,     1,     6,
       1,     1,     1,     6,     1,     6,     1,     1,     1,     1,
       3,     1,     4,     3,     0,     5,     3,     3,     2,     1,
       3,     1,     2,     2,     2,     4,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     4,     1,     3,     3,     3,
       1,     3,     3,     1,     3,     3,     1,     3,     3,     3,
       3,     1,     3,     3,     1,     3,     1,     3,     1,     3,
       1,     3,     1,     3,     1,     5,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     1,     0,     3,     1,     1,     2,     1,     2,
       1,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     5,
       4,     2,     1,     1,     1,     2,     3,     2,     1,     2,
       1,     1,     3,     1,     2,     3,     4,     5,     2,     1,
       3,     1,     3,     1,     1,     2,     1,     1,     3,     4,
       3,     4,     4,     3,     1,     2,     2,     3,     1,     2,
       1,     3,     1,     3,     2,     2,     1,     1,     3,     1,
       2,     1,     1,     2,     3,     2,     3,     3,     4,     2,
       3,     3,     4
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       9,     5,     9,     2,     9,     7,   163,     1,     4,     3,
       6,     8,     0,     9,   162,    10,     0,    11,    13,    12,
       0,     0,    16,     9,     0,     0,    15,    26,    87,    89,
       0,   112,   113,    86,    88,     0,   108,   109,   111,   107,
     106,   110,    91,   101,   114,     0,     0,   116,   120,   123,
     126,   131,   134,   136,   138,   140,   142,   144,   146,   160,
       0,     0,     0,     0,     0,    66,    67,     0,     0,     0,
       0,     0,     0,    62,    64,     0,    69,    72,    75,    82,
      52,    50,    17,     0,    31,   163,     0,   104,   188,   178,
     179,   180,   181,   184,   185,   182,   183,   213,   214,   177,
     192,   193,     0,     0,   198,   186,     0,   239,   187,   200,
       0,     0,    94,     0,     0,    98,   150,   151,   152,   153,
     154,   155,   156,   157,   158,   159,   148,     0,   149,   114,
     103,     0,   102,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   164,     0,     0,     0,     0,     0,     0,    82,
       0,    70,    71,     0,     0,     0,     0,     0,     0,     0,
      21,     0,     0,     0,     0,     0,     0,     0,    30,     0,
       0,     0,    45,    27,     0,   208,     0,    90,   197,   191,
       0,     0,   224,     0,   241,   240,   242,   199,     0,    97,
      93,     0,     0,    96,   147,   119,   117,   118,   121,   122,
     124,   125,   129,   130,   127,   128,   132,   133,   135,   137,
     139,   141,   143,     0,   161,     0,    84,     0,    82,     0,
       0,    59,    68,     0,     0,    57,    55,    56,    54,    63,
      65,   163,    73,    74,    58,    76,    77,     0,    43,     0,
       0,     0,    28,   105,     0,   211,     0,   209,     0,     0,
     194,     0,   172,   173,   174,   175,   176,   249,   236,   166,
     168,   170,     0,   230,   232,     0,   228,   226,   225,   245,
     165,     0,   243,     0,     0,   115,     0,    99,    92,     0,
       0,     0,     0,     0,    60,    22,     0,    44,     0,     0,
      41,     0,     0,     0,    32,     0,     0,     0,   206,     0,
       0,   190,   195,   217,     0,     0,     0,   201,   203,   216,
       0,     0,   234,   241,   235,   167,   169,   171,   250,     0,
     244,   229,   227,   246,   251,     0,   247,     0,    95,     0,
     145,     0,     0,     0,     0,    20,    61,    35,    36,     0,
      24,    33,    34,     0,     0,     0,     0,   207,   212,   210,
     189,     0,   204,   196,     0,     0,     0,     0,   215,   231,
     233,   252,   248,   100,    51,    53,    83,    85,    18,    23,
      42,   163,    39,    40,     0,    48,    49,    80,    81,     0,
       0,    78,    46,     0,   218,   202,   205,   237,   223,     0,
       0,   220,     0,   163,    25,     0,     0,    29,     0,     0,
     221,   222,     0,   219,    19,    37,    38,     0,     0,   238,
       0,     0,     0,     0,    47,    79
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,     4,     5,     6,   182,    16,    17,   379,
     403,    18,   241,   345,    26,   381,    85,   180,   305,   181,
     250,   302,   303,    27,   183,   389,   390,    71,    72,    73,
      74,    75,    76,    77,    78,    79,   392,   393,    80,    81,
      42,    43,   201,   286,   129,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
     127,   128,   103,    19,    20,   281,   268,   269,   104,   105,
     106,   259,   260,   261,   316,   317,   108,   256,   257,   109,
     318,   319,   320,   278,   272,   273,   274,   400,   110,   275,
     196
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -261
static const yytype_int16 yypact[] =
{
      -5,  -261,    53,  -261,    -2,  -261,   211,  -261,  -261,  -261,
    -261,  -261,   -32,    57,  -261,  -261,   117,  -261,  -261,  -261,
     345,   331,  -261,   127,     5,    92,  -261,  -261,  -261,  -261,
     355,  -261,  -261,  -261,  -261,   201,  -261,  -261,  -261,  -261,
    -261,  -261,  -261,    42,   365,   345,   373,  -261,   251,   168,
     304,   137,   310,    94,   128,   113,   217,    19,  -261,  -261,
     230,   151,   189,   213,   227,  -261,  -261,   331,   -39,   -39,
     232,    -7,     4,  -261,   271,    39,  -261,  -261,   246,   131,
    -261,  -261,  -261,   228,   114,   211,   201,  -261,  -261,  -261,
    -261,  -261,  -261,  -261,  -261,  -261,  -261,  -261,  -261,  -261,
    -261,  -261,   183,   -19,   458,  -261,   206,   182,  -261,   458,
     233,   258,   264,   203,   274,  -261,  -261,  -261,  -261,  -261,
    -261,  -261,  -261,  -261,  -261,  -261,  -261,   345,  -261,  -261,
    -261,   345,  -261,   345,   345,   345,   345,   345,   345,   345,
     345,   345,   345,   345,   345,   345,   345,   345,   345,   345,
     345,   345,  -261,   345,   224,   660,   203,   203,    43,   111,
     203,  -261,  -261,   331,   660,   660,   224,   224,   331,   331,
    -261,   203,   203,   203,   203,   203,   279,   285,  -261,   286,
     331,   308,  -261,  -261,   299,   319,   338,  -261,  -261,   323,
     458,   501,    -3,    66,    78,  -261,   101,  -261,   345,  -261,
    -261,   345,   123,  -261,  -261,  -261,  -261,  -261,   251,   251,
     168,   168,   304,   304,   304,   304,   137,   137,   310,    94,
     128,   113,   217,   -50,  -261,   333,   325,   340,   325,   276,
     290,  -261,  -261,   240,    50,  -261,  -261,  -261,  -261,  -261,
     271,   211,  -261,  -261,   325,   246,   246,   415,  -261,   362,
     190,     6,  -261,  -261,   338,   363,   -20,  -261,   458,   598,
    -261,    88,  -261,  -261,  -261,  -261,  -261,  -261,   107,   676,
     676,   676,   367,   370,  -261,   378,  -261,  -261,    -3,  -261,
    -261,   366,   101,   579,   226,  -261,    80,  -261,  -261,   345,
     224,   660,   384,   386,  -261,  -261,   390,  -261,    10,    10,
    -261,    10,   387,    31,  -261,   395,   -16,   345,  -261,   338,
     624,  -261,  -261,  -261,   -41,   345,   244,  -261,   377,   125,
     178,   439,  -261,    93,  -261,  -261,  -261,  -261,  -261,   650,
    -261,  -261,  -261,  -261,  -261,   410,  -261,   398,  -261,   345,
    -261,   416,   428,   429,   430,   435,  -261,  -261,  -261,   436,
    -261,  -261,  -261,   441,   444,    10,   523,  -261,  -261,  -261,
    -261,   442,  -261,  -261,    88,   345,   529,   255,   125,  -261,
    -261,  -261,  -261,  -261,  -261,  -261,  -261,  -261,  -261,  -261,
    -261,   211,  -261,  -261,   328,  -261,  -261,  -261,  -261,   433,
     445,   325,  -261,   446,  -261,  -261,  -261,  -261,  -261,   443,
     142,  -261,   434,   211,  -261,   450,   452,  -261,   523,   203,
    -261,  -261,   455,  -261,  -261,  -261,  -261,   453,   293,  -261,
     523,   463,   471,   472,  -261,  -261
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -261,  -261,   515,   536,    33,  -261,    -6,  -261,  -261,  -261,
    -261,  -261,  -261,  -261,  -261,  -261,  -261,  -261,  -261,  -261,
    -261,  -261,  -128,  -261,   172,  -153,  -261,  -148,  -144,   394,
     385,   -51,   344,   247,   248,   -66,  -261,  -261,  -261,  -261,
    -261,  -261,  -261,  -261,   -18,  -261,   512,   -38,   296,   311,
     225,   316,   417,   437,   427,   432,   438,  -261,  -179,  -124,
    -261,  -261,   -11,  -261,  -261,  -240,   124,  -261,  -149,  -261,
    -261,   324,  -232,   -22,  -261,   219,  -261,   332,   287,  -167,
    -242,     8,   -99,  -261,  -260,  -261,   256,  -261,   511,  -103,
    -184
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -85
static const yytype_int16 yytable[] =
{
      15,   159,    44,   204,   195,   164,   225,   130,   194,    60,
     282,   227,    87,   107,   280,   166,   158,    44,   237,   238,
     235,   236,   169,   335,   271,   276,   322,   312,   132,   224,
     313,   153,    65,    66,   314,   150,   160,    11,   351,   352,
      97,    98,   270,    21,   337,   192,   289,   202,   111,    31,
      32,   353,   354,     7,   308,   169,    11,   187,   357,   169,
       1,   309,   153,    10,   107,   309,   169,   358,    44,    28,
      29,    30,   361,    31,    32,   362,   165,   287,   312,   361,
      83,   300,   188,   192,   304,   301,   167,   197,   226,   228,
     229,   230,   194,   277,   233,   205,   206,   207,   228,   228,
     226,   226,   271,   271,   271,   280,   399,   244,   355,    44,
     340,   331,   234,    44,   151,   170,   271,   112,     8,   231,
     270,   270,   270,   -84,   173,   396,   294,   402,   280,   251,
     113,    22,   114,    44,   270,    44,   280,    33,    34,   282,
     223,    35,   341,   -84,   173,    36,    37,   342,   140,   141,
      38,   178,    39,   191,   271,   279,   338,    40,    41,   313,
     285,   339,   271,   314,   313,   324,   193,    84,   321,   323,
     347,   348,   270,   349,   192,    24,   283,    25,   313,   332,
     270,   193,   321,    44,   315,   146,   280,   232,   280,   284,
     174,   175,   179,   192,   -84,   193,   176,   298,   299,   271,
     366,    82,   174,   175,    28,    29,    30,   148,    31,    32,
     174,   175,   288,   367,   -84,   373,   176,   270,   411,   142,
     143,   147,   323,   412,   226,   228,   154,   384,    88,    28,
      29,    30,   149,    31,    32,   295,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   136,   137,   313,
     100,   101,   102,   314,   185,   417,   186,   191,    28,    29,
      30,   300,    31,    32,   155,   301,    12,   422,   192,   -14,
     193,   -14,    33,    34,    65,    66,    35,   189,   160,   190,
      36,    37,    68,    69,    13,    38,   168,    39,   156,    14,
     391,    61,    40,    41,    64,    65,    66,    33,    34,   160,
     177,    35,   157,    68,    69,    36,    37,   163,   152,   198,
      38,   153,    39,   138,   139,   336,   232,    40,    41,   174,
     175,    44,   363,   144,   145,   364,    33,    34,   368,   199,
      35,   368,   171,   172,    36,    37,   133,   134,   135,    38,
     200,    39,   391,   418,   401,   203,    40,    41,    28,    29,
      30,   247,    31,    32,   391,   174,   175,   292,    28,    29,
      30,   248,    31,    32,   249,   212,   213,   214,   215,   174,
     175,   293,   174,   175,   421,   253,    28,    29,    30,   252,
      31,    32,   116,   117,   118,   119,   120,   121,   122,   123,
     124,   125,   254,   325,   326,   327,   258,   414,    61,    62,
      63,    64,    65,    66,   174,   175,    67,   405,   406,   255,
      68,    69,   161,   162,   290,    70,    33,    34,   242,   243,
      35,   291,   245,   246,    36,    37,    33,    34,   296,    38,
      86,    39,   208,   209,    36,    37,    40,    41,   297,    38,
     307,    39,   126,   328,    33,    34,    40,    41,   131,   210,
     211,   329,    36,    37,   330,   333,   343,    38,   344,    39,
     216,   217,   346,   350,    40,    41,    88,   262,   263,   264,
     265,   266,   356,   365,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,    88,   371,   372,   100,   101,
     102,   378,   374,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    99,   375,   376,   377,   100,   101,   102,
     313,   407,   380,   382,   321,   267,   383,     9,   394,   410,
     408,   409,   415,   413,   416,   192,   419,   193,    88,   262,
     263,   264,   265,   266,   420,   423,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   424,   425,    23,
     100,   101,   102,   404,   240,   115,    88,   262,   263,   264,
     265,   266,   239,   218,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   220,   191,   267,   100,   101,
     102,   221,   310,   395,   219,   370,   306,   192,   222,   193,
     385,   386,   387,   388,    65,    66,   359,   184,   160,     0,
     397,     0,    68,    69,     0,   398,    88,   262,   263,   264,
     265,   266,     0,     0,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,    88,     0,     0,   100,   101,
     102,     0,     0,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    99,     0,     0,     0,   100,   101,   102,
       0,    88,     0,     0,     0,   334,     0,     0,     0,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
       0,     0,   311,   100,   101,   102,     0,    88,   262,   263,
     264,   265,   266,     0,     0,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,     0,     0,   360,   100,
     101,   102,   369,    88,   262,   263,   264,   265,   266,     0,
       0,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,     0,     0,     0,   100,   101,   102,    62,    63,
       0,    65,    66,     0,     0,   160,     0,     0,     0,    68,
      69
};

#define yypact_value_is_default(yystate) \
  ((yystate) == (-261))

#define yytable_value_is_error(yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
       6,    67,    20,   127,   107,    12,   154,    45,   107,    20,
     194,   155,    30,    35,   193,    11,    67,    35,   166,   167,
     164,   165,    16,   283,   191,   192,   268,   259,    46,   153,
      71,    81,    71,    72,    75,    16,    75,     4,     7,     8,
      43,    44,   191,    75,   284,    86,    96,   113,     6,     7,
       8,    20,    21,     0,    74,    16,    23,    76,    74,    16,
      65,    81,    81,    65,    86,    81,    16,   307,    86,     3,
       4,     5,   314,     7,     8,   315,    83,   201,   310,   321,
      75,    71,   104,    86,    78,    75,    82,   109,   154,   155,
     156,   157,   191,   192,   160,   133,   134,   135,   164,   165,
     166,   167,   269,   270,   271,   284,   366,   173,    77,   127,
     289,   278,   163,   131,    95,    76,   283,    75,    65,    76,
     269,   270,   271,    12,    13,   365,    76,   367,   307,   180,
      88,    74,    90,   151,   283,   153,   315,    71,    72,   323,
     151,    75,   290,    12,    13,    79,    80,   291,    11,    12,
      84,    37,    86,    75,   321,    89,    76,    91,    92,    71,
     198,    81,   329,    75,    71,   268,    88,    75,    75,   268,
     298,   299,   321,   301,    86,    58,    75,    60,    71,   278,
     329,    88,    75,   201,    96,    91,   365,    76,   367,    88,
      79,    80,    78,    86,    83,    88,    85,     7,     8,   366,
      75,    74,    79,    80,     3,     4,     5,    94,     7,     8,
      79,    80,    89,    88,    83,   339,    85,   366,    76,    82,
      83,    93,   321,    81,   290,   291,    75,   355,    27,     3,
       4,     5,    15,     7,     8,   241,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    79,    80,    71,
      49,    50,    51,    75,    71,   408,    73,    75,     3,     4,
       5,    71,     7,     8,    75,    75,    55,   420,    86,    58,
      88,    60,    71,    72,    71,    72,    75,    71,    75,    73,
      79,    80,    79,    80,    73,    84,    15,    86,    75,    78,
     356,    67,    91,    92,    70,    71,    72,    71,    72,    75,
      72,    75,    75,    79,    80,    79,    80,    75,    78,    76,
      84,    81,    86,     9,    10,    89,    76,    91,    92,    79,
      80,   339,    78,    13,    14,    81,    71,    72,   320,    71,
      75,   323,    86,    87,    79,    80,    85,    86,    87,    84,
      76,    86,   408,   409,    89,    71,    91,    92,     3,     4,
       5,    72,     7,     8,   420,    79,    80,    81,     3,     4,
       5,    76,     7,     8,    78,   140,   141,   142,   143,    79,
      80,    81,    79,    80,    81,    76,     3,     4,     5,    71,
       7,     8,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    73,   269,   270,   271,    73,   403,    67,    68,
      69,    70,    71,    72,    79,    80,    75,    79,    80,    71,
      79,    80,    68,    69,    81,    84,    71,    72,   171,   172,
      75,    81,   174,   175,    79,    80,    71,    72,    13,    84,
      75,    86,   136,   137,    79,    80,    91,    92,    76,    84,
      77,    86,    77,    76,    71,    72,    91,    92,    75,   138,
     139,    81,    79,    80,    76,    89,    72,    84,    72,    86,
     144,   145,    72,    76,    91,    92,    27,    28,    29,    30,
      31,    32,    77,    96,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    27,    76,    89,    49,    50,
      51,    56,    76,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    76,    76,    76,    49,    50,    51,
      71,    78,    76,    72,    75,    76,    72,     2,    76,    76,
      75,    75,    72,    89,    72,    86,    71,    88,    27,    28,
      29,    30,    31,    32,    81,    72,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    76,    76,    13,
      49,    50,    51,   381,   169,    43,    27,    28,    29,    30,
      31,    32,   168,   146,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,   148,    75,    76,    49,    50,
      51,   149,   258,   364,   147,   329,   254,    86,   150,    88,
      67,    68,    69,    70,    71,    72,   309,    86,    75,    -1,
      71,    -1,    79,    80,    -1,    76,    27,    28,    29,    30,
      31,    32,    -1,    -1,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    27,    -1,    -1,    49,    50,
      51,    -1,    -1,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    -1,    -1,    -1,    49,    50,    51,
      -1,    27,    -1,    -1,    -1,    76,    -1,    -1,    -1,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      -1,    -1,    74,    49,    50,    51,    -1,    27,    28,    29,
      30,    31,    32,    -1,    -1,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    -1,    -1,    74,    49,
      50,    51,    52,    27,    28,    29,    30,    31,    32,    -1,
      -1,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    -1,    -1,    -1,    49,    50,    51,    68,    69,
      -1,    71,    72,    -1,    -1,    75,    -1,    -1,    -1,    79,
      80
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    65,    98,    99,   100,   101,   102,     0,    65,    99,
      65,   101,    55,    73,    78,   103,   104,   105,   108,   160,
     161,    75,    74,   100,    58,    60,   111,   120,     3,     4,
       5,     7,     8,    71,    72,    75,    79,    80,    84,    86,
      91,    92,   137,   138,   141,   142,   143,   144,   145,   146,
     147,   148,   149,   150,   151,   152,   153,   154,   155,   156,
     159,    67,    68,    69,    70,    71,    72,    75,    79,    80,
      84,   124,   125,   126,   127,   128,   129,   130,   131,   132,
     135,   136,    74,    75,    75,   113,    75,   141,    27,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      49,    50,    51,   159,   165,   166,   167,   170,   173,   176,
     185,     6,    75,    88,    90,   143,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    77,   157,   158,   141,
     144,    75,   141,    85,    86,    87,    79,    80,     9,    10,
      11,    12,    82,    83,    13,    14,    91,    93,    94,    15,
      16,    95,    78,    81,    75,    75,    75,    75,   128,   132,
      75,   129,   129,    75,    12,    83,    11,    82,    15,    16,
      76,    86,    87,    13,    79,    80,    85,    72,    37,    78,
     114,   116,   103,   121,   185,    71,    73,    76,   170,    71,
      73,    75,    86,    88,   179,   186,   187,   170,    76,    71,
      76,   139,   132,    71,   156,   144,   144,   144,   145,   145,
     146,   146,   147,   147,   147,   147,   148,   148,   149,   150,
     151,   152,   153,   159,   156,   124,   132,   125,   132,   132,
     132,    76,    76,   132,   128,   125,   125,   124,   124,   126,
     127,   109,   130,   130,   132,   131,   131,    72,    76,    78,
     117,   128,    71,    76,    73,    71,   174,   175,    73,   168,
     169,   170,    28,    29,    30,    31,    32,    76,   163,   164,
     165,   176,   181,   182,   183,   186,   176,   179,   180,    89,
     155,   162,   187,    75,    88,   144,   140,   156,    89,    96,
      81,    81,    81,    81,    76,   103,    13,    76,     7,     8,
      71,    75,   118,   119,    78,   115,   174,    77,    74,    81,
     168,    74,   169,    71,    75,    96,   171,   172,   177,   178,
     179,    75,   177,   179,   186,   163,   163,   163,    76,    81,
      76,   176,   179,    89,    76,   181,    89,   162,    76,    81,
     155,   124,   125,    72,    72,   110,    72,   119,   119,   119,
      76,     7,     8,    20,    21,    77,    77,    74,   162,   175,
      74,   177,   162,    78,    81,    96,    75,    88,   178,    52,
     183,    76,    89,   156,    76,    76,    76,    76,    56,   106,
      76,   112,    72,    72,   119,    67,    68,    69,    70,   122,
     123,   132,   133,   134,    76,   172,   162,    71,    76,   181,
     184,    89,   162,   107,   121,    79,    80,    78,    75,    75,
      76,    76,    81,    89,   103,    72,    72,   122,   132,    71,
      81,    81,   122,    72,    76,    76
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* This macro is provided for backward compatibility. */

#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

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
#ifndef	YYINITDEPTH
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
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
  YYSIZE_T yysize0 = yytnamerr (0, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  YYSIZE_T yysize1;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = 0;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
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
                yysize1 = yysize + yytnamerr (0, yytname[yyx]);
                if (! (yysize <= yysize1
                       && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                  return 2;
                yysize = yysize1;
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

  yysize1 = yysize + yystrlen (yyformat);
  if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
    return 2;
  yysize = yysize1;

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

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {
      case 71: /* "ID" */

/* Line 1391 of yacc.c  */
#line 213 "parser.y"
	{ free((yyvaluep->symbol)); };

/* Line 1391 of yacc.c  */
#line 1804 "parser.c"
	break;
      case 100: /* "statement_list" */

/* Line 1391 of yacc.c  */
#line 216 "parser.y"
	{ osl_statement_free((yyvaluep->stmt)); };

/* Line 1391 of yacc.c  */
#line 1813 "parser.c"
	break;
      case 101: /* "statement_indented" */

/* Line 1391 of yacc.c  */
#line 216 "parser.y"
	{ osl_statement_free((yyvaluep->stmt)); };

/* Line 1391 of yacc.c  */
#line 1822 "parser.c"
	break;
      case 103: /* "statement" */

/* Line 1391 of yacc.c  */
#line 216 "parser.y"
	{ osl_statement_free((yyvaluep->stmt)); };

/* Line 1391 of yacc.c  */
#line 1831 "parser.c"
	break;
      case 105: /* "compound_statement" */

/* Line 1391 of yacc.c  */
#line 216 "parser.y"
	{ osl_statement_free((yyvaluep->stmt)); };

/* Line 1391 of yacc.c  */
#line 1840 "parser.c"
	break;
      case 106: /* "selection_else_statement" */

/* Line 1391 of yacc.c  */
#line 216 "parser.y"
	{ osl_statement_free((yyvaluep->stmt)); };

/* Line 1391 of yacc.c  */
#line 1849 "parser.c"
	break;
      case 108: /* "selection_statement" */

/* Line 1391 of yacc.c  */
#line 216 "parser.y"
	{ osl_statement_free((yyvaluep->stmt)); };

/* Line 1391 of yacc.c  */
#line 1858 "parser.c"
	break;
      case 111: /* "iteration_statement" */

/* Line 1391 of yacc.c  */
#line 216 "parser.y"
	{ osl_statement_free((yyvaluep->stmt)); };

/* Line 1391 of yacc.c  */
#line 1867 "parser.c"
	break;
      case 119: /* "idparent" */

/* Line 1391 of yacc.c  */
#line 213 "parser.y"
	{ free((yyvaluep->symbol)); };

/* Line 1391 of yacc.c  */
#line 1876 "parser.c"
	break;
      case 121: /* "loop_body" */

/* Line 1391 of yacc.c  */
#line 216 "parser.y"
	{ osl_statement_free((yyvaluep->stmt)); };

/* Line 1391 of yacc.c  */
#line 1885 "parser.c"
	break;
      case 129: /* "affine_primary_expression" */

/* Line 1391 of yacc.c  */
#line 214 "parser.y"
	{ osl_vector_free((yyvaluep->affex)); };

/* Line 1391 of yacc.c  */
#line 1894 "parser.c"
	break;
      case 130: /* "affine_unary_expression" */

/* Line 1391 of yacc.c  */
#line 214 "parser.y"
	{ osl_vector_free((yyvaluep->affex)); };

/* Line 1391 of yacc.c  */
#line 1903 "parser.c"
	break;
      case 131: /* "affine_multiplicative_expression" */

/* Line 1391 of yacc.c  */
#line 214 "parser.y"
	{ osl_vector_free((yyvaluep->affex)); };

/* Line 1391 of yacc.c  */
#line 1912 "parser.c"
	break;
      case 132: /* "affine_expression" */

/* Line 1391 of yacc.c  */
#line 214 "parser.y"
	{ osl_vector_free((yyvaluep->affex)); };

/* Line 1391 of yacc.c  */
#line 1921 "parser.c"
	break;
      case 133: /* "affine_ceildfloord_expression" */

/* Line 1391 of yacc.c  */
#line 214 "parser.y"
	{ osl_vector_free((yyvaluep->affex)); };

/* Line 1391 of yacc.c  */
#line 1930 "parser.c"
	break;
      case 135: /* "affine_ceild_expression" */

/* Line 1391 of yacc.c  */
#line 214 "parser.y"
	{ osl_vector_free((yyvaluep->affex)); };

/* Line 1391 of yacc.c  */
#line 1939 "parser.c"
	break;
      case 136: /* "affine_floord_expression" */

/* Line 1391 of yacc.c  */
#line 214 "parser.y"
	{ osl_vector_free((yyvaluep->affex)); };

/* Line 1391 of yacc.c  */
#line 1948 "parser.c"
	break;
      case 137: /* "primary_expression" */

/* Line 1391 of yacc.c  */
#line 215 "parser.y"
	{ osl_relation_list_free((yyvaluep->list)); };

/* Line 1391 of yacc.c  */
#line 1957 "parser.c"
	break;
      case 138: /* "postfix_expression" */

/* Line 1391 of yacc.c  */
#line 215 "parser.y"
	{ osl_relation_list_free((yyvaluep->list)); };

/* Line 1391 of yacc.c  */
#line 1966 "parser.c"
	break;
      case 140: /* "argument_expression_list" */

/* Line 1391 of yacc.c  */
#line 215 "parser.y"
	{ osl_relation_list_free((yyvaluep->list)); };

/* Line 1391 of yacc.c  */
#line 1975 "parser.c"
	break;
      case 141: /* "unary_expression" */

/* Line 1391 of yacc.c  */
#line 215 "parser.y"
	{ osl_relation_list_free((yyvaluep->list)); };

/* Line 1391 of yacc.c  */
#line 1984 "parser.c"
	break;
      case 144: /* "cast_expression" */

/* Line 1391 of yacc.c  */
#line 215 "parser.y"
	{ osl_relation_list_free((yyvaluep->list)); };

/* Line 1391 of yacc.c  */
#line 1993 "parser.c"
	break;
      case 145: /* "multiplicative_expression" */

/* Line 1391 of yacc.c  */
#line 215 "parser.y"
	{ osl_relation_list_free((yyvaluep->list)); };

/* Line 1391 of yacc.c  */
#line 2002 "parser.c"
	break;
      case 146: /* "additive_expression" */

/* Line 1391 of yacc.c  */
#line 215 "parser.y"
	{ osl_relation_list_free((yyvaluep->list)); };

/* Line 1391 of yacc.c  */
#line 2011 "parser.c"
	break;
      case 147: /* "shift_expression" */

/* Line 1391 of yacc.c  */
#line 215 "parser.y"
	{ osl_relation_list_free((yyvaluep->list)); };

/* Line 1391 of yacc.c  */
#line 2020 "parser.c"
	break;
      case 148: /* "relational_expression" */

/* Line 1391 of yacc.c  */
#line 215 "parser.y"
	{ osl_relation_list_free((yyvaluep->list)); };

/* Line 1391 of yacc.c  */
#line 2029 "parser.c"
	break;
      case 149: /* "equality_expression" */

/* Line 1391 of yacc.c  */
#line 215 "parser.y"
	{ osl_relation_list_free((yyvaluep->list)); };

/* Line 1391 of yacc.c  */
#line 2038 "parser.c"
	break;
      case 150: /* "and_expression" */

/* Line 1391 of yacc.c  */
#line 215 "parser.y"
	{ osl_relation_list_free((yyvaluep->list)); };

/* Line 1391 of yacc.c  */
#line 2047 "parser.c"
	break;
      case 151: /* "exclusive_or_expression" */

/* Line 1391 of yacc.c  */
#line 215 "parser.y"
	{ osl_relation_list_free((yyvaluep->list)); };

/* Line 1391 of yacc.c  */
#line 2056 "parser.c"
	break;
      case 152: /* "inclusive_or_expression" */

/* Line 1391 of yacc.c  */
#line 215 "parser.y"
	{ osl_relation_list_free((yyvaluep->list)); };

/* Line 1391 of yacc.c  */
#line 2065 "parser.c"
	break;
      case 153: /* "logical_and_expression" */

/* Line 1391 of yacc.c  */
#line 215 "parser.y"
	{ osl_relation_list_free((yyvaluep->list)); };

/* Line 1391 of yacc.c  */
#line 2074 "parser.c"
	break;
      case 154: /* "logical_or_expression" */

/* Line 1391 of yacc.c  */
#line 215 "parser.y"
	{ osl_relation_list_free((yyvaluep->list)); };

/* Line 1391 of yacc.c  */
#line 2083 "parser.c"
	break;
      case 155: /* "conditional_expression" */

/* Line 1391 of yacc.c  */
#line 215 "parser.y"
	{ osl_relation_list_free((yyvaluep->list)); };

/* Line 1391 of yacc.c  */
#line 2092 "parser.c"
	break;
      case 156: /* "assignment_expression" */

/* Line 1391 of yacc.c  */
#line 215 "parser.y"
	{ osl_relation_list_free((yyvaluep->list)); };

/* Line 1391 of yacc.c  */
#line 2101 "parser.c"
	break;
      case 159: /* "expression" */

/* Line 1391 of yacc.c  */
#line 215 "parser.y"
	{ osl_relation_list_free((yyvaluep->list)); };

/* Line 1391 of yacc.c  */
#line 2110 "parser.c"
	break;
      case 160: /* "expression_statement" */

/* Line 1391 of yacc.c  */
#line 216 "parser.y"
	{ osl_statement_free((yyvaluep->stmt)); };

/* Line 1391 of yacc.c  */
#line 2119 "parser.c"
	break;

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
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
  int yytoken;
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

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

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
      yychar = YYLEX;
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
  *++yyvsp = yylval;

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
     `$$ = $1'.

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

/* Line 1806 of yacc.c  */
#line 228 "parser.y"
    { CLAN_debug("rule scop_list.1: scop"); }
    break;

  case 3:

/* Line 1806 of yacc.c  */
#line 229 "parser.y"
    { CLAN_debug("rule scop_list.2: scop_list scop"); }
    break;

  case 4:

/* Line 1806 of yacc.c  */
#line 230 "parser.y"
    { CLAN_debug("rule scop_list.3: scop_list IGNORE"); }
    break;

  case 5:

/* Line 1806 of yacc.c  */
#line 231 "parser.y"
    { CLAN_debug("rule scop_list.4: IGNORE"); }
    break;

  case 6:

/* Line 1806 of yacc.c  */
#line 238 "parser.y"
    {
      int nb_parameters;
      osl_scop_p scop;
      osl_generic_p arrays;

      CLAN_debug("rule scop.1: statement_list IGNORE");
      scop = osl_scop_malloc();
      CLAN_strdup(scop->language, "C");

      // Build the SCoP context.
      nb_parameters = clan_symbol_nb_of_type(parser_symbol,
          CLAN_TYPE_PARAMETER);
      scop->parameters = clan_symbol_to_strings(parser_symbol,
          CLAN_TYPE_PARAMETER);
      scop->context = clan_relation_build_context(nb_parameters,
                                                  parser_options);
      
      // Set the statements.
      scop->statement = (yyvsp[(1) - (2)].stmt);

      // Compact the SCoP relations.
      if (CLAN_DEBUG) {
	CLAN_debug("SCoP before compaction:");
	osl_scop_dump(stderr, scop);
      }
      clan_scop_compact(scop);
      if (CLAN_DEBUG) {
	CLAN_debug("SCoP after compaction:");
	osl_scop_dump(stderr, scop);
      }

      // Simplify the SCoP iteration domains.
      if (!parser_options->nosimplify)
        clan_scop_simplify(scop);

      // Add extensions.
      scop->registry = osl_interface_get_default_registry();
      clan_scop_generate_scatnames(scop);
      arrays = clan_symbol_to_arrays(parser_symbol);
      osl_generic_add(&scop->extension, arrays);
      clan_scop_generate_coordinates(scop, parser_options->name);
      clan_scop_generate_clay(scop, scanner_clay);

      // Add the SCoP to parser_scop and prepare the state for the next SCoP.
      osl_scop_add(&parser_scop, scop);
      clan_symbol_free(parser_symbol);
      clan_parser_state_initialize(parser_options);
      CLAN_debug_call(osl_scop_dump(stderr, scop));
    }
    break;

  case 7:

/* Line 1806 of yacc.c  */
#line 293 "parser.y"
    { (yyval.stmt) = (yyvsp[(1) - (1)].stmt); }
    break;

  case 8:

/* Line 1806 of yacc.c  */
#line 295 "parser.y"
    { (yyval.stmt) = (yyvsp[(1) - (2)].stmt); osl_statement_add(&(yyval.stmt), (yyvsp[(2) - (2)].stmt)); }
    break;

  case 9:

/* Line 1806 of yacc.c  */
#line 302 "parser.y"
    { 
      if (parser_indent == CLAN_UNDEFINED)
        parser_indent = scanner_column_LALR - 1;
    }
    break;

  case 10:

/* Line 1806 of yacc.c  */
#line 307 "parser.y"
    {
      (yyval.stmt) = (yyvsp[(2) - (2)].stmt);
    }
    break;

  case 11:

/* Line 1806 of yacc.c  */
#line 316 "parser.y"
    { (yyval.stmt) = (yyvsp[(1) - (1)].stmt); }
    break;

  case 12:

/* Line 1806 of yacc.c  */
#line 317 "parser.y"
    { (yyval.stmt) = (yyvsp[(1) - (1)].stmt); }
    break;

  case 13:

/* Line 1806 of yacc.c  */
#line 318 "parser.y"
    { (yyval.stmt) = (yyvsp[(1) - (1)].stmt); }
    break;

  case 14:

/* Line 1806 of yacc.c  */
#line 319 "parser.y"
    {
      if (parser_options->autoscop && !parser_autoscop && !parser_loop_depth) {
        parser_line_start = scanner_line;
        parser_column_start = scanner_column_LALR;
        parser_autoscop = CLAN_TRUE;
        // Reinitialize the symbol table.
        clan_symbol_free(parser_symbol);
        parser_symbol = NULL;
        if (CLAN_DEBUG)
          fprintf(stderr, "Autoscop start: line %3d column %3d\n",
                  parser_line_start, parser_column_start);
      }
    }
    break;

  case 15:

/* Line 1806 of yacc.c  */
#line 333 "parser.y"
    {
      (yyval.stmt) = (yyvsp[(2) - (2)].stmt);
      if (parser_options->autoscop && parser_autoscop && !parser_loop_depth) {
        parser_line_end = scanner_line;
        parser_column_end = scanner_column;
        if (CLAN_DEBUG)
          fprintf(stderr, "Autoscop found: line %3d column %3d\n",
                  parser_line_end, parser_column_end);
      }
    }
    break;

  case 16:

/* Line 1806 of yacc.c  */
#line 349 "parser.y"
    { (yyval.stmt) = NULL; }
    break;

  case 17:

/* Line 1806 of yacc.c  */
#line 350 "parser.y"
    { (yyval.stmt) = (yyvsp[(2) - (3)].stmt); }
    break;

  case 18:

/* Line 1806 of yacc.c  */
#line 361 "parser.y"
    {
      if (!parser_valid_else[parser_if_depth]) {
	yyerror("unsupported negation of a condition involving a modulo");
	YYABORT;
      }
    }
    break;

  case 19:

/* Line 1806 of yacc.c  */
#line 368 "parser.y"
    {
      CLAN_debug("rule selection_else_statement.1: else <stmt>");
      (yyval.stmt) = (yyvsp[(3) - (3)].stmt);
      CLAN_debug_call(osl_statement_dump(stderr, (yyval.stmt)));
    }
    break;

  case 20:

/* Line 1806 of yacc.c  */
#line 374 "parser.y"
    {
      CLAN_debug("rule selection_else_statement.2: <void>");
      (yyval.stmt) = NULL;
    }
    break;

  case 21:

/* Line 1806 of yacc.c  */
#line 383 "parser.y"
    {
      CLAN_debug("rule selection_statement.1.1: if ( condition ) ...");
      osl_relation_list_dup(&parser_stack);
      clan_relation_and(parser_stack->elt, (yyvsp[(3) - (4)].setex));
      parser_if_depth++;
      if ((parser_loop_depth + parser_if_depth) > CLAN_MAX_DEPTH)
	CLAN_error("CLAN_MAX_DEPTH reached, recompile with a higher value");
    }
    break;

  case 22:

/* Line 1806 of yacc.c  */
#line 392 "parser.y"
    {
      osl_relation_p not_if;
      
      CLAN_debug("rule selection_statement.1.2: if ( condition ) <stmt> ...");
      osl_relation_list_drop(&parser_stack);
      osl_relation_list_dup(&parser_stack);
      if (!clan_relation_existential((yyvsp[(3) - (6)].setex))) {
	not_if = clan_relation_not((yyvsp[(3) - (6)].setex));
	clan_relation_and(parser_stack->elt, not_if);
	osl_relation_free(not_if);
	parser_valid_else[parser_if_depth] = 1;
      } else {
	parser_valid_else[parser_if_depth] = 0;
      }
      osl_relation_free((yyvsp[(3) - (6)].setex));
    }
    break;

  case 23:

/* Line 1806 of yacc.c  */
#line 409 "parser.y"
    {
      CLAN_debug("rule selection_statement.1.3: if ( condition ) <stmt>"
	         "[else <stmt>]");
      osl_relation_list_drop(&parser_stack);
      (yyval.stmt) = (yyvsp[(6) - (8)].stmt);
      osl_statement_add(&(yyval.stmt), (yyvsp[(8) - (8)].stmt));
      parser_if_depth--;
      parser_nb_local_dims[parser_loop_depth + parser_if_depth] = 0;
      CLAN_debug_call(osl_statement_dump(stderr, (yyval.stmt)));
    }
    break;

  case 24:

/* Line 1806 of yacc.c  */
#line 424 "parser.y"
    {
      osl_vector_p   iterator_term;
      osl_relation_p iterator_relation;
      osl_relation_p init_constraints;
      osl_relation_p stride_constraints;
      
      CLAN_debug("rule iteration_statement.1.1: for ( init cond stride ) ...");
      clan_parser_increment_loop_depth();

      // Check the stride and the initialization are correct.
      if (((yyvsp[(5) - (6)].value) == 0) ||
	  (((yyvsp[(5) - (6)].value) > 0) && (parser_min || parser_floord)) ||
          (((yyvsp[(5) - (6)].value) < 0) && (parser_max || parser_ceild))) {
	osl_relation_free((yyvsp[(3) - (6)].setex));
        osl_relation_free((yyvsp[(4) - (6)].setex));
        if ((yyvsp[(5) - (6)].value) == 0)
	  yyerror("unsupported zero loop stride");
	else if ((yyvsp[(5) - (6)].value) > 0)
	  yyerror("illegal min or floord in forward loop initialization");
        else
	  yyerror("illegal max or ceild in backward loop initialization");
        YYABORT;
      }
      parser_ceild  = 0;
      parser_floord = 0;
      parser_min    = 0;
      parser_max    = 0;

      // Generate the set of constraints contributed by the initialization.
      iterator_term = clan_vector_term(parser_symbol, 0, NULL,
                                       parser_options->precision);
      osl_int_set_si(parser_options->precision,
                     &iterator_term->v[parser_loop_depth], 1); 
      iterator_relation = osl_relation_from_vector(iterator_term);
      if ((yyvsp[(5) - (6)].value) > 0)
	init_constraints = clan_relation_greater(iterator_relation, (yyvsp[(3) - (6)].setex), 0);
      else
	init_constraints = clan_relation_greater((yyvsp[(3) - (6)].setex), iterator_relation, 0);
      osl_vector_free(iterator_term);
      osl_relation_free(iterator_relation);

      // Add the contribution of the initialization to the current domain.
      osl_relation_list_dup(&parser_stack);
      clan_relation_and(parser_stack->elt, init_constraints);
      
      // Add the contribution of the condition to the current domain.
      if (!parser_options->noloopcontext)
	clan_relation_loop_context((yyvsp[(4) - (6)].setex), init_constraints, parser_loop_depth);
      clan_relation_and(parser_stack->elt, (yyvsp[(4) - (6)].setex));

      // Add the contribution of the stride to the current domain.
      if (((yyvsp[(5) - (6)].value) != 1) && ((yyvsp[(5) - (6)].value) != -1)) {
	stride_constraints = clan_relation_stride(parser_stack->elt,
	                                          parser_loop_depth, (yyvsp[(5) - (6)].value));
	osl_relation_free(parser_stack->elt);
        parser_stack->elt = stride_constraints;
      }
      
      osl_relation_free(init_constraints);
      osl_relation_free((yyvsp[(3) - (6)].setex));
      osl_relation_free((yyvsp[(4) - (6)].setex));
      parser_scattering[2*parser_loop_depth-1] = ((yyvsp[(5) - (6)].value) > 0) ? 1 : -1;
      parser_scattering[2*parser_loop_depth] = 0;
    }
    break;

  case 25:

/* Line 1806 of yacc.c  */
#line 489 "parser.y"
    {
      CLAN_debug("rule iteration_statement.1.2: for ( init cond stride ) "
	         "body");
      (yyval.stmt) = (yyvsp[(8) - (8)].stmt);
      CLAN_debug_call(osl_statement_dump(stderr, (yyval.stmt)));
    }
    break;

  case 26:

/* Line 1806 of yacc.c  */
#line 496 "parser.y"
    {
      osl_vector_p   iterator_term;
      osl_relation_p iterator_relation;

      CLAN_debug("rule iteration_statement.2.1: loop_infinite ...");
      if (!clan_symbol_new_iterator(&parser_symbol, parser_iterators,
	                            "clan_infinite_loop", parser_loop_depth))
	YYABORT;

      clan_parser_increment_loop_depth();
      
      // Generate the constraint clan_infinite_loop >= 0.
      iterator_term = clan_vector_term(parser_symbol, 0, NULL,
                                       parser_options->precision);
      osl_int_set_si(parser_options->precision,
                     &iterator_term->v[parser_loop_depth], 1); 
      osl_int_set_si(parser_options->precision, &iterator_term->v[0], 1); 
      iterator_relation = osl_relation_from_vector(iterator_term);
      
      // Add it to the domain stack.
      osl_relation_list_dup(&parser_stack);
      clan_relation_and(parser_stack->elt, iterator_relation);
      osl_vector_free(iterator_term);
      osl_relation_free(iterator_relation);
      parser_scattering[2*parser_loop_depth-1] = 1;
      parser_scattering[2*parser_loop_depth] = 0;
    }
    break;

  case 27:

/* Line 1806 of yacc.c  */
#line 524 "parser.y"
    {
      CLAN_debug("rule iteration_statement.2.2: loop_infinite body");
      (yyval.stmt) = (yyvsp[(3) - (3)].stmt);
      CLAN_debug_call(osl_statement_dump(stderr, (yyval.stmt)));
    }
    break;

  case 28:

/* Line 1806 of yacc.c  */
#line 534 "parser.y"
    {
      if (!clan_symbol_new_iterator(&parser_symbol, parser_iterators, (yyvsp[(2) - (2)].symbol),
	                            parser_loop_depth))
	YYABORT;
    }
    break;

  case 29:

/* Line 1806 of yacc.c  */
#line 540 "parser.y"
    {
      CLAN_debug("rule lower_bound.1: ID = max_affex ;");
      free((yyvsp[(2) - (6)].symbol));
      (yyval.setex) = (yyvsp[(5) - (6)].setex);
      CLAN_debug_call(osl_relation_dump(stderr, (yyval.setex)));
    }
    break;

  case 32:

/* Line 1806 of yacc.c  */
#line 557 "parser.y"
    {
      CLAN_debug("rule upper_bound.1: <affex> ;");
      (yyval.setex) = (yyvsp[(1) - (2)].setex);
      CLAN_debug_call(osl_relation_dump(stderr, (yyval.setex)));
    }
    break;

  case 33:

/* Line 1806 of yacc.c  */
#line 573 "parser.y"
    { (yyval.value) =  1;  free((yyvsp[(1) - (2)].symbol)); }
    break;

  case 34:

/* Line 1806 of yacc.c  */
#line 574 "parser.y"
    { (yyval.value) = -1;  free((yyvsp[(1) - (2)].symbol)); }
    break;

  case 35:

/* Line 1806 of yacc.c  */
#line 575 "parser.y"
    { (yyval.value) =  1;  free((yyvsp[(2) - (2)].symbol)); }
    break;

  case 36:

/* Line 1806 of yacc.c  */
#line 576 "parser.y"
    { (yyval.value) = -1;  free((yyvsp[(2) - (2)].symbol)); }
    break;

  case 37:

/* Line 1806 of yacc.c  */
#line 577 "parser.y"
    { (yyval.value) =  (yyvsp[(5) - (5)].value); free((yyvsp[(1) - (5)].symbol)); free((yyvsp[(3) - (5)].symbol)); }
    break;

  case 38:

/* Line 1806 of yacc.c  */
#line 578 "parser.y"
    { (yyval.value) = -(yyvsp[(5) - (5)].value); free((yyvsp[(1) - (5)].symbol)); free((yyvsp[(3) - (5)].symbol)); }
    break;

  case 39:

/* Line 1806 of yacc.c  */
#line 579 "parser.y"
    { (yyval.value) =  (yyvsp[(3) - (3)].value); free((yyvsp[(1) - (3)].symbol)); }
    break;

  case 40:

/* Line 1806 of yacc.c  */
#line 580 "parser.y"
    { (yyval.value) = -(yyvsp[(3) - (3)].value); free((yyvsp[(1) - (3)].symbol)); }
    break;

  case 41:

/* Line 1806 of yacc.c  */
#line 584 "parser.y"
    { (yyval.symbol) = (yyvsp[(1) - (1)].symbol); }
    break;

  case 42:

/* Line 1806 of yacc.c  */
#line 586 "parser.y"
    { (yyval.symbol) = (yyvsp[(2) - (3)].symbol); }
    break;

  case 45:

/* Line 1806 of yacc.c  */
#line 597 "parser.y"
    {
      CLAN_debug("rule loop_body.1: <stmt>");
      parser_loop_depth--;
      clan_symbol_free(parser_iterators[parser_loop_depth]);
      osl_relation_list_drop(&parser_stack);
      (yyval.stmt) = (yyvsp[(1) - (1)].stmt);
      parser_scattering[2*parser_loop_depth]++;
      parser_nb_local_dims[parser_loop_depth + parser_if_depth] = 0;
      CLAN_debug_call(osl_statement_dump(stderr, (yyval.stmt)));
    }
    break;

  case 46:

/* Line 1806 of yacc.c  */
#line 617 "parser.y"
    {
      CLAN_debug("rule affine_minmax_expression.1: <affex>");
      (yyval.setex) = osl_relation_from_vector((yyvsp[(1) - (1)].affex));
      osl_vector_free((yyvsp[(1) - (1)].affex));
      CLAN_debug_call(osl_relation_dump(stderr, (yyval.setex)));
    }
    break;

  case 47:

/* Line 1806 of yacc.c  */
#line 624 "parser.y"
    {
      CLAN_debug("rule affine_minmax_expression.2: "
                 "MAX (affine_minmaxexpression , affine_minmax_expression )");
      (yyval.setex) = osl_relation_concat_constraints((yyvsp[(3) - (6)].setex), (yyvsp[(5) - (6)].setex));
      osl_relation_free((yyvsp[(3) - (6)].setex));
      osl_relation_free((yyvsp[(5) - (6)].setex));
      CLAN_debug_call(osl_relation_dump(stderr, (yyval.setex)));
    }
    break;

  case 48:

/* Line 1806 of yacc.c  */
#line 636 "parser.y"
    { parser_min = 1; }
    break;

  case 49:

/* Line 1806 of yacc.c  */
#line 637 "parser.y"
    { parser_max = 1; }
    break;

  case 50:

/* Line 1806 of yacc.c  */
#line 650 "parser.y"
    {
      CLAN_debug("rule affine_min_expression.1: <affex>");
      (yyval.setex) = osl_relation_from_vector((yyvsp[(1) - (1)].affex));
      osl_vector_free((yyvsp[(1) - (1)].affex));
      CLAN_debug_call(osl_relation_dump(stderr, (yyval.setex)));
    }
    break;

  case 51:

/* Line 1806 of yacc.c  */
#line 660 "parser.y"
    {
      CLAN_debug("rule affine_min_expression.2: "
                 "MIN ( affine_min_expression , affine_min_expresssion");
      (yyval.setex) = osl_relation_concat_constraints((yyvsp[(3) - (6)].setex), (yyvsp[(5) - (6)].setex));
      osl_relation_free((yyvsp[(3) - (6)].setex));
      osl_relation_free((yyvsp[(5) - (6)].setex));
      CLAN_debug_call(osl_relation_dump(stderr, (yyval.setex)));
    }
    break;

  case 52:

/* Line 1806 of yacc.c  */
#line 680 "parser.y"
    {
      CLAN_debug("rule affine_max_expression.1: <affex>");
      (yyval.setex) = osl_relation_from_vector((yyvsp[(1) - (1)].affex));
      osl_vector_free((yyvsp[(1) - (1)].affex));
      CLAN_debug_call(osl_relation_dump(stderr, (yyval.setex)));
    }
    break;

  case 53:

/* Line 1806 of yacc.c  */
#line 690 "parser.y"
    {
      CLAN_debug("rule affine_max_expression.2: "
                 "MAX ( affine_max_expression , affine_max_expression )");
      (yyval.setex) = osl_relation_concat_constraints((yyvsp[(3) - (6)].setex), (yyvsp[(5) - (6)].setex));
      osl_relation_free((yyvsp[(3) - (6)].setex));
      osl_relation_free((yyvsp[(5) - (6)].setex));
      CLAN_debug_call(osl_relation_dump(stderr, (yyval.setex)));
    }
    break;

  case 54:

/* Line 1806 of yacc.c  */
#line 713 "parser.y"
    {
      CLAN_debug("rule affine_relation.1: max_affex < min_affex");
      (yyval.setex) = clan_relation_greater((yyvsp[(3) - (3)].setex), (yyvsp[(1) - (3)].setex), 1);
      osl_relation_free((yyvsp[(1) - (3)].setex));
      osl_relation_free((yyvsp[(3) - (3)].setex));
      CLAN_debug_call(osl_relation_dump(stderr, (yyval.setex)));
    }
    break;

  case 55:

/* Line 1806 of yacc.c  */
#line 724 "parser.y"
    {
      CLAN_debug("rule affine_relation.2: min_affex > max_affex");
      (yyval.setex) = clan_relation_greater((yyvsp[(1) - (3)].setex), (yyvsp[(3) - (3)].setex), 1);
      osl_relation_free((yyvsp[(1) - (3)].setex));
      osl_relation_free((yyvsp[(3) - (3)].setex));
      CLAN_debug_call(osl_relation_dump(stderr, (yyval.setex)));
    }
    break;

  case 56:

/* Line 1806 of yacc.c  */
#line 735 "parser.y"
    {
      CLAN_debug("rule affine_relation.3: max_affex <= min_affex");
      (yyval.setex) = clan_relation_greater((yyvsp[(3) - (3)].setex), (yyvsp[(1) - (3)].setex), 0);
      osl_relation_free((yyvsp[(1) - (3)].setex));
      osl_relation_free((yyvsp[(3) - (3)].setex));
      CLAN_debug_call(osl_relation_dump(stderr, (yyval.setex)));
    }
    break;

  case 57:

/* Line 1806 of yacc.c  */
#line 746 "parser.y"
    {
      CLAN_debug("rule affine_relation.4: min_affex >= max_affex");
      (yyval.setex) = clan_relation_greater((yyvsp[(1) - (3)].setex), (yyvsp[(3) - (3)].setex), 0);
      osl_relation_free((yyvsp[(1) - (3)].setex));
      osl_relation_free((yyvsp[(3) - (3)].setex));
      CLAN_debug_call(osl_relation_dump(stderr, (yyval.setex)));
    }
    break;

  case 58:

/* Line 1806 of yacc.c  */
#line 757 "parser.y"
    {
      // a==b translates to a-b==0.
      osl_vector_p res;

      CLAN_debug("rule affine_relation.5: <affex> == <affex>");
      // Warning: cases like ceild(M,32) == ceild(N,32) are not handled.
      // Assert if we encounter such a case.
      assert ((osl_int_zero(parser_options->precision, (yyvsp[(1) - (3)].affex)->v[0]) ||
	       osl_int_one(parser_options->precision,  (yyvsp[(1) - (3)].affex)->v[0])) &&
	      (osl_int_zero(parser_options->precision, (yyvsp[(3) - (3)].affex)->v[0]) ||
	       osl_int_one(parser_options->precision,  (yyvsp[(3) - (3)].affex)->v[0])));
      res = osl_vector_sub((yyvsp[(1) - (3)].affex), (yyvsp[(3) - (3)].affex));
      osl_vector_tag_equality(res);
      (yyval.setex) = osl_relation_from_vector(res);
      osl_vector_free(res);
      osl_vector_free((yyvsp[(1) - (3)].affex));
      osl_vector_free((yyvsp[(3) - (3)].affex));
      CLAN_debug_call(osl_relation_dump(stderr, (yyval.setex)));
    }
    break;

  case 59:

/* Line 1806 of yacc.c  */
#line 780 "parser.y"
    {
      CLAN_debug("rule affine_relation.6: ( condition )");
      (yyval.setex) = (yyvsp[(2) - (3)].setex);
      CLAN_debug_call(osl_relation_dump(stderr, (yyval.setex)));
    }
    break;

  case 60:

/* Line 1806 of yacc.c  */
#line 789 "parser.y"
    {
      CLAN_debug("rule affine_relation.7: ! ( condition )");
      if (clan_relation_existential((yyvsp[(3) - (4)].setex))) {
        osl_relation_free((yyvsp[(3) - (4)].setex));
	yyerror("unsupported negation of a condition involving a modulo");
	YYABORT;
      }
      (yyval.setex) = clan_relation_not((yyvsp[(3) - (4)].setex));
      osl_relation_free((yyvsp[(3) - (4)].setex));
      CLAN_debug_call(osl_relation_dump(stderr, (yyval.setex)));
    }
    break;

  case 61:

/* Line 1806 of yacc.c  */
#line 804 "parser.y"
    {
      CLAN_debug("rule affine_relation.8: "
	         "affine_expression %% INTEGER == INTEGER");
      osl_int_set_si(parser_options->precision,
                     &((yyvsp[(1) - (5)].affex)->v[CLAN_MAX_DEPTH + 1 + clan_parser_nb_ld()]), -(yyvsp[(3) - (5)].value));
      osl_int_add_si(parser_options->precision,
	             &((yyvsp[(1) - (5)].affex)->v[(yyvsp[(1) - (5)].affex)->size - 1]), (yyvsp[(1) - (5)].affex)->v[(yyvsp[(1) - (5)].affex)->size - 1], -(yyvsp[(5) - (5)].value));
      clan_parser_add_ld();
      (yyval.setex) = osl_relation_from_vector((yyvsp[(1) - (5)].affex));
      osl_vector_free((yyvsp[(1) - (5)].affex));
      CLAN_debug_call(osl_relation_dump(stderr, (yyval.setex)));
    }
    break;

  case 62:

/* Line 1806 of yacc.c  */
#line 821 "parser.y"
    {
      CLAN_debug("rule affine_logical_and_expression.1: affine_relation");
      (yyval.setex) = (yyvsp[(1) - (1)].setex);
      CLAN_debug_call(osl_relation_dump(stderr, (yyval.setex)));
    }
    break;

  case 63:

/* Line 1806 of yacc.c  */
#line 827 "parser.y"
    {
      CLAN_debug("rule affine_logical_and_expression.2: "
	         "affine_logical_and_expression && affine_relation");
      clan_relation_and((yyvsp[(1) - (3)].setex), (yyvsp[(3) - (3)].setex));
      (yyval.setex) = (yyvsp[(1) - (3)].setex);
      osl_relation_free((yyvsp[(3) - (3)].setex));
      CLAN_debug_call(osl_relation_dump(stderr, (yyval.setex)));
    }
    break;

  case 64:

/* Line 1806 of yacc.c  */
#line 840 "parser.y"
    {
      CLAN_debug("rule affine_condition.1: affine_logical_and_expression");
      (yyval.setex) = (yyvsp[(1) - (1)].setex);
      CLAN_debug_call(osl_relation_dump(stderr, (yyval.setex)));
    }
    break;

  case 65:

/* Line 1806 of yacc.c  */
#line 846 "parser.y"
    {
      CLAN_debug("rule affine_condition.2: "
	         "affine_condition || affine_logical_and_expression");
      osl_relation_add(&(yyvsp[(1) - (3)].setex), (yyvsp[(3) - (3)].setex));
      (yyval.setex) = (yyvsp[(1) - (3)].setex);
      CLAN_debug_call(osl_relation_dump(stderr, (yyval.setex)));
    }
    break;

  case 66:

/* Line 1806 of yacc.c  */
#line 858 "parser.y"
    {
      clan_symbol_p id;

      CLAN_debug("rule affine_primary_expression.1: id");
      id = clan_symbol_add(&parser_symbol, (yyvsp[(1) - (1)].symbol), CLAN_UNDEFINED);
      // An id in an affex can be either an iterator or a parameter. If it is
      // an unknown (embeds read-only variables), it is updated to a parameter.
      if (id->type == CLAN_UNDEFINED) {
        if ((parser_nb_parameters + 1) > CLAN_MAX_PARAMETERS)
	        CLAN_error("CLAN_MAX_PARAMETERS reached,"
                             "recompile with a higher value");
        id->type = CLAN_TYPE_PARAMETER;
        id->rank = ++parser_nb_parameters;
      }

      if ((id->type != CLAN_TYPE_ITERATOR) &&
          (id->type != CLAN_TYPE_PARAMETER)) {
        free((yyvsp[(1) - (1)].symbol));
	if (id->type == CLAN_TYPE_ARRAY)
	  yyerror("variable or array reference in an affine expression");
	else
          yyerror("function call in an affine expression");
	YYABORT;
      }
      
      (yyval.affex) = clan_vector_term(parser_symbol, 1, (yyvsp[(1) - (1)].symbol), parser_options->precision);
      free((yyvsp[(1) - (1)].symbol));
      CLAN_debug_call(osl_vector_dump(stderr, (yyval.affex)));
    }
    break;

  case 67:

/* Line 1806 of yacc.c  */
#line 888 "parser.y"
    {
      CLAN_debug("rule affine_primary_expression.2: INTEGER");
      (yyval.affex) = clan_vector_term(parser_symbol, (yyvsp[(1) - (1)].value), NULL, parser_options->precision);
      CLAN_debug_call(osl_vector_dump(stderr, (yyval.affex)));
    }
    break;

  case 68:

/* Line 1806 of yacc.c  */
#line 894 "parser.y"
    {
      CLAN_debug("rule affine_primary_expression.3: "
                 "affine_additive_expression");
      (yyval.affex) = (yyvsp[(2) - (3)].affex);
      CLAN_debug_call(osl_vector_dump(stderr, (yyval.affex)));
    }
    break;

  case 69:

/* Line 1806 of yacc.c  */
#line 905 "parser.y"
    {
      CLAN_debug("rule affine_unary_expression.1: affine_primary_expression");
      (yyval.affex) = (yyvsp[(1) - (1)].affex);
      CLAN_debug_call(osl_vector_dump(stderr, (yyval.affex)));
    }
    break;

  case 70:

/* Line 1806 of yacc.c  */
#line 911 "parser.y"
    {
      CLAN_debug("rule affine_unary_expression.2: +affine_primary_expression");
      (yyval.affex) = (yyvsp[(2) - (2)].affex);
      CLAN_debug_call(osl_vector_dump(stderr, (yyval.affex)));
    }
    break;

  case 71:

/* Line 1806 of yacc.c  */
#line 917 "parser.y"
    {
      CLAN_debug("rule affine_unary_expression.2: -affine_primary_expression");
      (yyval.affex) = osl_vector_mul_scalar((yyvsp[(2) - (2)].affex), -1);
      osl_vector_free((yyvsp[(2) - (2)].affex));
      CLAN_debug_call(osl_vector_dump(stderr, (yyval.affex)));
    }
    break;

  case 72:

/* Line 1806 of yacc.c  */
#line 928 "parser.y"
    { 
      CLAN_debug("rule affine_multiplicative_expression.1: "
                 "affine_unary_expression");
      (yyval.affex) = (yyvsp[(1) - (1)].affex);
      CLAN_debug_call(osl_vector_dump(stderr, (yyval.affex)));
    }
    break;

  case 73:

/* Line 1806 of yacc.c  */
#line 935 "parser.y"
    {
      int coef;
      
      CLAN_debug("rule affine_multiplicative_expression.2: "
                 "affine_multiplicative_expression * affine_unary_expression");
      if (!osl_vector_is_scalar((yyvsp[(1) - (3)].affex)) && !osl_vector_is_scalar((yyvsp[(3) - (3)].affex))) {
        osl_vector_free((yyvsp[(1) - (3)].affex));
        osl_vector_free((yyvsp[(3) - (3)].affex));
        yyerror("non-affine expression");
	YYABORT;
      }

      if (osl_vector_is_scalar((yyvsp[(1) - (3)].affex))) {
        coef = osl_int_get_si((yyvsp[(1) - (3)].affex)->precision, (yyvsp[(1) - (3)].affex)->v[(yyvsp[(1) - (3)].affex)->size - 1]);
        (yyval.affex) = osl_vector_mul_scalar((yyvsp[(3) - (3)].affex), coef);
      } else {
        coef = osl_int_get_si((yyvsp[(3) - (3)].affex)->precision, (yyvsp[(3) - (3)].affex)->v[(yyvsp[(3) - (3)].affex)->size - 1]);
        (yyval.affex) = osl_vector_mul_scalar((yyvsp[(1) - (3)].affex), coef);
      }
      osl_vector_free((yyvsp[(1) - (3)].affex));
      osl_vector_free((yyvsp[(3) - (3)].affex));
      CLAN_debug_call(osl_vector_dump(stderr, (yyval.affex)));
    }
    break;

  case 74:

/* Line 1806 of yacc.c  */
#line 959 "parser.y"
    {
      int val1, val2;
      
      CLAN_debug("rule affine_multiplicative_expression.3: "
                 "affine_multiplicative_expression / affine_unary_expression");
      if (!osl_vector_is_scalar((yyvsp[(1) - (3)].affex)) || !osl_vector_is_scalar((yyvsp[(3) - (3)].affex))) {
        osl_vector_free((yyvsp[(1) - (3)].affex));
        osl_vector_free((yyvsp[(3) - (3)].affex));
        yyerror("non-affine expression");
	YYABORT;
      }
      val1 = osl_int_get_si((yyvsp[(1) - (3)].affex)->precision, (yyvsp[(1) - (3)].affex)->v[(yyvsp[(1) - (3)].affex)->size - 1]);
      val2 = osl_int_get_si((yyvsp[(3) - (3)].affex)->precision, (yyvsp[(3) - (3)].affex)->v[(yyvsp[(3) - (3)].affex)->size - 1]);
      (yyval.affex) = clan_vector_term(parser_symbol, val1 / val2, NULL,
                            parser_options->precision);
      osl_vector_free((yyvsp[(1) - (3)].affex));
      osl_vector_free((yyvsp[(3) - (3)].affex));
      CLAN_debug_call(osl_vector_dump(stderr, (yyval.affex)));
    }
    break;

  case 75:

/* Line 1806 of yacc.c  */
#line 983 "parser.y"
    { 
      CLAN_debug("rule affine_expression.1: "
                 "affine_multiplicative_expression");
      (yyval.affex) = (yyvsp[(1) - (1)].affex);
      CLAN_debug_call(osl_vector_dump(stderr, (yyval.affex)));
    }
    break;

  case 76:

/* Line 1806 of yacc.c  */
#line 990 "parser.y"
    {
      CLAN_debug("rule affine_expression.2: "
          "affine_expression + affine_multiplicative_expression");
      (yyval.affex) = osl_vector_add((yyvsp[(1) - (3)].affex), (yyvsp[(3) - (3)].affex));
      osl_vector_free((yyvsp[(1) - (3)].affex));
      osl_vector_free((yyvsp[(3) - (3)].affex));
      CLAN_debug_call(osl_vector_dump(stderr, (yyval.affex)));
    }
    break;

  case 77:

/* Line 1806 of yacc.c  */
#line 999 "parser.y"
    {
      CLAN_debug("rule affine_expression.3: "
          "affine_expression - affine_multiplicative_expression");
      (yyval.affex) = osl_vector_sub((yyvsp[(1) - (3)].affex), (yyvsp[(3) - (3)].affex));
      osl_vector_free((yyvsp[(1) - (3)].affex));
      osl_vector_free((yyvsp[(3) - (3)].affex));
      CLAN_debug_call(osl_vector_dump(stderr, (yyval.affex)));
    }
    break;

  case 78:

/* Line 1806 of yacc.c  */
#line 1012 "parser.y"
    {
      CLAN_debug("affine_ceildloord_expression.1: affine_expression");
      (yyval.affex) = (yyvsp[(1) - (1)].affex);
      CLAN_debug_call(osl_vector_dump(stderr, (yyval.affex)));
    }
    break;

  case 79:

/* Line 1806 of yacc.c  */
#line 1018 "parser.y"
    {
      CLAN_debug("affine_ceildfloord_expression.2: "
                 "ceildfloord ( affine_expression , INTEGER )");
      osl_int_set_si(parser_options->precision, &((yyvsp[(3) - (6)].affex)->v[0]), (yyvsp[(5) - (6)].value));
      (yyval.affex) = (yyvsp[(3) - (6)].affex);
      CLAN_debug_call(osl_vector_dump(stderr, (yyval.affex)));
    }
    break;

  case 80:

/* Line 1806 of yacc.c  */
#line 1029 "parser.y"
    { parser_ceild = 1; }
    break;

  case 81:

/* Line 1806 of yacc.c  */
#line 1030 "parser.y"
    { parser_floord = 1; }
    break;

  case 82:

/* Line 1806 of yacc.c  */
#line 1036 "parser.y"
    {
      CLAN_debug("affine_ceil_expression.1: affine_expression");
      (yyval.affex) = (yyvsp[(1) - (1)].affex);
      CLAN_debug_call(osl_vector_dump(stderr, (yyval.affex)));
    }
    break;

  case 83:

/* Line 1806 of yacc.c  */
#line 1042 "parser.y"
    {
      CLAN_debug("affine_ceil_expression.2: "
                 "CEILD ( affine_expression , INTEGER )");
      osl_int_set_si(parser_options->precision, &((yyvsp[(3) - (6)].affex)->v[0]), (yyvsp[(5) - (6)].value));
      (yyval.affex) = (yyvsp[(3) - (6)].affex);
      CLAN_debug_call(osl_vector_dump(stderr, (yyval.affex)));
    }
    break;

  case 84:

/* Line 1806 of yacc.c  */
#line 1054 "parser.y"
    {
      CLAN_debug("affine_floor_expression.1: affine_expression");
      (yyval.affex) = (yyvsp[(1) - (1)].affex);
      CLAN_debug_call(osl_vector_dump(stderr, (yyval.affex)));
    }
    break;

  case 85:

/* Line 1806 of yacc.c  */
#line 1060 "parser.y"
    {
      CLAN_debug("affine_floor_expression.2: "
                 "FLOORD ( affine_expression , INTEGER )");
      osl_int_set_si(parser_options->precision, &((yyvsp[(3) - (6)].affex)->v[0]), (yyvsp[(5) - (6)].value));
      (yyval.affex) = (yyvsp[(3) - (6)].affex);
      CLAN_debug_call(osl_vector_dump(stderr, (yyval.affex)));
    }
    break;

  case 86:

/* Line 1806 of yacc.c  */
#line 1077 "parser.y"
    {
      int nb_columns;
      osl_relation_p id;
      osl_relation_list_p list;
      clan_symbol_p symbol;

      CLAN_debug("rule primary_expression.1: ID");
      symbol = clan_symbol_add(&parser_symbol, (yyvsp[(1) - (1)].symbol), CLAN_UNDEFINED);
      nb_columns = CLAN_MAX_DEPTH + CLAN_MAX_LOCAL_DIMS +
	                 CLAN_MAX_PARAMETERS + 2;
      id = osl_relation_pmalloc(parser_options->precision, 0, nb_columns);
      osl_relation_set_attributes(id, 0, parser_loop_depth, 0,
                                  CLAN_MAX_PARAMETERS);
      clan_relation_tag_array(id, symbol->key);
      list = osl_relation_list_malloc();
      list->elt = id;

      // add the id to the extbody
      if (parser_options->extbody) {
        if (parser_access_start != -1) {
          osl_extbody_add(parser_access_extbody,
                          parser_access_start,
                          parser_access_length);
        }

        int len = strlen(parser_record);
        parser_access_start = len - strlen((yyvsp[(1) - (1)].symbol));
        parser_access_length = len - parser_access_start;
      }

      free((yyvsp[(1) - (1)].symbol));
      (yyval.list) = list;
      CLAN_debug_call(osl_relation_list_dump(stderr, (yyval.list)));
    }
    break;

  case 87:

/* Line 1806 of yacc.c  */
#line 1112 "parser.y"
    { (yyval.list) = NULL; }
    break;

  case 88:

/* Line 1806 of yacc.c  */
#line 1114 "parser.y"
    { (yyval.list) = NULL; }
    break;

  case 89:

/* Line 1806 of yacc.c  */
#line 1116 "parser.y"
    { (yyval.list) = NULL; }
    break;

  case 90:

/* Line 1806 of yacc.c  */
#line 1118 "parser.y"
    { (yyval.list) = (yyvsp[(2) - (3)].list); }
    break;

  case 91:

/* Line 1806 of yacc.c  */
#line 1124 "parser.y"
    { (yyval.list) = (yyvsp[(1) - (1)].list); }
    break;

  case 92:

/* Line 1806 of yacc.c  */
#line 1126 "parser.y"
    {
      if (parser_options->extbody)
        parser_access_length = strlen(parser_record) - parser_access_start;

      CLAN_debug("rule postfix_expression.2: postfix_expression [ <affex> ]");
      if (!clan_symbol_update_type(parser_symbol, (yyvsp[(1) - (4)].list), CLAN_TYPE_ARRAY))
        YYABORT;
      clan_relation_new_output_vector((yyvsp[(1) - (4)].list)->elt, (yyvsp[(3) - (4)].affex));
      osl_vector_free((yyvsp[(3) - (4)].affex));
      (yyval.list) = (yyvsp[(1) - (4)].list);
      CLAN_debug_call(osl_relation_list_dump(stderr, (yyval.list)));
    }
    break;

  case 93:

/* Line 1806 of yacc.c  */
#line 1139 "parser.y"
    { 
      // don't save access name of a function
      if (parser_options->extbody) {
        parser_access_extbody->nb_access -= osl_relation_list_count((yyvsp[(1) - (3)].list)) - 1;
        parser_access_start = -1;
      }

      if (!clan_symbol_update_type(parser_symbol, (yyvsp[(1) - (3)].list), CLAN_TYPE_FUNCTION))
        YYABORT;
      osl_relation_list_free((yyvsp[(1) - (3)].list));
      (yyval.list) = NULL;
    }
    break;

  case 94:

/* Line 1806 of yacc.c  */
#line 1152 "parser.y"
    {
      // don't save access name of a function
      if (parser_options->extbody) {
        parser_access_extbody->nb_access -= osl_relation_list_count((yyvsp[(1) - (2)].list)) - 1;
        parser_access_start = -1;
      }
    }
    break;

  case 95:

/* Line 1806 of yacc.c  */
#line 1160 "parser.y"
    {
      if (!clan_symbol_update_type(parser_symbol, (yyvsp[(1) - (5)].list), CLAN_TYPE_FUNCTION))
        YYABORT;
      osl_relation_list_free((yyvsp[(1) - (5)].list));
      (yyval.list) = (yyvsp[(4) - (5)].list);
    }
    break;

  case 96:

/* Line 1806 of yacc.c  */
#line 1167 "parser.y"
    {
      if (parser_options->extbody)
        parser_access_length = strlen(parser_record) - parser_access_start;

      clan_symbol_p symbol;

      CLAN_debug("rule postfix_expression.4: postfix_expression . ID");
      if (!clan_symbol_update_type(parser_symbol, (yyvsp[(1) - (3)].list), CLAN_TYPE_ARRAY))
        YYABORT;
      symbol = clan_symbol_add(&parser_symbol, (yyvsp[(3) - (3)].symbol), CLAN_TYPE_FIELD);
      clan_relation_new_output_scalar((yyvsp[(1) - (3)].list)->elt, symbol->key);
      free((yyvsp[(3) - (3)].symbol));
      (yyval.list) = (yyvsp[(1) - (3)].list);
      CLAN_debug_call(osl_relation_list_dump(stderr, (yyval.list)));
    }
    break;

  case 97:

/* Line 1806 of yacc.c  */
#line 1183 "parser.y"
    {
      if (parser_options->extbody)
        parser_access_length = strlen(parser_record) - parser_access_start;

      clan_symbol_p symbol;

      CLAN_debug("rule postfix_expression.5: postfix_expression -> ID");
      if (!clan_symbol_update_type(parser_symbol, (yyvsp[(1) - (3)].list), CLAN_TYPE_ARRAY))
        YYABORT;
      symbol = clan_symbol_add(&parser_symbol, (yyvsp[(3) - (3)].symbol), CLAN_TYPE_FIELD);
      clan_relation_new_output_scalar((yyvsp[(1) - (3)].list)->elt, symbol->key);
      free((yyvsp[(3) - (3)].symbol));
      (yyval.list) = (yyvsp[(1) - (3)].list);
      CLAN_debug_call(osl_relation_list_dump(stderr, (yyval.list)));
    }
    break;

  case 98:

/* Line 1806 of yacc.c  */
#line 1199 "parser.y"
    { 
      osl_relation_list_p list;

      CLAN_debug("rule postfix_expression.6: postfix_expression -> "
	         "postfix_expression ++/--");
      if (!clan_symbol_update_type(parser_symbol, (yyvsp[(1) - (2)].list), CLAN_TYPE_ARRAY))
        YYABORT;
      list = (yyvsp[(1) - (2)].list);
      // The last reference in the list is also written.
      if (list != NULL) {
        while (list->next != NULL)
          list = list->next;
        list->next = osl_relation_list_node(list->elt);
        list->next->elt->type = OSL_TYPE_WRITE;
      }
      (yyval.list) = (yyvsp[(1) - (2)].list);
      CLAN_debug_call(osl_relation_list_dump(stderr, (yyval.list)));

      // add an empty line in the extbody
      if (parser_options->extbody) {
        osl_extbody_add(parser_access_extbody, -1, -1);
      }
    }
    break;

  case 99:

/* Line 1806 of yacc.c  */
#line 1226 "parser.y"
    { (yyval.list) = (yyvsp[(1) - (1)].list); }
    break;

  case 100:

/* Line 1806 of yacc.c  */
#line 1228 "parser.y"
    {
      (yyval.list) = (yyvsp[(1) - (3)].list);
      osl_relation_list_add(&(yyval.list), (yyvsp[(3) - (3)].list));
    }
    break;

  case 101:

/* Line 1806 of yacc.c  */
#line 1236 "parser.y"
    { (yyval.list) = (yyvsp[(1) - (1)].list); }
    break;

  case 102:

/* Line 1806 of yacc.c  */
#line 1238 "parser.y"
    {
      osl_relation_list_p list;

      CLAN_debug("rule unary_expression.2: unary_expression -> "
	         "++/-- unary_expression");
      if (!clan_symbol_update_type(parser_symbol, (yyvsp[(2) - (2)].list), CLAN_TYPE_ARRAY))
        YYABORT;
      list = (yyvsp[(2) - (2)].list);
      // The last reference in the list is also written.
      if (list != NULL) {
        while (list->next != NULL)
          list = list->next;
        list->next = osl_relation_list_node(list->elt);
        list->next->elt->type = OSL_TYPE_WRITE;
      }
      (yyval.list) = (yyvsp[(2) - (2)].list);
      CLAN_debug_call(osl_relation_list_dump(stderr, (yyval.list)));

      // add an empty line in the extbody
      if (parser_options->extbody) {
        osl_extbody_add(parser_access_extbody, -1, -1);
      }
    }
    break;

  case 103:

/* Line 1806 of yacc.c  */
#line 1262 "parser.y"
    { (yyval.list) = (yyvsp[(2) - (2)].list); }
    break;

  case 104:

/* Line 1806 of yacc.c  */
#line 1264 "parser.y"
    { (yyval.list) = (yyvsp[(2) - (2)].list); }
    break;

  case 105:

/* Line 1806 of yacc.c  */
#line 1266 "parser.y"
    { (yyval.list) = NULL; }
    break;

  case 114:

/* Line 1806 of yacc.c  */
#line 1285 "parser.y"
    { (yyval.list) = (yyvsp[(1) - (1)].list); }
    break;

  case 115:

/* Line 1806 of yacc.c  */
#line 1287 "parser.y"
    { (yyval.list) = (yyvsp[(4) - (4)].list); }
    break;

  case 116:

/* Line 1806 of yacc.c  */
#line 1292 "parser.y"
    { (yyval.list) = (yyvsp[(1) - (1)].list); }
    break;

  case 117:

/* Line 1806 of yacc.c  */
#line 1294 "parser.y"
    {
      (yyval.list) = (yyvsp[(1) - (3)].list);
      osl_relation_list_add(&(yyval.list), (yyvsp[(3) - (3)].list));
    }
    break;

  case 118:

/* Line 1806 of yacc.c  */
#line 1299 "parser.y"
    {
      (yyval.list) = (yyvsp[(1) - (3)].list);
      osl_relation_list_add(&(yyval.list), (yyvsp[(3) - (3)].list));
    }
    break;

  case 119:

/* Line 1806 of yacc.c  */
#line 1304 "parser.y"
    {
      (yyval.list) = (yyvsp[(1) - (3)].list);
      osl_relation_list_add(&(yyval.list), (yyvsp[(3) - (3)].list));
    }
    break;

  case 120:

/* Line 1806 of yacc.c  */
#line 1312 "parser.y"
    { (yyval.list) = (yyvsp[(1) - (1)].list); }
    break;

  case 121:

/* Line 1806 of yacc.c  */
#line 1314 "parser.y"
    {
      (yyval.list) = (yyvsp[(1) - (3)].list);
      osl_relation_list_add(&(yyval.list), (yyvsp[(3) - (3)].list));
    }
    break;

  case 122:

/* Line 1806 of yacc.c  */
#line 1319 "parser.y"
    {
      (yyval.list) = (yyvsp[(1) - (3)].list);
      osl_relation_list_add(&(yyval.list), (yyvsp[(3) - (3)].list));
    }
    break;

  case 123:

/* Line 1806 of yacc.c  */
#line 1327 "parser.y"
    { (yyval.list) = (yyvsp[(1) - (1)].list); }
    break;

  case 124:

/* Line 1806 of yacc.c  */
#line 1329 "parser.y"
    {
      (yyval.list) = (yyvsp[(1) - (3)].list);
      osl_relation_list_add(&(yyval.list), (yyvsp[(3) - (3)].list));
    }
    break;

  case 125:

/* Line 1806 of yacc.c  */
#line 1334 "parser.y"
    {
      (yyval.list) = (yyvsp[(1) - (3)].list);
      osl_relation_list_add(&(yyval.list), (yyvsp[(3) - (3)].list));
    }
    break;

  case 126:

/* Line 1806 of yacc.c  */
#line 1342 "parser.y"
    { (yyval.list) = (yyvsp[(1) - (1)].list); }
    break;

  case 127:

/* Line 1806 of yacc.c  */
#line 1344 "parser.y"
    {
      (yyval.list) = (yyvsp[(1) - (3)].list);
      osl_relation_list_add(&(yyval.list), (yyvsp[(3) - (3)].list));
    }
    break;

  case 128:

/* Line 1806 of yacc.c  */
#line 1349 "parser.y"
    {
      (yyval.list) = (yyvsp[(1) - (3)].list);
      osl_relation_list_add(&(yyval.list), (yyvsp[(3) - (3)].list));
    }
    break;

  case 129:

/* Line 1806 of yacc.c  */
#line 1354 "parser.y"
    {
      (yyval.list) = (yyvsp[(1) - (3)].list);
      osl_relation_list_add(&(yyval.list), (yyvsp[(3) - (3)].list));
    }
    break;

  case 130:

/* Line 1806 of yacc.c  */
#line 1359 "parser.y"
    {
      (yyval.list) = (yyvsp[(1) - (3)].list);
      osl_relation_list_add(&(yyval.list), (yyvsp[(3) - (3)].list));
    }
    break;

  case 131:

/* Line 1806 of yacc.c  */
#line 1367 "parser.y"
    { (yyval.list) = (yyvsp[(1) - (1)].list); }
    break;

  case 132:

/* Line 1806 of yacc.c  */
#line 1369 "parser.y"
    {
      (yyval.list) = (yyvsp[(1) - (3)].list);
      osl_relation_list_add(&(yyval.list), (yyvsp[(3) - (3)].list));
    }
    break;

  case 133:

/* Line 1806 of yacc.c  */
#line 1374 "parser.y"
    {
      (yyval.list) = (yyvsp[(1) - (3)].list);
      osl_relation_list_add(&(yyval.list), (yyvsp[(3) - (3)].list));
    }
    break;

  case 134:

/* Line 1806 of yacc.c  */
#line 1382 "parser.y"
    { (yyval.list) = (yyvsp[(1) - (1)].list); }
    break;

  case 135:

/* Line 1806 of yacc.c  */
#line 1384 "parser.y"
    {
      (yyval.list) = (yyvsp[(1) - (3)].list);
      osl_relation_list_add(&(yyval.list), (yyvsp[(3) - (3)].list));
    }
    break;

  case 136:

/* Line 1806 of yacc.c  */
#line 1392 "parser.y"
    { (yyval.list) = (yyvsp[(1) - (1)].list); }
    break;

  case 137:

/* Line 1806 of yacc.c  */
#line 1394 "parser.y"
    {
      (yyval.list) = (yyvsp[(1) - (3)].list);
      osl_relation_list_add(&(yyval.list), (yyvsp[(3) - (3)].list));
    }
    break;

  case 138:

/* Line 1806 of yacc.c  */
#line 1402 "parser.y"
    { (yyval.list) = (yyvsp[(1) - (1)].list); }
    break;

  case 139:

/* Line 1806 of yacc.c  */
#line 1404 "parser.y"
    {
      (yyval.list) = (yyvsp[(1) - (3)].list);
      osl_relation_list_add(&(yyval.list), (yyvsp[(3) - (3)].list));
    }
    break;

  case 140:

/* Line 1806 of yacc.c  */
#line 1412 "parser.y"
    { (yyval.list) = (yyvsp[(1) - (1)].list); }
    break;

  case 141:

/* Line 1806 of yacc.c  */
#line 1414 "parser.y"
    {
      (yyval.list) = (yyvsp[(1) - (3)].list);
      osl_relation_list_add(&(yyval.list), (yyvsp[(3) - (3)].list));
    }
    break;

  case 142:

/* Line 1806 of yacc.c  */
#line 1422 "parser.y"
    { (yyval.list) = (yyvsp[(1) - (1)].list); }
    break;

  case 143:

/* Line 1806 of yacc.c  */
#line 1424 "parser.y"
    {
      (yyval.list) = (yyvsp[(1) - (3)].list);
      osl_relation_list_add(&(yyval.list), (yyvsp[(3) - (3)].list));
    }
    break;

  case 144:

/* Line 1806 of yacc.c  */
#line 1432 "parser.y"
    { (yyval.list) = (yyvsp[(1) - (1)].list); }
    break;

  case 145:

/* Line 1806 of yacc.c  */
#line 1434 "parser.y"
    {
      (yyval.list) = (yyvsp[(1) - (5)].list);
      osl_relation_list_add(&(yyval.list), (yyvsp[(3) - (5)].list));
      osl_relation_list_add(&(yyval.list), (yyvsp[(5) - (5)].list));
    }
    break;

  case 146:

/* Line 1806 of yacc.c  */
#line 1443 "parser.y"
    {
      CLAN_debug("rule assignment_expression.1: conditional_expression;");
      (yyval.list) = (yyvsp[(1) - (1)].list);
      clan_relation_list_define_type((yyval.list), OSL_TYPE_READ);
      CLAN_debug_call(osl_relation_list_dump(stderr, (yyval.list)));
    }
    break;

  case 147:

/* Line 1806 of yacc.c  */
#line 1450 "parser.y"
    {
      osl_relation_list_p list;

      CLAN_debug("rule assignment_expression.2: unary_expression "
	         "assignment_operator assignment_expression;");
      if (!clan_symbol_update_type(parser_symbol, (yyvsp[(1) - (3)].list), CLAN_TYPE_ARRAY))
        YYABORT;
      (yyval.list) = (yyvsp[(1) - (3)].list);
      // Accesses of $1 are READ except the last one which is a WRITE or both.
      clan_relation_list_define_type((yyval.list), OSL_TYPE_READ);
      list = (yyval.list);
      while (list->next != NULL)
        list = list->next;
      if ((yyvsp[(2) - (3)].value) == CLAN_TYPE_RDWR) {
        list->next = osl_relation_list_node(list->elt);
        list = list->next;

        // add an empty line in the extbody
        if (parser_options->extbody) {
          osl_extbody_add(parser_access_extbody, -1, -1);
        }
      }
      osl_relation_set_type(list->elt, OSL_TYPE_WRITE);
      osl_relation_list_add(&(yyval.list), (yyvsp[(3) - (3)].list));
      CLAN_debug_call(osl_relation_list_dump(stderr, (yyval.list)));
    }
    break;

  case 148:

/* Line 1806 of yacc.c  */
#line 1480 "parser.y"
    { (yyval.value) = CLAN_TYPE_WRITE; }
    break;

  case 149:

/* Line 1806 of yacc.c  */
#line 1482 "parser.y"
    { (yyval.value) = CLAN_TYPE_RDWR; }
    break;

  case 160:

/* Line 1806 of yacc.c  */
#line 1500 "parser.y"
    { (yyval.list) = (yyvsp[(1) - (1)].list); }
    break;

  case 161:

/* Line 1806 of yacc.c  */
#line 1502 "parser.y"
    {
      (yyval.list) = (yyvsp[(1) - (3)].list);
      osl_relation_list_add(&(yyval.list), (yyvsp[(3) - (3)].list));
    }
    break;

  case 162:

/* Line 1806 of yacc.c  */
#line 1510 "parser.y"
    {
      CLAN_debug("rule expression_statement.1: ;");
      (yyval.stmt) = NULL;
      CLAN_debug_call(osl_statement_dump(stderr, (yyval.stmt)));
    }
    break;

  case 163:

/* Line 1806 of yacc.c  */
#line 1516 "parser.y"
    {
      if (parser_options->extbody) {
        parser_access_start = -1;
        parser_access_extbody = osl_extbody_malloc();
      }

      CLAN_strdup(parser_record, scanner_latest_text);
      parser_recording = CLAN_TRUE;
    }
    break;

  case 164:

/* Line 1806 of yacc.c  */
#line 1526 "parser.y"
    {
      osl_statement_p statement;
      osl_body_p body;
      osl_generic_p gen;
      
      CLAN_debug("rule expression_statement.2: expression ;");
      statement = osl_statement_malloc();

      // - 1. Domain
      statement->domain = osl_relation_clone(parser_stack->elt);
      osl_relation_set_type(statement->domain, OSL_TYPE_DOMAIN);
      osl_relation_set_attributes(statement->domain, parser_loop_depth, 0,
	                          clan_parser_nb_ld(), CLAN_MAX_PARAMETERS);

      // - 2. Scattering
      statement->scattering = clan_relation_scattering(parser_scattering,
          parser_loop_depth, parser_options->precision);

      // - 3. Array accesses
      statement->access = (yyvsp[(2) - (3)].list);

      // - 4. Body.
      body = osl_body_malloc();
      body->iterators = clan_symbol_array_to_strings(parser_iterators,
                                                     parser_loop_depth);
      body->expression = osl_strings_encapsulate(parser_record);
      gen = osl_generic_shell(body, osl_body_interface());
      osl_generic_add(&statement->extension, gen);

      if (parser_options->extbody) {
        // Extended body

        // add the last access
        if (parser_access_start != -1) {
          osl_extbody_add(parser_access_extbody,
                          parser_access_start,
                          parser_access_length);
        }

        parser_access_extbody->body = osl_body_clone(body);
        gen = osl_generic_shell(parser_access_extbody, osl_extbody_interface());
        osl_generic_add(&statement->extension, gen);
      }

      parser_recording = CLAN_FALSE;
      parser_record = NULL;
      
      parser_scattering[2*parser_loop_depth]++;

      (yyval.stmt) = statement;
      CLAN_debug_call(osl_statement_dump(stderr, (yyval.stmt)));
    }
    break;

  case 189:

/* Line 1806 of yacc.c  */
#line 1623 "parser.y"
    { free((yyvsp[(2) - (5)].symbol)); }
    break;

  case 191:

/* Line 1806 of yacc.c  */
#line 1625 "parser.y"
    { free((yyvsp[(2) - (2)].symbol)); }
    break;

  case 207:

/* Line 1806 of yacc.c  */
#line 1662 "parser.y"
    { free((yyvsp[(2) - (5)].symbol)); }
    break;

  case 208:

/* Line 1806 of yacc.c  */
#line 1663 "parser.y"
    { free((yyvsp[(2) - (2)].symbol)); }
    break;

  case 211:

/* Line 1806 of yacc.c  */
#line 1672 "parser.y"
    { free((yyvsp[(1) - (1)].symbol)); }
    break;

  case 212:

/* Line 1806 of yacc.c  */
#line 1673 "parser.y"
    { free((yyvsp[(1) - (3)].symbol)); }
    break;

  case 217:

/* Line 1806 of yacc.c  */
#line 1687 "parser.y"
    { free((yyvsp[(1) - (1)].symbol)); }
    break;

  case 237:

/* Line 1806 of yacc.c  */
#line 1726 "parser.y"
    { free((yyvsp[(1) - (1)].symbol)); }
    break;

  case 238:

/* Line 1806 of yacc.c  */
#line 1727 "parser.y"
    { free((yyvsp[(3) - (3)].symbol)); }
    break;



/* Line 1806 of yacc.c  */
#line 4272 "parser.c"
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

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
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

  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

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

  *++yyvsp = yylval;


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

#if !defined(yyoverflow) || YYERROR_VERBOSE
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
  /* Do not reclaim the symbols of the rule which action triggered
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
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 2067 of yacc.c  */
#line 1753 "parser.y"



void yyerror(char *s) {
  int i, line = 1;
  char c = 'C';
  FILE* file;
 
  CLAN_debug("parse error notified");

  if (!parser_options->autoscop) {
    fprintf(stderr, "[Clan] Error: %s at line %d, column %d.\n", s,
        scanner_line, scanner_column - 1);

    // Print a message to show where is the problem.
    if ((parser_options != NULL) && (parser_options->name != NULL)) {
      file = fopen(parser_options->name, "r");
      if (file != NULL) {
        // Go to the right line.
        while (line != scanner_line) {
          c = fgetc(file);
          if (c == '\n')
            line++;
        }

        // Print the line.
        while (c != EOF) {
          c = fgetc(file);
          fprintf(stderr, "%c", c);
          if (c == '\n')
            break;
        }

        // Print the situation line.
        for (i = 0; i < scanner_column - 1; i++) {
          if (i < scanner_column - 5)
            fprintf(stderr, " ");
          else if (i < scanner_column - 2)
            fprintf(stderr, "~");
          else
            fprintf(stderr, "^\n");
        }
        fclose(file);
      } else {
        CLAN_warning("cannot open input file");
      }
    }
  }
  parser_error = CLAN_TRUE;
}


void clan_parser_add_ld() {
  parser_nb_local_dims[parser_loop_depth + parser_if_depth]++;

  if (CLAN_DEBUG) {
    int i;
    CLAN_debug("parser_nb_local_dims updated");
    for (i = 0; i <= parser_loop_depth + parser_if_depth; i++)
      fprintf(stderr, "%d:%d ", i, parser_nb_local_dims[i]);
    fprintf(stderr, "\n");
  }
  
  if (clan_parser_nb_ld() > CLAN_MAX_LOCAL_DIMS)
    CLAN_error("CLAN_MAX_LOCAL_DIMS reached, recompile with a higher value");
}


int clan_parser_nb_ld() {
  int i, nb_ld = 0;

  for (i = 0; i <= parser_loop_depth + parser_if_depth; i++)
    nb_ld += parser_nb_local_dims[i]; 
  return nb_ld;
}


void clan_parser_increment_loop_depth() {
  parser_loop_depth++;
  if ((parser_loop_depth + parser_if_depth) > CLAN_MAX_DEPTH)
    CLAN_error("CLAN_MAX_DEPTH reached, recompile with a higher value");
}


/**
 * clan_parser_state_malloc function:
 * this function achieves the memory allocation for the "parser state".
 * \param[in] precision Precision of the integer elements.
 */
void clan_parser_state_malloc(int precision) {
  int nb_columns, depth;

  nb_columns        = CLAN_MAX_DEPTH + CLAN_MAX_LOCAL_DIMS +
                      CLAN_MAX_PARAMETERS + 2;
  depth             = CLAN_MAX_DEPTH;
  parser_stack      = osl_relation_list_malloc();
  parser_stack->elt = osl_relation_pmalloc(precision, 0, nb_columns);
  CLAN_malloc(parser_nb_local_dims, int*, depth * sizeof(int));
  CLAN_malloc(parser_valid_else, int*, depth * sizeof(int));
  CLAN_malloc(parser_scattering, int*, (2 * depth + 1) * sizeof(int));
  CLAN_malloc(parser_iterators, clan_symbol_p*, depth* sizeof(clan_symbol_p));
}


/**
 * clan_parser_state_free function:
 * this function frees the memory allocated for the "parser state", with the
 * exception of the parser_scop.
 */
void clan_parser_state_free() {
  clan_symbol_free(parser_symbol);
  free(parser_scattering);
  free(parser_iterators);
  free(parser_nb_local_dims);
  free(parser_valid_else);
  osl_relation_list_drop(&parser_stack);
}


/**
 * clan_parser_state_initialize function:
 * this function achieves the initialization of the "parser state", with
 * the exception of parser_scop.
 */
void clan_parser_state_initialize(clan_options_p options) {
  int i;

  parser_symbol        = NULL;
  parser_loop_depth    = 0;
  parser_options       = options;
  parser_recording     = CLAN_FALSE;
  parser_record        = NULL;
  parser_if_depth      = 0;
  parser_ceild         = 0;
  parser_floord        = 0;
  parser_min           = 0;
  parser_max           = 0;
  parser_indent        = CLAN_UNDEFINED;
  parser_error         = CLAN_FALSE;
  parser_autoscop      = CLAN_FALSE;
  parser_line_start    = 1;
  parser_line_end      = 1;
  parser_column_start  = 1;
  parser_column_end    = 1;
  parser_nb_parameters = 0;

  for (i = 0; i < CLAN_MAX_DEPTH; i++) {
    parser_nb_local_dims[i] = 0;
    parser_valid_else[i] = 0;
  }

  for (i = 0; i < 2 * CLAN_MAX_DEPTH + 1; i++)
    parser_scattering[i] = 0;
}


/**
 * clan_parser_reinitialize function:
 * this function frees the temporary dynamic variables of the parser and
 * reset the variables to default values. It is meant to be used for a
 * clean restart after a parse error.
 */
void clan_parser_reinitialize() {
  int i;
  
  free(parser_record);
  clan_symbol_free(parser_symbol);
  for (i = 0; i < parser_loop_depth; i++)
    clan_symbol_free(parser_iterators[i]);
  while (parser_stack->next != NULL)
    osl_relation_list_drop(&parser_stack);
  osl_scop_free(parser_scop);
  clan_parser_state_initialize(parser_options);
}


/**
 * clan_parser_autoscop function:
 * this functions performs the automatic extraction of SCoPs from the input
 * file. It leaves the SCoP pragmas already set by the user intact (note that
 * as a consequence, user-SCoPs cannot be inserted to a larger SCoP).
 * It writes a file (named by the CLAN_AUTOPRAGMA_FILE macro) with the input
 * code where new SCoP pragmas have been inserted. If the option -autoscop
 * is set, it puts the list of SCoPs (including automatically discovered
 * SCoPs and user-SCoPs) in parser_scop.
 */
void clan_parser_autoscop() {
  int new_scop, nb_scops = 0;
  int line, column, restart_line, restart_column;
  long position;
  char c;
  int coordinates[5][CLAN_MAX_SCOPS]; // 0, 1: line start, end
                                      // 2, 3: column start, end
				      // 4: autoscop or not
 
  while (1) {
    // For the automatic extraction, we parse everything except user-SCoPs.
    if (!scanner_pragma)
      scanner_parsing = CLAN_TRUE;
    yyparse();

    new_scop = (parser_line_end != 1) || (parser_column_end != 1);
    restart_line = (new_scop) ? parser_line_end : scanner_line;
    restart_column = (new_scop) ? parser_column_end : scanner_column;
    if (CLAN_DEBUG) {
      if (new_scop)
	fprintf(stderr, "[Clan] Debug: new autoscop, ");
      else
	fprintf(stderr, "[Clan] Debug: no autoscop, ");
      fprintf(stderr, "restart at line %d, column %d\n",
	      restart_line, restart_column);
    }
 
    if (parser_error || new_scop) {
      if (new_scop) {
        // If a new SCoP has been found, store its coordinates.
        if (nb_scops == CLAN_MAX_SCOPS)
          CLAN_error("too many SCoPs! Change CLAN_MAX_SCOPS and recompile.");
        coordinates[0][nb_scops] = parser_line_start;
        coordinates[1][nb_scops] = parser_line_end;
        coordinates[2][nb_scops] = parser_column_start;
        coordinates[3][nb_scops] = parser_column_end;
        coordinates[4][nb_scops] = CLAN_TRUE;
        if (CLAN_DEBUG) {
          fprintf(stderr, "[Clan] Debug: AutoSCoP [%d,%d -> %d,%d]\n",
                  coordinates[0][nb_scops], coordinates[2][nb_scops],
                  coordinates[1][nb_scops], coordinates[3][nb_scops] - 1);
        }
        // Let's go for the next SCoP.
        parser_autoscop = CLAN_FALSE;
        nb_scops++;
      } else if (scanner_scop_start != CLAN_UNDEFINED) {
        // If the start of a user-SCoP is detected, store its coordinate.
	coordinates[0][nb_scops] = scanner_scop_start;
      } else if (scanner_scop_end != CLAN_UNDEFINED) {
        // If the end of a user-SCoP is detected, store its coordinate.
	coordinates[1][nb_scops] = scanner_scop_end;
	coordinates[2][nb_scops] = 0;
	coordinates[3][nb_scops] = 0;
	coordinates[4][nb_scops] = CLAN_FALSE;
        if (CLAN_DEBUG) {
          fprintf(stderr, "[Clan] Debug: user-SCoP [%d,%d -> %d,%d]\n",
                  coordinates[0][nb_scops], coordinates[2][nb_scops],
                  coordinates[1][nb_scops], coordinates[3][nb_scops]);
        }
	nb_scops++;
      }

      // Restart after the SCoP or after the error.
      rewind(yyin);
      line = 1;
      column = 1;
      while ((line != restart_line) || (column != restart_column)) {
        c = fgetc(yyin);
        column++;
        if (c == '\n') {
          line++;
          column = 1;
        }
      }
    }

    // Reinitialize the scanner and the parser for a clean restart.
    clan_scanner_free();
    clan_scanner_reinitialize(scanner_pragma, restart_line, restart_column);
    clan_parser_reinitialize();
    yyrestart(yyin);

    // Check whether we reached the end of file or not.
    position = ftell(yyin);
    c = fgetc(yyin);
    if (fgetc(yyin) == EOF)
      break;
    else 
      fseek(yyin, position, SEEK_SET);
  }
 
  // Write the code with the inserted SCoP pragmas in CLAN_AUTOPRAGMA_FILE.
  rewind(yyin);
  clan_scop_print_autopragma(yyin, nb_scops, coordinates);

  // Use the temporary file for usual parsing.
  scanner_line = 1;
  scanner_column = 1;
  scanner_pragma = CLAN_FALSE;
  parser_options->autoscop = CLAN_FALSE;
  if ((yyin = fopen(CLAN_AUTOPRAGMA_FILE, "r")) == NULL)
    CLAN_error("cannot create the temporary file");
  yyparse();
  fclose(yyin);

  // Update the SCoP coordinates with those of the original file.
  clan_scop_update_coordinates(parser_scop, coordinates);
  parser_options->autoscop = CLAN_TRUE;
  
  if (remove(CLAN_AUTOPRAGMA_FILE))
    CLAN_warning("cannot delete temporary file");
}


/**
 * clan_parse function:
 * this function parses a file to extract a SCoP and returns, if successful,
 * a pointer to the osl_scop_t structure.
 * \param input   The file to parse (already open).
 * \param options Options for file parsing.
 */
osl_scop_p clan_parse(FILE* input, clan_options_p options) {
  osl_scop_p scop;
  yyin = input;

  clan_parser_state_malloc(options->precision);
  clan_parser_state_initialize(options);
  clan_scanner_initialize();
  yyrestart(yyin);  //restart scanning another file
  parser_scop = NULL;

  if (!options->autoscop)
    yyparse();
  else
    clan_parser_autoscop();

  CLAN_debug("parsing done");

  clan_scanner_free();
  
  if (!parser_error)
    scop = parser_scop;
  else
    scop = NULL;

  clan_parser_state_free();
  CLAN_debug("parser state successfully freed");

  return scop;
}

