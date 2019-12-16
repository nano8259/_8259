// A Bison parser, made by GNU Bison 3.4.2.

// Skeleton interface for Bison LALR(1) parsers in C++

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


/**
 ** \file parser.hpp
 ** Define the  EzAquarii ::parser class.
 */

// C++ LALR(1) parser skeleton written by Akim Demaille.

// Undocumented macros, especially those whose name start with YY_,
// are private implementation details.  Do not rely on them.

#ifndef YY_YY_PARSER_HPP_INCLUDED
# define YY_YY_PARSER_HPP_INCLUDED
// //                    "%code requires" blocks.
#line 39 "parser.y"

    #include <iostream>
    #include <string>
    #include <vector>
    #include <stdint.h>
    #include "command.h"
    #include "symbol.h"

    using namespace std;

    namespace EzAquarii {
        class Scanner;
        class Interpreter;
    }

#line 64 "parser.hpp"

# include <cassert>
# include <cstdlib> // std::abort
# include <iostream>
# include <stdexcept>
# include <string>
# include <vector>

#if defined __cplusplus
# define YY_CPLUSPLUS __cplusplus
#else
# define YY_CPLUSPLUS 199711L
#endif

// Support move semantics when possible.
#if 201103L <= YY_CPLUSPLUS
# define YY_MOVE           std::move
# define YY_MOVE_OR_COPY   move
# define YY_MOVE_REF(Type) Type&&
# define YY_RVREF(Type)    Type&&
# define YY_COPY(Type)     Type
#else
# define YY_MOVE
# define YY_MOVE_OR_COPY   copy
# define YY_MOVE_REF(Type) Type&
# define YY_RVREF(Type)    const Type&
# define YY_COPY(Type)     const Type&
#endif

// Support noexcept when possible.
#if 201103L <= YY_CPLUSPLUS
# define YY_NOEXCEPT noexcept
# define YY_NOTHROW
#else
# define YY_NOEXCEPT
# define YY_NOTHROW throw ()
#endif

// Support constexpr when possible.
#if 201703 <= YY_CPLUSPLUS
# define YY_CONSTEXPR constexpr
#else
# define YY_CONSTEXPR
#endif
# include "location.hh"
#include <typeinfo>
#ifndef YYASSERT
# include <cassert>
# define YYASSERT assert
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

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
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

/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif

#line 37 "parser.y"
namespace  EzAquarii  {
#line 180 "parser.hpp"




  /// A Bison parser.
  class  Parser 
  {
  public:
#ifndef YYSTYPE
  /// A buffer to store and retrieve objects.
  ///
  /// Sort of a variant, but does not keep track of the nature
  /// of the stored data, since that knowledge is available
  /// via the current parser state.
  class semantic_type
  {
  public:
    /// Type of *this.
    typedef semantic_type self_type;

    /// Empty construction.
    semantic_type () YY_NOEXCEPT
      : yybuffer_ ()
      , yytypeid_ (YY_NULLPTR)
    {}

    /// Construct and fill.
    template <typename T>
    semantic_type (YY_RVREF (T) t)
      : yytypeid_ (&typeid (T))
    {
      YYASSERT (sizeof (T) <= size);
      new (yyas_<T> ()) T (YY_MOVE (t));
    }

    /// Destruction, allowed only if empty.
    ~semantic_type () YY_NOEXCEPT
    {
      YYASSERT (!yytypeid_);
    }

# if 201103L <= YY_CPLUSPLUS
    /// Instantiate a \a T in here from \a t.
    template <typename T, typename... U>
    T&
    emplace (U&&... u)
    {
      YYASSERT (!yytypeid_);
      YYASSERT (sizeof (T) <= size);
      yytypeid_ = & typeid (T);
      return *new (yyas_<T> ()) T (std::forward <U>(u)...);
    }
# else
    /// Instantiate an empty \a T in here.
    template <typename T>
    T&
    emplace ()
    {
      YYASSERT (!yytypeid_);
      YYASSERT (sizeof (T) <= size);
      yytypeid_ = & typeid (T);
      return *new (yyas_<T> ()) T ();
    }

    /// Instantiate a \a T in here from \a t.
    template <typename T>
    T&
    emplace (const T& t)
    {
      YYASSERT (!yytypeid_);
      YYASSERT (sizeof (T) <= size);
      yytypeid_ = & typeid (T);
      return *new (yyas_<T> ()) T (t);
    }
# endif

    /// Instantiate an empty \a T in here.
    /// Obsolete, use emplace.
    template <typename T>
    T&
    build ()
    {
      return emplace<T> ();
    }

    /// Instantiate a \a T in here from \a t.
    /// Obsolete, use emplace.
    template <typename T>
    T&
    build (const T& t)
    {
      return emplace<T> (t);
    }

    /// Accessor to a built \a T.
    template <typename T>
    T&
    as () YY_NOEXCEPT
    {
      YYASSERT (yytypeid_);
      YYASSERT (*yytypeid_ == typeid (T));
      YYASSERT (sizeof (T) <= size);
      return *yyas_<T> ();
    }

    /// Const accessor to a built \a T (for %printer).
    template <typename T>
    const T&
    as () const YY_NOEXCEPT
    {
      YYASSERT (yytypeid_);
      YYASSERT (*yytypeid_ == typeid (T));
      YYASSERT (sizeof (T) <= size);
      return *yyas_<T> ();
    }

    /// Swap the content with \a that, of same type.
    ///
    /// Both variants must be built beforehand, because swapping the actual
    /// data requires reading it (with as()), and this is not possible on
    /// unconstructed variants: it would require some dynamic testing, which
    /// should not be the variant's responsibility.
    /// Swapping between built and (possibly) non-built is done with
    /// self_type::move ().
    template <typename T>
    void
    swap (self_type& that) YY_NOEXCEPT
    {
      YYASSERT (yytypeid_);
      YYASSERT (*yytypeid_ == *that.yytypeid_);
      std::swap (as<T> (), that.as<T> ());
    }

    /// Move the content of \a that to this.
    ///
    /// Destroys \a that.
    template <typename T>
    void
    move (self_type& that)
    {
# if 201103L <= YY_CPLUSPLUS
      emplace<T> (std::move (that.as<T> ()));
# else
      emplace<T> ();
      swap<T> (that);
# endif
      that.destroy<T> ();
    }

# if 201103L <= YY_CPLUSPLUS
    /// Move the content of \a that to this.
    template <typename T>
    void
    move (self_type&& that)
    {
      emplace<T> (std::move (that.as<T> ()));
      that.destroy<T> ();
    }
#endif

    /// Copy the content of \a that to this.
    template <typename T>
    void
    copy (const self_type& that)
    {
      emplace<T> (that.as<T> ());
    }

    /// Destroy the stored \a T.
    template <typename T>
    void
    destroy ()
    {
      as<T> ().~T ();
      yytypeid_ = YY_NULLPTR;
    }

  private:
    /// Prohibit blind copies.
    self_type& operator= (const self_type&);
    semantic_type (const self_type&);

    /// Accessor to raw memory as \a T.
    template <typename T>
    T*
    yyas_ () YY_NOEXCEPT
    {
      void *yyp = yybuffer_.yyraw;
      return static_cast<T*> (yyp);
     }

    /// Const accessor to raw memory as \a T.
    template <typename T>
    const T*
    yyas_ () const YY_NOEXCEPT
    {
      const void *yyp = yybuffer_.yyraw;
      return static_cast<const T*> (yyp);
     }

    /// An auxiliary type to compute the largest semantic type.
    union union_type
    {
      // program
      // translation_unit
      // external_declaration
      // declaration
      // declaration_list
      // init_declarator_list
      // init_declarator
      // initializer
      // initializer_list
      // declarator
      // function_definition
      // declaration_specifiers
      // type_specifier
      // direct_declarator
      // parameter_type_list
      // parameter_list
      // parameter_declaration
      // identifier_list
      // compound_statement
      // statement_list
      // constant
      // primary_expression
      // postfix_expression
      // argument_expression_list
      // unary_expression
      // unary_operator
      // cast_expression
      // multiplicative_expression
      // additive_expression
      // shift_expression
      // relational_expression
      // equality_expression
      // and_expression
      // exclusive_or_expression
      // inclusive_or_expression
      // logical_and_expression
      // logical_or_expression
      // conditional_expression
      // assignment_expression
      // assignment_operator
      // expression
      // constant_expression
      // labeled_statement
      // selection_statement
      // iteration_statement
      // jump_statement
      // expression_statement
      // statement
      char dummy1[sizeof (EzAquarii::ASTNode)];

      // ID
      // INT_VALUE
      // FLOAT_VALUE
      char dummy2[sizeof (std::string)];
    };

    /// The size of the largest semantic type.
    enum { size = sizeof (union_type) };

    /// A buffer to store semantic values.
    union
    {
      /// Strongest alignment constraints.
      long double yyalign_me;
      /// A buffer large enough to store any of the semantic values.
      char yyraw[size];
    } yybuffer_;

    /// Whether the content is built: if defined, the name of the stored type.
    const std::type_info *yytypeid_;
  };

#else
    typedef YYSTYPE semantic_type;
#endif
    /// Symbol locations.
    typedef location location_type;

    /// Syntax errors thrown from user actions.
    struct syntax_error : std::runtime_error
    {
      syntax_error (const location_type& l, const std::string& m)
        : std::runtime_error (m)
        , location (l)
      {}

      syntax_error (const syntax_error& s)
        : std::runtime_error (s.what ())
        , location (s.location)
      {}

      ~syntax_error () YY_NOEXCEPT YY_NOTHROW;

      location_type location;
    };

    /// Tokens.
    struct token
    {
      enum yytokentype
      {
        TOKEN_END = 0,
        TOKEN_ID = 258,
        TOKEN_INT_VALUE = 259,
        TOKEN_FLOAT_VALUE = 260,
        TOKEN_INT = 261,
        TOKEN_FLOAT = 262,
        TOKEN_CHAR = 263,
        TOKEN_BREAK = 264,
        TOKEN_WHILE = 265,
        TOKEN_CONTINUE = 266,
        TOKEN_IF = 267,
        TOKEN_ELSE = 268,
        TOKEN_RETURN = 269,
        TOKEN_FOR = 270,
        TOKEN_SWITCH = 271,
        TOKEN_CASE = 272,
        TOKEN_DEFAULT = 273,
        TOKEN_ADD_ASSIGN = 274,
        TOKEN_SUB_ASSIGN = 275,
        TOKEN_MUL_ASSIGN = 276,
        TOKEN_DIV_ASSIGN = 277,
        TOKEN_MOD_ASSIGN = 278,
        TOKEN_INC_OP = 279,
        TOKEN_DEC_OP = 280,
        TOKEN_AT = 281,
        TOKEN_LT = 282,
        TOKEN_AE = 283,
        TOKEN_LE = 284,
        TOKEN_EQ = 285,
        TOKEN_NE = 286,
        TOKEN_AND = 287,
        TOKEN_OR = 288,
        TOKEN_ASSIGN = 289,
        TOKEN_PLUS_OP = 290,
        TOKEN_MINUS_OP = 291,
        TOKEN_DIV_OP = 292,
        TOKEN_STAR_OP = 293,
        TOKEN_MOD_OP = 294,
        TOKEN_AND_OP = 295,
        TOKEN_OR_OP = 296,
        TOKEN_XOR_OP = 297,
        TOKEN_COMMA = 298,
        TOKEN_LP = 299,
        TOKEN_RP = 300,
        TOKEN_LB = 301,
        TOKEN_RB = 302,
        TOKEN_LC = 303,
        TOKEN_RC = 304,
        TOKEN_COLON = 305,
        TOKEN_SEMMI = 306,
        TOKEN_LOWER_THAN_ELSE = 307
      };
    };

    /// (External) token type, as returned by yylex.
    typedef token::yytokentype token_type;

    /// Symbol type: an internal symbol number.
    typedef int symbol_number_type;

    /// The symbol type number to denote an empty symbol.
    enum { empty_symbol = -2 };

    /// Internal symbol number for tokens (subsumed by symbol_number_type).
    typedef unsigned char token_number_type;

    /// A complete symbol.
    ///
    /// Expects its Base type to provide access to the symbol type
    /// via type_get ().
    ///
    /// Provide access to semantic value and location.
    template <typename Base>
    struct basic_symbol : Base
    {
      /// Alias to Base.
      typedef Base super_type;

      /// Default constructor.
      basic_symbol ()
        : value ()
        , location ()
      {}

#if 201103L <= YY_CPLUSPLUS
      /// Move constructor.
      basic_symbol (basic_symbol&& that);
#endif

      /// Copy constructor.
      basic_symbol (const basic_symbol& that);

      /// Constructor for valueless symbols, and symbols from each type.
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, location_type&& l)
        : Base (t)
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const location_type& l)
        : Base (t)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, EzAquarii::ASTNode&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const EzAquarii::ASTNode& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::string&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::string& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

      /// Destroy the symbol.
      ~basic_symbol ()
      {
        clear ();
      }

      /// Destroy contents, and record that is empty.
      void clear ()
      {
        // User destructor.
        symbol_number_type yytype = this->type_get ();
        basic_symbol<Base>& yysym = *this;
        (void) yysym;
        switch (yytype)
        {
       default:
          break;
        }

        // Type destructor.
switch (yytype)
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
        value.template destroy< EzAquarii::ASTNode > ();
        break;

      case 3: // ID
      case 4: // INT_VALUE
      case 5: // FLOAT_VALUE
        value.template destroy< std::string > ();
        break;

      default:
        break;
    }

        Base::clear ();
      }

      /// Whether empty.
      bool empty () const YY_NOEXCEPT;

      /// Destructive move, \a s is emptied into this.
      void move (basic_symbol& s);

      /// The semantic value.
      semantic_type value;

      /// The location.
      location_type location;

    private:
#if YY_CPLUSPLUS < 201103L
      /// Assignment operator.
      basic_symbol& operator= (const basic_symbol& that);
#endif
    };

    /// Type access provider for token (enum) based symbols.
    struct by_type
    {
      /// Default constructor.
      by_type ();

#if 201103L <= YY_CPLUSPLUS
      /// Move constructor.
      by_type (by_type&& that);
#endif

      /// Copy constructor.
      by_type (const by_type& that);

      /// The symbol type as needed by the constructor.
      typedef token_type kind_type;

      /// Constructor from (external) token numbers.
      by_type (kind_type t);

      /// Record that this symbol is empty.
      void clear ();

      /// Steal the symbol type from \a that.
      void move (by_type& that);

      /// The (internal) type number (corresponding to \a type).
      /// \a empty when empty.
      symbol_number_type type_get () const YY_NOEXCEPT;

      /// The token.
      token_type token () const YY_NOEXCEPT;

      /// The symbol type.
      /// \a empty_symbol when empty.
      /// An int, not token_number_type, to be able to store empty_symbol.
      int type;
    };

    /// "External" symbols: returned by the scanner.
    struct symbol_type : basic_symbol<by_type>
    {
      /// Superclass.
      typedef basic_symbol<by_type> super_type;

      /// Empty symbol.
      symbol_type () {}

      /// Constructor for valueless symbols, and symbols from each type.
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, location_type l)
        : super_type(token_type (tok), std::move (l))
      {
        YYASSERT (tok == token::TOKEN_END || tok == token::TOKEN_INT || tok == token::TOKEN_FLOAT || tok == token::TOKEN_CHAR || tok == token::TOKEN_BREAK || tok == token::TOKEN_WHILE || tok == token::TOKEN_CONTINUE || tok == token::TOKEN_IF || tok == token::TOKEN_ELSE || tok == token::TOKEN_RETURN || tok == token::TOKEN_FOR || tok == token::TOKEN_SWITCH || tok == token::TOKEN_CASE || tok == token::TOKEN_DEFAULT || tok == token::TOKEN_ADD_ASSIGN || tok == token::TOKEN_SUB_ASSIGN || tok == token::TOKEN_MUL_ASSIGN || tok == token::TOKEN_DIV_ASSIGN || tok == token::TOKEN_MOD_ASSIGN || tok == token::TOKEN_INC_OP || tok == token::TOKEN_DEC_OP || tok == token::TOKEN_AT || tok == token::TOKEN_LT || tok == token::TOKEN_AE || tok == token::TOKEN_LE || tok == token::TOKEN_EQ || tok == token::TOKEN_NE || tok == token::TOKEN_AND || tok == token::TOKEN_OR || tok == token::TOKEN_ASSIGN || tok == token::TOKEN_PLUS_OP || tok == token::TOKEN_MINUS_OP || tok == token::TOKEN_DIV_OP || tok == token::TOKEN_STAR_OP || tok == token::TOKEN_MOD_OP || tok == token::TOKEN_AND_OP || tok == token::TOKEN_OR_OP || tok == token::TOKEN_XOR_OP || tok == token::TOKEN_COMMA || tok == token::TOKEN_LP || tok == token::TOKEN_RP || tok == token::TOKEN_LB || tok == token::TOKEN_RB || tok == token::TOKEN_LC || tok == token::TOKEN_RC || tok == token::TOKEN_COLON || tok == token::TOKEN_SEMMI || tok == token::TOKEN_LOWER_THAN_ELSE);
      }
#else
      symbol_type (int tok, const location_type& l)
        : super_type(token_type (tok), l)
      {
        YYASSERT (tok == token::TOKEN_END || tok == token::TOKEN_INT || tok == token::TOKEN_FLOAT || tok == token::TOKEN_CHAR || tok == token::TOKEN_BREAK || tok == token::TOKEN_WHILE || tok == token::TOKEN_CONTINUE || tok == token::TOKEN_IF || tok == token::TOKEN_ELSE || tok == token::TOKEN_RETURN || tok == token::TOKEN_FOR || tok == token::TOKEN_SWITCH || tok == token::TOKEN_CASE || tok == token::TOKEN_DEFAULT || tok == token::TOKEN_ADD_ASSIGN || tok == token::TOKEN_SUB_ASSIGN || tok == token::TOKEN_MUL_ASSIGN || tok == token::TOKEN_DIV_ASSIGN || tok == token::TOKEN_MOD_ASSIGN || tok == token::TOKEN_INC_OP || tok == token::TOKEN_DEC_OP || tok == token::TOKEN_AT || tok == token::TOKEN_LT || tok == token::TOKEN_AE || tok == token::TOKEN_LE || tok == token::TOKEN_EQ || tok == token::TOKEN_NE || tok == token::TOKEN_AND || tok == token::TOKEN_OR || tok == token::TOKEN_ASSIGN || tok == token::TOKEN_PLUS_OP || tok == token::TOKEN_MINUS_OP || tok == token::TOKEN_DIV_OP || tok == token::TOKEN_STAR_OP || tok == token::TOKEN_MOD_OP || tok == token::TOKEN_AND_OP || tok == token::TOKEN_OR_OP || tok == token::TOKEN_XOR_OP || tok == token::TOKEN_COMMA || tok == token::TOKEN_LP || tok == token::TOKEN_RP || tok == token::TOKEN_LB || tok == token::TOKEN_RB || tok == token::TOKEN_LC || tok == token::TOKEN_RC || tok == token::TOKEN_COLON || tok == token::TOKEN_SEMMI || tok == token::TOKEN_LOWER_THAN_ELSE);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, std::string v, location_type l)
        : super_type(token_type (tok), std::move (v), std::move (l))
      {
        YYASSERT (tok == token::TOKEN_ID || tok == token::TOKEN_INT_VALUE || tok == token::TOKEN_FLOAT_VALUE);
      }
#else
      symbol_type (int tok, const std::string& v, const location_type& l)
        : super_type(token_type (tok), v, l)
      {
        YYASSERT (tok == token::TOKEN_ID || tok == token::TOKEN_INT_VALUE || tok == token::TOKEN_FLOAT_VALUE);
      }
#endif
    };

    /// Build a parser object.
     Parser  (EzAquarii::Scanner &scanner_yyarg, EzAquarii::Interpreter &driver_yyarg);
    virtual ~ Parser  ();

    /// Parse.  An alias for parse ().
    /// \returns  0 iff parsing succeeded.
    int operator() ();

    /// Parse.
    /// \returns  0 iff parsing succeeded.
    virtual int parse ();

#if YYDEBUG
    /// The current debugging stream.
    std::ostream& debug_stream () const YY_ATTRIBUTE_PURE;
    /// Set the current debugging stream.
    void set_debug_stream (std::ostream &);

    /// Type for debugging levels.
    typedef int debug_level_type;
    /// The current debugging level.
    debug_level_type debug_level () const YY_ATTRIBUTE_PURE;
    /// Set the current debugging level.
    void set_debug_level (debug_level_type l);
#endif

    /// Report a syntax error.
    /// \param loc    where the syntax error is found.
    /// \param msg    a description of the syntax error.
    virtual void error (const location_type& loc, const std::string& msg);

    /// Report a syntax error.
    void error (const syntax_error& err);

    // Implementation of make_symbol for each symbol type.
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_END (location_type l)
      {
        return symbol_type (token::TOKEN_END, std::move (l));
      }
#else
      static
      symbol_type
      make_END (const location_type& l)
      {
        return symbol_type (token::TOKEN_END, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ID (std::string v, location_type l)
      {
        return symbol_type (token::TOKEN_ID, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_ID (const std::string& v, const location_type& l)
      {
        return symbol_type (token::TOKEN_ID, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_INT_VALUE (std::string v, location_type l)
      {
        return symbol_type (token::TOKEN_INT_VALUE, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_INT_VALUE (const std::string& v, const location_type& l)
      {
        return symbol_type (token::TOKEN_INT_VALUE, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_FLOAT_VALUE (std::string v, location_type l)
      {
        return symbol_type (token::TOKEN_FLOAT_VALUE, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_FLOAT_VALUE (const std::string& v, const location_type& l)
      {
        return symbol_type (token::TOKEN_FLOAT_VALUE, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_INT (location_type l)
      {
        return symbol_type (token::TOKEN_INT, std::move (l));
      }
#else
      static
      symbol_type
      make_INT (const location_type& l)
      {
        return symbol_type (token::TOKEN_INT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_FLOAT (location_type l)
      {
        return symbol_type (token::TOKEN_FLOAT, std::move (l));
      }
#else
      static
      symbol_type
      make_FLOAT (const location_type& l)
      {
        return symbol_type (token::TOKEN_FLOAT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CHAR (location_type l)
      {
        return symbol_type (token::TOKEN_CHAR, std::move (l));
      }
#else
      static
      symbol_type
      make_CHAR (const location_type& l)
      {
        return symbol_type (token::TOKEN_CHAR, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_BREAK (location_type l)
      {
        return symbol_type (token::TOKEN_BREAK, std::move (l));
      }
#else
      static
      symbol_type
      make_BREAK (const location_type& l)
      {
        return symbol_type (token::TOKEN_BREAK, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_WHILE (location_type l)
      {
        return symbol_type (token::TOKEN_WHILE, std::move (l));
      }
#else
      static
      symbol_type
      make_WHILE (const location_type& l)
      {
        return symbol_type (token::TOKEN_WHILE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CONTINUE (location_type l)
      {
        return symbol_type (token::TOKEN_CONTINUE, std::move (l));
      }
#else
      static
      symbol_type
      make_CONTINUE (const location_type& l)
      {
        return symbol_type (token::TOKEN_CONTINUE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_IF (location_type l)
      {
        return symbol_type (token::TOKEN_IF, std::move (l));
      }
#else
      static
      symbol_type
      make_IF (const location_type& l)
      {
        return symbol_type (token::TOKEN_IF, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ELSE (location_type l)
      {
        return symbol_type (token::TOKEN_ELSE, std::move (l));
      }
#else
      static
      symbol_type
      make_ELSE (const location_type& l)
      {
        return symbol_type (token::TOKEN_ELSE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RETURN (location_type l)
      {
        return symbol_type (token::TOKEN_RETURN, std::move (l));
      }
#else
      static
      symbol_type
      make_RETURN (const location_type& l)
      {
        return symbol_type (token::TOKEN_RETURN, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_FOR (location_type l)
      {
        return symbol_type (token::TOKEN_FOR, std::move (l));
      }
#else
      static
      symbol_type
      make_FOR (const location_type& l)
      {
        return symbol_type (token::TOKEN_FOR, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SWITCH (location_type l)
      {
        return symbol_type (token::TOKEN_SWITCH, std::move (l));
      }
#else
      static
      symbol_type
      make_SWITCH (const location_type& l)
      {
        return symbol_type (token::TOKEN_SWITCH, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CASE (location_type l)
      {
        return symbol_type (token::TOKEN_CASE, std::move (l));
      }
#else
      static
      symbol_type
      make_CASE (const location_type& l)
      {
        return symbol_type (token::TOKEN_CASE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DEFAULT (location_type l)
      {
        return symbol_type (token::TOKEN_DEFAULT, std::move (l));
      }
#else
      static
      symbol_type
      make_DEFAULT (const location_type& l)
      {
        return symbol_type (token::TOKEN_DEFAULT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ADD_ASSIGN (location_type l)
      {
        return symbol_type (token::TOKEN_ADD_ASSIGN, std::move (l));
      }
#else
      static
      symbol_type
      make_ADD_ASSIGN (const location_type& l)
      {
        return symbol_type (token::TOKEN_ADD_ASSIGN, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SUB_ASSIGN (location_type l)
      {
        return symbol_type (token::TOKEN_SUB_ASSIGN, std::move (l));
      }
#else
      static
      symbol_type
      make_SUB_ASSIGN (const location_type& l)
      {
        return symbol_type (token::TOKEN_SUB_ASSIGN, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_MUL_ASSIGN (location_type l)
      {
        return symbol_type (token::TOKEN_MUL_ASSIGN, std::move (l));
      }
#else
      static
      symbol_type
      make_MUL_ASSIGN (const location_type& l)
      {
        return symbol_type (token::TOKEN_MUL_ASSIGN, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DIV_ASSIGN (location_type l)
      {
        return symbol_type (token::TOKEN_DIV_ASSIGN, std::move (l));
      }
#else
      static
      symbol_type
      make_DIV_ASSIGN (const location_type& l)
      {
        return symbol_type (token::TOKEN_DIV_ASSIGN, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_MOD_ASSIGN (location_type l)
      {
        return symbol_type (token::TOKEN_MOD_ASSIGN, std::move (l));
      }
#else
      static
      symbol_type
      make_MOD_ASSIGN (const location_type& l)
      {
        return symbol_type (token::TOKEN_MOD_ASSIGN, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_INC_OP (location_type l)
      {
        return symbol_type (token::TOKEN_INC_OP, std::move (l));
      }
#else
      static
      symbol_type
      make_INC_OP (const location_type& l)
      {
        return symbol_type (token::TOKEN_INC_OP, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DEC_OP (location_type l)
      {
        return symbol_type (token::TOKEN_DEC_OP, std::move (l));
      }
#else
      static
      symbol_type
      make_DEC_OP (const location_type& l)
      {
        return symbol_type (token::TOKEN_DEC_OP, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_AT (location_type l)
      {
        return symbol_type (token::TOKEN_AT, std::move (l));
      }
#else
      static
      symbol_type
      make_AT (const location_type& l)
      {
        return symbol_type (token::TOKEN_AT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LT (location_type l)
      {
        return symbol_type (token::TOKEN_LT, std::move (l));
      }
#else
      static
      symbol_type
      make_LT (const location_type& l)
      {
        return symbol_type (token::TOKEN_LT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_AE (location_type l)
      {
        return symbol_type (token::TOKEN_AE, std::move (l));
      }
#else
      static
      symbol_type
      make_AE (const location_type& l)
      {
        return symbol_type (token::TOKEN_AE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LE (location_type l)
      {
        return symbol_type (token::TOKEN_LE, std::move (l));
      }
#else
      static
      symbol_type
      make_LE (const location_type& l)
      {
        return symbol_type (token::TOKEN_LE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_EQ (location_type l)
      {
        return symbol_type (token::TOKEN_EQ, std::move (l));
      }
#else
      static
      symbol_type
      make_EQ (const location_type& l)
      {
        return symbol_type (token::TOKEN_EQ, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_NE (location_type l)
      {
        return symbol_type (token::TOKEN_NE, std::move (l));
      }
#else
      static
      symbol_type
      make_NE (const location_type& l)
      {
        return symbol_type (token::TOKEN_NE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_AND (location_type l)
      {
        return symbol_type (token::TOKEN_AND, std::move (l));
      }
#else
      static
      symbol_type
      make_AND (const location_type& l)
      {
        return symbol_type (token::TOKEN_AND, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_OR (location_type l)
      {
        return symbol_type (token::TOKEN_OR, std::move (l));
      }
#else
      static
      symbol_type
      make_OR (const location_type& l)
      {
        return symbol_type (token::TOKEN_OR, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ASSIGN (location_type l)
      {
        return symbol_type (token::TOKEN_ASSIGN, std::move (l));
      }
#else
      static
      symbol_type
      make_ASSIGN (const location_type& l)
      {
        return symbol_type (token::TOKEN_ASSIGN, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_PLUS_OP (location_type l)
      {
        return symbol_type (token::TOKEN_PLUS_OP, std::move (l));
      }
#else
      static
      symbol_type
      make_PLUS_OP (const location_type& l)
      {
        return symbol_type (token::TOKEN_PLUS_OP, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_MINUS_OP (location_type l)
      {
        return symbol_type (token::TOKEN_MINUS_OP, std::move (l));
      }
#else
      static
      symbol_type
      make_MINUS_OP (const location_type& l)
      {
        return symbol_type (token::TOKEN_MINUS_OP, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DIV_OP (location_type l)
      {
        return symbol_type (token::TOKEN_DIV_OP, std::move (l));
      }
#else
      static
      symbol_type
      make_DIV_OP (const location_type& l)
      {
        return symbol_type (token::TOKEN_DIV_OP, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_STAR_OP (location_type l)
      {
        return symbol_type (token::TOKEN_STAR_OP, std::move (l));
      }
#else
      static
      symbol_type
      make_STAR_OP (const location_type& l)
      {
        return symbol_type (token::TOKEN_STAR_OP, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_MOD_OP (location_type l)
      {
        return symbol_type (token::TOKEN_MOD_OP, std::move (l));
      }
#else
      static
      symbol_type
      make_MOD_OP (const location_type& l)
      {
        return symbol_type (token::TOKEN_MOD_OP, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_AND_OP (location_type l)
      {
        return symbol_type (token::TOKEN_AND_OP, std::move (l));
      }
#else
      static
      symbol_type
      make_AND_OP (const location_type& l)
      {
        return symbol_type (token::TOKEN_AND_OP, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_OR_OP (location_type l)
      {
        return symbol_type (token::TOKEN_OR_OP, std::move (l));
      }
#else
      static
      symbol_type
      make_OR_OP (const location_type& l)
      {
        return symbol_type (token::TOKEN_OR_OP, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_XOR_OP (location_type l)
      {
        return symbol_type (token::TOKEN_XOR_OP, std::move (l));
      }
#else
      static
      symbol_type
      make_XOR_OP (const location_type& l)
      {
        return symbol_type (token::TOKEN_XOR_OP, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_COMMA (location_type l)
      {
        return symbol_type (token::TOKEN_COMMA, std::move (l));
      }
#else
      static
      symbol_type
      make_COMMA (const location_type& l)
      {
        return symbol_type (token::TOKEN_COMMA, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LP (location_type l)
      {
        return symbol_type (token::TOKEN_LP, std::move (l));
      }
#else
      static
      symbol_type
      make_LP (const location_type& l)
      {
        return symbol_type (token::TOKEN_LP, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RP (location_type l)
      {
        return symbol_type (token::TOKEN_RP, std::move (l));
      }
#else
      static
      symbol_type
      make_RP (const location_type& l)
      {
        return symbol_type (token::TOKEN_RP, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LB (location_type l)
      {
        return symbol_type (token::TOKEN_LB, std::move (l));
      }
#else
      static
      symbol_type
      make_LB (const location_type& l)
      {
        return symbol_type (token::TOKEN_LB, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RB (location_type l)
      {
        return symbol_type (token::TOKEN_RB, std::move (l));
      }
#else
      static
      symbol_type
      make_RB (const location_type& l)
      {
        return symbol_type (token::TOKEN_RB, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LC (location_type l)
      {
        return symbol_type (token::TOKEN_LC, std::move (l));
      }
#else
      static
      symbol_type
      make_LC (const location_type& l)
      {
        return symbol_type (token::TOKEN_LC, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RC (location_type l)
      {
        return symbol_type (token::TOKEN_RC, std::move (l));
      }
#else
      static
      symbol_type
      make_RC (const location_type& l)
      {
        return symbol_type (token::TOKEN_RC, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_COLON (location_type l)
      {
        return symbol_type (token::TOKEN_COLON, std::move (l));
      }
#else
      static
      symbol_type
      make_COLON (const location_type& l)
      {
        return symbol_type (token::TOKEN_COLON, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SEMMI (location_type l)
      {
        return symbol_type (token::TOKEN_SEMMI, std::move (l));
      }
#else
      static
      symbol_type
      make_SEMMI (const location_type& l)
      {
        return symbol_type (token::TOKEN_SEMMI, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LOWER_THAN_ELSE (location_type l)
      {
        return symbol_type (token::TOKEN_LOWER_THAN_ELSE, std::move (l));
      }
#else
      static
      symbol_type
      make_LOWER_THAN_ELSE (const location_type& l)
      {
        return symbol_type (token::TOKEN_LOWER_THAN_ELSE, l);
      }
#endif


  private:
    /// This class is not copyable.
     Parser  (const  Parser &);
     Parser & operator= (const  Parser &);

    /// State numbers.
    typedef int state_type;

    /// Generate an error message.
    /// \param yystate   the state where the error occurred.
    /// \param yyla      the lookahead token.
    virtual std::string yysyntax_error_ (state_type yystate,
                                         const symbol_type& yyla) const;

    /// Compute post-reduction state.
    /// \param yystate   the current state
    /// \param yysym     the nonterminal to push on the stack
    state_type yy_lr_goto_state_ (state_type yystate, int yysym);

    /// Whether the given \c yypact_ value indicates a defaulted state.
    /// \param yyvalue   the value to check
    static bool yy_pact_value_is_default_ (int yyvalue);

    /// Whether the given \c yytable_ value indicates a syntax error.
    /// \param yyvalue   the value to check
    static bool yy_table_value_is_error_ (int yyvalue);

    static const signed char yypact_ninf_;
    static const signed char yytable_ninf_;

    /// Convert a scanner token number \a t to a symbol number.
    static token_number_type yytranslate_ (token_type t);

    // Tables.
  // YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
  // STATE-NUM.
  static const short yypact_[];

  // YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
  // Performed when YYTABLE does not specify something else to do.  Zero
  // means the default is an error.
  static const unsigned char yydefact_[];

  // YYPGOTO[NTERM-NUM].
  static const short yypgoto_[];

  // YYDEFGOTO[NTERM-NUM].
  static const short yydefgoto_[];

  // YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
  // positive, shift that token.  If negative, reduce the rule whose
  // number is the opposite.  If YYTABLE_NINF, syntax error.
  static const unsigned char yytable_[];

  static const short yycheck_[];

  // YYSTOS[STATE-NUM] -- The (internal number of the) accessing
  // symbol of state STATE-NUM.
  static const unsigned char yystos_[];

  // YYR1[YYN] -- Symbol number of symbol that rule YYN derives.
  static const unsigned char yyr1_[];

  // YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.
  static const unsigned char yyr2_[];


    /// Convert the symbol name \a n to a form suitable for a diagnostic.
    static std::string yytnamerr_ (const char *n);


    /// For a symbol, its name in clear.
    static const char* const yytname_[];
#if YYDEBUG
  // YYRLINE[YYN] -- Source line where rule number YYN was defined.
  static const unsigned short yyrline_[];
    /// Report on the debug stream that the rule \a r is going to be reduced.
    virtual void yy_reduce_print_ (int r);
    /// Print the state stack on the debug stream.
    virtual void yystack_print_ ();

    /// Debugging level.
    int yydebug_;
    /// Debug stream.
    std::ostream* yycdebug_;

    /// \brief Display a symbol type, value and location.
    /// \param yyo    The output stream.
    /// \param yysym  The symbol.
    template <typename Base>
    void yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const;
#endif

    /// \brief Reclaim the memory associated to a symbol.
    /// \param yymsg     Why this token is reclaimed.
    ///                  If null, print nothing.
    /// \param yysym     The symbol.
    template <typename Base>
    void yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const;

  private:
    /// Type access provider for state based symbols.
    struct by_state
    {
      /// Default constructor.
      by_state () YY_NOEXCEPT;

      /// The symbol type as needed by the constructor.
      typedef state_type kind_type;

      /// Constructor.
      by_state (kind_type s) YY_NOEXCEPT;

      /// Copy constructor.
      by_state (const by_state& that) YY_NOEXCEPT;

      /// Record that this symbol is empty.
      void clear () YY_NOEXCEPT;

      /// Steal the symbol type from \a that.
      void move (by_state& that);

      /// The (internal) type number (corresponding to \a state).
      /// \a empty_symbol when empty.
      symbol_number_type type_get () const YY_NOEXCEPT;

      /// The state number used to denote an empty symbol.
      enum { empty_state = -1 };

      /// The state.
      /// \a empty when empty.
      state_type state;
    };

    /// "Internal" symbol: element of the stack.
    struct stack_symbol_type : basic_symbol<by_state>
    {
      /// Superclass.
      typedef basic_symbol<by_state> super_type;
      /// Construct an empty symbol.
      stack_symbol_type ();
      /// Move or copy construction.
      stack_symbol_type (YY_RVREF (stack_symbol_type) that);
      /// Steal the contents from \a sym to build this.
      stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) sym);
#if YY_CPLUSPLUS < 201103L
      /// Assignment, needed by push_back by some old implementations.
      /// Moves the contents of that.
      stack_symbol_type& operator= (stack_symbol_type& that);
#endif
    };

    /// A stack with random access from its top.
    template <typename T, typename S = std::vector<T> >
    class stack
    {
    public:
      // Hide our reversed order.
      typedef typename S::reverse_iterator iterator;
      typedef typename S::const_reverse_iterator const_iterator;
      typedef typename S::size_type size_type;

      stack (size_type n = 200)
        : seq_ (n)
      {}

      /// Random access.
      ///
      /// Index 0 returns the topmost element.
      T&
      operator[] (size_type i)
      {
        return seq_[size () - 1 - i];
      }

      /// Random access.
      ///
      /// Index 0 returns the topmost element.
      T&
      operator[] (int i)
      {
        return operator[] (size_type (i));
      }

      /// Random access.
      ///
      /// Index 0 returns the topmost element.
      const T&
      operator[] (size_type i) const
      {
        return seq_[size () - 1 - i];
      }

      /// Random access.
      ///
      /// Index 0 returns the topmost element.
      const T&
      operator[] (int i) const
      {
        return operator[] (size_type (i));
      }

      /// Steal the contents of \a t.
      ///
      /// Close to move-semantics.
      void
      push (YY_MOVE_REF (T) t)
      {
        seq_.push_back (T ());
        operator[] (0).move (t);
      }

      /// Pop elements from the stack.
      void
      pop (int n = 1) YY_NOEXCEPT
      {
        for (; 0 < n; --n)
          seq_.pop_back ();
      }

      /// Pop all elements from the stack.
      void
      clear () YY_NOEXCEPT
      {
        seq_.clear ();
      }

      /// Number of elements on the stack.
      size_type
      size () const YY_NOEXCEPT
      {
        return seq_.size ();
      }

      /// Iterator on top of the stack (going downwards).
      const_iterator
      begin () const YY_NOEXCEPT
      {
        return seq_.rbegin ();
      }

      /// Bottom of the stack.
      const_iterator
      end () const YY_NOEXCEPT
      {
        return seq_.rend ();
      }

      /// Present a slice of the top of a stack.
      class slice
      {
      public:
        slice (const stack& stack, int range)
          : stack_ (stack)
          , range_ (range)
        {}

        const T&
        operator[] (int i) const
        {
          return stack_[range_ - i];
        }

      private:
        const stack& stack_;
        int range_;
      };

    private:
      stack (const stack&);
      stack& operator= (const stack&);
      /// The wrapped container.
      S seq_;
    };


    /// Stack type.
    typedef stack<stack_symbol_type> stack_type;

    /// The stack.
    stack_type yystack_;

    /// Push a new state on the stack.
    /// \param m    a debug message to display
    ///             if null, no trace is output.
    /// \param sym  the symbol
    /// \warning the contents of \a s.value is stolen.
    void yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym);

    /// Push a new look ahead token on the state on the stack.
    /// \param m    a debug message to display
    ///             if null, no trace is output.
    /// \param s    the state
    /// \param sym  the symbol (for its value and location).
    /// \warning the contents of \a sym.value is stolen.
    void yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym);

    /// Pop \a n symbols from the stack.
    void yypop_ (int n = 1);

    /// Constants.
    enum
    {
      yyeof_ = 0,
      yylast_ = 515,     ///< Last index in yytable_.
      yynnts_ = 49,  ///< Number of nonterminal symbols.
      yyfinal_ = 11, ///< Termination state number.
      yyterror_ = 1,
      yyerrcode_ = 256,
      yyntokens_ = 53  ///< Number of tokens.
    };


    // User arguments.
    EzAquarii::Scanner &scanner;
    EzAquarii::Interpreter &driver;
  };

  inline
   Parser ::token_number_type
   Parser ::yytranslate_ (token_type t)
  {
    // YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to
    // TOKEN-NUM as returned by yylex.
    static
    const token_number_type
    translate_table[] =
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
      45,    46,    47,    48,    49,    50,    51,    52
    };
    const unsigned user_token_number_max_ = 307;
    const token_number_type undef_token_ = 2;

    if (static_cast<int> (t) <= yyeof_)
      return yyeof_;
    else if (static_cast<unsigned> (t) <= user_token_number_max_)
      return translate_table[t];
    else
      return undef_token_;
  }

  // basic_symbol.
#if 201103L <= YY_CPLUSPLUS
  template <typename Base>
   Parser ::basic_symbol<Base>::basic_symbol (basic_symbol&& that)
    : Base (std::move (that))
    , value ()
    , location (std::move (that.location))
  {
    switch (this->type_get ())
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
        value.move< EzAquarii::ASTNode > (std::move (that.value));
        break;

      case 3: // ID
      case 4: // INT_VALUE
      case 5: // FLOAT_VALUE
        value.move< std::string > (std::move (that.value));
        break;

      default:
        break;
    }

  }
#endif

  template <typename Base>
   Parser ::basic_symbol<Base>::basic_symbol (const basic_symbol& that)
    : Base (that)
    , value ()
    , location (that.location)
  {
    switch (this->type_get ())
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
        value.copy< EzAquarii::ASTNode > (YY_MOVE (that.value));
        break;

      case 3: // ID
      case 4: // INT_VALUE
      case 5: // FLOAT_VALUE
        value.copy< std::string > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

  }



  template <typename Base>
  bool
   Parser ::basic_symbol<Base>::empty () const YY_NOEXCEPT
  {
    return Base::type_get () == empty_symbol;
  }

  template <typename Base>
  void
   Parser ::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move (s);
    switch (this->type_get ())
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
        value.move< EzAquarii::ASTNode > (YY_MOVE (s.value));
        break;

      case 3: // ID
      case 4: // INT_VALUE
      case 5: // FLOAT_VALUE
        value.move< std::string > (YY_MOVE (s.value));
        break;

      default:
        break;
    }

    location = YY_MOVE (s.location);
  }

  // by_type.
  inline
   Parser ::by_type::by_type ()
    : type (empty_symbol)
  {}

#if 201103L <= YY_CPLUSPLUS
  inline
   Parser ::by_type::by_type (by_type&& that)
    : type (that.type)
  {
    that.clear ();
  }
#endif

  inline
   Parser ::by_type::by_type (const by_type& that)
    : type (that.type)
  {}

  inline
   Parser ::by_type::by_type (token_type t)
    : type (yytranslate_ (t))
  {}

  inline
  void
   Parser ::by_type::clear ()
  {
    type = empty_symbol;
  }

  inline
  void
   Parser ::by_type::move (by_type& that)
  {
    type = that.type;
    that.clear ();
  }

  inline
  int
   Parser ::by_type::type_get () const YY_NOEXCEPT
  {
    return type;
  }

  inline
   Parser ::token_type
   Parser ::by_type::token () const YY_NOEXCEPT
  {
    // YYTOKNUM[NUM] -- (External) token number corresponding to the
    // (internal) symbol number NUM (which must be that of a token).  */
    static
    const unsigned short
    yytoken_number_[] =
    {
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307
    };
    return token_type (yytoken_number_[type]);
  }

#line 37 "parser.y"
} //  EzAquarii 
#line 2265 "parser.hpp"





#endif // !YY_YY_PARSER_HPP_INCLUDED
