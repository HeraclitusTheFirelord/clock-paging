#ifndef __PAGING_STRATEGY_H__
#define __PAGING_STRATEGY_H__

class pagingStrategy
{
    public:
        virtual int update(int key) = 0;   //return the ranking
        virtual int evict(int key) = 0;
        
    

    private:
        int *buf;
}









#endif
