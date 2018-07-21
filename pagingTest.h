#ifndef __PAGING_H__
#define __PAGING_H__

#include "lru.h"
#include "lineClock.h"
#include "treeClock.h"
#include "lruClock.h"

using namespace std;
#include <stdio.h>
#include <vector>
#include <fstream>

class testManager
{
public:
    int strategySize;
    vector<pagingStrategy*> strategyList;
    ifstream fin;        
    char readBuf[105];

    testManager();
    ~testManager();

    bool addStrategy(pagingStrategy* s);

    int read(); 
    
    void beginTest(int updateNum);

    void log(bool showDetail=false);
};














#endif
