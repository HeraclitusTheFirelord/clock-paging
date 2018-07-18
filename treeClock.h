#ifndef __LRU_H__
#define __LRU_H__

#include "pagingStrategy.h"

#include "assert.h"

class treeClock:public pagingStrategy
{
public:
    treeClock(int _size, int _childNum):pagingStrategy(_size)
    {
        int tmp=_size;
        while(tmp % _childNum == 0)
            tmp = tmp / _childNum;
        assert(tmp==1);
        
        childNum = _childNum;
        clock = new BYTE[int(childNum / (childNum-1) * _size)];
        clockLen = int(childNum / (childNum-1);
        offset = _size / 3;
    }

    ~treeClock()
    {
        delete [] clock;
    }

protected:
    int childNum;
    BYTE *clock;
    int clockLen;
    int offset;

    int findEviction()
    {
        int k=0;
        while(true)
        {
            int start=4*k+1, end=4*k+4;
            for(int t=start;t<=end;t++)
            {
                if(clock[t]==0)
                {
                    if(start>=offset)
                    {
                        int pos = t - offset;
                        updatePosition(pos);
                        return pos; //find
                    }
                    else
                    {
                        k=t; //go to the next layer
                        break;
                    }
                }
                else
                    clock[k]=0;
            }
        }
    }

    void updatePosition(int pos)
    {
        int k = pos + offset;
        while(k>0)
        {
            clock[k]=1;
            k=(k-1)/4;
        }
    }



};

#endif
