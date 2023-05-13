#pragma once
#include <cassert>
#include <iostream>
#include <list>
#include <map>
#include <set>
#include <memory>
#include <sstream>
#include <string>
#include <utility>
#include <vector>
#include <algorithm>
using namespace std;
class Type;
class ArrayType;
class PointerType;
class FunType;
class Value;
class SYMBOL;
class INT;
class Initializer;
class Aggregate;
class SymbolDef;
class GlobalSymbolDef;
class MemoryDeclaration;
class GlobalMemoryDeclaration;
class Load;
class Store;
class GetPointer;
class GetElementPointer;
class BinaryExpr;
class Branch;
class Jump;
class FunCall;
class Return;
class FunDef;
class Funparams;
class FunBody;
class Block;
class Statement;
class EndStatement;
class FunDecl;
class FunDeclparms;
class InitIR;

class BaseIR 
{
    public:
        virtual ~BaseIR() = default;
        virtual void getir(string &s) =0;
};

class Type :public BaseIR
{
    public:
        enum TypeID 
        {
            I32TyID,
            FunTyID,  // Functions
            ArrayTyID,     // Arrays
            PointerTyID,   // Pointer
        };
        explicit Type(TypeID tid) : tid_(tid) {}
        TypeID tid_;
        ArrayType *arraytype=nullptr;
        FunType *funtype=nullptr;
        PointerType *pointertype=nullptr;
        void getir(string &s) override;
};

//[2 x [3 x i32]]: num_elements_ = 2, contained_ = [3 x i32]
class ArrayType : public Type 
{
    public:
        ArrayType(Type* contained, unsigned num_elements) : Type(Type::ArrayTyID), contained_(contained) , num_elements_(num_elements){}
        Type* contained_;        // The element type of the array.
        unsigned num_elements_;  // Number of elements in the array.
        void getir(string &s) override;
};

//[2 x [3 x i32]]*
class PointerType : public Type 
{
    public:
        PointerType(Type* contained) : Type(Type::PointerTyID), contained_(contained) {}
        Type* contained_;  // The element type of the ptr.
        void getir(string &s) override;
};

// declare i32 @putarray(i32, i32*)
class FunType : public Type 
{
    public:
        FunType(Type* result, std::vector<Type*> params) : Type(Type::FunTyID) 
        {
            result_ = result;
            for (Type* p : params) 
            {
                args_.push_back(p);
            }
        }
        Type* result_;
        std::vector<Type*> args_;
        void getir(string &s) override;
};


class Value : public BaseIR
{
    public:
        enum ValueID
        {
            SYMBOLID,
            INTID,
            undefID,
        };
        explicit Value(ValueID tid) : tid_(tid) {} 
        ~Value() = default;
        ValueID tid_;
        SYMBOL *symbol=nullptr;
        INT *i32=nullptr;
        void getir(string &s) override;
};

class SYMBOL: public Value
{
    public:
        SYMBOL(string symbol_):Value(Value::SYMBOLID), symbol(symbol_) {}
        string symbol;
        void getir(string &s) override;
};
class INT: public Value
{
    public:
        INT(int intconst):Value(Value::INTID),int_const(intconst){}
        int int_const;
        void getir(string &s) override;
};

class Initializer: public BaseIR
{
    public:
        enum InID
        {
            INDID,
            undefID,
            AggregateID,
            zeroinitID,
        };
        Aggregate *aggre=nullptr;
        explicit Initializer(InID tid) : tid_(tid) {} 
        InID tid_;
        void getir(string &s) override;
};

class Aggregate: public BaseIR
{
    public:
        vector<Initializer*>initialzer_;   
        void getir(string &s) override;
};

class SymbolDef: public BaseIR
{
    public:
};

class GlobalSymbolDef: public BaseIR
{
    public:
};

class MemoryDeclaration: public BaseIR
{
    public:
        
};

class GlobalMemoryDeclaration: public BaseIR
{
    public:
        
};
class Load: public BaseIR
{
    public:
        
};
class Store: public BaseIR
{
    public:
       
};
class GetPointer: public BaseIR
{
    public:
};
class GetElementPointer: public BaseIR
{
    public:
        
};
class BinaryExpr: public BaseIR
{
    public:
        
};
class Branch: public BaseIR
{
    public:
       
};
class Jump: public BaseIR
{
    public:
        
};
class FunCall: public BaseIR
{
    public:
        
};
class Return: public BaseIR
{
    public:
        Return(Value* value_) : value(std::move(value_)) {}
        Value *value=nullptr;
        void getir(string &s) override;
};
class FunDef: public BaseIR
{
    public:
        SYMBOL *symbol=nullptr;
        Funparams *funparams=nullptr;
        Type *type=nullptr;
        FunBody *funbody=nullptr;
        void getir(string &s) override;
};

class Funparam: public BaseIR
{
    public:
        SYMBOL *symbol=nullptr;
        Type *type=nullptr;
        void getir(string &s) override;
};
class Funparams: public BaseIR
{
    public:
        vector<Funparam*> funparam_;
        void getir(string &s) override;
};
class FunBody: public BaseIR
{
    public:
        FunBody(vector<Block*>block):block_(block){}
        vector<Block*> block_;
        void getir(string &s) override;
};
class Block: public BaseIR
{
    public:
        Block(SYMBOL*symbol_,vector<Statement *>stmt_,EndStatement*estmt):
        symbol(std::move(symbol_)), statement_(stmt_), endstatement(std::move(estmt)) {}
        SYMBOL *symbol=nullptr;
        vector<Statement*> statement_;
        EndStatement *endstatement=nullptr;
        void getir(string &s) override;
};
class Statement: public BaseIR
{
    public:
        SymbolDef *symboldef=nullptr;
        Store *store=nullptr;
        FunCall *funcall=nullptr;
        void getir(string &s) override;
};
class EndStatement: public BaseIR
{
    public:
        enum esID
        {
            BranchID,
            JumpID,
            ReturnID,
        };
        explicit EndStatement(esID tid) : tid_(tid) {}
        esID tid_;
        Branch *branch=nullptr;
        Jump *jump=nullptr;
        Return *ret=nullptr;
        void getir(string &s) override;
};
class FunDecl: public BaseIR
{
    public:
        SYMBOL *symbol=nullptr;
        FunDeclparms *fundeclparms=nullptr;
        Type *type=nullptr;
        void getir(string &s) override;
};
class FunDeclparms: public BaseIR
{
    public:
        vector<Type*>type_;
        void getir(string &s) override;
};


class InitIR : public BaseIR
{
    public:
        vector<GlobalSymbolDef*>globalsymboldef_;
        vector<FunDef*>fundef_;
        void getir(string &s) override;
};