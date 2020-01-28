//
// Created by yair on 17/1/20.
//
#ifndef MILESTONE2_SEARCHABLE_H
#define MILESTONE2_SEARCHABLE_H

#include <iostream>
#include <list>
#include "State.h"
#include <vector>
using namespace std;
template <class T>
class Searchable {
public:
    virtual State<T>* getInitialState() = 0;
    virtual State<T>* getGoalState() = 0;
    virtual vector<State<T>*> getAllPossibleStates(State<T>*) = 0;
};


#endif //MILESTONE2_SEARCHABLE_H
