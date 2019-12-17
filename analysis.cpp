#include <iostream>
#include "command.h"
#include "symbol.h"
#include "analysis.h"

using namespace EzAquarii;
using std::cout;
using std::endl;

ASTNode root;
//SymbolTable st;

void EzAquarii::passRoot(ASTNode r){
    root = r;    
    findSymbol(root);
}

void EzAquarii::findSymbol(ASTNode n){
    if(n.name == "declaration"){
        createSymbolDeclar(n);
    }else if (n.name == "function_definition"){
        createSymbolFunc(n);

    }else{
        for(int i = 0; i < n.nodes.size(); i++){
            findSymbol(n.nodes[i]);
        }
    }
}

void EzAquarii::createSymbolDeclar(ASTNode n){
    // 可能是变量的声明或者函数的声明
    // 此声明语句的属性：类型与标签
    Type::PlainType type;
    int label;
    for(int i = 0; i < n.nodes.size(); i++){
        //cout << it->name << endl;
        if(n.nodes[i].name == "type_specifier"){
            //cout << it->name << endl;
            cout << "get type_specifier" << endl;
            //找到了类型
            std::string type_str = n.nodes[i].nodes[0].name;
            if(type_str == "INT"){type = Type::PlainType::INT;}
            else if(type_str == "FLOAT"){type = Type::PlainType::FLOAT;}
            else if(type_str == "CHAR"){type = Type::PlainType::CHAR;}
            else{cout << "<<!!unkown type!!>>" << endl;}
        } else if (n.nodes[i].name == "init_declarator_list"){
            //找到了声明符列表
            cout << "get init_declarator_list" << endl;
            for(int j = 0; j < n.nodes[i].nodes.size(); j++){
                //遍历声明符列表，it_decli指向的声明符列表里的nodes
                if(n.nodes[i].nodes[j].name == "declarator"   ){
                    //找到了声明符，但是还不能确定是变量还是函数
                    cout << "get declarator" << endl;
                    //将声明符是变量还是函数还是数组的信息存放在declarator的value中
                    if(n.nodes[i].nodes[j].value == "variable"){
                        label = VAR;
                        st.addSymbol(n.nodes[i].nodes[j].nodes[0].value, type, label);}
                    else if(n.nodes[i].nodes[j].value == "function"){
                        label = FUNC;
                        st.addSymbol(n.nodes[i].nodes[j].nodes[0].value, type, label);}
                    else if(n.nodes[i].nodes[j].value == "array"){
                        label = ARRAY;
                        // 发现将要声明的内容是数组后，接下来往下找数组的维度信息，一边找一遍逐步构架数组
                        Type array_type; // 用来装最终将要添加到符号表中的Type
                        for(int k = 1; k < n.nodes[i].nodes[j].nodes.size() && n.nodes[i].nodes[j].nodes[k].name == "constant"; k++){
                            // TODO：这里有一个可以报错的地方，即方括号内的数字不为int
                            int tmp_length = std::stoi(n.nodes[i].nodes[j].nodes[k].nodes[0].value);
                            if(k == 1){ // 说明是第一个数组，使用基本类型进行定义
                                array_type = Type(type, tmp_length);
                            }else { // 是多维数组了，使用之前的数组进行定义
                                array_type = Type(array_type, tmp_length);
                            }
                        }
                        st.addSymbol(n.nodes[i].nodes[j].nodes[0].value, array_type, label);
                        }
                    else{cout << "<<!!unkown label!!>>" << endl;}
                    //声明符的第一个nodes一定是ID，终于可以创建symbol了！
                }
            }
        }
    }
}

void EzAquarii::createSymbolFunc(ASTNode n){
    cout << "get function_definition" << endl;

}

void EzAquarii::test(){
    cout << "get" << endl;
}