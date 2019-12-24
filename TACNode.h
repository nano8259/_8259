#ifndef TACNODE_H
#define TACNODE_H

#include <string>

namespace EzAquarii {

class OPN{
    public:
        enum Kind{
            NOTHING,
            INT,
            V, // 变量的别名
            TEMP, // 临时变量的别名
            LABEL,
            FUNC
        } kind;

        int val;
        std::string func_name;

        OPN();
        OPN(Kind k, int v);
        OPN(Kind k, std::string n);

        std::string opnString();
};

class TACNode{
    public:
        enum OP {
            LABEL, 
            FUNCTION,
            ASSIGN,
            PLUS,
            MINUS,
            STAR,
            DIV,
            GOTO,
            AT,LT,AE,LE,EQ,NE,AND,OR,
            RETURN,
            ARG,
            CALL_R, // 有返回值的函数调用
            CALL_NR, // 没有返回值的函数调用
            PARAM} op;
        
        OPN opn1, opn2, result;

        TACNode(OP o);

        void setOpn1(OPN opn);
        void setOpn2(OPN opn);
        void setResult(OPN opn);

        void display();
};

}
#endif