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

}
#endif