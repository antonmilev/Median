#pragma once
#include "Median.h"

/**
 * @file PerformanceTest.h
 * @brief Performance tests for the Median Class
 *
 * Tests can be run on Windows x86/x64 platforms.
 */

bool performanceTest(Median& m, int N, long& elapsed_ms);
bool performanceTestAll(int N);
