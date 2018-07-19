#ifndef __PAGING_STRATEGY_H__
#define __PAGING_STRATEGY_H__

using namespace std;
#include <memory.h>
#include <assert.h>
#include <iostream>
#include <string>

class pagingStrategy
{
public:
    pagingStrategy&update(int key)   //return LRU position of evicted item, -1 if no item evicted
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
            //cout<<"evict:"<<buf[insertPos]<<" "<<key<<endl;
            buf[insertPos] = key;
            bufTime[insertPos] = currentTime++;
            updatePosition(insertPos);
        }
        return *this;
    }

    pagingStrategy(int _size)
    {
        size = _size;
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

    void log()
    {
        cout<<"*******************"<<endl;
        cout<<strategyName<<" behavior:"<<endl;
        cout<<"query: "<<query<<", miss: "<<miss<<endl;
        int span=size;//int span = 512<size?512:size;
        for(int i=0;i<span;i++)
            cout<<lruCount[i]<<" ";
        cout<<endl;
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
    string strategyName;

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
