/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "ecc.y"

#include "ast/program.hpp"
#include <map>
Program *program;
map<string, Number *> constvar;
map<string, AggregateType *> aggrdef;

#line 78 "parser.cpp"

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

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_PARSER_HPP_INCLUDED
# define YY_YY_PARSER_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 13 "ecc.y"

#include <iostream>
#include <string>
#include <vector>
#include <stdint.h>
#include "ast/basic.hpp"
#include "ast/expression.hpp"
#include "ast/statement.hpp"
#include "ast/declaration.hpp"
#include "ast/type.hpp"
#include "ast/program.hpp"

using namespace std;

extern int yylineno;
extern char *yytext;
extern int yylex();

void yyerror(string s);
void yywarning(string s, string addition);

static void debug(string s);
static Expression *calculate(Expression *a, enum op_type op);
static Expression *calculate(Expression *a, Expression *b, enum op_type op);
static Expression *calculate(Expression *a, Expression *b, Expression *c, enum op_type op);

#line 148 "parser.cpp"

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    CHAR = 258,
    SHORT = 259,
    INT = 260,
    LONG = 261,
    FLOAT = 262,
    DOUBLE = 263,
    STRUCT = 264,
    ENUM = 265,
    UNION = 266,
    VOID = 267,
    AUTO = 268,
    REGISTER = 269,
    EXTERN = 270,
    CONST = 271,
    UNSIGNED = 272,
    SIGNED = 273,
    VOLATILE = 274,
    STATIC = 275,
    IF = 276,
    ELSE = 277,
    FOR = 278,
    DO = 279,
    WHILE = 280,
    BREAK = 281,
    CONTINUE = 282,
    SWITCH = 283,
    CASE = 284,
    DEFAULT = 285,
    GOTO = 286,
    ADD = 287,
    SUB = 288,
    MULORDEREFERENCE = 289,
    DIV = 290,
    MOD = 291,
    ADDASSIGN = 292,
    SUBASSIGN = 293,
    MULASSIGN = 294,
    DIVASSIGN = 295,
    MODASSIGN = 296,
    ANDORADDRESSOF = 297,
    OR = 298,
    XOR = 299,
    NOT = 300,
    SL = 301,
    SR = 302,
    ANDASSIGN = 303,
    ORASSIGN = 304,
    XORASSIGN = 305,
    SLASSIGN = 306,
    SRASSIGN = 307,
    ANDAND = 308,
    OROR = 309,
    NOTNOT = 310,
    LT = 311,
    GT = 312,
    GEQ = 313,
    LEQ = 314,
    NEQ = 315,
    EQ = 316,
    ASSIGN = 317,
    INC = 318,
    DEC = 319,
    POSITIVE = 320,
    NEGATIVE = 321,
    TYPEDEF = 322,
    SIZEOF = 323,
    RETURN = 324,
    DOTDOTDOT = 325,
    DELIM = 326,
    COMMA = 327,
    COLON = 328,
    QUESTION = 329,
    DOT = 330,
    TO = 331,
    LP = 332,
    RP = 333,
    LB = 334,
    RB = 335,
    LC = 336,
    RC = 337,
    NUMCHAR = 338,
    NUMSHORT = 339,
    NUMINT = 340,
    NUMLONG = 341,
    NUMFLOAT = 342,
    NUMDOUBLE = 343,
    STRING = 344,
    IDENTIFIER = 345,
    TYPENAME = 346
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 40 "ecc.y"

    union union_num num;
    string *stringValue;
    enum op_type op;
    
    Program *program;
    Node *node;

    TypeSpecifier *type;
    Qualifier *qual;
    AggregateType *aggrtype;
    pair<vector<TypeSpecifier *> *, vector<Identifier *> *> *member;
    vector<pair<vector<TypeSpecifier *> *, vector<Identifier *> *> *> *members;

    Declaration *declaration;
    VariableDeclaration *variableDeclaration;
    vector<VariableDeclaration *> *vars;
    Parameter *param;
    FunctionDeclaration *functionDeclaration;

    Statement *statement;
    CompoundStatement *compoundStatement;
    ExpressionStatement *expressionStatement;
    SelectionStatement *selectionStatement;
    IterationStatement *iterationStatement;

    Expression *expression;
    Identifier *identifier;
    vector<Identifier *> *ids;
    vector<Expression *> *exprs;
    Number *number;

#line 284 "parser.cpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_HPP_INCLUDED  */



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
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
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
#define YYFINAL  45
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1826

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  92
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  67
/* YYNRULES -- Number of rules.  */
#define YYNRULES  226
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  378

#define YYUNDEFTOK  2
#define YYMAXUTOK   346


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
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
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   135,   135,   138,   139,   142,   143,   146,   147,   152,
     153,   160,   203,   206,   207,   210,   211,   212,   213,   214,
     215,   218,   219,   222,   223,   226,   227,   228,   229,   230,
     233,   234,   235,   236,   237,   238,   239,   240,   241,   242,
     243,   244,   247,   248,   251,   265,   266,   269,   270,   273,
     274,   277,   314,   315,   316,   317,   320,   321,   324,   329,
     330,   333,   334,   335,   338,   339,   342,   343,   346,   347,
     350,   351,   352,   357,   358,   359,   360,   363,   364,   365,
     370,   373,   374,   383,   384,   387,   388,   391,   415,   416,
     419,   420,   423,   424,   425,   428,   429,   438,   446,   449,
     450,   451,   454,   455,   456,   457,   458,   459,   460,   461,
     462,   465,   466,   467,   468,   469,   470,   473,   476,   477,
     480,   481,   484,   485,   486,   487,   490,   491,   494,   495,
     496,   503,   504,   505,   506,   507,   508,   509,   510,   511,
     512,   515,   516,   517,   518,   519,   522,   523,   526,   527,
     534,   535,   536,   537,   538,   539,   540,   541,   542,   543,
     544,   547,   548,   551,   561,   562,   565,   566,   569,   570,
     573,   574,   577,   578,   581,   582,   583,   586,   587,   588,
     589,   590,   593,   594,   595,   598,   599,   600,   603,   604,
     605,   606,   609,   610,   616,   617,   622,   627,   628,   629,
     638,   639,   640,   641,   642,   643,   646,   647,   652,   657,
     662,   663,   664,   669,   676,   677,   678,   679,   682,   683,
     686,   689,   690,   691,   692,   693,   694
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "CHAR", "SHORT", "INT", "LONG", "FLOAT",
  "DOUBLE", "STRUCT", "ENUM", "UNION", "VOID", "AUTO", "REGISTER",
  "EXTERN", "CONST", "UNSIGNED", "SIGNED", "VOLATILE", "STATIC", "IF",
  "ELSE", "FOR", "DO", "WHILE", "BREAK", "CONTINUE", "SWITCH", "CASE",
  "DEFAULT", "GOTO", "ADD", "SUB", "MULORDEREFERENCE", "DIV", "MOD",
  "ADDASSIGN", "SUBASSIGN", "MULASSIGN", "DIVASSIGN", "MODASSIGN",
  "ANDORADDRESSOF", "OR", "XOR", "NOT", "SL", "SR", "ANDASSIGN",
  "ORASSIGN", "XORASSIGN", "SLASSIGN", "SRASSIGN", "ANDAND", "OROR",
  "NOTNOT", "LT", "GT", "GEQ", "LEQ", "NEQ", "EQ", "ASSIGN", "INC", "DEC",
  "POSITIVE", "NEGATIVE", "TYPEDEF", "SIZEOF", "RETURN", "DOTDOTDOT",
  "DELIM", "COMMA", "COLON", "QUESTION", "DOT", "TO", "LP", "RP", "LB",
  "RB", "LC", "RC", "NUMCHAR", "NUMSHORT", "NUMINT", "NUMLONG", "NUMFLOAT",
  "NUMDOUBLE", "STRING", "IDENTIFIER", "TYPENAME", "$accept", "program",
  "translation-unit", "external-decl", "function-definition", "decl",
  "decl-list", "decl-specs", "init-declarator-list", "init-declarator",
  "storage-class-specifier", "type-spec", "type-qualifier",
  "struct-or-union-spec", "struct-or-union", "struct-decl-list",
  "struct-decl", "spec-qualifier-list", "struct-declarator-list",
  "struct-declarator", "enum-spec", "enumerator-list", "enumerator",
  "declarator", "direct-declarator", "pointer", "type-qualifier-list",
  "param-type-list", "param-list", "param-decl", "id-list", "initializer",
  "initializer-list", "type-name", "abstract-declarator",
  "direct-abstract-declarator", "stat", "labeled-stat", "exp-stat",
  "compound-stat", "stat-list", "selection-stat", "iteration-stat",
  "jump-stat", "exp", "assignment-exp", "assignment-operator",
  "conditional-exp", "const-exp", "logical-or-exp", "logical-and-exp",
  "inclusive-or-exp", "exclusive-or-exp", "and-exp", "equality-exp",
  "relational-exp", "shift-expression", "additive-exp", "mult-exp",
  "cast-exp", "unary-exp", "unary-operator", "postfix-exp", "primary-exp",
  "argument-exp-list", "const", "number", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346
};
# endif

#define YYPACT_NINF (-227)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     697,  -227,  -227,  -227,  -227,  -227,  -227,  -227,   -34,  -227,
    -227,  -227,  -227,  -227,  -227,  -227,  -227,  -227,  -227,   107,
    -227,    44,  -227,  -227,    21,   697,  -227,  -227,  -227,   -14,
     961,   961,   961,  -227,    -6,  -227,   836,    93,   -35,   -64,
     -53,  -227,  -227,   107,   -28,  -227,  -227,  -227,   125,  -227,
     729,  -227,  -227,  -227,   291,   -11,   309,  -227,   836,   -14,
    -227,   818,  1226,    93,    33,   -33,  -227,   -64,  -227,  -227,
    -227,  -227,    44,  1262,   836,  -227,   291,   291,   795,  -227,
      28,   291,    -5,     6,  1112,    23,    40,    57,    47,  1664,
      59,    46,  -227,  -227,  -227,  -227,  1700,  1700,  -227,  -227,
    1736,   605,  -227,   487,  -227,  -227,  -227,  -227,  -227,  -227,
    -227,  -227,    66,   398,  -227,  -227,  -227,  -227,   972,  -227,
    -227,  -227,   150,  -227,  -227,   -31,   134,   146,   156,   206,
     185,   200,   233,   249,    68,  -227,   154,  1664,   155,  -227,
    -227,  -227,  -227,  -227,   208,  -227,  -227,    19,   190,   201,
    -227,   -24,  -227,  -227,  -227,   196,  -227,  1664,   -64,  -227,
      53,  -227,  1262,  -227,  -227,  -227,  -227,  -227,  -227,  -227,
    1664,   217,  -227,   210,   925,  1664,  1299,   260,  1664,  -227,
    -227,  1664,   231,  -227,   221,  1664,  -227,  -227,   487,  -227,
    -227,   219,   -19,   253,    89,  1112,  -227,  1042,  -227,  -227,
    -227,  1664,  1664,  1664,  1664,  1664,  1664,  1664,  1664,  1664,
    1664,  1664,  1664,  1664,  1664,  1664,  1664,  1664,  1664,  1664,
    1664,  -227,  -227,  -227,  -227,  -227,  -227,  -227,  -227,  -227,
    -227,  -227,  1664,  -227,  -227,  -227,   267,   268,  1335,  1664,
     576,  1372,  -227,    43,  -227,   133,  -227,   854,   270,  -227,
    -227,  -227,  -227,  -227,  -227,    55,  -227,  -227,    28,  1664,
    -227,    96,  1408,   234,   282,   101,   108,  -227,  -227,   272,
    -227,   608,   162,  -227,  1664,  -227,  -227,  -227,  -227,   134,
     269,   146,   156,   206,   185,   200,   200,   233,   233,   233,
     233,   249,   249,    68,    68,  -227,  -227,  -227,  -227,  -227,
    -227,  -227,  -227,   110,   -21,  -227,   283,   284,  -227,   285,
     133,   943,  1444,  -227,  -227,  -227,  1169,  -227,  -227,  -227,
    1112,  1480,   273,  1517,  1664,  1112,  1112,  -227,  -227,  1664,
    1664,  -227,  -227,  -227,  -227,  -227,  -227,   288,  -227,   287,
    -227,  -227,   341,  1112,   135,  1553,  1590,   275,   137,  -227,
    -227,  -227,  -227,  -227,  -227,  1112,  -227,  1112,  1112,   145,
    1112,   148,  1627,   297,  -227,  -227,  -227,  1112,  -227,  1112,
    1112,   157,  -227,  -227,  -227,  -227,  1112,  -227
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    30,    31,    32,    33,    34,    35,    47,     0,    48,
      36,    28,    29,    26,    42,    38,    37,    43,    27,    78,
      25,     0,    70,    41,     0,     2,     3,     5,     6,     0,
      15,    17,    19,    39,     0,    40,     0,    69,     0,     0,
      63,    81,    80,    77,     0,     1,     4,    12,     0,    21,
      23,    16,    18,    20,     0,    46,     0,    13,     0,     0,
      10,     0,     0,    68,    66,     0,    64,     0,    82,    79,
      71,    11,     0,     0,     0,     8,    53,    55,     0,    49,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   201,   200,   204,   205,     0,     0,   202,   203,
       0,     0,   121,     0,   125,   221,   222,   223,   224,   225,
     226,   216,   214,     0,   126,   111,   112,   113,     0,   114,
     115,   116,     0,   146,   148,   161,   164,   166,   168,   170,
     172,   174,   177,   182,   185,   188,   192,     0,   194,   206,
     215,   220,    14,     9,    23,    76,    90,    89,     0,    83,
      85,     0,    73,   214,   163,     0,   192,     0,     0,    62,
       0,    22,     0,    24,    92,     7,    52,    54,    45,    50,
       0,     0,    56,    58,     0,     0,     0,     0,     0,   143,
     142,     0,     0,   119,     0,     0,   195,   196,     0,   198,
     145,     0,    98,     0,     0,     0,   124,     0,   123,   127,
     120,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   154,   155,   151,   152,   153,   158,   160,   159,   156,
     157,   150,     0,   197,   212,   213,     0,     0,     0,     0,
       0,     0,    87,    99,    88,   101,    75,     0,     0,    74,
      72,    67,    65,    61,    95,     0,    60,    51,     0,     0,
      44,     0,     0,     0,     0,     0,     0,   118,   141,     0,
     144,     0,    99,    97,     0,   217,   117,   122,   147,   165,
       0,   167,   169,   171,   173,   176,   175,   178,   179,   181,
     180,   183,   184,   186,   187,   189,   190,   191,   149,   210,
     211,   209,   218,     0,     0,   110,     0,     0,   106,     0,
     100,     0,     0,    84,    86,    91,     0,    93,    57,    59,
       0,     0,     0,     0,     0,     0,     0,   199,   193,     0,
       0,   208,   207,   108,   102,   104,   109,     0,   105,     0,
      94,    96,   128,     0,     0,     0,     0,     0,     0,   131,
     130,   162,   219,   107,   103,     0,   140,     0,     0,     0,
       0,     0,     0,     0,   129,   139,   138,     0,   137,     0,
       0,     0,   132,   136,   135,   134,     0,   133
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -227,  -227,  -227,   344,  -227,    16,   188,     0,  -227,   298,
    -227,    10,   -10,  -227,  -227,   290,   -66,   -58,  -227,   121,
    -227,   314,   225,    -7,   -32,   -16,  -227,   -57,  -227,   141,
    -227,  -154,  -227,   197,  -123,  -226,   -83,  -227,  -227,   127,
     271,  -227,  -227,  -227,   -96,   -63,  -227,   -51,   -76,  -227,
     187,   183,   215,   224,   226,   140,    52,   138,   139,  -103,
     -60,  -227,  -227,  -227,  -227,  -227,  -227
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    24,    25,    26,    27,    57,    58,    59,    48,    49,
      30,    31,    32,    33,    34,    78,    79,    80,   171,   172,
      35,    65,    66,    36,    37,    38,    43,   306,   149,   150,
     151,   163,   255,   193,   307,   245,   114,   115,   116,   117,
     118,   119,   120,   121,   122,   123,   232,   124,   155,   125,
     126,   127,   128,   129,   130,   131,   132,   133,   134,   135,
     136,   137,   138,   139,   303,   140,   141
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      29,   177,   156,    42,   148,   191,    63,   194,   254,    41,
     164,   154,   169,   182,    44,    19,    28,   310,   166,   167,
      19,    45,    50,   202,   244,    29,    64,    69,    67,   156,
      51,    52,    53,    68,   233,   199,   186,   187,   154,   158,
     189,    28,    21,   203,    77,   192,   310,    39,   248,   159,
      70,   201,   144,    19,   249,    22,    40,    47,   271,   332,
     241,   147,    19,    21,    76,   144,    77,    77,    77,   273,
      81,    77,   175,   173,   142,    54,    22,   156,    19,   261,
     263,   251,   265,   176,    55,   266,    76,    76,    76,   194,
     142,    76,   194,    77,   256,   157,   240,   156,   241,   164,
     178,   170,   218,   219,   220,    21,   154,   280,   169,    22,
     156,   179,   276,    76,   199,   295,   296,   297,    22,   154,
     240,    21,   241,    14,   181,   158,    17,   316,   180,   142,
     192,   243,   183,    22,    22,   253,   184,   317,   278,   195,
     242,    19,   156,   304,   156,   156,   156,   156,   156,   156,
     156,   156,   156,   156,   156,   156,   156,   156,   156,   156,
     156,   201,   341,    60,    77,   309,   322,   275,   201,   298,
      61,   328,    62,   201,   320,   302,   272,    75,    77,   325,
     201,   156,   330,   319,    76,   143,   326,   204,   331,   205,
     154,   221,   222,   223,   224,   225,    71,    72,    76,   156,
     206,   165,   226,   227,   228,   229,   230,   201,   154,   201,
     311,    63,   312,   357,   156,   363,   231,   201,   234,   235,
     201,   200,   201,   367,   243,   344,   369,   347,   348,   201,
     236,   237,   238,    44,   239,   376,   339,   342,    74,   271,
     147,   241,   349,   350,   113,   208,   209,   147,   207,   359,
     361,   173,   156,   164,   337,   272,   210,   211,   212,   213,
     356,   154,   287,   288,   289,   290,   371,   352,   246,   156,
      73,   147,   364,   247,   365,   366,   250,   368,   351,   214,
     215,   216,   217,   259,   373,   264,   374,   375,   257,   258,
     270,   201,   268,   377,     1,     2,     3,     4,     5,     6,
       7,     8,     9,    10,   267,   323,   201,    14,    15,    16,
      17,   147,     1,     2,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      82,   274,    83,    84,    85,    86,    87,    88,    89,    90,
      91,   201,   329,    92,   345,   201,   362,   201,   285,   286,
     327,    93,   291,   292,    94,   293,   294,   299,   300,   324,
     315,   333,   334,   355,    95,   335,   353,   354,   372,    46,
     161,   174,    96,    97,    98,    99,    20,   100,   101,   318,
     102,   160,    23,   252,   197,   269,   103,   281,   314,   279,
      56,   104,   105,   106,   107,   108,   109,   110,   111,   112,
      23,     1,     2,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    82,
     282,    83,    84,    85,    86,    87,    88,    89,    90,    91,
     283,     0,    92,   284,     0,     0,     0,     0,     0,     0,
      93,     0,     0,    94,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    95,     0,     0,     0,     0,     0,     0,
       0,    96,    97,    98,    99,    20,   100,   101,     0,   102,
       0,     0,     0,     0,     0,   103,     0,     0,     0,    56,
     196,   105,   106,   107,   108,   109,   110,   111,   112,    23,
       1,     2,     3,     4,     5,     6,     7,     8,     9,    10,
       0,     0,     0,    14,    15,    16,    17,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    92,     0,     0,     0,     0,     0,     0,     0,    93,
       0,     0,    94,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    95,     0,     0,     0,     0,     0,     0,     0,
      96,    97,    98,    99,     0,   100,     0,     0,     0,     0,
       0,     0,     0,     0,   103,     0,     0,     0,     0,     0,
     105,   106,   107,   108,   109,   110,   111,   153,    23,     1,
       2,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      19,     1,     2,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    92,
       0,     0,    19,    20,     0,     0,     0,    93,     0,     0,
      94,     0,     0,   240,   305,   241,     0,     0,     0,     0,
      95,     0,     0,     0,     0,     0,    22,    23,    96,    97,
      98,    99,     0,   100,     0,    20,   190,     0,     0,     0,
       0,     0,   103,     0,     0,   271,   305,   241,   105,   106,
     107,   108,   109,   110,   111,   153,     0,     0,     0,    23,
       1,     2,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    19,     1,     2,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    20,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    21,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    22,    23,     0,
       0,    73,     0,     0,     0,     0,    20,     0,     1,     2,
       3,     4,     5,     6,     7,     8,     9,    10,     0,     0,
      56,    14,    15,    16,    17,     0,     0,     0,     0,     0,
      23,     1,     2,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,     1,
       2,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,     1,     2,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,     0,     0,   168,     0,     0,
       0,     0,     0,     0,     0,    20,    23,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   145,     0,     0,     0,
       0,     0,     0,    20,     0,     0,     0,     0,   146,    23,
       0,     0,     0,     0,     0,     0,     0,    56,     0,     0,
       0,    20,     0,     0,   313,     0,     0,    23,     1,     2,
       3,     4,     5,     6,     7,     8,     9,    10,     0,     0,
       0,    14,    15,    16,    17,    23,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,     1,     2,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    82,     0,    83,    84,    85,    86,    87,
      88,    89,    90,    91,     0,     0,    92,   260,     0,     0,
      20,     0,     0,     0,    93,     0,    23,    94,     0,     0,
       0,   336,     0,     0,     0,     0,     0,    95,    20,     0,
       0,     0,     0,     0,    23,    96,    97,    98,    99,     0,
     100,   101,     0,   102,     0,     0,     0,     0,     0,   103,
       0,     0,    23,    56,   198,   105,   106,   107,   108,   109,
     110,   111,   112,    82,     0,    83,    84,    85,    86,    87,
      88,    89,    90,    91,     0,     0,    92,     0,     0,     0,
       0,     0,     0,     0,    93,     0,     0,    94,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    95,     0,     0,
       0,     0,     0,     0,     0,    96,    97,    98,    99,     0,
     100,   101,     0,   102,     0,     0,     0,     0,     0,   103,
       0,     0,     0,    56,   277,   105,   106,   107,   108,   109,
     110,   111,   112,    82,     0,    83,    84,    85,    86,    87,
      88,    89,    90,    91,     0,     0,    92,     0,     0,     0,
       0,     0,     0,     0,    93,     0,     0,    94,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    95,     0,     0,
       0,     0,     0,     0,     0,    96,    97,    98,    99,     0,
     100,   101,     0,   102,     0,     0,     0,     0,     0,   103,
       0,     0,     0,    56,     0,   105,   106,   107,   108,   109,
     110,   111,   112,    92,     0,     0,     0,     0,     0,     0,
       0,    93,     0,     0,    94,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    95,     0,     0,     0,     0,     0,
       0,     0,    96,    97,    98,    99,     0,   100,     0,     0,
       0,     0,     0,     0,     0,     0,   103,     0,     0,     0,
     162,   340,   105,   106,   107,   108,   109,   110,   111,   153,
      92,     0,     0,     0,     0,     0,     0,     0,    93,     0,
       0,    94,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    95,     0,     0,     0,     0,     0,     0,     0,    96,
      97,    98,    99,     0,   100,     0,    92,     0,     0,     0,
       0,     0,     0,   103,    93,     0,   152,    94,     0,   105,
     106,   107,   108,   109,   110,   111,   153,    95,     0,     0,
       0,     0,     0,     0,     0,    96,    97,    98,    99,     0,
     100,     0,     0,    92,     0,     0,     0,     0,     0,   103,
       0,    93,     0,   162,    94,   105,   106,   107,   108,   109,
     110,   111,   153,     0,    95,     0,     0,     0,     0,     0,
       0,     0,    96,    97,    98,    99,     0,   100,     0,    92,
     262,     0,     0,     0,     0,     0,   103,    93,     0,     0,
      94,     0,   105,   106,   107,   108,   109,   110,   111,   153,
      95,     0,     0,     0,     0,     0,     0,     0,    96,    97,
      98,    99,     0,   100,     0,     0,    92,     0,     0,     0,
       0,     0,   103,   301,    93,     0,     0,    94,   105,   106,
     107,   108,   109,   110,   111,   153,     0,    95,     0,     0,
       0,     0,     0,     0,     0,    96,    97,    98,    99,     0,
     100,     0,    92,     0,     0,     0,     0,     0,     0,   103,
      93,     0,   308,    94,     0,   105,   106,   107,   108,   109,
     110,   111,   153,    95,     0,     0,     0,     0,     0,     0,
       0,    96,    97,    98,    99,     0,   100,     0,    92,   321,
       0,     0,     0,     0,     0,   103,    93,     0,     0,    94,
       0,   105,   106,   107,   108,   109,   110,   111,   153,    95,
       0,     0,     0,     0,     0,     0,     0,    96,    97,    98,
      99,     0,   100,     0,    92,     0,     0,     0,     0,     0,
       0,   103,    93,     0,   338,    94,     0,   105,   106,   107,
     108,   109,   110,   111,   153,    95,     0,     0,     0,     0,
       0,     0,     0,    96,    97,    98,    99,     0,   100,     0,
       0,    92,     0,     0,     0,     0,     0,   103,   343,    93,
       0,     0,    94,   105,   106,   107,   108,   109,   110,   111,
     153,     0,    95,     0,     0,     0,     0,     0,     0,     0,
      96,    97,    98,    99,     0,   100,     0,    92,   346,     0,
       0,     0,     0,     0,   103,    93,     0,     0,    94,     0,
     105,   106,   107,   108,   109,   110,   111,   153,    95,     0,
       0,     0,     0,     0,     0,     0,    96,    97,    98,    99,
       0,   100,     0,     0,    92,     0,     0,     0,     0,     0,
     103,   358,    93,     0,     0,    94,   105,   106,   107,   108,
     109,   110,   111,   153,     0,    95,     0,     0,     0,     0,
       0,     0,     0,    96,    97,    98,    99,     0,   100,     0,
       0,    92,     0,     0,     0,     0,     0,   103,   360,    93,
       0,     0,    94,   105,   106,   107,   108,   109,   110,   111,
     153,     0,    95,     0,     0,     0,     0,     0,     0,     0,
      96,    97,    98,    99,     0,   100,     0,     0,    92,     0,
       0,     0,     0,     0,   103,   370,    93,     0,     0,    94,
     105,   106,   107,   108,   109,   110,   111,   153,     0,    95,
       0,     0,     0,     0,     0,     0,     0,    96,    97,    98,
      99,     0,   100,     0,    92,     0,     0,     0,     0,     0,
       0,   103,    93,     0,     0,    94,     0,   105,   106,   107,
     108,   109,   110,   111,   153,    95,     0,     0,     0,     0,
       0,     0,     0,    96,    97,    98,    99,     0,   100,     0,
      92,     0,     0,     0,     0,     0,     0,   185,    93,     0,
       0,    94,     0,   105,   106,   107,   108,   109,   110,   111,
     153,    95,     0,     0,     0,     0,     0,     0,     0,    96,
      97,    98,    99,     0,   100,     0,     0,     0,     0,     0,
       0,     0,     0,   188,     0,     0,     0,     0,     0,   105,
     106,   107,   108,   109,   110,   111,   153
};

static const yytype_int16 yycheck[] =
{
       0,    84,    62,    19,    61,   101,    38,   103,   162,    19,
      73,    62,    78,    89,    21,    34,     0,   243,    76,    77,
      34,     0,    29,    54,   147,    25,    90,    43,    81,    89,
      30,    31,    32,    43,   137,   118,    96,    97,    89,    72,
     100,    25,    77,    74,    54,   103,   272,    81,    72,    82,
      78,    72,    59,    34,    78,    90,    90,    71,    77,    80,
      79,    61,    34,    77,    54,    72,    76,    77,    78,   192,
      81,    81,    77,    80,    58,    81,    90,   137,    34,   175,
     176,   157,   178,    77,    90,   181,    76,    77,    78,   185,
      74,    81,   188,   103,   170,    62,    77,   157,    79,   162,
      77,    73,    34,    35,    36,    77,   157,   203,   174,    90,
     170,    71,   195,   103,   197,   218,   219,   220,    90,   170,
      77,    77,    79,    16,    77,    72,    19,    72,    71,   113,
     188,   147,    73,    90,    90,    82,    90,    82,   201,    73,
     147,    34,   202,   239,   204,   205,   206,   207,   208,   209,
     210,   211,   212,   213,   214,   215,   216,   217,   218,   219,
     220,    72,   316,    36,   174,   241,   262,    78,    72,   232,
      77,   274,    79,    72,    78,   238,   192,    50,   188,    78,
      72,   241,    72,   259,   174,    58,    78,    53,    78,    43,
     241,    37,    38,    39,    40,    41,    71,    72,   188,   259,
      44,    74,    48,    49,    50,    51,    52,    72,   259,    72,
      77,   243,    79,    78,   274,    78,    62,    72,    63,    64,
      72,    71,    72,    78,   240,   321,    78,   323,   324,    72,
      75,    76,    77,   240,    79,    78,   312,   320,    50,    77,
     240,    79,   325,   326,    56,    60,    61,   247,    42,   345,
     346,   258,   312,   316,   311,   271,    56,    57,    58,    59,
     343,   312,   210,   211,   212,   213,   362,   330,    78,   329,
      62,   271,   355,    72,   357,   358,    80,   360,   329,    46,
      47,    32,    33,    73,   367,    25,   369,   370,    71,    72,
      71,    72,    71,   376,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    73,    71,    72,    16,    17,    18,
      19,   311,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    78,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    72,    73,    34,    71,    72,    71,    72,   208,   209,
      78,    42,   214,   215,    45,   216,   217,    90,    90,    77,
      90,    78,    78,    22,    55,    80,    78,    80,    71,    25,
      72,    81,    63,    64,    65,    66,    67,    68,    69,   258,
      71,    67,    91,   158,   113,   188,    77,   204,   247,   202,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
     205,    23,    24,    25,    26,    27,    28,    29,    30,    31,
     206,    -1,    34,   207,    -1,    -1,    -1,    -1,    -1,    -1,
      42,    -1,    -1,    45,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    55,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    63,    64,    65,    66,    67,    68,    69,    -1,    71,
      -1,    -1,    -1,    -1,    -1,    77,    -1,    -1,    -1,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      -1,    -1,    -1,    16,    17,    18,    19,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    34,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    42,
      -1,    -1,    45,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    55,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      63,    64,    65,    66,    -1,    68,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    77,    -1,    -1,    -1,    -1,    -1,
      83,    84,    85,    86,    87,    88,    89,    90,    91,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      34,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    34,
      -1,    -1,    34,    67,    -1,    -1,    -1,    42,    -1,    -1,
      45,    -1,    -1,    77,    78,    79,    -1,    -1,    -1,    -1,
      55,    -1,    -1,    -1,    -1,    -1,    90,    91,    63,    64,
      65,    66,    -1,    68,    -1,    67,    71,    -1,    -1,    -1,
      -1,    -1,    77,    -1,    -1,    77,    78,    79,    83,    84,
      85,    86,    87,    88,    89,    90,    -1,    -1,    -1,    91,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    34,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    67,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    77,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    90,    91,    -1,
      -1,    62,    -1,    -1,    -1,    -1,    67,    -1,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    -1,    -1,
      81,    16,    17,    18,    19,    -1,    -1,    -1,    -1,    -1,
      91,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    -1,    -1,    82,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    67,    91,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    78,    -1,    -1,    -1,
      -1,    -1,    -1,    67,    -1,    -1,    -1,    -1,    90,    91,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    81,    -1,    -1,
      -1,    67,    -1,    -1,    70,    -1,    -1,    91,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    -1,    -1,
      -1,    16,    17,    18,    19,    91,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    21,    -1,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    -1,    -1,    34,    82,    -1,    -1,
      67,    -1,    -1,    -1,    42,    -1,    91,    45,    -1,    -1,
      -1,    78,    -1,    -1,    -1,    -1,    -1,    55,    67,    -1,
      -1,    -1,    -1,    -1,    91,    63,    64,    65,    66,    -1,
      68,    69,    -1,    71,    -1,    -1,    -1,    -1,    -1,    77,
      -1,    -1,    91,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    21,    -1,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    -1,    -1,    34,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    42,    -1,    -1,    45,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    55,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    63,    64,    65,    66,    -1,
      68,    69,    -1,    71,    -1,    -1,    -1,    -1,    -1,    77,
      -1,    -1,    -1,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    21,    -1,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    -1,    -1,    34,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    42,    -1,    -1,    45,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    55,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    63,    64,    65,    66,    -1,
      68,    69,    -1,    71,    -1,    -1,    -1,    -1,    -1,    77,
      -1,    -1,    -1,    81,    -1,    83,    84,    85,    86,    87,
      88,    89,    90,    34,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    42,    -1,    -1,    45,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    55,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    63,    64,    65,    66,    -1,    68,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    77,    -1,    -1,    -1,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      34,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    42,    -1,
      -1,    45,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    55,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    63,
      64,    65,    66,    -1,    68,    -1,    34,    -1,    -1,    -1,
      -1,    -1,    -1,    77,    42,    -1,    80,    45,    -1,    83,
      84,    85,    86,    87,    88,    89,    90,    55,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    63,    64,    65,    66,    -1,
      68,    -1,    -1,    34,    -1,    -1,    -1,    -1,    -1,    77,
      -1,    42,    -1,    81,    45,    83,    84,    85,    86,    87,
      88,    89,    90,    -1,    55,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    63,    64,    65,    66,    -1,    68,    -1,    34,
      71,    -1,    -1,    -1,    -1,    -1,    77,    42,    -1,    -1,
      45,    -1,    83,    84,    85,    86,    87,    88,    89,    90,
      55,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    63,    64,
      65,    66,    -1,    68,    -1,    -1,    34,    -1,    -1,    -1,
      -1,    -1,    77,    78,    42,    -1,    -1,    45,    83,    84,
      85,    86,    87,    88,    89,    90,    -1,    55,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    63,    64,    65,    66,    -1,
      68,    -1,    34,    -1,    -1,    -1,    -1,    -1,    -1,    77,
      42,    -1,    80,    45,    -1,    83,    84,    85,    86,    87,
      88,    89,    90,    55,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    63,    64,    65,    66,    -1,    68,    -1,    34,    71,
      -1,    -1,    -1,    -1,    -1,    77,    42,    -1,    -1,    45,
      -1,    83,    84,    85,    86,    87,    88,    89,    90,    55,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    63,    64,    65,
      66,    -1,    68,    -1,    34,    -1,    -1,    -1,    -1,    -1,
      -1,    77,    42,    -1,    80,    45,    -1,    83,    84,    85,
      86,    87,    88,    89,    90,    55,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    63,    64,    65,    66,    -1,    68,    -1,
      -1,    34,    -1,    -1,    -1,    -1,    -1,    77,    78,    42,
      -1,    -1,    45,    83,    84,    85,    86,    87,    88,    89,
      90,    -1,    55,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      63,    64,    65,    66,    -1,    68,    -1,    34,    71,    -1,
      -1,    -1,    -1,    -1,    77,    42,    -1,    -1,    45,    -1,
      83,    84,    85,    86,    87,    88,    89,    90,    55,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    63,    64,    65,    66,
      -1,    68,    -1,    -1,    34,    -1,    -1,    -1,    -1,    -1,
      77,    78,    42,    -1,    -1,    45,    83,    84,    85,    86,
      87,    88,    89,    90,    -1,    55,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    63,    64,    65,    66,    -1,    68,    -1,
      -1,    34,    -1,    -1,    -1,    -1,    -1,    77,    78,    42,
      -1,    -1,    45,    83,    84,    85,    86,    87,    88,    89,
      90,    -1,    55,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      63,    64,    65,    66,    -1,    68,    -1,    -1,    34,    -1,
      -1,    -1,    -1,    -1,    77,    78,    42,    -1,    -1,    45,
      83,    84,    85,    86,    87,    88,    89,    90,    -1,    55,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    63,    64,    65,
      66,    -1,    68,    -1,    34,    -1,    -1,    -1,    -1,    -1,
      -1,    77,    42,    -1,    -1,    45,    -1,    83,    84,    85,
      86,    87,    88,    89,    90,    55,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    63,    64,    65,    66,    -1,    68,    -1,
      34,    -1,    -1,    -1,    -1,    -1,    -1,    77,    42,    -1,
      -1,    45,    -1,    83,    84,    85,    86,    87,    88,    89,
      90,    55,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    63,
      64,    65,    66,    -1,    68,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    77,    -1,    -1,    -1,    -1,    -1,    83,
      84,    85,    86,    87,    88,    89,    90
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    34,
      67,    77,    90,    91,    93,    94,    95,    96,    97,    99,
     102,   103,   104,   105,   106,   112,   115,   116,   117,    81,
      90,   104,   117,   118,   115,     0,    95,    71,   100,   101,
     115,    99,    99,    99,    81,    90,    81,    97,    98,    99,
     131,    77,    79,   116,    90,   113,   114,    81,   104,   117,
      78,    71,    72,    62,    98,   131,   103,   104,   107,   108,
     109,    81,    21,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    34,    42,    45,    55,    63,    64,    65,    66,
      68,    69,    71,    77,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    98,   128,   129,   130,   131,   132,   133,
     134,   135,   136,   137,   139,   141,   142,   143,   144,   145,
     146,   147,   148,   149,   150,   151,   152,   153,   154,   155,
     157,   158,    97,   131,   115,    78,    90,    99,   119,   120,
     121,   122,    80,    90,   139,   140,   152,    62,    72,    82,
     113,   101,    81,   123,   137,   131,   109,   109,    82,   108,
      73,   110,   111,   115,   107,    77,    77,   128,    77,    71,
      71,    77,   140,    73,    90,    77,   152,   152,    77,   152,
      71,   136,   109,   125,   136,    73,    82,   132,    82,   128,
      71,    72,    54,    74,    53,    43,    44,    42,    60,    61,
      56,    57,    58,    59,    46,    47,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    48,    49,    50,    51,
      52,    62,   138,   151,    63,    64,    75,    76,    77,    79,
      77,    79,   115,   117,   126,   127,    78,    72,    72,    78,
      80,   140,   114,    82,   123,   124,   140,    71,    72,    73,
      82,   136,    71,   136,    25,   136,   136,    73,    71,   125,
      71,    77,   117,   126,    78,    78,   128,    82,   137,   142,
     136,   143,   144,   145,   146,   147,   147,   148,   148,   148,
     148,   149,   149,   150,   150,   151,   151,   151,   137,    90,
      90,    78,   137,   156,   136,    78,   119,   126,    80,   140,
     127,    77,    79,    70,   121,    90,    72,    82,   111,   140,
      78,    71,   136,    71,    77,    78,    78,    78,   151,    73,
      72,    78,    80,    78,    78,    80,    78,   119,    80,   140,
      82,   123,   128,    78,   136,    71,    71,   136,   136,   128,
     128,   139,   137,    78,    80,    22,   128,    78,    78,   136,
      78,   136,    71,    78,   128,   128,   128,    78,   128,    78,
      78,   136,    71,   128,   128,   128,    78,   128
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    92,    93,    94,    94,    95,    95,    96,    96,    96,
      96,    97,    97,    98,    98,    99,    99,    99,    99,    99,
      99,   100,   100,   101,   101,   102,   102,   102,   102,   102,
     103,   103,   103,   103,   103,   103,   103,   103,   103,   103,
     103,   103,   104,   104,   105,   105,   105,   106,   106,   107,
     107,   108,   109,   109,   109,   109,   110,   110,   111,   111,
     111,   112,   112,   112,   113,   113,   114,   114,   115,   115,
     116,   116,   116,   116,   116,   116,   116,   117,   117,   117,
     117,   118,   118,   119,   119,   120,   120,   121,   121,   121,
     122,   122,   123,   123,   123,   124,   124,   125,   125,   126,
     126,   126,   127,   127,   127,   127,   127,   127,   127,   127,
     127,   128,   128,   128,   128,   128,   128,   129,   129,   129,
     130,   130,   131,   131,   131,   131,   132,   132,   133,   133,
     133,   134,   134,   134,   134,   134,   134,   134,   134,   134,
     134,   135,   135,   135,   135,   135,   136,   136,   137,   137,
     138,   138,   138,   138,   138,   138,   138,   138,   138,   138,
     138,   139,   139,   140,   141,   141,   142,   142,   143,   143,
     144,   144,   145,   145,   146,   146,   146,   147,   147,   147,
     147,   147,   148,   148,   148,   149,   149,   149,   150,   150,
     150,   150,   151,   151,   152,   152,   152,   152,   152,   152,
     153,   153,   153,   153,   153,   153,   154,   154,   154,   154,
     154,   154,   154,   154,   155,   155,   155,   155,   156,   156,
     157,   158,   158,   158,   158,   158,   158
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     2,     1,     1,     4,     3,     3,
       2,     3,     2,     1,     2,     1,     2,     1,     2,     1,
       2,     1,     3,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     5,     4,     2,     1,     1,     1,
       2,     3,     2,     1,     2,     1,     1,     3,     1,     3,
       2,     5,     4,     2,     1,     3,     1,     3,     2,     1,
       1,     3,     4,     3,     4,     4,     3,     2,     1,     3,
       2,     1,     2,     1,     3,     1,     3,     2,     2,     1,
       1,     3,     1,     3,     4,     1,     3,     2,     1,     1,
       2,     1,     3,     4,     3,     3,     2,     4,     3,     3,
       2,     1,     1,     1,     1,     1,     1,     3,     3,     2,
       2,     1,     4,     3,     3,     2,     1,     2,     5,     7,
       5,     5,     7,     9,     8,     8,     8,     7,     7,     7,
       6,     3,     2,     2,     3,     2,     1,     3,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     5,     1,     1,     3,     1,     3,     1,     3,
       1,     3,     1,     3,     1,     3,     3,     1,     3,     3,
       3,     3,     1,     3,     3,     1,     3,     3,     1,     3,
       3,     3,     1,     4,     1,     2,     2,     2,     2,     4,
       1,     1,     1,     1,     1,     1,     1,     4,     4,     3,
       3,     3,     2,     2,     1,     1,     1,     3,     1,     3,
       1,     1,     1,     1,     1,     1,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


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


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, int yyrule)
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
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
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
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
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
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
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
            else
              goto append;

          append:
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

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
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
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

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
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
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
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
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
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
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
          ++yyp;
          ++yyformat;
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
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYPTRDIFF_T yystacksize;

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
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
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

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
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
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
# undef YYSTACK_RELOCATE
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
  case 2:
#line 135 "ecc.y"
                                               { (yyval.program) = new Program((yyvsp[0].declaration)); program = (yyval.program); }
#line 2045 "parser.cpp"
    break;

  case 3:
#line 138 "ecc.y"
                                                                    { (yyval.declaration) = (yyvsp[0].declaration); (yyval.declaration)->tail = (yyval.declaration); }
#line 2051 "parser.cpp"
    break;

  case 4:
#line 139 "ecc.y"
                                                                { (yyval.declaration) = (yyvsp[-1].declaration); (yyval.declaration)->tail->next = (yyvsp[0].declaration); (yyval.declaration)->tail = (yyvsp[0].declaration); }
#line 2057 "parser.cpp"
    break;

  case 5:
#line 142 "ecc.y"
                                                    { (yyval.declaration) = (yyvsp[0].functionDeclaration); }
#line 2063 "parser.cpp"
    break;

  case 6:
#line 143 "ecc.y"
                                                    { (yyval.declaration) = (yyvsp[0].declaration); }
#line 2069 "parser.cpp"
    break;

  case 8:
#line 147 "ecc.y"
                                                                             {
                                (yyval.functionDeclaration) = (FunctionDeclaration *)(yyvsp[-1].node);
                                (yyval.functionDeclaration)->rettype = (yyvsp[-2].type);
                                (yyval.functionDeclaration)->stmts = (yyvsp[0].compoundStatement);
                            }
#line 2079 "parser.cpp"
    break;

  case 10:
#line 153 "ecc.y"
                                                                            {
                                (yyval.functionDeclaration) = (FunctionDeclaration *)(yyvsp[-1].node);
                                (yyval.functionDeclaration)->rettype = new IntType(); // default return type is int
                                (yyval.functionDeclaration)->stmts = (yyvsp[0].compoundStatement);
                            }
#line 2089 "parser.cpp"
    break;

  case 11:
#line 160 "ecc.y"
                                                                    {
                                vector<TypeSpecifier *> *ts = new vector<TypeSpecifier *>;

                                for(auto &p : *(yyvsp[-1].ids))
                                {
                                    Expression *size = p->right;

                                    // no array size defined and pointer qualifier
                                    if(!size && (p->qual && !p->qual->pcnt))
                                        ts->push_back((yyvsp[-2].type));
                                    else
                                    {
                                        // basic type
                                        TypeSpecifier *t = (yyvsp[-2].type);
                                        // pointer qualifier
                                        if(p->qual)
                                            for(int i = 0; i < p->qual->pcnt; i++)
                                                t = new MyPointerType(t);
                                        // if array size defined
                                        while(size)
                                        {
                                            if(((Number *)size)->valtype != VAL_NONE)
                                                t = new MyArrayType(t, ((Number *)size)->longView());
                                            else
                                                t = new MyPointerType(t);
                                            Expression *tmp = size;
                                            size = size->right;
                                            // delete tmp
                                        }
                                        ts->push_back(t);
                                    }

                                    // constant variable
                                    if((yyvsp[-2].type)->qual && (yyvsp[-2].type)->qual->isconst)
                                    {
                                        if(p->init->getName() != "\"Number\"")
                                            yyerror("not constant initializer for const variable");
                                        constvar[p->name] = (Number *)(p->init);
                                    }
                                }

                                (yyval.declaration) = new VariableDeclaration(ts, (yyvsp[-1].ids));
                            }
#line 2137 "parser.cpp"
    break;

  case 12:
#line 203 "ecc.y"
                                               { (yyval.declaration) = new TypeDeclaration((yyvsp[-1].type)); }
#line 2143 "parser.cpp"
    break;

  case 13:
#line 206 "ecc.y"
                                   { (yyval.vars) = new vector<VariableDeclaration *>; (yyval.vars)->push_back((VariableDeclaration *)(yyvsp[0].declaration)); }
#line 2149 "parser.cpp"
    break;

  case 14:
#line 207 "ecc.y"
                                             { (yyvsp[-1].vars)->push_back((VariableDeclaration *)(yyvsp[0].declaration)); (yyval.vars) = (yyvsp[-1].vars); }
#line 2155 "parser.cpp"
    break;

  case 17:
#line 212 "ecc.y"
                                        { (yyval.type) = (yyvsp[0].type); }
#line 2161 "parser.cpp"
    break;

  case 19:
#line 214 "ecc.y"
                                             { (yyval.type) = new IntType((yyvsp[0].qual)); }
#line 2167 "parser.cpp"
    break;

  case 20:
#line 215 "ecc.y"
                                                        { (yyval.type) = (yyvsp[0].type) ; (yyval.type)->qual = (yyvsp[-1].qual); }
#line 2173 "parser.cpp"
    break;

  case 21:
#line 218 "ecc.y"
                                              { (yyval.ids) = new vector<Identifier *>; (yyval.ids)->push_back((yyvsp[0].identifier)); }
#line 2179 "parser.cpp"
    break;

  case 22:
#line 219 "ecc.y"
                                                                         { (yyvsp[-2].ids)->push_back((yyvsp[0].identifier)); (yyval.ids) = (yyvsp[-2].ids); }
#line 2185 "parser.cpp"
    break;

  case 23:
#line 222 "ecc.y"
                                         { (yyval.identifier) = (Identifier *)(yyvsp[0].node); }
#line 2191 "parser.cpp"
    break;

  case 24:
#line 223 "ecc.y"
                                                            { (yyval.identifier) = (Identifier *)(yyvsp[-2].node); (yyval.identifier)->init = (yyvsp[0].expression); }
#line 2197 "parser.cpp"
    break;

  case 30:
#line 233 "ecc.y"
                                        { (yyval.type) = new CharType();      }
#line 2203 "parser.cpp"
    break;

  case 31:
#line 234 "ecc.y"
                                        { (yyval.type) = new ShortType();     }
#line 2209 "parser.cpp"
    break;

  case 32:
#line 235 "ecc.y"
                                        { (yyval.type) = new IntType();       }
#line 2215 "parser.cpp"
    break;

  case 33:
#line 236 "ecc.y"
                                        { (yyval.type) = new LongType();      }
#line 2221 "parser.cpp"
    break;

  case 34:
#line 237 "ecc.y"
                                        { (yyval.type) = new FloatType();     }
#line 2227 "parser.cpp"
    break;

  case 35:
#line 238 "ecc.y"
                                        { (yyval.type) = new DoubleType();    }
#line 2233 "parser.cpp"
    break;

  case 36:
#line 239 "ecc.y"
                                        { (yyval.type) = new VoidType();      }
#line 2239 "parser.cpp"
    break;

  case 39:
#line 242 "ecc.y"
                                                   { (yyval.type) = (yyvsp[0].aggrtype); }
#line 2245 "parser.cpp"
    break;

  case 42:
#line 247 "ecc.y"
                                        { (yyval.qual) = new Qualifier(); (yyval.qual)->isconst    = true; }
#line 2251 "parser.cpp"
    break;

  case 43:
#line 248 "ecc.y"
                                        { (yyval.qual) = new Qualifier(); (yyval.qual)->isvolatile = true; }
#line 2257 "parser.cpp"
    break;

  case 44:
#line 251 "ecc.y"
                                                                                {
                                if(aggrdef.find(*(yyvsp[-3].stringValue)) != aggrdef.end())
                                    // if the struct has been defined, fetch it directly
                                    (yyval.aggrtype) = aggrdef[*(yyvsp[-3].stringValue)];
                                else
                                {
                                    (yyval.aggrtype) = (yyvsp[-4].aggrtype);
                                    (yyval.aggrtype)->name = *(yyvsp[-3].stringValue);
                                    // add struct definition into map
                                    aggrdef[*(yyvsp[-3].stringValue)] = (yyval.aggrtype);
                                }
                                delete (yyvsp[-3].stringValue);
                                (yyval.aggrtype)->members = (yyvsp[-1].members);
                            }
#line 2276 "parser.cpp"
    break;

  case 45:
#line 265 "ecc.y"
                                                                     { (yyval.aggrtype) = (yyvsp[-3].aggrtype); (yyval.aggrtype)->members = (yyvsp[-1].members); }
#line 2282 "parser.cpp"
    break;

  case 46:
#line 266 "ecc.y"
                                                         { (yyval.aggrtype) = (yyvsp[-1].aggrtype); (yyval.aggrtype)->name = *(yyvsp[0].stringValue); delete (yyvsp[0].stringValue); }
#line 2288 "parser.cpp"
    break;

  case 47:
#line 269 "ecc.y"
                                        { (yyval.aggrtype) = new MyStructType(); }
#line 2294 "parser.cpp"
    break;

  case 48:
#line 270 "ecc.y"
                                        { (yyval.aggrtype) = new UnionType(); }
#line 2300 "parser.cpp"
    break;

  case 49:
#line 273 "ecc.y"
                                          { (yyval.members) = new vector<pair<vector<TypeSpecifier *> *, vector<Identifier *> *> *>(); (yyval.members)->push_back((yyvsp[0].member)); }
#line 2306 "parser.cpp"
    break;

  case 50:
#line 274 "ecc.y"
                                                           { (yyval.members) = (yyvsp[-1].members); (yyval.members)->push_back((yyvsp[0].member)); }
#line 2312 "parser.cpp"
    break;

  case 51:
#line 277 "ecc.y"
                                                                               {
                                vector<TypeSpecifier *> *ts = new vector<TypeSpecifier *>;

                                for(auto &p : *(yyvsp[-1].ids))
                                {
                                    Expression *size = p->right;

                                    // no array size defined and pointer qualifier
                                    if(!size && (p->qual && !p->qual->pcnt))
                                        ts->push_back((yyvsp[-2].type));
                                    else
                                    {
                                        // basic type
                                        TypeSpecifier *t = (yyvsp[-2].type);
                                        // pointer qualifier
                                        if(p->qual)
                                            for(int i = 0; i < p->qual->pcnt; i++)
                                                t = new MyPointerType(t);
                                        // if array size defined
                                        while(size)
                                        {
                                            if(((Number *)size)->valtype != VAL_NONE)
                                                t = new MyArrayType(t, ((Number *)size)->longView());
                                            else
                                                t = new MyPointerType(t);
                                            Expression *tmp = size;
                                            size = size->right;
                                            // delete tmp
                                        }
                                        ts->push_back(t);
                                    }
                                }

                                (yyval.member) = new pair<vector<TypeSpecifier *> *, vector<Identifier *> *>(ts, (yyvsp[-1].ids));
                            }
#line 2352 "parser.cpp"
    break;

  case 52:
#line 314 "ecc.y"
                                                            { (yyval.type) = (yyvsp[-1].type); (yyval.type)->qual = (yyval.type)->qual; delete (yyvsp[0].type); }
#line 2358 "parser.cpp"
    break;

  case 53:
#line 315 "ecc.y"
                                        { (yyval.type) = (yyvsp[0].type); }
#line 2364 "parser.cpp"
    break;

  case 56:
#line 320 "ecc.y"
                                                { (yyval.ids) = new vector<Identifier *>(); (yyval.ids)->push_back((yyvsp[0].identifier)); }
#line 2370 "parser.cpp"
    break;

  case 57:
#line 321 "ecc.y"
                                                                             { (yyval.ids) = (yyvsp[-2].ids); (yyval.ids)->push_back((yyvsp[0].identifier)); }
#line 2376 "parser.cpp"
    break;

  case 58:
#line 324 "ecc.y"
                                         {
                                if((yyvsp[0].node)->getName() != "\"Identifier\"")
                                    yyerror("not supported struct-declarator yet");
                                (yyval.identifier) = (Identifier *)(yyvsp[0].node);
                            }
#line 2386 "parser.cpp"
    break;

  case 68:
#line 346 "ecc.y"
                                                        { (yyval.node) = (yyvsp[0].node); ((Identifier *)(yyval.node))->qual = (yyvsp[-1].qual); }
#line 2392 "parser.cpp"
    break;

  case 69:
#line 347 "ecc.y"
                                                { (yyval.node) = (yyvsp[0].node); }
#line 2398 "parser.cpp"
    break;

  case 70:
#line 350 "ecc.y"
                                         { (yyval.node) = new Identifier(*(yyvsp[0].stringValue)); delete (yyvsp[0].stringValue); }
#line 2404 "parser.cpp"
    break;

  case 72:
#line 352 "ecc.y"
                                                                      {
                                (yyval.node) = (yyvsp[-3].node);
                                ((Expression *)(yyvsp[-1].number))->right = ((Identifier *)(yyval.node))->right;
                                ((Identifier *)(yyval.node))->right = (yyvsp[-1].number);
                            }
#line 2414 "parser.cpp"
    break;

  case 73:
#line 357 "ecc.y"
                                                                      { (yyval.node) = (yyvsp[-2].node); ((Identifier *)(yyval.node))->right = new Number(); }
#line 2420 "parser.cpp"
    break;

  case 75:
#line 359 "ecc.y"
                                                                      { (yyval.node) = new FunctionDeclaration(nullptr, (Identifier *)(yyvsp[-3].node), (yyvsp[-1].param), nullptr); }
#line 2426 "parser.cpp"
    break;

  case 76:
#line 360 "ecc.y"
                                                                      { (yyval.node) = new FunctionDeclaration(nullptr, (Identifier *)(yyvsp[-2].node), nullptr, nullptr); }
#line 2432 "parser.cpp"
    break;

  case 77:
#line 363 "ecc.y"
                                                                           { (yyval.qual) = (yyvsp[0].qual); (yyval.qual)->pcnt++; }
#line 2438 "parser.cpp"
    break;

  case 78:
#line 364 "ecc.y"
                                               { (yyval.qual) = new Qualifier(1); }
#line 2444 "parser.cpp"
    break;

  case 79:
#line 365 "ecc.y"
                                                                           {
                                (yyval.qual) = (yyvsp[-1].qual);
                                (yyval.qual)->pcnt += (yyvsp[0].qual)->pcnt + 1;
                                delete (yyvsp[0].qual);
                            }
#line 2454 "parser.cpp"
    break;

  case 80:
#line 370 "ecc.y"
                                                       { (yyval.qual) = (yyvsp[0].qual); (yyval.qual)->pcnt++; }
#line 2460 "parser.cpp"
    break;

  case 81:
#line 373 "ecc.y"
                                                 { (yyval.qual) = (yyvsp[0].qual); }
#line 2466 "parser.cpp"
    break;

  case 82:
#line 374 "ecc.y"
                                                                 {
                                (yyval.qual) = (yyvsp[-1].qual);
                                (yyval.qual)->isconst = (yyvsp[0].qual)->isconst;
                                (yyval.qual)->isvolatile = (yyvsp[0].qual)->isvolatile;
                                (yyval.qual)->pcnt += (yyvsp[0].qual)->pcnt;
                                delete (yyvsp[0].qual);
                            }
#line 2478 "parser.cpp"
    break;

  case 83:
#line 383 "ecc.y"
                                         { (yyval.param) = (yyvsp[0].param); }
#line 2484 "parser.cpp"
    break;

  case 84:
#line 384 "ecc.y"
                                                         { (yyval.param) = (yyvsp[-2].param); (yyval.param)->isvariableargs = true; }
#line 2490 "parser.cpp"
    break;

  case 85:
#line 387 "ecc.y"
                                         { (yyval.param) = (yyvsp[0].param); (yyval.param)->tail = (yyval.param); }
#line 2496 "parser.cpp"
    break;

  case 86:
#line 388 "ecc.y"
                                                          { (yyval.param) = (yyvsp[-2].param); (yyval.param)->tail->next = (yyvsp[0].param); (yyval.param)->tail = (yyvsp[0].param); }
#line 2502 "parser.cpp"
    break;

  case 87:
#line 391 "ecc.y"
                                                    {
                                Identifier *id = ((Identifier *)(yyvsp[0].node));
                                Expression *size = id->right;
                                if(!size && (id->qual && !id->qual->pcnt))
                                    (yyval.param) = new Parameter((yyvsp[-1].type), id);
                                else
                                {
                                    TypeSpecifier *t = (yyvsp[-1].type);
                                    if(id->qual)
                                        for(int i = 0; i < id->qual->pcnt; i++)
                                            t = new MyPointerType(t);
                                    while(size)
                                    {
                                        if(((Number *)size)->valtype != VAL_NONE)
                                            t = new MyArrayType(t, ((Number *)size)->longView());
                                        else
                                            t = new MyPointerType(t);
                                        Expression *tmp = size;
                                        size = size->right;
                                    }
                                    id->right = nullptr;
                                    (yyval.param) = new Parameter(t, id);
                                }
                            }
#line 2531 "parser.cpp"
    break;

  case 89:
#line 416 "ecc.y"
                                         { (yyval.param) = new Parameter((yyvsp[0].type)); }
#line 2537 "parser.cpp"
    break;

  case 90:
#line 419 "ecc.y"
                                                 { (yyval.ids) = new vector<Identifier *>; (yyval.ids)->push_back(new Identifier(*(yyvsp[0].stringValue))); delete (yyvsp[0].stringValue); }
#line 2543 "parser.cpp"
    break;

  case 91:
#line 420 "ecc.y"
                                                       { (yyvsp[-2].ids)->push_back(new Identifier(*(yyvsp[0].stringValue))); (yyval.ids) = (yyvsp[-2].ids); delete (yyvsp[0].stringValue);  }
#line 2549 "parser.cpp"
    break;

  case 92:
#line 423 "ecc.y"
                                                           { (yyval.expression) = (yyvsp[0].expression); }
#line 2555 "parser.cpp"
    break;

  case 93:
#line 424 "ecc.y"
                                                           { (yyval.expression) = (yyvsp[-1].expression); }
#line 2561 "parser.cpp"
    break;

  case 94:
#line 425 "ecc.y"
                                                           { (yyval.expression) = (yyvsp[-2].expression); }
#line 2567 "parser.cpp"
    break;

  case 95:
#line 428 "ecc.y"
                                          { (yyval.expression) = (yyvsp[0].expression); }
#line 2573 "parser.cpp"
    break;

  case 96:
#line 429 "ecc.y"
                                                                 { 
                                Expression *p = (yyvsp[-2].expression);
                                while(p->left)
                                    p = p->left;
                                p->left = (yyvsp[0].expression);
                                (yyval.expression) = (yyvsp[-2].expression);
                            }
#line 2585 "parser.cpp"
    break;

  case 97:
#line 438 "ecc.y"
                                                                      {
                                (yyval.type) = (yyvsp[-1].type);
                                if((yyvsp[0].node)->getName() == "\"Qualifier\"")
                                    for(int i = 0; i < ((Qualifier *)(yyvsp[0].node))->pcnt; i++)
                                        (yyval.type) = new MyPointerType((yyval.type));
                                else
                                    yyerror(string("abstract-declarator of type '") + (yyvsp[0].node)->getName() + "' is not supported yet");
                            }
#line 2598 "parser.cpp"
    break;

  case 98:
#line 446 "ecc.y"
                                                  { (yyval.type) = (yyvsp[0].type); }
#line 2604 "parser.cpp"
    break;

  case 99:
#line 449 "ecc.y"
                                      { (yyval.node) = (yyvsp[0].qual); }
#line 2610 "parser.cpp"
    break;

  case 111:
#line 465 "ecc.y"
                                             { (yyval.statement) = (yyvsp[0].statement); }
#line 2616 "parser.cpp"
    break;

  case 112:
#line 466 "ecc.y"
                                             { (yyval.statement) = (yyvsp[0].expressionStatement); }
#line 2622 "parser.cpp"
    break;

  case 113:
#line 467 "ecc.y"
                                             { (yyval.statement) = (yyvsp[0].compoundStatement); }
#line 2628 "parser.cpp"
    break;

  case 114:
#line 468 "ecc.y"
                                             { (yyval.statement) = (yyvsp[0].selectionStatement); }
#line 2634 "parser.cpp"
    break;

  case 115:
#line 469 "ecc.y"
                                             { (yyval.statement) = (yyvsp[0].iterationStatement); }
#line 2640 "parser.cpp"
    break;

  case 116:
#line 470 "ecc.y"
                                             { (yyval.statement) = (yyvsp[0].statement); }
#line 2646 "parser.cpp"
    break;

  case 117:
#line 473 "ecc.y"
                                                        { (yyval.statement) = new LabelStatement(*(yyvsp[-2].stringValue)); delete (yyvsp[-2].stringValue); }
#line 2652 "parser.cpp"
    break;

  case 118:
#line 476 "ecc.y"
                                                   { (yyval.statement) = new CaseStatement((yyvsp[-1].number)); }
#line 2658 "parser.cpp"
    break;

  case 119:
#line 477 "ecc.y"
                                            { (yyval.statement) = new CaseStatement(nullptr); }
#line 2664 "parser.cpp"
    break;

  case 120:
#line 480 "ecc.y"
                                            { (yyval.expressionStatement) = new ExpressionStatement((yyvsp[-1].expression)); }
#line 2670 "parser.cpp"
    break;

  case 121:
#line 481 "ecc.y"
                                        { (yyval.expressionStatement) = new ExpressionStatement(); }
#line 2676 "parser.cpp"
    break;

  case 122:
#line 484 "ecc.y"
                                                        { (yyval.compoundStatement) = new CompoundStatement((yyvsp[-2].vars), (yyvsp[-1].statement)); }
#line 2682 "parser.cpp"
    break;

  case 123:
#line 485 "ecc.y"
                                                        { (yyval.compoundStatement) = new CompoundStatement(nullptr, (yyvsp[-1].statement)); }
#line 2688 "parser.cpp"
    break;

  case 124:
#line 486 "ecc.y"
                                                        { (yyval.compoundStatement) = new CompoundStatement((yyvsp[-1].vars), nullptr); }
#line 2694 "parser.cpp"
    break;

  case 125:
#line 487 "ecc.y"
                                                        { (yyval.compoundStatement) = new CompoundStatement(nullptr, nullptr); }
#line 2700 "parser.cpp"
    break;

  case 126:
#line 490 "ecc.y"
                                   { (yyval.statement) = (yyvsp[0].statement); (yyval.statement)->tail = (yyval.statement); }
#line 2706 "parser.cpp"
    break;

  case 127:
#line 491 "ecc.y"
                                             { (yyval.statement) = (yyvsp[-1].statement); (yyval.statement)->tail->next = (yyvsp[0].statement); (yyval.statement)->tail = (yyvsp[0].statement); }
#line 2712 "parser.cpp"
    break;

  case 128:
#line 494 "ecc.y"
                                                                { (yyvsp[0].statement)->next = nullptr; (yyval.selectionStatement) = new IfElseStatement((yyvsp[-2].expression), (yyvsp[0].statement)); }
#line 2718 "parser.cpp"
    break;

  case 129:
#line 495 "ecc.y"
                                                            { (yyvsp[-2].statement)->next = (yyvsp[0].statement); (yyval.selectionStatement) = new IfElseStatement((yyvsp[-4].expression), (yyvsp[-2].statement)); }
#line 2724 "parser.cpp"
    break;

  case 130:
#line 496 "ecc.y"
                                                            {
                                if((yyvsp[0].statement)->getName() != "\"CompoundStatement\"")
                                    yyerror("case label not within a switch statement");
                                (yyval.selectionStatement) = new SwitchCaseStatement((yyvsp[-2].expression), (yyvsp[0].statement));
                            }
#line 2734 "parser.cpp"
    break;

  case 131:
#line 503 "ecc.y"
                                                                         { (yyval.iterationStatement) = new WhileStatement((yyvsp[-2].expression), (yyvsp[0].statement)); }
#line 2740 "parser.cpp"
    break;

  case 132:
#line 504 "ecc.y"
                                                                     { (yyval.iterationStatement) = new DoWhileStatement((yyvsp[-2].expression), (yyvsp[-5].statement)); }
#line 2746 "parser.cpp"
    break;

  case 133:
#line 505 "ecc.y"
                                                                     { (yyval.iterationStatement) = new ForStatement((yyvsp[-6].expression), (yyvsp[-4].expression), (yyvsp[-2].expression), (yyvsp[0].statement)); }
#line 2752 "parser.cpp"
    break;

  case 134:
#line 506 "ecc.y"
                                                                     { (yyval.iterationStatement) = new ForStatement((yyvsp[-5].expression), (yyvsp[-3].expression), nullptr, (yyvsp[0].statement)); }
#line 2758 "parser.cpp"
    break;

  case 135:
#line 507 "ecc.y"
                                                                     { (yyval.iterationStatement) = new ForStatement((yyvsp[-5].expression), nullptr, (yyvsp[-2].expression), (yyvsp[0].statement)); }
#line 2764 "parser.cpp"
    break;

  case 136:
#line 508 "ecc.y"
                                                                     { (yyval.iterationStatement) = new ForStatement(nullptr, (yyvsp[-4].expression), (yyvsp[-2].expression), (yyvsp[0].statement)); }
#line 2770 "parser.cpp"
    break;

  case 137:
#line 509 "ecc.y"
                                                                     { (yyval.iterationStatement) = new ForStatement((yyvsp[-4].expression), nullptr, nullptr, (yyvsp[0].statement)); }
#line 2776 "parser.cpp"
    break;

  case 138:
#line 510 "ecc.y"
                                                                     { (yyval.iterationStatement) = new ForStatement(nullptr, (yyvsp[-3].expression), nullptr, (yyvsp[0].statement)); }
#line 2782 "parser.cpp"
    break;

  case 139:
#line 511 "ecc.y"
                                                                     { (yyval.iterationStatement) = new ForStatement(nullptr, nullptr, (yyvsp[-2].expression), (yyvsp[0].statement)); }
#line 2788 "parser.cpp"
    break;

  case 140:
#line 512 "ecc.y"
                                                                     { (yyval.iterationStatement) = new ForStatement(nullptr, nullptr, nullptr, (yyvsp[0].statement)); }
#line 2794 "parser.cpp"
    break;

  case 141:
#line 515 "ecc.y"
                                                    { (yyval.statement) = new GotoStatement(*(yyvsp[-1].stringValue)); delete (yyvsp[-1].stringValue); }
#line 2800 "parser.cpp"
    break;

  case 142:
#line 516 "ecc.y"
                                                    { (yyval.statement) = new ContinueStatement(); }
#line 2806 "parser.cpp"
    break;

  case 143:
#line 517 "ecc.y"
                                                    { (yyval.statement) = new BreakStatement(); }
#line 2812 "parser.cpp"
    break;

  case 144:
#line 518 "ecc.y"
                                                    { (yyval.statement) = new ReturnStatement((yyvsp[-1].expression)); }
#line 2818 "parser.cpp"
    break;

  case 145:
#line 519 "ecc.y"
                                                    { (yyval.statement) = new ReturnStatement(); }
#line 2824 "parser.cpp"
    break;

  case 146:
#line 522 "ecc.y"
                                                         { (yyval.expression) = (yyvsp[0].expression); }
#line 2830 "parser.cpp"
    break;

  case 147:
#line 523 "ecc.y"
                                                       { (yyval.expression) = calculate((yyvsp[-2].expression), (yyvsp[0].expression), OP_COMMA); }
#line 2836 "parser.cpp"
    break;

  case 148:
#line 526 "ecc.y"
                                                  { (yyval.expression) = (yyvsp[0].expression); }
#line 2842 "parser.cpp"
    break;

  case 149:
#line 527 "ecc.y"
                                                                           {
                                if((yyvsp[-2].expression)->getName() == "\"Number\"")
                                    yyerror("lvalue required as left operand of assignment");
                                (yyval.expression) = new Expression((yyvsp[-2].expression), (yyvsp[0].expression), (yyvsp[-1].op));
                            }
#line 2852 "parser.cpp"
    break;

  case 150:
#line 534 "ecc.y"
                                            { (yyval.op) = OP_ASSIGN; }
#line 2858 "parser.cpp"
    break;

  case 151:
#line 535 "ecc.y"
                                        { (yyval.op) = OP_MULASSIGN; }
#line 2864 "parser.cpp"
    break;

  case 152:
#line 536 "ecc.y"
                                        { (yyval.op) = OP_DIVASSIGN; }
#line 2870 "parser.cpp"
    break;

  case 153:
#line 537 "ecc.y"
                                        { (yyval.op) = OP_MODASSIGN; }
#line 2876 "parser.cpp"
    break;

  case 154:
#line 538 "ecc.y"
                                        { (yyval.op) = OP_ADDASSIGN; }
#line 2882 "parser.cpp"
    break;

  case 155:
#line 539 "ecc.y"
                                        { (yyval.op) = OP_SUBASSIGN; }
#line 2888 "parser.cpp"
    break;

  case 156:
#line 540 "ecc.y"
                                        { (yyval.op) = OP_SLASSIGN; }
#line 2894 "parser.cpp"
    break;

  case 157:
#line 541 "ecc.y"
                                        { (yyval.op) = OP_SRASSIGN; }
#line 2900 "parser.cpp"
    break;

  case 158:
#line 542 "ecc.y"
                                        { (yyval.op) = OP_ANDASSIGN; }
#line 2906 "parser.cpp"
    break;

  case 159:
#line 543 "ecc.y"
                                        { (yyval.op) = OP_XORASSIGN; }
#line 2912 "parser.cpp"
    break;

  case 160:
#line 544 "ecc.y"
                                        { (yyval.op) = OP_ORASSIGN; }
#line 2918 "parser.cpp"
    break;

  case 161:
#line 547 "ecc.y"
                                             { (yyval.expression) = (yyvsp[0].expression); }
#line 2924 "parser.cpp"
    break;

  case 162:
#line 548 "ecc.y"
                                                                                { (yyval.expression) = calculate((yyvsp[-2].expression), (yyvsp[0].expression), (yyvsp[-4].expression), OP_IFELSE); }
#line 2930 "parser.cpp"
    break;

  case 163:
#line 551 "ecc.y"
                                                  {
                                if((yyvsp[0].expression)->getName() == "\"Number\"")
                                    (yyval.number) = (Number *)(yyvsp[0].expression);
                                else if((yyvsp[0].expression)->getName() == "\"Identifier\"" && constvar[((Identifier *)(yyvsp[0].expression))->name])
                                    (yyval.number) = (Number *)constvar[((Identifier *)(yyvsp[0].expression))->name];
                                else
                                    yyerror("const-exp is not a Number constant");
                            }
#line 2943 "parser.cpp"
    break;

  case 164:
#line 561 "ecc.y"
                                                  { (yyval.expression) = (yyvsp[0].expression); }
#line 2949 "parser.cpp"
    break;

  case 165:
#line 562 "ecc.y"
                                                                  { (yyval.expression) = calculate((yyvsp[-2].expression), (yyvsp[0].expression), OP_OROR); }
#line 2955 "parser.cpp"
    break;

  case 166:
#line 565 "ecc.y"
                                                   { (yyval.expression) = (yyvsp[0].expression); }
#line 2961 "parser.cpp"
    break;

  case 167:
#line 566 "ecc.y"
                                                                      { (yyval.expression) = calculate((yyvsp[-2].expression), (yyvsp[0].expression), OP_ANDAND); }
#line 2967 "parser.cpp"
    break;

  case 168:
#line 569 "ecc.y"
                                                   { (yyval.expression) = (yyvsp[0].expression); }
#line 2973 "parser.cpp"
    break;

  case 169:
#line 570 "ecc.y"
                                                                   { (yyval.expression) = calculate((yyvsp[-2].expression), (yyvsp[0].expression), OP_OR); }
#line 2979 "parser.cpp"
    break;

  case 170:
#line 573 "ecc.y"
                                          { (yyval.expression) = (yyvsp[0].expression); }
#line 2985 "parser.cpp"
    break;

  case 171:
#line 574 "ecc.y"
                                                           { (yyval.expression) = calculate((yyvsp[-2].expression), (yyvsp[0].expression), OP_XOR); }
#line 2991 "parser.cpp"
    break;

  case 172:
#line 577 "ecc.y"
                                                   { (yyval.expression) = (yyvsp[0].expression); }
#line 2997 "parser.cpp"
    break;

  case 173:
#line 578 "ecc.y"
                                                                  { (yyval.expression) = calculate((yyvsp[-2].expression), (yyvsp[0].expression), OP_AND); }
#line 3003 "parser.cpp"
    break;

  case 174:
#line 581 "ecc.y"
                                                 { (yyval.expression) = (yyvsp[0].expression);}
#line 3009 "parser.cpp"
    break;

  case 175:
#line 582 "ecc.y"
                                                             { (yyval.expression) = calculate((yyvsp[-2].expression), (yyvsp[0].expression), OP_EQ); }
#line 3015 "parser.cpp"
    break;

  case 176:
#line 583 "ecc.y"
                                                              { (yyval.expression) = calculate((yyvsp[-2].expression), (yyvsp[0].expression), OP_NEQ); }
#line 3021 "parser.cpp"
    break;

  case 177:
#line 586 "ecc.y"
                                                   { (yyval.expression) = (yyvsp[0].expression); }
#line 3027 "parser.cpp"
    break;

  case 178:
#line 587 "ecc.y"
                                                                 { (yyval.expression) = calculate((yyvsp[-2].expression), (yyvsp[0].expression), OP_LT); }
#line 3033 "parser.cpp"
    break;

  case 179:
#line 588 "ecc.y"
                                                                 { (yyval.expression) = calculate((yyvsp[-2].expression), (yyvsp[0].expression), OP_GT); }
#line 3039 "parser.cpp"
    break;

  case 180:
#line 589 "ecc.y"
                                                                  { (yyval.expression) = calculate((yyvsp[-2].expression), (yyvsp[0].expression), OP_LEQ); }
#line 3045 "parser.cpp"
    break;

  case 181:
#line 590 "ecc.y"
                                                                  { (yyval.expression) = calculate((yyvsp[-2].expression), (yyvsp[0].expression), OP_GEQ); }
#line 3051 "parser.cpp"
    break;

  case 182:
#line 593 "ecc.y"
                                               { (yyval.expression) = (yyvsp[0].expression); }
#line 3057 "parser.cpp"
    break;

  case 183:
#line 594 "ecc.y"
                                                               { (yyval.expression) = calculate((yyvsp[-2].expression), (yyvsp[0].expression), OP_SL); }
#line 3063 "parser.cpp"
    break;

  case 184:
#line 595 "ecc.y"
                                                               { (yyval.expression) = calculate((yyvsp[-2].expression), (yyvsp[0].expression), OP_SR); }
#line 3069 "parser.cpp"
    break;

  case 185:
#line 598 "ecc.y"
                                           { (yyval.expression) = (yyvsp[0].expression); }
#line 3075 "parser.cpp"
    break;

  case 186:
#line 599 "ecc.y"
                                                        { (yyval.expression) = calculate((yyvsp[-2].expression), (yyvsp[0].expression), OP_ADD); }
#line 3081 "parser.cpp"
    break;

  case 187:
#line 600 "ecc.y"
                                                        { (yyval.expression) = calculate((yyvsp[-2].expression), (yyvsp[0].expression), OP_SUB); }
#line 3087 "parser.cpp"
    break;

  case 188:
#line 603 "ecc.y"
                                               { (yyval.expression) = (yyvsp[0].expression); }
#line 3093 "parser.cpp"
    break;

  case 189:
#line 604 "ecc.y"
                                                                 { (yyval.expression) = calculate((yyvsp[-2].expression), (yyvsp[0].expression), OP_MUL); }
#line 3099 "parser.cpp"
    break;

  case 190:
#line 605 "ecc.y"
                                                    { (yyval.expression) = calculate((yyvsp[-2].expression), (yyvsp[0].expression), OP_DIV); }
#line 3105 "parser.cpp"
    break;

  case 191:
#line 606 "ecc.y"
                                                    { (yyval.expression) = calculate((yyvsp[-2].expression), (yyvsp[0].expression), OP_MOD); }
#line 3111 "parser.cpp"
    break;

  case 192:
#line 609 "ecc.y"
                                                { (yyval.expression) = (yyvsp[0].expression); }
#line 3117 "parser.cpp"
    break;

  case 193:
#line 610 "ecc.y"
                                                       {
                                // coercion type casting
                                (yyval.expression) = new Expression(new Expression((yyvsp[-2].type)), (yyvsp[0].expression), OP_CAST);
                            }
#line 3126 "parser.cpp"
    break;

  case 194:
#line 616 "ecc.y"
                                                  { (yyval.expression) = (yyvsp[0].expression); }
#line 3132 "parser.cpp"
    break;

  case 195:
#line 617 "ecc.y"
                                            {
                                if((yyvsp[0].expression)->getName() == "\"Number\"")
                                    yyerror("lvalue required as decrement operand");
                                (yyval.expression) = new Expression((yyvsp[0].expression), OP_INC_FRONT);
                            }
#line 3142 "parser.cpp"
    break;

  case 196:
#line 622 "ecc.y"
                                            {
                                if((yyvsp[0].expression)->getName() == "\"Number\"")
                                    yyerror("lvalue required as decrement operand");
                                (yyval.expression) = new Expression((yyvsp[0].expression), OP_DEC_FRONT);
                            }
#line 3152 "parser.cpp"
    break;

  case 197:
#line 627 "ecc.y"
                                                      { (yyval.expression) = calculate((yyvsp[0].expression), (yyvsp[-1].op)); }
#line 3158 "parser.cpp"
    break;

  case 199:
#line 629 "ecc.y"
                                                     {
                                if((yyvsp[-1].type)->isAggregateType())
                                    yylval.num.longValue = aggrdef[((AggregateType *)(yyvsp[-1].type))->name]->getSize();
                                else
                                    yylval.num.longValue = (yyvsp[-1].type)->getSize();
                                (yyval.expression) = new Number(yylval.num, new LongType(), VAL_LONG);
                            }
#line 3170 "parser.cpp"
    break;

  case 200:
#line 638 "ecc.y"
                                                 { (yyval.op) = OP_ADDRESSOF; }
#line 3176 "parser.cpp"
    break;

  case 201:
#line 639 "ecc.y"
                                                 { (yyval.op) = OP_DEREFERENCE; }
#line 3182 "parser.cpp"
    break;

  case 202:
#line 640 "ecc.y"
                                            { (yyval.op) = OP_POSITIVE; }
#line 3188 "parser.cpp"
    break;

  case 203:
#line 641 "ecc.y"
                                            { (yyval.op) = OP_NEGATIVE; }
#line 3194 "parser.cpp"
    break;

  case 204:
#line 642 "ecc.y"
                                            { (yyval.op) = OP_NOT; }
#line 3200 "parser.cpp"
    break;

  case 205:
#line 643 "ecc.y"
                                            { (yyval.op) = OP_NOTNOT; }
#line 3206 "parser.cpp"
    break;

  case 206:
#line 646 "ecc.y"
                                                  { (yyval.expression) = (yyvsp[0].expression); }
#line 3212 "parser.cpp"
    break;

  case 207:
#line 647 "ecc.y"
                                                    {
                                if((yyvsp[-3].expression)->getName() == "\"Number\"")
                                    yyerror("subscripted value is neither array nor pointer nor vector");
                                (yyval.expression) = new Expression((yyvsp[-3].expression), (yyvsp[-1].expression), OP_INDEX);
                            }
#line 3222 "parser.cpp"
    break;

  case 208:
#line 652 "ecc.y"
                                                                  {
                                if((yyvsp[-3].expression)->getName() == "\"Number\"")
                                    yyerror("called object is not a function or function pointer");
                                (yyval.expression) = new FunctionCall((yyvsp[-3].expression), (yyvsp[-1].exprs));
                            }
#line 3232 "parser.cpp"
    break;

  case 209:
#line 657 "ecc.y"
                                                {
                                if((yyvsp[-2].expression)->getName() == "\"Number\"")
                                    yyerror("called object is not a function or function pointer");
                                (yyval.expression) = new FunctionCall((yyvsp[-2].expression), nullptr);
                            }
#line 3242 "parser.cpp"
    break;

  case 210:
#line 662 "ecc.y"
                                                         { (yyval.expression) = new Expression((yyvsp[-2].expression), new Identifier(*(yyvsp[0].stringValue)), OP_DOT); delete (yyvsp[0].stringValue); }
#line 3248 "parser.cpp"
    break;

  case 211:
#line 663 "ecc.y"
                                                        { (yyval.expression) = new Expression((yyvsp[-2].expression), new Identifier(*(yyvsp[0].stringValue)), OP_TO); delete (yyvsp[0].stringValue); }
#line 3254 "parser.cpp"
    break;

  case 212:
#line 664 "ecc.y"
                                              {
                                if((yyvsp[-1].expression)->getName() == "\"Number\"")
                                    yyerror("lvalue required as increment operand");
                                (yyval.expression) = new Expression((yyvsp[-1].expression), OP_INC_REAR);
                            }
#line 3264 "parser.cpp"
    break;

  case 213:
#line 669 "ecc.y"
                                              {
                                if((yyvsp[-1].expression)->getName() == "\"Number\"")
                                    yyerror("lvalue required as decrement operand");
                                (yyval.expression) = new Expression((yyvsp[-1].expression), OP_DEC_REAR);
                            }
#line 3274 "parser.cpp"
    break;

  case 214:
#line 676 "ecc.y"
                                                    { (yyval.expression) = new Identifier(*(yyvsp[0].stringValue)); delete (yyvsp[0].stringValue); }
#line 3280 "parser.cpp"
    break;

  case 215:
#line 677 "ecc.y"
                                            { (yyval.expression) = (yyvsp[0].number); }
#line 3286 "parser.cpp"
    break;

  case 216:
#line 678 "ecc.y"
                                            { (yyval.expression) = new String(*(yyvsp[0].stringValue)); delete (yyvsp[0].stringValue); }
#line 3292 "parser.cpp"
    break;

  case 217:
#line 679 "ecc.y"
                                            { (yyval.expression) = (yyvsp[-1].expression); }
#line 3298 "parser.cpp"
    break;

  case 218:
#line 682 "ecc.y"
                                                 { (yyval.exprs) = new vector<Expression *>; (yyval.exprs)->push_back((yyvsp[0].expression)); }
#line 3304 "parser.cpp"
    break;

  case 219:
#line 683 "ecc.y"
                                                                     { (yyvsp[-2].exprs)->push_back((yyvsp[0].expression)); (yyval.exprs) = (yyvsp[-2].exprs); }
#line 3310 "parser.cpp"
    break;

  case 220:
#line 686 "ecc.y"
                                     { (yyval.number) = (yyvsp[0].number); }
#line 3316 "parser.cpp"
    break;

  case 221:
#line 689 "ecc.y"
                                        { (yyval.number) = new Number((yyvsp[0].num), new CharType(),   VAL_CHAR); }
#line 3322 "parser.cpp"
    break;

  case 222:
#line 690 "ecc.y"
                                        { (yyval.number) = new Number((yyvsp[0].num), new ShortType(),  VAL_SHORT); }
#line 3328 "parser.cpp"
    break;

  case 223:
#line 691 "ecc.y"
                                        { (yyval.number) = new Number((yyvsp[0].num), new IntType(),    VAL_INT); }
#line 3334 "parser.cpp"
    break;

  case 224:
#line 692 "ecc.y"
                                        { (yyval.number) = new Number((yyvsp[0].num), new LongType(),   VAL_LONG); }
#line 3340 "parser.cpp"
    break;

  case 225:
#line 693 "ecc.y"
                                        { (yyval.number) = new Number((yyvsp[0].num), new FloatType(),  VAL_FLOAT); }
#line 3346 "parser.cpp"
    break;

  case 226:
#line 694 "ecc.y"
                                        { (yyval.number) = new Number((yyvsp[0].num), new DoubleType(), VAL_DOUBLE); }
#line 3352 "parser.cpp"
    break;


#line 3356 "parser.cpp"

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
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

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


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
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
                  yystos[+*yyssp], yyvsp);
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
#line 697 "ecc.y"


void yyerror(string s)
{
    cerr << "\033[1;31m" << "error: " << "\033[0m" << s << endl;
    cerr << "Line " << yylineno << ": " << "\033[1;31m" << yytext << "\033[0m" << endl;
    exit(1);
}

void yywarning(string s, string addition)
{
    cerr << "\033[1;35m" << "warning: " << "\033[0m" << s << endl;
    cerr << "Line " << yylineno << ": " << "\033[1;35m" << yytext << "\033[0m" << ". " << addition << endl;
}

static void debug(string s) {
    cout << s << ": " << yytext << endl;
}

// constant folding
static Expression *calculate(Expression *a, enum op_type op)
{
    if(a->getName() == "\"Number\"" || (a->getName() == "\"Identifier\"" && constvar.find(((Identifier *)a)->name) != constvar.end() && (a = constvar[((Identifier *)a)->name])))
    {
        union union_num num;
        bool isfloatpoint = \
            (((Number *)a)->valtype == VAL_FLOAT) || \
            (((Number *)a)->valtype == VAL_DOUBLE);

        switch(op)
        {
        case OP_ADDRESSOF:
            yyerror("lvalue required as unary '&' operand");
        case OP_DEREFERENCE:
            yyerror("invalid type argument of unary '*' operand");
        case OP_POSITIVE:
            if(isfloatpoint)
                num.doubleValue = +((Number *)a)->doubleView();
            else
                num.longValue = +((Number *)a)->longView();
            break;
        case OP_NEGATIVE:
            if(isfloatpoint)
                num.doubleValue = -((Number *)a)->doubleView();
            else
                num.longValue = -((Number *)a)->longView();
            break;
        case OP_NOT:
            if(isfloatpoint)
                yyerror("logical not is not supported for double type");
            else
                num.longValue = ~((Number *)a)->longView();
            break;
        case OP_NOTNOT:
            if(isfloatpoint)
                num.doubleValue = !((Number *)a)->doubleView();
            else
                num.longValue = !((Number *)a)->longView();
            break;
        default:
            yyerror("not supported unary operator");
        }
        
        if(isfloatpoint)
            return new Number(num, new DoubleType(), VAL_DOUBLE);
        else
            return new Number(num, new LongType(), VAL_LONG);
    }
    
    return new Expression(a, op);
}

static Expression *calculate(Expression *a, Expression *b, enum op_type op)
{
    if(
        (a->getName() == "\"Number\"" || (a->getName() == "\"Identifier\"" && constvar.find(((Identifier *)a)->name) != constvar.end() && (a = constvar[((Identifier *)a)->name]))) && \
        (b->getName() == "\"Number\"" || (b->getName() == "\"Identifier\"" && constvar.find(((Identifier *)b)->name) != constvar.end() && (b = constvar[((Identifier *)b)->name])))
    )
    {
        union union_num num;
        bool isfloatpoint = \
            (((Number *)a)->valtype == VAL_FLOAT) || \
            (((Number *)b)->valtype == VAL_FLOAT) || \
            (((Number *)a)->valtype == VAL_DOUBLE) || \
            (((Number *)b)->valtype == VAL_DOUBLE);
        if (isfloatpoint)
        {
            double_t v1 = ((Number *)a)->doubleView(), v2 = ((Number *)b)->doubleView();
            switch(op)
            {
            case OP_ADD:
                num.doubleValue = v1 + v2;
                return new Number(num, new DoubleType(), VAL_DOUBLE);
            case OP_SUB:
                num.doubleValue = v1 - v2;
                return new Number(num, new DoubleType(), VAL_DOUBLE);
            case OP_MUL:
                num.doubleValue = v1 * v2;
                return new Number(num, new DoubleType(), VAL_DOUBLE);
            case OP_DIV:
                num.doubleValue = v1 / v2;
                return new Number(num, new DoubleType(), VAL_DOUBLE);
            case OP_COMMA:
                num.doubleValue = v2;
                return new Number(num, new DoubleType(), VAL_DOUBLE);
            case OP_EQ:
                num.longValue = v1 == v2;
                break;
            case OP_NEQ:
                num.longValue = v1 != v2;
                break;
            case OP_LT:
                num.longValue = v1 < v2;
                break;
            case OP_GT:
                num.longValue = v1 > v2;
                break;
            case OP_LEQ:
                num.longValue = v1 <= v2;
                break;
            case OP_GEQ:
                num.longValue = v1 >= v2;
                break;
            case OP_OROR:
                num.longValue = v1 || v2;
                break;
            case OP_ANDAND:
                num.longValue = v1 && v2;
                break;
            default:
                yyerror("not supported binary operator for double type");
            }
            return new Number(num, new LongType(), VAL_LONG);
        }
        else
        {
            uint64_t v1 = ((Number *)a)->longView(), v2 = ((Number *)b)->longView();
            switch(op)
            {
            case OP_ADD:
                num.longValue = v1 + v2;
                break;
            case OP_SUB:
                num.longValue = v1 - v2;
                break;
            case OP_MUL:
                num.longValue = v1 * v2;
                break;
            case OP_DIV:
                num.longValue = v1 / v2;
                break;
            case OP_MOD:
                num.longValue = v1 % v2;
                break;
            case OP_COMMA:
                num.longValue = v2;
                break;
            case OP_SL:
                num.longValue = v1 >> v2;
                break;
            case OP_SR:
                num.longValue = v1 << v2;
                break;
            case OP_AND:
                num.longValue = v1 & v2;
                break;
            case OP_OR:
                num.longValue = v1 | v2;
                break;
            case OP_XOR:
                num.longValue = v1 ^ v2;
                break;
            case OP_EQ:
                num.longValue = v1 == v2;
                break;
            case OP_NEQ:
                num.longValue = v1 != v2;
                break;
            case OP_LT:
                num.longValue = v1 < v2;
                break;
            case OP_GT:
                num.longValue = v1 > v2;
                break;
            case OP_LEQ:
                num.longValue = v1 <= v2;
                break;
            case OP_GEQ:
                num.longValue = v1 >= v2;
                break;
            case OP_OROR:
                num.longValue = v1 || v2;
                break;
            case OP_ANDAND:
                num.longValue = v1 && v2;
                break;
            default:
                yyerror("not supported binary operator for long type");
            }

            return new Number(num, new LongType(), VAL_LONG);
        }
    
    }
    return new Expression(a, b, op);
}

static Expression *calculate(Expression *a, Expression *b, Expression *c, enum op_type op)
{
    if(
        (a->getName() == "\"Number\"" || (a->getName() == "\"Identifier\"" && constvar.find(((Identifier *)a)->name) != constvar.end() && (a = constvar[((Identifier *)a)->name]))) && \
        (b->getName() == "\"Number\"" || (b->getName() == "\"Identifier\"" && constvar.find(((Identifier *)b)->name) != constvar.end() && (b = constvar[((Identifier *)b)->name]))) && \
        (c->getName() == "\"Number\"" || (c->getName() == "\"Identifier\"" && constvar.find(((Identifier *)c)->name) != constvar.end() && (c = constvar[((Identifier *)c)->name])))
    )
    {
        union union_num num;
        bool isfloatpoint = \
            (((Number *)b)->valtype == VAL_FLOAT) || \
            (((Number *)c)->valtype == VAL_FLOAT) || \
            (((Number *)b)->valtype == VAL_DOUBLE) || \
            (((Number *)c)->valtype == VAL_DOUBLE);
        bool choice;
        switch(op)
        {
        case OP_IFELSE:
            switch(((Number *)a)->valtype)
            {
            case VAL_CHAR:
            case VAL_SHORT:
            case VAL_INT:
            case VAL_LONG:
                choice = ((Number *)a)->longView() != 0;
                break;
            case VAL_FLOAT:
            case VAL_DOUBLE:
                choice = ((Number *)a)->doubleView() != 0;
                break;
            default:
                yyerror("not supported value type for condition");
            }
            break;
        default:
            yyerror("not supported trinary operator");
        }

        if(isfloatpoint)
        {
            if(choice)
                num.doubleValue = ((Number *)b)->doubleView();
            else
                num.doubleValue = ((Number *)c)->doubleView();
            return new Number(num, new DoubleType(), VAL_DOUBLE);
        }
        else
        {
            if(choice)
                num.doubleValue = ((Number *)b)->longView();
            else
                num.doubleValue = ((Number *)c)->longView();
            return new Number(num, new LongType(), VAL_LONG);
        }
    }
    
    return new Expression(a, b, c, op);
}
