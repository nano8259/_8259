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