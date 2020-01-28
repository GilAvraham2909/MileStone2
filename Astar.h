//
// Created by gil on 21/1/20.
//

#ifndef MILESTONE2_ASTAR_H
#define MILESTONE2_ASTAR_H

#include "Searcher.h"
#include <set>
#include "State.h"
#include <algorithm>
#include <unordered_set>
#include <math.h>


template<class T, class Solution>
class Astar : public Searcher<T, Solution> {

    unordered_set<State<T> *> closed;

public:

    Solution search(Searchable<T> *searchable) override {
        typename unordered_set<State<T>*>::iterator itClosed;

        static State<T>* goalState = searchable->getGoalState();
        State<T>* n;
        vector<State<T>*> curPossibleStates;
        vector<State<T>*> resPath;

        class LessThanOfStateCostPlusDist
        {
        public:
            bool operator()(State<T>* a, State<T>* b)
            {
                double uristA = h(a, goalState, distFunction);
                double uristB = h(b, goalState, distFunction);
                return (a->getTotalCost() + uristA) > (b->getTotalCost() + uristB);
            }
        };

        priority_queue<State<T>*, vector<State<T>*>, LessThanOfStateCostPlusDist> openList;
        priority_queue<State<T>*, vector<State<T>*>, LessThanOfStateCostPlusDist> openListCopy;



        openList.push(searchable->getInitialState());
        while (!openList.empty()) {
            n = openList.top();
            openList.pop();
            this->evaluatedNodes++;
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
                openListCopy = openList;
                bool foundInOpen = false;
                while (!openListCopy.empty()) {
                    State<T>* temp = openListCopy.top();
                    openListCopy.pop();
                    if (temp == s) {
                        foundInOpen = true;
                    }
                }
                if ((itClosed == closed.end()) && (!foundInOpen)) {

                    s->setCameFrom(n);
                    openList.push(s);
                } else {
                    if ((n->getTotalCost() + s->getCost()) < s->getTotalCost()) {
                        if (!foundInOpen) {
                            openList.push(s);
                        } else {
                            s->setCameFrom(n);
                            double newTotalCost = (n->getTotalCost() + s->getCost());
                            s->setTotalCost(newTotalCost);
                            State<T>* temp = s;
                            vector<State<T>*> tempQ;
                            int i=0;
                            State<T>* state;
                            int openSize = (int) openList.size();
                            while(i < openSize)
                            {
                                if (openList.top() == s) {
                                    break;
                                }
                                tempQ.push_back(openList.top());
                                openList.pop();
                                ++i;
                            }
                            openList.pop();
                            int tempQsize = (int) tempQ.size();
                            for (int m = 0;  m < tempQsize; ++m) {
                                openList.push(tempQ[m]);
                            }
                            openList.push(temp);
                        }
                    }
                }
            }
        }
        State<T> *initialState = searchable->getInitialState();
        cout << "total cost DFS: " << initialState->getTotalCost() << endl;
        cout << "numOfNodes: " << this->evaluatedNodes << endl;
    }

    static double distFunction(State<pair<int, int>> *s, State<pair<int, int>> *goal) {
        int sX = s->getState().first;
        int sY = s->getState().second;
        int goalX = goal->getState().first;
        int goalY = goal->getState().second;
        double distanceX = pow(sX - goalX, 2);
        double distanceY = pow(sY - goalY, 2);
        double calcDistance = sqrt(distanceX + distanceY);
        return calcDistance;
    }
    template<class function>
    static double h(State<T> *s, State<T> *goal, function distFunction) {
        double dist = distFunction(s, goal);
        return dist;
    }
};


#endif //MILESTONE2_ASTAR_H
