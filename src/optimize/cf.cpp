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
void get_new_cir(InitIR *ir)
{
    for(auto t:ir->fundef_)
    {

    }
}