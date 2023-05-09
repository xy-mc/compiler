#ifndef _IR_H_
#define _IR_H_

#include <cassert>
#include <iostream>
#include <list>
#include <map>
#include <set>
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

struct Use {
    Value* val_;
    unsigned int arg_no_;  // 操作数的序号，如func(a,b)中a的序号为0，b的序号为1
    Use(Value* val, unsigned int no) : val_(val), arg_no_(no) {}
};

//-----------------------------------------------Type-----------------------------------------------
class Type {
    public:
        enum TypeID 
        {
            I32TyID,
            FunTyID,  // Functions
            ArrayTyID,     // Arrays
            PointerTyID,   // Pointer
        };
        explicit Type(TypeID tid) : tid_(tid) {}
        ~Type() = default;
        virtual std::string print();
        TypeID tid_;
};

//[2 x [3 x i32]]: num_elements_ = 2, contained_ = [3 x i32]
class ArrayType : public Type 
{
    public:
        ArrayType(Type* contained, unsigned num_elements) : Type(Type::ArrayTyID), num_elements_(num_elements), contained_(contained) {}
        Type* contained_;        // The element type of the array.
        unsigned num_elements_;  // Number of elements in the array.
};

//[2 x [3 x i32]]*
class PointerType : public Type 
{
    public:
        PointerType(Type* contained) : Type(Type::PointerTyID), contained_(contained) {}
        Type* contained_;  // The element type of the ptr.
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
};


class Value
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
        unique_ptr<SYMBOL> symbol=nullptr;
        unique_ptr<INT> i32=nullptr;
};

class SYMBOL
{
    public:
        string sym;
};
class INT
{
    public:
        int int_const;
};

class Initializer
{
    public:
        enum InID
        {
            INDID,
            undefID,
            AggregateID,
            zeroinitID,
        };
        unique_ptr<Aggregate> aggre=nullptr;
        explicit Initializer(InID tid) : tid_(tid) {} 
        ~Initializer() = default;
        virtual std::string print();
        InID tid_;
};

class Aggregate
{
    public:
        vector<Initializer*>initialzer_;   
};

class SymbolDef
{
    public:
};

class GlobalSymbolDef
{
    public:
};

class MemoryDeclaration
{
    public:
};

class GlobalMemoryDeclaration
{
    public:
};
class Load
{
    public:
};
class Store
{
    public:
};
class GetPointer
{
    public:
};
class GetElementPointer
{
    public:
};
class BinaryExpr
{
    public:
};
class Branch
{
    public:
};
class Jump
{
    public:
};
class FunCall
{
    public:
};
class Return
{
    public:
        ~Return() = default;
        virtual std::string print();
        unique_ptr<Value> value=nullptr;
};
class FunDef
{
    public:
        ~FunDef() = default;
        virtual std::string print();
        unique_ptr<SYMBOL> symbol=nullptr;
        unique_ptr<Funparams> funparams=nullptr;
        unique_ptr<Type> type=nullptr;
        unique_ptr<FunBody> funbody=nullptr;
};

class Funparam
{
    public:
        ~Funparam() = default;
        virtual std::string print();
        unique_ptr<SYMBOL> symbol=nullptr;
        unique_ptr<Type> type=nullptr;
};
class Funparams
{
    public:
        ~Funparams() = default;
        virtual std::string print();
        vector<Funparam*> funparam_;
};
class FunBody
{
    public:
        ~FunBody() = default;
        virtual std::string print();
        unique_ptr<Block> block=nullptr;
};
class Block
{
    public:
        ~Block() = default;
        virtual std::string print();
        unique_ptr<SYMBOL> symbol=nullptr;
        vector<Statement*> statement_;
        unique_ptr<EndStatement> endStateme=nullptr;
};
class Statement
{
    public:
        ~Statement() = default;
        virtual std::string print();
        unique_ptr<SymbolDef> symboldef=nullptr;
        unique_ptr<Store> store=nullptr;
        unique_ptr<FunCall> funcall=nullptr;
};
class EndStatement
{
    public:
        ~EndStatement() = default;
        virtual std::string print();
        unique_ptr<Branch> branch=nullptr;
        unique_ptr<Jump> jump=nullptr;
        unique_ptr<Return> retu=nullptr;
};
class FunDecl
{
    public:
};
class FunDeclparms
{
    public:
};