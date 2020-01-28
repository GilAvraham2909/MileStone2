//
// Created by gil on 21/1/20.
//

#ifndef MILESTONE2_BESTFIRSTSEARCH_H
#define MILESTONE2_BESTFIRSTSEARCH_H

#include "Searcher.h"
#include <set>
#include "State.h"
#include <algorithm>
#include <unordered_set>



template <class T, class Solution>
class BestFirstSearch : public Searcher<T, Solution> {

    unordered_set<State<T>*> closed;

public:

    Solution search(Searchable<T>* searchable) override {
        typename unordered_set<State<T>*>::iterator itClosed;

        State<T>* goalState = searchable->getGoalState();
        State<T>* n;
        vector<State<T>*> curPossibleStates;
        vector<State<T>*> resPath;
        this->openList.push(searchable->getInitialState());
        while (!this->openList.empty()) {
            n = this->popOpenList();
            closed.insert(n);
            if (n == goalState) {
                string strPath;
                resPath.push_back(n);
                while (n->getCameFrom() != nullptr) {
                    State<T>* temp = n->getCameFrom();
                    resPath.push_back(temp);
                    n = temp;
                }
                reverse(resPath.begin(), resPath.end());
                int resPathSize = (int) resPath.size();
                for (int a = 0; a < resPathSize; ++a) {
                    strPath += resPath[a]->findDirection(resPath[a], resPath[a]->directionOfPairs);
                    if ((a != (resPathSize -1)) && (a != 0)) {
                        strPath += ", ";
                    }
                }
                return strPath;
            }

            curPossibleStates = searchable->getAllPossibleStates(n);
            if (curPossibleStates.empty()) {
                continue;
            }

            int possibleStatesSize = (int) curPossibleStates.size();
            for (int l = 0; l< possibleStatesSize; ++l) {
                State<T>* s = curPossibleStates[l];
                itClosed = closed.find(s);
                if (itClosed != closed.end()) {
                    continue;
                }
                this->openListCopy = this->openList;
                bool foundInOpen = false;
                while (!this->openListCopy.empty()) {
                    State<T>* temp = this->openListCopy.top();
                    this->openListCopy.pop();
                    if (temp == s) {
                        foundInOpen = true;
                    }
                }
                if ((itClosed == closed.end()) && (!foundInOpen)) {
                    s->setCameFrom(n);
                    this->openList.push(s);
                } else {
                    if ((n->getTotalCost() + s->getCost()) < s->getTotalCost()) {

                        if (!foundInOpen) {
                            this->openList.push(s);
                        } else {
                            s->setCameFrom(n);
                            double newTotalCost = (n->getTotalCost() + s->getCost());
                            s->setTotalCost(newTotalCost);
                            State<T>* temp = s;
                            vector<State<T>*> tempQ;
                            int i=0;
                            State<T>* state;
                            int openSize = (int) this->openList.size();
                            while(i < openSize)
                            {
                                if (this->openList.top() == s) {
                                    break;
                                }
                                tempQ.push_back(this->openList.top());
                                this->openList.pop();
                                ++i;
                            }
                            this->openList.pop();
                            int tempQsize = (int) tempQ.size();
                            for (int m = 0;  m < tempQsize; ++m) {
                                this->openList.push(tempQ[m]);
                            }
                            this->openList.push(temp);
                        }
                    }
                }
            }
        }
    }
};


#endif //MILESTONE2_BESTFIRSTSEARCH_H