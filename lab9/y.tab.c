/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "lab9.y" /* yacc.c:339  */

/* 
    Jacob Yanez
   	Lab 9: MIPS Code From AST
   	May 3, 2024

    This YACC file lays out the grammar for the CMINUS language. There
    was syntax directed semantic action added to each production rule
    which creates nodes to construct an Abstract Syntax Tree (AST) for 
    a given CMINUS program. Additionally, there has been some semantic
    action added to support a rudimentary symbol table implementation -- 
    mainly in productions that contain token T_INT and in productions that
    have any sort of types or calculations involved.
*/


/* begin specs */
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "symtable.h"
#include "emit.h"

ASTnode *PROGRAM;

int yylex();



/* added for use in yacc rules below, particularly for stopping the 
*  printing of verbose debug statements
*/
extern int mydebug;

// counter that keeps track of the current line number
extern int lineno;

int LEVEL = 0; // knowing how "deep" we are in blocks
int OFFSET = 0; // accumulating needed runtime space
int G_OFFSET = 0; // accumulation global variable offset
int MAX_OFFSET = 0; // largest offset needed for the current function

// prints out any errors that may occur during parsing, includes line number
void yyerror (s)  /* Called by yyparse on error */
     char *s;
{
  printf ("YACC PARSE ERROR: %s on line number %d\n", s, lineno);
}



#line 120 "y.tab.c" /* yacc.c:339  */

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
   by #include "y.tab.h".  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
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
    T_NUM = 258,
    T_ID = 259,
    T_STRING = 260,
    T_INT = 261,
    T_VOID = 262,
    T_READ = 263,
    T_WRITE = 264,
    T_LT = 265,
    T_GT = 266,
    T_LE = 267,
    T_GE = 268,
    T_E = 269,
    T_NE = 270,
    T_PLUS = 271,
    T_SUB = 272,
    T_MULT = 273,
    T_DIV = 274,
    T_MOD = 275,
    T_IF = 276,
    T_ELSE = 277,
    T_WHILE = 278,
    T_RETURN = 279
  };
#endif
/* Tokens.  */
#define T_NUM 258
#define T_ID 259
#define T_STRING 260
#define T_INT 261
#define T_VOID 262
#define T_READ 263
#define T_WRITE 264
#define T_LT 265
#define T_GT 266
#define T_LE 267
#define T_GE 268
#define T_E 269
#define T_NE 270
#define T_PLUS 271
#define T_SUB 272
#define T_MULT 273
#define T_DIV 274
#define T_MOD 275
#define T_IF 276
#define T_ELSE 277
#define T_WHILE 278
#define T_RETURN 279

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 57 "lab9.y" /* yacc.c:355  */

    int value;
    char * string;
    ASTnode *node;
    enum AST_MY_DATA_TYPE d_type;
    enum AST_OPERATORS operator;

#line 216 "y.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 233 "y.tab.c" /* yacc.c:358  */

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
#define YYFINAL  9
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   126

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  34
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  37
/* YYNRULES -- Number of rules.  */
#define YYNRULES  77
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  127

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   279

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
      29,    30,     2,     2,    28,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    25,
       2,    33,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    26,     2,    27,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    31,     2,    32,     2,     2,     2,     2,
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
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    88,    88,    91,    92,    99,   100,   103,   138,   144,
     150,   157,   166,   167,   171,   189,   170,   214,   215,   218,
     219,   226,   243,   263,   263,   285,   286,   293,   294,   301,
     302,   303,   304,   305,   306,   307,   308,   311,   316,   319,
     322,   323,   343,   344,   345,   346,   347,   348,   351,   352,
     373,   374,   377,   378,   399,   400,   401,   404,   405,   412,
     413,   414,   423,   461,   462,   465,   474,   486,   495,   506,
     514,   515,   522,   529,   534,   541,   557,   579
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "T_NUM", "T_ID", "T_STRING", "T_INT",
  "T_VOID", "T_READ", "T_WRITE", "T_LT", "T_GT", "T_LE", "T_GE", "T_E",
  "T_NE", "T_PLUS", "T_SUB", "T_MULT", "T_DIV", "T_MOD", "T_IF", "T_ELSE",
  "T_WHILE", "T_RETURN", "';'", "'['", "']'", "','", "'('", "')'", "'{'",
  "'}'", "'='", "$accept", "Program", "Declaration_List", "Declaration",
  "Var_Declaration", "Var_List", "Type_Specifier", "Fun_Declaration",
  "$@1", "$@2", "Params", "Param_List", "Param", "Compound_Stmt", "$@3",
  "Local_Declarations", "Statement_List", "Statement", "Expression_Stmt",
  "Expression", "Simple_Expression", "Relop", "Additive_Expression",
  "Addop", "Term", "Multop", "Factor", "Call", "Args", "Arg_List",
  "Selection_Stmt", "Iteration_Stmt", "Return_Stmt", "Read_Stmt",
  "Write_Stmt", "Assignment_Stmt", "Var", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,    59,    91,    93,    44,    40,
      41,   123,   125,    61
};
# endif

#define YYPACT_NINF -108

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-108)))

#define YYTABLE_NINF -18

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int8 yypact[] =
{
       2,  -108,  -108,    37,  -108,     2,  -108,    -2,  -108,  -108,
    -108,    20,    25,    49,    50,    40,  -108,    43,     1,  -108,
      38,    45,    46,    67,    47,  -108,    52,    50,    48,  -108,
       2,  -108,    54,    51,  -108,  -108,  -108,  -108,     2,     2,
      50,     7,  -108,  -108,    -9,    71,    18,    39,    64,    65,
      36,  -108,    39,  -108,    63,     7,  -108,    58,  -108,    75,
      44,  -108,  -108,  -108,  -108,  -108,  -108,  -108,  -108,    66,
      39,    39,    70,    72,    73,    76,  -108,  -108,    39,    39,
    -108,    77,    74,  -108,  -108,  -108,  -108,  -108,  -108,  -108,
    -108,  -108,  -108,  -108,    39,    39,  -108,  -108,  -108,    39,
      39,    78,    79,    80,  -108,  -108,  -108,  -108,    81,    82,
    -108,  -108,    41,    44,  -108,    83,  -108,    39,  -108,     7,
       7,  -108,  -108,    84,  -108,     7,  -108
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    12,    13,     0,     2,     3,     5,     0,     6,     1,
       4,     8,     0,     0,     0,     0,     7,     0,     8,    10,
       0,     9,    13,     0,     0,    18,    19,     0,    21,    15,
       0,    11,     0,     0,    20,    22,    23,    16,    25,    25,
       0,    27,    26,    58,    76,     0,     0,     0,     0,     0,
       0,    38,     0,    30,     0,    27,    29,     0,    39,    40,
      48,    52,    60,    31,    32,    34,    35,    36,    33,    59,
       0,    63,    76,     0,     0,     0,    59,    61,     0,     0,
      70,     0,     0,    24,    28,    37,    43,    44,    42,    45,
      46,    47,    50,    51,     0,     0,    54,    55,    56,     0,
       0,     0,    65,     0,    64,    72,    74,    73,     0,     0,
      71,    57,    41,    49,    53,     0,    77,     0,    62,     0,
       0,    75,    66,    67,    69,     0,    68
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
    -108,  -108,    95,  -108,    28,    -8,    21,  -108,  -108,  -108,
    -108,    85,  -108,    86,  -108,    87,    59,  -107,  -108,   -45,
       3,  -108,    15,  -108,    22,  -108,   -44,  -108,  -108,    -4,
    -108,  -108,  -108,  -108,  -108,  -108,   -41
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     3,     4,     5,     6,    12,     7,     8,    15,    33,
      24,    25,    26,    53,    38,    41,    54,    55,    56,    57,
      58,    94,    59,    95,    60,    99,    61,    62,   103,   104,
      63,    64,    65,    66,    67,    68,    76
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      69,    75,    11,    77,    73,    81,    19,    82,     1,     2,
      43,    44,   123,   124,    69,    45,    46,    70,   126,    31,
      71,    43,    44,    74,    47,   101,   102,    13,    48,    14,
      49,    50,    51,   108,   109,    47,    52,     9,    36,    43,
      44,    23,    43,    44,     1,    22,    13,    52,    14,   -14,
      16,    23,    17,    47,    18,   114,    47,    92,    93,    40,
      40,    80,    96,    97,    98,    52,    39,    39,    52,    20,
      21,    28,   102,    27,    32,    72,   -17,    29,    69,    69,
      30,    35,    36,    85,    69,    86,    87,    88,    89,    90,
      91,    92,    93,    78,    79,    83,    70,   105,   106,   100,
      10,   107,   110,   115,   111,   116,   125,   117,   121,   112,
     118,   119,   120,   122,    84,    34,     0,   113,     0,    37,
       0,     0,     0,     0,     0,     0,    42
};

static const yytype_int8 yycheck[] =
{
      41,    46,     4,    47,    45,    50,    14,    52,     6,     7,
       3,     4,   119,   120,    55,     8,     9,    26,   125,    27,
      29,     3,     4,     5,    17,    70,    71,    26,    21,    28,
      23,    24,    25,    78,    79,    17,    29,     0,    31,     3,
       4,    20,     3,     4,     6,     7,    26,    29,    28,    29,
      25,    30,     3,    17,     4,    99,    17,    16,    17,    38,
      39,    25,    18,    19,    20,    29,    38,    39,    29,    29,
      27,     4,   117,    28,    26,     4,    30,    30,   119,   120,
      28,    27,    31,    25,   125,    10,    11,    12,    13,    14,
      15,    16,    17,    29,    29,    32,    26,    25,    25,    33,
       5,    25,    25,   100,    30,    27,    22,    28,    25,    94,
      30,    30,    30,   117,    55,    30,    -1,    95,    -1,    33,
      -1,    -1,    -1,    -1,    -1,    -1,    39
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     6,     7,    35,    36,    37,    38,    40,    41,     0,
      36,     4,    39,    26,    28,    42,    25,     3,     4,    39,
      29,    27,     7,    40,    44,    45,    46,    28,     4,    30,
      28,    39,    26,    43,    45,    27,    31,    47,    48,    38,
      40,    49,    49,     3,     4,     8,     9,    17,    21,    23,
      24,    25,    29,    47,    50,    51,    52,    53,    54,    56,
      58,    60,    61,    64,    65,    66,    67,    68,    69,    70,
      26,    29,     4,    70,     5,    53,    70,    60,    29,    29,
      25,    53,    53,    32,    50,    25,    10,    11,    12,    13,
      14,    15,    16,    17,    55,    57,    18,    19,    20,    59,
      33,    53,    53,    62,    63,    25,    25,    25,    53,    53,
      25,    30,    56,    58,    60,    54,    27,    28,    30,    30,
      30,    25,    63,    51,    51,    22,    51
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    34,    35,    36,    36,    37,    37,    38,    39,    39,
      39,    39,    40,    40,    42,    43,    41,    44,    44,    45,
      45,    46,    46,    48,    47,    49,    49,    50,    50,    51,
      51,    51,    51,    51,    51,    51,    51,    52,    52,    53,
      54,    54,    55,    55,    55,    55,    55,    55,    56,    56,
      57,    57,    58,    58,    59,    59,    59,    60,    60,    60,
      60,    60,    61,    62,    62,    63,    63,    64,    64,    65,
      66,    66,    67,    68,    68,    69,    70,    70
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     2,     1,     1,     3,     1,     4,
       3,     6,     1,     1,     0,     0,     8,     1,     1,     1,
       3,     2,     4,     0,     5,     0,     2,     0,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     2,     1,     1,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     3,
       1,     1,     1,     3,     1,     1,     1,     3,     1,     1,
       1,     2,     4,     0,     1,     1,     3,     5,     7,     5,
       2,     3,     3,     3,     3,     4,     1,     4
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
#line 88 "lab9.y" /* yacc.c:1646  */
    {PROGRAM = (yyvsp[0].node);}
#line 1400 "y.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 91 "lab9.y" /* yacc.c:1646  */
    {(yyval.node) = (yyvsp[0].node);}
#line 1406 "y.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 93 "lab9.y" /* yacc.c:1646  */
    {
                            (yyval.node) = (yyvsp[-1].node);
                            (yyval.node) -> next = (yyvsp[0].node);
                        }
#line 1415 "y.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 99 "lab9.y" /* yacc.c:1646  */
    {(yyval.node) = (yyvsp[0].node);}
#line 1421 "y.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 100 "lab9.y" /* yacc.c:1646  */
    {(yyval.node) = (yyvsp[0].node);}
#line 1427 "y.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 104 "lab9.y" /* yacc.c:1646  */
    {
                        // need to update all elements to the list to the type
                        // populate s1 connected list with the defined type
                        ASTnode *p = (yyvsp[-1].node);
                        while (p != NULL)
                        {
                            p -> my_data_type = (yyvsp[-2].d_type);
                            
                            // if variable is already in the symbol table, BARF
                            if (Search(p -> name, LEVEL, 0) != NULL)
                            {
                                yyerror(p -> name);
                                yyerror("Symbol already defined");
                                exit(1);
                            }
                            if (p -> value == 0)
                            {
                                // if variable is a scalar
                                p -> symbol = Insert(p -> name, p -> my_data_type, SYM_SCALAR, LEVEL, 1, OFFSET);
                                OFFSET += 1;
                            }
                            else
                            {
                                // if variable is an array
                                p -> symbol = Insert(p -> name, p -> my_data_type, SYM_ARRAY, LEVEL, p -> value, OFFSET);
                                OFFSET += p -> value;
                            }
                            p = p -> s1;
                        }
                        (yyval.node) = (yyvsp[-1].node);
                    }
#line 1463 "y.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 139 "lab9.y" /* yacc.c:1646  */
    {
                        (yyval.node) = ASTCreateNode(A_VARDEC);
                        (yyval.node) -> name = (yyvsp[0].string);
                        // value is -1 if not an array
                    }
#line 1473 "y.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 145 "lab9.y" /* yacc.c:1646  */
    {  
                        (yyval.node) = ASTCreateNode(A_VARDEC);
                        (yyval.node) -> name = (yyvsp[-3].string);
                        (yyval.node) -> value = (yyvsp[-1].value);
                    }
#line 1483 "y.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 151 "lab9.y" /* yacc.c:1646  */
    {
                        (yyval.node) = ASTCreateNode(A_VARDEC);
                        (yyval.node) -> name = (yyvsp[-2].string);
                        (yyval.node) -> s1 = (yyvsp[0].node);
                        // value is -1 if not an array
                    }
#line 1494 "y.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 158 "lab9.y" /* yacc.c:1646  */
    {
                        (yyval.node) = ASTCreateNode(A_VARDEC);
                        (yyval.node) -> name = (yyvsp[-5].string);
                        (yyval.node) -> value = (yyvsp[-3].value);
                        (yyval.node) -> s1 = (yyvsp[0].node);
                    }
#line 1505 "y.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 166 "lab9.y" /* yacc.c:1646  */
    {(yyval.d_type) = A_INTTYPE;}
#line 1511 "y.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 167 "lab9.y" /* yacc.c:1646  */
    {(yyval.d_type) = A_VOIDTYPE;}
#line 1517 "y.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 171 "lab9.y" /* yacc.c:1646  */
    {
                        // check to see if function is defined in symbol table
                        if (Search((yyvsp[0].string), LEVEL, 0) != NULL)
                        {
                            // function is already defined, BARF
                            yyerror((yyvsp[0].string));
                            yyerror("Function name already in use");
                            exit(1);
                        }
                        // function name is not in symbol table, insert it
                        Insert((yyvsp[0].string), (yyvsp[-1].d_type), SYM_FUNCTION, LEVEL, 0, 0);

                        // setup offsets before entering function
                        G_OFFSET = OFFSET;
                        OFFSET = 2;
                        MAX_OFFSET = OFFSET;
                    }
#line 1539 "y.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 189 "lab9.y" /* yacc.c:1646  */
    {
                        /* obtain symbol table entry for current function and declare
                        its param values to be those pointed to by Params
                        */
                        Search((yyvsp[-4].string), LEVEL, 0) -> fparms = (yyvsp[-1].node);
                    }
#line 1550 "y.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 196 "lab9.y" /* yacc.c:1646  */
    {
                        (yyval.node) = ASTCreateNode(A_FUNCTIONDEC);
                        (yyval.node) -> name = (yyvsp[-6].string);
                        (yyval.node) -> my_data_type = (yyvsp[-7].d_type);
                        (yyval.node) -> s1 = (yyvsp[-3].node);
                        (yyval.node) -> s2 = (yyvsp[0].node);

                        (yyval.node) -> symbol = Search((yyvsp[-6].string), LEVEL, 0);

                        /* officially set offset of current function to the total that was
                        calculated throughout the offset
                        */
                        (yyval.node) -> symbol -> offset = MAX_OFFSET;

                        OFFSET = G_OFFSET; // resets offset for global variables
                    }
#line 1571 "y.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 214 "lab9.y" /* yacc.c:1646  */
    {(yyval.node) = NULL;}
#line 1577 "y.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 215 "lab9.y" /* yacc.c:1646  */
    {(yyval.node) = (yyvsp[0].node);}
#line 1583 "y.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 218 "lab9.y" /* yacc.c:1646  */
    {(yyval.node) = (yyvsp[0].node);}
#line 1589 "y.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 220 "lab9.y" /* yacc.c:1646  */
    {
                    (yyval.node) = (yyvsp[-2].node);
                    (yyval.node) -> next = (yyvsp[0].node);
                }
#line 1598 "y.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 227 "lab9.y" /* yacc.c:1646  */
    {
                    // if param with same name as another is declared for a function
                    if (Search((yyvsp[0].string), LEVEL + 1, 0) != NULL)
                    {
                        yyerror((yyvsp[0].string));
                        yyerror("Duplicate parameter in function definition");
                        exit(1);
                    }

                    (yyval.node) = ASTCreateNode(A_PARAM);
                    (yyval.node) -> name = (yyvsp[0].string);
                    (yyval.node) -> my_data_type = (yyvsp[-1].d_type);

                    (yyval.node) -> symbol = Insert((yyval.node) -> name, (yyval.node) -> my_data_type, SYM_SCALAR, LEVEL + 1, 1, OFFSET);
                    OFFSET += 1;
                }
#line 1619 "y.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 244 "lab9.y" /* yacc.c:1646  */
    {
                            if (Search((yyvsp[-2].string), LEVEL + 1, 0) != NULL)
                            {
                                yyerror((yyvsp[-2].string));
                                yyerror("Duplicate parameter in function definition");
                                exit(1);
                            }

                            (yyval.node) = ASTCreateNode(A_PARAM);
                            (yyval.node) -> name = (yyvsp[-2].string);
                            (yyval.node) -> my_data_type = (yyvsp[-3].d_type);
                            // value is -1 if parameter is an array
                            (yyval.node) -> value = -1;

                            (yyval.node) -> symbol = Insert((yyval.node) -> name, (yyval.node) -> my_data_type, SYM_ARRAY, LEVEL + 1, 1, OFFSET);
                            OFFSET += 1;
                        }
#line 1641 "y.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 263 "lab9.y" /* yacc.c:1646  */
    {LEVEL++;}
#line 1647 "y.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 265 "lab9.y" /* yacc.c:1646  */
    {
                        (yyval.node) = ASTCreateNode(A_COMPOUND);
                        (yyval.node) -> s1 = (yyvsp[-2].node);
                        (yyval.node) -> s2 = (yyvsp[-1].node);
                        // display state of symbol table after exiting the function
                        if (mydebug)
                        {
                            Display();
                        }
                        if (OFFSET > MAX_OFFSET)
                        {
                            MAX_OFFSET = OFFSET;
                        }

                        // delete symbols that were defined under this function's scope
                        OFFSET -= Delete(LEVEL);
                        LEVEL--;
                    }
#line 1670 "y.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 285 "lab9.y" /* yacc.c:1646  */
    {(yyval.node) = NULL;}
#line 1676 "y.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 287 "lab9.y" /* yacc.c:1646  */
    {
                            (yyval.node) = (yyvsp[-1].node);
                            (yyval.node) -> next = (yyvsp[0].node);
                        }
#line 1685 "y.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 293 "lab9.y" /* yacc.c:1646  */
    {(yyval.node) = NULL;}
#line 1691 "y.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 295 "lab9.y" /* yacc.c:1646  */
    {
                        (yyval.node) = (yyvsp[-1].node);
                        (yyval.node) -> next = (yyvsp[0].node);
                    }
#line 1700 "y.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 301 "lab9.y" /* yacc.c:1646  */
    {(yyval.node) = (yyvsp[0].node);}
#line 1706 "y.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 302 "lab9.y" /* yacc.c:1646  */
    {(yyval.node) = (yyvsp[0].node);}
#line 1712 "y.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 303 "lab9.y" /* yacc.c:1646  */
    {(yyval.node) = (yyvsp[0].node);}
#line 1718 "y.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 304 "lab9.y" /* yacc.c:1646  */
    {(yyval.node) = (yyvsp[0].node);}
#line 1724 "y.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 305 "lab9.y" /* yacc.c:1646  */
    {(yyval.node) = (yyvsp[0].node);}
#line 1730 "y.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 306 "lab9.y" /* yacc.c:1646  */
    {(yyval.node) = (yyvsp[0].node);}
#line 1736 "y.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 307 "lab9.y" /* yacc.c:1646  */
    {(yyval.node) = (yyvsp[0].node);}
#line 1742 "y.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 308 "lab9.y" /* yacc.c:1646  */
    {(yyval.node) = (yyvsp[0].node);}
#line 1748 "y.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 312 "lab9.y" /* yacc.c:1646  */
    {
                        (yyval.node) = ASTCreateNode(A_EXPRSTAT);
                        (yyval.node) -> s1 = (yyvsp[-1].node);
                    }
#line 1757 "y.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 316 "lab9.y" /* yacc.c:1646  */
    {(yyval.node) = ASTCreateNode(A_EXPRSTAT);}
#line 1763 "y.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 319 "lab9.y" /* yacc.c:1646  */
    {(yyval.node) = (yyvsp[0].node);}
#line 1769 "y.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 322 "lab9.y" /* yacc.c:1646  */
    {(yyval.node) = (yyvsp[0].node);}
#line 1775 "y.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 324 "lab9.y" /* yacc.c:1646  */
    {
                            if ((yyvsp[-2].node) -> my_data_type != (yyvsp[0].node) -> my_data_type)
                            {
                                yyerror("Type mismatch in comparison");
                                exit(1);
                            }
                            (yyval.node) = ASTCreateNode(A_EXPR);
                            (yyval.node) -> s1 = (yyvsp[-2].node);
                            (yyval.node) -> s2 = (yyvsp[0].node);
                            (yyval.node) -> operator = (yyvsp[-1].operator);
                            // synthesize data type of expression
                            (yyval.node) -> my_data_type = (yyvsp[-2].node) -> my_data_type;
                            (yyval.node) -> name = CreateTemp();
                            // insert temp symbol into symbol table
                            (yyval.node) -> symbol = Insert((yyval.node) -> name, (yyvsp[-2].node) -> my_data_type, SYM_SCALAR, LEVEL, 1, OFFSET);
                            OFFSET += 1;
                        }
#line 1797 "y.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 343 "lab9.y" /* yacc.c:1646  */
    {(yyval.operator) = A_LE;}
#line 1803 "y.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 344 "lab9.y" /* yacc.c:1646  */
    {(yyval.operator) = A_LT;}
#line 1809 "y.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 345 "lab9.y" /* yacc.c:1646  */
    {(yyval.operator) = A_GT;}
#line 1815 "y.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 346 "lab9.y" /* yacc.c:1646  */
    {(yyval.operator) = A_GE;}
#line 1821 "y.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 347 "lab9.y" /* yacc.c:1646  */
    {(yyval.operator) = A_E;}
#line 1827 "y.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 348 "lab9.y" /* yacc.c:1646  */
    {(yyval.operator) = A_NE;}
#line 1833 "y.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 351 "lab9.y" /* yacc.c:1646  */
    {(yyval.node) = (yyvsp[0].node);}
#line 1839 "y.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 353 "lab9.y" /* yacc.c:1646  */
    {
                        if ((yyvsp[-2].node) -> my_data_type != (yyvsp[0].node) -> my_data_type)
                        {
                            yyerror("Type mismatch in calculation");
                            exit(1);
                        }
                        (yyval.node) = ASTCreateNode(A_EXPR);
                        (yyval.node) -> s1 = (yyvsp[-2].node);
                        (yyval.node) -> s2 = (yyvsp[0].node);
                        (yyval.node) -> operator = (yyvsp[-1].operator);
                        // synthesize data type of expression
                        (yyval.node) -> my_data_type = (yyvsp[-2].node) -> my_data_type;
                        // create temporary symbol to store result of expression
                        (yyval.node) -> name = CreateTemp();
                        // insert temp symbol into symbol table
                        (yyval.node) -> symbol = Insert((yyval.node) -> name, (yyvsp[-2].node) -> my_data_type, SYM_SCALAR, LEVEL, 1, OFFSET);
                        OFFSET += 1;
                    }
#line 1862 "y.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 373 "lab9.y" /* yacc.c:1646  */
    {(yyval.operator) = A_PLUS;}
#line 1868 "y.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 374 "lab9.y" /* yacc.c:1646  */
    {(yyval.operator) = A_MINUS;}
#line 1874 "y.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 377 "lab9.y" /* yacc.c:1646  */
    {(yyval.node) = (yyvsp[0].node);}
#line 1880 "y.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 379 "lab9.y" /* yacc.c:1646  */
    {
                if ((yyvsp[-2].node) -> my_data_type != (yyvsp[0].node) -> my_data_type)
                {
                    yyerror("Type mismatch in calculation");
                    exit(1);
                }
                (yyval.node) = ASTCreateNode(A_EXPR);
                (yyval.node) -> s1 = (yyvsp[-2].node);
                (yyval.node) -> s2 = (yyvsp[0].node);
                (yyval.node) -> operator = (yyvsp[-1].operator);
                // synthesize data type of expression
                (yyval.node) -> my_data_type = (yyvsp[-2].node) -> my_data_type;
                // create temporary symbol to store result of expression
                (yyval.node) -> name = CreateTemp();
                // insert temp symbol into symbol table
                (yyval.node) -> symbol = Insert((yyval.node) -> name, (yyvsp[-2].node) -> my_data_type, SYM_SCALAR, LEVEL, 1, OFFSET);
                OFFSET += 1;
            }
#line 1903 "y.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 399 "lab9.y" /* yacc.c:1646  */
    {(yyval.operator) = A_TIMES;}
#line 1909 "y.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 400 "lab9.y" /* yacc.c:1646  */
    {(yyval.operator) = A_DIVIDE;}
#line 1915 "y.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 401 "lab9.y" /* yacc.c:1646  */
    {(yyval.operator) = A_MOD;}
#line 1921 "y.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 404 "lab9.y" /* yacc.c:1646  */
    {(yyval.node) = (yyvsp[-1].node);}
#line 1927 "y.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 406 "lab9.y" /* yacc.c:1646  */
    {
                (yyval.node) = ASTCreateNode(A_NUM);
                (yyval.node) -> value = (yyvsp[0].value);
                // data type of numbers will be int
                (yyval.node) -> my_data_type = A_INTTYPE;
            }
#line 1938 "y.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 412 "lab9.y" /* yacc.c:1646  */
    {(yyval.node) = (yyvsp[0].node);}
#line 1944 "y.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 413 "lab9.y" /* yacc.c:1646  */
    {(yyval.node) = (yyvsp[0].node);}
#line 1950 "y.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 415 "lab9.y" /* yacc.c:1646  */
    {
                // treat neg. nums. as expression with one argument
                (yyval.node) = ASTCreateNode(A_EXPR);
                (yyval.node) -> operator = A_UMINUS;
                (yyval.node) -> s1 = (yyvsp[0].node);
            }
#line 1961 "y.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 424 "lab9.y" /* yacc.c:1646  */
    {
                    struct SymbTab *p;
                    p = Search((yyvsp[-3].string), 0, 0);
                    if (p == NULL)
                    {
                        // called function that is not defined
                        yyerror((yyvsp[-3].string));
                        yyerror("Called function that is not defined");
                        exit(1);
                    }
                    // name checks out, but is it a function?
                    if (p -> SubType != SYM_FUNCTION)
                    {
                        yyerror((yyvsp[-3].string));
                        yyerror("is not defined as a function");
                        exit(1);
                    }
                    
                    /* verify formal parameters and actual arguments are
                    the same type and length*/ 

                    if (checkParams((yyvsp[-1].node), p -> fparms) == 0)
                    {
                        yyerror((yyvsp[-3].string));
                        yyerror("arguments do not match declared formal parameters");
                        exit(1);
                    }

                    (yyval.node) = ASTCreateNode(A_CALL);
                    (yyval.node) -> name = (yyvsp[-3].string);
                    (yyval.node) -> s1 = (yyvsp[-1].node);
                    (yyval.node) -> symbol = p;
                    // declare type of function call (for type checking)
                    (yyval.node) -> my_data_type = p -> Declared_Type;
                }
#line 2001 "y.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 461 "lab9.y" /* yacc.c:1646  */
    {(yyval.node) = NULL;}
#line 2007 "y.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 462 "lab9.y" /* yacc.c:1646  */
    {(yyval.node) = (yyvsp[0].node);}
#line 2013 "y.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 466 "lab9.y" /* yacc.c:1646  */
    {
                            (yyval.node) = ASTCreateNode(A_ARG);
                            (yyval.node) -> s1 = (yyvsp[0].node);
                            // create temp symbol for the argument and store it in the symbol table
                            (yyval.node) -> name = CreateTemp();
                            (yyval.node) -> symbol = Insert((yyval.node) -> name, (yyvsp[0].node) -> my_data_type, SYM_SCALAR, LEVEL, 1, OFFSET);
                            OFFSET += 1;
                        }
#line 2026 "y.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 475 "lab9.y" /* yacc.c:1646  */
    {
                            (yyval.node) = ASTCreateNode(A_ARG);
                            (yyval.node) -> s1 = (yyvsp[-2].node);
                            (yyval.node) -> next = (yyvsp[0].node);
                            // create temp symbol for the argument and store it in the symbol table
                            (yyval.node) -> name = CreateTemp();
                            (yyval.node) -> symbol = Insert((yyval.node) -> name, (yyvsp[-2].node) -> my_data_type, SYM_SCALAR, LEVEL, 1, OFFSET);
                            OFFSET += 1;
                        }
#line 2040 "y.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 487 "lab9.y" /* yacc.c:1646  */
    {
                        // s2 is a node that "contains" the if body and the else body
                        (yyval.node) = ASTCreateNode(A_IF);
                        (yyval.node) -> s1 = (yyvsp[-2].node);
                        (yyval.node) -> s2 = ASTCreateNode(A_IFBODY);
                        (yyval.node) -> s2 -> s1 = (yyvsp[0].node); // if body
                        // no else body
                    }
#line 2053 "y.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 496 "lab9.y" /* yacc.c:1646  */
    {
                        (yyval.node) = ASTCreateNode(A_IF);
                        (yyval.node) -> s1 = (yyvsp[-4].node);
                        (yyval.node) -> s2 = ASTCreateNode(A_IFBODY);
                        (yyval.node) -> s2 -> s1 = (yyvsp[-2].node); // if body
                        // else body is assigned to s2 -> s2
                        (yyval.node) -> s2 -> s2 = (yyvsp[0].node);
                    }
#line 2066 "y.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 507 "lab9.y" /* yacc.c:1646  */
    {
                        (yyval.node) = ASTCreateNode(A_WHILE);
                        (yyval.node) -> s1 = (yyvsp[-2].node);
                        (yyval.node) -> s2 = (yyvsp[0].node);
                    }
#line 2076 "y.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 514 "lab9.y" /* yacc.c:1646  */
    {(yyval.node) = ASTCreateNode(A_RETURN);}
#line 2082 "y.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 516 "lab9.y" /* yacc.c:1646  */
    {
                    (yyval.node) = ASTCreateNode(A_RETURN);
                    (yyval.node) -> s1 = (yyvsp[-1].node);
                }
#line 2091 "y.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 523 "lab9.y" /* yacc.c:1646  */
    {
                    (yyval.node) = ASTCreateNode(A_READ);
                    (yyval.node) -> s1 = (yyvsp[-1].node);
                }
#line 2100 "y.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 530 "lab9.y" /* yacc.c:1646  */
    {
                    (yyval.node) = ASTCreateNode(A_WRITE);
                    (yyval.node) -> s1 = (yyvsp[-1].node);
                }
#line 2109 "y.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 535 "lab9.y" /* yacc.c:1646  */
    {
                    (yyval.node) = ASTCreateNode(A_WRITE);
                    (yyval.node) -> name = (yyvsp[-1].string);
                }
#line 2118 "y.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 542 "lab9.y" /* yacc.c:1646  */
    {
                        if ((yyvsp[-3].node) -> my_data_type != (yyvsp[-1].node) -> my_data_type)
                        {
                            yyerror("Conflicting types at assignment statment");
                            exit(1);
                        }
                        (yyval.node) = ASTCreateNode(A_ASSIGN);
                        (yyval.node) -> s1 = (yyvsp[-3].node);
                        (yyval.node) -> s2 = (yyvsp[-1].node);
                        (yyval.node) -> name = CreateTemp();
                        (yyval.node) -> symbol = Insert((yyval.node) -> name, (yyvsp[-3].node) -> my_data_type, SYM_SCALAR, LEVEL, 1, OFFSET);
                        OFFSET += 1;
                    }
#line 2136 "y.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 557 "lab9.y" /* yacc.c:1646  */
    {
                struct SymbTab *p;
                p = Search((yyvsp[0].string), LEVEL, 1);
                if (p == NULL)
                {
                    // reference to a symbol NOT in table
                    yyerror((yyvsp[0].string));
                    yyerror("Symbol used but not defined");
                    exit(1);
                }
                if (p -> SubType != SYM_SCALAR)
                {
                    // reference to a non-scalar variable
                    yyerror((yyvsp[0].string));
                    yyerror("Incorrect symbol type usage");
                    exit(1);
                }
                (yyval.node) = ASTCreateNode(A_VAR);
                (yyval.node) -> name = (yyvsp[0].string);
                (yyval.node) -> symbol = p;
                (yyval.node) -> my_data_type = p -> Declared_Type;
            }
#line 2163 "y.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 580 "lab9.y" /* yacc.c:1646  */
    {  
                struct SymbTab *p;
                p = Search((yyvsp[-3].string), LEVEL, 1);
                if (p == NULL)
                {
                    // reference to a symbol NOT in table
                    yyerror((yyvsp[-3].string));
                    yyerror("Symbol used but not defined");
                    exit(1);
                }
                if (p -> SubType != SYM_ARRAY)
                {
                    // reference to a non-scalar variable
                    yyerror((yyvsp[-3].string));
                    yyerror("Incorrect symbol type usage");
                    exit(1);
                }
                (yyval.node) = ASTCreateNode(A_VAR);
                (yyval.node) -> name = (yyvsp[-3].string);
                (yyval.node) -> s1 = (yyvsp[-1].node);
                (yyval.node) -> symbol = p;
                (yyval.node) -> my_data_type = p -> Declared_Type;
            }
#line 2191 "y.tab.c" /* yacc.c:1646  */
    break;


#line 2195 "y.tab.c" /* yacc.c:1646  */
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
#line 605 "lab9.y" /* yacc.c:1906  */
	/* end of rules, start of program */

/*
* call main parsing function used by yacc
*/
int main(int argc, char *argv[])
{
    FILE *fp;
    int i;
    char s[100];

    // option -d turn on debug
    // option -o output file name
    for (i = 0; i < argc; i++) {
        if (strcmp(argv[i], "-d") == 0)
        {
            mydebug = 1;
        }
        if (strcmp(argv[i], "-o") == 0)
        {
            strcpy(s, argv[i + 1]);
            strcat(s, ".asm");
            //printf("File name is %s\n", s);
        }
    }

    fp = fopen(s, "w");
    if (fp == NULL)
    {
        printf("cannot open %s\n", s);
        exit(1);
    }

    yyparse();

    if (mydebug)
    {
        printf("Finished parsing\n");
    }
    
    if (mydebug) 
    {
        Display(); // shows our global variables and functions
    }

    if (mydebug)
    {
        printf("\n\n AST PRINT \n\n");
    }

    if (mydebug)
    {
        ASTprint(0, PROGRAM);
    }
    EMIT(PROGRAM, fp);
}
