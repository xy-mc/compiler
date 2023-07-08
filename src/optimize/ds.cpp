//本代码做一些数据流分析
#include <cassert>
#include <cstdio>
#include <iostream>
#include <memory>
#include <string>
#include <fstream>
#include <algorithm>
#include <map>
#include "AST/ast.hpp"
#include "IR/ir.hpp"
#include "IR/genIR.hpp"
#include "back/genrs.hpp"
using namespace std;
map<string,int>need_symbol;

InitIR *get_new_dir(InitIR *ir)
{
    InitIR *returnIR=new InitIR();
    returnIR->globalsymboldef_=ir->globalsymboldef_;
    for(auto t:ir->fundef_)
    {
        for(auto t:ir->globalsymboldef_)
        {
            need_symbol[t->symbol->symbol]=2;
        }
        reverse(t->funbody->block_.begin(),t->funbody->block_.end());
        for(auto h:t->funbody->block_)
        {
            EndStatement *ed=h->endstatement;
            switch(ed->tid)
            {
                case EndStatement::branchID:
                {
                    Value *va=ed->branch->value;
                    switch(va->tid)
                    {
                        case Value::SYMBOLID:
                        {
                            SYMBOL *symbol=static_cast<SYMBOL*>(va);
                            need_symbol[symbol->symbol]=1;
                            break;
                        }
                        case Value::INTID:
                        {
                            break;
                        }
                    }
                    break;
                }
                case EndStatement::jumpID:
                {
                    break;
                }
                case EndStatement::returnID:
                {
                    if(ed->ret->value==nullptr)
                        break;
                    Value *va=ed->ret->value;
                    switch(va->tid)
                    {
                        case Value::SYMBOLID:
                        {
                            SYMBOL *symbol=static_cast<SYMBOL*>(va);
                            need_symbol[symbol->symbol]=1;
                            break;
                        }
                        case Value::INTID:
                        {
                            break;
                        }
                    }
                    break;
                }
            }
            //枚举一下endstmt
            vector<Statement*>y=h->statement_;
            reverse(y.begin(),y.end());
            for(auto x:y)
            {
                switch(x->tid)
                {
                    case Statement::SyDeID:
                    {
                        SymbolDef *sy=x->symboldef;
                        switch(sy->tid)
                        {
                            case SymbolDef::MemID:
                            {
                                break;
                            }
                            case SymbolDef::LoadID:
                            {
                                if(need_symbol[sy->symbol->symbol]!=0)
                                {
                                    need_symbol[sy->load->symbol->symbol]=1;
                                }
                                break;
                            }
                            case SymbolDef::GetPID:
                            {
                                if(need_symbol[sy->symbol->symbol]!=0)
                                {
                                    need_symbol[sy->getpointer->symbol->symbol]=1;
                                    switch(sy->getpointer->value->tid)
                                    {
                                        case Value::SYMBOLID:
                                        {
                                            SYMBOL *symbol=static_cast<SYMBOL*>(sy->getpointer->value);
                                            need_symbol[symbol->symbol]=1;
                                            break;
                                        }
                                        case Value::INTID:
                                        {
                                            break;
                                        }
                                    }
                                }
                                break;
                            }
                            case SymbolDef::GetPmID:
                            {
                                if(need_symbol[sy->symbol->symbol]!=0)
                                {
                                    need_symbol[sy->getelemptr->symbol->symbol]=1;
                                    switch(sy->getelemptr->value->tid)
                                    {
                                        case Value::SYMBOLID:
                                        {
                                            SYMBOL *symbol=static_cast<SYMBOL*>(sy->getelemptr->value);
                                            need_symbol[symbol->symbol]=1;
                                            break;
                                        }
                                        case Value::INTID:
                                        {
                                            break;
                                        }
                                    }
                                }
                                break;
                            }
                            case SymbolDef::BiEpID:
                            {
                                if(need_symbol[sy->symbol->symbol]!=0)
                                {
                                    switch(sy->binaryexpr->value1->tid)
                                    {
                                        case Value::SYMBOLID:
                                        {
                                            SYMBOL *symbol=static_cast<SYMBOL*>(sy->binaryexpr->value1);
                                            need_symbol[symbol->symbol]=1;
                                            break;
                                        }
                                        case Value::INTID:
                                        {
                                            break;
                                        }
                                    }
                                    switch(sy->binaryexpr->value2->tid)
                                    {
                                        case Value::SYMBOLID:
                                        {
                                            SYMBOL *symbol=static_cast<SYMBOL*>(sy->binaryexpr->value2);
                                            need_symbol[symbol->symbol]=1;
                                            break;
                                        }
                                        case Value::INTID:
                                        {
                                            break;
                                        }
                                    }
                                }
                                break;
                            }
                            case SymbolDef::FuncID:
                            {
                                for(auto m:sy->funcall->value_)
                                {
                                    switch(m->tid)
                                    {
                                        case Value::SYMBOLID:
                                        {
                                            SYMBOL *symbol=static_cast<SYMBOL*>(m);
                                            need_symbol[symbol->symbol]=1;
                                            break;
                                        }
                                        case Value::INTID:
                                        {
                                            break;
                                        }
                                    }
                                }
                                break;
                            }
                        }
                        break;
                    }
                    case Statement::FuncID:
                    {
                        FunCall *func=x->funcall;
                        for(auto m:func->value_)
                        {
                            switch(m->tid)
                            {
                                case Value::SYMBOLID:
                                {
                                    SYMBOL *symbol=static_cast<SYMBOL*>(m);
                                    need_symbol[symbol->symbol]=1;
                                    break;
                                }
                                case Value::INTID:
                                {
                                    break;
                                }
                            }
                        }
                        break;
                    }
                    case Statement::StoreID://xymc
                    {
                        Store *stor=x->store;
                        if(need_symbol[stor->symbol->symbol]!=0)
                        {
                            switch(stor->value->tid)
                            {
                                case Value::SYMBOLID:
                                {
                                    SYMBOL *symbol=static_cast<SYMBOL*>(stor->value);
                                    need_symbol[symbol->symbol]=1;
                                    break;
                                }
                                case Value::INTID:
                                {
                                    break;
                                }
                            }
                        }
                        if(stor->symbol->symbol[0]=='%')
                        {
                            need_symbol[stor->symbol->symbol]=1;
                            switch(stor->value->tid)
                            {
                                case Value::SYMBOLID:
                                {
                                    SYMBOL *symbol=static_cast<SYMBOL*>(stor->value);
                                    need_symbol[symbol->symbol]=1;
                                    break;
                                }
                                case Value::INTID:
                                {
                                    break;
                                }
                            }
                        }
                        break;
                    }
                }
            }
        }
        vector<Block *>block_now;
        Block *block;
        // reverse(t->funbody->block_.begin(),t->funbody->block_.end());
        for(auto h:t->funbody->block_)
        {
            EndStatement *ed=h->endstatement;
            switch(ed->tid)
            {
                case EndStatement::branchID:
                {
                    Value *va=ed->branch->value;
                    switch(va->tid)
                    {
                        case Value::SYMBOLID:
                        {
                            SYMBOL *symbol=static_cast<SYMBOL*>(va);
                            need_symbol[symbol->symbol]=1;
                            break;
                        }
                        case Value::INTID:
                        {
                            break;
                        }
                    }
                    break;
                }
                case EndStatement::jumpID:
                {
                    break;
                }
                case EndStatement::returnID:
                {
                    if(ed->ret->value==nullptr)
                        break;
                    Value *va=ed->ret->value;
                    switch(va->tid)
                    {
                        case Value::SYMBOLID:
                        {
                            SYMBOL *symbol=static_cast<SYMBOL*>(va);
                            need_symbol[symbol->symbol]=1;
                            break;
                        }
                        case Value::INTID:
                        {
                            break;
                        }
                    }
                    break;
                }
            }
            //枚举一下endstmt
            vector<Statement*>y=h->statement_;
            reverse(y.begin(),y.end());
            vector<Statement *>stmt_;
            for(auto x:y)
            {
                switch(x->tid)
                {
                    case Statement::SyDeID:
                    {
                        SymbolDef *sy=x->symboldef;
                        switch(sy->tid)
                        {
                            case SymbolDef::MemID:
                            {
                                if(need_symbol[sy->symbol->symbol]!=0)
                                    stmt_.push_back(x);
                                break;
                            }
                            case SymbolDef::LoadID:
                            {
                                if(need_symbol[sy->symbol->symbol]!=0)
                                {
                                    need_symbol[sy->load->symbol->symbol]=1;
                                    stmt_.push_back(x);
                                }
                                break;
                            }
                            case SymbolDef::GetPID:
                            {
                                if(need_symbol[sy->symbol->symbol]!=0)
                                {
                                    need_symbol[sy->getpointer->symbol->symbol]=1;
                                    switch(sy->getpointer->value->tid)
                                    {
                                        case Value::SYMBOLID:
                                        {
                                            SYMBOL *symbol=static_cast<SYMBOL*>(sy->getpointer->value);
                                            need_symbol[symbol->symbol]=1;
                                            break;
                                        }
                                        case Value::INTID:
                                        {
                                            break;
                                        }
                                    }
                                    stmt_.push_back(x);
                                }
                                break;
                            }
                            case SymbolDef::GetPmID:
                            {
                                if(need_symbol[sy->symbol->symbol]!=0)
                                {
                                    need_symbol[sy->getelemptr->symbol->symbol]=1;
                                    switch(sy->getelemptr->value->tid)
                                    {
                                        case Value::SYMBOLID:
                                        {
                                            SYMBOL *symbol=static_cast<SYMBOL*>(sy->getelemptr->value);
                                            need_symbol[symbol->symbol]=1;
                                            break;
                                        }
                                        case Value::INTID:
                                        {
                                            break;
                                        }
                                    }
                                    stmt_.push_back(x);
                                }
                                break;
                            }
                            case SymbolDef::BiEpID:
                            {
                                if(need_symbol[sy->symbol->symbol]!=0)
                                {
                                    switch(sy->binaryexpr->value1->tid)
                                    {
                                        case Value::SYMBOLID:
                                        {
                                            SYMBOL *symbol=static_cast<SYMBOL*>(sy->binaryexpr->value1);
                                            need_symbol[symbol->symbol]=1;
                                            break;
                                        }
                                        case Value::INTID:
                                        {
                                            break;
                                        }
                                    }
                                    switch(sy->binaryexpr->value2->tid)
                                    {
                                        case Value::SYMBOLID:
                                        {
                                            SYMBOL *symbol=static_cast<SYMBOL*>(sy->binaryexpr->value2);
                                            need_symbol[symbol->symbol]=1;
                                            break;
                                        }
                                        case Value::INTID:
                                        {
                                            break;
                                        }
                                    }
                                    stmt_.push_back(x);
                                }
                                break;
                            }
                            case SymbolDef::FuncID:
                            {
                                for(auto m:sy->funcall->value_)
                                {
                                    switch(m->tid)
                                    {
                                        case Value::SYMBOLID:
                                        {
                                            SYMBOL *symbol=static_cast<SYMBOL*>(m);
                                            need_symbol[symbol->symbol]=1;
                                            break;
                                        }
                                        case Value::INTID:
                                        {
                                            break;
                                        }
                                    }
                                }
                                stmt_.push_back(x);
                                break;
                            }
                        }
                        break;
                    }
                    case Statement::FuncID:
                    {
                        FunCall *func=x->funcall;
                        for(auto m:func->value_)
                        {
                            switch(m->tid)
                            {
                                case Value::SYMBOLID:
                                {
                                    SYMBOL *symbol=static_cast<SYMBOL*>(m);
                                    need_symbol[symbol->symbol]=1;
                                    break;
                                }
                                case Value::INTID:
                                {
                                    break;
                                }
                            }
                        }
                        stmt_.push_back(x);
                        break;
                    }
                    case Statement::StoreID://xymc
                    {
                        Store *stor=x->store;
                        if(need_symbol[stor->symbol->symbol]!=0)
                        {
                            switch(stor->value->tid)
                            {
                                case Value::SYMBOLID:
                                {
                                    SYMBOL *symbol=static_cast<SYMBOL*>(stor->value);
                                    need_symbol[symbol->symbol]=1;
                                    break;
                                }
                                case Value::INTID:
                                {
                                    break;
                                }
                            }
                            stmt_.push_back(x); 
                        }
                        break;
                    }
                }
            }
            reverse(stmt_.begin(),stmt_.end());
            block=new Block(h->symbol,stmt_,ed);
            stmt_.clear();
            block_now.push_back(block);
        }
        reverse(block_now.begin(),block_now.end());
        FunBody *funbody=new FunBody(block_now);
        FunDef *fundef=new FunDef(t->symbol,t->funparams,t->type,funbody,t->def_num,t->is_call,t->max_num);
        returnIR->fundef_.push_back(fundef);
        block_now.clear();
        need_symbol.clear();
    }
    return returnIR;
}