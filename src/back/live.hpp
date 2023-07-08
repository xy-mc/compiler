#pragma once
#include "IR/ir.hpp"
#include <map>
extern map<string,int>live_line;//所用符号在块中从后往前数的行数
void live_analyse(Block *block);