#include <iostream>
#include "genir.h"
#include "analysis.h"

#include <regex>

using namespace EzAquarii;
using std::cout;
using std::endl;

extern SymbolTable st;
extern ASTNode root;

void EzAquarii::startGenTAC(){
    cout << "get" << endl;
    cout << st.symbol_table.size() << endl;
    cout << root.name << endl;
}