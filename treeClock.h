#ifndef __TREE_CLOCK_H__
#define __TREE_CLOCK_H__

#include "pagingStrategy.h"

using namespace std;
#include <memory.h>
#include <assert.h>

typedef unsigned char BYTE;

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
        clockLen = _size * childNum / (childNum-1);
        myClock = new BYTE[clockLen];
        memset(myClock, 0, clockLen * sizeof(BYTE));
        offset = _size / (childNum-1);
        strategyName = string("tree(") +
            to_string(childNum) + string(") clock");
    }

    ~treeClock()
    {
        delete [] myClock;
    }

protected:
    int childNum;
    BYTE *myClock;
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
                assert(t>=0 && t<clockLen);
                if(myClock[t]==0)
                {
                    if(start>=offset)
                    {
                        int pos = t - offset;
                        assert(pos>=0 && pos<size);
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
                    myClock[t]=0;
            }
        }
    }

    void updatePosition(int pos)
    {
        int k = pos + offset;
        assert(k>=0 && k<clockLen);
        while(k>0)
        {
            myClock[k]=1;
            k=(k-1)/4;
        }
    }



};

#endif
