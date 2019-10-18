#pragma once
#include "Median.h"

/**
 * @file PerformanceTest.h
 * @brief Performance tests for the Median Class
 *
 * Tests can be run on Windows x86/x64 platforms.
 */

 /*! Performance test with randomly generated values, also checks if the returned values are correct
     \brief Test with randomly generated values
     \param N number of the test values
     \return True if sucessful
 */
bool performanceTestAllRandom(int N);

/*! Performance test with linearly descending values, also checks if the returned values are correct
    \brief Test with descending values
    \param N number of the test values
    \return True if sucessful
*/
bool performanceTestAllWorst(int N);

/*! Performance test with repeating (0-9) values
    \brief Test with repeating values
    \param N number of the test values
    \return True if sucessful
*/
bool performanceTestAllRepeating(int N);
