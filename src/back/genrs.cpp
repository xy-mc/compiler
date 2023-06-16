#include "genrs.hpp"
#include<assert.h>
#include<string>
#include<map>
using namespace std;

map<string,string>fhb_;
map<string,string>param_num;//存储参数该怎么获得
map<string,bool>global_def;//存储一个符号是否为全局变量
bool fun_iscall;//表示该函数内部是否call了一个新的函数
int paramnum;
SYMBOL *nowsymbol;
INT *nowint;
int initz=0;
int inita=0;//参数使用的寄存器
string stmt="";
int choose=0;
bool if_finalblock;//记录是否为一个函数的最后一个块
int sp_num;//记录sp的移动数目


void chuli(string t,string &s)
{
    switch (choose)
    {
        case 0:
            s+="    add "+t+", x0, x0\n";
            break;
        case 1:
            s+="    li "+t+", "+to_string(nowint->int_const)+'\n';
            break;
        case 2:
            s+="    lw "+t+", "+fhb_[nowsymbol->symbol]+'\n';
            break;
        case 3:
            return;
    }
}

void GenRS::Visit(InitIR &ir)
{
    if(!ir.globalsymboldef_.empty())
    {
        for(GlobalSymbolDef* t:ir.globalsymboldef_)
        {
            t->accept(*this);
        }
    }
    if(!ir.fundef_.empty())
    {
        for(FunDef* t:ir.fundef_)
        {
            t->accept(*this);
        }
    }
}

void GenRS::Visit(FunDef &ir)
{
    fhb_.clear();
    param_num.clear();
    inita=0;
    GenRS::rs+="\n    .text\n";
    GenRS::rs+="    .globl ";
    GenRS::rs+=ir.symbol->symbol+'\n';
    GenRS::rs+=ir.symbol->symbol;
    GenRS::rs+=":\n";
    sp_num=ir.def_num;
    if(sp_num)
    {
        GenRS::rs+="    addi sp, sp, -";
        GenRS::rs+=to_string(sp_num)+'\n';
    }
    if(ir.is_call)
    {
        fun_iscall=1;
        GenRS::rs+="    sw ra, "+to_string(sp_num-4)+"(sp)\n";
    }
    initz=max(ir.max_num-8,0)*4;
    if(ir.funparams!=nullptr)
        ir.funparams->accept(*this);
    ir.funbody->accept(*this);
    fun_iscall=0;
}

void GenRS::Visit(FunBody &ir)
{
    int i=0;
    if(!ir.block_.empty())
    {
        for(Block *t:ir.block_)
        {
            i++;
            if(i==ir.block_.size())
                if_finalblock=1;
            t->accept(*this);
        }
    }
}

void GenRS::Visit(Block &ir)
{
    GenRS::rs+=ir.symbol->symbol;
    GenRS::rs+=":\n";
    if(!ir.statement_.empty())
    {
        for(Statement *t:ir.statement_)
            t->accept(*this);
    }
    ir.endstatement->accept(*this);
}

void GenRS::Visit(Statement &ir)
{
    switch (ir.tid)
    {
        case Statement::SyDeID:
            ir.symboldef->accept(*this);
            break;
        case Statement::StoreID:
            ir.store->accept(*this);
            break;
        case Statement::FuncID:
            ir.funcall->accept(*this);
    }
}

void GenRS::Visit(SymbolDef &ir)
{
    string h=ir.symbol->symbol;
    switch(ir.tid)
    {
        case SymbolDef::MemID:
            return;
        case SymbolDef::LoadID:
            ir.load->accept(*this);
            break;
        case SymbolDef::BiEpID:
            ir.binaryexpr->accept(*this);
            break;
        case SymbolDef::FuncID:
            ir.symbol->accept(*this);
            ir.funcall->accept(*this);
            GenRS::rs+="    sw a0, "+fhb_[h]+'\n';
            return;
    }
    ir.symbol->accept(*this);
    GenRS::rs+="    sw t2, "+fhb_[h]+'\n';
}

void GenRS::Visit(BinaryExpr &ir)
{
    string t0="t0",t1="t1";
    switch(ir.tid)
    {
        case BinaryExpr::neID:
            ir.value1->accept(*this);
            chuli(t0,GenRS::rs);
            ir.value2->accept(*this);
            chuli(t1,GenRS::rs);
            GenRS::rs+="    sub t2, t0, t1\n";
            GenRS::rs+="    snez t2, t2\n";
            break;
        case BinaryExpr::eqID:
            ir.value1->accept(*this);
            chuli(t0,GenRS::rs);
            ir.value2->accept(*this);
            chuli(t1,GenRS::rs);
            GenRS::rs+="    sub t2, t0, t1\n";
            GenRS::rs+="    seqz t2, t2\n";
            break;
        case BinaryExpr::gtID: 
            ir.value1->accept(*this);
            chuli(t0,GenRS::rs);
            ir.value2->accept(*this);
            chuli(t1,GenRS::rs);
            GenRS::rs+="    sgt t2, t0, t1\n";
            break;
        case BinaryExpr::ltID:
            ir.value1->accept(*this);
            chuli(t0,GenRS::rs);
            ir.value2->accept(*this);
            chuli(t1,GenRS::rs);
            GenRS::rs+="    slt t2, t0, t1\n";
            break; 
        case BinaryExpr::geID:
            ir.value1->accept(*this);
            chuli(t0,GenRS::rs);
            ir.value2->accept(*this);
            chuli(t1,GenRS::rs);
            GenRS::rs+="    slt t2, t0, t1\n"; 
            GenRS::rs+="    seqz  t2, t2\n";
            break;
        case BinaryExpr::leID:
            ir.value1->accept(*this);
            chuli(t0,GenRS::rs);
            ir.value2->accept(*this);
            chuli(t1,GenRS::rs);
            GenRS::rs+="    sgt t2, t0, t1\n"; 
            GenRS::rs+="    seqz  t2, t2\n";
            break; 
        case BinaryExpr::addID:
            ir.value1->accept(*this);
            chuli(t0,GenRS::rs);
            ir.value2->accept(*this);
            chuli(t1,GenRS::rs);
            GenRS::rs+="    add t2, t0, t1\n"; 
            break; 
        case BinaryExpr::subID: 
            ir.value1->accept(*this);
            chuli(t0,GenRS::rs);
            ir.value2->accept(*this);
            chuli(t1,GenRS::rs);
            GenRS::rs+="    sub t2, t0, t1\n"; 
            break; 
        case BinaryExpr::mulID:
            ir.value1->accept(*this);
            chuli(t0,GenRS::rs);
            ir.value2->accept(*this);
            chuli(t1,GenRS::rs);
            GenRS::rs+="    mul t2, t0, t1\n"; 
            break;  
        case BinaryExpr::divID:
            ir.value1->accept(*this);
            chuli(t0,GenRS::rs);
            ir.value2->accept(*this);
            chuli(t1,GenRS::rs);
            GenRS::rs+="    div t2, t0, t1\n"; 
            break;  
        case BinaryExpr::modID:
            ir.value1->accept(*this);
            chuli(t0,GenRS::rs);
            ir.value2->accept(*this);
            chuli(t1,GenRS::rs);
            GenRS::rs+="    rem t2, t0, t1\n"; 
            break;  
        case BinaryExpr::andID:
            ir.value1->accept(*this);
            chuli(t0,GenRS::rs);
            ir.value2->accept(*this);
            chuli(t1,GenRS::rs);
            GenRS::rs+="    and t2, t0, t1\n"; 
            break;  
        case BinaryExpr::orID:
            ir.value1->accept(*this);
            chuli(t0,GenRS::rs);
            ir.value2->accept(*this);
            chuli(t1,GenRS::rs);
            GenRS::rs+="    or t2, t0, t1\n"; 
            break;  
        case BinaryExpr::xorID:
            ir.value1->accept(*this);
            chuli(t0,GenRS::rs);
            ir.value2->accept(*this);
            chuli(t1,GenRS::rs);
            GenRS::rs+="    xor t2, t0, t1\n"; 
            break;  
        case BinaryExpr::shlID:
            return; 
        case BinaryExpr::shrID:
            return; 
        case BinaryExpr::sarID:
            return;
    }
}

void GenRS::Visit(EndStatement &ir)
{
    switch (ir.tid)
    {
        case EndStatement::branchID:
            ir.branch->accept(*this);
            break;
        case EndStatement::jumpID:
            ir.jump->accept(*this);
            break;
        case EndStatement::returnID:
        {
            ir.ret->accept(*this);
            if(sp_num)
            {
                if(fun_iscall)
                {
                    GenRS::rs+="    lw ra, "+to_string(sp_num-4)+"(sp)\n";
                }
                GenRS::rs+="    addi sp, sp, ";
                GenRS::rs+=to_string(sp_num)+'\n';
            }
            GenRS::rs+="    ret\n";
        }
    }
}

void GenRS::Visit(Return &ir)
{
    if(ir.value!=nullptr)
        ir.value->accept(*this);
    else
        return;
    chuli("t2",GenRS::rs);
    GenRS::rs+="    add a0, t2, x0\n";
}

void GenRS::Visit(Value &ir)
{   
    switch (ir.tid)
    {
        case Value::SYMBOLID:
            ir.symbol->accept(*this);
            break;
        case Value::INTID:
            ir.i32->accept(*this);
            break;
        case Value::undefID:
            return;
    }
}
 
void GenRS::Visit(INT &ir)
{
    choose=1;
    nowint=&ir;
}

void GenRS::Visit(SYMBOL &ir)
{
    choose=2;
    string h=ir.symbol;
    if(global_def[h]&&fhb_.find(h)==fhb_.end())
    {
        fhb_[h]=to_string(initz)+"(sp)";
        initz+=4;
        GenRS::rs+="    la t0 , "+h.substr(1)+'\n';
        GenRS::rs+="    lw t0, 0(t0)\n";
        GenRS::rs+="    sw t0, "+fhb_[h]+'\n';
        return;
    }
    if(param_num.find(h)!=param_num.end())
    {
        choose=3;
        nowsymbol=&ir;
        return;
    }
    if(fhb_.find(h)==fhb_.end())
    {
        fhb_[h]=to_string(initz)+"(sp)";
        initz+=4;
    }
    nowsymbol=&ir;
}

void GenRS::Visit(Type &ir)
{
    return;
}

void GenRS::Visit(ArrayType &ir)
{
    return;
}

void GenRS::Visit(PointerType &ir)
{
    return;
}

void GenRS::Visit(FunType &ir)
{
    return;
}

void GenRS::Visit(Initializer &ir)
{
    switch(ir.tid)
    {
        case Initializer::intID:
        {
            GenRS::rs+="    .word "+to_string(ir.i32)+'\n';
            break;
        }
        case Initializer::undefID:
        {
            return;
        }
        case Initializer::aggreID:
        {
            return;
        }
        case Initializer::zeroID:
        {
            GenRS::rs+="    .zero 4\n";
            break;
        }
    }
}

void GenRS::Visit(Aggregate &ir)
{
    return;
}

void GenRS::Visit(GlobalSymbolDef &ir)
{
    GenRS::rs+="\n    .data\n";
    GenRS::rs+="    .global "+ir.symbol->symbol.substr(1)+'\n';
    GenRS::rs+=ir.symbol->symbol.substr(1)+":\n";
    global_def[ir.symbol->symbol]=1;
    ir.globalmemorydeclaration->accept(*this);
}

void GenRS::Visit(MemoryDeclaration &ir)
{
    return;
}

void GenRS::Visit(GlobalMemoryDeclaration &ir)
{
    ir.initializer->accept(*this);
}

void GenRS::Visit(Load &ir)
{
    ir.symbol->accept(*this);
    chuli("t2",GenRS::rs);
}

void GenRS::Visit(Store &ir)
{
    switch (ir.tid)
    {
        case Store::valueID:
            ir.value->accept(*this);
            chuli("t2",GenRS::rs);
            break;
        case Store::initID:
            return;
    }
    if(choose==3)
    {
        if(param_num[nowsymbol->symbol]=="null")
        {
            GenRS::rs+="    lw t2 , "+to_string(inita+sp_num)+"(sp)\n";
            GenRS::rs+="    sw t2 , "+fhb_[ir.symbol->symbol]+'\n';
            inita+=4;
            return;
        }
        GenRS::rs+="    sw "+param_num[nowsymbol->symbol]+", "+fhb_[ir.symbol->symbol]+'\n';
        return;
    }
    ir.symbol->accept(*this);
    string h=ir.symbol->symbol;
    GenRS::rs+="    sw t2, "+fhb_[h]+'\n';
}

void GenRS::Visit(GetPointer &ir)
{
    return;
}

void GenRS::Visit(GetElementPointer &ir)
{
    return;
}    

void GenRS::Visit(Branch &ir)
{
    ir.value->accept(*this);
    chuli("t2",GenRS::rs);
    GenRS::rs+="    bnez t2, ";
    GenRS::rs+=ir.symbol1->symbol+'\n';
    GenRS::rs+="    j ";
    GenRS::rs+=ir.symbol2->symbol;
    GenRS::rs+='\n';
}   

void GenRS::Visit(Jump &ir)
{
    GenRS::rs+="    j ";
    GenRS::rs+=ir.symbol->symbol;
    GenRS::rs+='\n';
}

void GenRS::Visit(FunCall &ir)
{
    int sp=0;
    inita=0;
    if(!ir.value_.empty())
    {
        for(Value *t:ir.value_)
        {
            if(inita<=7)
            {
                t->accept(*this);
                chuli("t2",GenRS::rs);
                GenRS::rs+="    add a"+to_string(inita)+",t2 ,x0\n";
                inita++;
            }
            else
            {
                t->accept(*this);
                chuli("t2",GenRS::rs);
                GenRS::rs+="    sw t2, "+to_string(sp)+"(sp)\n";
                sp+=4;
            }
        }
    }
    GenRS::rs+="    call "+ir.symbol->symbol+'\n';
}

void GenRS::Visit(Funparams &ir)
{
    paramnum=0;
    for(Funparam *t:ir.funparam_)
    {
        t->accept(*this);
    }
}   

void GenRS::Visit(Funparam &ir)
{
    string h=ir.symbol->symbol;
    if(paramnum>7)
    {
        param_num[h]="null";
    }
    else
    {
        param_num[h]="a"+to_string(paramnum);
    }
    paramnum++;
}

void GenRS::Visit(FunDecl &ir)
{
    return;
}  

void GenRS::Visit(FunDeclparams &ir)
{
    return;
}  
        