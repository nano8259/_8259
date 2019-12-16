#include "symbol.h"

#include <iterator>
#include <iostream>
#include <sstream>

using namespace EzAquarii;
using std::cout;
using std::endl;
using std::list;
using std::string;

Symbol::Symbol(std::string n, int le, int t, int la, int o, int w)
:name(n), level(le), type(t), label(la), offset(o), width(w)
{
}

void Symbol::printSymbol(){
    string type_str;
    string label_str;
    switch (type)
    {
    case INT: type_str = "int";
        break;
    case FLOAT: type_str = "float";
        break;
    case CHAR: type_str = "char";
        break;
    default:
        break;
    }
    switch (label)
    {
    case FUNC: label_str = "func";
        break;
    case VAR: label_str = "var";
        break;
    case ARRAY: label_str = "array";
        break;
    default:
        break;
    }
    cout << name << "\t" << level << "\t" << type_str << "\t" << label_str << "\t" << offset << "\t" << width << endl;
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
    symbol_table.push_back(s);
    // 打印表
    printTable();
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
        symbol_table.pop_front();
    }

    offset_now = symbol_scope_so.top();
    symbol_scope_so.pop();
}

void SymbolTable::printTable(){
    for(list<Symbol>::iterator it = symbol_table.begin(); it != symbol_table.end(); it++){
        it->printSymbol();
    }
}