//
// Created by gil on 21/1/20.
//

#define LINE_SEPARATOR "@"

#include <thread>
#include "MatrixBuilder.h"
#include "MyTestClientHandler.h"
#include "BestFirstSearch.h"
#include "DFS.h"
#include "BFS.h"
#include "Astar.h"
#include "FileCacheManager.h"
#include "MyParallelServer.h"
#include "MyClientHandler.h"

#define T pair<int, int>

PairsMatrix* MatrixBuilder::createMatrix(vector<string> matrixToBe) {
    vector<State<T>*> allStates;
    map<T, State<T>*> posAndStateMap;
    map<State<T>*, vector<State<T>*>> stateAndValidNeighborsMap;
    int rowsNum = 0;
    for (int i = 0; i < matrixToBe.size(); ++i) {
        if (matrixToBe[i] == LINE_SEPARATOR) {
            ++rowsNum;
        }
    }
    rowsNum -= 2;
    int colsNum = 0;
    int k = 0;
    while (matrixToBe[k] != LINE_SEPARATOR) {
        ++colsNum;
        ++k;
    }
    vector<string> matrixToBeCopy = matrixToBe;
    for (int i = 0; i < matrixToBeCopy.size(); ++i) {
        if (matrixToBeCopy[i] == LINE_SEPARATOR) {
            matrixToBeCopy.erase(matrixToBeCopy.begin() + i);
        }
    }
    int intMatrix[rowsNum][colsNum];
    for (int curRow = 0; curRow < rowsNum; ++curRow) {
        for (int curCol = 0; curCol < colsNum; ++curCol) {
            intMatrix[curRow][curCol] = stoi(matrixToBeCopy[((curRow * colsNum) + curCol)]);
        }
    }

    cout <<endl;
    for (int curRow = 0; curRow < rowsNum; ++curRow) {
        for (int curCol = 0; curCol < colsNum; ++curCol) {
            cout<< intMatrix[curRow][curCol] <<" ";
        }
        cout <<endl;
    }
    for (int curRow = 0; curRow < rowsNum; ++curRow) {
        for (int curCol = 0; curCol < colsNum; ++curCol) {
            T curPos = T(curRow, curCol);
            State<T>* singleState = new State<T>(curPos);
            singleState->setCost(intMatrix[curRow][curCol]);
            allStates.push_back(singleState);
            posAndStateMap[curPos] = singleState;
        }
    }
    for (int curRow = 0; curRow < rowsNum; ++curRow) {
        for (int curCol = 0; curCol < colsNum; ++curCol) {
            T curPos = T(curRow, curCol);
            State<T>* curState = posAndStateMap.at(curPos);
            T leftPos = T(curRow, curCol-1);
            T rightPos = T(curRow, curCol+1);
            T upPos = T(curRow-1, curCol);
            T downPos = T(curRow+1, curCol);
            vector<T> positions = {rightPos, downPos, leftPos, upPos};
            vector<State<T>*> possibleNeighbors;
            for (int i = 0; i < positions.size(); ++i) {
                if (posAndStateMap.count(positions[i]) && (posAndStateMap.at(positions[i])->getCost() != -1)) {
                    possibleNeighbors.push_back(posAndStateMap.at(positions[i]));
                }
            }
            stateAndValidNeighborsMap[curState] = possibleNeighbors;
        }
    }
    int numOfMatrixLineSeparators = rowsNum;
    int afterMatrixPos = rowsNum*colsNum + numOfMatrixLineSeparators;
    int initialI = stoi(matrixToBe[afterMatrixPos]);
    int initialJ = stoi(matrixToBe[afterMatrixPos + 1]);
    int goalI = stoi(matrixToBe[afterMatrixPos + 3]);
    int goalJ = stoi(matrixToBe[afterMatrixPos + 4]);
    pair<int, int> initialPos = pair<int, int>(initialI, initialJ);
    pair<int, int> goalPos = pair<int, int>(goalI, goalJ);
    State<T>* initialState = posAndStateMap.at(initialPos);
    State<T>* goalState = posAndStateMap.at(goalPos);
    PairsMatrix *resMatrix;
    resMatrix = new PairsMatrix(allStates, initialState, goalState, stateAndValidNeighborsMap);
    return resMatrix;
}
