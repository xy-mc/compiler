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
        std::unique_ptr<ArrayType> arraytype=nullptr;
        std::unique_ptr<FunType> funtype=nullptr;
        std::unique_ptr<PointerType> pointertype=nullptr;
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
        virtual std::string print();
        ValueID tid_;
        std::unique_ptr<SYMBOL> symbol=nullptr;
        std::unique_ptr<INT> i32=nullptr;
        void getir(string &s) override;
};

class SYMBOL: public BaseIR
{
    public:
        string sym;
};
class INT: public BaseIR
{
    public:
        int int_const;
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
        std::unique_ptr<Aggregate> aggre=nullptr;
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
        std::unique_ptr<Value> value=nullptr;
        void getir(string &s) override;
};
class FunDef: public BaseIR
{
    public:
        std::unique_ptr<SYMBOL> symbol=nullptr;
        std::unique_ptr<Funparams> funparams=nullptr;
        std::unique_ptr<Type> type=nullptr;
        std::unique_ptr<FunBody> funbody=nullptr;
        void getir(string &s) override;
};

class Funparam: public BaseIR
{
    public:
        std::unique_ptr<SYMBOL> symbol=nullptr;
        std::unique_ptr<Type> type=nullptr;
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
        vector<Block*> block_;
        void getir(string &s) override;
};
class Block: public BaseIR
{
    public:
        std::unique_ptr<SYMBOL> symbol=nullptr;
        vector<Statement*> statement_;
        std::unique_ptr<EndStatement> endstatement=nullptr;
        void getir(string &s) override;
};
class Statement: public BaseIR
{
    public:
        std::unique_ptr<SymbolDef> symboldef=nullptr;
        std::unique_ptr<Store> store=nullptr;
        std::unique_ptr<FunCall> funcall=nullptr;
        void getir(string &s) override;
};
class EndStatement: public BaseIR
{
    public:
        std::unique_ptr<Branch> branch=nullptr;
        std::unique_ptr<Jump> jump=nullptr;
        std::unique_ptr<Return> retu=nullptr;
        void getir(string &s) override;
};
class FunDecl: public BaseIR
{
    public:
        std::unique_ptr<SYMBOL> symbol=nullptr;
        std::unique_ptr<FunDeclparms> fundeclparms=nullptr;
        std::unique_ptr<Type> type=nullptr;
        void getir(string &s) override;
};
class FunDeclparms: public BaseIR
{
    public:
        vector<Type*>type_;
        void getir(string &s) override;
};