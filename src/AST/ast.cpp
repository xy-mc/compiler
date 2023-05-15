#include "ast.hpp"


void CompUnitAST::accept(Visitor &visitor) {
    visitor.visit(*this);
}

void FuncDefAST::accept(Visitor &visitor) {
    visitor.visit(*this);
}

void FuncTypeAST::accept(Visitor &visitor) {
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

void UnaryOpAST::accept(Visitor &visitor) {
    visitor.visit(*this);
}



