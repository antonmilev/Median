#pragma once
#include "Median.h"

/**
 * @file PerformanceTest.h
 * @brief Performance tests for the Median Class
 *
 * Tests can be run on Windows x86/x64 platforms.
 */

bool performanceTestAllRandom(int N);
bool performanceTestAllWorst(int N);
bool performanceTestAllRepeating(int N);
