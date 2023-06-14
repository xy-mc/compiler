#include "genIR.hpp"
#include <map>
#include <string>
#include <cassert>
#include <iostream>
#include <algorithm>
using namespace std;

vector<Block *>block_;
vector<Statement *>stmt_;
vector<Funparam *>funparam_;
EndStatement *endstmt;
FunDef *nowfun;
int defnum_jubu;//存储需要放在栈中的局部变量
int max_sum;//存储某个call中对多的参数个数
bool is_call;//存储是否出现call指令
Type *nowfuntype;
Funparams *nowfunparams;
Block *nowblock;
SYMBOL *block_symbol;//此block的名字
Statement *nowstate;
Value *nowvalue;
FunCall *nowfuncall;
int inits=0;
int initb=0;
int get_value;
bool lval_wr;//0表示lval出现在左边，反之出现在右边
Scope *scope=new Scope();
string nowid;                                                                                                                
SYMBOL *true_block,*false_block;
SYMBOL *break_block,*continue_block;
bool in_ifexp;//是if的exp中，都可以用短路
bool is_luoji;//是否为逻辑表达式
map<string,int>def_number;//存储第几个相同变量来满足SSA
map<string,bool>funcall_type;//存储函数是否为void
string luoji="@luoji";
bool funblock;//判断该block是否为函数后面直接跟着的
int funcrp_choose;//判断explist是参数还是初始化，如果是初始化是要按部就班还是直接生成nowinit
Initializer *nowinit;
ArrayType *nowtype;

bool is_explist;//判断这个语法树的作用，1为使用值，0为数组初始化
vector<int>value_;//存储数组的初始化时获得的一系列数字,全局数组
vector<int>multiple_;//存储数组的倍数
vector<int>dimension_;//存储数组的维数
int dimension;

string get_name(string s)
{
    string name;
    if(def_number.find(s)==def_number.end())
    {
        def_number[s]=1;
        name=s;
    }
    else
    {
        def_number[s]++;
        name=s+"_"+to_string(def_number[s]);
    }
    return name;
}

void get_block()
{
    if(block_symbol==nullptr)
        block_symbol=new SYMBOL("block_"+to_string(initb++));
    nowblock=new Block(block_symbol,stmt_,endstmt);
    stmt_.clear();
    block_.push_back(nowblock);
    nowblock=nullptr;
    endstmt=nullptr;
    block_symbol=nullptr;
}

void GenIR::visit(CompUnitAST& ast)
{
    scope->enter();
    Initializer *initializer=new Initializer(Initializer::intID,0,nullptr);
    Type *type=new Type(Type::i32ID);
    GlobalMemoryDeclaration *globalmemorydeclaration=new GlobalMemoryDeclaration(type,initializer);
    SYMBOL *symbol=new SYMBOL(luoji);
    GlobalSymbolDef *globalsymboldef=new GlobalSymbolDef(symbol,globalmemorydeclaration);
    initir->globalsymboldef_.push_back(globalsymboldef);
    funcall_type["getint"]=1;
    funcall_type["getch"]=1;
    funcall_type["getarray"]=1;
    if(!ast.decldef_.empty())
    {
        for(auto &t:ast.decldef_)
        {
            t->accept(*this);
        }
    }
    scope->exit();
}

void GenIR::visit(DeclDefAST &ast)
{
    switch(ast.tid)
    {
        case DeclDefAST::declID:
            ast.decl->accept(*this);
            break;
        case DeclDefAST::funcID:
            ast.funcdef->accept(*this);
            break;
    }
}

void GenIR::visit(FuncDefAST& ast)
{
    scope->enter();
    defnum_jubu=0;
    SYMBOL *symbol=new SYMBOL(ast.ident);
    ast.btype->accept(*this);
    if(nowfuntype==nullptr)
        funcall_type[ast.ident]=0;
    else
        funcall_type[ast.ident]=1;
    if(ast.funcfparams!=nullptr)
        ast.funcfparams->accept(*this);
    nowfunparams=new Funparams(funparam_);
    funparam_.clear();
    funblock=1;
    ast.block->accept(*this);
    funblock=0;
    scope->exit();
    if(!stmt_.empty())
    {
        Return *ret=new Return(nullptr);
        endstmt=new EndStatement(EndStatement::returnID,nullptr,nullptr,ret);
        get_block();
    }
    FunBody *funbody=new FunBody(block_);
    block_.clear();
    if(is_call)
        defnum_jubu++;
    defnum_jubu+=max(max_sum-8,0);
    int num=defnum_jubu*4;
    nowfun=new FunDef(symbol,nowfunparams,nowfuntype,funbody,(num + 15) & ~15,is_call,max_sum);
    is_call=0;
    max_sum=0;
    initir->fundef_.push_back(nowfun);
    nowfun=nullptr;
}

void GenIR::visit(BTypeAST& ast)
{
    switch (ast.tid)
    {
        case BTypeAST::intID:
            nowfuntype=new Type(Type::i32ID);
            break;
        case BTypeAST::voidID:
            nowfuntype=nullptr;
            break;
    }
}

void GenIR::visit(FuncFParamsAST& ast)
{
    if(!ast.funcfparam_.empty())
    {
        for(auto &t:ast.funcfparam_)
        {
            t->accept(*this);
        }
    }
}

void GenIR::visit(FuncFParamAST& ast)
{
    Type *type=new Type(Type::i32ID);
    Def *def=new Def(Def::funID,0,ast.ident);
    assert(scope->push(ast.ident,def));
    SYMBOL *symbol1=new SYMBOL("@"+ast.ident);
    Funparam *funparam=new Funparam(symbol1,type);
    funparam_.push_back(funparam);
    funparam=nullptr;
    MemoryDeclaration *memorydeclaration=new MemoryDeclaration(type);
    SYMBOL *symbol2=new SYMBOL("%"+ast.ident);
    SymbolDef *symboldef=new SymbolDef(symbol2,SymbolDef::MemID,memorydeclaration,nullptr,nullptr,nullptr,nullptr,nullptr);
    nowstate=new Statement(Statement::SyDeID,symboldef,nullptr,nullptr);
    defnum_jubu++;
    stmt_.push_back(nowstate);
    nowstate=nullptr;
    Store *store=new Store(Store::valueID,symbol1,nullptr,symbol2);
    nowstate=new Statement(Statement::StoreID,nullptr,store,nullptr);
    stmt_.push_back(nowstate);
    nowstate=nullptr;
}

void GenIR::visit(BlockAST& ast)
{
    if(!ast.blockitem_.empty())
    {
        for(auto &t:ast.blockitem_)
        {
            t->accept(*this);
        }
    }
    else if(funblock)
    {
        Return *ret=new Return(nullptr);
        endstmt=new EndStatement(EndStatement::returnID,nullptr,nullptr,ret);
        get_block();
    }
}

void GenIR::visit(BlockItemAST& ast)
{
    switch(ast.tid)
    {
        case BlockItemAST::declID:
            ast.decl->accept(*this);
            break;
        case BlockItemAST::stmtID:
            ast.stmt->accept(*this);
            break;
    }
}

void GenIR::visit(StmtAST& ast)
{
    switch(ast.tid)
    {
        case StmtAST::lvalID:
        {
            ast.exp->accept(*this);
            get_value=ast.exp->getvalue();
            lval_wr=0;
            ast.lval->accept(*this);
            break;
        }
        case StmtAST::expID:
        {
            ast.exp->accept(*this);
            break;
        }
        case StmtAST::nexpID:
            break;
        case StmtAST::blockID:
        {
            scope->enter();
            funblock=0;
            ast.block->accept(*this);
            scope->exit();
            break;
        }
        case StmtAST::rexpID:
        {
            ast.exp->accept(*this);
            Return *ret=new Return(nowvalue);
            endstmt=new EndStatement(EndStatement::returnID,nullptr,nullptr,ret);
            get_block();
            break;
        }
        case StmtAST::rnexpID:
        {
            Return *ret=new Return(nullptr);
            endstmt=new EndStatement(EndStatement::returnID,nullptr,nullptr,ret);
            get_block();
            break;
        }
        case StmtAST::ifID:
        {
            auto block1=true_block;
            auto block2=false_block;
            true_block=new SYMBOL("block_"+to_string(initb++));
            false_block=new SYMBOL("block_"+to_string(initb++));
            in_ifexp=true;
            ast.exp->accept(*this);
            in_ifexp=false;
            block_symbol=true_block;
            ast.ifstmt->accept(*this);
            Jump *jump=new Jump(false_block);
            endstmt=new EndStatement(EndStatement::jumpID,nullptr,jump,nullptr);
            get_block();
            block_symbol=false_block;
            true_block=block1;
            false_block=block2;
            break;
        }
        case StmtAST::ifelID:
        {
            auto block1=true_block;
            auto block2=false_block;
            true_block=new SYMBOL("block_"+to_string(initb++));
            false_block=new SYMBOL("block_"+to_string(initb++));
            SYMBOL *to_block=new SYMBOL("block_"+to_string(initb++));
            in_ifexp=true;
            ast.exp->accept(*this);
            in_ifexp=false;
            block_symbol=true_block;
            ast.ifstmt->accept(*this);
            Jump *jump=new Jump(to_block);
            endstmt=new EndStatement(EndStatement::jumpID,nullptr,jump,nullptr);
            get_block();
            block_symbol=false_block;
            ast.elsestmt->accept(*this);
            endstmt=new EndStatement(EndStatement::jumpID,nullptr,jump,nullptr);
            get_block();
            block_symbol=to_block;
            true_block=block1;
            false_block=block2;
            break;
        }
        case StmtAST::whileID:
        {
            auto block1=true_block;
            auto block2=false_block;
            auto block3=break_block;
            auto block4=continue_block;
            true_block=new SYMBOL("block_"+to_string(initb++));
            false_block=new SYMBOL("block_"+to_string(initb++));
            SYMBOL *to_block=new SYMBOL("block_"+to_string(initb++));
            break_block=false_block;
            continue_block=to_block;
            Jump *jump=new Jump(to_block);
            endstmt=new EndStatement(EndStatement::jumpID,nullptr,jump,nullptr);
            get_block();
            block_symbol=to_block;
            in_ifexp=true;
            ast.exp->accept(*this);
            in_ifexp=false;
            block_symbol=true_block;
            ast.whilestmt->accept(*this);
            endstmt=new EndStatement(EndStatement::jumpID,nullptr,jump,nullptr);
            get_block();
            block_symbol=false_block;
            true_block=block1;
            false_block=block2;
            break_block=block3;
            continue_block=block4;
            break;
        }
        case StmtAST::breakID:
        {
            auto block1=true_block;
            auto block2=false_block;
            Jump *jump=new Jump(break_block);
            endstmt=new EndStatement(EndStatement::jumpID,nullptr,jump,nullptr);
            get_block();
            true_block=block1;
            false_block=block2;
            break;
        }
        case StmtAST::continueID:
        {
            auto block1=true_block;
            auto block2=false_block;
            Jump *jump=new Jump(continue_block);
            endstmt=new EndStatement(EndStatement::jumpID,nullptr,jump,nullptr);
            get_block();
            true_block=block1;
            false_block=block2;
            break;
        }
    }
}

void GenIR::visit(ExpAST& ast)
{
    auto block1=true_block;
    auto block2=false_block;
    int is_luoji_=is_luoji;
    if(!in_ifexp)
    {
        true_block=new SYMBOL("block_"+to_string(initb++));
        false_block=new SYMBOL("block_"+to_string(initb++));
    }
    is_luoji=0;
    ast.lorexp->accept(*this);
    if(in_ifexp)
    {
        Branch *branch=new Branch(nowvalue,true_block,false_block);
        endstmt=new EndStatement(EndStatement::branchID,branch,nullptr,nullptr);
        get_block();
    }
    if(is_luoji&&!in_ifexp)
    {
        Branch *branch=new Branch(nowvalue,true_block,false_block);
        endstmt=new EndStatement(EndStatement::branchID,branch,nullptr,nullptr);
        get_block();

        SYMBOL *block_to=new SYMBOL("block_"+to_string(initb++));
        Jump *jump=new Jump(block_to);
        SYMBOL *symbol=new SYMBOL(luoji);

        Value *value1=new INT(1);
        Value *value2=new INT(0);

        block_symbol=true_block;
        Store *store1=new Store(Store::valueID,value1,nullptr,symbol);
        Statement *newstmt1=new Statement(Statement::StoreID,nullptr,store1,nullptr);
        stmt_.push_back(newstmt1);
        endstmt=new EndStatement(EndStatement::jumpID,nullptr,jump,nullptr);
        get_block();

        block_symbol=false_block;
        Store *store2=new Store(Store::valueID,value2,nullptr,symbol);
        Statement *newstmt2=new Statement(Statement::StoreID,nullptr,store2,nullptr);
        stmt_.push_back(newstmt2);
        endstmt=new EndStatement(EndStatement::jumpID,nullptr,jump,nullptr);
        get_block();

        block_symbol=block_to;
        Load *load=new Load(symbol);
        SYMBOL *symbol2=new SYMBOL("%"+to_string(inits++));
        nowvalue=symbol2;
        SymbolDef *symboldef=new SymbolDef(symbol2,SymbolDef::LoadID,nullptr,load,nullptr,nullptr,nullptr,nullptr);
        defnum_jubu++;
        nowstate=new Statement(Statement::SyDeID,symboldef,nullptr,nullptr);
        stmt_.push_back(nowstate);
    }
    is_luoji=is_luoji_;
    true_block=block1;
    false_block=block2;
}

void GenIR::visit(LAndExpAST& ast)
{
    auto block1=true_block;
    auto block2=false_block;
    switch(ast.tid)
    {
        case LAndExpAST::eqID:
        {
            ast.eqexp->accept(*this);
            break;
        }
        case LAndExpAST::landID:
        {
            is_luoji=1;
            SYMBOL *y_block=new SYMBOL("block_"+to_string(initb++));
            true_block=y_block;
            ast.landexp->accept(*this);
            true_block=block1;
            Branch *branch1=new Branch(nowvalue,y_block,false_block);
            endstmt=new EndStatement(EndStatement::branchID,branch1,nullptr,nullptr);
            get_block();
            block_symbol=y_block;
            ast.eqexp->accept(*this);
            break;
        }
    }
    true_block=block1;
    false_block=block2;
}

void GenIR::visit(LOrExpAST& ast)
{
    auto block1=true_block;
    auto block2=false_block;
    switch(ast.tid)
    {
        case LOrExpAST::landID:
        {
            ast.landexp->accept(*this);
            break;
        }
        case LOrExpAST::lorID:
        {
            is_luoji=1;
            SYMBOL *y_block=new SYMBOL("block_"+to_string(initb++));
            false_block=y_block;
            ast.lorexp->accept(*this);
            false_block=block2;
            Branch *branch=new Branch(nowvalue,true_block,y_block);
            endstmt=new EndStatement(EndStatement::branchID,branch,nullptr,nullptr);
            get_block();
            block_symbol=y_block;
            ast.landexp->accept(*this);
            break;
        }
    }
    true_block=block1;
    false_block=block2;
}

void GenIR::visit(MulExpAST& ast)
{
    Value *value1;
    Value *value2;
    BinaryExpr *bx;
    switch(ast.tid)
    {
        case MulExpAST::unarID:
            ast.unaryexp->accept(*this);
            return;
        case MulExpAST::mulID:
            ast.mulexp->accept(*this);
            value1=nowvalue;
            ast.unaryexp->accept(*this);
            value2=nowvalue;
            bx=new BinaryExpr(BinaryExpr::mulID,value1,value2);
            break;
        case MulExpAST::divID:
            ast.mulexp->accept(*this);
            value1=nowvalue;
            ast.unaryexp->accept(*this);
            value2=nowvalue;
            bx=new BinaryExpr(BinaryExpr::divID,value1,value2);
            break;
        case MulExpAST::modID:
            ast.mulexp->accept(*this);
            value1=nowvalue;
            ast.unaryexp->accept(*this);
            value2=nowvalue;
            bx=new BinaryExpr(BinaryExpr::modID,value1,value2);
            break;
    }
    SYMBOL *symbol=new SYMBOL("%"+to_string(inits++));
    nowvalue=symbol;
    SymbolDef *symboldef=new SymbolDef(symbol,SymbolDef::BiEpID,nullptr,nullptr,nullptr,nullptr,bx,nullptr);
    defnum_jubu++;
    nowstate=new Statement(Statement::SyDeID,symboldef,nullptr,nullptr);
    stmt_.push_back(nowstate);
    nowstate=nullptr;
}

void GenIR::visit(AddExpAST& ast)
{
    Value *value1;
    Value *value2;
    BinaryExpr *bx;
    switch(ast.tid)
    {
        case AddExpAST::mulID:
            ast.mulexp->accept(*this);
            return;
        case AddExpAST::addID:
            ast.addexp->accept(*this);
            value1=nowvalue;
            ast.mulexp->accept(*this);
            value2=nowvalue;
            bx=new BinaryExpr(BinaryExpr::addID,value1,value2);
            break;
        case AddExpAST::subID:
            ast.addexp->accept(*this);
            value1=nowvalue;
            ast.mulexp->accept(*this);
            value2=nowvalue;
            bx=new BinaryExpr(BinaryExpr::subID,value1,value2);
            break;
    }
    SYMBOL *symbol=new SYMBOL("%"+to_string(inits++));
    nowvalue=symbol;
    SymbolDef *symboldef=new SymbolDef(symbol,SymbolDef::BiEpID,nullptr,nullptr,nullptr,nullptr,bx,nullptr);
    defnum_jubu++;
    nowstate=new Statement(Statement::SyDeID,symboldef,nullptr,nullptr);
    stmt_.push_back(nowstate);
    nowstate=nullptr;
}

void GenIR::visit(RelExpAST& ast)
{
    Value *value1;
    Value *value2;
    BinaryExpr *bx;
    switch(ast.tid)
    {
        case RelExpAST::addID:
            ast.addexp->accept(*this);
            return;
        case RelExpAST::ltID:
            ast.relexp->accept(*this);
            value1=nowvalue;
            ast.addexp->accept(*this);
            value2=nowvalue;
            bx=new BinaryExpr(BinaryExpr::ltID,value1,value2);
            break;
        case RelExpAST::gtID:
            ast.relexp->accept(*this);
            value1=nowvalue;
            ast.addexp->accept(*this);
            value2=nowvalue;
            bx=new BinaryExpr(BinaryExpr::gtID,value1,value2);
            break;
        case RelExpAST::leID:
            ast.relexp->accept(*this);
            value1=nowvalue;
            ast.addexp->accept(*this);
            value2=nowvalue;
            bx=new BinaryExpr(BinaryExpr::leID,value1,value2);
            break;
        case RelExpAST::geID:
            ast.relexp->accept(*this);
            value1=nowvalue;
            ast.addexp->accept(*this);
            value2=nowvalue;
            bx=new BinaryExpr(BinaryExpr::geID,value1,value2);
            break;
    }
    SYMBOL *symbol=new SYMBOL("%"+to_string(inits++));
    nowvalue=symbol;
    SymbolDef *symboldef=new SymbolDef(symbol,SymbolDef::BiEpID,nullptr,nullptr,nullptr,nullptr,bx,nullptr);
    defnum_jubu++;
    nowstate=new Statement(Statement::SyDeID,symboldef,nullptr,nullptr);
    stmt_.push_back(nowstate);
    nowstate=nullptr;
}

void GenIR::visit(EqExpAST& ast)
{
    Value *value1;
    Value *value2;
    BinaryExpr *bx;
    switch(ast.tid)
    {
        case EqExpAST::relID:
            ast.relexp->accept(*this);
            return;
        case EqExpAST::eqID:
            ast.eqexp->accept(*this);
            value1=nowvalue;
            ast.relexp->accept(*this);
            value2=nowvalue;
            bx=new BinaryExpr(BinaryExpr::eqID,value1,value2);
            break;
        case EqExpAST::neID:
            ast.eqexp->accept(*this);
            value1=nowvalue;
            ast.relexp->accept(*this);
            value2=nowvalue;
            bx=new BinaryExpr(BinaryExpr::neID,value1,value2);
    }
    SYMBOL *symbol=new SYMBOL("%"+to_string(inits++));
    nowvalue=symbol;
    SymbolDef *symboldef=new SymbolDef(symbol,SymbolDef::BiEpID,nullptr,nullptr,nullptr,nullptr,bx,nullptr);
    defnum_jubu++;
    nowstate=new Statement(Statement::SyDeID,symboldef,nullptr,nullptr);
    stmt_.push_back(nowstate);
    nowstate=nullptr;
}

void GenIR::visit(UnaryExpAST &ast)
{
    Value *value1;
    Value *value2;
    BinaryExpr *bx;
    switch(ast.tid)
    {
        case UnaryExpAST::priID:
        {
            ast.primaryexp->accept(*this);
            return;
        }
        case UnaryExpAST::poID:
        {
            ast.unaryexp->accept(*this);
            return;
        }
        case UnaryExpAST::neID:
        {
            ast.unaryexp->accept(*this);
            value1=new INT(0);
            value2=nowvalue;
            bx=new BinaryExpr(BinaryExpr::subID,value1,value2);
            break;
        }
        case UnaryExpAST::noID:
        {
            ast.unaryexp->accept(*this);
            value1=nowvalue;
            value2=new INT(0);
            bx=new BinaryExpr(BinaryExpr::eqID,value1,value2);
            break;
        }
        case UnaryExpAST::funcID:
        {
            is_call=1;
            auto funcall_=nowfuncall;
            SYMBOL *symbol=new SYMBOL(ast.ident);
            nowfuncall=new FunCall(symbol);
            funcrp_choose=0;
            ast.funcrparams->accept(*this);
            if(funcall_type[ast.ident])
            {
                SYMBOL *symbol=new SYMBOL("%"+to_string(inits++));
                nowvalue=symbol;
                SymbolDef *symboldef=new SymbolDef(symbol,SymbolDef::FuncID,nullptr,nullptr,nullptr,nullptr,nullptr,nowfuncall);
                defnum_jubu++;
                nowstate=new Statement(Statement::SyDeID,symboldef,nullptr,nullptr);
            }
            else
                nowstate=new Statement(Statement::FuncID,nullptr,nullptr,nowfuncall);
            stmt_.push_back(nowstate);
            nowstate=nullptr;
            nowfuncall=funcall_;
            return;
        }
        case UnaryExpAST::nfuncID:
        {
            is_call=1;
            SYMBOL *symbol=new SYMBOL(ast.ident);
            nowfuncall=new FunCall(symbol);
            if(funcall_type[ast.ident])
            {
                SYMBOL *symbol=new SYMBOL("%"+to_string(inits++));
                nowvalue=symbol;
                SymbolDef *symboldef=new SymbolDef(symbol,SymbolDef::FuncID,nullptr,nullptr,nullptr,nullptr,nullptr,nowfuncall);
                defnum_jubu++;
                nowstate=new Statement(Statement::SyDeID,symboldef,nullptr,nullptr);
            }
            else
                nowstate=new Statement(Statement::FuncID,nullptr,nullptr,nowfuncall);
            stmt_.push_back(nowstate);
            nowstate=nullptr;
            return;
        }
    }
    SYMBOL *symbol=new SYMBOL("%"+to_string(inits++));
    nowvalue=symbol;
    SymbolDef *symboldef=new SymbolDef(symbol,SymbolDef::BiEpID,nullptr,nullptr,nullptr,nullptr,bx,nullptr);
    defnum_jubu++;
    nowstate=new Statement(Statement::SyDeID,symboldef,nullptr,nullptr);
    stmt_.push_back(nowstate);
    nowstate=nullptr;
    
}

void GenIR::visit(PrimaryExpAST &ast)
{
    switch(ast.tid)
    {
        case PrimaryExpAST::expID:
            ast.exp->accept(*this);
            break;
        case PrimaryExpAST::lvalID:
            lval_wr=1;
            ast.lval->accept(*this);
            break;
        case PrimaryExpAST::numID:
            ast.number->accept(*this);
            break;
    }
}

void GenIR::visit(NumberAST& ast)
{
    nowvalue=new INT(ast.int_const);
}

void GenIR::visit(DeclAST& ast)
{
    switch(ast.tid)
    {
        case DeclAST::constID:
            ast.constdecl->accept(*this);
            break;
        case DeclAST::varID:
            ast.vardecl->accept(*this);
            break;
    }
}

void GenIR::visit(ConstDeclAST& ast)
{
    if(!ast.constdef_.empty())
    {
        for(auto &t:ast.constdef_)
            t->accept(*this);
    }
}

void GenIR::visit(ExpListAST& ast)
{
    if(is_explist)
    {
        if(lval_wr)
        {
            SYMBOL *symbol1=new SYMBOL("@"+nowid);
            SYMBOL *symbol2;
            for(auto &t:ast.exp_)
            {
                t->accept(*this);
                symbol2=new SYMBOL("%"+to_string(inits++));
                GetElementPointer *getelemptr=new GetElementPointer(symbol1,nowvalue);
                SymbolDef *symboldef1=new SymbolDef(symbol2,SymbolDef::GetPmID,nullptr,nullptr,nullptr,getelemptr,nullptr,nullptr);
                defnum_jubu++;
                nowstate=new Statement(Statement::SyDeID,symboldef1,nullptr,nullptr);
                stmt_.push_back(nowstate);
                nowstate=nullptr;
                symbol1=symbol2;
            }
            SYMBOL *symbol3=new SYMBOL("%"+to_string(inits++));
            Load *load=new Load(symbol2);
            nowvalue=symbol3;
            SymbolDef *symboldef2=new SymbolDef(symbol3,SymbolDef::LoadID,nullptr,load,nullptr,nullptr,nullptr,nullptr);
            defnum_jubu++;
            nowstate=new Statement(Statement::SyDeID,symboldef2,nullptr,nullptr);
            stmt_.push_back(nowstate);
            nowstate=nullptr;
            }
        else
        {
            Value *value1=nowvalue;
            SYMBOL *symbol1=new SYMBOL("@"+nowid);
            SYMBOL *symbol2;
            for(auto &t:ast.exp_)
            {
                t->accept(*this);
                symbol2=new SYMBOL("%"+to_string(inits++));
                GetElementPointer *getelemptr=new GetElementPointer(symbol1,nowvalue);
                SymbolDef *symboldef1=new SymbolDef(symbol2,SymbolDef::GetPmID,nullptr,nullptr,nullptr,getelemptr,nullptr,nullptr);
                defnum_jubu++;
                nowstate=new Statement(Statement::SyDeID,symboldef1,nullptr,nullptr);
                stmt_.push_back(nowstate);
                nowstate=nullptr;
                symbol1=symbol2;
            }
            Store *store=new Store(Store::valueID,value1,nullptr,symbol2);
            nowstate=new Statement(Statement::StoreID,nullptr,store,nullptr);
            stmt_.push_back(nowstate);
            nowstate=nullptr;
        }
        return;
    }
    Type *type=new Type(Type::i32ID);
    ArrayType *arraytype;
    bool flag=0;
    int ans=1;
    multiple_.clear();
    dimension_.clear();
    for(auto &t:ast.exp_)
    {
        get_value=t->getvalue();
        dimension_.push_back(get_value);
        ans*=get_value;
        multiple_.push_back(ans);
        if(!flag)
        {
            flag=1;
            arraytype=new ArrayType(type,get_value);
        }
        else
        {
            arraytype=new ArrayType(arraytype,get_value);
        }
    }
    nowtype=arraytype;
    std::reverse(multiple_.begin(), multiple_.end());
}

void GenIR::visit(ConstDefAST& ast)
{
    dimension=-1;
    switch(ast.tid)
    {
        case ConstDefAST::nconstID:
        {
            ast.constinitval->accept(*this);
            string name=get_name(ast.ident);
            Def *def=new Def(Def::constID,get_value,name);
            assert(scope->push(ast.ident,def));
            break;
        }
        case ConstDefAST::constID:
        {
            value_.clear();
            ast.constexplist->accept(*this);
            string name=get_name(ast.ident);
            nowid=name;
            ast.constinitval->accept(*this);
            Def *def=new Def(Def::arrayID,0,name);
            assert(scope->push(ast.ident,def));
            if(scope->in_global())
            {
                Aggregate *aggregate=new Aggregate();
                for(auto t:value_)
                {
                    Initializer *init=new Initializer(Initializer::intID,t,nullptr);
                    aggregate->initialzer_.push_back(init);
                }
                Initializer *initializer=new Initializer(Initializer::aggreID,0,aggregate);
                GlobalMemoryDeclaration *globalmemorydeclaration=new GlobalMemoryDeclaration(nowtype,initializer);
                SYMBOL *symbol=new SYMBOL("@"+nowid);
                GlobalSymbolDef *globalsymboldef=new GlobalSymbolDef(symbol,globalmemorydeclaration);
                initir->globalsymboldef_.push_back(globalsymboldef);
            }
            else
            {
                vector<int>dimen_;
                int cnt=dimension_.size();
                for(int i=0;i<cnt;i++)
                {
                    dimen_.push_back(0);
                }
                for(int i=0;i<value_.size();i++)
                {
                    Value *value1=new INT(value_[i]);
                    SYMBOL *symbol1=new SYMBOL("@"+scope->find(ast.ident)->name);
                    SYMBOL *symbol2;
                    for(auto t:dimen_)
                    {
                        symbol2=new SYMBOL("%"+to_string(inits++));
                        nowvalue=new INT(t);
                        GetElementPointer *getelemptr=new GetElementPointer(symbol1,nowvalue);
                        SymbolDef *symboldef1=new SymbolDef(symbol2,SymbolDef::GetPmID,nullptr,nullptr,nullptr,getelemptr,nullptr,nullptr);
                        defnum_jubu++;
                        nowstate=new Statement(Statement::SyDeID,symboldef1,nullptr,nullptr);
                        stmt_.push_back(nowstate);
                        nowstate=nullptr;
                        symbol1=symbol2;
                    }
                    Store *store=new Store(Store::valueID,value1,nullptr,symbol2);
                    nowstate=new Statement(Statement::StoreID,nullptr,store,nullptr);
                    stmt_.push_back(nowstate);
                    nowstate=nullptr;
                    dimen_[cnt-1]+=1;
                    int j=cnt-1;
                    while(dimen_[j]==dimension_[j])
                    {
                        dimen_[j]=0;
                        j--;
                        if(j>=0)
                            dimen_[j]+=1;
                        else
                            break;
                    }
                }
            }
            break;
        }
    }
}

void GenIR::visit(ConstInitValListAST& ast)
{
    auto dimension1=dimension;
    int cnt=value_.size();
    for(int i=dimension;i<multiple_.size();i++)
    {
        if(cnt%multiple_[i]==0)
            dimension=i;
    }
    for(auto &t:ast.constinitval_)
            t->accept(*this);
    dimension=dimension1;
}

void GenIR::visit(ConstInitValAST& ast)
{
    auto dimension1=dimension;
    switch(ast.tid)
    {
        case ConstInitValAST::cexpID:
        {
            ast.constexp->accept(*this);
            if(dimension==-1)
                return;
            value_.push_back(get_value);
            return;
        }
        case ConstInitValAST::nexpID:
        {
            dimension+=1;
            break;
        }
        case ConstInitValAST::cexp_ID:
        {
            dimension+=1;
            ast.constinitvallist->accept(*this);
            break;
        }
    }
    for(int i=value_.size();i<multiple_[dimension];i++)
        value_.push_back(0);
    dimension=dimension1;
}

void GenIR::visit(ConstExpAST& ast)
{
    get_value=ast.exp->getvalue();
}

void GenIR::visit(VarDeclAST& ast)
{
    if(!ast.vardef_.empty())
    {
        for(auto &t:ast.vardef_)
        {
            t->accept(*this);
        }
    }
}

void GenIR::visit(VarDefAST& ast)
{
    value_.clear();
    dimension=-1;
    string name=get_name(ast.ident);
    switch(ast.tid)
    {
        case VarDefAST::ncinitID:
        {
            nowid=name;
            ast.initval->accept(*this);
            Def *def1=new Def(Def::varID,get_value,name);
            assert(scope->push(ast.ident,def1));
            if(scope->in_global())
            {
                Initializer *initializer=new Initializer(Initializer::intID,get_value,nullptr);
                Type *type=new Type(Type::i32ID);
                GlobalMemoryDeclaration *globalmemorydeclaration=new GlobalMemoryDeclaration(type,initializer);
                SYMBOL *symbol=new SYMBOL("@"+name);
                GlobalSymbolDef *globalsymboldef=new GlobalSymbolDef(symbol,globalmemorydeclaration);
                initir->globalsymboldef_.push_back(globalsymboldef);
            }
            break;
        }
        case VarDefAST::nconstID:
        {
            if(scope->in_global())
            {
                Initializer *initializer=new Initializer(Initializer::zeroID,0,nullptr);
                Type *type=new Type(Type::i32ID);
                GlobalMemoryDeclaration *globalmemorydeclaration=new GlobalMemoryDeclaration(type,initializer);
                SYMBOL *symbol=new SYMBOL("@"+name);
                GlobalSymbolDef *globalsymboldef=new GlobalSymbolDef(symbol,globalmemorydeclaration);
                initir->globalsymboldef_.push_back(globalsymboldef);
                Def *def=new Def(Def::varID,0,name);
                assert(scope->push(ast.ident,def));
                return;
            }
            Type *type=new Type(Type::i32ID);
            MemoryDeclaration *memorydeclaration=new MemoryDeclaration(type);
            SYMBOL *symbol=new SYMBOL("@"+name);
            SymbolDef *symboldef=new SymbolDef(symbol,SymbolDef::MemID,memorydeclaration,nullptr,nullptr,nullptr,nullptr,nullptr);
            defnum_jubu++;
            nowstate=new Statement(Statement::SyDeID,symboldef,nullptr,nullptr);
            stmt_.push_back(nowstate);
            nowstate=nullptr;
            Def *def2=new Def(Def::nvarID,0,name);
            assert(scope->push(ast.ident,def2));
            break;
        }
        case VarDefAST::constID:
        {
            Def *def=new Def(Def::arrayID,0,name);
            assert(scope->push(ast.ident,def));
            ast.constexplist->accept(*this);
            SYMBOL *symbol=new SYMBOL("@"+name);
            if(scope->in_global())
            {
                Initializer *initializer=new Initializer(Initializer::zeroID,0,nullptr);
                GlobalMemoryDeclaration *globalmemorydeclaration=new GlobalMemoryDeclaration(nowtype,initializer);
                GlobalSymbolDef *globalsymboldef=new GlobalSymbolDef(symbol,globalmemorydeclaration);
                initir->globalsymboldef_.push_back(globalsymboldef);
                return;
            }
            MemoryDeclaration *memorydeclaration=new MemoryDeclaration(nowtype);
            SymbolDef *symboldef=new SymbolDef(symbol,SymbolDef::MemID,memorydeclaration,nullptr,nullptr,nullptr,nullptr,nullptr);
            defnum_jubu++;
            nowstate=new Statement(Statement::SyDeID,symboldef,nullptr,nullptr);
            stmt_.push_back(nowstate);
            nowstate=nullptr;
            break;
        }
        case VarDefAST::cinitID:
        {
            Def *def=new Def(Def::arrayID,0,name);
            assert(scope->push(ast.ident,def));
            ast.constexplist->accept(*this);
            SYMBOL *symbol=new SYMBOL("@"+name);
            nowid=name;
            if(scope->in_global())
            {
                ast.initval->accept(*this);
                Aggregate *aggregate=new Aggregate();
                for(auto t:value_)
                {
                    Initializer *init=new Initializer(Initializer::intID,t,nullptr);
                    aggregate->initialzer_.push_back(init);
                }
                Initializer *initializer=new Initializer(Initializer::aggreID,0,aggregate);
                GlobalMemoryDeclaration *globalmemorydeclaration=new GlobalMemoryDeclaration(nowtype,initializer);
                SYMBOL *symbol=new SYMBOL("@"+nowid);
                GlobalSymbolDef *globalsymboldef=new GlobalSymbolDef(symbol,globalmemorydeclaration);
                initir->globalsymboldef_.push_back(globalsymboldef);
                return;
            }
            MemoryDeclaration *memorydeclaration=new MemoryDeclaration(nowtype);
            SymbolDef *symboldef=new SymbolDef(symbol,SymbolDef::MemID,memorydeclaration,nullptr,nullptr,nullptr,nullptr,nullptr);
            defnum_jubu++;
            nowstate=new Statement(Statement::SyDeID,symboldef,nullptr,nullptr);
            stmt_.push_back(nowstate);
            nowstate=nullptr;
            ast.initval->accept(*this);
            break;
        }
    }
}

void GenIR::visit(InitValListAST& ast)//xymc
{
    auto dimension1=dimension;
    int cnt=value_.size();
    for(int i=dimension;i<multiple_.size();i++)
    {
        if(cnt%multiple_[i]==0)
            dimension=i;
    }
    for(auto &t:ast.initval_)
            t->accept(*this);
    dimension=dimension1;
}

void GenIR::visit(InitValAST& ast)
{
    int cnt=dimension_.size();
    vector<int>dimen_;
    for(int i=0;i<cnt;i++)
    {
        dimen_.push_back(0);
    }
    auto dimension1=dimension;
    switch(ast.tid)
    {
        case InitValAST::expID:
        {
            if(dimension==-1)
            {
                if(scope->in_global())
                {
                    get_value=ast.exp->getvalue();
                    return;
                }
                ast.exp->accept(*this);
                get_value=ast.exp->getvalue();
                SYMBOL *symbol=new SYMBOL("@"+nowid);
                Type *type=new Type(Type::i32ID);
                MemoryDeclaration *memorydeclaration=new MemoryDeclaration(type);
                SymbolDef *symboldef=new SymbolDef(symbol,SymbolDef::MemID,memorydeclaration,nullptr,nullptr,nullptr,nullptr,nullptr);
                defnum_jubu++;
                nowstate=new Statement(Statement::SyDeID,symboldef,nullptr,nullptr);
                stmt_.push_back(nowstate);
                nowstate=nullptr;
                Store *store=new Store(Store::valueID,nowvalue,nullptr,symbol);
                nowstate=new Statement(Statement::StoreID,nullptr,store,nullptr);
                stmt_.push_back(nowstate);
                nowstate=nullptr;
                return;
            }
            if(scope->in_global())
            {
                get_value=ast.exp->getvalue();
                value_.push_back(get_value);
                return;
            }
            else
            {
                value_.push_back(0);
                ast.exp->accept(*this);
                Value *value1=nowvalue;
                SYMBOL *symbol1=new SYMBOL("@"+nowid);
                SYMBOL *symbol2;
                for(auto t:dimen_)
                {
                    symbol2=new SYMBOL("%"+to_string(inits++));
                    nowvalue=new INT(t);
                    GetElementPointer *getelemptr=new GetElementPointer(symbol1,nowvalue);
                    SymbolDef *symboldef1=new SymbolDef(symbol2,SymbolDef::GetPmID,nullptr,nullptr,nullptr,getelemptr,nullptr,nullptr);
                    defnum_jubu++;
                    nowstate=new Statement(Statement::SyDeID,symboldef1,nullptr,nullptr);
                    stmt_.push_back(nowstate);
                    nowstate=nullptr;
                    symbol1=symbol2;
                }
                Store *store=new Store(Store::valueID,value1,nullptr,symbol2);
                nowstate=new Statement(Statement::StoreID,nullptr,store,nullptr);
                stmt_.push_back(nowstate);
                nowstate=nullptr;
                dimen_[cnt-1]+=1;
                int j=cnt-1;
                while(dimen_[j]==dimension_[j])
                {
                    dimen_[j]=0;
                    j--;
                    if(j>=0)
                        dimen_[j]+=1;
                    else
                        break;
                }
            }
        }
        case InitValAST::nexpID:
        {
            dimension+=1;
            break;
        }
        case InitValAST::init_ID:
        {
            dimension+=1;
            ast.initvallist->accept(*this);
            break;
        }
    }
    if(scope->in_global())
    {
        for(int i=value_.size();i<multiple_[dimension];i++)
            value_.push_back(0);
    }
    else
    {
        for(int i=value_.size();i<multiple_[dimension];i++)
        {
            Value *value1=new INT(0);
            SYMBOL *symbol1=new SYMBOL("@"+nowid);
            SYMBOL *symbol2;
            for(auto t:dimen_)
            {
                symbol2=new SYMBOL("%"+to_string(inits++));
                nowvalue=new INT(t);
                GetElementPointer *getelemptr=new GetElementPointer(symbol1,nowvalue);
                SymbolDef *symboldef1=new SymbolDef(symbol2,SymbolDef::GetPmID,nullptr,nullptr,nullptr,getelemptr,nullptr,nullptr);
                defnum_jubu++;
                nowstate=new Statement(Statement::SyDeID,symboldef1,nullptr,nullptr);
                stmt_.push_back(nowstate);
                nowstate=nullptr;
                symbol1=symbol2;
            }
            Store *store=new Store(Store::valueID,value1,nullptr,symbol2);
            nowstate=new Statement(Statement::StoreID,nullptr,store,nullptr);
            stmt_.push_back(nowstate);
            nowstate=nullptr;
            dimen_[cnt-1]+=1;
            int j=cnt-1;
            while(dimen_[j]==dimension_[j])
            {
                dimen_[j]=0;
                j--;
                if(j>=0)
                    dimen_[j]+=1;
                else
                    break;
            }
        }
    }
    dimension=dimension1;
}

void GenIR::visit(LValAST& ast)
{
    switch(ast.tid)
    {
        case LValAST::nexpID:
        {
            if(lval_wr)
            {
                assert(scope->find(ast.ident)->tid!=Def::nvarID);
                switch(scope->find(ast.ident)->tid)
                {
                    case Def::constID:
                    {
                        nowvalue=new INT(scope->find(ast.ident)->value);
                        break;
                    }
                    case Def::varID:
                    {
                        SYMBOL *symbol1=new SYMBOL("@"+scope->find(ast.ident)->name);
                        Load *load=new Load(symbol1);
                        SYMBOL *symbol2=new SYMBOL("%"+to_string(inits++));
                        nowvalue=symbol2;
                        SymbolDef *symboldef=new SymbolDef(symbol2,SymbolDef::LoadID,nullptr,load,nullptr,nullptr,nullptr,nullptr);
                        defnum_jubu++;
                        nowstate=new Statement(Statement::SyDeID,symboldef,nullptr,nullptr);
                        stmt_.push_back(nowstate);
                        nowstate=nullptr;
                        break;
                    }
                    case Def::funID:
                    {
                        SYMBOL *symbol1=new SYMBOL("%"+scope->find(ast.ident)->name);
                        Load *load=new Load(symbol1);
                        SYMBOL *symbol2=new SYMBOL("%"+to_string(inits++));
                        nowvalue=symbol2;
                        SymbolDef *symboldef=new SymbolDef(symbol2,SymbolDef::LoadID,nullptr,load,nullptr,nullptr,nullptr,nullptr);
                        defnum_jubu++;
                        nowstate=new Statement(Statement::SyDeID,symboldef,nullptr,nullptr);
                        stmt_.push_back(nowstate);
                        nowstate=nullptr;
                        break;
                    }
                }
            }
            else
            {
                scope->find(ast.ident)->tid=Def::varID;
                scope->find(ast.ident)->value=get_value;
                SYMBOL *symbol=new SYMBOL("@"+scope->find(ast.ident)->name);
                Store *store=new Store(Store::valueID,nowvalue,nullptr,symbol);
                nowstate=new Statement(Statement::StoreID,nullptr,store,nullptr);
                stmt_.push_back(nowstate);
                nowstate=nullptr;
            }
            break;
        }
        case LValAST::expID:
        {
            assert(scope->find(ast.ident)->tid==Def::arrayID);
            is_explist=1;
            ast.explist->accept(*this);
            is_explist=0;
            break;
        }
    }
}

void GenIR::visit(FuncRParamsAST &ast)
{
    int sum=0;
    if(!ast.exp_.empty())
    {
        for(auto &t:ast.exp_)
        {
            t->accept(*this);
            nowfuncall->value_.push_back(nowvalue);
            sum++;
        }
    }
    max_sum=max(sum,max_sum);
}



