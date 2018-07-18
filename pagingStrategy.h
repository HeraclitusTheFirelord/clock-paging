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
                break;
            }
        }
        query++;
        if(!flag)
        {
            miss++;
            int evictPos;
            if(notValidPos!=-1)
                evictPos=notValidPos;
            else
            {
                evictPos = findEviction();
                LRUCount = getLRUCount(evictPos);
                }
            buf[evictPos] = key;
            bufTime[evictPos] = currentTime++;
        }
        return LRUCount;
    }

    void reset()
    {
        memset(buf, 0, size * sizeof(int));
        memset(valid, 0, size * sizeof(bool));
        currentTime = 0;
        memset(buf, 0, size * sizeof(unsigned int));
        query = miss = 0;
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
        memset(buf, 0, size * sizeof(unsigned int));
        query = miss = 0;
    }

    ~pagingStrategy()
    {
        delete [] buf;
        delete [] bufTime;
    }

protected:
    int size;
    int *buf;
    bool *valid;
    unsigned int currentTime;
    unsigned int *bufTime;
    int query;
    int miss;

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
};



#endif
