#ifndef __LINE_CLOCK_H__
#define __LINE_CLOCK_H__

#include "pagingStrategy.h"

#include <memory.h>

typedef unsigned char BYTE;

class lineClock:public pagingStrategy
{
public:
    lineClock(int _size):pagingStrategy(_size)
    {
        myClock = new BYTE[_size];
        memset(myClock, 0, _size * sizeof(BYTE)); 
        pointer=0;
        strategyName="line clock";
    }
    ~lineClock()
    {
        delete [] myClock;
    }

protected:
    BYTE *myClock;
    int pointer;

    int findEviction()
    {
        while(true)
        {
            int t=pointer;
            pointer=(pointer+1)%size;
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
