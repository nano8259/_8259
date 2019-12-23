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

D			[0-9]
L			[a-zA-Z_]
H			[a-fA-F0-9]
E			[Ee][+-]?{D}+
FS			(f|F|l|L)
IS			(u|U|l|L)*

%{
	#include <iostream>
	#include <cstdlib>
	#include "scanner.h"
	#include "interpreter.h"
	#include "parser.hpp"
	#include "location.hh"
    #include <string>

	using namespace std;

	// Original yyterminate() macro returns int. Since we're using Bison 3 variants
	// as tokens, we must redefine it to change type from `int` to `Parser::semantic_type`
	#define yyterminate() EzAquarii::Parser::make_END(EzAquarii::location());

	// This will track current scanner location.
	// Action is called when length of the token is known.
	#define YY_USER_ACTION m_driver.increaseLocation(yyleng);
	
	// !!!WARNING!!!
	// Location API is used, but the location is not initialized, 'cause I'm lazy. When making
	// a token with make_{something} method you can pass detailed token location. Current location
	// is accessible with m_driver.location() method. All puzzle elements are there - just
	// pass location value in every action code block below. I'm going to waste more time writing
	// this excuse than putting this boilerplate below...
	//
	// Location class can be found in location.hh and posistion.hh files. It's just a bit too much
	// boilerplate for this small example. Bummer.
    void print(std::string&& type, char* yytext);
%}

%option nodefault
%option noyywrap
%option c++
%option yyclass="Scanner"
%option prefix="EzAquarii_"

INT "int"
FLOAT "float"
COMMA ,
LP \(
RP \)
LB \[
RB \]
LC \{
RC \}
ASSIGN =
PLUS [+]
MINUS [-]
STAR [*]
DIV [/]
SEMMI ;
INT_VALUE 0|[1-9][0-9]* 
FLOAT_VALUE [0-9]*[.][0-9]+([eE][+-]?[0-9]*|[0])?f?
SPACE [ \t]
ID [a-zA-Z][a-zA-Z0-9]*

%%
\/\/(.)*\n      { m_driver.increaseLocation(); }
{INT}           { print("INT", yytext);
                return EzAquarii::Parser::make_INT(EzAquarii::location());}
{FLOAT}         { print("FLOAT", yytext);
                return EzAquarii::Parser::make_FLOAT(EzAquarii::location());}
"char"			{ print("CHAR", yytext);
                return EzAquarii::Parser::make_CHAR(EzAquarii::location());}
"break"			{ print("BREAK", yytext);
                return EzAquarii::Parser::make_BREAK(EzAquarii::location());}
"continue"		{ print("CONTINUE", yytext);
                return EzAquarii::Parser::make_CONTINUE(EzAquarii::location());}
"if"			{ print("IF", yytext);
                return EzAquarii::Parser::make_IF(EzAquarii::location());}
"while"			{ print("WHILE", yytext);
                return EzAquarii::Parser::make_WHILE(EzAquarii::location());}
"else"          { print("ELSE", yytext);
                return EzAquarii::Parser::make_ELSE(EzAquarii::location());}
"for"           { print("FOR", yytext);
                return EzAquarii::Parser::make_FOR(EzAquarii::location());}
"switch"        { print("SWITCH", yytext);
                return EzAquarii::Parser::make_SWITCH(EzAquarii::location());}
"case"          { print("CASE", yytext);
                return EzAquarii::Parser::make_CASE(EzAquarii::location());}
"default"       { print("DEFAULT", yytext);
                return EzAquarii::Parser::make_DEFAULT(EzAquarii::location());}
"return"        { print("RETURN", yytext);
                return EzAquarii::Parser::make_RETURN(EzAquarii::location());}

"+="			{ print("ADD_ASSIGN", yytext);/*复合赋值运算符，自增自减符，算数运算符、比较运算符*/
                return EzAquarii::Parser::make_ADD_ASSIGN(EzAquarii::location());}
"-="			{ print("SUB_ASSIGN", yytext);
                return EzAquarii::Parser::make_SUB_ASSIGN(EzAquarii::location());}
"*="			{ print("MUL_ASSIGN", yytext);
                return EzAquarii::Parser::make_MUL_ASSIGN(EzAquarii::location());}
"/="			{ print("DIV_ASSIGN", yytext);
                return EzAquarii::Parser::make_DIV_ASSIGN(EzAquarii::location());}
"%="			{ print("MOD_ASSIGN", yytext);
                return EzAquarii::Parser::make_MOD_ASSIGN(EzAquarii::location());}
"++"			{ print("INC_OP", yytext);
                return EzAquarii::Parser::make_PLUS_OP(EzAquarii::location());}
"--"			{ print("DEC_OP", yytext);
                return EzAquarii::Parser::make_DEC_OP(EzAquarii::location());}
">"             { print("AT", yytext);
                return EzAquarii::Parser::make_AT(EzAquarii::location());}
"<"             { print("LT", yytext);
                return EzAquarii::Parser::make_LT(EzAquarii::location());}
">="            { print("AE", yytext);
                return EzAquarii::Parser::make_AE(EzAquarii::location());}
"<="            { print("LE", yytext);
                return EzAquarii::Parser::make_LE(EzAquarii::location());}
"=="            { print("EQ", yytext);
                return EzAquarii::Parser::make_EQ(EzAquarii::location());}
"!="            { print("NE", yytext);
                return EzAquarii::Parser::make_NE(EzAquarii::location());}
"&&"            { print("AND", yytext);
                return EzAquarii::Parser::make_AND(EzAquarii::location());}
"||"            { print("OR", yytext);
                return EzAquarii::Parser::make_OR(EzAquarii::location());}

{ASSIGN}        { print("ASSIGN_OP", yytext);/*Assignment,赋值符，将==的判断放在=前*/
                return EzAquarii::Parser::make_ASSIGN(EzAquarii::location());}  
{PLUS}          { print("PLUS_OP", yytext);
                return EzAquarii::Parser::make_PLUS_OP(EzAquarii::location());}
{MINUS}         { print("MINUS_OP", yytext);
                return EzAquarii::Parser::make_MINUS_OP(EzAquarii::location());}
{DIV}           { print("DIV_OP", yytext);
                return EzAquarii::Parser::make_DIV_OP(EzAquarii::location());}
{STAR}          { print("STAR_OP", yytext);
                return EzAquarii::Parser::make_STAR_OP(EzAquarii::location());}
"%"             { print("MOD_OP", yytext);
                return EzAquarii::Parser::make_MOD_OP(EzAquarii::location());}
"&"             { print("AND_OP", yytext);
                return EzAquarii::Parser::make_AND_OP(EzAquarii::location());}
"|"             { print("OR_OP", yytext);
                return EzAquarii::Parser::make_OR_OP(EzAquarii::location());}
"^"             { print("EOR_OP", yytext);
                return EzAquarii::Parser::make_XOR_OP(EzAquarii::location());}

{COMMA}         { print("COMMA", yytext);
                return EzAquarii::Parser::make_COMMA(EzAquarii::location());}
{LP}            { print("LP", yytext);
                return EzAquarii::Parser::make_LP(EzAquarii::location());}
{RP}            { print("RP", yytext);
                return EzAquarii::Parser::make_RP(EzAquarii::location());}
{LB}            { print("LB", yytext);
                return EzAquarii::Parser::make_LB(EzAquarii::location());}
{RB}            { print("RB", yytext);
                return EzAquarii::Parser::make_RB(EzAquarii::location());}
{LC}            { print("LC", yytext);
                return EzAquarii::Parser::make_LC(EzAquarii::location());}
{RC}            { print("RC", yytext);
                return EzAquarii::Parser::make_RC(EzAquarii::location());}
":"             { print("COLON", yytext);
                return EzAquarii::Parser::make_COLON(EzAquarii::location());}
{SEMMI}         { print("SEMMI", yytext);
                return EzAquarii::Parser::make_SEMMI(EzAquarii::location());}

{INT_VALUE}     { print("INT_VALUE", yytext);
                /*long number = stol(yytext, 0, 10);*/
                return EzAquarii::Parser::make_INT_VALUE(yytext, EzAquarii::location());}
{FLOAT_VALUE}   { print("FLOAT_VALUE", yytext);
                /*double number = stod(yytext);*/
                return EzAquarii::Parser::make_FLOAT_VALUE(yytext, EzAquarii::location());}
{SPACE}         { /*drop them and do nothing*/ }

{ID}            { print("ID", yytext);
                return EzAquarii::Parser::make_ID(yytext, EzAquarii::location());}

"\n"            { m_driver.increaseLocation(); }

.           { 
                cout << "Scanner: unknown character [" << yytext << "]" << endl; 
            }
            
<<EOF>>     { return yyterminate(); }


%%

void print(std::string&& type, char* yytext){
    //cout << "Scanner:<" << type << ">" << yytext << endl;
    return;
}