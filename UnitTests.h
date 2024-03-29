#pragma once
#include "Median.h"

/**
 * @file UnitTests.h
 * @brief Provides unit tests for Median Class
 *
 * Tests can be run on Windows x86/x64 platforms. 
 */

void printc(int color, const char* output, ...);
void printResult(const char* fname, bool bRes);

int test_median_basic(Median& m);
int test_median_iter(Median& m);
int test_median_random(Median& m);

int unitTest(const char* name);
void unitTestAll();
