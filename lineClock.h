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
        strategyName="line clock";
    }
    ~lineClock()
    {
        delete [] myClock;
    }

protected:
    BYTE *myClock;

    int findEviction()
    {
        int i=0;
        while(true)
        {
            if(myClock[i]==1)
            {
                myClock[i]=0;
            }
            else
            {
                myClock[i]=1;
                return i;
            }
            i=(i+1)%size;
        }
    }

    void updatePosition(int pos)
    {
        myClock[pos]=1;
    }



};

#endif
