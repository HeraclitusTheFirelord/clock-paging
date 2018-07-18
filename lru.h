#ifndef __LRU_H__
#define __LRU_H__

#include "pagingStrategy.h"

class lru:public pagingStrategy
{
public:
    lru(int _size):pagingStrategy(_size){}
    ~lru(){}

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

    void updatePosition(int pos){}
};

#endif
