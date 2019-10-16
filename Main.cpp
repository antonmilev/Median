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

    // run these in Release only
#ifdef NDEBUG
    performanceTestAll(5000);
    performanceTestAll(10000);
    performanceTestAll(15000);
    performanceTestAll(20000);
#endif 

    return 0;
}

