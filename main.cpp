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
    m.addStrategy(new lru(64));
    m.addStrategy(new lineClock(64));
    m.addStrategy(new treeClock(64,4));
    m.beginTest(10000);
    m.log();

    return 0;
}

