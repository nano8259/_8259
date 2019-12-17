// A Bison parser, made by GNU Bison 3.4.2.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2019 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.

// Undocumented macros, especially those whose name start with YY_,
// are private implementation details.  Do not rely on them.

// //                    "%code top" blocks.
#line 62 "parser.y"

    #include <iostream>
    #include "scanner.h"
    #include "parser.hpp"
    #include "interpreter.h"
    #include "location.hh"
    
    // yylex() arguments are defined in parser.y
    static EzAquarii::Parser::symbol_type yylex(EzAquarii::Scanner &scanner, EzAquarii::Interpreter &driver) {
        return scanner.get_next_token();
    }
    
    // you can accomplish the same thing by inlining the code using preprocessor
    // x and y are same as in above static function
    // #define yylex(x, y) scanner.get_next_token()
    
    using namespace EzAquarii;

#line 57 "parser.cpp"




#include "parser.hpp"




#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

// Whether we are compiled with exception support.
#ifndef YY_EXCEPTIONS
# if defined __GNUC__ && !defined __EXCEPTIONS
#  define YY_EXCEPTIONS 0
# else
#  define YY_EXCEPTIONS 1
# endif
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (false)
# endif


// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << '\n';                       \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yystack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 37 "parser.y"
namespace  EzAquarii  {
#line 156 "parser.cpp"


  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
   Parser ::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr;
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
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }


  /// Build a parser object.
   Parser :: Parser  (EzAquarii::Scanner &scanner_yyarg, EzAquarii::Interpreter &driver_yyarg)
    :
#if YYDEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      scanner (scanner_yyarg),
      driver (driver_yyarg)
  {}

   Parser ::~ Parser  ()
  {}

   Parser ::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------------.
  | Symbol types.  |
  `---------------*/



  // by_state.
   Parser ::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

   Parser ::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
   Parser ::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
   Parser ::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

   Parser ::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

   Parser ::symbol_number_type
   Parser ::by_state::type_get () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[state];
  }

   Parser ::stack_symbol_type::stack_symbol_type ()
  {}

   Parser ::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state), YY_MOVE (that.location))
  {
    switch (that.type_get ())
    {
      case 54: // program
      case 55: // translation_unit
      case 56: // external_declaration
      case 57: // declaration
      case 58: // declaration_list
      case 59: // init_declarator_list
      case 60: // init_declarator
      case 61: // initializer
      case 62: // initializer_list
      case 63: // declarator
      case 64: // function_definition
      case 65: // declaration_specifiers
      case 66: // type_specifier
      case 67: // direct_declarator
      case 68: // parameter_type_list
      case 69: // parameter_list
      case 70: // parameter_declaration
      case 71: // identifier_list
      case 72: // compound_statement
      case 73: // statement_list
      case 74: // constant
      case 75: // primary_expression
      case 76: // postfix_expression
      case 77: // argument_expression_list
      case 78: // unary_expression
      case 79: // unary_operator
      case 80: // cast_expression
      case 81: // multiplicative_expression
      case 82: // additive_expression
      case 83: // shift_expression
      case 84: // relational_expression
      case 85: // equality_expression
      case 86: // and_expression
      case 87: // exclusive_or_expression
      case 88: // inclusive_or_expression
      case 89: // logical_and_expression
      case 90: // logical_or_expression
      case 91: // conditional_expression
      case 92: // assignment_expression
      case 93: // assignment_operator
      case 94: // expression
      case 95: // constant_expression
      case 96: // labeled_statement
      case 97: // selection_statement
      case 98: // iteration_statement
      case 99: // jump_statement
      case 100: // expression_statement
      case 101: // statement
        value.YY_MOVE_OR_COPY< EzAquarii::ASTNode > (YY_MOVE (that.value));
        break;

      case 3: // ID
      case 4: // INT_VALUE
      case 5: // FLOAT_VALUE
        value.YY_MOVE_OR_COPY< std::string > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
  }

   Parser ::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s, YY_MOVE (that.location))
  {
    switch (that.type_get ())
    {
      case 54: // program
      case 55: // translation_unit
      case 56: // external_declaration
      case 57: // declaration
      case 58: // declaration_list
      case 59: // init_declarator_list
      case 60: // init_declarator
      case 61: // initializer
      case 62: // initializer_list
      case 63: // declarator
      case 64: // function_definition
      case 65: // declaration_specifiers
      case 66: // type_specifier
      case 67: // direct_declarator
      case 68: // parameter_type_list
      case 69: // parameter_list
      case 70: // parameter_declaration
      case 71: // identifier_list
      case 72: // compound_statement
      case 73: // statement_list
      case 74: // constant
      case 75: // primary_expression
      case 76: // postfix_expression
      case 77: // argument_expression_list
      case 78: // unary_expression
      case 79: // unary_operator
      case 80: // cast_expression
      case 81: // multiplicative_expression
      case 82: // additive_expression
      case 83: // shift_expression
      case 84: // relational_expression
      case 85: // equality_expression
      case 86: // and_expression
      case 87: // exclusive_or_expression
      case 88: // inclusive_or_expression
      case 89: // logical_and_expression
      case 90: // logical_or_expression
      case 91: // conditional_expression
      case 92: // assignment_expression
      case 93: // assignment_operator
      case 94: // expression
      case 95: // constant_expression
      case 96: // labeled_statement
      case 97: // selection_statement
      case 98: // iteration_statement
      case 99: // jump_statement
      case 100: // expression_statement
      case 101: // statement
        value.move< EzAquarii::ASTNode > (YY_MOVE (that.value));
        break;

      case 3: // ID
      case 4: // INT_VALUE
      case 5: // FLOAT_VALUE
        value.move< std::string > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

    // that is emptied.
    that.type = empty_symbol;
  }

#if YY_CPLUSPLUS < 201103L
   Parser ::stack_symbol_type&
   Parser ::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    switch (that.type_get ())
    {
      case 54: // program
      case 55: // translation_unit
      case 56: // external_declaration
      case 57: // declaration
      case 58: // declaration_list
      case 59: // init_declarator_list
      case 60: // init_declarator
      case 61: // initializer
      case 62: // initializer_list
      case 63: // declarator
      case 64: // function_definition
      case 65: // declaration_specifiers
      case 66: // type_specifier
      case 67: // direct_declarator
      case 68: // parameter_type_list
      case 69: // parameter_list
      case 70: // parameter_declaration
      case 71: // identifier_list
      case 72: // compound_statement
      case 73: // statement_list
      case 74: // constant
      case 75: // primary_expression
      case 76: // postfix_expression
      case 77: // argument_expression_list
      case 78: // unary_expression
      case 79: // unary_operator
      case 80: // cast_expression
      case 81: // multiplicative_expression
      case 82: // additive_expression
      case 83: // shift_expression
      case 84: // relational_expression
      case 85: // equality_expression
      case 86: // and_expression
      case 87: // exclusive_or_expression
      case 88: // inclusive_or_expression
      case 89: // logical_and_expression
      case 90: // logical_or_expression
      case 91: // conditional_expression
      case 92: // assignment_expression
      case 93: // assignment_operator
      case 94: // expression
      case 95: // constant_expression
      case 96: // labeled_statement
      case 97: // selection_statement
      case 98: // iteration_statement
      case 99: // jump_statement
      case 100: // expression_statement
      case 101: // statement
        value.move< EzAquarii::ASTNode > (that.value);
        break;

      case 3: // ID
      case 4: // INT_VALUE
      case 5: // FLOAT_VALUE
        value.move< std::string > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    // that is emptied.
    that.state = empty_state;
    return *this;
  }
#endif

  template <typename Base>
  void
   Parser ::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
   Parser ::yy_print_ (std::ostream& yyo,
                                     const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    symbol_number_type yytype = yysym.type_get ();
#if defined __GNUC__ && ! defined __clang__ && ! defined __ICC && __GNUC__ * 100 + __GNUC_MINOR__ <= 408
    // Avoid a (spurious) G++ 4.8 warning about "array subscript is
    // below array bounds".
    if (yysym.empty ())
      std::abort ();
#endif
    yyo << (yytype < yyntokens_ ? "token" : "nterm")
        << ' ' << yytname_[yytype] << " ("
        << yysym.location << ": ";
    YYUSE (yytype);
    yyo << ')';
  }
#endif

  void
   Parser ::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
   Parser ::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
   Parser ::yypop_ (int n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
   Parser ::debug_stream () const
  {
    return *yycdebug_;
  }

  void
   Parser ::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


   Parser ::debug_level_type
   Parser ::debug_level () const
  {
    return yydebug_;
  }

  void
   Parser ::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

   Parser ::state_type
   Parser ::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  bool
   Parser ::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  bool
   Parser ::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
   Parser ::operator() ()
  {
    return parse ();
  }

  int
   Parser ::parse ()
  {
    // State.
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The locations where the error started and ended.
    stack_symbol_type yyerror_range[3];

    /// The return value of parse ().
    int yyresult;

#if YY_EXCEPTIONS
    try
#endif // YY_EXCEPTIONS
      {
    YYCDEBUG << "Starting parse\n";


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, YY_MOVE (yyla));

  /*-----------------------------------------------.
  | yynewstate -- push a new symbol on the stack.  |
  `-----------------------------------------------*/
  yynewstate:
    YYCDEBUG << "Entering state " << yystack_[0].state << '\n';

    // Accept?
    if (yystack_[0].state == yyfinal_)
      YYACCEPT;

    goto yybackup;


  /*-----------.
  | yybackup.  |
  `-----------*/
  yybackup:
    // Try to take a decision without lookahead.
    yyn = yypact_[yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token: ";
#if YY_EXCEPTIONS
        try
#endif // YY_EXCEPTIONS
          {
            symbol_type yylookahead (yylex (scanner, driver));
            yyla.move (yylookahead);
          }
#if YY_EXCEPTIONS
        catch (const syntax_error& yyexc)
          {
            YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
            error (yyexc);
            goto yyerrlab1;
          }
#endif // YY_EXCEPTIONS
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.type_get ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.type_get ())
      goto yydefault;

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", yyn, YY_MOVE (yyla));
    goto yynewstate;


  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;


  /*-----------------------------.
  | yyreduce -- do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_ (yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
      switch (yyr1_[yyn])
    {
      case 54: // program
      case 55: // translation_unit
      case 56: // external_declaration
      case 57: // declaration
      case 58: // declaration_list
      case 59: // init_declarator_list
      case 60: // init_declarator
      case 61: // initializer
      case 62: // initializer_list
      case 63: // declarator
      case 64: // function_definition
      case 65: // declaration_specifiers
      case 66: // type_specifier
      case 67: // direct_declarator
      case 68: // parameter_type_list
      case 69: // parameter_list
      case 70: // parameter_declaration
      case 71: // identifier_list
      case 72: // compound_statement
      case 73: // statement_list
      case 74: // constant
      case 75: // primary_expression
      case 76: // postfix_expression
      case 77: // argument_expression_list
      case 78: // unary_expression
      case 79: // unary_operator
      case 80: // cast_expression
      case 81: // multiplicative_expression
      case 82: // additive_expression
      case 83: // shift_expression
      case 84: // relational_expression
      case 85: // equality_expression
      case 86: // and_expression
      case 87: // exclusive_or_expression
      case 88: // inclusive_or_expression
      case 89: // logical_and_expression
      case 90: // logical_or_expression
      case 91: // conditional_expression
      case 92: // assignment_expression
      case 93: // assignment_operator
      case 94: // expression
      case 95: // constant_expression
      case 96: // labeled_statement
      case 97: // selection_statement
      case 98: // iteration_statement
      case 99: // jump_statement
      case 100: // expression_statement
      case 101: // statement
        yylhs.value.emplace< EzAquarii::ASTNode > ();
        break;

      case 3: // ID
      case 4: // INT_VALUE
      case 5: // FLOAT_VALUE
        yylhs.value.emplace< std::string > ();
        break;

      default:
        break;
    }


      // Default location.
      {
        stack_type::slice range (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, range, yylen);
        yyerror_range[1].location = yylhs.location;
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
#if YY_EXCEPTIONS
      try
#endif // YY_EXCEPTIONS
        {
          switch (yyn)
            {
  case 2:
#line 119 "parser.y"
    {yylhs.value.as < EzAquarii::ASTNode > () = ASTNode("program"); yylhs.value.as < EzAquarii::ASTNode > ().nodes = yystack_[0].value.as < EzAquarii::ASTNode > ().nodes; yylhs.value.as < EzAquarii::ASTNode > ().display();
        cout << "there are totally " <<driver.location() << "chars in this program" << endl;
        passRoot(yylhs.value.as < EzAquarii::ASTNode > ());}
#line 798 "parser.cpp"
    break;

  case 3:
#line 126 "parser.y"
    {yylhs.value.as < EzAquarii::ASTNode > () = ASTNode("translation_unit"); yylhs.value.as < EzAquarii::ASTNode > ().addNode(yystack_[0].value.as < EzAquarii::ASTNode > ());}
#line 804 "parser.cpp"
    break;

  case 4:
#line 128 "parser.y"
    {yylhs.value.as < EzAquarii::ASTNode > () = yystack_[1].value.as < EzAquarii::ASTNode > (); yylhs.value.as < EzAquarii::ASTNode > ().addNode(yystack_[0].value.as < EzAquarii::ASTNode > ());}
#line 810 "parser.cpp"
    break;

  case 5:
#line 133 "parser.y"
    {yylhs.value.as < EzAquarii::ASTNode > () = ASTNode("external_declaration"); yylhs.value.as < EzAquarii::ASTNode > ().addNode(yystack_[0].value.as < EzAquarii::ASTNode > ());}
#line 816 "parser.cpp"
    break;

  case 6:
#line 135 "parser.y"
    {yylhs.value.as < EzAquarii::ASTNode > () = ASTNode("external_declaration"); yylhs.value.as < EzAquarii::ASTNode > ().addNode(yystack_[0].value.as < EzAquarii::ASTNode > ());}
#line 822 "parser.cpp"
    break;

  case 7:
#line 140 "parser.y"
    {yylhs.value.as < EzAquarii::ASTNode > () = ASTNode("declaration"); yylhs.value.as < EzAquarii::ASTNode > ().addNode(yystack_[1].value.as < EzAquarii::ASTNode > ())/*.addNode(ASTNode("SEMMI", ";"))*/;}
#line 828 "parser.cpp"
    break;

  case 8:
#line 142 "parser.y"
    {yylhs.value.as < EzAquarii::ASTNode > () = ASTNode("declaration"); yylhs.value.as < EzAquarii::ASTNode > ().addNode(yystack_[2].value.as < EzAquarii::ASTNode > ()).addNode(yystack_[1].value.as < EzAquarii::ASTNode > ())/*.addNode(ASTNode("SEMMI", ";"))*/;}
#line 834 "parser.cpp"
    break;

  case 9:
#line 147 "parser.y"
    {yylhs.value.as < EzAquarii::ASTNode > () = ASTNode("declaration_list"); yylhs.value.as < EzAquarii::ASTNode > ().addNode(yystack_[0].value.as < EzAquarii::ASTNode > ());}
#line 840 "parser.cpp"
    break;

  case 10:
#line 149 "parser.y"
    {yylhs.value.as < EzAquarii::ASTNode > () = yystack_[1].value.as < EzAquarii::ASTNode > (); yylhs.value.as < EzAquarii::ASTNode > ().addNode(yystack_[0].value.as < EzAquarii::ASTNode > ());}
#line 846 "parser.cpp"
    break;

  case 11:
#line 153 "parser.y"
    {yylhs.value.as < EzAquarii::ASTNode > () = ASTNode("init_declarator_list"); yylhs.value.as < EzAquarii::ASTNode > ().addNode(yystack_[0].value.as < EzAquarii::ASTNode > ());}
#line 852 "parser.cpp"
    break;

  case 12:
#line 155 "parser.y"
    {yylhs.value.as < EzAquarii::ASTNode > () = yystack_[2].value.as < EzAquarii::ASTNode > (); yylhs.value.as < EzAquarii::ASTNode > ()/*.addNode(ASTNode("COMMA", ","))*/.addNode(yystack_[0].value.as < EzAquarii::ASTNode > ());}
#line 858 "parser.cpp"
    break;

  case 13:
#line 159 "parser.y"
    {yylhs.value.as < EzAquarii::ASTNode > () = yystack_[0].value.as < EzAquarii::ASTNode > ();}
#line 864 "parser.cpp"
    break;

  case 14:
#line 161 "parser.y"
    {yylhs.value.as < EzAquarii::ASTNode > () = yystack_[2].value.as < EzAquarii::ASTNode > (); yylhs.value.as < EzAquarii::ASTNode > ().addNode(ASTNode("ASSIGN", "=")).addNode(yystack_[0].value.as < EzAquarii::ASTNode > ());}
#line 870 "parser.cpp"
    break;

  case 15:
#line 165 "parser.y"
    {yylhs.value.as < EzAquarii::ASTNode > () = ASTNode("initializer"); yylhs.value.as < EzAquarii::ASTNode > ().nodes = yystack_[0].value.as < EzAquarii::ASTNode > ().nodes;}
#line 876 "parser.cpp"
    break;

  case 16:
#line 167 "parser.y"
    {yylhs.value.as < EzAquarii::ASTNode > () = ASTNode("initializer"); yylhs.value.as < EzAquarii::ASTNode > ().addNode(ASTNode("LC", "{")).addNode(yystack_[1].value.as < EzAquarii::ASTNode > ()).addNode(ASTNode("RC", "}"));}
#line 882 "parser.cpp"
    break;

  case 17:
#line 169 "parser.y"
    {yylhs.value.as < EzAquarii::ASTNode > () = ASTNode("initializer"); yylhs.value.as < EzAquarii::ASTNode > ().addNode(ASTNode("LC", "{")).addNode(yystack_[2].value.as < EzAquarii::ASTNode > ()).addNode(ASTNode("RC", "}"));}
#line 888 "parser.cpp"
    break;

  case 18:
#line 173 "parser.y"
    {yylhs.value.as < EzAquarii::ASTNode > () = ASTNode("initializer_list"); yylhs.value.as < EzAquarii::ASTNode > ().addNode(yystack_[0].value.as < EzAquarii::ASTNode > ());}
#line 894 "parser.cpp"
    break;

  case 19:
#line 175 "parser.y"
    {yylhs.value.as < EzAquarii::ASTNode > () = yystack_[2].value.as < EzAquarii::ASTNode > (); yylhs.value.as < EzAquarii::ASTNode > ().addNode(yystack_[0].value.as < EzAquarii::ASTNode > ());}
#line 900 "parser.cpp"
    break;

  case 20:
#line 179 "parser.y"
    {yylhs.value.as < EzAquarii::ASTNode > () = ASTNode("declarator", yystack_[0].value.as < EzAquarii::ASTNode > ().value); /*$$.addNode($1);*/ yylhs.value.as < EzAquarii::ASTNode > ().nodes = yystack_[0].value.as < EzAquarii::ASTNode > ().nodes;}
#line 906 "parser.cpp"
    break;

  case 21:
#line 184 "parser.y"
    {yylhs.value.as < EzAquarii::ASTNode > () = ASTNode("function_definition"); yylhs.value.as < EzAquarii::ASTNode > ().addNode(yystack_[3].value.as < EzAquarii::ASTNode > ()).addNode(yystack_[2].value.as < EzAquarii::ASTNode > ()).addNode(yystack_[1].value.as < EzAquarii::ASTNode > ()).addNode(yystack_[0].value.as < EzAquarii::ASTNode > ());}
#line 912 "parser.cpp"
    break;

  case 22:
#line 186 "parser.y"
    {yylhs.value.as < EzAquarii::ASTNode > () = ASTNode("function_definition"); yylhs.value.as < EzAquarii::ASTNode > ().addNode(yystack_[2].value.as < EzAquarii::ASTNode > ()).addNode(yystack_[1].value.as < EzAquarii::ASTNode > ()).addNode(yystack_[0].value.as < EzAquarii::ASTNode > ());}
#line 918 "parser.cpp"
    break;

  case 23:
#line 190 "parser.y"
    {yylhs.value.as < EzAquarii::ASTNode > () = yystack_[0].value.as < EzAquarii::ASTNode > ();}
#line 924 "parser.cpp"
    break;

  case 24:
#line 194 "parser.y"
    {yylhs.value.as < EzAquarii::ASTNode > () = ASTNode("type_specifier"); yylhs.value.as < EzAquarii::ASTNode > ().addNode(ASTNode("INT", "int"));}
#line 930 "parser.cpp"
    break;

  case 25:
#line 195 "parser.y"
    {yylhs.value.as < EzAquarii::ASTNode > () = ASTNode("type_specifier"); yylhs.value.as < EzAquarii::ASTNode > ().addNode(ASTNode("FLOAT", "float"));}
#line 936 "parser.cpp"
    break;

  case 26:
#line 196 "parser.y"
    {yylhs.value.as < EzAquarii::ASTNode > () = ASTNode("type_specifier"); yylhs.value.as < EzAquarii::ASTNode > ().addNode(ASTNode("CHAR", "char"));}
#line 942 "parser.cpp"
    break;

  case 27:
#line 202 "parser.y"
    {yylhs.value.as < EzAquarii::ASTNode > () = ASTNode("direct_declarator", "variable"); yylhs.value.as < EzAquarii::ASTNode > ().addNode(ASTNode("ID", yystack_[0].value.as < std::string > ()));}
#line 948 "parser.cpp"
    break;

  case 28:
#line 204 "parser.y"
    {yylhs.value.as < EzAquarii::ASTNode > () = ASTNode("direct_declarator"); 
        yylhs.value.as < EzAquarii::ASTNode > ().addNode(ASTNode("LP", "(")).addNode(yystack_[1].value.as < EzAquarii::ASTNode > ()).addNode(ASTNode("RP", ")"));}
#line 955 "parser.cpp"
    break;

  case 29:
#line 207 "parser.y"
    {yylhs.value.as < EzAquarii::ASTNode > () = ASTNode("direct_declarator", "array"); yylhs.value.as < EzAquarii::ASTNode > ().nodes = yystack_[3].value.as < EzAquarii::ASTNode > ().nodes;/*这里的nodes应该是ID*/
        yylhs.value.as < EzAquarii::ASTNode > ().addNode(yystack_[1].value.as < EzAquarii::ASTNode > ());}
#line 962 "parser.cpp"
    break;

  case 30:
#line 210 "parser.y"
    {yylhs.value.as < EzAquarii::ASTNode > () = ASTNode("direct_declarator", "array"); yylhs.value.as < EzAquarii::ASTNode > ().nodes = yystack_[2].value.as < EzAquarii::ASTNode > ().nodes;/*这里的nodes应该是ID*/
        yylhs.value.as < EzAquarii::ASTNode > ().addNode(ASTNode("LB", "[")).addNode(ASTNode("RB", "]"));}
#line 969 "parser.cpp"
    break;

  case 31:
#line 213 "parser.y"
    {yylhs.value.as < EzAquarii::ASTNode > () = ASTNode("direct_declarator", "function"); yylhs.value.as < EzAquarii::ASTNode > ().nodes = yystack_[3].value.as < EzAquarii::ASTNode > ().nodes;/*这里的nodes应该是ID*/
        yylhs.value.as < EzAquarii::ASTNode > ().addNode(yystack_[1].value.as < EzAquarii::ASTNode > ());}
#line 976 "parser.cpp"
    break;

  case 32:
#line 216 "parser.y"
    {yylhs.value.as < EzAquarii::ASTNode > () = ASTNode("direct_declarator", "function"); yylhs.value.as < EzAquarii::ASTNode > ().nodes = yystack_[3].value.as < EzAquarii::ASTNode > ().nodes;/*这里的nodes应该是ID*/
        yylhs.value.as < EzAquarii::ASTNode > ().addNode(ASTNode("LP", "(")).addNode(yystack_[1].value.as < EzAquarii::ASTNode > ()).addNode(ASTNode("RP", ")"));}
#line 983 "parser.cpp"
    break;

  case 33:
#line 219 "parser.y"
    {yylhs.value.as < EzAquarii::ASTNode > () = ASTNode("direct_declarator", "function"); yylhs.value.as < EzAquarii::ASTNode > ().nodes = yystack_[2].value.as < EzAquarii::ASTNode > ().nodes;/*这里的nodes应该是ID*/}
#line 989 "parser.cpp"
    break;

  case 34:
#line 223 "parser.y"
    {yylhs.value.as < EzAquarii::ASTNode > () = yystack_[0].value.as < EzAquarii::ASTNode > ();}
#line 995 "parser.cpp"
    break;

  case 35:
#line 227 "parser.y"
    {yylhs.value.as < EzAquarii::ASTNode > () = ASTNode("parameter_list"); yylhs.value.as < EzAquarii::ASTNode > ().addNode(yystack_[0].value.as < EzAquarii::ASTNode > ());}
#line 1001 "parser.cpp"
    break;

  case 36:
#line 229 "parser.y"
    {yylhs.value.as < EzAquarii::ASTNode > () = yystack_[2].value.as < EzAquarii::ASTNode > (); yylhs.value.as < EzAquarii::ASTNode > ().addNode(yystack_[0].value.as < EzAquarii::ASTNode > ());}
#line 1007 "parser.cpp"
    break;

  case 37:
#line 234 "parser.y"
    {yylhs.value.as < EzAquarii::ASTNode > () = ASTNode("parameter_declaration"); 
        yylhs.value.as < EzAquarii::ASTNode > ().addNode(yystack_[1].value.as < EzAquarii::ASTNode > ()).addNode(yystack_[0].value.as < EzAquarii::ASTNode > ());}
#line 1014 "parser.cpp"
    break;

  case 38:
#line 236 "parser.y"
    {yylhs.value.as < EzAquarii::ASTNode > () = ASTNode("parameter_declaration"); yylhs.value.as < EzAquarii::ASTNode > ().addNode(yystack_[0].value.as < EzAquarii::ASTNode > ());}
#line 1020 "parser.cpp"
    break;

  case 39:
#line 240 "parser.y"
    {yylhs.value.as < EzAquarii::ASTNode > () = ASTNode("identifier_list"); yylhs.value.as < EzAquarii::ASTNode > ().addNode(ASTNode("ID", yystack_[0].value.as < std::string > ()));}
#line 1026 "parser.cpp"
    break;

  case 40:
#line 242 "parser.y"
    {yylhs.value.as < EzAquarii::ASTNode > () = yystack_[2].value.as < EzAquarii::ASTNode > (); yylhs.value.as < EzAquarii::ASTNode > ().addNode(yystack_[0].value.as < std::string > ());}
#line 1032 "parser.cpp"
    break;

  case 41:
#line 247 "parser.y"
    {yylhs.value.as < EzAquarii::ASTNode > () = ASTNode("compound_statement"); yylhs.value.as < EzAquarii::ASTNode > ().addNode(ASTNode("LC", "{")).addNode(ASTNode("RC", "}"));}
#line 1038 "parser.cpp"
    break;

  case 42:
#line 249 "parser.y"
    {yylhs.value.as < EzAquarii::ASTNode > () = ASTNode("compound_statement"); yylhs.value.as < EzAquarii::ASTNode > ().addNode(ASTNode("LC", "{")).addNode(yystack_[1].value.as < EzAquarii::ASTNode > ()).addNode(ASTNode("RC", "}"));}
#line 1044 "parser.cpp"
    break;

  case 43:
#line 251 "parser.y"
    {yylhs.value.as < EzAquarii::ASTNode > () = ASTNode("compound_statement"); yylhs.value.as < EzAquarii::ASTNode > ().addNode(ASTNode("LC", "{")).addNode(yystack_[1].value.as < EzAquarii::ASTNode > ()).addNode(ASTNode("RC", "}"));}
#line 1050 "parser.cpp"
    break;

  case 44:
#line 253 "parser.y"
    {yylhs.value.as < EzAquarii::ASTNode > () = ASTNode("compound_statement"); yylhs.value.as < EzAquarii::ASTNode > ().addNode(ASTNode("LC", "{")).addNode(yystack_[2].value.as < EzAquarii::ASTNode > ()).addNode(yystack_[1].value.as < EzAquarii::ASTNode > ()).addNode(ASTNode("RC", "}"));}
#line 1056 "parser.cpp"
    break;

  case 45:
#line 258 "parser.y"
    {yylhs.value.as < EzAquarii::ASTNode > () = ASTNode("statement_list"); yylhs.value.as < EzAquarii::ASTNode > ().addNode(yystack_[0].value.as < EzAquarii::ASTNode > ());}
#line 1062 "parser.cpp"
    break;

  case 46:
#line 260 "parser.y"
    {yylhs.value.as < EzAquarii::ASTNode > () = yystack_[1].value.as < EzAquarii::ASTNode > (); yylhs.value.as < EzAquarii::ASTNode > ().addNode(yystack_[0].value.as < EzAquarii::ASTNode > ());}
#line 1068 "parser.cpp"
    break;

  case 47:
#line 265 "parser.y"
    {yylhs.value.as < EzAquarii::ASTNode > () = ASTNode("constant"); yylhs.value.as < EzAquarii::ASTNode > ().addNode(ASTNode("INT_VALUE", yystack_[0].value.as < std::string > ()));}
#line 1074 "parser.cpp"
    break;

  case 48:
#line 267 "parser.y"
    {yylhs.value.as < EzAquarii::ASTNode > () = ASTNode("constant"); yylhs.value.as < EzAquarii::ASTNode > ().addNode(ASTNode("FLOAT_VALUE", yystack_[0].value.as < std::string > ()));}
#line 1080 "parser.cpp"
    break;

  case 49:
#line 272 "parser.y"
    {yylhs.value.as < EzAquarii::ASTNode > () = ASTNode("primary_expression"); yylhs.value.as < EzAquarii::ASTNode > ().addNode(ASTNode("ID", yystack_[0].value.as < std::string > ()));}
#line 1086 "parser.cpp"
    break;

  case 50:
#line 274 "parser.y"
    {yylhs.value.as < EzAquarii::ASTNode > () = yystack_[0].value.as < EzAquarii::ASTNode > ();}
#line 1092 "parser.cpp"
    break;

  case 51:
#line 277 "parser.y"
    {yylhs.value.as < EzAquarii::ASTNode > () = ASTNode("primary_expression"); 
        yylhs.value.as < EzAquarii::ASTNode > ().addNode(ASTNode("LP", "(")).addNode(yystack_[1].value.as < EzAquarii::ASTNode > ()).addNode(ASTNode("RP", ")"));}
#line 1099 "parser.cpp"
    break;

  case 52:
#line 283 "parser.y"
    {yylhs.value.as < EzAquarii::ASTNode > () = yystack_[0].value.as < EzAquarii::ASTNode > ();}
#line 1105 "parser.cpp"
    break;

  case 53:
#line 285 "parser.y"
    {yylhs.value.as < EzAquarii::ASTNode > () = ASTNode("postfix_expression"); 
        yylhs.value.as < EzAquarii::ASTNode > ().addNode(yystack_[3].value.as < EzAquarii::ASTNode > ()).addNode(ASTNode("LB", "[")).addNode(yystack_[1].value.as < EzAquarii::ASTNode > ()).addNode(ASTNode("RB", "]"));}
#line 1112 "parser.cpp"
    break;

  case 54:
#line 288 "parser.y"
    {yylhs.value.as < EzAquarii::ASTNode > () = ASTNode("postfix_expression"); 
        yylhs.value.as < EzAquarii::ASTNode > ().addNode(yystack_[2].value.as < EzAquarii::ASTNode > ()).addNode(ASTNode("LP", "(")).addNode(ASTNode("RP", ")"));}
#line 1119 "parser.cpp"
    break;

  case 55:
#line 291 "parser.y"
    {yylhs.value.as < EzAquarii::ASTNode > () = ASTNode("postfix_expression"); 
        yylhs.value.as < EzAquarii::ASTNode > ().addNode(yystack_[3].value.as < EzAquarii::ASTNode > ()).addNode(ASTNode("LP", "(")).addNode(yystack_[1].value.as < EzAquarii::ASTNode > ()).addNode(ASTNode("RP", ")"));}
#line 1126 "parser.cpp"
    break;

  case 56:
#line 294 "parser.y"
    {yylhs.value.as < EzAquarii::ASTNode > () = ASTNode("postfix_expression"); 
        yylhs.value.as < EzAquarii::ASTNode > ().addNode(yystack_[1].value.as < EzAquarii::ASTNode > ()).addNode(ASTNode("INC_OP", "+="));}
#line 1133 "parser.cpp"
    break;

  case 57:
#line 297 "parser.y"
    {yylhs.value.as < EzAquarii::ASTNode > () = ASTNode("postfix_expression"); 
        yylhs.value.as < EzAquarii::ASTNode > ().addNode(yystack_[1].value.as < EzAquarii::ASTNode > ()).addNode(ASTNode("DEC_OP", "-="));}
#line 1140 "parser.cpp"
    break;

  case 58:
#line 303 "parser.y"
    {yylhs.value.as < EzAquarii::ASTNode > () = yystack_[0].value.as < EzAquarii::ASTNode > ();}
#line 1146 "parser.cpp"
    break;

  case 59:
#line 305 "parser.y"
    {yylhs.value.as < EzAquarii::ASTNode > () = yystack_[2].value.as < EzAquarii::ASTNode > (); yylhs.value.as < EzAquarii::ASTNode > ().addNode(yystack_[0].value.as < EzAquarii::ASTNode > ());}
#line 1152 "parser.cpp"
    break;

  case 60:
#line 310 "parser.y"
    {yylhs.value.as < EzAquarii::ASTNode > () = yystack_[0].value.as < EzAquarii::ASTNode > ();}
#line 1158 "parser.cpp"
    break;

  case 61:
#line 312 "parser.y"
    {yylhs.value.as < EzAquarii::ASTNode > () = ASTNode("unary_expression"); yylhs.value.as < EzAquarii::ASTNode > ().addNode(ASTNode("INC_OP", "+=")).addNode(yystack_[0].value.as < EzAquarii::ASTNode > ());}
#line 1164 "parser.cpp"
    break;

  case 62:
#line 314 "parser.y"
    {yylhs.value.as < EzAquarii::ASTNode > () = ASTNode("unary_expression"); yylhs.value.as < EzAquarii::ASTNode > ().addNode(ASTNode("DEC_OP", "-=")).addNode(yystack_[0].value.as < EzAquarii::ASTNode > ());}
#line 1170 "parser.cpp"
    break;

  case 63:
#line 316 "parser.y"
    {yylhs.value.as < EzAquarii::ASTNode > () = ASTNode("unary_expression"); yylhs.value.as < EzAquarii::ASTNode > ().addNode(yystack_[1].value.as < EzAquarii::ASTNode > ()).addNode(yystack_[0].value.as < EzAquarii::ASTNode > ());}
#line 1176 "parser.cpp"
    break;

  case 64:
#line 322 "parser.y"
    {yylhs.value.as < EzAquarii::ASTNode > () = ASTNode("unary_operator"); yylhs.value.as < EzAquarii::ASTNode > ().addNode(ASTNode("PLUS_OP", "+"));}
#line 1182 "parser.cpp"
    break;

  case 65:
#line 323 "parser.y"
    {yylhs.value.as < EzAquarii::ASTNode > () = ASTNode("unary_operator"); yylhs.value.as < EzAquarii::ASTNode > ().addNode(ASTNode("MINUS_OP", "-"));}
#line 1188 "parser.cpp"
    break;

  case 66:
#line 328 "parser.y"
    {yylhs.value.as < EzAquarii::ASTNode > () = yystack_[0].value.as < EzAquarii::ASTNode > ();}
#line 1194 "parser.cpp"
    break;

  case 67:
#line 330 "parser.y"
    {yylhs.value.as < EzAquarii::ASTNode > () = ASTNode("cast_expression"); 
        yylhs.value.as < EzAquarii::ASTNode > ().addNode(ASTNode("LP", "(")).addNode(yystack_[2].value.as < EzAquarii::ASTNode > ()).addNode(ASTNode("RP", ")")).addNode(yystack_[0].value.as < EzAquarii::ASTNode > ());}
#line 1201 "parser.cpp"
    break;

  case 68:
#line 336 "parser.y"
    {yylhs.value.as < EzAquarii::ASTNode > () = yystack_[0].value.as < EzAquarii::ASTNode > ();}
#line 1207 "parser.cpp"
    break;

  case 69:
#line 338 "parser.y"
    {yylhs.value.as < EzAquarii::ASTNode > () = ASTNode("multiplicative_expression"); 
        yylhs.value.as < EzAquarii::ASTNode > ().addNode(yystack_[2].value.as < EzAquarii::ASTNode > ()).addNode(ASTNode("STAR_OP", "*")).addNode(yystack_[0].value.as < EzAquarii::ASTNode > ());}
#line 1214 "parser.cpp"
    break;

  case 70:
#line 341 "parser.y"
    {yylhs.value.as < EzAquarii::ASTNode > () = ASTNode("multiplicative_expression"); 
        yylhs.value.as < EzAquarii::ASTNode > ().addNode(yystack_[2].value.as < EzAquarii::ASTNode > ()).addNode(ASTNode("DIV_OP", "/")).addNode(yystack_[0].value.as < EzAquarii::ASTNode > ());}
#line 1221 "parser.cpp"
    break;

  case 71:
#line 344 "parser.y"
    {yylhs.value.as < EzAquarii::ASTNode > () = ASTNode("multiplicative_expression"); 
        yylhs.value.as < EzAquarii::ASTNode > ().addNode(yystack_[2].value.as < EzAquarii::ASTNode > ()).addNode(ASTNode("MOD_OP", "%")).addNode(yystack_[0].value.as < EzAquarii::ASTNode > ());}
#line 1228 "parser.cpp"
    break;

  case 72:
#line 350 "parser.y"
    {yylhs.value.as < EzAquarii::ASTNode > () = yystack_[0].value.as < EzAquarii::ASTNode > ();}
#line 1234 "parser.cpp"
    break;

  case 73:
#line 352 "parser.y"
    {yylhs.value.as < EzAquarii::ASTNode > () = ASTNode("additive_expression"); 
        yylhs.value.as < EzAquarii::ASTNode > ().addNode(yystack_[2].value.as < EzAquarii::ASTNode > ()).addNode(ASTNode("PLUS_OP", "+")).addNode(yystack_[0].value.as < EzAquarii::ASTNode > ());}
#line 1241 "parser.cpp"
    break;

  case 74:
#line 355 "parser.y"
    {yylhs.value.as < EzAquarii::ASTNode > () = ASTNode("additive_expression"); 
        yylhs.value.as < EzAquarii::ASTNode > ().addNode(yystack_[2].value.as < EzAquarii::ASTNode > ()).addNode(ASTNode("MINUS_OP", "-")).addNode(yystack_[0].value.as < EzAquarii::ASTNode > ());}
#line 1248 "parser.cpp"
    break;

  case 75:
#line 361 "parser.y"
    {yylhs.value.as < EzAquarii::ASTNode > () = yystack_[0].value.as < EzAquarii::ASTNode > ();}
#line 1254 "parser.cpp"
    break;

  case 76:
#line 368 "parser.y"
    {yylhs.value.as < EzAquarii::ASTNode > () = yystack_[0].value.as < EzAquarii::ASTNode > ();}
#line 1260 "parser.cpp"
    break;

  case 77:
#line 370 "parser.y"
    {yylhs.value.as < EzAquarii::ASTNode > () = ASTNode("relational_expression"); 
        yylhs.value.as < EzAquarii::ASTNode > ().addNode(yystack_[2].value.as < EzAquarii::ASTNode > ()).addNode(ASTNode("LT", "<")).addNode(yystack_[0].value.as < EzAquarii::ASTNode > ());}
#line 1267 "parser.cpp"
    break;

  case 78:
#line 373 "parser.y"
    {yylhs.value.as < EzAquarii::ASTNode > () = ASTNode("relational_expression"); 
        yylhs.value.as < EzAquarii::ASTNode > ().addNode(yystack_[2].value.as < EzAquarii::ASTNode > ()).addNode(ASTNode("AT", ">")).addNode(yystack_[0].value.as < EzAquarii::ASTNode > ());}
#line 1274 "parser.cpp"
    break;

  case 79:
#line 376 "parser.y"
    {yylhs.value.as < EzAquarii::ASTNode > () = ASTNode("relational_expression"); 
        yylhs.value.as < EzAquarii::ASTNode > ().addNode(yystack_[2].value.as < EzAquarii::ASTNode > ()).addNode(ASTNode("LE", "<=")).addNode(yystack_[0].value.as < EzAquarii::ASTNode > ());}
#line 1281 "parser.cpp"
    break;

  case 80:
#line 379 "parser.y"
    {yylhs.value.as < EzAquarii::ASTNode > () = ASTNode("relational_expression"); 
        yylhs.value.as < EzAquarii::ASTNode > ().addNode(yystack_[2].value.as < EzAquarii::ASTNode > ()).addNode(ASTNode("GE", ">=")).addNode(yystack_[0].value.as < EzAquarii::ASTNode > ());}
#line 1288 "parser.cpp"
    break;

  case 81:
#line 385 "parser.y"
    {yylhs.value.as < EzAquarii::ASTNode > () = yystack_[0].value.as < EzAquarii::ASTNode > ();}
#line 1294 "parser.cpp"
    break;

  case 82:
#line 387 "parser.y"
    {yylhs.value.as < EzAquarii::ASTNode > () = ASTNode("equality_expression"); 
        yylhs.value.as < EzAquarii::ASTNode > ().addNode(yystack_[2].value.as < EzAquarii::ASTNode > ()).addNode(ASTNode("EQ", "==")).addNode(yystack_[0].value.as < EzAquarii::ASTNode > ());}
#line 1301 "parser.cpp"
    break;

  case 83:
#line 390 "parser.y"
    {yylhs.value.as < EzAquarii::ASTNode > () = ASTNode("equality_expression"); 
        yylhs.value.as < EzAquarii::ASTNode > ().addNode(yystack_[2].value.as < EzAquarii::ASTNode > ()).addNode(ASTNode("NE", "<=")).addNode(yystack_[0].value.as < EzAquarii::ASTNode > ());}
#line 1308 "parser.cpp"
    break;

  case 84:
#line 396 "parser.y"
    {yylhs.value.as < EzAquarii::ASTNode > () = yystack_[0].value.as < EzAquarii::ASTNode > ();}
#line 1314 "parser.cpp"
    break;

  case 85:
#line 398 "parser.y"
    {yylhs.value.as < EzAquarii::ASTNode > () = ASTNode("and_expression"); 
        yylhs.value.as < EzAquarii::ASTNode > ().addNode(yystack_[2].value.as < EzAquarii::ASTNode > ()).addNode(ASTNode("AND_OP", "&&")).addNode(yystack_[0].value.as < EzAquarii::ASTNode > ());}
#line 1321 "parser.cpp"
    break;

  case 86:
#line 404 "parser.y"
    {yylhs.value.as < EzAquarii::ASTNode > () = yystack_[0].value.as < EzAquarii::ASTNode > ();}
#line 1327 "parser.cpp"
    break;

  case 87:
#line 406 "parser.y"
    {yylhs.value.as < EzAquarii::ASTNode > () = ASTNode("exclusive_or_expression"); 
        yylhs.value.as < EzAquarii::ASTNode > ().addNode(yystack_[2].value.as < EzAquarii::ASTNode > ()).addNode(ASTNode("XOR_OP", "^")).addNode(yystack_[0].value.as < EzAquarii::ASTNode > ());}
#line 1334 "parser.cpp"
    break;

  case 88:
#line 412 "parser.y"
    {yylhs.value.as < EzAquarii::ASTNode > () = yystack_[0].value.as < EzAquarii::ASTNode > ();}
#line 1340 "parser.cpp"
    break;

  case 89:
#line 414 "parser.y"
    {yylhs.value.as < EzAquarii::ASTNode > () = ASTNode("inclusive_or_expression"); 
        yylhs.value.as < EzAquarii::ASTNode > ().addNode(yystack_[2].value.as < EzAquarii::ASTNode > ()).addNode(ASTNode("OR_OP", "|")).addNode(yystack_[0].value.as < EzAquarii::ASTNode > ());}
#line 1347 "parser.cpp"
    break;

  case 90:
#line 420 "parser.y"
    {yylhs.value.as < EzAquarii::ASTNode > () = yystack_[0].value.as < EzAquarii::ASTNode > ();}
#line 1353 "parser.cpp"
    break;

  case 91:
#line 422 "parser.y"
    {yylhs.value.as < EzAquarii::ASTNode > () = ASTNode("logical_and_expression"); 
        yylhs.value.as < EzAquarii::ASTNode > ().addNode(yystack_[2].value.as < EzAquarii::ASTNode > ()).addNode(ASTNode("AND", "&&")).addNode(yystack_[0].value.as < EzAquarii::ASTNode > ());}
#line 1360 "parser.cpp"
    break;

  case 92:
#line 428 "parser.y"
    {yylhs.value.as < EzAquarii::ASTNode > () = yystack_[0].value.as < EzAquarii::ASTNode > ();}
#line 1366 "parser.cpp"
    break;

  case 93:
#line 430 "parser.y"
    {yylhs.value.as < EzAquarii::ASTNode > () = ASTNode("logical_or_expression"); 
        yylhs.value.as < EzAquarii::ASTNode > ().addNode(yystack_[2].value.as < EzAquarii::ASTNode > ()).addNode(ASTNode("OR", "||")).addNode(yystack_[0].value.as < EzAquarii::ASTNode > ());}
#line 1373 "parser.cpp"
    break;

  case 94:
#line 436 "parser.y"
    {yylhs.value.as < EzAquarii::ASTNode > () = yystack_[0].value.as < EzAquarii::ASTNode > ();}
#line 1379 "parser.cpp"
    break;

  case 95:
#line 442 "parser.y"
    {yylhs.value.as < EzAquarii::ASTNode > () = yystack_[0].value.as < EzAquarii::ASTNode > ();}
#line 1385 "parser.cpp"
    break;

  case 96:
#line 444 "parser.y"
    {yylhs.value.as < EzAquarii::ASTNode > () = ASTNode("assignment_expression"); 
        yylhs.value.as < EzAquarii::ASTNode > ().addNode(yystack_[2].value.as < EzAquarii::ASTNode > ()).addNode(yystack_[1].value.as < EzAquarii::ASTNode > ()).addNode(yystack_[0].value.as < EzAquarii::ASTNode > ());}
#line 1392 "parser.cpp"
    break;

  case 97:
#line 449 "parser.y"
    {yylhs.value.as < EzAquarii::ASTNode > () = ASTNode("assignment_operator"); yylhs.value.as < EzAquarii::ASTNode > ().addNode(ASTNode("ASSIGN", "="));}
#line 1398 "parser.cpp"
    break;

  case 98:
#line 450 "parser.y"
    {yylhs.value.as < EzAquarii::ASTNode > () = ASTNode("assignment_operator"); yylhs.value.as < EzAquarii::ASTNode > ().addNode(ASTNode("MUL_ASSIGN", "×="));}
#line 1404 "parser.cpp"
    break;

  case 99:
#line 451 "parser.y"
    {yylhs.value.as < EzAquarii::ASTNode > () = ASTNode("assignment_operator"); yylhs.value.as < EzAquarii::ASTNode > ().addNode(ASTNode("DIV_ASSIGN", "/="));}
#line 1410 "parser.cpp"
    break;

  case 100:
#line 452 "parser.y"
    {yylhs.value.as < EzAquarii::ASTNode > () = ASTNode("assignment_operator"); yylhs.value.as < EzAquarii::ASTNode > ().addNode(ASTNode("MOD_ASSIGN", "%="));}
#line 1416 "parser.cpp"
    break;

  case 101:
#line 453 "parser.y"
    {yylhs.value.as < EzAquarii::ASTNode > () = ASTNode("assignment_operator"); yylhs.value.as < EzAquarii::ASTNode > ().addNode(ASTNode("ADD_ASSIGN", "+="));}
#line 1422 "parser.cpp"
    break;

  case 102:
#line 454 "parser.y"
    {yylhs.value.as < EzAquarii::ASTNode > () = ASTNode("assignment_operator"); yylhs.value.as < EzAquarii::ASTNode > ().addNode(ASTNode("SUB_ASSIGN", "-="));}
#line 1428 "parser.cpp"
    break;

  case 103:
#line 464 "parser.y"
    {yylhs.value.as < EzAquarii::ASTNode > () = yystack_[0].value.as < EzAquarii::ASTNode > ();}
#line 1434 "parser.cpp"
    break;

  case 104:
#line 466 "parser.y"
    {yylhs.value.as < EzAquarii::ASTNode > () = ASTNode("expression"); 
        yylhs.value.as < EzAquarii::ASTNode > () = yystack_[2].value.as < EzAquarii::ASTNode > (); yylhs.value.as < EzAquarii::ASTNode > ().addNode(yystack_[0].value.as < EzAquarii::ASTNode > ());}
#line 1441 "parser.cpp"
    break;

  case 105:
#line 472 "parser.y"
    {yylhs.value.as < EzAquarii::ASTNode > () = yystack_[0].value.as < EzAquarii::ASTNode > ();}
#line 1447 "parser.cpp"
    break;

  case 106:
#line 477 "parser.y"
    {yylhs.value.as < EzAquarii::ASTNode > () = ASTNode("labeled_statement"); 
        yylhs.value.as < EzAquarii::ASTNode > ().addNode(ASTNode("CASE", "case")).addNode(yystack_[2].value.as < EzAquarii::ASTNode > ()).addNode(ASTNode("COLON", ":")).addNode(yystack_[0].value.as < EzAquarii::ASTNode > ());}
#line 1454 "parser.cpp"
    break;

  case 107:
#line 480 "parser.y"
    {yylhs.value.as < EzAquarii::ASTNode > () = ASTNode("labeled_statement"); 
        yylhs.value.as < EzAquarii::ASTNode > ().addNode(ASTNode("DEFAULT", "default")).addNode(ASTNode("COLON", ":")).addNode(yystack_[0].value.as < EzAquarii::ASTNode > ());}
#line 1461 "parser.cpp"
    break;

  case 108:
#line 486 "parser.y"
    {yylhs.value.as < EzAquarii::ASTNode > () = ASTNode("selection_statement"); 
        yylhs.value.as < EzAquarii::ASTNode > ().addNode(ASTNode("IF", "if")).addNode(ASTNode("LP", "(")).addNode(yystack_[2].value.as < EzAquarii::ASTNode > ()).addNode(ASTNode("RP", ")")).addNode(yystack_[0].value.as < EzAquarii::ASTNode > ());}
#line 1468 "parser.cpp"
    break;

  case 109:
#line 489 "parser.y"
    {yylhs.value.as < EzAquarii::ASTNode > () = ASTNode("selection_statement"); 
        yylhs.value.as < EzAquarii::ASTNode > ().addNode(ASTNode("IF", "if")).addNode(ASTNode("LP", "(")).addNode(yystack_[4].value.as < EzAquarii::ASTNode > ()).addNode(ASTNode("RP", ")"));
        yylhs.value.as < EzAquarii::ASTNode > ().addNode(yystack_[2].value.as < EzAquarii::ASTNode > ()).addNode(ASTNode("ELSE", "else")).addNode(yystack_[0].value.as < EzAquarii::ASTNode > ());}
#line 1476 "parser.cpp"
    break;

  case 110:
#line 493 "parser.y"
    {yylhs.value.as < EzAquarii::ASTNode > () = ASTNode("selection_statement"); 
        yylhs.value.as < EzAquarii::ASTNode > ().addNode(ASTNode("SWITCH", "switch")).addNode(ASTNode("LP", "(")).addNode(yystack_[2].value.as < EzAquarii::ASTNode > ()).addNode(ASTNode("RP", ")")).addNode(yystack_[0].value.as < EzAquarii::ASTNode > ());}
#line 1483 "parser.cpp"
    break;

  case 111:
#line 499 "parser.y"
    {yylhs.value.as < EzAquarii::ASTNode > () = ASTNode("iteration_statement"); 
        yylhs.value.as < EzAquarii::ASTNode > ().addNode(ASTNode("WHILE", "while")).addNode(ASTNode("LP", "(")).addNode(yystack_[2].value.as < EzAquarii::ASTNode > ()).addNode(ASTNode("RP", ")")).addNode(yystack_[0].value.as < EzAquarii::ASTNode > ());}
#line 1490 "parser.cpp"
    break;

  case 112:
#line 502 "parser.y"
    {yylhs.value.as < EzAquarii::ASTNode > () = ASTNode("iteration_statement"); 
        yylhs.value.as < EzAquarii::ASTNode > ().addNode(ASTNode("FOR", "for")).addNode(ASTNode("LP", "(")).addNode(yystack_[4].value.as < EzAquarii::ASTNode > ()).addNode(yystack_[3].value.as < EzAquarii::ASTNode > ()).addNode(yystack_[2].value.as < EzAquarii::ASTNode > ());
        yylhs.value.as < EzAquarii::ASTNode > ().addNode(ASTNode("RP", ")")).addNode(yystack_[0].value.as < EzAquarii::ASTNode > ());}
#line 1498 "parser.cpp"
    break;

  case 113:
#line 510 "parser.y"
    {yylhs.value.as < EzAquarii::ASTNode > () = ASTNode("jump_statement"); 
        yylhs.value.as < EzAquarii::ASTNode > ().addNode(ASTNode("CONTINUE", "continue"))/*.addNode(ASTNode("SEMMI", ";"))*/;}
#line 1505 "parser.cpp"
    break;

  case 114:
#line 513 "parser.y"
    {yylhs.value.as < EzAquarii::ASTNode > () = ASTNode("jump_statement"); 
        yylhs.value.as < EzAquarii::ASTNode > ().addNode(ASTNode("BREAK", "break"));}
#line 1512 "parser.cpp"
    break;

  case 115:
#line 516 "parser.y"
    {yylhs.value.as < EzAquarii::ASTNode > () = ASTNode("jump_statement"); 
        yylhs.value.as < EzAquarii::ASTNode > ().addNode(ASTNode("RETURN", "return"));}
#line 1519 "parser.cpp"
    break;

  case 116:
#line 519 "parser.y"
    {yylhs.value.as < EzAquarii::ASTNode > () = ASTNode("jump_statement"); 
        yylhs.value.as < EzAquarii::ASTNode > ().addNode(ASTNode("RETURN", "return"));}
#line 1526 "parser.cpp"
    break;

  case 117:
#line 524 "parser.y"
    {yylhs.value.as < EzAquarii::ASTNode > () = ASTNode("expression_statement");;}
#line 1532 "parser.cpp"
    break;

  case 118:
#line 526 "parser.y"
    {yylhs.value.as < EzAquarii::ASTNode > () = ASTNode("expression_statement"); 
        yylhs.value.as < EzAquarii::ASTNode > ().addNode(yystack_[1].value.as < EzAquarii::ASTNode > ());}
#line 1539 "parser.cpp"
    break;

  case 119:
#line 531 "parser.y"
    {yylhs.value.as < EzAquarii::ASTNode > () = ASTNode("statement"); yylhs.value.as < EzAquarii::ASTNode > ().addNode(yystack_[0].value.as < EzAquarii::ASTNode > ());}
#line 1545 "parser.cpp"
    break;

  case 120:
#line 532 "parser.y"
    {yylhs.value.as < EzAquarii::ASTNode > () = ASTNode("statement"); yylhs.value.as < EzAquarii::ASTNode > ().addNode(yystack_[0].value.as < EzAquarii::ASTNode > ());}
#line 1551 "parser.cpp"
    break;

  case 121:
#line 533 "parser.y"
    {yylhs.value.as < EzAquarii::ASTNode > () = ASTNode("statement"); yylhs.value.as < EzAquarii::ASTNode > ().addNode(yystack_[0].value.as < EzAquarii::ASTNode > ());}
#line 1557 "parser.cpp"
    break;

  case 122:
#line 534 "parser.y"
    {yylhs.value.as < EzAquarii::ASTNode > () = ASTNode("statement"); yylhs.value.as < EzAquarii::ASTNode > ().addNode(yystack_[0].value.as < EzAquarii::ASTNode > ());}
#line 1563 "parser.cpp"
    break;

  case 123:
#line 535 "parser.y"
    {yylhs.value.as < EzAquarii::ASTNode > () = ASTNode("statement"); yylhs.value.as < EzAquarii::ASTNode > ().addNode(yystack_[0].value.as < EzAquarii::ASTNode > ());}
#line 1569 "parser.cpp"
    break;

  case 124:
#line 536 "parser.y"
    {yylhs.value.as < EzAquarii::ASTNode > () = ASTNode("statement"); yylhs.value.as < EzAquarii::ASTNode > ().addNode(yystack_[0].value.as < EzAquarii::ASTNode > ());}
#line 1575 "parser.cpp"
    break;


#line 1579 "parser.cpp"

            default:
              break;
            }
        }
#if YY_EXCEPTIONS
      catch (const syntax_error& yyexc)
        {
          YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
          error (yyexc);
          YYERROR;
        }
#endif // YY_EXCEPTIONS
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;
      YY_STACK_PRINT ();

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, YY_MOVE (yylhs));
    }
    goto yynewstate;


  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        error (yyla.location, yysyntax_error_ (yystack_[0].state, yyla));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.type_get () == yyeof_)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:
    /* Pacify compilers when the user code never invokes YYERROR and
       the label yyerrorlab therefore never appears in user code.  */
    if (false)
      YYERROR;

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    goto yyerrlab1;


  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    {
      stack_symbol_type error_token;
      for (;;)
        {
          yyn = yypact_[yystack_[0].state];
          if (!yy_pact_value_is_default_ (yyn))
            {
              yyn += yyterror_;
              if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yyterror_)
                {
                  yyn = yytable_[yyn];
                  if (0 < yyn)
                    break;
                }
            }

          // Pop the current state because it cannot handle the error token.
          if (yystack_.size () == 1)
            YYABORT;

          yyerror_range[1].location = yystack_[0].location;
          yy_destroy_ ("Error: popping", yystack_[0]);
          yypop_ ();
          YY_STACK_PRINT ();
        }

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      // Shift the error token.
      error_token.state = yyn;
      yypush_ ("Shifting", YY_MOVE (error_token));
    }
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


  /*-----------------------------------------------------.
  | yyreturn -- parsing is finished, return the result.  |
  `-----------------------------------------------------*/
  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
#if YY_EXCEPTIONS
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack\n";
        // Do not try to display the values of the reclaimed symbols,
        // as their printers might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
#endif // YY_EXCEPTIONS
  }

  void
   Parser ::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what ());
  }

  // Generate an error message.
  std::string
   Parser ::yysyntax_error_ (state_type yystate, const symbol_type& yyla) const
  {
    // Number of reported tokens (one for the "unexpected", one per
    // "expected").
    size_t yycount = 0;
    // Its maximum.
    enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
    // Arguments of yyformat.
    char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];

    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yyla) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yyla.  (However, yyla is currently not documented for users.)
       - Of course, the expected token list depends on states to have
         correct lookahead information, and it depends on the parser not
         to perform extra reductions after fetching a lookahead from the
         scanner and before detecting a syntax error.  Thus, state
         merging (from LALR or IELR) and default reductions corrupt the
         expected token list.  However, the list is correct for
         canonical LR with one exception: it will still contain any
         token that will not be accepted due to an error action in a
         later state.
    */
    if (!yyla.empty ())
      {
        int yytoken = yyla.type_get ();
        yyarg[yycount++] = yytname_[yytoken];
        int yyn = yypact_[yystate];
        if (!yy_pact_value_is_default_ (yyn))
          {
            /* Start YYX at -YYN if negative to avoid negative indexes in
               YYCHECK.  In other words, skip the first -YYN actions for
               this state because they are default actions.  */
            int yyxbegin = yyn < 0 ? -yyn : 0;
            // Stay within bounds of both yycheck and yytname.
            int yychecklim = yylast_ - yyn + 1;
            int yyxend = yychecklim < yyntokens_ ? yychecklim : yyntokens_;
            for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
              if (yycheck_[yyx + yyn] == yyx && yyx != yyterror_
                  && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
                {
                  if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                    {
                      yycount = 1;
                      break;
                    }
                  else
                    yyarg[yycount++] = yytname_[yyx];
                }
          }
      }

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
      default: // Avoid compiler warnings.
        YYCASE_ (0, YY_("syntax error"));
        YYCASE_ (1, YY_("syntax error, unexpected %s"));
        YYCASE_ (2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_ (3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_ (4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_ (5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    std::string yyres;
    // Argument number.
    size_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += yytnamerr_ (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const signed char  Parser ::yypact_ninf_ = -127;

  const signed char  Parser ::yytable_ninf_ = -1;

  const short
   Parser ::yypact_[] =
  {
      98,  -127,  -127,  -127,    13,    98,  -127,  -127,  -127,     7,
    -127,  -127,  -127,  -127,     6,  -127,   -26,  -127,    28,    44,
     -27,     6,  -127,   420,   190,  -127,    31,     7,  -127,    21,
     291,  -127,  -127,    -4,  -127,  -127,  -127,   340,   340,  -127,
    -127,   471,   420,  -127,  -127,  -127,    40,    25,   466,  -127,
      82,    96,  -127,    74,   124,   -17,    -9,    14,    50,    65,
    -127,  -127,     9,    43,    66,    78,    17,   106,   113,   466,
      76,  -127,  -127,   239,  -127,   288,  -127,   -11,  -127,  -127,
    -127,  -127,  -127,  -127,  -127,  -127,  -127,  -127,     6,   102,
     116,  -127,    49,  -127,  -127,  -127,   117,   466,  -127,  -127,
     120,    93,  -127,     0,  -127,  -127,   437,   466,  -127,  -127,
    -127,  -127,  -127,  -127,   466,  -127,   466,   466,   466,   466,
     466,   466,   466,   466,   466,   466,   466,   466,   466,   466,
     466,   466,  -127,   466,  -127,   466,  -127,    27,   105,   466,
     118,   386,  -127,   337,  -127,  -127,   466,  -127,  -127,  -127,
      98,   163,  -127,  -127,   466,  -127,   403,  -127,  -127,    94,
    -127,    34,  -127,  -127,  -127,  -127,    82,    82,  -127,  -127,
    -127,  -127,    74,    74,   124,   -17,    -9,    14,    50,    99,
     100,  -127,   105,   103,   386,  -127,  -127,  -127,  -127,  -127,
    -127,  -127,  -127,   466,  -127,  -127,   386,   386,   466,   386,
    -127,  -127,  -127,   154,   108,  -127,   386,   386,  -127,  -127
  };

  const unsigned char
   Parser ::yydefact_[] =
  {
       0,    24,    25,    26,     0,     2,     3,     5,     6,     0,
      23,     1,     4,    27,     0,     7,     0,    11,    13,    20,
       0,     0,     8,     0,     0,     9,     0,     0,    22,     0,
       0,    28,    12,    13,    49,    47,    48,     0,     0,    64,
      65,     0,     0,    14,    50,    52,    60,    66,     0,    68,
      72,    75,    76,    81,    84,    86,    88,    90,    92,    94,
      95,    15,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    41,   117,     0,   120,     0,   103,     0,   119,   122,
     123,   124,   121,    45,    10,    21,    39,    33,    38,     0,
      34,    35,     0,    30,    66,   105,     0,     0,    61,    62,
       0,     0,    18,     0,    56,    57,     0,     0,   101,   102,
      98,    99,   100,    97,     0,    63,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   114,     0,   113,     0,   115,     0,     0,     0,
       0,     0,    43,     0,    42,    46,     0,   118,    37,    31,
       0,     0,    32,    29,     0,    51,     0,    16,    54,     0,
      58,     0,    96,    70,    69,    71,    73,    74,    78,    77,
      80,    79,    82,    83,    85,    87,    89,    91,    93,     0,
       0,   116,     0,     0,     0,   107,    44,   104,    36,    40,
      67,    17,    19,     0,    55,    53,     0,     0,     0,     0,
     106,    59,   111,   108,     0,   110,     0,     0,   109,   112
  };

  const short
   Parser ::yypgoto_[] =
  {
    -127,  -127,  -127,   164,   -10,   147,  -127,   151,   -38,  -127,
      -3,  -127,     2,   132,  -127,  -127,  -127,    24,  -127,    54,
     119,  -127,  -127,  -127,  -127,    59,  -127,   -43,    41,  -127,
      -8,    37,    64,    75,    80,    81,    79,  -127,   -15,   -23,
    -127,   -40,   143,  -127,  -127,  -127,  -127,  -126,   -72
  };

  const short
   Parser ::yydefgoto_[] =
  {
      -1,     4,     5,     6,     7,    26,    16,    17,    43,   103,
      33,     8,    27,    10,    19,    89,    90,    91,    92,    74,
      75,    44,    45,    46,   159,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    76,
     114,    77,    96,    78,    79,    80,    81,    82,    83
  };

  const unsigned char
   Parser ::yytable_[] =
  {
      61,   101,     9,   145,   102,   115,    18,     9,    25,    13,
      13,    20,   182,    11,    25,    95,    84,    21,    31,    61,
      34,    35,    36,   127,    86,    22,   137,     1,     2,     3,
      23,    88,   146,   128,     1,     2,     3,     1,     2,     3,
     147,    37,    38,   156,   108,   109,   110,   111,   112,   157,
      14,    14,    39,    40,    95,   129,   198,   101,    15,   113,
     132,    41,    23,    84,   104,   105,    87,   161,   136,   185,
     146,   145,    28,   163,   164,   165,    24,   146,   181,    24,
      85,   195,   130,   160,   106,   148,   107,   133,    29,    94,
      30,   162,   151,   179,   152,   180,    98,    99,   131,   183,
     121,   122,   123,   124,     1,     2,     3,    94,    34,    35,
      36,   190,   200,   168,   169,   170,   171,   134,   192,   116,
     117,   118,   135,   187,   202,   203,   141,   205,    94,    37,
      38,   119,   120,    61,   208,   209,   146,   193,   155,   194,
      39,    40,   146,   146,   196,   197,   146,   149,   199,    41,
     138,   146,    88,   207,   125,   126,    72,   139,   204,   150,
     166,   167,   172,   173,   153,   154,   189,   206,   184,    12,
     201,    73,    32,   100,   188,    94,    94,    94,    94,    94,
      94,    94,    94,    94,    94,    94,    94,    94,    94,    94,
      94,   174,   143,    34,    35,    36,     1,     2,     3,    62,
      63,    64,    65,   175,    66,    67,    68,    69,    70,   176,
     178,   177,   140,    94,    37,    38,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    39,    40,     0,     0,     0,
       0,     0,     0,     0,    41,     0,     0,     0,    24,    71,
       0,    72,    34,    35,    36,     1,     2,     3,    62,    63,
      64,    65,     0,    66,    67,    68,    69,    70,     0,     0,
       0,     0,     0,    37,    38,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    39,    40,     0,     0,     0,     0,
       0,     0,     0,    41,     0,     0,     0,    24,   142,     0,
      72,    34,    35,    36,    34,    35,    36,    62,    63,    64,
      65,     0,    66,    67,    68,    69,    70,     0,     0,     0,
       0,     0,    37,    38,     0,    37,    38,     0,     0,     0,
       0,     0,     0,    39,    40,     0,    39,    40,     0,     0,
       0,     0,    41,     0,     0,    41,    24,   144,    93,    72,
      34,    35,    36,    34,    35,    36,    62,    63,    64,    65,
       0,    66,    67,    68,    69,    70,     0,     0,     0,     0,
       0,    37,    38,     0,    37,    38,     0,     0,     0,     0,
       0,     0,    39,    40,     0,    39,    40,     0,     0,     0,
       0,    41,     0,     0,    97,    24,   186,     0,    72,    34,
      35,    36,     0,     0,     0,    62,    63,    64,    65,     0,
      66,    67,    68,    69,    70,     0,    34,    35,    36,     0,
      37,    38,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    39,    40,    34,    35,    36,     0,    37,    38,     0,
      41,     0,     0,     0,    24,     0,     0,    72,    39,    40,
      34,    35,    36,     0,    37,    38,     0,    41,     0,     0,
       0,    42,   191,     0,     0,    39,    40,     0,     0,     0,
       0,    37,    38,     0,    41,     0,     0,     0,    42,    34,
      35,    36,    39,    40,    34,    35,    36,     1,     2,     3,
       0,    41,   158,     0,     0,     0,     0,     0,     0,     0,
      37,    38,     0,     0,     0,    37,    38,     0,     0,     0,
       0,    39,    40,     0,     0,     0,    39,    40,     0,     0,
      41,     0,     0,     0,     0,    41
  };

  const short
   Parser ::yycheck_[] =
  {
      23,    41,     0,    75,    42,    48,     9,     5,    18,     3,
       3,    14,   138,     0,    24,    30,    26,    43,    45,    42,
       3,     4,     5,    40,     3,    51,    66,     6,     7,     8,
      34,    29,    43,    42,     6,     7,     8,     6,     7,     8,
      51,    24,    25,    43,    19,    20,    21,    22,    23,    49,
      44,    44,    35,    36,    69,    41,   182,    97,    51,    34,
      51,    44,    34,    73,    24,    25,    45,   107,    51,   141,
      43,   143,    18,   116,   117,   118,    48,    43,    51,    48,
      26,    47,    32,   106,    44,    88,    46,    44,    44,    30,
      46,   114,    43,   133,    45,   135,    37,    38,    33,   139,
      26,    27,    28,    29,     6,     7,     8,    48,     3,     4,
       5,   154,   184,   121,   122,   123,   124,    51,   156,    37,
      38,    39,    44,   146,   196,   197,    50,   199,    69,    24,
      25,    35,    36,   156,   206,   207,    43,    43,    45,    45,
      35,    36,    43,    43,    45,    45,    43,    45,    45,    44,
      44,    43,   150,    45,    30,    31,    51,    44,   198,    43,
     119,   120,   125,   126,    47,    45,     3,    13,    50,     5,
     193,    24,    21,    41,   150,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   126,   127,   128,   129,   130,
     131,   127,    73,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,   128,    14,    15,    16,    17,    18,   129,
     131,   130,    69,   154,    24,    25,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    35,    36,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    44,    -1,    -1,    -1,    48,    49,
      -1,    51,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    -1,    14,    15,    16,    17,    18,    -1,    -1,
      -1,    -1,    -1,    24,    25,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    35,    36,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    44,    -1,    -1,    -1,    48,    49,    -1,
      51,     3,     4,     5,     3,     4,     5,     9,    10,    11,
      12,    -1,    14,    15,    16,    17,    18,    -1,    -1,    -1,
      -1,    -1,    24,    25,    -1,    24,    25,    -1,    -1,    -1,
      -1,    -1,    -1,    35,    36,    -1,    35,    36,    -1,    -1,
      -1,    -1,    44,    -1,    -1,    44,    48,    49,    47,    51,
       3,     4,     5,     3,     4,     5,     9,    10,    11,    12,
      -1,    14,    15,    16,    17,    18,    -1,    -1,    -1,    -1,
      -1,    24,    25,    -1,    24,    25,    -1,    -1,    -1,    -1,
      -1,    -1,    35,    36,    -1,    35,    36,    -1,    -1,    -1,
      -1,    44,    -1,    -1,    44,    48,    49,    -1,    51,     3,
       4,     5,    -1,    -1,    -1,     9,    10,    11,    12,    -1,
      14,    15,    16,    17,    18,    -1,     3,     4,     5,    -1,
      24,    25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    35,    36,     3,     4,     5,    -1,    24,    25,    -1,
      44,    -1,    -1,    -1,    48,    -1,    -1,    51,    35,    36,
       3,     4,     5,    -1,    24,    25,    -1,    44,    -1,    -1,
      -1,    48,    49,    -1,    -1,    35,    36,    -1,    -1,    -1,
      -1,    24,    25,    -1,    44,    -1,    -1,    -1,    48,     3,
       4,     5,    35,    36,     3,     4,     5,     6,     7,     8,
      -1,    44,    45,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      24,    25,    -1,    -1,    -1,    24,    25,    -1,    -1,    -1,
      -1,    35,    36,    -1,    -1,    -1,    35,    36,    -1,    -1,
      44,    -1,    -1,    -1,    -1,    44
  };

  const unsigned char
   Parser ::yystos_[] =
  {
       0,     6,     7,     8,    54,    55,    56,    57,    64,    65,
      66,     0,    56,     3,    44,    51,    59,    60,    63,    67,
      63,    43,    51,    34,    48,    57,    58,    65,    72,    44,
      46,    45,    60,    63,     3,     4,     5,    24,    25,    35,
      36,    44,    48,    61,    74,    75,    76,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,     9,    10,    11,    12,    14,    15,    16,    17,
      18,    49,    51,    58,    72,    73,    92,    94,    96,    97,
      98,    99,   100,   101,    57,    72,     3,    45,    65,    68,
      69,    70,    71,    47,    78,    91,    95,    44,    78,    78,
      66,    94,    61,    62,    24,    25,    44,    46,    19,    20,
      21,    22,    23,    34,    93,    80,    37,    38,    39,    35,
      36,    26,    27,    28,    29,    30,    31,    40,    42,    41,
      32,    33,    51,    44,    51,    44,    51,    94,    44,    44,
      95,    50,    49,    73,    49,   101,    43,    51,    63,    45,
      43,    43,    45,    47,    45,    45,    43,    49,    45,    77,
      92,    94,    92,    80,    80,    80,    81,    81,    83,    83,
      83,    83,    84,    84,    85,    86,    87,    88,    89,    94,
      94,    51,   100,    94,    50,   101,    49,    92,    70,     3,
      80,    49,    61,    43,    45,    47,    45,    45,   100,    45,
     101,    92,   101,   101,    94,   101,    13,    45,   101,   101
  };

  const unsigned char
   Parser ::yyr1_[] =
  {
       0,    53,    54,    55,    55,    56,    56,    57,    57,    58,
      58,    59,    59,    60,    60,    61,    61,    61,    62,    62,
      63,    64,    64,    65,    66,    66,    66,    67,    67,    67,
      67,    67,    67,    67,    68,    69,    69,    70,    70,    71,
      71,    72,    72,    72,    72,    73,    73,    74,    74,    75,
      75,    75,    76,    76,    76,    76,    76,    76,    77,    77,
      78,    78,    78,    78,    79,    79,    80,    80,    81,    81,
      81,    81,    82,    82,    82,    83,    84,    84,    84,    84,
      84,    85,    85,    85,    86,    86,    87,    87,    88,    88,
      89,    89,    90,    90,    91,    92,    92,    93,    93,    93,
      93,    93,    93,    94,    94,    95,    96,    96,    97,    97,
      97,    98,    98,    99,    99,    99,    99,   100,   100,   101,
     101,   101,   101,   101,   101
  };

  const unsigned char
   Parser ::yyr2_[] =
  {
       0,     2,     1,     1,     2,     1,     1,     2,     3,     1,
       2,     1,     3,     1,     3,     1,     3,     4,     1,     3,
       1,     4,     3,     1,     1,     1,     1,     1,     3,     4,
       3,     4,     4,     3,     1,     1,     3,     2,     1,     1,
       3,     2,     3,     3,     4,     1,     2,     1,     1,     1,
       1,     3,     1,     4,     3,     4,     2,     2,     1,     3,
       1,     2,     2,     2,     1,     1,     1,     4,     1,     3,
       3,     3,     1,     3,     3,     1,     1,     3,     3,     3,
       3,     1,     3,     3,     1,     3,     1,     3,     1,     3,
       1,     3,     1,     3,     1,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     3,     1,     4,     3,     5,     7,
       5,     5,     7,     2,     2,     2,     3,     1,     2,     1,
       1,     1,     1,     1,     1
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const  Parser ::yytname_[] =
  {
  "\"end of file\"", "error", "$undefined", "ID", "INT_VALUE",
  "FLOAT_VALUE", "INT", "FLOAT", "CHAR", "BREAK", "WHILE", "CONTINUE",
  "IF", "ELSE", "RETURN", "FOR", "SWITCH", "CASE", "DEFAULT", "ADD_ASSIGN",
  "SUB_ASSIGN", "MUL_ASSIGN", "DIV_ASSIGN", "MOD_ASSIGN", "INC_OP",
  "DEC_OP", "AT", "LT", "AE", "LE", "EQ", "NE", "AND", "OR", "ASSIGN",
  "PLUS_OP", "MINUS_OP", "DIV_OP", "STAR_OP", "MOD_OP", "AND_OP", "OR_OP",
  "XOR_OP", "COMMA", "LP", "RP", "LB", "RB", "LC", "RC", "COLON", "SEMMI",
  "LOWER_THAN_ELSE", "$accept", "program", "translation_unit",
  "external_declaration", "declaration", "declaration_list",
  "init_declarator_list", "init_declarator", "initializer",
  "initializer_list", "declarator", "function_definition",
  "declaration_specifiers", "type_specifier", "direct_declarator",
  "parameter_type_list", "parameter_list", "parameter_declaration",
  "identifier_list", "compound_statement", "statement_list", "constant",
  "primary_expression", "postfix_expression", "argument_expression_list",
  "unary_expression", "unary_operator", "cast_expression",
  "multiplicative_expression", "additive_expression", "shift_expression",
  "relational_expression", "equality_expression", "and_expression",
  "exclusive_or_expression", "inclusive_or_expression",
  "logical_and_expression", "logical_or_expression",
  "conditional_expression", "assignment_expression", "assignment_operator",
  "expression", "constant_expression", "labeled_statement",
  "selection_statement", "iteration_statement", "jump_statement",
  "expression_statement", "statement", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned short
   Parser ::yyrline_[] =
  {
       0,   118,   118,   125,   127,   132,   134,   139,   141,   146,
     148,   153,   154,   159,   160,   165,   166,   168,   173,   174,
     179,   183,   185,   190,   194,   195,   196,   201,   203,   206,
     209,   212,   215,   218,   223,   227,   228,   233,   236,   240,
     241,   246,   248,   250,   252,   257,   259,   264,   266,   271,
     273,   276,   282,   284,   287,   290,   293,   296,   302,   304,
     309,   311,   313,   315,   322,   323,   327,   329,   335,   337,
     340,   343,   349,   351,   354,   360,   367,   369,   372,   375,
     378,   384,   386,   389,   395,   397,   403,   405,   411,   413,
     419,   421,   427,   429,   435,   441,   443,   449,   450,   451,
     452,   453,   454,   463,   465,   471,   476,   479,   485,   488,
     492,   498,   501,   509,   512,   515,   518,   524,   525,   531,
     532,   533,   534,   535,   536
  };

  // Print the state stack on the debug stream.
  void
   Parser ::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << i->state;
    *yycdebug_ << '\n';
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
   Parser ::yy_reduce_print_ (int yyrule)
  {
    unsigned yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):\n";
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG


#line 37 "parser.y"
} //  EzAquarii 
#line 2186 "parser.cpp"

#line 539 "parser.y"


// Bison expects us to provide implementation - otherwise linker complains
void EzAquarii::Parser::error(const location &loc , const std::string &message) {
        
        // Location should be initialized inside scanner action, but is not in this example.
        // Let's grab location directly from driver class.
	// cout << "Error: " << message << endl << "Location: " << loc << endl;
	
        cout << "Error: " << message << endl << "Error location: " << driver.locationString() << endl;
}
