#include <iostream>
#include "Median.h"
#include "UnitTests.h"
#include "PerformanceTest.h"

int main()
{   
    unitTestAll();

    // run these in Release only
#ifdef NDEBUG
    performanceTestAllRandom(20000);
    performanceTestAllWorst(100000);
    performanceTestAllRepeating(20000);
#endif 

    return 0;
}
