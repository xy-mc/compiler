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
    s+="} ";
}

void FunBody::getir(string &s)
{
    for (Block *t:block_)
        t->getir(s);
}

void Block::getir(string &s)
{
    symbol->getir(s);
    s+=": ";
    s+='\n';
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
        // case FuncID:
        //     funcall->getir(s);
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
        case ReturnID:
            ret->getir(s);
            s+='\n';
            break;
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

void FunDeclparms::accept(Visitor_&visitor) {
    visitor.Visit(*this);
}

void InitIR::accept(Visitor_&visitor) {
    visitor.Visit(*this);
}
