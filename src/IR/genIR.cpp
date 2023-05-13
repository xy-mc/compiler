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
int nownumber;
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
    SYMBOL *block_symbol=new SYMBOL("%"+to_string(inits++));
    nowblock=new Block(block_symbol,stmt_,endstmt);
    stmt_.clear();
    block_.push_back(nowblock);
    nowblock=nullptr;
}

void GenIR::visit(StmtAST& ast)
{
    ast.number->accept(*this);
    endstmt=new EndStatement(EndStatement::ReturnID);
    nowvalue=new Value(Value::INTID);
    nowvalue->i32=new INT(nownumber);
    endstmt->ret=new Return(nowvalue);
}

void GenIR::visit(NumberAST& ast)
{
    nownumber=ast.int_const;
}


