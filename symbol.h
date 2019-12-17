#ifndef SYMBOL_H
#define SYMBOL_H

// 定义标记
#define FUNC 0
#define VAR 1
#define ARRAY 2

#include <string>
#include <stack>
#include <list>
#include <vector>
#include <stdint.h>

namespace EzAquarii {

class Type{
    // 类型类，这样可以嵌套地实现多维数组
    public:
        //本Type类的类型，基本类型或数组
        enum TypeType {PLAIN = 0, ARRAY_T = 1} type_type;
        // 基本类型
        enum PlainType {INT = 0, FLOAT = 2, CHAR = 3} plain_type;
        // 假如不是基本类型的话，使用vector容器装子类型，方便假如后来要实现结构体
        std::vector<Type> type_list;
        // 此类型的宽度
        int width;
        // 数组的长度，不是数组的话则为0
        int length;

        Type();
        // 基本类型使用的构造函数，仅需传入类型
        Type(PlainType t);
        // 子类型是基本类型的数组使用的构造函数，需要传入类型与长度
        Type(PlainType t, int l);
        // 子类型是数组的数组使用的构造函数，传入子类型、长度
        Type(Type t, int l);
        // 返回在打印符号表的时候需要使用的代表此类型的字符串
        std::string typeString();

    private:
        // 计算该类型的宽度，在构造函数中调用，委派构造函数太麻烦没看懂
        void setWidth();
};

class Symbol{
    public:
        // 构造一个使用基本类型的符号项，width由传入的plaintype类型计算出
        Symbol(std::string n, int le, Type::PlainType t, int la, int o);
        // 若这个符号项是函数，则width应该是0，则直接向width传入0
        Symbol(std::string n, int le, Type::PlainType t, int la, int o, int w);
        // 构造一个数组
        Symbol(std::string n, int lev, Type t, int la, int o, int len);
        Symbol(std::string n, int lev, Type t, int la, int o);
        // 打印一个符号项
        void printSymbol();

        int width; // 宽度

    private:
        std::string name; // 变量名
        // 别名？
        int level; // 层号
        Type type; // 类型
        int label; // 标记
        int offset; // 偏移量
        
};

class SymbolTable{
    public:
        SymbolTable();
        // 添加一个符号项
        void addSymbol(Symbol s);
        // 变量、函数的添加函数
        void addSymbol(std::string n, Type::PlainType t, int la);
        // 数组的添加函数
        void addSymbol(std::string n, Type::PlainType t, int la, int len); // 使用基本类型的数组
        void addSymbol(std::string n, Type t, int la, int len); 
        void addSymbol(std::string n, Type t, int la);

        // 新的作用域开始
        void scopeStart();
        // 当前作用域结束
        void scopeEnd();
        // 打印符号表
        void printTable();

        
    private:
        // 存储符号表的栈，因为stack不提供遍历，所以换使用list
        std::vector<Symbol> symbol_table;
        // 存储各个作用域的起点的栈，因为使用c++的栈实现，存储的不是偏移而是每个作用域开始时的变量个数
        std::stack<int> symbol_scope_sp; // start point
        // 存储各个作用域起始偏移量的栈
        std::stack<int> symbol_scope_so; // start offset
        // 当前的偏移量
        int offset_now;
        // 当前的level
        int level_now;
        
};

//若在这里声明全局变量，则会出现重复定义错误
//SymbolTable st;

}
#endif // SYMBOL_H
