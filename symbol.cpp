#include "symbol.h"

#include <iostream>
#include <sstream>

using namespace EzAquarii;


Symbol::Symbol(std::string n, int le, int t, int la, int o, int w)
:name(n), level(le), type(t), label(la), offset(o), width(w)
{
}

SymbolTable::SymbolTable()
:level_now(0), offset_now(0)
{    
}

void SymbolTable::addSymbol(std::string n, int t, int la){
    int wi = 0;
    switch (t)
    {
    case INT:
        wi = 4;
        break;
    case FLOAT:
        wi = 4;
        break;
    case CHAR:
        wi = 2;
        break;
    default:
        break;
    }
    Symbol s = Symbol(n, level_now, t, la, offset_now, wi);
    offset_now += wi;
    addSymbol(s);
}

void SymbolTable::addSymbol(Symbol s){
    symbol_table.push(s);
}

void SymbolTable::scopeStart(){
    level_now += 1;
    // 记录当前的数量
    symbol_scope_sp.push(symbol_table.size());
    // 记录当前的偏移量
    symbol_scope_so.push(offset_now);
}

void SymbolTable::scopeEnd(){
    int i;
    level_now -= 1;

    i = symbol_table.size() - symbol_scope_sp.top();
    for(symbol_scope_sp.pop(); i > 0; i--){
        symbol_table.pop();
    }

    offset_now = symbol_scope_so.top();
    symbol_scope_so.pop();
}