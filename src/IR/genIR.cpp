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
}

void GenIR::visit(ExpAST& ast)
{
    ast.unaryexp->accept(*this);
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
        ast.unaryop->accept(*this);
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
    SYMBOL *symbol=new SYMBOL(to_string(inits++));
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
        Return *ret=new Return(nowvalue);
        endstmt=new EndStatement(EndStatement::ReturnID,ret);
    }
}

void GenIR::visit(NumberAST& ast)
{
    nowvalue=new INT(ast.int_const);
}


