#include "pagingTest.h"

using namespace std;
#include <vector>

int main(int argc, char ** argv)
{
#if 0
    pagingStrategy*s = new treeClock(4, 4);
    s->update(0).update(1).update(2).update(3);
    s->update(4).update(5).update(3).update(7);
    s->update(0).update(1).update(2);
    s->log(true);
#endif

    testManager m;
#if 1
    //m.addStrategy(new lru(64));
    //m.addStrategy(new lineClock(64));
    //m.addStrategy(new treeClock(64,4));
    //m.addStrategy(new treeClock(64,64));
    //m.addStrategy(new lruClock(64,1));
    //m.addStrategy(new lruClock(64,2));
    //m.addStrategy(new lruClock(64,4));
    //m.addStrategy(new lruClock(64,8));
    //m.addStrategy(new lruClock(64,16));
    //m.addStrategy(new lruClock(64,32));
    //m.addStrategy(new lruClock(64,64));
    vector<int> v;
    int c1[1]={64};
    v=vector<int>(c1,c1+1);    
    m.addStrategy(new treeLru(64, v));
    int c20[2]={8, 8}; 
    v=vector<int>(c20,c20+2);    
    m.addStrategy(new treeLru(64, v));
    int c21[2]={16, 4};
    v=vector<int>(c21,c21+2);    
    m.addStrategy(new treeLru(64, v));
    int c2[2]={32, 2};
    v=vector<int>(c2,c2+2);    
    m.addStrategy(new treeLru(64, v));
    int c30[3]={8, 4, 2};
    v=vector<int>(c30,c30+3);    
    m.addStrategy(new treeLru(64, v));
    int c3[3]={4, 4, 4};
    v=vector<int>(c3,c3+3);    
    m.addStrategy(new treeLru(64, v));
    int c6[6]={2, 2, 2, 2, 2, 2};
    v=vector<int>(c6,c6+6);    
    m.addStrategy(new treeLru(64, v));

    m.beginTest(10000);
    m.log(true);
#endif
#if 0
    m.addStrategy(new lru(4096));
    m.addStrategy(new lineClock(4096));
    //m.addStrategy(new treeClock(4096,2));
    m.addStrategy(new treeClock(4096,4));
    //m.addStrategy(new treeClock(4096,8)); 
    //m.addStrategy(new treeClock(4096,64));
    //m.addStrategy(new treeClock(4096,4096));
    int c1[1]={4096};
    v=vector<int>(c1,c1+1);    
    m.addStrategy(new treeLru(4096, v));
    int c2[2]={64, 64};
    v=vector<int>(c2,c2+2);    
    m.addStrategy(new treeLru(4096, v));
    int c3[3]={16, 16, 16};
    v=vector<int>(c3,c3+3);    
    m.addStrategy(new treeLru(4096, v));
    int c4[4]={8, 8, 8, 8};
    v=vector<int>(c4,c4+4);    
    m.addStrategy(new treeLru(4096, v));

    m.beginTest(200000);
    m.log();
#endif

    return 0;
}

