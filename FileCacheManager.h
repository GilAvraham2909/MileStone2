//
// Created by yair on 16/1/20.
//

#ifndef MILESTONE2_FILECACHEMANAGER_H
#define MILESTONE2_FILECACHEMANAGER_H

#include <map>
#include <mutex>
#include "CacheManager.h"

class FileCacheManager : public CacheManager<string, string> {
    map<string, string> SolutionByProblemMap;// This is the map of the problems and solutions.
    mutex mutexFileCacheM;
public:
    FileCacheManager();
    virtual bool isThereSolution(string problem);
    virtual string getSolution(string problem);
    virtual void saveSolution(string problem, string solution);
    void writeSolutionsToFile();
    void loadSolutions();
};


#endif //MILESTONE2_FILECACHEMANAGER_H
