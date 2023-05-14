#ifndef TEST_AST_H
#define TEST_AST_H
#pragma once

#include <cstring>
#include <vector>
#include <string>
#include <memory>
#include <iostream>
#include <../define.hpp>
using namespace std;
class BaseAST;

class CompUnitAST;
class FuncDefAST;
class FuncTypeAST;
class BlockAST;
class StmtAST;
class ExpAST;
class PrimaryExpAST;
class UnaryExpAST;
class UnaryOpAST;
class NumberAST;
class Visitor;




class BaseAST 
{
    public:
        virtual ~BaseAST() = default;
        virtual void accept(Visitor &visitor) = 0;
        virtual void getast(string &s) const =0;
};

class CompUnitAST : public BaseAST 
{
    public:
        std::unique_ptr<BaseAST> funcdef;
        void getast(string &s) const override
        {
            s+="CompUnitAST { ";
            funcdef->getast(s);
            s+="} ";
        }
        void accept(Visitor &visitor) override;
};


class FuncDefAST : public BaseAST 
{
    public:
        std::unique_ptr<BaseAST> functype;
        std::string ident;
        std::unique_ptr<BaseAST> block;
        void getast(string &s) const override
        {
            s+="FuncDefAST { ";
            functype->getast(s);
            s+=", " +ident + ", ";
            block->getast(s);
            s+="} ";
        }
        void accept(Visitor &visitor) override;
};

class FuncTypeAST : public BaseAST 
{
    public:
        void getast(string &s) const override
        {
            s+="FuncTypeAST { ";
            s+="int ";
            s+="} ";
        }
        void accept(Visitor &visitor) override;
};

class BlockAST : public BaseAST 
{
    public:
        std::unique_ptr<BaseAST> stmt;
        void getast(string &s) const override
        {
            s+="BlockAST { ";
            stmt->getast(s);
            s+="} ";
        }
        void accept(Visitor &visitor) override;
};

class StmtAST : public BaseAST 
{
    public:
        std::unique_ptr<BaseAST> exp;
        void getast(string &s) const override
        {
            s+="StmtAST { ";
            s+="return ";
            exp->getast(s);
            s+="; ";
            s+="} ";
        } 
        void accept(Visitor &visitor) override;
};

class ExpAST : public BaseAST
{
    public:
        std::unique_ptr<BaseAST>unaryexp;
        void getast(string &s)const override
        {
            s+="ExpAST ";
            s+="{ ";
            unaryexp->getast(s);
            s+="; ";
            s+="} ";
        }
        void accept(Visitor &visitor) override;
};

class PrimaryExpAST : public BaseAST
{
    public:
        std::unique_ptr<BaseAST> exp=nullptr;
        std::unique_ptr<BaseAST> number=nullptr;
        void getast(string &s) const override
        {
            s+="PrimaryExpAST ";
            s+="{ ";
            if(exp!=nullptr)
            {
                s+="( ";
                exp->getast(s);
                s+=") ";
            }
            else
            {
                number->getast(s);
            }
            s+="; ";
            s+="} ";
        }
        void accept(Visitor &visitor) override;
};

class NumberAST : public BaseAST 
{
    public:
        int int_const;
        void getast(string &s)const override
        {
            s+=to_string(int_const);
        }
        void accept(Visitor &visitor) override;
};

class UnaryExpAST : public BaseAST
{
    public:
        std::unique_ptr<BaseAST> primaryexp=nullptr;
        std::unique_ptr<BaseAST> unaryop=nullptr;
        std::unique_ptr<BaseAST> unaryexp=nullptr;
        void getast(string &s) const override
        {
            s+="UnaryExpAST ";
            s+="{ ";
            if(primaryexp!=nullptr)
            {
                primaryexp->getast(s);
            }
            else
            {
                unaryop->getast(s);
                unaryexp->getast(s);
            }
            s+="; ";
            s+="} ";
        }
        void accept(Visitor &visitor) override;
};

class UnaryOpAST : public BaseAST
{
    public:
        enum UnaryOpID
        {
            PID,
            NeID,
            NoID,
        };
        UnaryOpAST(UnaryOpID tid_):tid(tid_){}
        UnaryOpID tid;
        void getast(string &s)const override
        {
            switch (tid)
            {
                case PID:
                    s+="+ ";
                    break;
                case NeID:
                    s+="- ";
                    break;
                case NoID:
                    s+="! ";
            }
        }
        void accept(Visitor &visitor) override;
};

class Visitor {
public:
    virtual void visit(CompUnitAST& ast) = 0;
    virtual void visit(FuncDefAST& ast) = 0;
    virtual void visit(FuncTypeAST& ast) = 0;
    virtual void visit(BlockAST& ast) = 0;
    virtual void visit(StmtAST& ast) = 0;
    virtual void visit(ExpAST& ast)=0;
    virtual void visit(PrimaryExpAST& ast)=0;
    virtual void visit(NumberAST& ast) = 0;
    virtual void visit(UnaryExpAST& ast)=0;
    virtual void visit(UnaryOpAST& ast)=0;
};

#endif //TEST_AST_H
