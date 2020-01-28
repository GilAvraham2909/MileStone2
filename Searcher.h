//
// Created by yair on 17/1/20.
//

#ifndef MILESTONE2_SEARCHER_H
#define MILESTONE2_SEARCHER_H

#include "SearcherInterface.h"
#include "Searchable.h"
#include <queue>
template <class T, class Solution>
class Searcher : public SearcherInterface<T, Solution> {
public:
    Searcher(){
        evaluatedNodes = 0;
    }
    int getOpenListSize() {
        return (int) openList.size();
    }

    int getNumberOfNodesEvaluated() {
        return evaluatedNodes;
    }

    virtual Solution search(Searchable<T>* searchable) = 0;

protected:

    class LessThanOfStateCost
    {
    public:
        bool operator()(State<T>* lhs, State<T>* rhs)
        {
            return lhs->getTotalCost() > rhs->getTotalCost();
        }
    };
    priority_queue<State<T>*, vector<State<T>*>, LessThanOfStateCost> openList;
    priority_queue<State<T>*, vector<State<T>*>, LessThanOfStateCost> openListCopy;
    int evaluatedNodes;
    virtual State<T>* popOpenList() {
        evaluatedNodes++;
        auto temp = openList.top();
        openList.pop();
        return temp;
    }

};


#endif //MILESTONE2_SEARCHER_H
