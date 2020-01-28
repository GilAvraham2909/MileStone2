//
// Created by yair on 15/1/20.
//


#ifndef MILESTONE2_CLIENTHANDLER_H
#define MILESTONE2_CLIENTHANDLER_H

#include<vector>
#include "ClientHandler.h"
#include "Solver.h"
#include "CacheManager.h"
#include "FileCacheManager.h"
#include "Searchable.h"
#include "MatrixBuilder.h"
#include "PairsMatrix.h"
#include "SearchSolverOA.h"
#include <stdio.h>
#include <stdlib.h>

#include <netdb.h>
#include <unistd.h>
#include <netinet/in.h>

#include <string.h>

#include <sys/socket.h>
#include <thread>
#include <fstream>
#include <algorithm>

#include <iostream>
using namespace std;
class ClientHandler {
public:
    virtual void handleClient(int socket) = 0;
    vector<string> lexer(string lineInput, char c) {
        vector<string> result;
        char delimiter = c;
        string token;
        size_t pos = 0;
        while ((pos = lineInput.find(delimiter)) != string::npos) {
            token = lineInput.substr(0, pos);
            lineInput.erase(0, pos + 1);
            token.erase(remove(token.begin(), token.end(), ' '), token.end());
            token.erase(remove(token.begin(), token.end(), '\n'), token.end());
            result.push_back(token);
        }
        return result;
    }
};


#endif //MILESTONE2_CLIENTHANDLER_H
