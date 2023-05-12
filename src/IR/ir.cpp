#include<ir.hpp>
using namespace std;
void Type::getir(string &s) 
{
    switch (this->tid_)
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
    switch (this->tid_)
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


void FunDef::getir(string &s)
{
    s+="fun ";
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