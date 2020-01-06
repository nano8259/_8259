#include <iostream>
#include "analysis.h"
#include "genir.h"
#include <fstream>
#include <regex>

using namespace EzAquarii;
using std::cout;
using std::endl;
using std::regex_match;
using std::regex;

ASTNode root;
SymbolTable st;
// 全局变量：写入中间代码的文件
std::ofstream irfile("fibo.ir");
// 写入汇编代码
std::ofstream acfile("ac.s");
int new_label_now = 0; // 若目前生成一个标号的话，这个标号的序号应当是多少

void EzAquarii::passRoot(ASTNode r){
    root = r;    
    findSymbol(root);
}
//这里是先根遍历的，尝试改成后根遍历
void EzAquarii::findSymbol(ASTNode &n){
    // 这个名字不合适，因为找引用的时候也用的是这个函数
    if(n.name == "declaration"){
        createSymbolDeclaration(n);
    }else if (n.name == "function_definition"){
        createFunctionDefinition(n);
        // 因为函数的定义中仍然会有需要分析的语句，所以还需要对字句依次分析
        for(int i = 0; i < n.nodes.size(); i++){
            findSymbol(n.nodes[i]);
            n.merge(n.nodes[i]);
        }
        TACNode code = TACNode(TACNode::OP::LABEL);
        code.setResult(OPN(OPN::Kind::LABEL, n.Snext));
        n.code.push_back(code); 
    }else if (n.name == "compound_statement"){
        // 开始代码段的代码加在这里会导致函数的形参无法正确的获得偏移量
        // st.scopeStart();
        for(int i = 0; i < n.nodes.size(); i++){
            findSymbol(n.nodes[i]);
        }
        // 在符号表分析完后再分析语句块
        analysis_compound_statement(n);
        st.scopeEnd();
    }/*else if(n.name == "selection_statement"){
        //cout << "get_selection_statement" << endl;
        analysis_selection_statement(n);
    }*/else if (regex_match(n.name, regex(".*expression"))){
        // 找到一个带有enpression的句子后，就进行分析
        analysisExpression(n);
    }
    else{ // 不是以上节点，则继续分析其子节点
        for(int i = 0; i < n.nodes.size(); i++){
            findSymbol(n.nodes[i]);
            n.merge(n.nodes[i]);
        }
    }
    
    if(n.name == "program") {
        toAssembly(n);
        n.displayCode();
        // n.debug_display_all_code();
    }
}

void EzAquarii::toAssembly(ASTNode n){
    std::vector<TACNode> code = n.code;
    acfile << ".data" << endl;
    acfile << "_Prompt: .asciiz \"Enter an integer:  \"" << endl;
    acfile << "_ret: .asciiz \"\\n\"" << endl;
    acfile << ".globl main" << endl;
    acfile << ".text" << endl;
    acfile << "read:" << endl;
    acfile << "  la $a0,_Prompt" << endl;
    acfile << "  li $v0,4" << endl;
    acfile << "  syscall" << endl;
    acfile << "  li $v0,5" << endl;
    acfile << "  syscall" << endl;
    acfile << "  jr $ra" << endl;
    acfile << "write:" << endl;
    acfile << "  li $v0,1" << endl;
    acfile << "  syscall" << endl;
    acfile << "  li $v0,4" << endl;
    acfile << "  la $a0,_ret" << endl;
    acfile << "  syscall" << endl;
    acfile << "  move $v0,$0" << endl;
    acfile << "  jr $ra" << endl;
    for(int i = 0; i < code.size(); i++){
        cout << i << endl;
        TACNode code_now = code[i];
        switch (code_now.op) {
            case TACNode::OP::ASSIGN:
                        if (code_now.opn1.kind==OPN::Kind::INT)
                            acfile << "  li $t3, "<< code_now.opn1.val << endl;
                        else {
                            acfile << "  lw $t1, " << code_now.opn1.offset << "($sp)" << endl;
                            acfile << "  move $t3, $t1\n" ;
                            }
                        acfile << "  sw $t3, " << code_now.result.offset << "($sp)\n";
                        break;
            case TACNode::OP::PLUS:
            case TACNode::OP::MINUS:
            case TACNode::OP::STAR:
            case TACNode::OP::DIV:
                       acfile << "  lw $t1, " << code_now.opn1.offset << "($sp)\n";
                       acfile << "  lw $t2, " << code_now.opn2.offset << "($sp)\n";
                       if (code_now.op==TACNode::OP::PLUS)       acfile << "  add $t3,$t1,$t2\n";
                       else if (code_now.op==TACNode::OP::MINUS) acfile << "  sub $t3,$t1,$t2\n";
                            else if (code_now.op==TACNode::OP::STAR)  acfile << "  mul $t3,$t1,$t2\n";
                                 else  {acfile << "  div $t1, $t2\n";
                                        acfile << "  mflo $t3\n";
                                        }
                        acfile << "  sw $t3, " << code_now.result.offset << "($sp)\n";
                        break;
            case TACNode::OP::FUNCTION:
                        acfile << "\n" << code_now.result.func_name << ":\n";
                        if (code_now.result.func_name == "main")
                            //acfile << "  addi $sp, $sp, -" << st.symbol_table[code_now.result.offset].offset << "\n" );
                            acfile << "  addi $sp, $sp, -" << code_now.result.offset << "\n";
                        break;
            case TACNode::OP::PARAM:
                        break;
            case TACNode::OP::LABEL: acfile << "label" << code_now.result.val <<":\n";
                        break;
            case TACNode::OP::GOTO:  acfile << "  j label" << code_now.result.val << "\n";
                        break;
            case TACNode::OP::LT:
            case TACNode::OP::LE:
            case TACNode::OP::AE:
            case TACNode::OP::AT:
            case TACNode::OP::EQ:
            case TACNode::OP::NE:
                        acfile << "  lw $t1, " << code_now.opn1.offset << "($sp)\n";
                        acfile << "  lw $t2, " << code_now.opn2.offset << "($sp)\n";
                        //if (code_now.op==JLE) acfile << "  ble $t1,$t2,%s\n", code_now.result.id);
                        //else if (code_now.op==JLT) acfile << "  blt $t1,$t2,%s\n", code_now.result.id);
                        //else if (code_now.op==JGE) acfile << "  bge $t1,$t2,%s\n", code_now.result.id);
                        //else if (code_now.op==JGT) acfile << "  bgt $t1,$t2,%s\n", code_now.result.id);
                        if (code_now.op==TACNode::OP::EQ)  acfile << "  beq $t1,$t2,label" << code_now.result.val << "\n";
                        //else                 acfile << "  bne $t1,$t2,%s\n", code_now.result.id);
                        break;
            case TACNode::OP::ARG:   
                        break;
            case TACNode::OP::CALL_R:  
                        if (code_now.opn1.func_name == "read"){ 
                            acfile << "  addi $sp, $sp, -4\n";
                            acfile << "  sw $ra,0($sp)\n"; 
                            acfile << "  jal read\n"; 
                            acfile << "  lw $ra,0($sp)\n"; 
                            acfile << "  addi $sp, $sp, 4\n";
                            acfile << "  sw $v0, " << code_now.result.offset << "($sp)\n";
                            break;
                        }
                        if (code_now.opn1.func_name == "write"){ 
                            // !!!这里假设只有一个参数
                            acfile << "  lw $a0, " << code[i-1].result.offset << "($sp)\n";
                            acfile << "  addi $sp, $sp, -4\n";
                            acfile << "  sw $ra,0($sp)\n";
                            acfile << "  jal write\n";
                            acfile << "  lw $ra,0($sp)\n";
                            acfile << "  addi $sp, $sp, 4\n";
                            break;
                            }

                        // !!!这里假设只有一个参数
                        acfile << "  move $t0,$sp\n"; 
                        acfile << "  addi $sp, $sp, -" << st.symbol_table[st.searchIndex(code_now.opn1.func_name)].width << "\n";
                        acfile << "  sw $ra,0($sp)\n"; 
                        

                        // !!!
                        //acfile << "  lw $t1, %d($t0)\n", p->result.offset); 
                        acfile << "  lw $t1, " << code[i-1].result.offset << "($t0)\n"; // 应该是arg那句
                        acfile << "  move $t3,$t1\n";
                        //acfile << "  sw $t3," << st.symbol_table[st.searchIndex(code_now.opn1.func_name)+1].offset << "($sp)\n"; 
                        acfile << "  sw $t3," << 4 << "($sp)\n";
                        //不能这样写，用寄存器传参吧 v0
                        //acfile << "  move $v0,$t3\n";

                        acfile << "  jal " << code_now.opn1.func_name << "\n"; 
                        acfile << "  lw $ra,0($sp)\n"; 
                        acfile << "  addi $sp,$sp," << st.symbol_table[st.searchIndex(code_now.opn1.func_name)].width << "\n"; 
                        acfile << "  sw $v0," << code_now.result.offset <<"($sp)\n"; 
                        break;
            case TACNode::OP::RETURN:
                        acfile << "  lw $v0," << code_now.result.offset << "($sp)\n"; 
                        acfile << "  jr $ra\n";
                        break;

        }
    }
}

void EzAquarii::analysis_selection_statement(ASTNode &n){
    //cout << "analysis_selection_statement" << endl;
    // !!!这里假设只有IF，没有ELSE，而且只有一个语句
    n.Snext = new_label_now++;
    n.Ts.push_back(n.nodes[1]); // 一个条件表达式
    n.Ts.push_back(n.nodes[2]); // 一个语句
    n.Ts[0].Etrue = new_label_now++;
    n.Ts[0].Efalse = n.Snext;
    n.Ts[0].Snext = n.Snext;
    n.Ts[1].Snext = n.Snext;
    analysis_expression(n.Ts[0]);
    analysis_statement(n.Ts[1]);
    n.merge(n.Ts[0]);
    TACNode code = TACNode(TACNode::OP::LABEL);
    code.setResult(OPN(OPN::Kind::LABEL, n.Ts[0].Etrue));
    n.code.push_back(code); 
    n.merge(n.Ts[1]);
    TACNode code2 = TACNode(TACNode::OP::LABEL);
    code2.setResult(OPN(OPN::Kind::LABEL, n.Snext));
    n.code.push_back(code2); 
}

void EzAquarii::analysis_expression(ASTNode &n){
    //cout << "analysis_expression" << endl;
    // !!!这里假设每一个三目表达式都是计算式，每一个两目表达式都是函数调用，单目表达式是函数调用，没有参数
    if(n.nodes.size() == 3){
        //计算式
        if(n.nodes[1].name == "OR"){
            // 首先为这个表达式整一个临时变量存着
            // st.addTempSymbol(Type::PlainType::INT);
            // n.place = st.symbol_table.size()-1;
            // 或，使用短路，前面表达式的真指向条件判断表达式的真，前面表达式的假指向后面表达式
            // 后面表达式的真指向条件判断表达式的真，后面表达式的假指向条件判断表达式的Snext
            n.nodes[0].Etrue = n.Etrue;
            n.nodes[0].Efalse = new_label_now++;
            analysis_expression(n.nodes[0]);
            // 这行中间代码是Efalse的中间代码

            // 开始合并IF语句中条件表达式的代码
            n.merge(n.nodes[0]);
            n.code.push_back(TACNode(TACNode::OP::LABEL));
            n.code[n.code.size()-1].setResult(OPN(OPN::Kind::LABEL, n.nodes[0].Efalse));

            n.nodes[2].Etrue = n.Etrue;
            n.nodes[2].Efalse = n.Snext;
            analysis_expression(n.nodes[2]);

            n.merge(n.nodes[2]);
        } else{
            // 除了OR之外的表达式，都需要先找出来OPN
            OPN opn1, opn2;
            if(n.nodes[0].name != "primary_expression" && n.nodes[0].name != "constant" && n.nodes[0].value != "array"){
                // 不是这两种的话，说明是还需要分析的表达式
                // 表达式的值就是place对应的temp
                analysis_expression(n.nodes[0]); // 首先对子表达式进行分析
                n.merge(n.nodes[0]); // 然后将语句合并
                opn1 = symbol_to_opn(st.symbol_table[n.nodes[0].place]);
            }else if(n.nodes[0].name == "primary_expression"){
                // !!!这里假设所有的primary_expression都是ID
                opn1 = symbol_to_opn(st.symbol_table[st.searchIndex(n.nodes[0].nodes[0].value)]);
            }else if(n.nodes[0].name == "constant"){
                // 这里还需要一行中间代码将立即数存入寄存器
                n.code.push_back(TACNode(TACNode::OP::ASSIGN));
                n.code[n.code.size()-1].setOpn1(OPN(OPN::Kind::INT, std::stoi(n.nodes[0].nodes[0].value)));
                st.addTempSymbol(Type::PlainType::INT);
                int temp_place = st.symbol_table.size()-1;
                n.code[n.code.size()-1].setResult(symbol_to_opn(st.symbol_table[temp_place]));
                opn1 = symbol_to_opn(st.symbol_table[temp_place]);
            }else if(n.nodes[0].value == "array"){
                //opn1 = symbol_to_opn(st.symbol_table[st.searchIndex(n.nodes[0].nodes[0].value)]);
                int index = std::stoi(n.nodes[0].nodes[1].nodes[0].value);
                int off = st.symbol_table[st.searchIndex(n.nodes[0].nodes[0].nodes[0].value)].offset;
                cout << off << "\t" << index << endl;
                opn1 = OPN(OPN::Kind::V, st.searchIndex(n.nodes[0].nodes[0].nodes[0].value), off + index *4);
                cout << opn1.opnString() << endl;
            }
            if(n.nodes[2].name != "primary_expression" && n.nodes[2].name != "constant" && n.nodes[2].value != "array"){
                // 第二个OPN同理
                analysis_expression(n.nodes[2]);
                n.merge(n.nodes[2]); // 然后将语句合并
                opn2 = symbol_to_opn(st.symbol_table[n.nodes[2].place]);
            }else if(n.nodes[2].name == "primary_expression"){
                opn2 = symbol_to_opn(st.symbol_table[st.searchIndex(n.nodes[2].nodes[0].value)]);
            }else if(n.nodes[2].name == "constant"){
                // 这里还需要一行中间代码将立即数存入寄存器
                n.code.push_back(TACNode(TACNode::OP::ASSIGN));
                n.code[n.code.size()-1].setOpn1(OPN(OPN::Kind::INT, std::stoi(n.nodes[2].nodes[0].value)));
                st.addTempSymbol(Type::PlainType::INT);
                st.printTable();
                int temp_place = st.symbol_table.size()-1;
                n.code[n.code.size()-1].setResult(symbol_to_opn(st.symbol_table[temp_place]));
                opn2 = symbol_to_opn(st.symbol_table[temp_place]);
            }else if(n.nodes[2].value == "array"){
                //opn1 = symbol_to_opn(st.symbol_table[st.searchIndex(n.nodes[0].nodes[0].value)]);
                int index = std::stoi(n.nodes[2].nodes[1].nodes[0].value);
                int off = st.symbol_table[st.searchIndex(n.nodes[2].nodes[0].nodes[0].value)].offset;
                cout << off << "\t" << index << endl;
                opn2 = OPN(OPN::Kind::V, st.searchIndex(n.nodes[2].nodes[0].nodes[0].value), off + index *4);
                cout << opn1.opnString() << endl;
            }
            // 找到OPN后开始生成代码
            if(n.nodes[1].name == "assignment_operator"){
                // !!!为了实现复合赋值运算符，所以不是非终结符，这里假设仅为“=”
                n.code.push_back(TACNode(TACNode::OP::ASSIGN));
                n.code[n.code.size()-1].setResult(opn1);
                n.code[n.code.size()-1].setOpn1(opn2);
            }else{
                // 首先为这个表达式整一个临时变量存着
                st.addTempSymbol(Type::PlainType::INT);
                n.place = st.symbol_table.size()-1;
                // !!!在本程序中只有加法和EQ，所以正常的式子只写加法和EQ
                // 好吧是减法
                if(n.nodes[1].name == "PLUS_OP"){
                    n.code.push_back(TACNode(TACNode::OP::PLUS));
                    n.code[n.code.size()-1].setResult(symbol_to_opn(st.symbol_table[n.place]));
                    n.code[n.code.size()-1].setOpn1(opn1);
                    n.code[n.code.size()-1].setOpn2(opn2);
                }else if(n.nodes[1].name == "MINUS_OP"){
                    n.code.push_back(TACNode(TACNode::OP::MINUS));
                    n.code[n.code.size()-1].setResult(symbol_to_opn(st.symbol_table[n.place]));
                    n.code[n.code.size()-1].setOpn1(opn1);
                    n.code[n.code.size()-1].setOpn2(opn2);
                }else if(n.nodes[1].name == "EQ"){
                    n.code.push_back(TACNode(TACNode::OP::EQ));
                    n.code[n.code.size()-1].setResult(OPN(OPN::Kind::LABEL, n.Etrue));
                    n.code[n.code.size()-1].setOpn1(opn1);
                    n.code[n.code.size()-1].setOpn2(opn2);
                    n.code.push_back(TACNode(TACNode::GOTO));
                    n.code[n.code.size()-1].setResult(OPN(OPN::Kind::LABEL, n.Efalse));
                }
            }
        }
    }else if(n.nodes.size() == 2){
        // !!!假设这个就是函数，且仅有一个参数
        // 首先为这个表达式整一个临时变量存着
        st.addTempSymbol(Type::PlainType::INT);
        n.place = st.symbol_table.size()-1;
        // 首先找参数
        // !!!这里假设只有使用变量或者表达式调用，没有使用立即数调用
        OPN opn1;
        if(n.nodes[1].nodes.size() == 3){
            // 不是这两种的话，说明是还需要分析的表达式
            // 表达式的值就是place对应的temp
            analysis_expression(n.nodes[1]); // 首先对子表达式进行分析
            n.merge(n.nodes[1]); // 然后将语句合并
            opn1 = symbol_to_opn(st.symbol_table[n.nodes[1].place]);
        }else if(n.nodes[1].nodes.size() == 1){
            // !!!这里假设所有的primary_expression都是ID
            opn1 = symbol_to_opn(st.symbol_table[st.searchIndex(n.nodes[1].nodes[0].value)]);
        }
        // 找到操作数之后ARG
        n.code.push_back(TACNode(TACNode::OP::ARG));
        //cout << opn1.opnString();
        n.code[n.code.size()-1].setResult(opn1);
        // !!!假设所有的函数都是有返回值的
        n.code.push_back(TACNode(TACNode::OP::CALL_R));
        n.code[n.code.size()-1].setResult(symbol_index_to_opn(n.place));
        n.code[n.code.size()-1].setOpn1(symbol_index_to_opn(st.searchIndex(n.nodes[0].nodes[0].value)));
        // st.symbol_table[st.searchIndex(n.nodes[0].nodes[0].value)].printSymbol();
    }else if(n.nodes.size() == 1){
        // !!!没有参数的函数调用
        // 首先为这个表达式整一个临时变量存着
        st.addTempSymbol(Type::PlainType::INT);
        n.place = st.symbol_table.size()-1;
        n.code.push_back(TACNode(TACNode::OP::CALL_R));
        n.code[n.code.size()-1].setResult(symbol_index_to_opn(n.place));
        n.code[n.code.size()-1].setOpn1(symbol_index_to_opn(st.searchIndex(n.nodes[0].nodes[0].value)));
    }
    // n.displayCode();
    // cout << "" <<endl;
}

void EzAquarii::analysis_compound_statement(ASTNode &n){
    // 传入的节点为compound_statement
    // 可能有一个节点也有可能有两个节点，只需要处理statement_list
    ASTNode statement_list;
    for(int i = 0; i < n.nodes.size(); i++){
        if(n.nodes[i].name == "statement_list"){
            statement_list = n.nodes[i];
        }
    }
    // 找到了statement_list后逐一分析其语句
    for(int i = 0; i < statement_list.nodes.size(); i++){
        analysis_statement(statement_list.nodes[i]);
        n.merge(statement_list.nodes[i]);
    }
}

void EzAquarii::analysis_statement(ASTNode &n){
    // 传入的节点为statement
    // !!!statement仅有jump_statement、selection_statement和表达式
    if(n.nodes[0].name == "jump_statement"){
        analysis_jump_statement(n.nodes[0]);
    }else if(n.nodes[0].name == "selection_statement"){
        analysis_selection_statement((n.nodes[0]));
    }else if(regex_match(n.nodes[0].name, regex(".*expression"))){
        analysis_expression(n.nodes[0]);
    }
    n.merge(n.nodes[0]);
}

void EzAquarii::analysis_jump_statement(ASTNode &n){
    // !!!jump_statement只有return
    // 找到操作数
    OPN opn;
    if(n.nodes[1].name == "constant"){
        // 这里还需要一行中间代码将立即数存入寄存器
        n.code.push_back(TACNode(TACNode::OP::ASSIGN));
        // 立即数没有便宜地址
        n.code[n.code.size()-1].setOpn1(OPN(OPN::Kind::INT, std::stoi(n.nodes[1].nodes[0].value)));
        st.addTempSymbol(Type::PlainType::INT);
        int temp_place = st.symbol_table.size()-1;
        n.code[n.code.size()-1].setResult(symbol_to_opn(st.symbol_table[temp_place]));
        opn = symbol_to_opn(st.symbol_table[temp_place]);
    }else{
        // !!!除此之外就是表达式
        analysis_expression(n.nodes[1]);
        n.merge(n.nodes[1]);
        opn = symbol_to_opn(st.symbol_table[n.nodes[1].place]);
        
    }
    n.code.push_back(TACNode(TACNode::OP::RETURN));
    n.code[n.code.size()-1].setResult(opn);
}

OPN EzAquarii::symbol_to_opn(Symbol s){
    switch (s.alias_type)
    {
    case Symbol::AliasType::V:
        return OPN(OPN::Kind::V, s.alias_no, s.offset);
        break;
    case Symbol::AliasType::TEMP:
        return OPN(OPN::Kind::TEMP, s.alias_no, s.offset);
        break;
    default:
        break;
    }
    return OPN(OPN::Kind::NOTHING, 0);
}

OPN EzAquarii::symbol_index_to_opn(int i){
    Symbol s = st.symbol_table[i];
    if (s.getLabel() == FUNC){
        return OPN(OPN::Kind::FUNCTION, s.getName(), s.offset);
    }else{
        switch (s.alias_type)
        {
        case Symbol::AliasType::V:
            return OPN(OPN::Kind::V, s.alias_no, s.offset);
            break;
        case Symbol::AliasType::TEMP:
            return OPN(OPN::Kind::TEMP, s.alias_no, s.offset);
            break;
        default:
            break;
        }
    }
    return OPN(OPN::Kind::NOTHING, 0);
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
            //cout << "get type_specifier" << endl;
            //找到了类型
            std::string type_str = n.nodes[i].nodes[0].name;
            if(type_str == "INT"){type = Type::PlainType::INT;}
            else if(type_str == "FLOAT"){type = Type::PlainType::FLOAT;}
            else if(type_str == "CHAR"){type = Type::PlainType::CHAR;}
            else{cout << "<<!!unkown type!!>>" << endl;}
        } else if (n.nodes[i].name == "init_declarator_list"){
            //找到了声明符列表
            //cout << "get init_declarator_list" << endl;
            for(int j = 0; j < n.nodes[i].nodes.size(); j++){
                //遍历声明符列表，it_decli指向的声明符列表里的nodes
                if(n.nodes[i].nodes[j].name == "declarator"   ){
                    //找到了声明符，但是还不能确定是变量还是函数
                    //cout << "get declarator" << endl;
                    //将声明符是变量还是函数还是数组的信息存放在declarator的value中
                    if(n.nodes[i].nodes[j].value == "variable"){
                        label = VAR;
                        if(checkDuplicate(n.nodes[i].nodes[j].nodes[0].value) == true) {
                            st.addSymbol(n.nodes[i].nodes[j].nodes[0].value, type, label);
                        }
                        // st.addSymbol(n.nodes[i].nodes[j].nodes[0].value, type, label);
                    }
                    else if(n.nodes[i].nodes[j].value == "function"){
                        label = FUNC;
                        //Symbol s = st.addSymbol(n.nodes[i].nodes[j].nodes[0].value, type, label);
                        //这里发现使用返回引用比较麻烦，所以转为之间取出st中最新加入的Symbol，为该函数
                        if(checkDuplicate(n.nodes[i].nodes[j].nodes[0].value) == true) {
                            st.addSymbol(n.nodes[i].nodes[j].nodes[0].value, type, label);
                        }
                        // Symbol s = st.getLast();
                        // cout << &s << endl;
                        // st.symbol_table[st.symbol_table.size() - 1].addParameter(Type(Type::PlainType::INT));
                        // s.isDefined = false;
                        createFunctionDeclarationParameters(n.nodes[i].nodes[j]);
                    }
                    else if(n.nodes[i].nodes[j].value == "array"){
                        label = ARRAY;
                        // 发现将要声明的内容是数组后，接下来往下找数组的维度信息，一边找一遍逐步构建数组
                        Type array_type; // 用来装最终将要添加到符号表中的Type
                        for(int k = 1; k < n.nodes[i].nodes[j].nodes.size() && n.nodes[i].nodes[j].nodes[k].name == "constant"; k++){
                            // TODO：这里有一个可以报错的地方，即方括号内的数字不为int
                            int tmp_length = 0;
                            if(!regex_match(n.nodes[i].nodes[j].nodes[k].nodes[0].value, regex("0|[1-9][0-9]*"))){
                                printErrorInfo(112, n.nodes[i].nodes[j].nodes[0].value);
                            }else{
                                tmp_length = std::stoi(n.nodes[i].nodes[j].nodes[k].nodes[0].value);
                            }
                            if(k == 1){ // 说明是第一个数组，使用基本类型进行定义
                                array_type = Type(type, tmp_length);
                            }else { // 是多维数组了，使用之前的数组进行定义
                                array_type = Type(array_type, tmp_length);
                            }
                        }
                        if(checkDuplicate(n.nodes[i].nodes[j].nodes[0].value) == true) {
                            st.addSymbol(n.nodes[i].nodes[j].nodes[0].value, array_type, label);
                        }
                    } else{cout << "<<!!unkown label!!>>" << endl;}
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
    if(n.nodes.size() >= 2){
        ASTNode node_list = n.nodes[1]; // "parameter_list"节点为第二个节点
        for(int i = 0; i < node_list.nodes.size(); i++){
            // node_list的nodes里的节点均为parameter_declaration节点
            std::string type_str = node_list.nodes[i].nodes[0].nodes[0].name;
            Type::PlainType type;
            if(type_str == "INT"){type = Type::PlainType::INT;}
            else if(type_str == "FLOAT"){type = Type::PlainType::FLOAT;}
            else if(type_str == "CHAR"){type = Type::PlainType::CHAR;}
            st.symbol_table[st.symbol_table.size() - 1].addParameter(Type(type));
            //cout << node_list.nodes[i].nodes[0].nodes[1].value << endl;
            // if (i == 1)
            // 这里创建参数
            st.addSymbol(node_list.nodes[i].nodes[1].nodes[0].value ,type , VAR);
            // st.printTable();
        }   
        
    }else{
        return;
    }
}

bool EzAquarii::checkDuplicate(std::string id){
    // 这个函数的作用是查看变量或者函数的声明是否有重复
    Symbol* sp = st.search(id);
    if(sp == NULL){ // 检测是否重复定义
        return true; // 说明没有找到名字相同的
    }else if(sp->getLevel() == st.getLevelNow()){
        // 如果出现重复定义错误的话，跳过这个，继续分析下面的
        if(sp->getLabel() == FUNC){
            printErrorInfo(113, id);
        }else if(sp->getLabel() == VAR || sp->getLabel() == ARRAY ){
            printErrorInfo(103, id);
        }
    }else{
        return true;
    }
    return false;
}

bool EzAquarii::createFunctionDefinition(ASTNode &n){
    //cout << "get function_definition" << endl;
    Type::PlainType type;
    std::string id = n.nodes[1].nodes[0].value;
    std::string type_str = n.nodes[0].nodes[0].name;
    std::vector<std::string> para_list;
    std::vector<std::string> id_list;
    if(type_str == "INT"){type = Type::PlainType::INT;}
    else if(type_str == "FLOAT"){type = Type::PlainType::FLOAT;}
    else if(type_str == "CHAR"){type = Type::PlainType::CHAR;}
    else{cout << "<<!!unkown type!!>>" << endl;}
    if(n.nodes[1].nodes.size() == 2){
        ASTNode para_list_node = n.nodes[1].nodes[1];
        for(int i = 0; i < para_list_node.nodes.size(); i++){
            para_list.push_back(para_list_node.nodes[i].nodes[0].nodes[0].value);
            id_list.push_back(para_list_node.nodes[i].nodes[0].nodes[1].value);
        }
    }
    // 所需信息：类型、函数名、参数列表均已找到，下面开始检查
    Symbol* sp = st.search(id);
    if(sp == NULL){
        // 没有找到同名函数，则在符号表中添加这个函数
        st.addSymbol(id, type, FUNC);
        st.symbol_table[st.symbol_table.size() - 1].isDefined = true;
        // 函数的本身的声明还是在原来的代码段里，但是参数需要放到新的代码段中
        st.scopeStart();
        createFunctionDeclarationParameters(n.nodes[1]);
        // 还要加上形参
        // !!!这里假设形参只有一个且是整型
        if(n.nodes[1].nodes.size() == 2){
            // 说明是有形参的
            // st.addSymbol(id_list[0], Type::PlainType::INT, VAR);
        }
    }else if(sp->getLabel() != FUNC){
        // 找到了同名符号，但是并非函数，则报错并返回
        printErrorInfo(114, id); // 函数的定义与声明不符
        return false;
    }else if(sp->isDefined == true){
        // 找到了同名符号且是函数，看看是不是已经定义了
        printErrorInfo(104, id);
        return false;
    }else if (type != sp->getType().plain_type){
        // 这里有点问题, 没法比较多维数组
        // 找到了已经声明的未定义函数，看看类型与参数列表是否不同
        cout <<type<<sp->getType().plain_type << endl;
        printErrorInfo(114, id); // 函数的定义与声明不符
        return false;
    }else{
        if(sp->parameter_list.size() != para_list.size()){
            printErrorInfo(114, id); // 函数的定义与声明不符
            return false;
        }else{
            for(int i = 0; i < para_list.size(); i++){
                if(para_list[i] != sp->parameter_list[i].typeString()){
                    printErrorInfo(114, id); // 函数的定义与声明不符
                    return false;
                }
            }
        }
    }


    // 下面开始生成function的中间代码
    TACNode code = TACNode(TACNode::OP::FUNCTION);
    code.setResult(symbol_index_to_opn(st.searchIndex(id)));
    n.code.push_back(code);
    if(n.nodes[1].nodes.size() == 2){
        TACNode code2 = TACNode(TACNode::OP::PARAM);
        code2.setResult(symbol_index_to_opn(st.searchIndex("a"))); // !!!
        n.code.push_back(code2);
    }
    n.Snext = new_label_now++;
    n.nodes[2].Snext = n.Snext; // compound_statement

    st.symbol_table[st.searchIndex(id)].isDefined = true;
    return true;
}

void EzAquarii::analysisExpression(ASTNode n){
    // n是name为expression_statement/..._expression的节点，子节点为表达式语句中的内容
    // 遍历这个表达式语句并且对每个使用的标识符查看是否存在未声明错误
    cout << n.value <<endl;
    if(n.value == "function"){
        // function的第一个子节点是名称，第二个子节点是参数列表
        std::string func_name = n.nodes[0].nodes[0].value;
        std::vector<std::string> para_list;
        if(n.nodes.size() == 2){
            for(int i = 0; i < n.nodes[1].nodes.size(); i++){
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
    }else if (n.value == "array"){
        // 第一个子节点是名称，第二个子节点是下标
        // 这里的问题是没有支持多维访问
        std::string array_name = n.nodes[0].nodes[0].value;
        std::vector<std::string> index_list;
        if(n.nodes.size() == 2){
            for(int i = 0; i < n.nodes[1].nodes.size(); i++){
                index_list.push_back(n.nodes[1].nodes[i].value);
            }
        }
        Symbol* sp = st.search(array_name);
        if(sp == NULL){
            printErrorInfo(102, array_name); // 使用未定义的变量
        }else if (sp->getLabel() != ARRAY){
            printErrorInfo(110, array_name); // 对非数组型变量使用"[...]"(数组访问)操作符
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
    //cout << err_info_str << n << err_info[n] << id << endl;
}

void EzAquarii::test(){
    cout << "get" << endl;
}

int EzAquarii::newTemp(){
    // 目前只有INT
    Symbol s =  st.addTempSymbol(Type::PlainType::INT);
    return st.symbol_table.size() - 1;
}

int EzAquarii::newLabel(){
    return new_label_now++;
}