#include <iostream>
#include "command.h"
#include "TACNode.h"
#include <regex>

using namespace EzAquarii;
using std::cout;
using std::endl;
using std::regex_match;
using std::regex;

int label_no = 0;

OPN::OPN()
:kind(NOTHING){
}

OPN::OPN(Kind k, int v)
:kind(k), val(v){
    //cout << "get gen" << k << v <<endl;
}

OPN::OPN(Kind k, std::string n)
:kind(k), func_name(n){
}

std::string OPN::opnString(){
    std::string kind_str;
    std::string val_str;
    switch (kind)
    {
    case NOTHING:
        //cout << "haha" << endl;
        kind_str = "";
        val_str = "";
        break;
    case INT:
        kind_str = "#";
        val_str = std::to_string(val);
        break;
    case V:
        kind_str = "v";
        val_str = std::to_string(val);
        break;
    case TEMP:
        kind_str = "temp";
        val_str = std::to_string(val);
        break;
    case LABEL:
        kind_str = "label";
        val_str = std::to_string(val);
        break;
    case FUNCTION:
        kind_str = "";
        val_str = func_name;
        break;
    default:
        break;
    }
    //cout << kind_str << val_str << endl;
    return (kind_str + val_str);
}


TACNode::TACNode(OP o)
:op(o){
}

void TACNode::setOpn1(OPN opn){
    opn1 = opn;
}
void TACNode::setOpn2(OPN opn){
    opn2 = opn;
}
void TACNode::setResult(OPN opn){
    result = opn;
}

std::string TACNode::display(){
    std::string str;
    switch (op)
    {
    case LABEL:
        str = "LABEL " + result.opnString() + " :";
        break;
    case FUNCTION:
        str = "FUNCTION " + result.opnString() + " :";
        break;
    case ASSIGN:
        str = result.opnString() + " := " + opn1.opnString();
        break;
    case PLUS:
        str = result.opnString() + " := " + opn2.opnString() + " + " + opn1.opnString();
        break;
    case MINUS:
        str = result.opnString() + " := " + opn2.opnString() + " - " + opn1.opnString();
        break;    
    case STAR:
        str = result.opnString() + " := " + opn2.opnString() + " * " + opn1.opnString();
        break;
    case DIV:
        str = result.opnString() + " := " + opn2.opnString() + " / " + opn1.opnString();
        break;
    case GOTO:
        str = "GOTO " + result.opnString();
        break;
    case AT:
        str = "IF " + opn1.opnString() + " > " + opn2.opnString() + " GOTO " + result.opnString();
        break;
    case LT:
        str = "IF " + opn1.opnString() + " < " + opn2.opnString() + " GOTO " + result.opnString();
        break;
    case AE:
        str = "IF " + opn1.opnString() + " >= " + opn2.opnString() + " GOTO " + result.opnString();
        break;
    case LE:
        str = "IF " + opn1.opnString() + " <= " + opn2.opnString() + " GOTO " + result.opnString();
        break;
    case EQ:
        str = "IF " + opn1.opnString() + " == " + opn2.opnString() + " GOTO " + result.opnString();
        break;
    case NE:
        str = "IF " + opn1.opnString() + " != " + opn2.opnString() + " GOTO " + result.opnString();
        break;
    case AND:
        str = "IF " + opn1.opnString() + " && " + opn2.opnString() + " GOTO " + result.opnString();
        break;
    case OR:
        str = "IF " + opn1.opnString() + " || " + opn2.opnString() + " GOTO " + result.opnString();
        break;
    case RETURN:
        str = "RETURN " + result.opnString() + " :";
        break;
    case CALL_R:
        str = result.opnString() + " := CALL " + opn1.opnString();
        break;
    case CALL_NR:
        str = "CALL " + opn1.opnString();
        break;
    case PARAM:
        str = "PARAM " + result.opnString();
        break;
    default:
        break;
    }
    cout << str << endl;
    return str;
}