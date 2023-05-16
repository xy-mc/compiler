#pragma once

#include <cstring>
#include <vector>
#include <string>
#include <memory>
#include <iostream>
#include "../define.hpp"
#include "IR/ir.hpp"
using namespace std;

class BaseAST;
class Visitor;
class CompUnitAST;
class FuncDefAST;
class FuncTypeAST;
class BlockAST;
class StmtAST;
class ExpAST;
class MulExpAST;
class AddExpAST;
class RelExpAST;
class EqExpAST;
class LAndExpAST;
class LOrExpAST;
class PrimaryExpAST;
class UnaryExpAST;
class UnaryOpAST;
class NumberAST;




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
        std::unique_ptr<BaseAST>lorexp;
        void getast(string &s)const override
        {
            s+="ExpAST ";
            s+="{ ";
            lorexp->getast(s);
            s+="; ";
            s+="} ";
        }
        void accept(Visitor &visitor) override;
};

class MulExpAST:public BaseAST
{
    public:
        enum MulID
        {
            unarID,
            mulID,
            divID,
            modID,
        };
        std::unique_ptr<BaseAST>unaryexp=nullptr;
        std::unique_ptr<BaseAST>mulexp=nullptr;
        MulID tid;
        void getast(string &s)const override
        {
            return;
        }
        void accept(Visitor &visitor) override;
};

class AddExpAST : public BaseAST
{
    public:
        enum AddID
        {
            mulID,
            addID,
            subID,
        };
        std::unique_ptr<BaseAST>addexp=nullptr;
        std::unique_ptr<BaseAST>mulexp=nullptr;
        AddID tid;
        void getast(string &s)const override
        {
            return;
        }
        void accept(Visitor &visitor) override;
};

class RelExpAST :public BaseAST
{
    public:
        enum RelID
        {
            addID,
            ltID, 
            gtID, 
            leID, 
            geID, 
        };
        std::unique_ptr<BaseAST>addexp=nullptr;
        std::unique_ptr<BaseAST>relexp=nullptr;
        RelID tid;
        void getast(string &s)const override
        {
            return;
        }
        void accept(Visitor &visitor) override;
};

class EqExpAST : public BaseAST
{
    public:
        enum EqID
        {
            relID,
            neID, 
            eqID,
        };
        std::unique_ptr<BaseAST>relexp=nullptr;
        std::unique_ptr<BaseAST>eqexp=nullptr;
        EqID tid;
        void getast(string &s)const override
        {
            return;
        }
        void accept(Visitor &visitor) override;
};

class LAndExpAST :public BaseAST
{
    public:
        enum LAndID
        {
            eqID,
            landID,  
        };
        std::unique_ptr<BaseAST>eqexp=nullptr;
        std::unique_ptr<BaseAST>landexp=nullptr;
        LAndID tid;
        void getast(string &s)const override
        {
            return;
        }
        void accept(Visitor &visitor) override;
};

class LOrExpAST:public BaseAST
{
    public:
        enum LOrID
        {
            landID,
            lorID,
        };
        std::unique_ptr<BaseAST>landexp=nullptr;
        std::unique_ptr<BaseAST>lorexp=nullptr;
        LOrID tid;
        void getast(string &s)const override
        {
            return;
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
        virtual void visit(MulExpAST& ast)=0;
        virtual void visit(AddExpAST& ast)=0;
        virtual void visit(RelExpAST& ast)=0;
        virtual void visit(EqExpAST& ast)=0;
        virtual void visit(LAndExpAST& ast)=0;
        virtual void visit(LOrExpAST& ast)=0;
        virtual void visit(PrimaryExpAST& ast)=0;
        virtual void visit(NumberAST& ast) = 0;
        virtual void visit(UnaryExpAST& ast)=0;
        virtual void visit(UnaryOpAST& ast)=0;
};


