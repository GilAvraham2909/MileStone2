//
// Created by gil on 21/1/20.
//


#include "PairsMatrix.h"

PairsMatrix::PairsMatrix(const vector<State<pair<int, int>> *> &allStates,
                         State<pair<int, int>> *initialState,
                         State<pair<int, int>> *goalState,
                         const map<State<pair<int, int>> *, vector<State<pair<int, int>> *>> &stateAndValidNeighborsMap)
        : allStates(allStates), initialState(initialState),
          goalState(goalState),
          stateAndValidNeighborsMap(stateAndValidNeighborsMap) {}

State<pair<int, int>> *PairsMatrix::getInitialState() {
    return initialState;
}

State<pair<int, int>> *PairsMatrix::getGoalState() {
    return goalState;
}

vector<State<pair<int, int>> *>
PairsMatrix::getAllPossibleStates(State<pair<int, int>> *state) {
    return stateAndValidNeighborsMap.at(state);
}

const vector<State<pair<int, int>> *> &PairsMatrix::getAllStates() const {
    return allStates;
}

void
PairsMatrix::setAllStates(const vector<State<pair<int, int>> *> &allStates) {
    PairsMatrix::allStates = allStates;
}

void PairsMatrix::setInitialState(State<pair<int, int>> *initialState) {
    PairsMatrix::initialState = initialState;
}

void PairsMatrix::setGoalState(State<pair<int, int>> *goalState) {
    PairsMatrix::goalState = goalState;
}

const map<State<pair<int, int>> *, vector<State<pair<int, int>> *>> &
PairsMatrix::getStateAndValidNeighborsMap() const {
    return stateAndValidNeighborsMap;
}

void PairsMatrix::setStateAndValidNeighborsMap(
        const map<State<pair<int, int>> *, vector<State<pair<int, int>> *>> &stateAndValidNeighborsMap) {
    PairsMatrix::stateAndValidNeighborsMap = stateAndValidNeighborsMap;
}
