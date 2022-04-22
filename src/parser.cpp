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
Program *program;

#line 75 "parser.cpp"

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
# define YYERROR_VERBOSE 0
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_PARSER_HPP_INCLUDED
# define YY_YY_PARSER_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 8 "ecc.y"

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
void yywarning(string s, string addition = "");

#line 139 "parser.cpp"

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
    MUL = 289,
    DIV = 290,
    MOD = 291,
    ADDASSIGN = 292,
    SUBASSIGN = 293,
    MULASSIGN = 294,
    DIVASSIGN = 295,
    MODASSIGN = 296,
    AND = 297,
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
    TYPEDEF = 320,
    SIZEOF = 321,
    RETURN = 322,
    DOTDOTDOT = 323,
    DELIM = 324,
    COMMA = 325,
    COLON = 326,
    QUESTION = 327,
    DOT = 328,
    TO = 329,
    LP = 330,
    RP = 331,
    LB = 332,
    RB = 333,
    LC = 334,
    RC = 335,
    NUMCHAR = 336,
    NUMSHORT = 337,
    NUMINT = 338,
    NUMLONG = 339,
    NUMFLOAT = 340,
    NUMDOUBLE = 341,
    STRING = 342,
    IDENTIFIER = 343
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 29 "ecc.y"

    union union_num num;
    string *stringValue;
    enum op_type op;
    bool flag;
    
    Program *program;

    TypeSpecifier *type;

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

#line 268 "parser.cpp"

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
#define YYFINAL  41
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1790

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  89
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  69
/* YYNRULES -- Number of rules.  */
#define YYNRULES  217
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  374

#define YYUNDEFTOK  2
#define YYMAXUTOK   343


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
      85,    86,    87,    88
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   114,   114,   117,   118,   121,   122,   125,   126,   127,
     128,   131,   132,   135,   136,   139,   140,   150,   151,   154,
     155,   156,   157,   158,   159,   160,   161,   162,   163,   166,
     167,   170,   171,   172,   175,   176,   179,   180,   183,   184,
     187,   188,   191,   194,   195,   196,   197,   200,   201,   204,
     205,   206,   209,   210,   211,   214,   215,   218,   219,   222,
     223,   226,   227,   228,   229,   230,   231,   232,   235,   236,
     237,   238,   241,   242,   245,   246,   249,   250,   253,   254,
     255,   258,   259,   262,   263,   264,   267,   268,   271,   272,
     275,   278,   279,   280,   281,   282,   283,   284,   285,   286,
     289,   292,   295,   296,   297,   298,   299,   300,   303,   304,
     305,   308,   309,   312,   313,   314,   315,   318,   319,   322,
     323,   324,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   339,   340,   341,   342,   343,   346,   347,   350,
     351,   354,   355,   356,   357,   358,   359,   360,   361,   362,
     363,   364,   367,   368,   371,   374,   375,   378,   379,   382,
     383,   386,   387,   390,   391,   394,   395,   396,   399,   400,
     401,   402,   403,   406,   407,   408,   411,   412,   413,   416,
     417,   418,   419,   422,   423,   426,   427,   428,   429,   430,
     431,   434,   435,   436,   437,   438,   439,   442,   443,   444,
     445,   446,   447,   448,   449,   452,   453,   454,   455,   458,
     459,   468,   471,   472,   473,   474,   475,   476
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "CHAR", "SHORT", "INT", "LONG", "FLOAT",
  "DOUBLE", "STRUCT", "ENUM", "UNION", "VOID", "AUTO", "REGISTER",
  "EXTERN", "CONST", "UNSIGNED", "SIGNED", "VOLATILE", "STATIC", "IF",
  "ELSE", "FOR", "DO", "WHILE", "BREAK", "CONTINUE", "SWITCH", "CASE",
  "DEFAULT", "GOTO", "ADD", "SUB", "MUL", "DIV", "MOD", "ADDASSIGN",
  "SUBASSIGN", "MULASSIGN", "DIVASSIGN", "MODASSIGN", "AND", "OR", "XOR",
  "NOT", "SL", "SR", "ANDASSIGN", "ORASSIGN", "XORASSIGN", "SLASSIGN",
  "SRASSIGN", "ANDAND", "OROR", "NOTNOT", "LT", "GT", "GEQ", "LEQ", "NEQ",
  "EQ", "ASSIGN", "INC", "DEC", "TYPEDEF", "SIZEOF", "RETURN", "DOTDOTDOT",
  "DELIM", "COMMA", "COLON", "QUESTION", "DOT", "TO", "LP", "RP", "LB",
  "RB", "LC", "RC", "NUMCHAR", "NUMSHORT", "NUMINT", "NUMLONG", "NUMFLOAT",
  "NUMDOUBLE", "STRING", "IDENTIFIER", "$accept", "program",
  "translation-unit", "external-decl", "function-definition", "decl",
  "decl-list", "decl-specs", "signed-spec", "type-spec", "type-qualifier",
  "struct-or-union-spec", "struct-or-union", "struct-decl-list",
  "init-declarator-list", "init-declarator", "struct-decl",
  "spec-qualifier-list", "struct-declarator-list", "struct-declarator",
  "enum-spec", "enumerator-list", "enumerator", "declarator",
  "direct-declarator", "pointer", "type-qualifier-list", "param-type-list",
  "param-list", "param-decl", "id-list", "initializer", "initializer-list",
  "type-name", "abstract-declarator", "direct-abstract-declarator",
  "typedef-name", "id", "stat", "labeled-stat", "exp-stat",
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
     335,   336,   337,   338,   339,   340,   341,   342,   343
};
# endif

#define YYPACT_NINF (-159)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-101)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     210,  -159,  -159,  -159,  -159,  -159,  -159,  -159,   -41,  -159,
    -159,  -159,  -159,    24,     7,  -159,    16,   210,  -159,  -159,
    -159,    60,   464,  -159,  -159,   -23,  -159,   776,   -11,   -27,
    -159,   -14,   -65,   -37,  -159,  -159,  -159,  -159,    24,   -31,
    -159,  -159,  -159,  -159,   118,  -159,   482,  -159,  -159,   911,
     -12,   378,   119,    12,    27,  -159,  -159,   862,  1178,   -11,
     -20,  -159,    26,   -65,  -159,  -159,  -159,  -159,     7,  1213,
      12,  -159,   911,   911,   605,  -159,   171,   911,    39,    62,
    1064,    72,    83,    92,    97,  1631,   114,   -65,  -159,  -159,
    -159,  -159,  -159,  -159,  1688,  1688,  1702,  1248,  -159,   758,
    -159,  -159,  -159,  -159,  -159,  -159,  -159,  -159,  -159,   500,
      60,    50,  -159,  -159,  -159,  -159,   928,  -159,  -159,  -159,
     141,  -159,  -159,   -28,   124,   163,   179,   183,   230,   267,
     253,   288,   234,  -159,   498,  1631,   219,  -159,  -159,  -159,
      36,   586,  -159,  -159,    40,  -159,   878,  -159,   125,     9,
      69,  -159,  -159,  -159,   160,  -159,   -65,  -159,  1631,    13,
    -159,   181,  1213,  -159,  -159,  -159,  -159,  -159,  -159,  -159,
    1631,   266,  -159,   170,   894,  1631,  1305,   189,   237,  1631,
    -159,  -159,  1631,   194,  1064,   206,  1631,  -159,  -159,   758,
    -159,  -159,   269,    53,   202,   159,    79,  -159,  -159,   996,
    1064,  -159,  -159,  -159,  1631,  1631,  1631,  1631,  1631,  1631,
    1631,  1631,  1631,  1631,  1631,  1631,  1631,  1631,  1631,  1631,
    1631,  1631,  1631,  1631,  -159,  -159,  -159,  -159,  -159,  -159,
    -159,  -159,  -159,  -159,  -159,  1631,  -159,  -159,  -159,   -65,
     -65,  1362,  1631,  -159,   205,  -159,   208,   209,   221,   672,
    -159,  -159,  -159,   -65,  -159,  -159,  -159,  -159,  -159,  -159,
      64,  -159,  -159,   171,  1631,  -159,    81,  1397,   289,   227,
     106,   110,  1064,  -159,  -159,   270,  -159,   273,  -159,  1631,
    -159,  -159,  -159,  -159,   124,   272,   163,   179,   183,   230,
     267,   267,   253,   253,   253,   253,   288,   288,   234,   234,
    -159,  -159,  -159,  -159,  -159,  -159,  -159,  -159,   132,    20,
    -159,  -159,  -159,  -159,  -159,   276,   277,  -159,  1121,  -159,
    -159,  -159,  1064,  1454,   292,  1489,  1631,  1064,  1064,  -159,
    -159,  -159,  1631,  1631,  -159,  -159,  -159,  -159,  -159,  -159,
     335,  1064,   133,  1546,  1560,   298,   154,  -159,  -159,  -159,
    -159,  1064,  -159,  1064,  1064,   156,  1064,   182,  1617,   302,
    -159,  -159,  -159,  1064,  -159,  1064,  1064,   191,  -159,  -159,
    -159,  -159,  1064,  -159
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    19,    20,    21,    22,    23,    24,    34,     0,    35,
      25,    18,    17,    69,     0,   101,     0,     2,     3,     5,
       6,     0,     0,    16,    26,     0,    27,     0,    60,     0,
      28,    61,     0,    54,    29,    30,    72,    71,    68,     0,
      61,     1,     4,    12,     0,    38,    40,    15,   100,     0,
      33,     0,    80,     0,    74,    76,    10,     0,     0,    59,
       0,    55,    57,     0,    73,    70,    62,    11,     0,     0,
       0,     9,    44,    46,     0,    36,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   193,   194,
     192,   191,   195,   196,     0,     0,     0,     0,   112,     0,
     116,   212,   213,   214,   215,   216,   217,   207,    13,     0,
       0,   205,   117,   102,   103,   104,     0,   105,   106,   107,
       0,   137,   139,   152,   155,   157,   159,   161,   163,   165,
     168,   173,   176,   179,   183,     0,   185,   197,   206,   211,
       0,     0,    78,    79,    90,     8,     0,    67,     0,     0,
     100,    64,   205,   154,     0,   183,     0,    53,     0,     0,
      39,    40,     0,    41,    83,     7,    43,    45,    32,    37,
       0,     0,    47,    49,     0,     0,     0,   205,     0,     0,
     134,   133,     0,     0,     0,     0,     0,   186,   187,     0,
     189,   136,     0,    89,     0,   205,     0,   115,    14,     0,
       0,   114,   118,   111,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   145,   146,   142,   143,   144,   149,
     151,   150,   147,   148,   141,     0,   188,   203,   204,     0,
       0,     0,     0,    99,     0,    95,     0,     0,     0,     0,
      75,    77,    65,     0,    66,    63,    56,    58,    52,    86,
       0,    51,    42,     0,     0,    31,     0,     0,     0,     0,
       0,     0,     0,   110,   132,     0,   135,     0,    88,     0,
     208,   113,   108,   138,   156,     0,   158,   160,   162,   164,
     167,   166,   169,   170,   172,   171,   174,   175,   177,   178,
     180,   181,   182,   140,   201,   202,   200,   209,     0,     0,
      91,    97,    93,    98,    94,     0,     0,    82,     0,    84,
      48,    50,     0,     0,     0,     0,     0,     0,     0,   109,
     190,   184,     0,     0,   199,   198,    96,    92,    85,    87,
     119,     0,     0,     0,     0,     0,     0,   122,   121,   153,
     210,     0,   131,     0,     0,     0,     0,     0,     0,     0,
     120,   130,   129,     0,   128,     0,     0,     0,   123,   127,
     126,   125,     0,   124
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -159,  -159,  -159,   361,  -159,   -38,  -159,    18,  -159,    59,
      15,  -159,  -159,   303,  -159,   311,   -69,   -63,  -159,   128,
    -159,   329,   238,    10,   364,    21,  -159,   -45,  -159,   251,
    -159,  -158,  -159,   224,   -50,  -159,  -159,     0,   -77,  -159,
    -159,   -16,   305,  -159,  -159,  -159,   158,   -62,  -159,   -52,
     -66,  -159,   193,   211,   207,   212,   214,   162,   116,   152,
     157,  -120,    96,  -159,  -159,  -159,  -159,  -159,  -159
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    16,    17,    18,    19,    20,   109,    52,    22,    23,
      73,    24,    25,    74,    44,    45,    75,    76,   171,   172,
      26,    60,    61,    27,    28,    29,    38,    53,    54,    55,
     149,   163,   260,   194,   244,   144,    30,   152,   112,   113,
     114,   115,   116,   117,   118,   119,   120,   121,   235,   122,
     154,   123,   124,   125,   126,   127,   128,   129,   130,   131,
     132,   133,   134,   135,   136,   137,   308,   138,   139
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      31,    70,   143,   178,   259,   169,   153,   164,    33,   166,
     167,    56,   148,   108,    40,   236,    41,    31,    21,   183,
    -100,    40,    48,    15,    39,    50,   205,    48,    36,    40,
      71,    46,    62,   153,    37,    21,   193,   145,    32,   202,
      34,    13,    63,    35,   206,    66,    48,    15,    14,    48,
     156,   111,    40,    64,   165,  -100,    49,   150,    13,    65,
     157,    15,   142,    62,    57,    15,    58,    77,    40,   110,
      13,   198,    48,    48,    48,   247,    40,    48,   161,   253,
     177,    47,    14,   156,  -100,   254,   173,   185,   158,   153,
     204,    51,   257,   258,    13,    15,   246,   146,   335,   195,
     164,   300,   301,   302,   261,   169,   153,   273,    72,   111,
      40,   140,   243,   141,   175,   248,   177,   249,   153,  -100,
     161,   200,   202,   282,    15,  -100,   193,   110,   277,    43,
     141,    72,    72,    72,   318,    14,    72,   176,  -100,   -81,
      40,   195,   283,   278,   319,   -81,    48,   179,    15,   204,
      39,   204,   180,    13,   155,   280,    62,   322,    72,   331,
     339,   181,  -100,  -100,  -100,  -100,  -100,  -100,  -100,  -100,
    -100,  -100,   182,   303,    48,  -100,   204,   207,  -100,   307,
     204,   155,   327,   316,   177,   184,   328,    67,    68,   195,
     187,   188,   190,  -100,   140,   329,   141,   153,   321,   177,
     177,   252,   333,   204,   315,    13,   208,    15,   334,   353,
     203,   204,   153,     1,     2,     3,     4,     5,     6,     7,
       8,     9,    10,   209,   204,   210,   204,    11,    12,  -100,
     359,   155,   363,    72,  -100,  -100,  -100,   155,   255,   304,
     305,   264,   170,    69,    13,   340,    14,  -100,    72,   195,
     347,   348,   204,   317,   155,   192,   164,   196,   365,    15,
     200,   204,   269,    40,   352,   272,   155,   372,   221,   222,
     223,   350,   177,   173,   360,   274,   361,   362,   279,   364,
     349,   310,   237,   238,   311,    14,   369,   312,   370,   371,
     211,   212,   239,   240,   241,   373,   242,   313,    15,   217,
     218,   155,   326,   155,   155,   155,   155,   155,   155,   155,
     155,   155,   155,   155,   155,   155,   155,   155,   155,   155,
     219,   220,   177,   213,   214,   215,   216,   177,   177,   292,
     293,   294,   295,   266,   268,   262,   263,   270,   276,   204,
     271,   177,   204,   332,   196,   155,   330,   196,   277,   243,
     141,   177,   336,   177,   177,   337,   177,   351,   325,   204,
     155,   343,   204,   177,   285,   177,   177,   358,   204,   296,
     297,   368,   177,   290,   291,   155,   298,   299,    42,   160,
     174,     1,     2,     3,     4,     5,     6,     7,     8,     9,
      10,   320,   159,    59,   256,    11,    12,   251,   284,    78,
     309,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,   275,   199,   287,     0,     0,   286,     0,
      91,   288,     0,    92,   289,   324,     0,     0,   155,     0,
       0,     0,     0,    93,     0,     0,     0,     0,     0,     0,
       0,    94,    95,     0,    96,    97,     0,    98,     0,     0,
       0,     0,     0,    99,     0,     0,     0,    51,   100,   101,
     102,   103,   104,   105,   106,   107,    15,     1,     2,     3,
       4,     5,     6,     7,     8,     9,    10,     0,     0,     0,
       0,   342,     0,   345,   346,     1,     2,     3,     4,     5,
       6,     7,     8,     9,    10,     0,     0,     0,     0,    11,
      12,   355,   357,     1,     2,     3,     4,     5,     6,     7,
       8,     9,    10,     0,     0,     0,   367,    11,    12,     0,
       0,    78,     0,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,   224,   225,   226,   227,   228,
       0,     0,    91,     0,    69,    92,   229,   230,   231,   232,
     233,     0,    15,     0,     0,    93,     0,     0,     0,     0,
     234,    51,     0,    94,    95,     0,    96,    97,     0,    98,
      15,     0,     0,     0,     0,    99,     0,     0,     0,    51,
     197,   101,   102,   103,   104,   105,   106,   107,    15,     1,
       2,     3,     4,     5,     6,     7,     8,     9,    10,     0,
       0,     0,     0,    11,    12,     0,     0,     0,     1,     2,
       3,     4,     5,     6,     7,     8,     9,    10,    88,    89,
      90,    34,     0,     0,    35,     0,     0,     0,    91,     0,
       0,    92,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    93,     0,     0,     0,     0,     0,     0,     0,    94,
      95,     0,    96,     0,     0,     0,     0,     0,     0,     0,
       0,    99,     0,     0,   245,     0,     0,   101,   102,   103,
     104,   105,   106,   107,    15,     1,     2,     3,     4,     5,
       6,     7,     8,     9,    10,   168,     0,     0,     0,    11,
      12,     0,     0,    15,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    88,    89,    90,     0,     0,     0,
       0,     0,     0,     0,    91,     0,     0,    92,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    93,     0,     0,
       0,     0,     0,     0,     0,    94,    95,     0,    96,     0,
       0,     0,     0,     0,     0,     0,     0,    99,     0,     0,
     314,     0,     0,   101,   102,   103,   104,   105,   106,   107,
      15,     1,     2,     3,     4,     5,     6,     7,     8,     9,
      10,     0,     0,     0,    34,     0,     0,    35,     0,     1,
       2,     3,     4,     5,     6,     7,     8,     9,    10,     0,
      88,    89,    90,    11,    12,     0,     0,     0,     0,     0,
      91,     0,     0,    92,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    93,     0,     0,     0,     0,     0,     0,
       0,    94,    95,     0,    96,     0,     0,     0,     0,     0,
       0,     0,     0,    99,     0,     0,     0,     0,     0,   101,
     102,   103,   104,   105,   106,   107,    15,     0,     0,     0,
       0,     0,     0,     0,     0,    51,     0,     0,     0,     0,
       0,     0,     0,     0,    15,     1,     2,     3,     4,     5,
       6,     7,     8,     9,    10,     0,     0,     0,     0,    11,
      12,     1,     2,     3,     4,     5,     6,     7,     8,     9,
      10,     0,     0,     0,     0,    11,    12,     1,     2,     3,
       4,     5,     6,     7,     8,     9,    10,     0,     0,     0,
      34,     0,     0,    35,     1,     2,     3,     4,     5,     6,
       7,     8,     9,    10,     0,     0,     0,    34,     0,     0,
      35,     0,     0,     0,     0,     0,     0,     0,   147,     0,
       0,     0,     0,     0,     0,     0,   250,     0,     0,    78,
      15,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,     0,     0,     0,    15,     0,     0,     0,
      91,     0,     0,    92,   265,     0,     0,     0,     0,     0,
       0,     0,    15,    93,     0,     0,     0,     0,     0,     0,
       0,    94,    95,     0,    96,    97,     0,    98,     0,    15,
       0,     0,     0,    99,     0,     0,     0,    51,   201,   101,
     102,   103,   104,   105,   106,   107,    15,    78,     0,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,     0,     0,     0,     0,     0,     0,     0,    91,     0,
       0,    92,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    93,     0,     0,     0,     0,     0,     0,     0,    94,
      95,     0,    96,    97,     0,    98,     0,     0,     0,     0,
       0,    99,     0,     0,     0,    51,   281,   101,   102,   103,
     104,   105,   106,   107,    15,    78,     0,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,     0,
       0,     0,     0,     0,     0,     0,    91,     0,     0,    92,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    93,
       0,     0,     0,     0,     0,     0,     0,    94,    95,     0,
      96,    97,     0,    98,     0,     0,     0,     0,     0,    99,
       0,     0,     0,    51,     0,   101,   102,   103,   104,   105,
     106,   107,    15,    88,    89,    90,     0,     0,     0,     0,
       0,     0,     0,    91,     0,     0,    92,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    93,     0,     0,     0,
       0,     0,     0,     0,    94,    95,     0,    96,     0,     0,
       0,     0,     0,     0,     0,     0,    99,     0,     0,     0,
     162,   338,   101,   102,   103,   104,   105,   106,   107,    15,
      88,    89,    90,     0,     0,     0,     0,     0,     0,     0,
      91,     0,     0,    92,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    93,     0,     0,     0,     0,     0,     0,
       0,    94,    95,     0,    96,    88,    89,    90,     0,     0,
       0,     0,     0,    99,     0,    91,   151,     0,    92,   101,
     102,   103,   104,   105,   106,   107,    15,     0,    93,     0,
       0,     0,     0,     0,     0,     0,    94,    95,     0,    96,
      88,    89,    90,     0,     0,     0,     0,     0,    99,     0,
      91,     0,   162,    92,   101,   102,   103,   104,   105,   106,
     107,    15,     0,    93,     0,     0,     0,     0,     0,     0,
       0,    94,    95,     0,    96,     0,     0,   191,     0,     0,
       0,     0,     0,    99,     0,     0,     0,     0,     0,   101,
     102,   103,   104,   105,   106,   107,    15,    88,    89,    90,
       0,     0,     0,     0,     0,     0,     0,    91,     0,     0,
      92,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      93,     0,     0,     0,     0,     0,     0,     0,    94,    95,
       0,    96,     0,     0,   267,     0,     0,     0,     0,     0,
      99,     0,     0,     0,     0,     0,   101,   102,   103,   104,
     105,   106,   107,    15,    88,    89,    90,     0,     0,     0,
       0,     0,     0,     0,    91,     0,     0,    92,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    93,     0,     0,
       0,     0,     0,     0,     0,    94,    95,     0,    96,    88,
      89,    90,     0,     0,     0,     0,     0,    99,   306,    91,
       0,     0,    92,   101,   102,   103,   104,   105,   106,   107,
      15,     0,    93,     0,     0,     0,     0,     0,     0,     0,
      94,    95,     0,    96,     0,     0,   323,     0,     0,     0,
       0,     0,    99,     0,     0,     0,     0,     0,   101,   102,
     103,   104,   105,   106,   107,    15,    88,    89,    90,     0,
       0,     0,     0,     0,     0,     0,    91,     0,     0,    92,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    93,
       0,     0,     0,     0,     0,     0,     0,    94,    95,     0,
      96,    88,    89,    90,     0,     0,     0,     0,     0,    99,
     341,    91,     0,     0,    92,   101,   102,   103,   104,   105,
     106,   107,    15,     0,    93,     0,     0,     0,     0,     0,
       0,     0,    94,    95,     0,    96,     0,     0,   344,     0,
       0,     0,     0,     0,    99,     0,     0,     0,     0,     0,
     101,   102,   103,   104,   105,   106,   107,    15,    88,    89,
      90,     0,     0,     0,     0,     0,     0,     0,    91,     0,
       0,    92,    88,    89,    90,     0,     0,     0,     0,     0,
       0,    93,    91,     0,     0,    92,     0,     0,     0,    94,
      95,     0,    96,     0,     0,    93,     0,     0,     0,     0,
       0,    99,   354,    94,    95,     0,    96,   101,   102,   103,
     104,   105,   106,   107,    15,    99,   356,     0,     0,     0,
       0,   101,   102,   103,   104,   105,   106,   107,    15,    88,
      89,    90,     0,     0,     0,     0,     0,     0,     0,    91,
       0,     0,    92,    88,    89,    90,     0,     0,     0,     0,
       0,     0,    93,    91,     0,     0,    92,     0,     0,     0,
      94,    95,     0,    96,     0,     0,    93,     0,     0,     0,
       0,     0,    99,   366,    94,    95,     0,    96,   101,   102,
     103,   104,   105,   106,   107,    15,    99,     0,     0,     0,
       0,     0,   101,   102,   103,   104,   105,   106,   107,    15,
      88,    89,    90,     0,     0,     0,     0,     0,     0,     0,
      91,     0,     0,    92,    88,    89,    90,     0,     0,     0,
       0,     0,     0,    93,    91,     0,     0,    92,     0,     0,
       0,    94,    95,     0,    96,     0,     0,    93,     0,     0,
       0,     0,     0,   186,     0,    94,    95,     0,    96,   101,
     102,   103,   104,   105,   106,   107,    15,   189,     0,     0,
       0,     0,     0,   101,   102,   103,   104,   105,   106,   107,
      15
};

static const yytype_int16 yycheck[] =
{
       0,    46,    52,    80,   162,    74,    58,    69,     8,    72,
      73,    27,    57,    51,    14,   135,     0,    17,     0,    85,
      34,    21,    22,    88,    14,    25,    54,    27,    13,    29,
      46,    21,    32,    85,    13,    17,    99,    53,    79,   116,
      16,    34,    79,    19,    72,    76,    46,    88,    75,    49,
      70,    51,    52,    38,    70,    69,    79,    57,    34,    38,
      80,    88,    52,    63,    75,    88,    77,    79,    68,    51,
      34,   109,    72,    73,    74,   141,    76,    77,    68,    70,
      80,    22,    75,    70,    34,    76,    76,    87,    62,   141,
      70,    79,   158,    80,    34,    88,   141,    70,    78,    99,
     162,   221,   222,   223,   170,   174,   158,   184,    49,   109,
     110,    75,    76,    77,    75,    75,   116,    77,   170,    69,
     110,    71,   199,   200,    88,    75,   189,   109,    75,    69,
      77,    72,    73,    74,    70,    75,    77,    75,    88,    70,
     140,   141,   204,   193,    80,    76,   146,    75,    88,    70,
     140,    70,    69,    34,    58,    76,   156,    76,    99,   279,
     318,    69,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    75,   235,   174,    16,    70,    53,    19,   241,
      70,    85,    76,   249,   184,    71,    76,    69,    70,   189,
      94,    95,    96,    34,    75,   272,    77,   249,   264,   199,
     200,    76,    70,    70,   249,    34,    43,    88,    76,    76,
      69,    70,   264,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    44,    70,    42,    70,    17,    18,    70,
      76,   135,    76,   174,    75,    76,    77,   141,    78,   239,
     240,    71,    71,    62,    34,   322,    75,    88,   189,   249,
     327,   328,    70,   253,   158,    97,   318,    99,    76,    88,
      71,    70,    25,   263,   341,    71,   170,    76,    34,    35,
      36,   333,   272,   263,   351,    69,   353,   354,    76,   356,
     332,    76,    63,    64,    76,    75,   363,    78,   365,   366,
      60,    61,    73,    74,    75,   372,    77,    76,    88,    46,
      47,   205,    75,   207,   208,   209,   210,   211,   212,   213,
     214,   215,   216,   217,   218,   219,   220,   221,   222,   223,
      32,    33,   322,    56,    57,    58,    59,   327,   328,   213,
     214,   215,   216,   175,   176,    69,    70,   179,    69,    70,
     182,   341,    70,    71,   186,   249,    76,   189,    75,    76,
      77,   351,    76,   353,   354,    78,   356,    22,    69,    70,
     264,    69,    70,   363,   206,   365,   366,    69,    70,   217,
     218,    69,   372,   211,   212,   279,   219,   220,    17,    68,
      77,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,   263,    63,    29,   156,    17,    18,   146,   205,    21,
     242,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,   189,   109,   208,    -1,    -1,   207,    -1,
      42,   209,    -1,    45,   210,   267,    -1,    -1,   332,    -1,
      -1,    -1,    -1,    55,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    63,    64,    -1,    66,    67,    -1,    69,    -1,    -1,
      -1,    -1,    -1,    75,    -1,    -1,    -1,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    -1,    -1,    -1,
      -1,   323,    -1,   325,   326,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    -1,    -1,    -1,    -1,    17,
      18,   343,   344,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    -1,    -1,    -1,   358,    17,    18,    -1,
      -1,    21,    -1,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    37,    38,    39,    40,    41,
      -1,    -1,    42,    -1,    62,    45,    48,    49,    50,    51,
      52,    -1,    88,    -1,    -1,    55,    -1,    -1,    -1,    -1,
      62,    79,    -1,    63,    64,    -1,    66,    67,    -1,    69,
      88,    -1,    -1,    -1,    -1,    75,    -1,    -1,    -1,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    -1,
      -1,    -1,    -1,    17,    18,    -1,    -1,    -1,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    32,    33,
      34,    16,    -1,    -1,    19,    -1,    -1,    -1,    42,    -1,
      -1,    45,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    55,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    63,
      64,    -1,    66,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    75,    -1,    -1,    78,    -1,    -1,    81,    82,    83,
      84,    85,    86,    87,    88,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    80,    -1,    -1,    -1,    17,
      18,    -1,    -1,    88,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    32,    33,    34,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    42,    -1,    -1,    45,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    55,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    63,    64,    -1,    66,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    75,    -1,    -1,
      78,    -1,    -1,    81,    82,    83,    84,    85,    86,    87,
      88,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    -1,    -1,    -1,    16,    -1,    -1,    19,    -1,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    -1,
      32,    33,    34,    17,    18,    -1,    -1,    -1,    -1,    -1,
      42,    -1,    -1,    45,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    55,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    63,    64,    -1,    66,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    75,    -1,    -1,    -1,    -1,    -1,    81,
      82,    83,    84,    85,    86,    87,    88,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    79,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    88,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    -1,    -1,    -1,    -1,    17,
      18,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    -1,    -1,    -1,    -1,    17,    18,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    -1,    -1,    -1,
      16,    -1,    -1,    19,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    -1,    -1,    -1,    16,    -1,    -1,
      19,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    76,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    68,    -1,    -1,    21,
      88,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    -1,    -1,    -1,    88,    -1,    -1,    -1,
      42,    -1,    -1,    45,    80,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    88,    55,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    63,    64,    -1,    66,    67,    -1,    69,    -1,    88,
      -1,    -1,    -1,    75,    -1,    -1,    -1,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    21,    -1,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    42,    -1,
      -1,    45,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    55,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    63,
      64,    -1,    66,    67,    -1,    69,    -1,    -1,    -1,    -1,
      -1,    75,    -1,    -1,    -1,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    21,    -1,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    42,    -1,    -1,    45,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    55,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    63,    64,    -1,
      66,    67,    -1,    69,    -1,    -1,    -1,    -1,    -1,    75,
      -1,    -1,    -1,    79,    -1,    81,    82,    83,    84,    85,
      86,    87,    88,    32,    33,    34,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    42,    -1,    -1,    45,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    55,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    63,    64,    -1,    66,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    75,    -1,    -1,    -1,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      32,    33,    34,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      42,    -1,    -1,    45,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    55,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    63,    64,    -1,    66,    32,    33,    34,    -1,    -1,
      -1,    -1,    -1,    75,    -1,    42,    78,    -1,    45,    81,
      82,    83,    84,    85,    86,    87,    88,    -1,    55,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    63,    64,    -1,    66,
      32,    33,    34,    -1,    -1,    -1,    -1,    -1,    75,    -1,
      42,    -1,    79,    45,    81,    82,    83,    84,    85,    86,
      87,    88,    -1,    55,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    63,    64,    -1,    66,    -1,    -1,    69,    -1,    -1,
      -1,    -1,    -1,    75,    -1,    -1,    -1,    -1,    -1,    81,
      82,    83,    84,    85,    86,    87,    88,    32,    33,    34,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    42,    -1,    -1,
      45,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      55,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    63,    64,
      -1,    66,    -1,    -1,    69,    -1,    -1,    -1,    -1,    -1,
      75,    -1,    -1,    -1,    -1,    -1,    81,    82,    83,    84,
      85,    86,    87,    88,    32,    33,    34,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    42,    -1,    -1,    45,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    55,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    63,    64,    -1,    66,    32,
      33,    34,    -1,    -1,    -1,    -1,    -1,    75,    76,    42,
      -1,    -1,    45,    81,    82,    83,    84,    85,    86,    87,
      88,    -1,    55,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      63,    64,    -1,    66,    -1,    -1,    69,    -1,    -1,    -1,
      -1,    -1,    75,    -1,    -1,    -1,    -1,    -1,    81,    82,
      83,    84,    85,    86,    87,    88,    32,    33,    34,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    42,    -1,    -1,    45,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    55,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    63,    64,    -1,
      66,    32,    33,    34,    -1,    -1,    -1,    -1,    -1,    75,
      76,    42,    -1,    -1,    45,    81,    82,    83,    84,    85,
      86,    87,    88,    -1,    55,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    63,    64,    -1,    66,    -1,    -1,    69,    -1,
      -1,    -1,    -1,    -1,    75,    -1,    -1,    -1,    -1,    -1,
      81,    82,    83,    84,    85,    86,    87,    88,    32,    33,
      34,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    42,    -1,
      -1,    45,    32,    33,    34,    -1,    -1,    -1,    -1,    -1,
      -1,    55,    42,    -1,    -1,    45,    -1,    -1,    -1,    63,
      64,    -1,    66,    -1,    -1,    55,    -1,    -1,    -1,    -1,
      -1,    75,    76,    63,    64,    -1,    66,    81,    82,    83,
      84,    85,    86,    87,    88,    75,    76,    -1,    -1,    -1,
      -1,    81,    82,    83,    84,    85,    86,    87,    88,    32,
      33,    34,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    42,
      -1,    -1,    45,    32,    33,    34,    -1,    -1,    -1,    -1,
      -1,    -1,    55,    42,    -1,    -1,    45,    -1,    -1,    -1,
      63,    64,    -1,    66,    -1,    -1,    55,    -1,    -1,    -1,
      -1,    -1,    75,    76,    63,    64,    -1,    66,    81,    82,
      83,    84,    85,    86,    87,    88,    75,    -1,    -1,    -1,
      -1,    -1,    81,    82,    83,    84,    85,    86,    87,    88,
      32,    33,    34,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      42,    -1,    -1,    45,    32,    33,    34,    -1,    -1,    -1,
      -1,    -1,    -1,    55,    42,    -1,    -1,    45,    -1,    -1,
      -1,    63,    64,    -1,    66,    -1,    -1,    55,    -1,    -1,
      -1,    -1,    -1,    75,    -1,    63,    64,    -1,    66,    81,
      82,    83,    84,    85,    86,    87,    88,    75,    -1,    -1,
      -1,    -1,    -1,    81,    82,    83,    84,    85,    86,    87,
      88
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    17,    18,    34,    75,    88,    90,    91,    92,    93,
      94,    96,    97,    98,   100,   101,   109,   112,   113,   114,
     125,   126,    79,   126,    16,    19,    99,   114,   115,   112,
     126,     0,    92,    69,   103,   104,   112,    98,   126,    79,
     126,    79,    96,   116,   117,   118,   130,    75,    77,   113,
     110,   111,   126,    79,    99,   114,    76,    69,    70,    62,
     116,   130,    98,    99,   102,   105,   106,    79,    21,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    42,    45,    55,    63,    64,    66,    67,    69,    75,
      80,    81,    82,    83,    84,    85,    86,    87,    94,    95,
      96,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   138,   140,   141,   142,   143,   144,   145,   146,
     147,   148,   149,   150,   151,   152,   153,   154,   156,   157,
      75,    77,   112,   123,   124,   130,    70,    76,   116,   119,
     126,    78,   126,   138,   139,   151,    70,    80,    62,   110,
     104,   112,    79,   120,   136,   130,   106,   106,    80,   105,
      71,   107,   108,   112,   102,    75,    75,   126,   127,    75,
      69,    69,    75,   139,    71,   126,    75,   151,   151,    75,
     151,    69,   135,   106,   122,   126,   135,    80,    94,   131,
      71,    80,   127,    69,    70,    54,    72,    53,    43,    44,
      42,    60,    61,    56,    57,    58,    59,    46,    47,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    48,
      49,    50,    51,    52,    62,   137,   150,    63,    64,    73,
      74,    75,    77,    76,   123,    78,   116,   139,    75,    77,
      68,   118,    76,    70,    76,    78,   111,   139,    80,   120,
     121,   139,    69,    70,    71,    80,   135,    69,   135,    25,
     135,   135,    71,   127,    69,   122,    69,    75,   123,    76,
      76,    80,   127,   136,   141,   135,   142,   143,   144,   145,
     146,   146,   147,   147,   147,   147,   148,   148,   149,   149,
     150,   150,   150,   136,   126,   126,    76,   136,   155,   135,
      76,    76,    78,    76,    78,   116,   139,   126,    70,    80,
     108,   139,    76,    69,   135,    69,    75,    76,    76,   127,
      76,   150,    71,    70,    76,    78,    76,    78,    80,   120,
     127,    76,   135,    69,    69,   135,   135,   127,   127,   138,
     136,    22,   127,    76,    76,   135,    76,   135,    69,    76,
     127,   127,   127,    76,   127,    76,    76,   135,    69,   127,
     127,   127,    76,   127
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    89,    90,    91,    91,    92,    92,    93,    93,    93,
      93,    94,    94,    95,    95,    96,    96,    97,    97,    98,
      98,    98,    98,    98,    98,    98,    98,    98,    98,    99,
      99,   100,   100,   100,   101,   101,   102,   102,   103,   103,
     104,   104,   105,   106,   106,   106,   106,   107,   107,   108,
     108,   108,   109,   109,   109,   110,   110,   111,   111,   112,
     112,   113,   113,   113,   113,   113,   113,   113,   114,   114,
     114,   114,   115,   115,   116,   116,   117,   117,   118,   118,
     118,   119,   119,   120,   120,   120,   121,   121,   122,   122,
     123,   124,   124,   124,   124,   124,   124,   124,   124,   124,
     125,   126,   127,   127,   127,   127,   127,   127,   128,   128,
     128,   129,   129,   130,   130,   130,   130,   131,   131,   132,
     132,   132,   133,   133,   133,   133,   133,   133,   133,   133,
     133,   133,   134,   134,   134,   134,   134,   135,   135,   136,
     136,   137,   137,   137,   137,   137,   137,   137,   137,   137,
     137,   137,   138,   138,   139,   140,   140,   141,   141,   142,
     142,   143,   143,   144,   144,   145,   145,   145,   146,   146,
     146,   146,   146,   147,   147,   147,   148,   148,   148,   149,
     149,   149,   149,   150,   150,   151,   151,   151,   151,   151,
     151,   152,   152,   152,   152,   152,   152,   153,   153,   153,
     153,   153,   153,   153,   153,   154,   154,   154,   154,   155,
     155,   156,   157,   157,   157,   157,   157,   157
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     2,     1,     1,     4,     3,     3,
       2,     3,     2,     1,     2,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     5,     4,     2,     1,     1,     1,     2,     1,     3,
       1,     3,     3,     2,     1,     2,     1,     1,     3,     1,
       3,     2,     5,     4,     2,     1,     3,     1,     3,     2,
       1,     1,     3,     4,     3,     4,     4,     3,     2,     1,
       3,     2,     1,     2,     1,     3,     1,     3,     2,     2,
       1,     1,     3,     1,     3,     4,     1,     3,     2,     1,
       1,     3,     4,     3,     3,     2,     4,     3,     3,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     3,     4,
       3,     2,     1,     4,     3,     3,     2,     1,     2,     5,
       7,     5,     5,     7,     9,     8,     8,     8,     7,     7,
       7,     6,     3,     2,     2,     3,     2,     1,     3,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     5,     1,     1,     3,     1,     3,     1,
       3,     1,     3,     1,     3,     1,     3,     3,     1,     3,
       3,     3,     3,     1,     3,     3,     1,     3,     3,     1,
       3,     3,     3,     1,     4,     1,     2,     2,     2,     2,
       4,     1,     1,     1,     1,     1,     1,     1,     4,     4,
       3,     3,     3,     2,     2,     1,     1,     1,     3,     1,
       3,     1,     1,     1,     1,     1,     1,     1
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
#line 114 "ecc.y"
                                               { (yyval.program) = new Program((yyvsp[0].declaration)); program = (yyval.program); }
#line 2018 "parser.cpp"
    break;

  case 3:
#line 117 "ecc.y"
                                                { (yyval.declaration) = (yyvsp[0].declaration); }
#line 2024 "parser.cpp"
    break;

  case 4:
#line 118 "ecc.y"
                                                             { (yyvsp[-1].declaration)->next = (yyvsp[0].declaration); (yyval.declaration) = (yyvsp[-1].declaration); }
#line 2030 "parser.cpp"
    break;

  case 5:
#line 121 "ecc.y"
                                                  { (yyval.declaration) = (yyvsp[0].functionDeclaration); }
#line 2036 "parser.cpp"
    break;

  case 6:
#line 122 "ecc.y"
                                   { (yyval.declaration) = (yyvsp[0].variableDeclaration); }
#line 2042 "parser.cpp"
    break;

  case 7:
#line 125 "ecc.y"
                                                                                  { (yyval.functionDeclaration) = new FunctionDeclaration((yyvsp[-3].type), (yyvsp[-2].expression), (yyvsp[-1].param), (yyvsp[0].compoundStatement)); }
#line 2048 "parser.cpp"
    break;

  case 8:
#line 126 "ecc.y"
                                                                                  { (yyval.functionDeclaration) = new FunctionDeclaration(nullptr, (yyvsp[-2].expression), (yyvsp[-1].param), (yyvsp[0].compoundStatement)); }
#line 2054 "parser.cpp"
    break;

  case 9:
#line 127 "ecc.y"
                                                                                  { (yyval.functionDeclaration) = new FunctionDeclaration((yyvsp[-2].type), (yyvsp[-1].expression), nullptr, (yyvsp[0].compoundStatement)); }
#line 2060 "parser.cpp"
    break;

  case 10:
#line 128 "ecc.y"
                                                                                  { (yyval.functionDeclaration) = new FunctionDeclaration(nullptr, (yyvsp[-1].expression), nullptr, (yyvsp[0].compoundStatement)); }
#line 2066 "parser.cpp"
    break;

  case 11:
#line 131 "ecc.y"
                                                                    { (yyval.variableDeclaration) = new VariableDeclaration((yyvsp[-2].type), (yyvsp[-1].ids)); }
#line 2072 "parser.cpp"
    break;

  case 13:
#line 135 "ecc.y"
                                   { (yyval.vars) = new vector<VariableDeclaration *>; (yyval.vars)->push_back((yyvsp[0].variableDeclaration)); }
#line 2078 "parser.cpp"
    break;

  case 14:
#line 136 "ecc.y"
                                             { (yyvsp[-1].vars)->push_back((yyvsp[0].variableDeclaration)); (yyval.vars) = (yyvsp[-1].vars); }
#line 2084 "parser.cpp"
    break;

  case 15:
#line 139 "ecc.y"
                                                    { (yyvsp[0].type)->isunsigned = (yyvsp[-1].flag); (yyval.type) = (yyvsp[0].type); }
#line 2090 "parser.cpp"
    break;

  case 16:
#line 140 "ecc.y"
                                        { (yyval.type) = (yyvsp[0].type); }
#line 2096 "parser.cpp"
    break;

  case 17:
#line 150 "ecc.y"
                                     { (yyval.flag) = false; }
#line 2102 "parser.cpp"
    break;

  case 18:
#line 151 "ecc.y"
                                       { (yyval.flag) = true; }
#line 2108 "parser.cpp"
    break;

  case 19:
#line 154 "ecc.y"
                                   { (yyval.type) = new CharType(); }
#line 2114 "parser.cpp"
    break;

  case 20:
#line 155 "ecc.y"
                                    { (yyval.type) = new ShortType(); }
#line 2120 "parser.cpp"
    break;

  case 21:
#line 156 "ecc.y"
                                  { (yyval.type) = new IntType(); }
#line 2126 "parser.cpp"
    break;

  case 22:
#line 157 "ecc.y"
                                   { (yyval.type) = new LongType(); }
#line 2132 "parser.cpp"
    break;

  case 23:
#line 158 "ecc.y"
                                    { (yyval.type) = new FloatType(); }
#line 2138 "parser.cpp"
    break;

  case 24:
#line 159 "ecc.y"
                                     { (yyval.type) = new DoubleType(); }
#line 2144 "parser.cpp"
    break;

  case 25:
#line 160 "ecc.y"
                                   { (yyval.type) = new VoidType(); }
#line 2150 "parser.cpp"
    break;

  case 38:
#line 183 "ecc.y"
                                              { (yyval.ids) = new vector<Identifier *>; (yyval.ids)->push_back((yyvsp[0].identifier)); }
#line 2156 "parser.cpp"
    break;

  case 39:
#line 184 "ecc.y"
                                                                         { (yyvsp[-2].ids)->push_back((yyvsp[0].identifier)); (yyval.ids) = (yyvsp[-2].ids); }
#line 2162 "parser.cpp"
    break;

  case 40:
#line 187 "ecc.y"
                                         { (yyval.identifier) = new Identifier((yyvsp[0].expression)); }
#line 2168 "parser.cpp"
    break;

  case 41:
#line 188 "ecc.y"
                                                            { (yyval.identifier) = new Identifier((yyvsp[-2].expression), (yyvsp[0].expression)); }
#line 2174 "parser.cpp"
    break;

  case 60:
#line 223 "ecc.y"
                                                { (yyval.expression) = (yyvsp[0].identifier); }
#line 2180 "parser.cpp"
    break;

  case 61:
#line 226 "ecc.y"
                                 { (yyval.identifier) = (yyvsp[0].identifier); }
#line 2186 "parser.cpp"
    break;

  case 74:
#line 245 "ecc.y"
                                         { (yyval.param) = (yyvsp[0].param); }
#line 2192 "parser.cpp"
    break;

  case 76:
#line 249 "ecc.y"
                                         { (yyval.param) = (yyvsp[0].param); }
#line 2198 "parser.cpp"
    break;

  case 77:
#line 250 "ecc.y"
                                                          { (yyvsp[-2].param)->next = (yyvsp[0].param); (yyval.param) = (yyvsp[-2].param); }
#line 2204 "parser.cpp"
    break;

  case 78:
#line 253 "ecc.y"
                                                    { (yyval.param) = new Parameter((yyvsp[-1].type), (yyvsp[0].expression)); }
#line 2210 "parser.cpp"
    break;

  case 80:
#line 255 "ecc.y"
                                         { (yyval.param) = new Parameter((yyvsp[0].type)); }
#line 2216 "parser.cpp"
    break;

  case 81:
#line 258 "ecc.y"
                                         { (yyval.ids) = new vector<Identifier *>; (yyval.ids)->push_back((yyvsp[0].identifier)); }
#line 2222 "parser.cpp"
    break;

  case 82:
#line 259 "ecc.y"
                                               { (yyvsp[-2].ids)->push_back((yyvsp[0].identifier)); (yyval.ids) = (yyvsp[-2].ids); }
#line 2228 "parser.cpp"
    break;

  case 83:
#line 262 "ecc.y"
                                             { (yyval.expression) = (yyvsp[0].expression); }
#line 2234 "parser.cpp"
    break;

  case 100:
#line 289 "ecc.y"
                                 { (yyval.identifier) = (yyvsp[0].identifier); }
#line 2240 "parser.cpp"
    break;

  case 101:
#line 292 "ecc.y"
                                         { (yyval.identifier) = new Identifier(new String(*yylval.stringValue)); }
#line 2246 "parser.cpp"
    break;

  case 102:
#line 295 "ecc.y"
                                           { (yyval.statement) = (yyvsp[0].statement); }
#line 2252 "parser.cpp"
    break;

  case 103:
#line 296 "ecc.y"
                                       { (yyval.statement) = (yyvsp[0].expressionStatement); }
#line 2258 "parser.cpp"
    break;

  case 104:
#line 297 "ecc.y"
                                            { (yyval.statement) = (yyvsp[0].compoundStatement); }
#line 2264 "parser.cpp"
    break;

  case 105:
#line 298 "ecc.y"
                                             { (yyval.statement) = (yyvsp[0].selectionStatement); }
#line 2270 "parser.cpp"
    break;

  case 106:
#line 299 "ecc.y"
                                             { (yyval.statement) = (yyvsp[0].iterationStatement); }
#line 2276 "parser.cpp"
    break;

  case 107:
#line 300 "ecc.y"
                                        { (yyval.statement) = (yyvsp[0].statement); }
#line 2282 "parser.cpp"
    break;

  case 111:
#line 308 "ecc.y"
                                            { (yyval.expressionStatement) = new ExpressionStatement((yyvsp[-1].expression)); }
#line 2288 "parser.cpp"
    break;

  case 112:
#line 309 "ecc.y"
                                    { (yyval.expressionStatement) = new ExpressionStatement(); }
#line 2294 "parser.cpp"
    break;

  case 113:
#line 312 "ecc.y"
                                                        { (yyval.compoundStatement) = new CompoundStatement((yyvsp[-2].vars), (yyvsp[-1].statement)); }
#line 2300 "parser.cpp"
    break;

  case 114:
#line 313 "ecc.y"
                                              { (yyval.compoundStatement) = new CompoundStatement(nullptr, (yyvsp[-1].statement)); }
#line 2306 "parser.cpp"
    break;

  case 115:
#line 314 "ecc.y"
                                              { (yyval.compoundStatement) = new CompoundStatement((yyvsp[-1].vars), nullptr); }
#line 2312 "parser.cpp"
    break;

  case 116:
#line 315 "ecc.y"
                                    { (yyval.compoundStatement) = new CompoundStatement(nullptr, nullptr); }
#line 2318 "parser.cpp"
    break;

  case 117:
#line 318 "ecc.y"
                                   { (yyval.statement) = (yyvsp[0].statement); }
#line 2324 "parser.cpp"
    break;

  case 118:
#line 319 "ecc.y"
                                             { (yyvsp[-1].statement)->next = (yyvsp[0].statement); (yyval.statement) = (yyvsp[-1].statement); }
#line 2330 "parser.cpp"
    break;

  case 119:
#line 322 "ecc.y"
                                                    { (yyval.selectionStatement) = new IfElseStatement((yyvsp[-2].expression), (yyvsp[0].statement)); }
#line 2336 "parser.cpp"
    break;

  case 120:
#line 323 "ecc.y"
                                                          { (yyvsp[-2].statement)->next = (yyvsp[0].statement); (yyval.selectionStatement) = new IfElseStatement((yyvsp[-4].expression), (yyvsp[-2].statement)); }
#line 2342 "parser.cpp"
    break;

  case 122:
#line 327 "ecc.y"
                                                       { (yyval.iterationStatement) = new WhileStatement((yyvsp[-2].expression), (yyvsp[0].statement)); }
#line 2348 "parser.cpp"
    break;

  case 123:
#line 328 "ecc.y"
                                                            { (yyval.iterationStatement) = new DoWhileStatement((yyvsp[-2].expression), (yyvsp[-5].statement)); }
#line 2354 "parser.cpp"
    break;

  case 124:
#line 329 "ecc.y"
                                                                     { (yyval.iterationStatement) = new ForStatement((yyvsp[-6].expression), (yyvsp[-4].expression), (yyvsp[-2].expression), (yyvsp[0].statement)); }
#line 2360 "parser.cpp"
    break;

  case 125:
#line 330 "ecc.y"
                                                                     { (yyval.iterationStatement) = new ForStatement((yyvsp[-5].expression), (yyvsp[-3].expression), nullptr, (yyvsp[0].statement)); }
#line 2366 "parser.cpp"
    break;

  case 126:
#line 331 "ecc.y"
                                                                     { (yyval.iterationStatement) = new ForStatement((yyvsp[-5].expression), nullptr, (yyvsp[-2].expression), (yyvsp[0].statement)); }
#line 2372 "parser.cpp"
    break;

  case 127:
#line 332 "ecc.y"
                                                                     { (yyval.iterationStatement) = new ForStatement(nullptr, (yyvsp[-4].expression), (yyvsp[-2].expression), (yyvsp[0].statement)); }
#line 2378 "parser.cpp"
    break;

  case 128:
#line 333 "ecc.y"
                                                                     { (yyval.iterationStatement) = new ForStatement((yyvsp[-4].expression), nullptr, nullptr, (yyvsp[0].statement)); }
#line 2384 "parser.cpp"
    break;

  case 129:
#line 334 "ecc.y"
                                                                     { (yyval.iterationStatement) = new ForStatement(nullptr, (yyvsp[-3].expression), nullptr, (yyvsp[0].statement)); }
#line 2390 "parser.cpp"
    break;

  case 130:
#line 335 "ecc.y"
                                                                     { (yyval.iterationStatement) = new ForStatement(nullptr, nullptr, (yyvsp[-2].expression), (yyvsp[0].statement)); }
#line 2396 "parser.cpp"
    break;

  case 131:
#line 336 "ecc.y"
                                                                     { (yyval.iterationStatement) = new ForStatement(nullptr, nullptr, nullptr, (yyvsp[0].statement)); }
#line 2402 "parser.cpp"
    break;

  case 135:
#line 342 "ecc.y"
                                               { (yyval.statement) = new ReturnStatement((yyvsp[-1].expression)); }
#line 2408 "parser.cpp"
    break;

  case 136:
#line 343 "ecc.y"
                                           { (yyval.statement) = new ReturnStatement(); }
#line 2414 "parser.cpp"
    break;

  case 137:
#line 346 "ecc.y"
                                                         { (yyval.expression) = (yyvsp[0].expression); }
#line 2420 "parser.cpp"
    break;

  case 138:
#line 347 "ecc.y"
                                                       { (yyval.expression) = new Expression((yyvsp[-2].expression), (yyvsp[0].expression), OP_COMMA); }
#line 2426 "parser.cpp"
    break;

  case 139:
#line 350 "ecc.y"
                                                  { (yyval.expression) = (yyvsp[0].expression); }
#line 2432 "parser.cpp"
    break;

  case 140:
#line 351 "ecc.y"
                                                                           { (yyval.expression) = new Expression((yyvsp[-2].expression), (yyvsp[0].expression), (yyvsp[-1].op)); }
#line 2438 "parser.cpp"
    break;

  case 141:
#line 354 "ecc.y"
                                         { (yyval.op) = OP_ASSIGN; }
#line 2444 "parser.cpp"
    break;

  case 142:
#line 355 "ecc.y"
                                        { (yyval.op) = OP_MULASSIGN; }
#line 2450 "parser.cpp"
    break;

  case 143:
#line 356 "ecc.y"
                                        { (yyval.op) = OP_DIVASSIGN; }
#line 2456 "parser.cpp"
    break;

  case 144:
#line 357 "ecc.y"
                                        { (yyval.op) = OP_MODASSIGN; }
#line 2462 "parser.cpp"
    break;

  case 145:
#line 358 "ecc.y"
                                        { (yyval.op) = OP_ADDASSIGN; }
#line 2468 "parser.cpp"
    break;

  case 146:
#line 359 "ecc.y"
                                        { (yyval.op) = OP_SUBASSIGN; }
#line 2474 "parser.cpp"
    break;

  case 147:
#line 360 "ecc.y"
                                       { (yyval.op) = OP_SLASSIGN; }
#line 2480 "parser.cpp"
    break;

  case 148:
#line 361 "ecc.y"
                                       { (yyval.op) = OP_SRASSIGN; }
#line 2486 "parser.cpp"
    break;

  case 149:
#line 362 "ecc.y"
                                        { (yyval.op) = OP_ANDASSIGN; }
#line 2492 "parser.cpp"
    break;

  case 150:
#line 363 "ecc.y"
                                        { (yyval.op) = OP_XORASSIGN; }
#line 2498 "parser.cpp"
    break;

  case 151:
#line 364 "ecc.y"
                                       { (yyval.op) = OP_ORASSIGN; }
#line 2504 "parser.cpp"
    break;

  case 152:
#line 367 "ecc.y"
                                             { (yyval.expression) = (yyvsp[0].expression); }
#line 2510 "parser.cpp"
    break;

  case 153:
#line 368 "ecc.y"
                                                                                { (yyval.expression) = new Expression((yyvsp[-2].expression), (yyvsp[0].expression), (yyvsp[-4].expression), OP_IFELSE); }
#line 2516 "parser.cpp"
    break;

  case 154:
#line 371 "ecc.y"
                                                  { (yyval.expression) = (yyvsp[0].expression); }
#line 2522 "parser.cpp"
    break;

  case 155:
#line 374 "ecc.y"
                                                  { (yyval.expression) = (yyvsp[0].expression); }
#line 2528 "parser.cpp"
    break;

  case 156:
#line 375 "ecc.y"
                                                                  { (yyval.expression) = new Expression((yyvsp[-2].expression), (yyvsp[0].expression), OP_OROR); }
#line 2534 "parser.cpp"
    break;

  case 157:
#line 378 "ecc.y"
                                                   { (yyval.expression) = (yyvsp[0].expression); }
#line 2540 "parser.cpp"
    break;

  case 158:
#line 379 "ecc.y"
                                                                      { (yyval.expression) = new Expression((yyvsp[-2].expression), (yyvsp[0].expression), OP_ANDAND); }
#line 2546 "parser.cpp"
    break;

  case 159:
#line 382 "ecc.y"
                                                   { (yyval.expression) = (yyvsp[0].expression); }
#line 2552 "parser.cpp"
    break;

  case 160:
#line 383 "ecc.y"
                                                                   { (yyval.expression) = new Expression((yyvsp[-2].expression), (yyvsp[0].expression), OP_OR); }
#line 2558 "parser.cpp"
    break;

  case 161:
#line 386 "ecc.y"
                                          { (yyval.expression) = (yyvsp[0].expression); }
#line 2564 "parser.cpp"
    break;

  case 162:
#line 387 "ecc.y"
                                                           { (yyval.expression) = new Expression((yyvsp[-2].expression), (yyvsp[0].expression), OP_XOR); }
#line 2570 "parser.cpp"
    break;

  case 163:
#line 390 "ecc.y"
                                                   { (yyval.expression) = (yyvsp[0].expression); }
#line 2576 "parser.cpp"
    break;

  case 164:
#line 391 "ecc.y"
                                                       { (yyval.expression) = new Expression((yyvsp[-2].expression), (yyvsp[0].expression), OP_AND); }
#line 2582 "parser.cpp"
    break;

  case 165:
#line 394 "ecc.y"
                                                 { (yyval.expression) = (yyvsp[0].expression);}
#line 2588 "parser.cpp"
    break;

  case 166:
#line 395 "ecc.y"
                                                             { (yyval.expression) = new Expression((yyvsp[-2].expression), (yyvsp[0].expression), OP_EQ); }
#line 2594 "parser.cpp"
    break;

  case 167:
#line 396 "ecc.y"
                                                              { (yyval.expression) = new Expression((yyvsp[-2].expression), (yyvsp[0].expression), OP_NEQ); }
#line 2600 "parser.cpp"
    break;

  case 168:
#line 399 "ecc.y"
                                                   { (yyval.expression) = (yyvsp[0].expression); }
#line 2606 "parser.cpp"
    break;

  case 169:
#line 400 "ecc.y"
                                                                 { (yyval.expression) = new Expression((yyvsp[-2].expression), (yyvsp[0].expression), OP_LT); }
#line 2612 "parser.cpp"
    break;

  case 170:
#line 401 "ecc.y"
                                                                 { (yyval.expression) = new Expression((yyvsp[-2].expression), (yyvsp[0].expression), OP_GT); }
#line 2618 "parser.cpp"
    break;

  case 171:
#line 402 "ecc.y"
                                                                  { (yyval.expression) = new Expression((yyvsp[-2].expression), (yyvsp[0].expression), OP_LEQ); }
#line 2624 "parser.cpp"
    break;

  case 172:
#line 403 "ecc.y"
                                                                  { (yyval.expression) = new Expression((yyvsp[-2].expression), (yyvsp[0].expression), OP_GEQ); }
#line 2630 "parser.cpp"
    break;

  case 173:
#line 406 "ecc.y"
                                               { (yyval.expression) = (yyvsp[0].expression); }
#line 2636 "parser.cpp"
    break;

  case 174:
#line 407 "ecc.y"
                                                               { (yyval.expression) = new Expression((yyvsp[-2].expression), (yyvsp[0].expression), OP_SL); }
#line 2642 "parser.cpp"
    break;

  case 175:
#line 408 "ecc.y"
                                                               { (yyval.expression) = new Expression((yyvsp[-2].expression), (yyvsp[0].expression), OP_SR); }
#line 2648 "parser.cpp"
    break;

  case 176:
#line 411 "ecc.y"
                                           { (yyval.expression) = (yyvsp[0].expression); }
#line 2654 "parser.cpp"
    break;

  case 177:
#line 412 "ecc.y"
                                                        { (yyval.expression) = new Expression((yyvsp[-2].expression), (yyvsp[0].expression), OP_ADD); }
#line 2660 "parser.cpp"
    break;

  case 178:
#line 413 "ecc.y"
                                                        { (yyval.expression) = new Expression((yyvsp[-2].expression), (yyvsp[0].expression), OP_SUB); }
#line 2666 "parser.cpp"
    break;

  case 179:
#line 416 "ecc.y"
                                               { (yyval.expression) = (yyvsp[0].expression); }
#line 2672 "parser.cpp"
    break;

  case 180:
#line 417 "ecc.y"
                                                    { (yyval.expression) = new Expression((yyvsp[-2].expression), (yyvsp[0].expression), OP_MUL); }
#line 2678 "parser.cpp"
    break;

  case 181:
#line 418 "ecc.y"
                                                    { (yyval.expression) = new Expression((yyvsp[-2].expression), (yyvsp[0].expression), OP_DIV); }
#line 2684 "parser.cpp"
    break;

  case 182:
#line 419 "ecc.y"
                                                    { (yyval.expression) = new Expression((yyvsp[-2].expression), (yyvsp[0].expression), OP_MOD); }
#line 2690 "parser.cpp"
    break;

  case 183:
#line 422 "ecc.y"
                                                { (yyval.expression) = (yyvsp[0].expression); }
#line 2696 "parser.cpp"
    break;

  case 185:
#line 426 "ecc.y"
                                                   { (yyval.expression) = (yyvsp[0].expression); }
#line 2702 "parser.cpp"
    break;

  case 186:
#line 427 "ecc.y"
                                            { (yyval.expression) = new Expression((yyvsp[0].expression), OP_INC_FRONT); }
#line 2708 "parser.cpp"
    break;

  case 187:
#line 428 "ecc.y"
                                            { (yyval.expression) = new Expression((yyvsp[0].expression), OP_DEC_FRONT); }
#line 2714 "parser.cpp"
    break;

  case 188:
#line 429 "ecc.y"
                                                      { (yyval.expression) = new Expression((yyvsp[0].expression), (yyvsp[-1].op)); }
#line 2720 "parser.cpp"
    break;

  case 191:
#line 434 "ecc.y"
                                  { (yyval.op) = OP_AND; }
#line 2726 "parser.cpp"
    break;

  case 192:
#line 435 "ecc.y"
                                  { (yyval.op) = OP_POINTER; }
#line 2732 "parser.cpp"
    break;

  case 193:
#line 436 "ecc.y"
                                  { (yyval.op) = OP_POSITIVE; }
#line 2738 "parser.cpp"
    break;

  case 194:
#line 437 "ecc.y"
                                  { (yyval.op) = OP_NEGTIVE; }
#line 2744 "parser.cpp"
    break;

  case 195:
#line 438 "ecc.y"
                                  { (yyval.op) = OP_NOT; }
#line 2750 "parser.cpp"
    break;

  case 196:
#line 439 "ecc.y"
                                     { (yyval.op) = OP_NOTNOT; }
#line 2756 "parser.cpp"
    break;

  case 197:
#line 442 "ecc.y"
                                                  { (yyval.expression) = (yyvsp[0].expression); }
#line 2762 "parser.cpp"
    break;

  case 198:
#line 443 "ecc.y"
                                                    { (yyval.expression) = new Identifier((yyvsp[-3].expression), (yyvsp[-1].expression)); }
#line 2768 "parser.cpp"
    break;

  case 199:
#line 444 "ecc.y"
                                                                  { (yyval.expression) = new FunctionCall((yyvsp[-3].expression), (yyvsp[-1].exprs)); }
#line 2774 "parser.cpp"
    break;

  case 200:
#line 445 "ecc.y"
                                                { (yyval.expression) = new FunctionCall((yyvsp[-2].expression), nullptr); }
#line 2780 "parser.cpp"
    break;

  case 203:
#line 448 "ecc.y"
                                              { (yyval.expression) = new Expression((yyvsp[-1].expression), OP_INC_REAR); }
#line 2786 "parser.cpp"
    break;

  case 204:
#line 449 "ecc.y"
                                              { (yyval.expression) = new Expression((yyvsp[-1].expression), OP_DEC_REAR); }
#line 2792 "parser.cpp"
    break;

  case 205:
#line 452 "ecc.y"
                                         { (yyval.expression) = (yyvsp[0].identifier); }
#line 2798 "parser.cpp"
    break;

  case 206:
#line 453 "ecc.y"
                                    { (yyval.expression) = (yyvsp[0].number); }
#line 2804 "parser.cpp"
    break;

  case 207:
#line 454 "ecc.y"
                                     { (yyval.expression) = new String(*yylval.stringValue); }
#line 2810 "parser.cpp"
    break;

  case 208:
#line 455 "ecc.y"
                                        { (yyval.expression) = (yyvsp[-1].expression); }
#line 2816 "parser.cpp"
    break;

  case 209:
#line 458 "ecc.y"
                                                 { (yyval.exprs) = new vector<Expression *>; (yyval.exprs)->push_back((yyvsp[0].expression)); }
#line 2822 "parser.cpp"
    break;

  case 210:
#line 459 "ecc.y"
                                                                     { (yyvsp[-2].exprs)->push_back((yyvsp[0].expression)); (yyval.exprs) = (yyvsp[-2].exprs); }
#line 2828 "parser.cpp"
    break;

  case 211:
#line 468 "ecc.y"
                                     { (yyval.number) = (yyvsp[0].number); }
#line 2834 "parser.cpp"
    break;

  case 212:
#line 471 "ecc.y"
                                      { (yyval.number) = new Number((yyvsp[0].num), new CharType(), VAL_CHAR); }
#line 2840 "parser.cpp"
    break;

  case 213:
#line 472 "ecc.y"
                                       { (yyval.number) = new Number((yyvsp[0].num), new ShortType(), VAL_SHORT); }
#line 2846 "parser.cpp"
    break;

  case 214:
#line 473 "ecc.y"
                                     { (yyval.number) = new Number((yyvsp[0].num), new IntType(), VAL_INT); }
#line 2852 "parser.cpp"
    break;

  case 215:
#line 474 "ecc.y"
                                      { (yyval.number) = new Number((yyvsp[0].num), new LongType(), VAL_LONG); }
#line 2858 "parser.cpp"
    break;

  case 216:
#line 475 "ecc.y"
                                       { (yyval.number) = new Number((yyvsp[0].num), new FloatType(), VAL_FLOAT); }
#line 2864 "parser.cpp"
    break;

  case 217:
#line 476 "ecc.y"
                                        { (yyval.number) = new Number((yyvsp[0].num), new DoubleType(), VAL_DOUBLE); }
#line 2870 "parser.cpp"
    break;


#line 2874 "parser.cpp"

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
#line 479 "ecc.y"


void yyerror(string s)
{
    cerr << "\033[1;31m"
         << "error: "
         << "\033[0m" << s << " in Line " << yylineno << ": " << yytext << endl;
    exit(1);
}

void yywarning(string s, string addition)
{
    cerr << "\033[1;35m"
         << "warning: "
         << "\033[0m" << s << " in Line " << yylineno << ": " << yytext << ". " << addition << endl;
}
