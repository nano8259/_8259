#ifndef ANALYSIS_H
#define ANALYSIS_H

#include <string>
#include <vector>
#include <list>
#include <stdint.h>
#include <map>
#include "command.h"
#include "symbol.h"

namespace EzAquarii {

void passRoot(ASTNode r);

void findSymbol(ASTNode n);
void createSymbolDeclaration(ASTNode n);
void createFunctionDeclarationParameters(ASTNode n);
bool createFunctionDefinition(ASTNode n);
void createSymbolTable(ASTNode n);

void analysisExpression(ASTNode n);
bool checkDuplicate(std::string id);

void printErrorInfo(int n, std::string id);

void test();

// 新临时变量，返回no
int newTemp();
// 新标号，返回no
int newLabel();
 
// 使用下划线代码风格的是中间代码生成的函数，只能这样了，对不起
void analysis_selection_statement(ASTNode &n);
void analysis_expression(ASTNode &n);
void analysis_statement(ASTNode &n);
void analysis_jump_statement(ASTNode &n);

OPN symbol_to_opn(Symbol s);
OPN symbol_index_to_opn(int i);

}
#endif