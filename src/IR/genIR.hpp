#pragma once
#include "ir.hpp"
#include "AST/ast.hpp"


class GenIR: public Visitor 
{
    public:    
        void visit(CompUnitAST &ast) override;
        void visit(FuncDefAST &ast) override;
        void visit(FuncTypeAST& ast) override;
        void visit(BlockAST &ast) override;
        void visit(StmtAST &ast) override;
        void visit(ExpAST& ast) override;
        void visit(PrimaryExpAST& ast) override;
        void visit(NumberAST &ast) override;
        void visit(UnaryExpAST& ast) override;
        void visit(UnaryOpAST& ast) override;
        InitIR *initir=new InitIR();
};