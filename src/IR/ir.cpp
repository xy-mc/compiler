#include<ir.hpp>
using namespace std;
void Type::getir(string &s) 
{
    switch (this->tid)
    {
        case I32TyID:
            s += "i32 ";
            break;
        case FunTyID:
            funtype->getir(s);
            break;
        case ArrayTyID:
            arraytype->getir(s);
            break;
        case PointerTyID:
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
    for(Statement *t:statement_)
        t->getir(s);
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
        // case StoreID:
        //     store->getir(s);
        //     break;
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