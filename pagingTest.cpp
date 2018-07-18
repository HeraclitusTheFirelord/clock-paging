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

}

bool testManager::readFile(char* name)
{

}

void testManager::beginTest()
{

}










