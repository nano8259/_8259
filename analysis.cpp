#include <iostream>
#include "command.h"
#include "symbol.h"
#include "analysis.h"

#include <regex>

using namespace EzAquarii;
using std::cout;
using std::endl;
using std::regex_match;
using std::regex;

ASTNode root;
//SymbolTable st;

void EzAquarii::passRoot(ASTNode r){
    root = r;    
    findSymbol(root);
}

void EzAquarii::findSymbol(ASTNode n){
    // 这个名字不合适，因为找引用的时候也用的是这个函数
    if(n.name == "declaration"){
        createSymbolDeclaration(n);
    }else if (n.name == "function_definition"){
        createFunctionDefinition(n);
        // 因为函数的定义中仍然会有需要分析的语句，所以还需要对字句依次分析
        for(int i = 0; i < n.nodes.size(); i++){
            findSymbol(n.nodes[i]);
        }
    }else if (n.name == "compound_statement"){
        st.scopeStart();
        for(int i = 0; i < n.nodes.size(); i++){
            findSymbol(n.nodes[i]);
        }
        st.scopeEnd();
    }else if (regex_match(n.name, regex(".*expression"))){
        // 找到一个带有enpression的句子后，就进行分析
        analysisExpression(n);
    }
    else{ // 不是以上节点，则继续分析其子节点
        for(int i = 0; i < n.nodes.size(); i++){
            findSymbol(n.nodes[i]);
        }
    }
}

void EzAquarii::createSymbolDeclaration(ASTNode n){
    // 创建声明的符号
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
                        //Symbol s = st.addSymbol(n.nodes[i].nodes[j].nodes[0].value, type, label);
                        //这里发现使用返回引用比较麻烦，所以转为之间取出st中最新加入的Symbol，为该函数
                        st.addSymbol(n.nodes[i].nodes[j].nodes[0].value, type, label);
                        // Symbol s = st.getLast();
                        // cout << &s << endl;
                        // st.symbol_table[st.symbol_table.size() - 1].addParameter(Type(Type::PlainType::INT));
                        // s.isDefined = false;
                        createFunctionDeclarationParameters(n.nodes[i].nodes[j]);
                    }
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

void EzAquarii::createFunctionDeclarationParameters(ASTNode n){
    // 传入的节点为"declarator: function"节点
    // Symbol s = st.symbol_table[st.symbol_table.size() - 1];
    // cout << &s << endl;
    // ？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？
    // 要搞懂这里的地址问题
    st.symbol_table[st.symbol_table.size() - 1].isDefined = false;
    ASTNode node_list = n.nodes[1]; // "parameter_list"节点为第二个节点
    for(int i = 0; i < node_list.nodes.size(); i++){
        // node_list的nodes里的节点均为parameter_declaration节点
        std::string type_str = node_list.nodes[i].nodes[0].nodes[0].name;
        Type::PlainType type;
        if(type_str == "INT"){type = Type::PlainType::INT;}
        else if(type_str == "FLOAT"){type = Type::PlainType::FLOAT;}
        else if(type_str == "CHAR"){type = Type::PlainType::CHAR;}
        st.symbol_table[st.symbol_table.size() - 1].addParameter(Type(type));
        st.printTable();
    }
}

void EzAquarii::createFunctionDefinition(ASTNode n){
    cout << "get function_definition" << endl;

}

void EzAquarii::analysisExpression(ASTNode n){
    // n是name为expression_statement/..._expression的节点，子节点为表达式语句中的内容
    // 遍历这个表达式语句并且对每个使用的标识符查看是否存在未声明错误
    if(n.value == "function"){
        // function的第一个子节点是名称，第二个子节点是参数列表
        std::string func_name = n.nodes[0].nodes[0].value;
        std::vector<std::string> para_list;
        if(n.nodes.size() == 2){
            for(int i = 0; i < n.nodes[1].nodes.size(); i++){
                cout << "HERE  " << n.nodes[1].nodes[i].value << endl;
                para_list.push_back(n.nodes[1].nodes[i].value);
            }
        }
        // 找到函数名称及参数列表后，开始判断调用的函数是否已声明
        Symbol* sp = st.search(func_name);
        if(sp == NULL){
            printErrorInfo(102, func_name); // 使用未定义的变量
        }else if (sp->getLabel() != FUNC){
            printErrorInfo(111, func_name); // 对普通变量使用\"(...)\"或\"()\"(函数调用)操作符
        }else{
            if(sp->parameter_list.size() != para_list.size()){
                printErrorInfo(109, func_name); // 函数调用时实参与形参的数目或类型不匹配
            }else{
                for(int i = 0; i < para_list.size(); i++){
                    Symbol* psp = st.search(para_list[i]);
                    if(psp == NULL){
                        printErrorInfo(101, para_list[i]); // 使用未定义的变量
                    }else if(psp->getType().typeString() != sp->parameter_list[i].typeString()){
                        printErrorInfo(109, func_name); // 函数调用时实参与形参的数目或类型不匹配
                    }
                }
            }
        }
    }else if(n.name == "ID"){
        // 这里的ID既不在函数中，也不在数组中，说明是普通的变量
        Symbol* sp = st.search(n.value);
        if(sp == NULL){
            printErrorInfo(101, n.value); // 使用未定义的变量
        }else if (sp->getLabel() == FUNC){
            printErrorInfo(115, n.value); // 在调用函数时未使用\"(...)\"或\"()\"(函数调用)操作符
        }
    }else{
        for(int i = 0; i < n.nodes.size(); i++){
            analysisExpression(n.nodes[i]);
        }
    }

}

std::map<int, std::string> err_info = {
    {100, "未知语义错误"},
    {101, "使用未定义的变量"},
    {102, "调用未定义或未声明的函数"},
    {103, "变量出现重复定义"},
    {104, "函数出现重复定义"},
    {105, "赋值号两边表达式类型不匹配"},
    {106, "操作数类型不匹配"},
    {107, "操作数类型与操作符不匹配"},
    {108, "return语句返回值的类型与函数定义的返回类型不匹配"},
    {109, "函数调用时实参与形参的数目或类型不匹配"},
    {110, "对非数组型变量使用\"[...]\"(数组访问)操作符"},
    {111, "对普通变量使用\"(...)\"或\"()\"(函数调用)操作符"},
    {112, "数组访问操作符\"[...]\"中出现非整型数字"},
    {113, "尝试声明已经声明过的函数"},
    {114, "函数的定义与声明不符"},
    {115, "在调用函数时未使用\"(...)\"或\"()\"(函数调用)操作符"}

};

void EzAquarii::printErrorInfo(int n, std::string id){
    std::string err_info_str; // 用来放报错的行数

    err_info_str += "ERROR";
    cout << err_info_str << n << err_info[n] << id << endl;
}

void EzAquarii::test(){
    cout << "get" << endl;
}