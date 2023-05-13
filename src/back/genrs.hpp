#pragma once
#include "IR/genIR.hpp"
class GenRS
{
    public:
        std::string rs="";
        void Visit(InitIR *ir);
        void Visit(FunDef *ir);
        void Visit(SYMBOL *ir);
        void Visit(FunBody *ir);
        void Visit(Block *ir);
        void Visit(Statement *ir);
        void Visit(EndStatement *ir);
        void Visit(Return *ir);
        void Visit(Value *ir);
        void Visit(INT *ir);
};