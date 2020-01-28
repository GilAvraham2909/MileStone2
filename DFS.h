//
// Created by gil on 21/1/20.
//


#ifndef MILESTONE2_DFS_H
#define MILESTONE2_DFS_H

#include "State.h"
#include "Searcher.h"

template<class T, class Solution>
class DFS : public Searcher<T, Solution> {

public:
    int getNumberOfNodesEvaluated() override {
        return this->evaluatedNodes;
    }

    Solution search(Searchable<T> *searchable) override {
        State<T> *goalState = searchable->getGoalState();
        State<T> *initialState = searchable->getInitialState();
        string strPath = DFSUtil(initialState, goalState, searchable);

        return strPath;
    }

    string DFSUtil(State<T> *initialState, State<T> *goalState,Searchable<T> *searchable) {
        initialState->setVisited(true);
        ++this->evaluatedNodes;
        if (initialState == goalState) {
            cout << initialState->getCost() << endl;
            cout << "total cost DFS: " << initialState->getTotalCost() << endl;
            cout << "numOfNodes: " << getNumberOfNodesEvaluated() << endl;
            vector<State<T> *> resPath;
            string strPath;
            State<T> *n = initialState;
            resPath.push_back(n);
            while (n->getCameFrom() != nullptr) {
                State<T> *temp = n->getCameFrom();
                resPath.push_back(temp);
                n = temp;
            }
            reverse(resPath.begin(), resPath.end());
            int resPathSize = (int) resPath.size();
            for (int a = 0; a < resPathSize; ++a) {
                strPath += resPath[a]->findDirection(resPath[a],
                                                     resPath[a]->directionOfPairs);
                if ((a != (resPathSize - 1)) && (a != 0)) {
                    strPath += ", ";
                }
            }
            return strPath;
        }
        cout << initialState->getCost() << " ";
        vector<State<T> *> curPossibleStates;
        curPossibleStates = searchable->getAllPossibleStates(initialState);
        int possibleStatesSize = (int) curPossibleStates.size();
        for (int i = 0; i < possibleStatesSize; ++i) {
            if (!(curPossibleStates[i]->isVisited())) {
                curPossibleStates[i]->setCameFrom(initialState);
                return DFSUtil(curPossibleStates[i], goalState, searchable);
            }
        }
    }

};
#endif //MILESTONE2_DFS_H
