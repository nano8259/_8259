#include "symbol.h"

#include <iterator>
#include <iostream>
#include <sstream>

using namespace EzAquarii;
using std::cout;
using std::endl;
using std::list;
using std::string;

Type::Type()
:width(0), length(0){
}

Type::Type(PlainType t)
:type_type(PLAIN), plain_type(t), length(0){ 
    setWidth();   
}

Type::Type(PlainType t, int l)
:type_type(ARRAY_T), length(l){
    // 总而言之，只要是数组类型就不应该有plain_type，所以还是将传入的基本类型变成Type类存在type_list里    
    type_list.push_back(Type(t));
    setWidth();
}

Type::Type(Type t, int l)
:type_type(ARRAY_T), length(l){
    type_list.push_back(t);
    setWidth();
}

string Type::typeString(){
    string type_str;
    if(type_type == Type::TypeType::PLAIN){
        switch (plain_type){
        case Type::PlainType::INT:
            type_str = "int";
            break;
        case Type::PlainType::FLOAT:
            type_str = "float";
            break;
        case Type::PlainType::CHAR:
            type_str = "char";
            break;                    
        default:
            break;
        }
    }else if (type_type == Type::TypeType::ARRAY_T){
        if(type_list[0].type_type == ARRAY_T){
            type_str = "array";
        }else{
            switch (plain_type){
            case Type::PlainType::INT:
                type_str = "int";
                break;
            case Type::PlainType::FLOAT:
                type_str = "float";
                break;
            case Type::PlainType::CHAR:
                type_str = "char";
                break;                    
            default:
                break;
            }
        }

    }
    return type_str;
}

void Type::setWidth(){
    if(type_type == PLAIN){
        switch (plain_type)
        {
        case INT:
            width = 4;
            break;
        case FLOAT:
            width = 4;
            break;
        case CHAR:
            width = 2;
            break;                    
        default:
            break;
        }
    }else if (type_type == ARRAY_T){
        int tmp_width = 0; // 计算list里的所有的Type的宽度
        for(int i = 0; i < type_list.size(); i++){
            tmp_width += type_list[i].width;
        }
        width = tmp_width * length;
    }
}

Symbol::Symbol(){

}

Symbol::Symbol(std::string n, int le, Type::PlainType t, int la, int o)
:name(n), level(le), label(la), offset(o){
    type = Type(t);
    width = type.width;
}

Symbol::Symbol(std::string n, int le, Type::PlainType t, int la, int o, int w)
:name(n), level(le), label(la), offset(o), width(0){
    type = Type(t);
}

Symbol::Symbol(std::string n, int lev, Type t, int la, int o, int len)
:name(n), level(lev), label(la), offset(o){
    type = Type(t, len);
    width = t.width;
}

Symbol::Symbol(std::string n, int lev, Type t, int la, int o)
:name(n), level(lev), label(la), offset(o){
    type = t;
    width = t.width;
}

void Symbol::printSymbol(){
    string type_str = type.typeString();
    string label_str;
    string parameter_str;
    switch (label)
    {
    case FUNC: 
        label_str = "func";
        for(int i = 0; i < parameter_list.size(); i++){
            parameter_str += parameter_list[i].typeString();
            parameter_str += " ";
        }
        break;
    case VAR: label_str = "var";
        break;
    case ARRAY: label_str = "array";
        break;
    default:
        break;
    }
    cout << name << "\t" << level << "\t" << type_str << "\t" << label_str << "\t" << offset << "\t" << width << "\t" << parameter_str << endl;
}

void Symbol::addParameter(Type t){
    parameter_list.push_back(t);
}

string Symbol::getName(){
    return name;
}

SymbolTable::SymbolTable()
:level_now(0), offset_now(0)
{    
}

Symbol SymbolTable::addSymbol(std::string n, Type::PlainType t, int la){
    int wi = 0;
    Symbol s;
    if (la == FUNC){
        // 如果是函数的话，则不应该有偏移量，直接向width传入0
        s = Symbol(n, level_now, t, la, offset_now, 0);
        addSymbol(s);
    }
    else if (la == VAR){ // 是基本类型，使用基本类型的构造方法
        s = Symbol(n, level_now, t, la, offset_now);
        wi = s.width;
        addSymbol(s);
    }else if (la == ARRAY){ // 是数组，使用数组的构造方法
        s = Symbol(n, level_now, t, la, offset_now);
    }
    offset_now += wi;
    return s;
}

Symbol SymbolTable::addSymbol(std::string n, Type::PlainType t, int la, int len){
    return addSymbol(n, Type(t), la, len);
    
}

Symbol SymbolTable::addSymbol(std::string n, Type t, int la, int len){
    int wi = 0;
    Symbol s;
    if (la == ARRAY){ // 是数组，使用数组的构造方法
        Symbol s = Symbol(n, level_now, t, la, offset_now, len);
        wi = s.width;
        addSymbol(s);
    }
    offset_now += wi;
    return s;
}

Symbol SymbolTable::addSymbol(std::string n, Type t, int la){
    int wi = 0;
    Symbol s;
    if (la == ARRAY){ // 是数组，使用数组的构造方法
        Symbol s = Symbol(n, level_now, t, la, offset_now);
        wi = s.width;
        addSymbol(s);
    }
    offset_now += wi;
    return s;
}

Symbol SymbolTable::addSymbol(Symbol s){
    symbol_table.push_back(s);
    // 打印表
    printTable();
    return s;
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
        symbol_table.pop_back();
    }

    offset_now = symbol_scope_so.top();
    symbol_scope_so.pop();
}

void SymbolTable::printTable(){
    cout << "name\tlevel\ttype\tlable\toffset\twidth\tparameters" << endl;
    for(int i = 0; i < symbol_table.size(); i++){
        symbol_table[i].printSymbol();
    }
}

Symbol& SymbolTable::getLast(){
    return symbol_table[symbol_table.size() - 1];
}

Symbol* SymbolTable::search(std::string s){
    for(int i = symbol_table.size() - 1; i > -1; i--){
        if(symbol_table[i].getName() == s){
            return &symbol_table[i];
        }
    }
    return NULL;
}