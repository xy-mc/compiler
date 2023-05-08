#pragma once
#include<iostream>
#include<string>
using namespace std;
// int ir_t=0;
// using namespace std;
// 所有 AST 的基类
class BaseAST {
    public:
        virtual ~BaseAST() = default;
        virtual void Dump() const = 0;
        virtual void getast(string &s) const =0;
        virtual void getir(string &s) const=0;
};
// CompUnit 是 BaseAST
class CompUnitAST : public BaseAST {
    public:
  // 用智能指针管理对象
        std::unique_ptr<BaseAST> func_def;
        void Dump() const override 
        {
            std::cout << "CompUnitAST { ";
            func_def->Dump();
            std::cout << " }";
        }
        void getast(string &s) const override
        {
            s+="CompUnitAST { ";
            func_def->getast(s);
            s+=" }";
        }
        void getir(string &s)const override
        {
            func_def->getir(s);
        }
};

// FuncDef 也是 BaseAST
class FuncDefAST : public BaseAST {
    public:
        std::unique_ptr<BaseAST> func_type;
        std::string ident;
        std::unique_ptr<BaseAST> block;
        void Dump() const override 
        {
            std::cout << "FuncDefAST { ";
            func_type->Dump();
            std::cout << ", " << ident << ", ";
            block->Dump();
            std::cout << " }";
        }
        void getast(string &s) const override
        {
            s+="FuncDefAST { ";
            func_type->getast(s);
            s+=", " +ident + ", ";
            block->getast(s);
            s+=" }";
        }
        void getir(string &s)const override
        {
            s+="fun ";
            s+="@"+ident+"(): ";
            func_type->getir(s);
            s+="{ \n";
            block->getir(s);
        }
};
class FuncTypeAST : public BaseAST {
    public:
        void Dump() const override
        {
            std::cout<<"FuncTypeAST { ";
            std::cout<<"int";
            std::cout<<" }";
        }
        void getast(string &s) const override
        {
            s+="FuncTypeAST { ";
            s+="int";
            s+=" }";
        }
        void getir(string &s)const override
        {
            s+="i32 ";
        }
};
class BlockAST : public BaseAST {
    public:
        std::unique_ptr<BaseAST> stmt;
        void Dump() const override
        {
            std::cout<<"BlockAST { ";
            stmt->Dump();
            std::cout<<" }";
        }
        void getast(string &s) const override
        {
            s+="BlockAST { ";
            stmt->getast(s);
            s+=" }";
        }
        void getir(string &s) const override
        {
            s+="%entry:\n";
            // ir_t++;
            stmt->getir(s);
        }
};
class StmtAST : public BaseAST {
    public:
        std::unique_ptr<BaseAST> number;
        void Dump() const override
        {
            std::cout<<"StmtAST { ";
            std::cout<<"return ";
            number->Dump();
            std::cout<<" ;";
            std::cout<<" }";
        }
        void getast(string &s) const override
        {
            s+="StmtAST { ";
            s+="return ";
            number->getast(s);
            s+=" ;";
            s+=" }";
        } 
        void getir(string &s)const override
        {
            s+="    ret ";
            number->getir(s);
            s+="\n}";
        }
};
class NumberAST : public BaseAST {
    public:
        int int_const;
        void Dump() const override
        {
            // std::cout<<" { ";
            std::cout<<int_const;
            // std::cout<<" }";
        }
        void getast(string &s)const override
        {
            s+=to_string(int_const);
        }
        void getir(string &s)const override
        {
            s+=to_string(int_const);
        }
};