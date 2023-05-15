#include "genIR.hpp"
using namespace std;

// vector<GlobalSymbolDef*>globalsym_;
// vector<FunDef*>fun_;
vector<Block *>block_;
vector<Statement *>stmt_;
EndStatement *endstmt;
FunDef *nowfun;
Block *nowblock; 
Statement *nowstate;
Value *nowvalue;
int inits=0;
void GenIR::visit(CompUnitAST& ast)
{
    ast.funcdef->accept(*this);
}

void GenIR::visit(FuncDefAST& ast)
{
    nowfun=new FunDef();
    nowfun->symbol=new SYMBOL(ast.ident);
    nowfun->type=new Type(Type::I32TyID);
    ast.block->accept(*this);
    nowfun->funbody=new FunBody(block_);
    block_.clear();
    initir->fundef_.push_back(nowfun);
    nowfun=nullptr;
}

void GenIR::visit(FuncTypeAST& ast)
{
    return;
}

void GenIR::visit(BlockAST& ast)
{
    ast.stmt->accept(*this);
    SYMBOL *block_symbol=new SYMBOL("%entry");
    nowblock=new Block(block_symbol,stmt_,endstmt);
    stmt_.clear();
    block_.push_back(nowblock);
    nowblock=nullptr;
}

void GenIR::visit(StmtAST& ast)
{
    ast.exp->accept(*this);
    Return *ret=new Return(nowvalue);
    endstmt=new EndStatement(EndStatement::ReturnID,ret);
}

void GenIR::visit(ExpAST& ast)
{
    ast.lorexp->accept(*this);
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
    SymbolDef *symboldef=new SymbolDef(symbol,SymbolDef::BiEpID,bx);
    nowstate=new Statement(Statement::SyDeID,symboldef);
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
    SymbolDef *symboldef=new SymbolDef(symbol,SymbolDef::BiEpID,bx);
    nowstate=new Statement(Statement::SyDeID,symboldef);
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
    SymbolDef *symboldef=new SymbolDef(symbol,SymbolDef::BiEpID,bx);
    nowstate=new Statement(Statement::SyDeID,symboldef);
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
    SymbolDef *symboldef=new SymbolDef(symbol,SymbolDef::BiEpID,bx);
    nowstate=new Statement(Statement::SyDeID,symboldef);
    stmt_.push_back(nowstate);
    nowstate=nullptr;
}

void GenIR::visit(LAndExpAST& ast)
{
    Value *value1;
    Value *value2;
    BinaryExpr *bx;
    switch(ast.tid)
    {
        case LAndExpAST::eqID:
            ast.eqexp->accept(*this);
            return;
        case LAndExpAST::landID:
            ast.landexp->accept(*this);
            value1=nowvalue;
            ast.eqexp->accept(*this);
            value2=nowvalue;
            Value *value3=new INT(0);
            BinaryExpr *bx1=new BinaryExpr(BinaryExpr::neID,value1,value3);
            SYMBOL *symbol1=new SYMBOL("%"+to_string(inits++));
            SymbolDef *symboldef1=new SymbolDef(symbol1,SymbolDef::BiEpID,bx1);
            Statement *newstmt1=new Statement(Statement::SyDeID,symboldef1);
            stmt_.push_back(newstmt1);
            BinaryExpr *bx2=new BinaryExpr(BinaryExpr::neID,value2,value3);
            SYMBOL *symbol2=new SYMBOL("%"+to_string(inits++));
            SymbolDef *symboldef2=new SymbolDef(symbol2,SymbolDef::BiEpID,bx2);
            Statement *newstmt2=new Statement(Statement::SyDeID,symboldef2);
            stmt_.push_back(newstmt2);
            Value *value1_=symbol1;
            Value *value2_=symbol2;
            SYMBOL *symbol3=new SYMBOL("%"+to_string(inits++));
            nowvalue=symbol3;
            BinaryExpr *bx3=new BinaryExpr(BinaryExpr::andID,value1_,value2_);
            SymbolDef *symboldef3=new SymbolDef(symbol3,SymbolDef::BiEpID,bx3);
            Statement *newstmt3=new Statement(Statement::SyDeID,symboldef3);
            stmt_.push_back(newstmt3);
    }
}

void GenIR::visit(LOrExpAST& ast)
{
    Value *value1;
    Value *value2;
    BinaryExpr *bx;
    switch(ast.tid)
    {
        case LOrExpAST::landID:
            ast.landexp->accept(*this);
            return;
        case LOrExpAST::lorID:
            ast.lorexp->accept(*this);
            value1=nowvalue;
            ast.landexp->accept(*this);
            value2=nowvalue;
            Value *value3=new INT(0);
            BinaryExpr *bx1=new BinaryExpr(BinaryExpr::neID,value1,value3);
            SYMBOL *symbol1=new SYMBOL("%"+to_string(inits++));
            SymbolDef *symboldef1=new SymbolDef(symbol1,SymbolDef::BiEpID,bx1);
            Statement *newstmt1=new Statement(Statement::SyDeID,symboldef1);
            stmt_.push_back(newstmt1);
            BinaryExpr *bx2=new BinaryExpr(BinaryExpr::neID,value2,value3);
            SYMBOL *symbol2=new SYMBOL("%"+to_string(inits++));
            SymbolDef *symboldef2=new SymbolDef(symbol2,SymbolDef::BiEpID,bx2);
            Statement *newstmt2=new Statement(Statement::SyDeID,symboldef2);
            stmt_.push_back(newstmt2);
            Value *value1_=symbol1;
            Value *value2_=symbol2;
            SYMBOL *symbol3=new SYMBOL("%"+to_string(inits++));
            nowvalue=symbol3;
            BinaryExpr *bx3=new BinaryExpr(BinaryExpr::orID,value1_,value2_);
            SymbolDef *symboldef3=new SymbolDef(symbol3,SymbolDef::BiEpID,bx3);
            Statement *newstmt3=new Statement(Statement::SyDeID,symboldef3);
            stmt_.push_back(newstmt3);
    }
}

void GenIR::visit(UnaryExpAST &ast)
{
    if(ast.primaryexp!=nullptr)
    {
        ast.primaryexp->accept(*this);
    }
    else
    {
        ast.unaryexp->accept(*this);
        if(ast.unaryop!=nullptr)
        {
            ast.unaryop->accept(*this);
        }
    }
}

void GenIR::visit(UnaryOpAST &ast)
{
    Value *value1;
    Value *value2;
    BinaryExpr *bx;
    switch (ast.tid)
    {   
        case UnaryOpAST::PID:
            return;
        case UnaryOpAST::NeID:
            value1=new INT(0);
            value2=nowvalue;
            bx=new BinaryExpr(BinaryExpr::subID,value1,value2);
            break;
        case UnaryOpAST::NoID:
            value1=nowvalue;
            value2=new INT(0);
            bx=new BinaryExpr(BinaryExpr::eqID,value1,value2);
    }
    SYMBOL *symbol=new SYMBOL("%"+to_string(inits++));
    nowvalue=symbol;
    SymbolDef *symboldef=new SymbolDef(symbol,SymbolDef::BiEpID,bx);
    nowstate=new Statement(Statement::SyDeID,symboldef);
    stmt_.push_back(nowstate);
    nowstate=nullptr;
}

void GenIR::visit(PrimaryExpAST &ast)
{
    if(ast.exp!=nullptr)
    {
        ast.exp->accept(*this);                                               
    }
    else
    {
        ast.number->accept(*this);
    }
}

void GenIR::visit(NumberAST& ast)
{
    nowvalue=new INT(ast.int_const);
}


