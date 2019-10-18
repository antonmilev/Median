#include <iostream>
#include "Median.h"
#include "UnitTests.h"
#include "PerformanceTest.h"

int main()
{   
    unitTest_MedianVector();
    unitTest_MedianNthElement();
    unitTest_MedianVectorLBound();
    unitTest_MedianMultisetAdvance();
    unitTest_MedianMultisetIterator();
    unitTest_MedianRBTree();

    // run these in Release only
#ifdef NDEBUG
    performanceTestAllRandom(20000);
    performanceTestAllWorst(100000);
    performanceTestAllRepeating(20000);
#endif 

    return 0;
}

