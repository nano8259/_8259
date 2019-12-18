/*
 * The MIT License (MIT)
 * 
 * Copyright (c) 2014 Krzysztof Narkiewicz <krzysztof.narkiewicz@ezaquarii.com>
 * 
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 * 
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 * 
 */

#ifndef COMMAND_H
#define COMMAND_H

#include <string>
#include <vector>
#include <list>
#include <stdint.h>

namespace EzAquarii {

class ASTNode{
    public:
        ASTNode();

        ASTNode(std::string _name);
        //叶节点
        ASTNode(std::string _name, std::string _value);

        void display();
        void display(std::vector<int> v);

        ASTNode& addNode(ASTNode _node);
        ASTNode& addNodes(std::vector<ASTNode> ns);

        int kind;

        std::string name;

        std::string value;

        // ASTNode* ptr[4];
        std::vector<ASTNode> nodes;
        int pos;                       //语法单位所在位置行号
        // int place;                     //存放（临时）变量在符号表的位置序号
        // char Etrue[15],Efalse[15];       //对布尔表达式的翻译时，真假转移目标的标号
        // char Snext[15];                 //结点对应语句S执行后的下一条语句位置标号
        // struct codenode *code;          //该结点中间代码链表头指针
        // int type;                      //用以标识表达式结点的类型
        // int offset;                     //偏移量
        // int width;                     //占数据字节数
   private:
        
};


/**
 * AST node. If you can call it AST at all...
 * It keeps function name and a list of arguments.
 */
class Command
{
public:
    Command(const std::string &name, const std::vector<uint64_t> arguments);
    Command(const std::string &name);
    Command();
    ~Command();
    
    std::string str() const;
    std::string name() const;
    
private:
    std::string m_name;
    std::vector<uint64_t> m_args;
};

}

#endif // COMMAND_H
