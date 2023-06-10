#include "ir.hpp"
#include "AST/ast.hpp"
#include <cassert>
#include<string>
using namespace std;
int initss=0;
void Type::getir(string &s) 
{
    switch (this->tid)
    {
        case i32ID:
            s += "i32 ";
            break;
        case funID:
            funtype->getir(s);
            break;
        case arrayID:
            arraytype->getir(s);
            break;
        case poterID:
            pointertype->getir(s);
    }
}

void Return::getir(string &s)
{
    s+="ret ";
    if(value!=nullptr)
        value->getir(s);
    s+='\n';
}

void Value::getir(string &s)
{
    switch (this->tid)
    {
        case SYMBOLID:
            symbol->getir(s);
            break;
        case INTID:
            i32->getir(s);
            break;
        case undefID:
            s+="; ";
    }
}

void SYMBOL::getir(string &s)
{
    s+=symbol;
}

void INT::getir(string &s)
{
    s+=to_string(int_const);
}

void FunDef::getir(string &s)
{
    s+="fun ";
    s+="@";
    symbol->getir(s);
    s+="( ";
    if(funparams!=nullptr)
        funparams->getir(s);
    s+=") ";
    if(type!=nullptr)
    {
        s+=": ";
        type->getir(s);
    }
    s+="{ ";
    s+='\n';
    funbody->getir(s);
    s+="}\n";
}

void Funparams::getir(string &s)
{
    for(int i=0;i<funparam_.size();i++)
    {
        funparam_[i]->getir(s);
        if(i<funparam_.size()-1)
            s+=", ";
    }
}

void Funparam::getir(string &s)
{
    symbol->getir(s);
    s+=": ";
    type->getir(s);
}

void FunBody::getir(string &s)
{
    for (Block *t:block_)
        t->getir(s);
}

void Block::getir(string &s)
{
    if(symbol!=nullptr)
    {
        s+='%';
        symbol->getir(s);
        s+=": ";
        s+='\n';
    }
    if(!statement_.empty())
    {
        for(Statement *t:statement_)
            t->getir(s);
    }
    assert(endstatement!=nullptr);
    endstatement->getir(s);
}

void InitIR::getir(string &s)
{
    for(GlobalSymbolDef *t:globalsymboldef_)
        t->getir(s);
    for(FunDef *t:fundef_)
        t->getir(s);
}

void Statement::getir(string &s)
{
    switch (this->tid)
    {
        case SyDeID:
            symboldef->getir(s);
            break;
        case StoreID:
            store->getir(s);
            break;
        case FuncID:
             funcall->getir(s);
    }
}

void SymbolDef::getir(string &s)
{
    symbol->getir(s);
    s+="= ";
    switch (this->tid)
    {
        case BiEpID:
            binaryexpr->getir(s);
            break;
        case MemID:
            memorydeclaration->getir(s);
            break;
        case LoadID:
            load->getir(s);
            break;
        case FuncID:
            funcall->getir(s);
            break;
    }
}

void BinaryExpr::getir(string &s)
{
    switch (this->tid)
    {
        case neID: 
            s+="ne ";
            break;
        case eqID:
            s+="eq ";
            break;
        case gtID:
            s+="gt ";
            break; 
        case ltID:
            s+="lt ";
            break; 
        case geID:
            s+="ge ";
            break; 
        case leID:
            s+="le ";
            break; 
        case addID:
            s+="add ";
            break; 
        case subID:
            s+="sub ";
            break; 
        case mulID:
            s+="mul ";
            break; 
        case divID:
            s+="div ";
            break; 
        case modID:
            s+="mod ";
            break; 
        case andID:
            s+="and ";
            break; 
        case orID:
            s+="or ";
            break; 
        case xorID:
            s+="xor ";
            break; 
        case shlID:
            s+="shl ";
            break; 
        case shrID: 
            s+="shr ";
            break;
        case sarID:
            s+="sar ";
    }
    value1->getir(s);
    s+=", ";
    value2->getir(s);
    s+='\n';
}

void EndStatement::getir(string &s)
{
    switch(this->tid)
    {
        case branchID:
            branch->getir(s);
            break;
        case jumpID:
            jump->getir(s);
            break;
        case returnID:
            ret->getir(s);
    }
}

void Store::getir(string &s)
{
    s+="store ";
    if(value!=nullptr)
        value->getir(s);
    else 
        initializer->getir(s);
    s+=", ";
    symbol->getir(s);
    s+='\n';
}

void MemoryDeclaration::getir(string &s)
{
    s+="alloc ";
    type->getir(s);
    s+='\n';
}

void Load::getir(string &s)
{
    s+="load ";
    symbol->getir(s);
    s+='\n';
}

void Jump::getir(string &s)
{
    s+="jump ";
    s+='%';
    symbol->getir(s);
    s+='\n';
}

void Branch::getir(string &s)
{
    s+="br ";
    assert(value!=nullptr);
    value->getir(s);
    s+=", ";
    assert(symbol1!=nullptr);
    s+='%';
    symbol1->getir(s);
    s+=", ";
    assert(symbol2!=nullptr);
    s+='%';
    symbol2->getir(s);
    s+="\n";
}

void FunCall::getir(string &s)
{
    s+="call @";
    symbol->getir(s);
    s+="(";
    for(int i=0;i<value_.size();i++)
    {
        value_[i]->getir(s);
        if(i<value_.size()-1)
            s+=", ";
    }
    s+=")\n";
}

void FunDecl::getir(string &s)
{
    s+="decl ";
    symbol->getir(s);
    s+="( ";
    if(fundeclparams!=nullptr)
        fundeclparams->getir(s);
    s+=") ";
    if(type!=nullptr)
    {
        s+=": ";
        type->getir(s);
    }
}

void FunDeclparams::getir(string &s)
{
    for(int i=0;i<type_.size();i++)
    {
        type_[i]->getir(s);
        if(i<type_.size()-1)
            s+=", ";
    }
}

void GlobalSymbolDef::getir(string &s)
{
    s+="global ";
    symbol->getir(s);
    s+="= ";
    globalmemorydeclaration->getir(s);
    s+='\n';
}

void GlobalMemoryDeclaration::getir(string &s)
{
    s+="alloc ";
    type->getir(s);
    s+=", ";
    initializer->getir(s);
}

void Initializer::getir(string &s)
{
    switch(this->tid)
    {
        case intID:
            s+=to_string(i32);
            break;
        case undefID:
            break;
        case aggreID:
            break;
        case zeroID:
            s+="0";
            break;
    }
}


void Type::accept(Visitor_&visitor) {
    visitor.Visit(*this);
}

void ArrayType::accept(Visitor_&visitor) {
    visitor.Visit(*this);
}

void PointerType::accept(Visitor_&visitor) {
    visitor.Visit(*this);
}

void FunType::accept(Visitor_&visitor) {
    visitor.Visit(*this);
}

void Value::accept(Visitor_&visitor) {
    visitor.Visit(*this);
}

void SYMBOL::accept(Visitor_&visitor) {
    visitor.Visit(*this);
}

void INT::accept(Visitor_&visitor) {
    visitor.Visit(*this);
}

void Initializer::accept(Visitor_&visitor) {
    visitor.Visit(*this);
}

void Aggregate::accept(Visitor_&visitor) {
    visitor.Visit(*this);
}

void SymbolDef::accept(Visitor_&visitor) {
    visitor.Visit(*this);
}

void GlobalSymbolDef::accept(Visitor_&visitor) {
    visitor.Visit(*this);
}

void MemoryDeclaration::accept(Visitor_&visitor) {
    visitor.Visit(*this);
}

void GlobalMemoryDeclaration::accept(Visitor_&visitor) {
    visitor.Visit(*this);
}

void Load::accept(Visitor_&visitor) {
    visitor.Visit(*this);
}

void Store::accept(Visitor_&visitor) {
    visitor.Visit(*this);
}

void GetPointer::accept(Visitor_&visitor) {
    visitor.Visit(*this);
}

void GetElementPointer::accept(Visitor_&visitor) {
    visitor.Visit(*this);
}

void BinaryExpr::accept(Visitor_&visitor) {
    visitor.Visit(*this);
}

void Branch::accept(Visitor_&visitor) {
    visitor.Visit(*this);
}

void Jump::accept(Visitor_&visitor) {
    visitor.Visit(*this);
}

void FunCall::accept(Visitor_&visitor) {
    visitor.Visit(*this);
}

void Return::accept(Visitor_&visitor) {
    visitor.Visit(*this);
}

void FunDef::accept(Visitor_&visitor) {
    visitor.Visit(*this);
}

void Funparams::accept(Visitor_&visitor) {
    visitor.Visit(*this);
}

void Funparam::accept(Visitor_&visitor) {
    visitor.Visit(*this);
}

void FunBody::accept(Visitor_&visitor) {
    visitor.Visit(*this);
}

void Block::accept(Visitor_&visitor) {
    visitor.Visit(*this);
}

void Statement::accept(Visitor_&visitor) {
    visitor.Visit(*this);
}

void EndStatement::accept(Visitor_&visitor) {
    visitor.Visit(*this);
}

void FunDecl::accept(Visitor_&visitor) {
    visitor.Visit(*this);
}

void FunDeclparams::accept(Visitor_&visitor) {
    visitor.Visit(*this);
}

void InitIR::accept(Visitor_&visitor) {
    visitor.Visit(*this);
}
