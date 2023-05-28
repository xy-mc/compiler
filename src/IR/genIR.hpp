#pragma once
#include "ir.hpp"
#include "AST/ast.hpp"
#include <map>
#include <vector>
class Def
{
    public:
        enum defID
        {
            constID,
            varID,
            nvarID,
            funID,
        };
        Def(defID tid_,int value_,string name_):tid(tid_),value(value_),name(name_){}
        defID tid;
        int value;
        string name;
};

class Scope 
{
    public:
        // enter a new scope
        void enter() 
        {
            fhb.push_back({});
        }

        // exit a scope
        void exit() 
        {
            fhb.pop_back();
        }

        // bool in_global() 
        // {
        //     return fhb.size() == 1;
        // }

        // push a name to scope
        // return true if successful
        // return false if this name already exits
        // but func name could be same with variable name
        bool push(std::string name, Def *def) 
        {
            bool result;
            result = (fhb[fhb.size() - 1].insert({name, def})).second;
            return result;
        }

        Def* find(std::string name) 
        {
            for (auto s = fhb.rbegin(); s != fhb.rend(); s++) 
            {
                auto iter = s->find(name);
                if (iter != s->end()) 
                {
                    return iter->second;
                }
            }
            return nullptr;
        }


    private:
        std::vector<std::map<std::string, Def *>> fhb;
};

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
        void visit(DeclAST& ast) override;
        void visit(ConstDeclAST& ast) override;
        void visit(BTypeAST& ast) override;
        void visit(ConstDefAST& ast) override;
        void visit(ConstInitValAST& ast) override;
        void visit(BlockItemAST& ast) override;
        void visit(LValAST& ast) override;
        void visit(ConstExpAST& ast) override;
        void visit(VarDeclAST& ast) override;
        void visit(VarDefAST& ast) override;
        void visit(InitValAST& ast) override;
        void visit(FuncFParamsAST& ast) override;
        void visit(FuncFParamAST& ast) override;
        void visit(FuncRParamsAST& ast) override;
        void visit(DeclDefAST& ast) override;
        InitIR *initir=new InitIR();
};