#ifndef ANALYSIS_H
#define ANALYSIS_H

#include <string>
#include <vector>
#include <list>
#include <stdint.h>
#include "command.h"
#include "symbol.h"

namespace EzAquarii {

static SymbolTable st;

void passRoot(ASTNode r);

void findSymbol(ASTNode n);
void createSymbolDeclar(ASTNode n);
void createSymbolFunc(ASTNode n);
void createSymbolTable(ASTNode n);

void test();

}
#endif