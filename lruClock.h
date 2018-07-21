#ifndef __LRU_CLOCK_H__
#define __LRU_CLOCK_H__

#include "pagingStrategy.h"

#include <memory.h>

typedef unsigned char BYTE;

class lruClock:public pagingStrategy
{
public:
    lruClock(int _size, int _lruSize):pagingStrategy(_size)
    {
        assert(_size % _lruSize == 0);
        myClock = new BYTE[_size];
        memset(myClock, 0, _size * sizeof(BYTE)); 
        lruSize = _lruSize;
        groupOffset = _size / _lruSize;
        pointer=new int[_lruSize];
        for(int i=0;i<_lruSize;i++)
        {
            pointer[i]=groupOffset * i;
        }
        strategyName=string("lru(") + to_string(_lruSize) + string(") clock");
    }
    ~lruClock()
    {
        delete [] myClock;
        delete [] pointer;
    }

protected:
    BYTE *myClock;
    int lruSize;
    int groupOffset;
    int *pointer;

    int findEviction()
    {
        int minPos=0;
        unsigned int minTime=bufTime[0];
        for(int i=0;i<size;i++)
        {
            if(minTime>bufTime[i])
            {
                minTime=bufTime[i];
                minPos=i;
            }
        }
        int minPointer=minPos / groupOffset;
        while(true)
        {
            int t=pointer[minPointer];
            pointer[minPointer]=(pointer[minPointer]+1)%groupOffset+
                minPointer*groupOffset;
            if(myClock[t]==1)
            {
                myClock[t]=0;
            }
            else
            {
                myClock[t]=1;
                return t;
            }
        }
    }

    void updatePosition(int pos)
    {
        myClock[pos]=1;
    }
};

#endif
