#ifndef __TREE_LRU_H__
#define __TREE_LRU_H__

#include "pagingStrategy.h"

using namespace std;
#include <memory.h>
#include <assert.h>
#include <vector>

typedef unsigned char BYTE;

class treeLru:public pagingStrategy
{
public:
    treeLru(int _size, vector<int>&_childNum):pagingStrategy(_size)
    {
        int tmp = _size;
        auto iter = _childNum.begin();
        while(iter!=_childNum.end() && tmp%(*iter)==0)
        {
            tmp = tmp / (*iter);
            iter++;
        }
        assert(tmp==1 && iter==_childNum.end());
        
        layerNum = _childNum.size();
        childNum = new int[layerNum];
        memset(childNum, 0, layerNum * sizeof(int));
        offset = new int[layerNum];
        memset(offset, 0, layerNum * sizeof(int));
        timeSize=0;
        int leafSize=1;
        iter=_childNum.begin();
        for(int i=0;i<layerNum;i++,iter++)
        {
            timeSize+=leafSize;
            childNum[i]=*iter;
            offset[i]=timeSize;
            leafSize*=childNum[i];
        }
        timeTree = new unsigned int[timeSize];
        memset(timeTree, 0, timeSize * sizeof(unsigned int));
        strategyName = "tree(";
        for(int i=0;i<layerNum;i++)
        {
            if(i==0)
            {
                strategyName += to_string(childNum[i]);
                continue;
            }
            strategyName += ", " + to_string(childNum[i]);
            
        }
        strategyName += ") lru";
    }

    ~treeLru()
    {
        delete [] childNum;
        delete [] offset;
        delete [] timeTree;
    }

protected:
    int layerNum;
    int *childNum;
    int *offset;
    int timeSize;
    unsigned int *timeTree;

    int findEviction()
    {
        int curIndex=0;
        int curLayer=0;
        int curOffset=0;
        while(true)
        {
            int starts=curOffset+offset[curLayer];
            int ends=curOffset+offset[curLayer]+childNum[curLayer]-1;
            if(starts<timeSize)
            {
                assert(starts>=0 && ends<timeSize);
                int minPos=starts;
                unsigned int minTime=timeTree[starts];
                for(int i=starts+1;i<=ends;i++)
                {
                    if(minTime>timeTree[i])
                    {
                        minTime=timeTree[i];
                        minPos=i;
                    }
                }
                curIndex=(minPos-offset[curLayer])%childNum[curLayer];
                assert(curIndex>=0 && curIndex<childNum[curLayer]);
                curLayer++;
                curOffset=(curOffset+curIndex)*childNum[curLayer];
            }
            else
            {
                starts-=timeSize;
                ends-=timeSize;
                assert(starts>=0 && ends<size);
                int minPos=starts;
                unsigned int minTime=bufTime[starts];
                for(int i=starts+1;i<=ends;i++)
                {
                    if(minTime>bufTime[i])
                    {
                        minTime=bufTime[i];
                        minPos=i;
                    }
                }
                return minPos;
            }
        }
    }

    void updatePosition(int pos)
    {
        int k = pos + timeSize;
        int curLayer=layerNum-1;
        unsigned int posTime=bufTime[pos];
        while(k>0)
        {
            int layerIndex=k-offset[curLayer];
            int fatherIndex=layerIndex/childNum[curLayer];
            if(curLayer>=1)
            {
                k=fatherIndex+offset[curLayer-1];
            }
            else
                k=0;
            timeTree[k]=posTime;
            curLayer--;
        }
    }


};

#endif
