#pragma once
#include <memory>
#include <string>
#include <vector>
#include <iostream>

using namespace std;
class Visitor_;
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
        virtual void accept(Visitor_ &visitor) = 0;
};

class Type :public BaseIR
{
    public:
        enum TypeID 
        {
            i32ID,
            funID,  // Functions
            arrayID,     // Arrays
            poterID,   // Pointer
        };
        explicit Type(TypeID tid_) : tid(tid_) {}
        TypeID tid;
        ArrayType *arraytype=nullptr;
        FunType *funtype=nullptr;
        PointerType *pointertype=nullptr;
        void getir(string &s) override;
        void accept(Visitor_ &visitor) override;
};

//[2 x [3 x i32]]: num_elements_ = 2, contained_ = [3 x i32]
class ArrayType : public Type 
{
    public:
        ArrayType(Type* contained, unsigned num_elements) : Type(Type::arrayID), contained_(contained) , num_elements_(num_elements){}
        Type* contained_;        // The element type of the array.
        unsigned num_elements_;  // Number of elements in the array.
        void getir(string &s) override;
        void accept(Visitor_ &visitor) override;
};

//[2 x [3 x i32]]*
class PointerType : public Type 
{
    public:
        PointerType(Type* contained) : Type(Type::poterID), contained_(contained) {}
        Type* contained_;  // The element type of the ptr.
        void getir(string &s) override;
        void accept(Visitor_ &visitor) override;
};

// declare i32 @putarray(i32, i32*)
class FunType : public Type 
{
    public:
        FunType(Type* result, std::vector<Type*> params) : Type(Type::funID) 
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
        void accept(Visitor_ &visitor) override;
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
        explicit Value(ValueID tid_) : tid(tid_) {} 
        ~Value() = default;
        ValueID tid;
        SYMBOL *symbol=nullptr;
        INT *i32=nullptr;
        void getir(string &s) override;
        void accept(Visitor_ &visitor) override;
};

class SYMBOL: public Value
{
    public:
        SYMBOL(string symbol_):Value(Value::SYMBOLID), symbol(symbol_) {}
        string symbol;
        void getir(string &s) override;
        void accept(Visitor_ &visitor) override;
};
class INT: public Value
{
    public:
        INT(int intconst):Value(Value::INTID),int_const(intconst){}
        int int_const;
        void getir(string &s) override;
        void accept(Visitor_ &visitor) override;
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
        void accept(Visitor_ &visitor) override;
};

class Aggregate: public BaseIR
{
    public:
        vector<Initializer*>initialzer_;   
        void getir(string &s) override;
        void accept(Visitor_ &visitor) override;
};

class SymbolDef: public BaseIR
{
    public:
        enum SymbolDefID
        {
            MemID,
            LoadID,
            GetPID,
            BiEpID,
            FuncID,
        };
        SymbolDef(SYMBOL *symbol_,SymbolDefID tid_,MemoryDeclaration *memorydeclaration_,Load *load_,BinaryExpr 
        *binaryexpr_):symbol(symbol_),tid(tid_),memorydeclaration(memorydeclaration_),load(load_),
        binaryexpr(binaryexpr_){}
        SYMBOL *symbol;
        SymbolDefID tid;
        MemoryDeclaration *memorydeclaration;
        Load *load;
        BinaryExpr *binaryexpr;
        void getir(string &s) override;
        void accept(Visitor_ &visitor) override;
};

class GlobalSymbolDef: public BaseIR
{
    public:
        void accept(Visitor_ &visitor) override;
};

class MemoryDeclaration: public BaseIR
{
    public:
        MemoryDeclaration(Type *type_):type(type_){}
        Type *type;
        void accept(Visitor_ &visitor) override;
        void getir(string &s) override;
};

class GlobalMemoryDeclaration: public BaseIR
{
    public:
        void accept(Visitor_ &visitor) override;
};
class Load: public BaseIR
{
    public:
        Load(SYMBOL *symbol_): symbol(symbol_){}
        SYMBOL *symbol;
        void accept(Visitor_ &visitor) override;
        void getir(string &s) override;
};
class Store: public BaseIR
{
    public:
        enum StoreID
        {
            valueID,
            initID,
        };
        Store(StoreID tid_,Value *value_,Initializer *initializer_,SYMBOL *symbol_):tid(tid_),value(value_),
        initializer(initializer_),symbol(symbol_){}
        StoreID tid;
        Value *value;
        Initializer *initializer;
        SYMBOL *symbol;
        void accept(Visitor_ &visitor) override;
        void getir(string &s) override;
};
class GetPointer: public BaseIR
{
    public:
        void accept(Visitor_ &visitor) override;
};
class GetElementPointer: public BaseIR
{
    public:
        void accept(Visitor_ &visitor) override;
};
class BinaryExpr: public BaseIR
{
    public:
        enum BEID
        {
            neID, 
            eqID,
            gtID, 
            ltID, 
            geID, 
            leID, 
            addID, 
            subID, 
            mulID, 
            divID, 
            modID, 
            andID, 
            orID, 
            xorID, 
            shlID, 
            shrID, 
            sarID,
        };
        BinaryExpr(BEID tid_,Value *value1_,Value *value2_):tid(tid_),value1(value1_),value2(value2_){}
        BEID tid; 
        Value *value1=nullptr;
        Value *value2=nullptr;
        void getir(string &s) override;
        void accept(Visitor_ &visitor) override;       
};
class Branch: public BaseIR
{
    public:
       void accept(Visitor_ &visitor) override;
};
class Jump: public BaseIR
{
    public:
        void accept(Visitor_ &visitor) override;
};
class FunCall: public BaseIR
{
    public:
        void accept(Visitor_ &visitor) override;
};
class Return: public BaseIR
{
    public:
        Return(Value* value_) : value(std::move(value_)) {}
        Value *value=nullptr;
        void getir(string &s) override;
        void accept(Visitor_ &visitor) override;
};
class FunDef: public BaseIR
{
    public:
        SYMBOL *symbol=nullptr;
        Funparams *funparams=nullptr;
        Type *type=nullptr;
        FunBody *funbody=nullptr;
        void getir(string &s) override;
        void accept(Visitor_ &visitor) override;
};

class Funparam: public BaseIR
{
    public:
        SYMBOL *symbol=nullptr;
        Type *type=nullptr;
        void getir(string &s) override;
        void accept(Visitor_ &visitor) override;
};
class Funparams: public BaseIR
{
    public:
        vector<Funparam*> funparam_;
        void getir(string &s) override;
        void accept(Visitor_ &visitor) override;
};
class FunBody: public BaseIR
{
    public:
        FunBody(vector<Block*>block):block_(block){}
        vector<Block*> block_;
        void getir(string &s) override;
        void accept(Visitor_ &visitor) override;
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
        void accept(Visitor_ &visitor) override;
};
class Statement: public BaseIR
{
    public:
        enum StmtID
        {
            SyDeID,
            StoreID,
            FuncID,
        };
        Statement(StmtID tid_,SymbolDef *symboldef_,Store *store_):tid(tid_),symboldef(symboldef_),store(store_){}
        StmtID tid;
        SymbolDef *symboldef=nullptr;
        Store *store=nullptr;
        // FunCall *funcall=nullptr;
        void getir(string &s) override;
        void accept(Visitor_ &visitor) override;
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
        EndStatement(esID tid_,Return *ret_):tid(tid_),ret(ret_){}
        esID tid;
        // Branch *branch=nullptr;
        // Jump *jump=nullptr;
        Return *ret=nullptr;
        void getir(string &s) override;
        void accept(Visitor_ &visitor) override;
};

class FunDecl: public BaseIR
{
    public:
        SYMBOL *symbol=nullptr;
        FunDeclparms *fundeclparms=nullptr;
        Type *type=nullptr;
        void getir(string &s) override;
        void accept(Visitor_ &visitor) override;
};

class FunDeclparms: public BaseIR
{
    public:
        vector<Type*>type_;
        void getir(string &s) override;
        void accept(Visitor_ &visitor) override;
};


class InitIR : public BaseIR
{
    public:
        vector<GlobalSymbolDef*>globalsymboldef_;
        vector<FunDef*>fundef_;
        void getir(string &s) override;
        void accept(Visitor_ &visitor) override;
};

class Visitor_
{
    public:
        virtual void Visit(InitIR &ir)=0;
        virtual void Visit(FunDef &ir)=0;
        virtual void Visit(SYMBOL &ir)=0;
        virtual void Visit(FunBody &ir)=0;
        virtual void Visit(Block &ir)=0;
        virtual void Visit(Statement &ir)=0;
        virtual void Visit(SymbolDef &ir)=0;
        virtual void Visit(BinaryExpr &ir)=0;
        virtual void Visit(EndStatement &ir)=0;
        virtual void Visit(Return &ir)=0;
        virtual void Visit(Value &ir)=0;
        virtual void Visit(INT &ir)=0;
        virtual void Visit(Type &ir)=0;
        virtual void Visit(ArrayType &ir)=0;
        virtual void Visit(PointerType &ir)=0;
        virtual void Visit(FunType &ir)=0;
        virtual void Visit(Initializer &ir)=0;
        virtual void Visit(Aggregate &ir)=0;
        virtual void Visit(GlobalSymbolDef &ir)=0;
        virtual void Visit(MemoryDeclaration &ir)=0;
        virtual void Visit(GlobalMemoryDeclaration &ir)=0;
        virtual void Visit(Load &ir)=0;
        virtual void Visit(Store &ir)=0;
        virtual void Visit(GetPointer &ir)=0;
        virtual void Visit(GetElementPointer &ir)=0;
        virtual void Visit(Branch &ir)=0;
        virtual void Visit(Jump &ir)=0;
        virtual void Visit(FunCall &ir)=0;
        virtual void Visit(Funparams &ir)=0;
        virtual void Visit(FunDecl &ir)=0;
        virtual void Visit(FunDeclparms &ir)=0;
};