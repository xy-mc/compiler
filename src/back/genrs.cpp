#include "genrs.hpp"
#include<string>
using namespace std;
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
void GenRS::Visit(SYMBOL *ir)
{
    return;
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
    Visit(ir->endstatement);
}
void GenRS::Visit(Statement *ir)
{
    return;
}
void GenRS::Visit(EndStatement *ir)
{
    Visit(ir->ret);
    GenRS::rs+="ret";
}
void GenRS::Visit(Return *ir)
{
    GenRS::rs+="li a0,";
    Visit(ir->value);
}
void GenRS::Visit(Value *ir)
{
    Visit(ir->i32);
}
void GenRS::Visit(INT *ir)
{
    GenRS::rs+=to_string(ir->int_const)+"\n";
}