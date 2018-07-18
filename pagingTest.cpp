#include "pagingTest.h"

testManager::testManager():
strategySize(0)
{}

testManager::~testManager()
{
    for(auto it=strategyList.begin();it!=strategyList.end();it++)
    {
        pagingStrategy*s = *it;
        delete s;
    }
}

bool testManager::addStrategy(pagingStrategy* s)
{
    return true;
}

bool testManager::readFile(char* name)
{
    return true;
}

void testManager::beginTest()
{

}










