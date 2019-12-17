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

#include "command.h"
#include "symbol.h"
#include "analysis.h"

#include <iostream>
#include <sstream>
#include <vector>

using namespace EzAquarii;
using std::cout;
using std::endl;
using std::list;

ASTNode::ASTNode(){
    kind = -1;
    name = "unknown";
}

ASTNode::ASTNode(std::string _name)
: name(move(_name)){
    kind = 0; // kind为0代表是非终结符
}

ASTNode::ASTNode(std::string _name, std::string _value)
: name(move(_name)), value(move(_value)){
    kind = 1; // kind为1代表终结符
}

void ASTNode::display(){
    std::vector<int> v = std::vector<int>();
    display(v);
}

//对抽象语法树的先根遍历
void ASTNode::display(std::vector<int> v){ 
    // v是记录在这一行前面需要打印的内容的vector，初始传入为空
        for(int i = 0; i < v.size(); i++){
            if(v[i] == 0){ // 此处应该是空白
                if(i != v.size()-1){ // 若不是最后一个，就输出空白
                    cout << "  ";
                }else{ // 若是最后一个，说明是父节点的最后一个子节点
                    cout << "└─";
                }
            }else if (v[i] == 1){
                if(i != v.size()-1){ // 若不是最后一个，就输出竖线
                    cout << "│ ";
                }else{ // 若是最后一个
                    cout << "├─";
                }
            }
        }
        if(this->kind == 0){
            cout << this->name << '\n';
        }else if (this->kind == 1)
        {
            cout << this->name << ": " << this->value << '\n';
        }
        
        for(int i = 0; i < nodes.size(); i++){
            if(i != nodes.size() - 1){
                v.push_back(1);
            }else{
                v.push_back(0);
            }
            //cout << std::distance(it, this->nodes.end()) << "  " << v.size() << endl;
            nodes[i].display(v);
            v.pop_back();
        }
    }

ASTNode& ASTNode::addNode(ASTNode _node){
    nodes.push_back(_node);
    return *this;
}

void ASTNode::createSymbolTable(){
    if(name == "declaration"){
        // 可能是变量的声明或者函数的声明
        // 此声明语句的属性：类型与标签
        Type::PlainType type;
        int label;
        for(int i = 0; i < nodes.size(); i++){
            //cout << it->name << endl;
            if(nodes[i].name == "type_specifier"){
                //cout << it->name << endl;
                cout << "get type_specifier" << endl;
                //找到了类型
                std::string type_str = nodes[i].nodes[0].name;
                if(type_str == "INT"){type = Type::PlainType::INT;}
                else if(type_str == "FLOAT"){type = Type::PlainType::FLOAT;}
                else if(type_str == "CHAR"){type = Type::PlainType::CHAR;}
                else{cout << "<<!!unkown type!!>>" << endl;}
            } else if (nodes[i].name == "init_declarator_list"){
                //找到了声明符列表
                cout << "get init_declarator_list" << endl;
                for(int j = 0; j < nodes[i].nodes.size(); j++){
                    //遍历声明符列表，it_decli指向的声明符列表里的nodes
                    if(nodes[i].nodes[j].name == "declarator"   ){
                        //找到了声明符，但是还不能确定是变量还是函数
                        cout << "get declarator" << endl;
                        //将声明符是变量还是函数还是数组的信息存放在declarator的value中
                        if(nodes[i].nodes[j].value == "variable"){
                            label = VAR;
                            st.addSymbol(nodes[i].nodes[j].nodes[0].value, type, label);}
                        else if(nodes[i].nodes[j].value == "function"){
                            label = FUNC;
                            st.addSymbol(nodes[i].nodes[j].nodes[0].value, type, label);}
                        else if(nodes[i].nodes[j].value == "array"){
                            label = ARRAY;
                            // 发现将要声明的内容是数组后，接下来往下找数组的维度信息，一边找一遍逐步构架数组
                            Type array_type; // 用来装最终将要添加到符号表中的Type
                            for(int k = 1; k < nodes[i].nodes[j].nodes.size() && nodes[i].nodes[j].nodes[k].name == "constant"; k++){
                                // TODO：这里有一个可以报错的地方，即方括号内的数字不为int
                                cout << nodes[i].nodes[j].nodes[k].name << endl;
                                int tmp_length = std::stoi(nodes[i].nodes[j].nodes[k].nodes[0].value);
                                if(k == 1){ // 说明是第一个数组，使用基本类型进行定义
                                    array_type = Type(type, tmp_length);
                                }else { // 是多维数组了，使用之前的数组进行定义
                                    array_type = Type(array_type, tmp_length);
                                }
                            }
                            st.addSymbol(nodes[i].nodes[j].nodes[0].value, array_type, label);
                            }
                        else{cout << "<<!!unkown label!!>>" << endl;}
                        //声明符的第一个nodes一定是ID，终于可以创建symbol了！
                    }
                }
            }
        }
    } else if (name == "function_definition"){
        // 函数的定义
        cout << "get function_definition" << endl;
    }else{
        // 啥也不是，递归的寻找子树中的声明语句
        for(int i = 0; i < nodes.size(); i++){
            nodes[i].createSymbolTable();
        }
    } 
}

Command::Command(const std::string &name, const std::vector<uint64_t> arguments) :
    m_name(name),
    m_args(arguments)
{
}

Command::Command(const std::string &name) :
    m_name(name),
    m_args()
{
}

Command::Command() :
    m_name(),
    m_args()
{
}

Command::~Command()
{
}
    
std::string Command::str() const {
    std::stringstream ts;
    ts << "name = [" << m_name << "], ";
    ts << "arguments = [";
    
    for(int i = 0; i < m_args.size(); i++) {
        ts << m_args[i];
        if(i < m_args.size() - 1) {
            ts << ", ";
        }
    }
    
    ts << "]";
    return ts.str();
}

std::string Command::name() const {
    return m_name;
}