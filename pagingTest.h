#ifndef __PAGING_H__
#define __PAGING_H__

#include "lru.h"
#include "lineClock.h"
#include "treeClock.h"

#include <stdio.h>
#include <vector>

class testManager
{
public:
    int strategySize;
    std::vector<pagingStrategy*> strategyList;

    testManager();
    ~testManager();

    bool addStrategy(pagingStrategy* s);

    bool readFile(char* name);

    void beginTest();

    
};














#endif
