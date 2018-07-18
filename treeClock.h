#ifndef __LRU_H__
#define __LRU_H__

#include "pagingStrategy.h"

class treeClock:public pagingStrategy
{
public:
    treeClock(int _size):pagingStrategy(_size){}
    ~treeClock(){}

protected:
    int findEviction()
    {
        int minPos=0;
        unsigned int minTime=bufTime[0];
        for(int i=1;i<size;i++)
        {
            if(minTime<bufTime[i])
            {
                minTime=bufTime[i];
                minPos=i;
            }
        }
        return minPos;
    }





};

#endif
