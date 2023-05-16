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
        void visit(MulExpAST& ast) override;
        void visit(AddExpAST& ast) override;
        void visit(RelExpAST& ast) override;
        void visit(EqExpAST& ast) override;
        void visit(LAndExpAST& ast) override;
        void visit(LOrExpAST& ast) override;
        void visit(PrimaryExpAST& ast) override;
        void visit(NumberAST &ast) override;
        void visit(UnaryExpAST& ast) override;
        void visit(UnaryOpAST& ast) override;
        virtual void visit(DeclAST& ast) override;
        virtual void visit(ConstDeclAST& ast) override;
        virtual void visit(BTypeAST& ast) override;
        virtual void visit(ConstDefAST& ast) override;
        virtual void visit(ConstInitValAST& ast) override;
        virtual void visit(BlockItemAST& ast) override;
        virtual void visit(LValAST& ast) override;
        virtual void visit(ConstExpAST& ast) override;
        InitIR *initir=new InitIR();
};