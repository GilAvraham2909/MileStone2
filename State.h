//
// Created by yair on 18/1/20.
//

#ifndef MILESTONE2_STATE_H
#define MILESTONE2_STATE_H

#include <map>
#include <cfloat>
using namespace std;

template <class T>
class State {

    T state;
    double cost;
    State<T>* cameFrom;
    double totalCost;
    bool is_visited = false;
    string direction = "";


public:
    State(T state) {
        this->state = state;
        cameFrom = nullptr;
        cost = 0;
        totalCost = cost;
    }

    bool operator==(State<T> state1){
        return (this->state == state1.getState());
    }

    bool operator==(State<T>* state1){
        return (this->state == state1->getState());
    }

    friend bool operator==(State<T>* state1, State<T> state2){
        return (state1->getState() == state2.getState());
    }

    T getState() {
        return state;
    }

    double getCost()  {
        return cost;
    }

    void setCost(double cost) {
        State::cost = cost;
        totalCost = cost;
    }

    State<T>* getCameFrom() {
        return cameFrom;
    }

    void setCameFrom( State<T>* cameFrom) {
        this->cameFrom = cameFrom;
        setTotalCost(cameFrom->getTotalCost() + cost);
    }

    double getTotalCost() {
        return totalCost;
    }

    void setTotalCost(double totalCost) {
        State::totalCost = totalCost;
    }

    bool isVisited() const {
        return is_visited;
    }

    void setVisited(bool visited) {
        is_visited = visited;
    }

    virtual double distanceTo(State<T>* goal) {}

    const std::string &getDirection() const {
        return direction;
    }

    void setDirection(const std::string &direction) {
        State::direction = direction;
    }

    template<class function>
    static string findDirection(State<T> *son, function dirFunction) {
        string direction = dirFunction(son);
        return direction;
    }

    static string directionOfPairs(State<pair<int, int>> *son) {
        if (son->getCameFrom() == nullptr) {
            return "";
        }
        State<pair<int, int>> *father = son->getCameFrom();
        int sonX = son->getState().first;
        int sonY = son->getState().second;
        int fatherX = father->getState().first;
        int fatherY = father->getState().second;
        if (sonX == fatherX) {
            if (fatherY == sonY) {
                son->setDirection(father->getDirection());
                return father->getDirection();
            } else if (fatherY > sonY) {
                son->setDirection("Left");
                return "Left";
            } else if (fatherY < sonY) {
                son->setDirection("Right");
                return "Right";
            }
        } else if (fatherX < sonX) {
            son->setDirection("Down");
            return "Down";
        } else if (fatherX > sonX) {
            son->setDirection("Up");
            return "Up";
        }
    }
};


#endif //MILESTONE2_STATE_H
