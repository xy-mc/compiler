#pragma once

#include <cstring>
#include <vector>
#include <string>
#include <memory>
#include <iostream>
#include <map>
#include "../define.hpp"
#include "IR/ir.hpp"
using namespace std;

class BaseAST;
class Visitor;
class CompUnitAST;
class FuncDefAST;
class BlockAST;
class BlockItemListAST;
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
class NumberAST;

class DeclAST;
class ConstDeclAST;
class BTypeAST;
class ConstDefAST;
class ConstInitValAST;
class BlockItemAST;
class LValAST;
class ConstExpAST;

class VarDeclAST;
class VarDefAST;
class InitValAST;

class FuncFParamsAST;
class FuncFParamAST;
class FuncRParamsAST;
class DeclDefAST;

class ExpListAST;
class ConstInitValListAST;
class InitValListAST;

class BaseAST 
{
    public:
        virtual ~BaseAST() = default;
        virtual void accept(Visitor &visitor) = 0;
        virtual int getvalue()=0;
};

class CompUnitAST : public BaseAST 
{
    public:
        vector<std::unique_ptr<BaseAST>> decldef_;
        void accept(Visitor &visitor) override;
        int getvalue() override
        {
            return 0;
        }
};

class DeclDefAST :public BaseAST
{
    public:
        enum DeclDefID
        {
            declID,
            funcID,
        };
        unique_ptr<BaseAST>decl;
        unique_ptr<BaseAST>funcdef;
        DeclDefID tid;
        void accept(Visitor &visitor) override;
        int getvalue() override
        {
            return 0;
        }
};

class FuncDefAST : public BaseAST 
{
    public:
        std::unique_ptr<BaseAST> btype;
        std::string ident;
        std::unique_ptr<BaseAST> funcfparams;
        std::unique_ptr<BaseAST> block;
        void accept(Visitor &visitor) override;
        int getvalue() override
        {
            return 0;
        }
};

class BTypeAST : public BaseAST 
{
    public:
        enum BivTID
        {
            intID,
            voidID,
        };
        BivTID tid;
        void accept(Visitor &visitor) override;
        int getvalue() override
        {
            return 0;
        }
};

class FuncFParamsAST :public BaseAST
{
    public:
        vector<unique_ptr<BaseAST>>funcfparam_;
        void accept(Visitor &visitor) override;
        int getvalue() override
        {
            return 0;
        }
};

class FuncFParamAST :public BaseAST
{
    public:
        enum FuncFpID
        {
            nparenID,
            oparenID,
            parensID,
        };
        FuncFpID tid;
        unique_ptr<BaseAST>btype;
        string ident;
        unique_ptr<BaseAST>constexplist;
        void accept(Visitor &visitor) override;
        int getvalue() override
        {
            return 0;
        }
};

class BlockAST : public BaseAST 
{
    public:
        vector<unique_ptr<BaseAST>> blockitem_;
        void accept(Visitor &visitor) override;
        int getvalue() override
        {
            return 0;
        }
};

class BlockItemListAST 
{
    public:
        vector<unique_ptr<BaseAST>> blockitem_;
};

class BlockItemAST:public BaseAST
{
    public:
        enum BlItID
        {
            declID,
            stmtID,
        };
        unique_ptr<BaseAST>decl=nullptr;
        unique_ptr<BaseAST>stmt=nullptr;
        BlItID tid;
        void accept(Visitor &visitor) override;
        int getvalue() override
        {
            return 0;
        }
};

class StmtAST : public BaseAST 
{
    public:
        enum StmtID
        {
            lvalID,
            expID,
            nexpID,
            blockID,
            rexpID,
            rnexpID,
            ifID,
            ifelID,
            whileID,
            breakID,
            continueID,
        };
        StmtID tid;
        std::unique_ptr<BaseAST> exp;
        std::unique_ptr<BaseAST> lval;
        std::unique_ptr<BaseAST> block;
        std::unique_ptr<BaseAST> ifstmt;
        std::unique_ptr<BaseAST> elsestmt;
        std::unique_ptr<BaseAST> whilestmt;
        void accept(Visitor &visitor) override;
        int getvalue() override
        {
            return 0;
        }
};

class ExpAST : public BaseAST
{
    public:
        std::unique_ptr<BaseAST>lorexp;
        void accept(Visitor &visitor) override;
        int getvalue() override
        {
            return lorexp->getvalue();
        }
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
        void accept(Visitor &visitor) override;
        int getvalue() override
        {
            switch(tid)
            {
                case unarID:
                    return unaryexp->getvalue();
                case mulID:
                    return unaryexp->getvalue()*mulexp->getvalue();
                case divID:
                    return unaryexp->getvalue()/mulexp->getvalue();
                case modID:
                    return unaryexp->getvalue()%mulexp->getvalue();
            }
        }
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
        void accept(Visitor &visitor) override;
        int getvalue() override
        {
            switch(tid)
            {
                case mulID:
                    return mulexp->getvalue();
                case addID:
                    return addexp->getvalue()+mulexp->getvalue();
                case subID:
                    return addexp->getvalue()-mulexp->getvalue();
            }
        }
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
        void accept(Visitor &visitor) override;
        int getvalue() override
        {
            switch(tid)
            {
                case addID:
                    return addexp->getvalue();
                case ltID:
                    return relexp->getvalue()<addexp->getvalue();
                case gtID:
                    return relexp->getvalue()>addexp->getvalue();
                case leID:
                    return relexp->getvalue()<=addexp->getvalue();
                case geID:
                    return relexp->getvalue()>=addexp->getvalue();
            }
        }
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
        void accept(Visitor &visitor) override;
        int getvalue()override
        {
            switch(tid)
            {
                case relID:
                    return relexp->getvalue();
                case neID:
                    return eqexp->getvalue()!=relexp->getvalue();
                case eqID:
                    return eqexp->getvalue()==relexp->getvalue();
            }
        }
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
        void accept(Visitor &visitor) override;
        int getvalue()override
        {
            switch(tid)
            {
                case eqID:
                    return eqexp->getvalue();
                case landID:
                    return landexp->getvalue()&&eqexp->getvalue();
            }
        }
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
        void accept(Visitor &visitor) override;
        int getvalue()override
        {
            switch(tid)
            {
                case landID:
                    return landexp->getvalue();
                case lorID:
                    return lorexp->getvalue()||landexp->getvalue();
            }
        }
};

class PrimaryExpAST:public BaseAST
{
    public:
        enum PrExID
        {
            expID,
            lvalID,
            numID,
        };
        unique_ptr<BaseAST>exp=nullptr;
        unique_ptr<BaseAST>lval=nullptr;
        unique_ptr<BaseAST>number=nullptr;
        PrExID tid;
        void accept(Visitor &visitor) override;
        int getvalue()override
        {
            switch(tid)
            {
                case expID:
                    return exp->getvalue();
                case lvalID:
                    return lval->getvalue();
                case numID:
                    return number->getvalue();
            }
        }
};

class NumberAST : public BaseAST 
{
    public:
        int int_const;
        void accept(Visitor &visitor) override;
        int getvalue() override
        {
            return int_const;
        }
};

class UnaryExpAST : public BaseAST
{
    public:
        enum UnaryOpID
        {
            priID,
            poID,
            neID,
            noID,
            funcID,
            nfuncID,
        };
        std::unique_ptr<BaseAST> primaryexp=nullptr;
        std::unique_ptr<BaseAST> unaryexp=nullptr;
        string ident;
        std::unique_ptr<BaseAST> funcrparams;
        UnaryOpID tid;
        void accept(Visitor &visitor) override;
        int getvalue() override
        {
            switch(tid)
            {
                case priID:
                    return primaryexp->getvalue();
                    break;
                case neID:
                    return -unaryexp->getvalue();
                    break;
                case noID:
                    return !unaryexp->getvalue();
                    break;
            }
            return 0;
        }
};

class FuncRParamsAST : public BaseAST
{
    public:
        vector<unique_ptr<BaseAST>>exp_;
        void accept(Visitor &visitor) override;
        int getvalue() override
        {
            return 0;
        }
};

class DeclAST : public BaseAST
{
    public:
        enum DeclID
        {
            constID,
            varID,
        };
        DeclID tid;
        unique_ptr<BaseAST>constdecl;
        unique_ptr<BaseAST>vardecl;
        void accept(Visitor &visitor) override;
        int getvalue() override
        {
            return 0;
        }
};

class ConstDeclAST :public BaseAST
{
    public:
        unique_ptr<BaseAST>btype;
        vector<unique_ptr<BaseAST>>constdef_;
        void accept(Visitor &visitor) override;
        int getvalue() override
        {
            return 0;
        }
};

class ConstDefListAST 
{
    public:
        vector<unique_ptr<BaseAST>>constdef_;
};

class ExpListAST:public BaseAST
{
    public:
        vector<unique_ptr<BaseAST>>exp_;
        void accept(Visitor &visitor) override;
        int getvalue() override
        {
            return 0;
        }
};

class ConstDefAST:public BaseAST
{
    public:
        enum ConstDefID
        {
            nconstID,
            constID,
        };
        ConstDefID tid;
        string ident;
        unique_ptr<BaseAST>constexplist;
        unique_ptr<BaseAST>constinitval;
        void accept(Visitor &visitor) override;
        int getvalue() override
        {
            return 0;
        }
};

class VarDeclAST :public BaseAST
{
    public:
        unique_ptr<BaseAST>btype;
        vector<unique_ptr<BaseAST>>vardef_;
        void accept(Visitor &visitor) override;
        int getvalue() override
        {
            return 0;
        }
};

class VarDefListAST 
{
    public:
        vector<unique_ptr<BaseAST>>vardef_;
};

class VarDefAST:public BaseAST
{
    public:
        enum VarDefID
        {
            nconstID,
            constID,
            ncinitID,
            cinitID,
        };
        VarDefID tid;
        string ident;
        unique_ptr<BaseAST>constexplist=nullptr;
        unique_ptr<BaseAST>initval=nullptr;
        void accept(Visitor &visitor) override;
        int getvalue() override
        {
            return 0;
        }
};

class InitValAST :public BaseAST
{
    public:
        enum InitValID
        {
            expID,
            init_ID,
            nexpID,
        };
        InitValID tid;
        unique_ptr<BaseAST>exp;
        unique_ptr<BaseAST>initvallist;
        void accept(Visitor &visitor) override;
        int getvalue() override
        {
            return exp->getvalue();
        }
};

class InitValListAST:public BaseAST
{
    public:
        vector<unique_ptr<BaseAST>>initval_;
        void accept(Visitor &visitor) override;
        int getvalue() override
        {
            return 0;
        }
};

class ConstInitValAST:public BaseAST
{
    public:
        enum CInitValID
        {
            cexpID,
            cexp_ID,
            nexpID,
        };
        CInitValID tid;
        unique_ptr<BaseAST>constexp;
        unique_ptr<BaseAST>constinitvallist;
        void accept(Visitor &visitor) override;
        int getvalue() override
        {
            return 0;
        }
};

class ConstInitValListAST:public BaseAST
{
    public:
        vector<unique_ptr<BaseAST>>constinitval_;
        void accept(Visitor &visitor) override;
        int getvalue() override
        {
            return 0;
        }
};

class LValAST:public BaseAST
{
    public:
        enum LValID
        {
            expID,
            nexpID,
        };
        LValID tid;
        string ident;
        unique_ptr<BaseAST>explist;
        void accept(Visitor &visitor) override;
        int getvalue() override;
};

class ConstExpAST:public BaseAST
{
    public:
        unique_ptr<BaseAST>exp;
        void accept(Visitor &visitor) override;
        int getvalue() override
        {
            return 0;
        }
};



class Visitor {
    public:
        virtual void visit(CompUnitAST& ast) = 0;
        virtual void visit(FuncDefAST& ast) = 0;
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
        virtual void visit(DeclAST& ast)=0;
        virtual void visit(ConstDeclAST& ast)=0;
        virtual void visit(BTypeAST& ast)=0;
        virtual void visit(ConstDefAST& ast)=0;
        virtual void visit(ConstInitValAST& ast)=0;
        virtual void visit(BlockItemAST& ast)=0;
        virtual void visit(LValAST& ast)=0;
        virtual void visit(ConstExpAST& ast)=0;
        virtual void visit(VarDeclAST& ast)=0;
        virtual void visit(VarDefAST& ast)=0;
        virtual void visit(InitValAST& ast)=0;
        virtual void visit(FuncFParamsAST& ast)=0;
        virtual void visit(FuncFParamAST& ast)=0;
        virtual void visit(FuncRParamsAST& ast)=0;
        virtual void visit(DeclDefAST& ast)=0;
        virtual void visit(ExpListAST& ast)=0;
        virtual void visit(ConstInitValListAST& ast)=0;
        virtual void visit(InitValListAST& ast)=0;
};


