#ifndef SYMBOL_H
#define SYMBOL_H
// 定义类型
#define INT 1
#define FLOAT 2
#define CHAR 3
// 定义标记
#define FUNC 1
#define VAR 2
#define CONST 3

#include <string>
#include <stack>
#include <stdint.h>

namespace EzAquarii {

class Symbol{
    public:
        // 构造一个符号项，除了
        Symbol(std::string n, int le, int t, int la, int o, int w);

    private:
        std::string name; // 变量名
        // 别名？
        int level; // 层号
        int type; // 类型
        int label; // 标记
        int offset; // 偏移量
        int width; // 宽度
};

class SymbolTable{
    public:
        SymbolTable();
        // 添加一个符号项
        void addSymbol(Symbol s);
        // 新的作用域开始
        void scopeStart();
        // 当前作用域结束
        void scopeEnd();

        
    private:
        // 存储符号表的栈
        std::stack<Symbol> symbol_table;
        // 存储各个作用域的起点的栈，因为使用c++的栈实现，存储的不是偏移而是每个作用域开始时的变量个数
        std::stack<int> symbol_scope_sp; // start point
        // 存储各个作用域起始偏移量的栈
        std::stack<int> symbol_scope_so; // start offset
        // 当前的偏移量
        int offset_now;
        // 当前的level
        int level_now;
        
};
}

#endif // SYMBOL_H
