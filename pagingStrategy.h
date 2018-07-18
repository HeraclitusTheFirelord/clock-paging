#ifndef __PAGING_STRATEGY_H__
#define __PAGING_STRATEGY_H__

#include <memory.h>
#include <assert.h>

class pagingStrategy
{
public:
    int update(int key)   //return LRU position of evicted item, -1 if no item evicted
    {
        int LRUCount=-1;
        bool flag = false;
        int notValidPos=-1;
        for(int i=0;i<size;i++)
        {
            if(notValidPos==-1 && !valid[i])notValidPos=i;
            if(valid[i] && buf[i]==key)  //find the item
            {
                flag = true;
                bufTime[i] = currentTime++;
                updatePosition(i);
                break;
            }
        }
        query++;
        if(!flag)
        {
            miss++;
            int insertPos;
            if(notValidPos!=-1)
            {
                insertPos=notValidPos;
                valid[insertPos]=true;
            }
            else
            {
                insertPos = findEviction();
                LRUCount = getLRUCount(insertPos);
                lruCount[LRUCount]++;
            }
            buf[insertPos] = key;
            bufTime[insertPos] = currentTime++;
        }
        return LRUCount;
    }

    pagingStrategy(int _size)
    {
        size = size;
        buf = new int[size];
        memset(buf, 0, size * sizeof(int));
        valid = new bool[size];
        memset(valid, 0, size * sizeof(bool));
        currentTime = 0;
        bufTime = new unsigned int[size];
        memset(bufTime, 0, size * sizeof(unsigned int));
        query = miss = 0;
        lruCount = new int[size];
        memset(lruCount, 0, size * sizeof(int));
    }

    virtual ~pagingStrategy()
    {
        delete [] buf;
        delete [] bufTime;
        delete [] lruCount;
    }

protected:
    int size;
    int *buf;
    bool *valid;
    unsigned int currentTime;
    unsigned int *bufTime;
    int query;
    int miss;
    int *lruCount;

    int getLRUCount(int pos)
    {
        unsigned int targetTime = bufTime[pos];
        int leastRecentCnt=0;
        for(int i=0;i<size;i++)
        {
            assert(valid[i]);
            if(bufTime[i]<targetTime)
                leastRecentCnt++;
        }
        return leastRecentCnt;
    }

    virtual int findEviction() = 0;
    virtual void updatePosition(int pos) = 0;
};



#endif
