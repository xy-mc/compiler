//本代码做一些数据流分析
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
map<string,bool>need_symbol;

InitIR *get_new_sir(InitIR *ir)
{
    InitIR *returnIR;
    returnIR->globalsymboldef_=ir->globalsymboldef_;
    for(auto t:ir->globalsymboldef_)
    {
        need_symbol[t->symbol->symbol]=1;
    }
    for(auto t:ir->fundef_)
    {
        for(auto h:t->funbody->block_)
        {
            //枚举一下endstmt
            auto y=h->statement_;
            for(auto x=y.rbegin();x!=y.rend();x++)
            {

            }
        }
    }
}