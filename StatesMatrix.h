//
// Created by gil on 21/1/20.
//

#ifndef MILESTONE2_STATESMATRIX_H
#define MILESTONE2_STATESMATRIX_H

#include "State.h"
#include "Searchable.h"
#include <map>
#include <list>
using  namespace std;
template <class T>
class StatesMatrix : public Searchable<T> {
    list<State<T>*> allStates;
    State<T>* initialState;
    State<T>* goalState;
    struct cmpByState {
        bool operator()(State<T>* a, State<T>* b) {
            return a->getState() < b->getState();
        }
    };
    typedef map<State<T>*, list<State<T>*>, cmpByState> state_map;
    state_map myMap;

public:
    StatesMatrix(list<State<T> *> &allStates1, State<T> *initialState1,State<T> *goalState1,state_map& myMap1) {
        allStates = allStates1;
        initialState = initialState1;
        goalState = goalState1;
        myMap = myMap1;
    }

    virtual State<T>* getInitialState() {
        return initialState;
    }

    virtual State<T>* getGoalState() {
        return goalState;
    }

    virtual list<State<T>*> getAllPossibleStates(State<T>* state) {
        if (myMap.count(state)) {
            list<State<T>*> res = myMap[state];
            return res;
        } else {
            return list<State<T>*>();
        }
    }


    void setGoalState(State<T> *goalstat) {
        goalState = goalstat;
    }

    map<State<T> *, list<State<T> *>> &getState_map() {
        return this->state_map;
    }

    void setStateAndValidNeighborsMap(map<State<T> *, list<State<T> *>> &map) {
        this->state_map = map;
    }
    const list<State<T> *> &getAllStates() const {
        return allStates;
    }

    void setAllStates(const list<State<T> *> &allSt) {
        allStates = allSt;
    }

    void setInitialState(State<T> *initialS) {
        initialState = initialS;
    }

};


#endif //MILESTONE2_STATESMATRIX_H
