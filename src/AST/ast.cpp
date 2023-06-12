#include "ast.hpp"
#include "genIR.hpp"

void CompUnitAST::accept(Visitor &visitor) {
    visitor.visit(*this);
}

void FuncDefAST::accept(Visitor &visitor) {
    visitor.visit(*this);
}

void BlockAST::accept(Visitor &visitor) {
    visitor.visit(*this);
}

void StmtAST::accept(Visitor &visitor) {
    visitor.visit(*this);
}

void ExpAST::accept(Visitor &visitor) {
    visitor.visit(*this);
}

void MulExpAST::accept(Visitor &visitor) {
    visitor.visit(*this);
}

void AddExpAST::accept(Visitor &visitor) {
    visitor.visit(*this);
}

void RelExpAST::accept(Visitor &visitor) {
    visitor.visit(*this);
}

void EqExpAST::accept(Visitor &visitor) {
    visitor.visit(*this);
}

void LAndExpAST::accept(Visitor &visitor) {
    visitor.visit(*this);
}

void LOrExpAST::accept(Visitor &visitor) {
    visitor.visit(*this);
}

void PrimaryExpAST::accept(Visitor &visitor) {
    visitor.visit(*this);
}

void NumberAST::accept(Visitor &visitor) {
    visitor.visit(*this);
}

void UnaryExpAST::accept(Visitor &visitor) {
    visitor.visit(*this);
}

void DeclAST::accept(Visitor &visitor) {
    visitor.visit(*this);
}

void ConstDeclAST::accept(Visitor &visitor) {
    visitor.visit(*this);
}

void BTypeAST::accept(Visitor &visitor) {
    visitor.visit(*this);
}

void ConstDefAST::accept(Visitor &visitor) {
    visitor.visit(*this);
}

void ConstInitValAST::accept(Visitor &visitor) {
    visitor.visit(*this);
}

void BlockItemAST::accept(Visitor &visitor) {
    visitor.visit(*this);
}

void LValAST::accept(Visitor &visitor) {
    visitor.visit(*this);
}

void ConstExpAST::accept(Visitor &visitor) {
    visitor.visit(*this);
}

void VarDeclAST::accept(Visitor &visitor) {
    visitor.visit(*this);
}

void VarDefAST::accept(Visitor &visitor) {
    visitor.visit(*this);
}

void InitValAST::accept(Visitor &visitor) {
    visitor.visit(*this);
}

void FuncFParamsAST::accept(Visitor &visitor) {
    visitor.visit(*this);
}

void FuncFParamAST::accept(Visitor &visitor) {
    visitor.visit(*this);
}

void FuncRParamsAST::accept(Visitor &visitor) {
    visitor.visit(*this);
}

void DeclDefAST::accept(Visitor &visitor) {
    visitor.visit(*this);
}



extern Scope *scope;

int LValAST::getvalue()
{
    return scope->find(ident)->value;
}