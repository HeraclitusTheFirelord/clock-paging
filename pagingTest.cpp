#include "pagingTest.h"

testManager::testManager():
strategySize(0)
{
    fin = ifstream("dat/0.dat",ios::in|ios::binary);
}

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
    strategySize++;
    strategyList.push_back(s);
    return true;
}

int testManager::read()
{
    fin.read(readBuf,13);
    readBuf[4]='\0';
    int tmp=0;
    for(int i=0;i<4;i++)tmp=tmp*256+(int)readBuf[i];
    return tmp;
}

void testManager::beginTest(int updateNum)
{
    while(updateNum--)
    {
        int n=read();
        for(auto it=strategyList.begin();it!=strategyList.end();it++)
        {
            (*it)->update(n);
        }
    }
}

void testManager::log(bool showDetail=false)
{
    for(auto it=strategyList.begin();it!=strategyList.end();it++)
    {
        (*it)->log(showDetail);
    }
}








