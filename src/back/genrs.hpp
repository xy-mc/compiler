#pragma once
#include "IR/genIR.hpp"
class GenRS : public Visitor_
{
    public:
        std::string rs="";
        void Visit(InitIR &ir) override;
        void Visit(FunDef &ir) override;
        void Visit(SYMBOL &ir) override;
        void Visit(FunBody &ir) override;
        void Visit(Block &ir) override;
        void Visit(Statement &ir) override;
        void Visit(SymbolDef &ir) override;
        void Visit(BinaryExpr &ir) override;
        void Visit(EndStatement &ir) override;
        void Visit(Return &ir) override;
        void Visit(Value &ir) override;
        void Visit(INT &ir) override;
        void Visit(Type &ir) override;
        void Visit(ArrayType &ir) override;
        void Visit(PointerType &ir) override;
        void Visit(FunType &ir) override;
        void Visit(Initializer &ir) override;
        void Visit(Aggregate &ir) override;
        void Visit(GlobalSymbolDef &ir) override;
        void Visit(MemoryDeclaration &ir) override;
        void Visit(GlobalMemoryDeclaration &ir) override;
        void Visit(Load &ir) override;
        void Visit(Store &ir) override;
        void Visit(GetPointer &ir) override;
        void Visit(GetElementPointer &ir) override;
        void Visit(Branch &ir) override;
        void Visit(Jump &ir) override;
        void Visit(FunCall &ir) override;
        void Visit(Funparams &ir) override;
        void Visit(Funparam &ir) override;
        void Visit(FunDecl &ir) override;
        void Visit(FunDeclparams &ir) override;
};