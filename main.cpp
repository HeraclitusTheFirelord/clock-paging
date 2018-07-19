#include "pagingTest.h"

int main(int argc, char ** argv)
{
    /*
    pagingStrategy*s = new treeClock(4, 4);
    s->update(0).update(1).update(2).update(3);
    s->update(4).update(5).update(3).update(7);
    s->update(0).update(1).update(2);
    s->log();
    */

    testManager m;
#if 1 
    m.addStrategy(new lru(64));
    m.addStrategy(new lineClock(64));
    m.addStrategy(new treeClock(64,4));

    m.beginTest(10000);
#endif
#if 0
    m.addStrategy(new lru(4096));
    m.addStrategy(new lineClock(4096));
    m.addStrategy(new treeClock(4096,2));
    m.addStrategy(new treeClock(4096,4));
    m.addStrategy(new treeClock(4096,8));
    m.addStrategy(new treeClock(4096,64));
  
    m.beginTest(200000);
#endif
    m.log(true);

    return 0;
}

