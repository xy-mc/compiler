//本代码实现活跃变量分析
#include <cassert>
#include <cstdio>
#include <iostream>
#include <memory>
#include <string>
#include <fstream>
#include <map>
#include "AST/ast.hpp"
#include "IR/ir.hpp"
#include "IR/genIR.hpp"
#include "back/genrs.hpp"
#include "live.hpp"
#include <algorithm>
#include <vector>

void live_analyse(Block *block)
{
    int i=0;
    vector<Statement*>y=block->statement_;
    reverse(y.begin(),y.end());
    for(auto x:y)
    {
        i++;
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
                        assign_live(sy->symbol->symbol,i);
                        break;
                    }
                    case SymbolDef::GetPID:
                    {
                        assign_live(sy->getpointer->symbol->symbol,i);
                        switch(sy->getpointer->value->tid)
                        {
                            case Value::SYMBOLID:
                            {
                                SYMBOL *symbol=static_cast<SYMBOL*>(sy->getpointer->value);
                                assign_live(symbol->symbol,i);
                                break;
                            }
                            case Value::INTID:
                            {
                                break;
                            }
                        }
                        break;
                    }
                    case SymbolDef::GetPmID:
                    {
                        assign_live(sy->getelemptr->symbol->symbol,i);
                        switch(sy->getelemptr->value->tid)
                        {
                            case Value::SYMBOLID:
                            {
                                SYMBOL *symbol=static_cast<SYMBOL*>(sy->getelemptr->value);
                                assign_live(symbol->symbol,i);
                                break;
                            }
                            case Value::INTID:
                            {
                                break;
                            }
                        }
                        break;
                    }
                    case SymbolDef::BiEpID:
                    {
                        switch(sy->binaryexpr->value1->tid)
                        {
                            case Value::SYMBOLID:
                            {
                                SYMBOL *symbol=static_cast<SYMBOL*>(sy->binaryexpr->value1);
                                assign_live(symbol->symbol,i);
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
                                assign_live(symbol->symbol,i);
                                break;
                            }
                            case Value::INTID:
                            {
                                break;
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
                                    assign_live(symbol->symbol,i);
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
                            assign_live(symbol->symbol,i);
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
            case Statement::StoreID:
            {
                Store *stor=x->store;
                switch(stor->value->tid)
                {
                    case Value::SYMBOLID:
                    {
                        SYMBOL *symbol=static_cast<SYMBOL*>(stor->value);
                        assign_live(symbol->symbol,i);
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
    }
}