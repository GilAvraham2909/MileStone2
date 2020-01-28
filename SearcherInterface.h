//
// Created by yair on 17/1/20.
//

#ifndef MILESTONE2_SEARCHERINTERFACE_H
#define MILESTONE2_SEARCHERINTERFACE_H

#include <iostream>
#include "Searchable.h"
using namespace std;

template <class T, class Solution>
class SearcherInterface {
public:
    virtual Solution search(Searchable<T>* searchable) = 0;
    virtual int getNumberOfNodesEvaluated() = 0;
};


#endif //MILESTONE2_SEARCHERINTERFACE_H
