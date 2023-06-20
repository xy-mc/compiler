//本代码做一些控制流分析
#include <cassert>
#include <cstdio>
#include <iostream>
#include <memory>
#include <string>
#include <fstream>
#include "AST/ast.hpp"
#include "IR/ir.hpp"
#include "IR/genIR.hpp"
#include "back/genrs.hpp"
using namespace std;
map<string,bool> need_block;//非死代码块置为1

void get_need_block(InitIR *ir,InitIR *rir)
{
    for(auto t:ir->fundef_)
    {
        vector<Block *>block_now;
        for(auto h:t->funbody->block_)
        {
            if(need_block[h->symbol->symbol])
                block_now.push_back(h);
        }
        FunBody *funbody=new FunBody(block_now);
        FunDef *fundef=new FunDef(t->symbol,t->funparams,t->type,funbody,t->def_num,t->is_call,t->max_num);
        rir->fundef_.push_back(fundef);
        block_now.clear();
    }
}

InitIR * get_new_cir(InitIR *ir)
{
    InitIR *returnIR=new InitIR();
    returnIR->globalsymboldef_=ir->globalsymboldef_;
    for(auto t:ir->fundef_)
    {
        bool flag=1;
        for(auto h:t->funbody->block_)
        {
            if(flag)
            {
                need_block[h->symbol->symbol]=1;
                flag=0;
            }
            else
            {
                if(need_block[h->symbol->symbol]==0)
                continue;
            }
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
                            need_block[ed->branch->symbol1->symbol]=1;
                            need_block[ed->branch->symbol2->symbol]=1;
                            break;
                        }
                        case Value::INTID:
                        {
                            INT *i32_=static_cast<INT*>(va);
                            if(i32_->int_const!=0)
                            {
                                need_block[ed->branch->symbol1->symbol]=1;
                                Jump *jump=new Jump(ed->branch->symbol1);
                                EndStatement *endstmt=new EndStatement(EndStatement::jumpID,nullptr,jump,nullptr);
                                h->endstatement=endstmt;
                            }
                            else
                            {
                                need_block[ed->branch->symbol2->symbol]=1;
                                Jump *jump=new Jump(ed->branch->symbol2);
                                EndStatement *endstmt=new EndStatement(EndStatement::jumpID,nullptr,jump,nullptr);
                                h->endstatement=endstmt;
                            }
                            break;
                        }
                    }
                    break;
                }
                case EndStatement::jumpID:
                {
                    need_block[ed->jump->symbol->symbol]=1;
                    break;
                }
                case EndStatement::returnID:
                {
                    break;
                }
            }
        }
    }
    get_need_block(ir,returnIR);
    return returnIR;
}
