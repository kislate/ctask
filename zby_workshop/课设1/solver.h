#ifndef SOLVER_H
#define SOLVER_H

#include "cnfparser.h"

// DPLL主函数，返回1为SAT，0为UNSAT
int DPLL(Formula *F, int *assign, int var_num);

#endif