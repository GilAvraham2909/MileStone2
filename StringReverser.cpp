//
// Created by yair on 17/1/20.
//

#include "StringReverser.h"
#include <algorithm>


string StringReverser::solve(string s) {
    reverse(s.begin(), s.end());
    return s;
}
