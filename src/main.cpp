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
#include "optimize/cf.hpp"
using namespace std;

// 声明 lexer 的输入, 以及 parser 函数
// 为什么不引用 sysy.tab.hpp 呢? 因为首先里面没有 yyin 的定义
// 其次, 因为这个文件不是我们自己写的, 而是被 Bison 生成出来的
// 你的代码编辑器/IDE 很可能找不到这个文件, 然后会给你报错 (虽然编译不会出错)
// 看起来会很烦人, 于是干脆采用这种看起来 dirty 但实际很有效的手段
extern FILE *yyin;
extern int yyparse(unique_ptr<BaseAST> &ast);

int main(int argc, const char *argv[]) {
  // 解析命令行参数. 测试脚本/评测平台要求你的编译器能接收如下参数:
  // compiler 模式 输入文件 -o 输出文件
  assert(argc == 5);
  auto mode = std::string(argv[1]);
  auto input = argv[2];
  auto output = argv[4];

  // 打开输入文件, 并且指定 lexer 在解析的时候读取这个文件
  yyin = fopen(input, "r");
  assert(yyin);

  // 调用 parser 函数, parser 函数会进一步调用 lexer 解析输入文件的
  unique_ptr<BaseAST> ast;
  auto ret = yyparse(ast);
  assert(!ret);

  // 输出解析得到的 AST, 其实就是个字符串
  string s="decl @getint(): i32\n"
          "decl @getch(): i32\n"
          "decl @getarray(*i32): i32\n"
          "decl @putint(i32)\n"
          "decl @putch(i32)\n"
          "decl @putarray(i32, *i32)\n"
          "decl @starttime()\n"
          "decl @stoptime()\n";
  GenIR genir;
  ast->accept(genir);
  GenRS genrs;
  genir.initir=get_new_cir(genir.initir);
  if(mode=="-koopa")
    genir.initir->getir(s);
  else if(mode=="-riscv")
  {
    genir.initir->accept(genrs);
    s=genrs.rs;
  }
  else if(mode=="-perf")
  {
    genir.initir->accept(genrs);
    s=genrs.rs;
  }
  std::ofstream ofs(output);
  if (ofs.is_open()) 
  {  
      ofs << s;
      // 关闭文件输出流
      ofs.close();
  } 
  else 
  {
        std::cout << "无法打开文件" << std::endl;
  }
  return 0;
}
