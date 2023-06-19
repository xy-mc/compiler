#include "genrs.hpp"//"符号表被清空了"
#include<assert.h>
#include<algorithm>
#include<string>
#include<map>
using namespace std;

class Fhb_node
{
    public:
        Fhb_node(int address_):address(address_){}
        int address;//记录符号的地址
        int is_point;//记录是否存的也是一个地址
        int is_potype;//记录是否为pointer类型
        string array_now;//记录它是哪个数组
        vector<int>multi_;//记录地址计算中需要的乘数
};
map<string,Fhb_node *>fhb_;//记录符号存储的位置(因为这个可能会被清空，所以我们需要重新设置一个全局的)
map<string,Fhb_node *>fhb_global;
map<string,string>param_num;//存储参数该怎么获得
map<string,bool>global_def;//存储一个符号是否为全局变量
bool fun_iscall;//表示该函数内部是否call了一个新的函数
int paramnum;
INT *nowint;
int initz=0;
int inita=0;//参数使用的寄存器
string stmt="";
int choose=0;
bool if_finalblock;//记录是否为一个函数的最后一个块
int sp_num;//记录sp的移动数目

bool is_load_store;//判断这个符号是load还是store,1是load，0是store
int dimension_now;//存储现在计算到哪一维
string id_now;//记录现在正在使用的符号'
string array_now;//记录现在对哪个数组进行指针运算
bool is_point;//记录是否是指针来访问
bool is_global;//记录是否为全局变量

int global_zero;
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
        {
            int address=fhb_[id_now]->address;
            if(address>=2047)
            {
                s+="    li t3, "+to_string(address)+'\n';
                s+="    add t3, sp, t3\n";
                s+="    lw "+t+", "+"0(t3)\n";
            }
            else
                s+="    lw "+t+", "+to_string(address)+"(sp)\n";
            break;
        }
        case 3:
            return;
    }
}

void getaddress(string &s,int address,string t)
{
    if(address>=2047)
    {
        s+="    li t3, "+to_string(address)+'\n';
        s+="    add t3, sp, t3\n";
        s+="    sw "+t+", 0(t3)\n";
    }
    else
        s+="    sw "+t+", "+to_string(address)+"(sp)\n";
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
    fhb_=fhb_global;
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
        if(sp_num>=2047)
        {
            GenRS::rs+="    li t2, "+to_string(sp_num)+'\n';
            GenRS::rs+="    sub sp, sp, t2\n";
        }
        else
        {
            GenRS::rs+="    addi sp, sp, -";
            GenRS::rs+=to_string(sp_num)+'\n';
        }
    }
    if(ir.is_call)
    {
        fun_iscall=1;
        if(sp_num>=2051)
        {
            GenRS::rs+="    li t0, "+to_string(sp_num-4)+'\n';
            GenRS::rs+="    add t2, sp, t0\n";
            GenRS::rs+="    sw ra, 0(t2)\n";
        }
        else
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
    id_now=ir.symbol->symbol;
    ir.symbol->accept(*this);
    switch(ir.tid)
    {
        case SymbolDef::MemID:
            ir.memorydeclaration->accept(*this);
            return;
        case SymbolDef::LoadID:
            ir.load->accept(*this);
            break;
        case SymbolDef::BiEpID:
            ir.binaryexpr->accept(*this);
            break;
        case SymbolDef::FuncID:
        {
            ir.funcall->accept(*this);
            int address=fhb_[ir.symbol->symbol]->address;
            getaddress(GenRS::rs,address,"a0");
            return;
        }
        case SymbolDef::GetPID:
            fhb_[id_now]->is_point=1;
            ir.getpointer->accept(*this);
            break;
        case SymbolDef::GetPmID:
            fhb_[id_now]->is_point=1;
            ir.getelemptr->accept(*this);
            break;
    }
    int address=fhb_[ir.symbol->symbol]->address;
    getaddress(GenRS::rs,address,"t2");
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
                    if(sp_num>=2051)
                    {
                        GenRS::rs+="    li t0, "+to_string(sp_num-4)+'\n';
                        GenRS::rs+="    add t2, sp, t0\n";
                        GenRS::rs+="    lw ra, 0(t2)\n";
                    }
                    else
                        GenRS::rs+="    lw ra, "+to_string(sp_num-4)+"(sp)\n";
                }
                if(sp_num>=2047)
                {
                    GenRS::rs+="    li t2, "+to_string(sp_num)+'\n';
                    GenRS::rs+="    add sp, sp, t2\n";
                }
                else
                {
                    GenRS::rs+="    addi sp, sp, ";
                    GenRS::rs+=to_string(sp_num)+'\n';
                }
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
    if(global_def[h]&&is_load_store)
    {
        GenRS::rs+="    la t0 , "+h.substr(1)+'\n';
        GenRS::rs+="    lw t0, 0(t0)\n";
        int address=fhb_[id_now]->address;
        if(address>=2047)
        {
            GenRS::rs+="    li t1, "+to_string(address)+'\n';
            GenRS::rs+="    add t1, sp, t1\n";
            GenRS::rs+="    sw t0, 0(t1)\n";
        }
        else
            GenRS::rs+="    sw t0, "+to_string(address)+"(sp)\n";
        return;
    }
    id_now=ir.symbol;
    if(param_num.find(id_now)!=param_num.end())
    {
        choose=3;
        return;
    }
    if(fhb_.find(id_now)==fhb_.end())
    {
        Fhb_node *node=new Fhb_node(initz); 
        initz+=4;
        fhb_[id_now]=node;
    }
}

void GenRS::Visit(Type &ir)
{
    switch(ir.tid)
    {
        case Type::i32ID:
        {
            if(is_point)
            {
                fhb_[id_now]->multi_.push_back(1);
                fhb_[id_now]->multi_.push_back(1);
            }
            global_zero=4;
            break;
        }
        case Type::arrayID:
            ir.arraytype->accept(*this);
            break;
        case Type::poterID:
            ir.pointertype->accept(*this);
            break;
        case Type::funID:
            ir.funtype->accept(*this);
            break;
    }
}

void GenRS::Visit(ArrayType &ir)
{
    if(global_def[id_now])
    {
        fhb_global[id_now]->multi_=ir.multiple_;
        global_zero=ir.multiple_[0]*4;
        return;
    }
    if(!is_point)
    {
        initz-=4;
        initz+=ir.multiple_[0]*4;
        fhb_[id_now]->multi_=ir.multiple_;
    }
    else
    {
        std::reverse(ir.multiple_.begin(), ir.multiple_.end());
        ir.multiple_.push_back(0);
        std::reverse(ir.multiple_.begin(), ir.multiple_.end());
        fhb_[id_now]->multi_=ir.multiple_;
    }
}

void GenRS::Visit(PointerType &ir)
{
    is_point=1;
    fhb_[id_now]->is_potype=1;
    ir.type->accept(*this);
    is_point=0;
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
            ir.aggregate->accept(*this);
            break;
        }
        case Initializer::zeroID:
        {
            GenRS::rs+="    .zero "+to_string(global_zero)+'\n';
            break;
        }
    }
}

void GenRS::Visit(Aggregate &ir)
{
    for(Initializer *t:ir.initialzer_)
    {
        t->accept(*this);
    }
}

void GenRS::Visit(GlobalSymbolDef &ir)
{
    GenRS::rs+="\n    .data\n";
    GenRS::rs+="    .global "+ir.symbol->symbol.substr(1)+'\n';
    GenRS::rs+=ir.symbol->symbol.substr(1)+":\n";
    global_def[ir.symbol->symbol]=1;
    id_now=ir.symbol->symbol;
    Fhb_node *node=new Fhb_node(0); 
    fhb_global[id_now]=node;
    ir.globalmemorydeclaration->accept(*this);
}

void GenRS::Visit(MemoryDeclaration &ir)
{
    ir.type->accept(*this);
}

void GenRS::Visit(GlobalMemoryDeclaration &ir)
{
    ir.type->accept(*this);
    ir.initializer->accept(*this);
}

void GenRS::Visit(Load &ir)
{
    is_load_store=1;
    string h=ir.symbol->symbol;
    if(fhb_[h]->is_potype==1)
    {
        fhb_[id_now]->is_potype=1;
        fhb_[id_now]->array_now=h;
        array_now=h;
    }
    ir.symbol->accept(*this);
    int address=fhb_[h]->address;
    if(fhb_[h]->is_point==1)
    {
        if(address>=2047)
        {
            GenRS::rs+="    li t3, "+to_string(address)+'\n';
            GenRS::rs+="    add t3, sp, t3\n";
            GenRS::rs+="    lw t0, 0(t3)\n";
        }
        else
            GenRS::rs+="    lw t0, "+to_string(address)+"(sp)\n";
        GenRS::rs+="    lw t2, 0(t0)\n";
        return;
    }
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
        if(param_num[id_now]=="null")
        {
            int address=inita+sp_num;
            if(address>=2047)
            {
                GenRS::rs+="    li t3, "+to_string(address)+'\n';
                GenRS::rs+="    add t3, sp, t3\n";
                GenRS::rs+="    lw t2, 0(t3)\n";
            }
            else
                GenRS::rs+="    lw t2, "+to_string(address)+"(sp)\n";
            address=fhb_[ir.symbol->symbol]->address;
            getaddress(GenRS::rs,address,"t2");
            inita+=4;
            return;
        }
        int address=fhb_[ir.symbol->symbol]->address;
        getaddress(GenRS::rs,address,param_num[id_now]);
        return;
    }
    is_load_store=0;
    ir.symbol->accept(*this);
    string h=ir.symbol->symbol;
    if(global_def[h])
    {
        GenRS::rs+="    la t0 , "+h.substr(1)+'\n';
        GenRS::rs+="    sw t2 , 0(t0)\n";
        return;
    }
    int address=fhb_[h]->address;
    if(fhb_[h]->is_point==1)
    {
        // cout<<h<<endl;
        if(address>=2047)
        {
            GenRS::rs+="    li t3, "+to_string(address)+'\n';
            GenRS::rs+="    add t3, sp, t3\n";
            GenRS::rs+="    lw t0, 0(t3)\n";
        }
        else
            GenRS::rs+="    lw t0, "+to_string(address)+"(sp)\n";
        GenRS::rs+="    sw t2, 0(t0)\n";
        return;
    }
    getaddress(GenRS::rs,address,"t2");
}

void GenRS::Visit(GetPointer &ir)
{
    int address=fhb_[ir.symbol->symbol]->address;
    if(fhb_[ir.symbol->symbol]->is_potype==1)
    {
        array_now=fhb_[ir.symbol->symbol]->array_now;
        dimension_now=0;
        address=fhb_[array_now]->address;
        if(address>=2047)
        {
            GenRS::rs+="    li t3, "+to_string(address)+'\n';
            GenRS::rs+="    add t3, sp, t3\n";
            GenRS::rs+="    lw t0, 0(t3)\n";
        }
        else
            GenRS::rs+="    lw t0, "+to_string(address)+"(sp)\n";
        GenRS::rs+="    mv t4, t0\n";
    }
    else if(fhb_[ir.symbol->symbol]->multi_.size()!=0)
    {
        array_now=ir.symbol->symbol;
        dimension_now=0;
        if(global_def[array_now])
        {
            GenRS::rs+="    la t4 , "+array_now.substr(1)+'\n';
        }
        else
        {
            if(address>=2047)
            {
                GenRS::rs+="    li t0, "+to_string(address)+'\n';
                GenRS::rs+="    add t4, sp, t0\n";
            }
            else
                GenRS::rs+="    addi t4, sp, "+to_string(address)+'\n';
        }
    }
    else
    {
        if(address>=2047)
        {
            GenRS::rs+="    li t3, "+to_string(address)+'\n';
            GenRS::rs+="    add t3, sp, t3\n";
            GenRS::rs+="    lw t0, 0(t3)\n";
        }
        else
            GenRS::rs+="    lw t0, "+to_string(address)+"(sp)\n";
        GenRS::rs+="    mv t4, t0\n";
    }
    dimension_now+=1;
    ir.value->accept(*this);
    chuli("t1",GenRS::rs);
    GenRS::rs+="    li t2, "+to_string(4*fhb_[array_now]->multi_[dimension_now])+'\n';
    GenRS::rs+="    mul t1, t1, t2\n";
    GenRS::rs+="    add t2, t4, t1\n";
}

void GenRS::Visit(GetElementPointer &ir)
{
    int address=fhb_[ir.symbol->symbol]->address;
    if(fhb_[ir.symbol->symbol]->multi_.size()!=0)
    {
        array_now=ir.symbol->symbol;
        dimension_now=0;
        if(global_def[array_now])
        {
            GenRS::rs+="    la t4 , "+array_now.substr(1)+'\n';
        }
        else
        {
            if(address>=2047)
            {
                GenRS::rs+="    li t0, "+to_string(address)+'\n';
                GenRS::rs+="    add t4, sp, t0\n";
            }
            else
                GenRS::rs+="    addi t4, sp, "+to_string(address)+'\n';
        }
    }
    else
    {
        if(address>=2047)
        {
            GenRS::rs+="    li t3, "+to_string(address)+'\n';
            GenRS::rs+="    add t3, sp, t3\n";
            GenRS::rs+="    lw t0, 0(t3)\n";
        }
        else
            GenRS::rs+="    lw t0, "+to_string(address)+"(sp)\n";
        GenRS::rs+="    mv t4, t0\n";
    }
    dimension_now+=1;
    ir.value->accept(*this);
    chuli("t1",GenRS::rs);
    GenRS::rs+="    li t2, "+to_string(4*fhb_[array_now]->multi_[dimension_now])+'\n';
    GenRS::rs+="    mul t1, t1, t2\n";
    GenRS::rs+="    add t2, t4, t1\n";
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
            t->accept(*this);
            if(inita<=7)
            {
                chuli("t2",GenRS::rs);
                GenRS::rs+="    add a"+to_string(inita)+",t2 ,x0\n";
                inita++;
            }
            else
            {
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
        