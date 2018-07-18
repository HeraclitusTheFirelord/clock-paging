#ifndef __LRU_H__
#define __LRU_H__

#include "pagingStrategy.h"

class lineClock:public pagingStrategy
{
public:
    lineClock(int _size):pagingStrategy(_size){}
    ~lineClock(){}

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
