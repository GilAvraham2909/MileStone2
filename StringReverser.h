//
// Created by yair on 17/1/20.
//

#ifndef MILESTONE2_STRINGREVERSER_H
#define MILESTONE2_STRINGREVERSER_H

#include "Solver.h"

class StringReverser : public Solver<string, string> {
public:
    virtual string solve(string s);
};
#endif //MILESTONE2_STRINGREVERSER_H
