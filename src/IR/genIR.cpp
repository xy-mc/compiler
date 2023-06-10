#include "genIR.hpp"
#include <map>
#include <string>
#include <cassert>
using namespace std;

vector<Block *>block_;
vector<Statement *>stmt_;
vector<Funparam *>funparam_;
EndStatement *endstmt;
FunDef *nowfun;
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
    }
}

void GenIR::visit(FuncDefAST& ast)
{
    scope->enter();
    SYMBOL *symbol=new SYMBOL(ast.ident);
    ast.btype->accept(*this);
    if(ast.funcfparams!=nullptr)
        ast.funcfparams->accept(*this);
    nowfunparams=new Funparams(funparam_);
    funparam_.clear();
    ast.block->accept(*this);
    scope->exit();
    if(!stmt_.empty())
    {
        Return *ret=new Return(nullptr);
        endstmt=new EndStatement(EndStatement::returnID,nullptr,nullptr,ret);
        get_block();
    }
    FunBody *funbody=new FunBody(block_);
    block_.clear();
    nowfun=new FunDef(symbol,nowfunparams,nowfuntype,funbody);
    if(nowfuntype==nullptr)
        funcall_type[ast.ident]=0;
    else
        funcall_type[ast.ident]=1;
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
    SymbolDef *symboldef=new SymbolDef(symbol2,SymbolDef::MemID,memorydeclaration,nullptr,nullptr,nullptr);
    nowstate=new Statement(Statement::SyDeID,symboldef,nullptr,nullptr);
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
    else
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
        SymbolDef *symboldef=new SymbolDef(symbol2,SymbolDef::LoadID,nullptr,load,nullptr,nullptr);
        nowstate=new Statement(Statement::SyDeID,symboldef,nullptr,nullptr);
        stmt_.push_back(nowstate);
    }
    is_luoji=is_luoji_;
    true_block=block1;
    false_block=block2;
}

void GenIR::visit(LAndExpAST& ast)
{
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
            ast.landexp->accept(*this);
            SYMBOL *y_block=new SYMBOL("block_"+to_string(initb++));
            Branch *branch1=new Branch(nowvalue,y_block,false_block);
            endstmt=new EndStatement(EndStatement::branchID,branch1,nullptr,nullptr);
            get_block();
            block_symbol=y_block;
            ast.eqexp->accept(*this);
            break;
        }
    }
}

void GenIR::visit(LOrExpAST& ast)
{
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
            ast.lorexp->accept(*this);
            SYMBOL *y_block=new SYMBOL("block_"+to_string(initb++));
            Branch *branch=new Branch(nowvalue,true_block,y_block);
            endstmt=new EndStatement(EndStatement::branchID,branch,nullptr,nullptr);
            get_block();
            block_symbol=y_block;
            ast.landexp->accept(*this);
        }
    }
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
    }
    SYMBOL *symbol=new SYMBOL("%"+to_string(inits++));
    nowvalue=symbol;
    SymbolDef *symboldef=new SymbolDef(symbol,SymbolDef::BiEpID,nullptr,nullptr,bx,nullptr);
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
    }
    SYMBOL *symbol=new SYMBOL("%"+to_string(inits++));
    nowvalue=symbol;
    SymbolDef *symboldef=new SymbolDef(symbol,SymbolDef::BiEpID,nullptr,nullptr,bx,nullptr);
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
    }
    SYMBOL *symbol=new SYMBOL("%"+to_string(inits++));
    nowvalue=symbol;
    SymbolDef *symboldef=new SymbolDef(symbol,SymbolDef::BiEpID,nullptr,nullptr,bx,nullptr);
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
    SymbolDef *symboldef=new SymbolDef(symbol,SymbolDef::BiEpID,nullptr,nullptr,bx,nullptr);
    nowstate=new Statement(Statement::SyDeID,symboldef,nullptr,nullptr);
    stmt_.push_back(nowstate);
    nowstate=nullptr;
}

// void GenIR::visit(LAndExpAST& ast)
// {
//     Value *value1;
//     Value *value2;
//     BinaryExpr *bx;
//     switch(ast.tid)
//     {
//         case LAndExpAST::eqID:
//             ast.eqexp->accept(*this);
//             return;
//         case LAndExpAST::landID:
//             ast.landexp->accept(*this);
//             value1=nowvalue;
//             ast.eqexp->accept(*this);
//             value2=nowvalue;
//             Value *value3=new INT(0);
//             BinaryExpr *bx1=new BinaryExpr(BinaryExpr::neID,value1,value3);
//             SYMBOL *symbol1=new SYMBOL("%"+to_string(inits++));
//             SymbolDef *symboldef1=new SymbolDef(symbol1,SymbolDef::BiEpID,nullptr,nullptr,bx1,nullptr);
//             Statement *newstmt1=new Statement(Statement::SyDeID,symboldef1,nullptr,nullptr);
//             stmt_.push_back(newstmt1);
//             BinaryExpr *bx2=new BinaryExpr(BinaryExpr::neID,value2,value3);
//             SYMBOL *symbol2=new SYMBOL("%"+to_string(inits++));
//             SymbolDef *symboldef2=new SymbolDef(symbol2,SymbolDef::BiEpID,nullptr,nullptr,bx2,nullptr);
//             Statement *newstmt2=new Statement(Statement::SyDeID,symboldef2,nullptr,nullptr);
//             stmt_.push_back(newstmt2);
//             Value *value1_=symbol1;
//             Value *value2_=symbol2;
//             SYMBOL *symbol3=new SYMBOL("%"+to_string(inits++));
//             nowvalue=symbol3;
//             BinaryExpr *bx3=new BinaryExpr(BinaryExpr::andID,value1_,value2_);
//             SymbolDef *symboldef3=new SymbolDef(symbol3,SymbolDef::BiEpID,nullptr,nullptr,bx3,nullptr);
//             Statement *newstmt3=new Statement(Statement::SyDeID,symboldef3,nullptr,nullptr);
//             stmt_.push_back(newstmt3);
//     }
// }

// void GenIR::visit(LOrExpAST& ast)
// {
//     Value *value1;
//     Value *value2;
//     BinaryExpr *bx;
//     switch(ast.tid)
//     {
//         case LOrExpAST::landID:
//             ast.landexp->accept(*this);
//             return;
//         case LOrExpAST::lorID:
//             ast.lorexp->accept(*this);
//             value1=nowvalue;
//             ast.landexp->accept(*this);
//             value2=nowvalue;
//             Value *value3=new INT(0);
//             BinaryExpr *bx1=new BinaryExpr(BinaryExpr::neID,value1,value3);
//             SYMBOL *symbol1=new SYMBOL("%"+to_string(inits++));
//             SymbolDef *symboldef1=new SymbolDef(symbol1,SymbolDef::BiEpID,nullptr,nullptr,bx1,nullptr);
//             Statement *newstmt1=new Statement(Statement::SyDeID,symboldef1,nullptr,nullptr);
//             stmt_.push_back(newstmt1);
//             BinaryExpr *bx2=new BinaryExpr(BinaryExpr::neID,value2,value3);
//             SYMBOL *symbol2=new SYMBOL("%"+to_string(inits++));
//             SymbolDef *symboldef2=new SymbolDef(symbol2,SymbolDef::BiEpID,nullptr,nullptr,bx2,nullptr);
//             Statement *newstmt2=new Statement(Statement::SyDeID,symboldef2,nullptr,nullptr);
//             stmt_.push_back(newstmt2);
//             Value *value1_=symbol1;
//             Value *value2_=symbol2;
//             SYMBOL *symbol3=new SYMBOL("%"+to_string(inits++));
//             nowvalue=symbol3;
//             BinaryExpr *bx3=new BinaryExpr(BinaryExpr::orID,value1_,value2_);
//             SymbolDef *symboldef3=new SymbolDef(symbol3,SymbolDef::BiEpID,nullptr,nullptr,bx3,nullptr);
//             Statement *newstmt3=new Statement(Statement::SyDeID,symboldef3,nullptr,nullptr);
//             stmt_.push_back(newstmt3);
//     }
// }

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
            return;
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
            auto funcall_=nowfuncall;
            SYMBOL *symbol=new SYMBOL(ast.ident);
            nowfuncall=new FunCall(symbol);
            ast.funcrparams->accept(*this);
            if(funcall_type[ast.ident])
            {
                SYMBOL *symbol=new SYMBOL("%"+to_string(inits++));
                nowvalue=symbol;
                SymbolDef *symboldef=new SymbolDef(symbol,SymbolDef::FuncID,nullptr,nullptr,nullptr,nowfuncall);
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
            SYMBOL *symbol=new SYMBOL(ast.ident);
            nowfuncall=new FunCall(symbol);
            if(funcall_type[ast.ident])
            {
                SYMBOL *symbol=new SYMBOL("%"+to_string(inits++));
                nowvalue=symbol;
                SymbolDef *symboldef=new SymbolDef(symbol,SymbolDef::FuncID,nullptr,nullptr,nullptr,nowfuncall);
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
    SymbolDef *symboldef=new SymbolDef(symbol,SymbolDef::BiEpID,nullptr,nullptr,bx,nullptr);
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

void GenIR::visit(ConstDefAST& ast)
{
    ast.constinitval->accept(*this);
    string name=get_name(ast.ident);
    Def *def=new Def(Def::constID,get_value,name);
    assert(scope->push(ast.ident,def));
}

void GenIR::visit(ConstInitValAST& ast)
{
    ast.constexp->accept(*this);
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
            t->accept(*this);
    }
}

void GenIR::visit(VarDefAST& ast)
{
    string name=get_name(ast.ident);
    if(ast.initval!=nullptr)
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
    }
    else
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
        SymbolDef *symboldef=new SymbolDef(symbol,SymbolDef::MemID,memorydeclaration,nullptr,nullptr,nullptr);
        nowstate=new Statement(Statement::SyDeID,symboldef,nullptr,nullptr);
        stmt_.push_back(nowstate);
        nowstate=nullptr;
        Def *def2=new Def(Def::nvarID,0,name);
        assert(scope->push(ast.ident,def2));
    }
}

void GenIR::visit(InitValAST& ast)
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
    SymbolDef *symboldef=new SymbolDef(symbol,SymbolDef::MemID,memorydeclaration,nullptr,nullptr,nullptr);
    nowstate=new Statement(Statement::SyDeID,symboldef,nullptr,nullptr);
    stmt_.push_back(nowstate);
    nowstate=nullptr;
    Store *store=new Store(Store::valueID,nowvalue,nullptr,symbol);
    nowstate=new Statement(Statement::StoreID,nullptr,store,nullptr);
    stmt_.push_back(nowstate);
    nowstate=nullptr;
}

void GenIR::visit(LValAST& ast)
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
                SymbolDef *symboldef=new SymbolDef(symbol2,SymbolDef::LoadID,nullptr,load,nullptr,nullptr);
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
                SymbolDef *symboldef=new SymbolDef(symbol2,SymbolDef::LoadID,nullptr,load,nullptr,nullptr);
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
}

void GenIR::visit(FuncRParamsAST &ast)
{
    if(!ast.exp_.empty())
    {
        for(auto &t:ast.exp_)
        {
            t->accept(*this);
            nowfuncall->value_.push_back(nowvalue);
        }
    }
}





