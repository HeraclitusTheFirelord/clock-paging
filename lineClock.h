#ifndef __LRU_H__
#define __LRU_H__

#include "pagingStrategy.h"

class lineClock:public pagingStrategy
{
public:
    lineClock(int _size):pagingStrategy(_size)
    {
        clock = new BYTE[_size];
        memset(clock, 0, _size * sizeof(BYTE)); 
    }
    ~lineClock()
    {
        delete [] clock;
    }

protected:
    BYTE *clock;

    int findEviction()
    {
        int i=0;
        while(true)
        {
            if(clock[i]==1)
            {
                clock[i]=0;
            }
            else
            {
                clock[i]=1;
                return i;
            }
            i=(i+1)%size;
        }
    }

    void updatePosition(int pos)
    {
        clock[pos]=1;
    }



};

#endif
