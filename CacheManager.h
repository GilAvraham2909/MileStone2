//
// Created by yair on 15/1/20.
//


#ifndef MILESTONE2_CACHEMANAGER_H
#define MILESTONE2_CACHEMANAGER_H

#include <iostream>
using namespace std;

template <class Problem, class Solution>
class CacheManager {
public:
    virtual bool isThereSolution(Problem) = 0;

    virtual Solution getSolution(Problem) = 0;

    virtual void saveSolution(Problem, Solution) = 0;
};


#endif //MILESTONE2_CACHEMANAGER_H
