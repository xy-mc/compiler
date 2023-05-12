#pragma once
#include "ir.hpp"
#include "AST/ast.hpp"
#include <map>

class GenIR: public Visitor 
{
    public:
    virtual void visit(CompUnitAST& ast) = 0;
    // virtual void visit(DeclDefAST& ast) = 0;
    // virtual void visit(DeclAST& ast) = 0;
    // virtual void visit(DefAST& ast) = 0;
    // virtual void visit(InitValAST& ast) = 0;
    virtual void visit(FuncDefAST& ast) = 0;
    virtual void visit(FuncTypeAST& ast) = 0;
    // virtual void visit(FuncFParamAST& ast) = 0;
    virtual void visit(BlockAST& ast) = 0;
    // virtual void visit(BlockItemAST& ast) = 0;
    virtual void visit(StmtAST& ast) = 0;
    // virtual void visit(ReturnStmtAST& ast) = 0;
    // virtual void visit(SelectStmtAST& ast) = 0;
    // virtual void visit(IterationStmtAST& ast) = 0;
    // virtual void visit(AddExpAST& ast) = 0;
    // virtual void visit(MulExpAST& ast) = 0;
    // virtual void visit(UnaryExpAST& ast) = 0;
    // virtual void visit(PrimaryExpAST& ast) = 0;
    // virtual void visit(LValAST& ast) = 0;
    virtual void visit(NumberAST& ast) = 0;
    // virtual void visit(CallAST& ast) = 0;
    // virtual void visit(RelExpAST& ast) = 0;
    // virtual void visit(EqExpAST& ast) = 0;
    // virtual void visit(LAndExpAST& ast) = 0;
    // virtual void visit(LOrExpAST& ast) = 0;
    std::unique_ptr<InitIR> initir=nullptr;
}