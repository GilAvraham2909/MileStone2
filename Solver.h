//
// Created by yair on 18/1/20.
//
#ifndef MILESTONE2_SOLVER_H
#define MILESTONE2_SOLVER_H

#include <iostream>
using namespace std;

template <class Problem, class Solution>
class Solver {
public:
    virtual Solution solve(Problem problem) = 0;
};


#endif //MILESTONE2_SOLVER_H
