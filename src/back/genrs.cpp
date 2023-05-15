#include "genrs.hpp"
#include<string>
#include<map>
using namespace std;

map<string,string>fhb;
SYMBOL *nowsymbol;
INT *nowint;
int initz=4;
string stmt="";
void GenRS::Visit(InitIR *ir)
{
    GenRS::rs+=".text\n";
    if(!ir->globalsymboldef_.empty())
    {

    }
    GenRS::rs+=".globl main\n";
    if(!ir->fundef_.empty())
    {
        for(FunDef* t:ir->fundef_)
        {
            Visit(t);
        }
    }
}

void GenRS::Visit(FunDef *ir)
{
    GenRS::rs+=ir->symbol->symbol;
    GenRS::rs+=":\n";
    Visit(ir->funbody);
}

void GenRS::Visit(FunBody *ir)
{
    if(!ir->block_.empty())
    {
        for(Block *t:ir->block_)
            Visit(t);
    }
}

void GenRS::Visit(Block *ir)
{
    if(!ir->statement_.empty())
    {
        for(Statement *t:ir->statement_)
            Visit(t);
    }
    Visit(ir->endstatement);
}

void GenRS::Visit(Statement *ir)
{
    switch (ir->tid)
    {
        case Statement::SyDeID:
            Visit(ir->symboldef);
            break;
    }
}

void GenRS::Visit(SymbolDef *ir)
{
    switch(ir->tid)
    {
        case SymbolDef::BiEpID:
            Visit(ir->binaryexpr);
            break;
    }
    Visit(ir->symbol);
    string h=ir->symbol->symbol;
    fhb[h]=to_string(initz)+"(sp)";
    initz+=4;
    GenRS::rs+="sw t2, "+fhb[h]+'\n';
}

int choose;

void chuli(string t,string &s)
{
    switch (choose)
    {
        case 0:
            s+="add "+t+", x0, x0\n";
            break;
        case 1:
            s+="lw "+t+", "+fhb[to_string(nowint->int_const)]+'\n';
            break;
        case 2:
            s+="lw "+t+", "+fhb[nowsymbol->symbol]+'\n';
    }
}

void GenRS::Visit(BinaryExpr *ir)
{
    string t0="t0",t1="t1";
    switch(ir->tid)
    {
        case BinaryExpr::neID:
            Visit(ir->value1);
            chuli(t0,GenRS::rs);
            Visit(ir->value2);
            chuli(t1,GenRS::rs);
            GenRS::rs+="sub t1, t0, t1\n";
            GenRS::rs+="snez t2, t1\n";
            break;
        case BinaryExpr::eqID:
            Visit(ir->value1);
            chuli(t0,GenRS::rs);
            Visit(ir->value2);
            chuli(t1,GenRS::rs);
            GenRS::rs+="sub t1, t0, t1\n";
            GenRS::rs+="seqz t2, t1\n";
            break;
        case BinaryExpr::gtID: 
            Visit(ir->value1);
            chuli(t0,GenRS::rs);
            Visit(ir->value2);
            chuli(t1,GenRS::rs);
            GenRS::rs+="sgt t2, t0, t1\n";
            break;
        case BinaryExpr::ltID:
            Visit(ir->value1);
            chuli(t0,GenRS::rs);
            Visit(ir->value2);
            chuli(t1,GenRS::rs);
            GenRS::rs+="slt t2, t0, t1\n";
            break; 
        case BinaryExpr::geID:
            Visit(ir->value1);
            chuli(t0,GenRS::rs);
            Visit(ir->value2);
            chuli(t1,GenRS::rs);
            GenRS::rs+="slt t2, t0, t1\n"; 
            GenRS::rs+="seqz  t1, t1\n";
            break;
        case BinaryExpr::leID:
            Visit(ir->value1);
            chuli(t0,GenRS::rs);
            Visit(ir->value2);
            chuli(t1,GenRS::rs);
            GenRS::rs+="sgt t2, t0, t1\n"; 
            GenRS::rs+="seqz  t1, t1\n";
            break; 
        case BinaryExpr::addID:
            Visit(ir->value1);
            chuli(t0,GenRS::rs);
            Visit(ir->value2);
            chuli(t1,GenRS::rs);
            GenRS::rs+="add t2, t0, t1\n"; 
            break; 
        case BinaryExpr::subID: 
            Visit(ir->value1);
            chuli(t0,GenRS::rs);
            Visit(ir->value2);
            chuli(t1,GenRS::rs);
            GenRS::rs+="sub t2, t0, t1\n"; 
            break; 
        case BinaryExpr::mulID:
            Visit(ir->value1);
            chuli(t0,GenRS::rs);
            Visit(ir->value2);
            chuli(t1,GenRS::rs);
            GenRS::rs+="mul t2, t0, t1\n"; 
            break;  
        case BinaryExpr::divID:
            Visit(ir->value1);
            chuli(t0,GenRS::rs);
            Visit(ir->value2);
            chuli(t1,GenRS::rs);
            GenRS::rs+="div t2, t0, t1\n"; 
            break;  
        case BinaryExpr::modID:
            Visit(ir->value1);
            chuli(t0,GenRS::rs);
            Visit(ir->value2);
            chuli(t1,GenRS::rs);
            GenRS::rs+="rem t2, t0, t1\n"; 
            break;  
        case BinaryExpr::andID:
            Visit(ir->value1);
            chuli(t0,GenRS::rs);
            Visit(ir->value2);
            chuli(t1,GenRS::rs);
            GenRS::rs+="and t2, t0, t1\n"; 
            break;  
        case BinaryExpr::orID:
            Visit(ir->value1);
            chuli(t0,GenRS::rs);
            Visit(ir->value2);
            chuli(t1,GenRS::rs);
            GenRS::rs+="or t2, t0, t1\n"; 
            break;  
        case BinaryExpr::xorID:
            Visit(ir->value1);
            chuli(t0,GenRS::rs);
            Visit(ir->value2);
            chuli(t1,GenRS::rs);
            GenRS::rs+="xor t2, t0, t1\n"; 
            break;  
        case BinaryExpr::shlID:
            return; 
        case BinaryExpr::shrID:
            return; 
        case BinaryExpr::sarID:
            return;
    }
}

void GenRS::Visit(EndStatement *ir)
{
    Visit(ir->ret);
    GenRS::rs+="ret";
}

void GenRS::Visit(Return *ir)
{
    GenRS::rs+="add a0, t2, x0";
    Visit(ir->value);
}

void GenRS::Visit(Value *ir)
{
    switch (ir->tid)
    {
        case Value::SYMBOLID:
            Visit(ir->symbol);
            break;
        case Value::INTID:
            Visit(ir->i32);
            break;
        case Value::undefID:
            return;
    }
}
 
void GenRS::Visit(INT *ir)
{
    choose=1;
    string h=to_string(ir->int_const);
    if(ir->int_const==0)
    {
        choose=0;
        fhb[h]="x0";
    }
    else if(fhb.find(h)==fhb.end())
    {
        fhb[h]=to_string(initz)+"(sp)";
        initz+=4;
        GenRS::rs+="li t0, "+h+'\n';
        GenRS::rs+="sw t0, "+fhb[h]+'\n';
    }
    nowint=ir;
}

void GenRS::Visit(SYMBOL *ir)
{
    choose=2;
    nowsymbol=ir;
}