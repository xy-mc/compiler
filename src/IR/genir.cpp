#include<genir.hpp>
using namespace std;

vector<GlobalSymbolDef*>globalsym_;
vector<FunDef*>fun_;
vector<Block *>block_;
vector<Statement *>stmt_;
std::unique_ptr<EndStatement> endstmt;
std::unique_ptr<FunDef> nowfun;
std::unique_ptr<Block> nowblock;
std::unique_ptr<Statement> nowstate;
std::unique_ptr<Value> nowvalue;
char inits='0';
int nownumber;
void GenIR::visit(CompUnitAST& ast)
{
    ast.funcdef->accept(*this);
    initir->globalsymboldef_=globalsym_;
    initir->fundef_=fun_;
}

void GenIR::visit(FuncDefAST& ast)
{
    nowfun->symbol=new SYMBOL(ast.indent);
    nowfun->type=new Type(I32TyID);
    ast.block->accept(*this);
    nowfun->funbody=new FunBody(block_);
    blcok_.clear();
    fun_.push_back(nowfun);
    nowfun=nullptr;
}

void GenIR::visit(BlockAST& ast)
{
    ast.stmt->accept(*this);
    block_symbol=new SYMBOL(inits++);
    nowblock=new Block(block_symbol,stmt_,endstmt);
    stmt_.clear();
    block_.push_back(nowblock);
    nowblock=nullptr;
}

void GenIR::visit(StmtAST& ast)
{
    ast.number->accept(*this);
    endstate=new EndStatement(ReturnID);
    nowvalue=new Value(INtID);
    nowvalue->i32=new INT(nownumber);
    endstate->ret=new Return(nowvalue);
}

void GenIR::visit(NumberAST& ast)
{
    nownumber=ast.int_const;
}