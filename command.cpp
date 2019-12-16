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
        
        for(list<ASTNode>::iterator it = this->nodes.begin(); it != this->nodes.end(); it++){
            if(std::distance(it, this->nodes.end()) != 1){
                v.push_back(1);
            }else{
                v.push_back(0);
            }
            //cout << std::distance(it, this->nodes.end()) << "  " << v.size() << endl;
            it->display(v);
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
        int type;
        int label;
        for(list<ASTNode>::iterator it = nodes.begin(); it != nodes.end(); it++){
            //cout << it->name << endl;
            if(it->name == "type_specifier"){
                //cout << it->name << endl;
                cout << "get type_specifier" << endl;
                //找到了类型
                std::string type_str = it->nodes.begin()->name;
                if(type_str == "INT"){type = INT;}
                else if(type_str == "FLOAT"){type = FLOAT;}
                else if(type_str == "CHAR"){type = CHAR;}
                else{cout << "<<!!unkown type!!>>" << endl;}
            } else if (it->name == "init_declarator_list"){
                //找到了声明符列表
                cout << "get init_declarator_list" << endl;
                for(list<ASTNode>::iterator it_decli = it->nodes.begin(); it_decli != it->nodes.end(); it_decli++){
                    //遍历声明符列表，it_decli指向的声明符列表里的nodes
                    if(it_decli->name == "declarator"   ){
                        //找到了声明符，但是还不能确定是变量还是函数
                        cout << "get declarator" << endl;
                        //将声明符是变量还是函数还是数组的信息存放在declarator的value中
                        if(it_decli->value == "variable"){label = VAR;}
                        else if(it_decli->value == "function"){label = FUNC;}
                        else if(it_decli->value == "array"){label = ARRAY;}
                        else{cout << "<<!!unkown label!!>>" << endl;}
                        //声明符的第一个nodes一定是ID，终于可以创建symbol了！
                        st.addSymbol(it_decli->nodes.begin()->value, type, label);
                    }
                }
            }
        }
    } else if (name == "function_definition"){
        // 函数的定义
        cout << "get function_definition" << endl;
    }else{
        // 啥也不是，递归的寻找子树中的声明语句
        for(list<ASTNode>::iterator it = nodes.begin(); it != nodes.end(); it++){
            it->createSymbolTable();
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