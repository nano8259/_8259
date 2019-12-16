#include <iostream>
#include "command.h"
#include "symbol.h"
#include "analysis.h"

using namespace EzAquarii;
using std::cout;
using std::endl;

ASTNode root;
//SymbolTable st;

void EzAquarii::passRoot(ASTNode r){
    root = r;    
    root.createSymbolTable();
}

void EzAquarii::test(){
    cout << "get" << endl;
}