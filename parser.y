/*
 * The MIT License (MIT)
 * 
 * Copyright (c) 2014 Krzysztof Narkiewicz <krzysztof.narkiewicz@ezaquarii.com>
 * 
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 * 
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 * 
 */

%skeleton "lalr1.cc" /* -*- C++ -*- */
%require "3.0"
%defines
%define api.parser.class { Parser }

%define api.token.constructor
%define api.value.type variant
%define parse.assert
%define api.namespace { EzAquarii }
%code requires
{
    #include <iostream>
    #include <string>
    #include <vector>
    #include <stdint.h>
    #include "command.h"
    #include "symbol.h"
    #include "analysis.h"

    using namespace std;

    namespace EzAquarii {
        class Scanner;
        class Interpreter;
    }
}

// Bison calls yylex() function that must be provided by us to suck tokens
// from the scanner. This block will be placed at the beginning of IMPLEMENTATION file (cpp).
// We define this function here (function! not method).
// This function is called only inside Bison, so we make it static to limit symbol visibility for the linker
// to avoid potential linking conflicts.
%code top
{
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
}

%lex-param { EzAquarii::Scanner &scanner }
%lex-param { EzAquarii::Interpreter &driver }
%parse-param { EzAquarii::Scanner &scanner }
%parse-param { EzAquarii::Interpreter &driver }
%locations
%define parse.trace
%define parse.error verbose

%define api.token.prefix {TOKEN_}

%token END 0 "end of file"
%token <std::string> ID  ;
%token <std::string> INT_VALUE ;
%token <std::string> FLOAT_VALUE ;
%token INT FLOAT CHAR BREAK WHILE CONTINUE IF ELSE RETURN FOR SWITCH CASE DEFAULT /* 关键字*/
%token ADD_ASSIGN SUB_ASSIGN MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN INC_OP DEC_OP /* 复合赋值符、自增自减符*/
%token AT LT AE LE EQ NE AND OR /* 大于、小于、大于等于、小于等于、等于、不等于、与、或*/
%token ASSIGN PLUS_OP MINUS_OP DIV_OP STAR_OP MOD_OP AND_OP OR_OP XOR_OP/* 赋值符、加减乘除运算符*/
%token COMMA LP RP LB RB LC RC COLON SEMMI /* 逗号，P小括弧B中括弧C大括弧，分号*/

%type <EzAquarii::ASTNode> program  translation_unit
%type <EzAquarii::ASTNode> external_declaration function_definition declaration declarator direct_declarator statement_list
%type <EzAquarii::ASTNode> declaration_specifiers type_specifier constant expression init_declarator_list parameter_declaration
%type <EzAquarii::ASTNode> compound_statement primary_expression declaration_list identifier_list parameter_type_list
%type <EzAquarii::ASTNode> init_declarator initializer initializer_list unary_operator multiplicative_expression
%type <EzAquarii::ASTNode> postfix_expression argument_expression_list unary_expression cast_expression parameter_list
%type <EzAquarii::ASTNode> additive_expression shift_expression relational_expression equality_expression and_expression
%type <EzAquarii::ASTNode> exclusive_or_expression inclusive_or_expression logical_and_expression logical_or_expression
%type <EzAquarii::ASTNode> conditional_expression assignment_expression assignment_operator constant_expression statement
%type <EzAquarii::ASTNode> labeled_statement selection_statement iteration_statement jump_statement expression_statement

%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE

%%

program:
    translation_unit
        {$$ = ASTNode("program"); $$.nodes = $1.nodes; $$.display();
        cout << "there are totally " <<driver.location() << "chars in this program" << endl;
        passRoot($$);}
    ;

translation_unit:
    external_declaration
        {$$ = ASTNode("translation_unit"); $$.addNode($1);} |
    translation_unit external_declaration
        {$$ = $1; $$.addNode($2);}
    ;

external_declaration:
	declaration 
        {$$ = ASTNode("external_declaration"); $$.addNode($1);}|
	function_definition 
        {$$ = ASTNode("external_declaration"); $$.addNode($1);}
	;

declaration:
    declaration_specifiers SEMMI 
        {$$ = ASTNode("declaration"); $$.addNode($1)/*.addNode(ASTNode("SEMMI", ";"))*/;}|
    declaration_specifiers init_declarator_list SEMMI 
        {$$ = ASTNode("declaration"); $$.addNode($1).addNode($2)/*.addNode(ASTNode("SEMMI", ";"))*/;}
    ;

declaration_list:
	declaration 
        {$$ = ASTNode("declaration_list"); $$.addNode($1);}|
	declaration_list declaration
        {$$ = $1; $$.addNode($2);}
    ;

init_declarator_list:
    init_declarator {$$ = ASTNode("init_declarator_list"); $$.addNode($1);}|
	init_declarator_list COMMA init_declarator
        {$$ = $1; $$/*.addNode(ASTNode("COMMA", ","))*/.addNode($3);}
	;

init_declarator:
	declarator {$$ = $1;}|
	declarator ASSIGN initializer
        {$$ = $1; $$.addNode(ASTNode("ASSIGN", "=")).addNode($3);}
	;

initializer: 
    assignment_expression {$$ = ASTNode("initializer"); $$.nodes = $1.nodes;}|
	LC initializer_list RC
        {$$ = ASTNode("initializer"); $$.addNode(ASTNode("LC", "{")).addNode($2).addNode(ASTNode("RC", "}"));}|
	LC initializer_list COMMA RC
        {$$ = ASTNode("initializer"); $$.addNode(ASTNode("LC", "{")).addNode($2).addNode(ASTNode("RC", "}"));}
	;

initializer_list: 
    initializer {$$ = ASTNode("initializer_list"); $$.addNode($1);}|
        initializer_list COMMA initializer
        {$$ = $1; $$.addNode($3);}
	;

declarator:
    direct_declarator {$$ = ASTNode("declarator", $1.value); /*$$.addNode($1);*/ $$.nodes = $1.nodes;}
    ;

function_definition:
    declaration_specifiers declarator declaration_list compound_statement 
        {$$ = ASTNode("function_definition"); $$.addNode($1).addNode($2).addNode($3).addNode($4);}|
    declaration_specifiers declarator compound_statement 
        {$$ = ASTNode("function_definition"); $$.addNode($1).addNode($2).addNode($3);}
    ;

declaration_specifiers:
    type_specifier {$$ = $1;}
    ;

type_specifier:
    INT {$$ = ASTNode("type_specifier"); $$.addNode(ASTNode("INT", "int"));}|
    FLOAT {$$ = ASTNode("type_specifier"); $$.addNode(ASTNode("FLOAT", "float"));}|
    CHAR {$$ = ASTNode("type_specifier"); $$.addNode(ASTNode("CHAR", "char"));}
    ;

direct_declarator:
    /*将声明符是变量还是函数还是数组的信息存放在declarator的value中*/
    ID 
        {$$ = ASTNode("direct_declarator", "variable"); $$.addNode(ASTNode("ID", $1));}|
    LP declarator RP
        {$$ = ASTNode("direct_declarator"); 
        $$.addNode(ASTNode("LP", "(")).addNode($2).addNode(ASTNode("RP", ")"));} |
        direct_declarator LB constant_expression RB
        {$$ = ASTNode("direct_declarator", "array"); $$.nodes = $1.nodes;/*这里的nodes应该是ID*/
        $$.addNode($3);} |
        direct_declarator LB RB
        {$$ = ASTNode("direct_declarator", "array"); $$.nodes = $1.nodes;/*这里的nodes应该是ID*/
        $$.addNode(ASTNode("LB", "[")).addNode(ASTNode("RB", "]"));} |
	direct_declarator LP parameter_type_list RP
        {$$ = ASTNode("direct_declarator", "function"); $$.nodes = $1.nodes;/*这里的nodes应该是ID*/
        $$.addNode(ASTNode("LP", "(")).addNode($3).addNode(ASTNode("RP", ")"));} |
	direct_declarator LP identifier_list RP
        {$$ = ASTNode("direct_declarator", "function"); $$.nodes = $1.nodes;/*这里的nodes应该是ID*/
        $$.addNode(ASTNode("LP", "(")).addNode($3).addNode(ASTNode("RP", ")"));} |
	direct_declarator LP RP
        {$$ = ASTNode("direct_declarator", "function"); $$.nodes = $1.nodes;/*这里的nodes应该是ID*/
        $$.addNode(ASTNode("LP", "(")).addNode(ASTNode("RP", ")"));}
    ;

parameter_type_list: 
    parameter_list {$$ = $1;}
    ;

parameter_list: 
    parameter_declaration {$$ = ASTNode("parameter_list"); $$.addNode($1);}|
	parameter_list COMMA parameter_declaration
        {$$ = $1; $$.addNode($3);}
	;

parameter_declaration: 
    declaration_specifiers declarator
        {$$ = ASTNode("parameter_declaration"); 
        $$.addNode($1).addNode($2);}|
	declaration_specifiers {$$ = ASTNode("parameter_declaration"); $$.addNode($1);}
	;

identifier_list: 
    ID  {$$ = ASTNode("identifier_list"); $$.addNode(ASTNode("ID", $1));}|
	identifier_list COMMA ID
        {$$ = $1; $$.addNode($3);}
    ;

compound_statement:
    LC RC 
        {$$ = ASTNode("compound_statement"); $$.addNode(ASTNode("LC", "{")).addNode(ASTNode("RC", "}"));}|
    LC statement_list RC
        {$$ = ASTNode("compound_statement"); $$.addNode(ASTNode("LC", "{")).addNode($2).addNode(ASTNode("RC", "}"));}|
	LC declaration_list RC
        {$$ = ASTNode("compound_statement"); $$.addNode(ASTNode("LC", "{")).addNode($2).addNode(ASTNode("RC", "}"));}|
	LC declaration_list statement_list RC
        {$$ = ASTNode("compound_statement"); $$.addNode(ASTNode("LC", "{")).addNode($2).addNode($3).addNode(ASTNode("RC", "}"));}
	;

statement_list: 
    statement
        {$$ = ASTNode("statement_list"); $$.addNode($1);}|
	statement_list statement
        {$$ = $1; $$.addNode($2);}
	;

constant:
    INT_VALUE 
        {$$ = ASTNode("constant"); $$.addNode(ASTNode("INT_VALUE", $1));}|
    FLOAT_VALUE 
        {$$ = ASTNode("constant"); $$.addNode(ASTNode("FLOAT_VALUE", $1));}
    ;

primary_expression: 
    ID 
        {$$ = ASTNode("primary_expression"); $$.addNode(ASTNode("ID", $1));}|
	constant 
        {$$ = $1;}|
	/*STRING_LITERAL*/
	LP expression RP 
        {$$ = ASTNode("primary_expression"); 
        $$.addNode(ASTNode("LP", "(")).addNode($2).addNode(ASTNode("RP", ")"));}
	;

postfix_expression: 
    primary_expression 
        {$$ = $1;}|
	postfix_expression LB expression RB 
        {$$ = ASTNode("postfix_expression"); 
        $$.addNode($1).addNode(ASTNode("LB", "[")).addNode($3).addNode(ASTNode("RB", "]"));}|
	postfix_expression LP RP
        {$$ = ASTNode("postfix_expression"); 
        $$.addNode($1).addNode(ASTNode("LP", "(")).addNode(ASTNode("RP", ")"));}|
	postfix_expression LP argument_expression_list RP
        {$$ = ASTNode("postfix_expression"); 
        $$.addNode($1).addNode(ASTNode("LP", "(")).addNode($3).addNode(ASTNode("RP", ")"));}|
	postfix_expression INC_OP
        {$$ = ASTNode("postfix_expression"); 
        $$.addNode($1).addNode(ASTNode("INC_OP", "+="));}|
	postfix_expression DEC_OP
        {$$ = ASTNode("postfix_expression"); 
        $$.addNode($1).addNode(ASTNode("DEC_OP", "-="));}
	;

argument_expression_list: 
    assignment_expression
        {$$ = $1;}|
	argument_expression_list COMMA assignment_expression
        {$$ = $1; $$.addNode($3);}
	;

unary_expression: 
    postfix_expression
        {$$ = $1;}|
	INC_OP unary_expression
        {$$ = ASTNode("unary_expression"); $$.addNode(ASTNode("INC_OP", "+=")).addNode($2);}|
	DEC_OP unary_expression
        {$$ = ASTNode("unary_expression"); $$.addNode(ASTNode("DEC_OP", "-=")).addNode($2);}|
	unary_operator cast_expression
        {$$ = ASTNode("unary_expression"); $$.addNode($1).addNode($2);}
	;

unary_operator: 
    /*AND_OP {$$ = ASTNode("unary_operator"); $$.addNode(ASTNode("AND_OP", "&"));} |
	STAR_OP{$$ = ASTNode("unary_operator"); $$.addNode(ASTNode("STAR_OP", "*"));} |*/
	PLUS_OP{$$ = ASTNode("unary_operator"); $$.addNode(ASTNode("PLUS_OP", "+"));} |
	MINUS_OP{$$ = ASTNode("unary_operator"); $$.addNode(ASTNode("MINUS_OP", "-"));} 
	;

cast_expression: 
    unary_expression
        {$$ = $1;}|
	LP type_specifier RP cast_expression
        {$$ = ASTNode("cast_expression"); 
        $$.addNode(ASTNode("LP", "(")).addNode($2).addNode(ASTNode("RP", ")")).addNode($4);}
	;

multiplicative_expression: 
    cast_expression
        {$$ = $1;}|
	multiplicative_expression STAR_OP cast_expression
        {$$ = ASTNode("multiplicative_expression"); 
        $$.addNode($1).addNode(ASTNode("STAR_OP", "*")).addNode($3);}|
	multiplicative_expression DIV_OP cast_expression
        {$$ = ASTNode("multiplicative_expression"); 
        $$.addNode($1).addNode(ASTNode("DIV_OP", "/")).addNode($3);}|
	multiplicative_expression MOD_OP cast_expression
        {$$ = ASTNode("multiplicative_expression"); 
        $$.addNode($1).addNode(ASTNode("MOD_OP", "%")).addNode($3);}
	;

additive_expression: 
    multiplicative_expression
        {$$ = $1;}|
	additive_expression PLUS_OP multiplicative_expression
        {$$ = ASTNode("additive_expression"); 
        $$.addNode($1).addNode(ASTNode("PLUS_OP", "+")).addNode($3);}|
	additive_expression MINUS_OP multiplicative_expression
        {$$ = ASTNode("additive_expression"); 
        $$.addNode($1).addNode(ASTNode("MINUS_OP", "-")).addNode($3);}
	;

shift_expression:
    additive_expression
        {$$ = $1;}
	/*| shift_expression LEFT_OP additive_expression
	| shift_expression RIGHT_OP additive_expression*/
	;

relational_expression:
    shift_expression
        {$$ = $1;}|
	relational_expression LT shift_expression
        {$$ = ASTNode("relational_expression"); 
        $$.addNode($1).addNode(ASTNode("LT", "<")).addNode($3);}|
	relational_expression AT shift_expression
        {$$ = ASTNode("relational_expression"); 
        $$.addNode($1).addNode(ASTNode("AT", ">")).addNode($3);}|
	relational_expression LE shift_expression
        {$$ = ASTNode("relational_expression"); 
        $$.addNode($1).addNode(ASTNode("LE", "<=")).addNode($3);}|
	relational_expression AE shift_expression
        {$$ = ASTNode("relational_expression"); 
        $$.addNode($1).addNode(ASTNode("GE", ">=")).addNode($3);}
	;

equality_expression: 
    relational_expression
        {$$ = $1;}|
	equality_expression EQ relational_expression
        {$$ = ASTNode("equality_expression"); 
        $$.addNode($1).addNode(ASTNode("EQ", "==")).addNode($3);}|
	equality_expression NE relational_expression
        {$$ = ASTNode("equality_expression"); 
        $$.addNode($1).addNode(ASTNode("NE", "<=")).addNode($3);}
	;

and_expression: 
    equality_expression
        {$$ = $1;}|
	and_expression AND_OP equality_expression
        {$$ = ASTNode("and_expression"); 
        $$.addNode($1).addNode(ASTNode("AND_OP", "&&")).addNode($3);}
	;

exclusive_or_expression:
    and_expression
        {$$ = $1;}|
	exclusive_or_expression XOR_OP and_expression
        {$$ = ASTNode("exclusive_or_expression"); 
        $$.addNode($1).addNode(ASTNode("XOR_OP", "^")).addNode($3);}
	;

inclusive_or_expression: 
    exclusive_or_expression
        {$$ = $1;}|
	inclusive_or_expression OR_OP exclusive_or_expression
        {$$ = ASTNode("inclusive_or_expression"); 
        $$.addNode($1).addNode(ASTNode("OR_OP", "|")).addNode($3);}
	;

logical_and_expression: 
    inclusive_or_expression
        {$$ = $1;}|
	logical_and_expression AND inclusive_or_expression
        {$$ = ASTNode("logical_and_expression"); 
        $$.addNode($1).addNode(ASTNode("AND", "&&")).addNode($3);}
	;

logical_or_expression:
    logical_and_expression
        {$$ = $1;}|
	logical_or_expression OR logical_and_expression
        {$$ = ASTNode("logical_or_expression"); 
        $$.addNode($1).addNode(ASTNode("OR", "||")).addNode($3);}
	;

conditional_expression: 
    logical_or_expression
        {$$ = $1;}
	/*| logical_or_expression '?' expression ':' conditional_expression*/
	;

assignment_expression: 
    conditional_expression
        {$$ = $1;}|
	unary_expression assignment_operator assignment_expression
        {$$ = ASTNode("assignment_expression"); 
        $$.addNode($1).addNode($2).addNode($3);}
	;

assignment_operator: 
    ASSIGN {$$ = ASTNode("assignment_operator"); $$.addNode(ASTNode("ASSIGN", "="));} |
    MUL_ASSIGN {$$ = ASTNode("assignment_operator"); $$.addNode(ASTNode("MUL_ASSIGN", "×="));} |
	DIV_ASSIGN {$$ = ASTNode("assignment_operator"); $$.addNode(ASTNode("DIV_ASSIGN", "/="));} |
	MOD_ASSIGN {$$ = ASTNode("assignment_operator"); $$.addNode(ASTNode("MOD_ASSIGN", "%="));} |
	ADD_ASSIGN {$$ = ASTNode("assignment_operator"); $$.addNode(ASTNode("ADD_ASSIGN", "+="));} |
	SUB_ASSIGN {$$ = ASTNode("assignment_operator"); $$.addNode(ASTNode("SUB_ASSIGN", "-="));}
	/*| LEFT_ASSIGN
	| RIGHT_ASSIGN
	| AND_ASSIGN
	| XOR_ASSIGN
	| OR_ASSIGN*/
	;

expression: 
    assignment_expression
        {$$ = $1;}|
	expression COMMA assignment_expression
        {$$ = ASTNode("expression"); 
        $$ = $1; $$.addNode($3);}
	;

constant_expression: 
    conditional_expression
        {$$ = $1;}
	;

labeled_statement:
    CASE constant_expression COLON statement
        {$$ = ASTNode("labeled_statement"); 
        $$.addNode(ASTNode("CASE", "case")).addNode($2).addNode(ASTNode("COLON", ":")).addNode($4);}|
	DEFAULT COLON statement
        {$$ = ASTNode("labeled_statement"); 
        $$.addNode(ASTNode("DEFAULT", "default")).addNode(ASTNode("COLON", ":")).addNode($3);}
	;

selection_statement: 
    IF LP expression RP statement %prec LOWER_THAN_ELSE
        {$$ = ASTNode("selection_statement"); 
        $$.addNode(ASTNode("IF", "if")).addNode(ASTNode("LP", "(")).addNode($3).addNode(ASTNode("RP", ")")).addNode($5);}|
	IF LP expression RP statement ELSE statement
        {$$ = ASTNode("selection_statement"); 
        $$.addNode(ASTNode("IF", "if")).addNode(ASTNode("LP", "(")).addNode($3).addNode(ASTNode("RP", ")"));
        $$.addNode($5).addNode(ASTNode("ELSE", "else")).addNode($7);}|
	SWITCH LP expression RP statement
        {$$ = ASTNode("selection_statement"); 
        $$.addNode(ASTNode("SWITCH", "switch")).addNode(ASTNode("LP", "(")).addNode($3).addNode(ASTNode("RP", ")")).addNode($5);}
	;

iteration_statement: 
    WHILE LP expression RP statement 
        {$$ = ASTNode("iteration_statement"); 
        $$.addNode(ASTNode("WHILE", "while")).addNode(ASTNode("LP", "(")).addNode($3).addNode(ASTNode("RP", ")")).addNode($5);}|
	FOR LP expression_statement expression_statement expression RP statement
        {$$ = ASTNode("iteration_statement"); 
        $$.addNode(ASTNode("FOR", "for")).addNode(ASTNode("LP", "(")).addNode($3).addNode($4).addNode($5);
        $$.addNode(ASTNode("RP", ")")).addNode($7);}
	;

jump_statement:
    /*删除了句末的分号*/
	CONTINUE SEMMI
        {$$ = ASTNode("jump_statement"); 
        $$.addNode(ASTNode("CONTINUE", "continue"))/*.addNode(ASTNode("SEMMI", ";"))*/;}|
	BREAK SEMMI
        {$$ = ASTNode("jump_statement"); 
        $$.addNode(ASTNode("BREAK", "break"));}|
	RETURN SEMMI
        {$$ = ASTNode("jump_statement"); 
        $$.addNode(ASTNode("RETURN", "return"));}|
	RETURN expression SEMMI
        {$$ = ASTNode("jump_statement"); 
        $$.addNode(ASTNode("RETURN", "return"));}
	;

expression_statement: 
    SEMMI {$$ = ASTNode("expression_statement");;}|
	expression SEMMI
        {$$ = ASTNode("expression_statement"); 
        $$.addNode($1);}
	;

statement: 
    labeled_statement {$$ = ASTNode("statement"); $$.addNode($1);}|
	compound_statement {$$ = ASTNode("statement"); $$.addNode($1);}|
	expression_statement {$$ = ASTNode("statement"); $$.addNode($1);}|
	selection_statement {$$ = ASTNode("statement"); $$.addNode($1);}|
	iteration_statement {$$ = ASTNode("statement"); $$.addNode($1);}|
	jump_statement {$$ = ASTNode("statement"); $$.addNode($1);}
	;

%%

// Bison expects us to provide implementation - otherwise linker complains
void EzAquarii::Parser::error(const location &loc , const std::string &message) {
        
        // Location should be initialized inside scanner action, but is not in this example.
        // Let's grab location directly from driver class.
	// cout << "Error: " << message << endl << "Location: " << loc << endl;
	
        cout << "Error: " << message << endl << "Error location: " << driver.locationString() << endl;
}
