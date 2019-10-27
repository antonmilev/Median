#include <vector>
#include <chrono>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include "PerformanceTest.h"
#include "MedianFactory.h"

using namespace std;

// test performance with randomly generated values 
// verify results of the middle() function in the cycle
// set elapsed_ms to elapsed time in ms, in float format
// returns true on success
bool performanceTestRandom(const char* name, const vector<int>& random, const vector<int>& correct)
{
    cout << fixed << setprecision(2);
    // try to create object with the given name
    std::unique_ptr<Median> m = create_Median(name);
    if (!m)
    {
        cout << "Error creating:  " << name << endl;
        return false;
    }

    m->clear();
    if (m->size() != 0)
    {
        cout << "Error, Performance Test Failed!\n";
        return false;
    }
    vector<int> arr;
    auto start = std::chrono::high_resolution_clock::now();
    for (int k = 0; k < random.size(); k++)
    {
        m->add(random[k]);

        if (m->middle() != correct[k])
        {
            cout << "Error, Performance Test Failed!\n";
            return false;
        }
    }
    auto end = std::chrono::high_resolution_clock::now();
    float elapsed_ms = 1000 * std::chrono::duration_cast<std::chrono::duration<float>>(end - start).count();

    cout << std::left << setw(30) << m->name() << std::left << elapsed_ms << " [ms]" << endl;
    return true;
}

// test performance with adding values in descending order
// verify results of the middle() function in the cycle
// set elapsed_ms to elapsed time in ms, in float format
// returns true on success
bool performanceTestWorst(const char* name, int N)
{
    cout << fixed << setprecision(2);
    // try to create object with the given name
    std::unique_ptr<Median> m = create_Median(name);
    if (!m)
    {
        cout << "Error creating:  " << name << endl;
        return false;
    }

    m->clear();
    if (m->size() != 0)
    {
        cout << "Error, Performance Test Failed!\n";
        return false;
    }

    auto start = std::chrono::high_resolution_clock::now();
    for (int k = N; k >= 0; k--)
    {
        m->add(k);

        if (m->middle() != (k + N) / 2)
        {
            cout << "Error, Performance Test Failed!\n";
            return false;
        }
    }

    if (m->middle() != N / 2)
    {
        cout << "Error, Performance Test Failed!\n";
        return false;
    }

    auto end = std::chrono::high_resolution_clock::now();
    float elapsed_ms = 1000 * std::chrono::duration_cast<std::chrono::duration<float>>(end - start).count();

    cout << std::left << setw(30) << m->name() << std::left << elapsed_ms << " [ms]" << endl;
    return true;
}

// test performance with adding only repeating values from 0 to 9
// set elapsed_ms to elapsed time in ms, in float format
// returns true on success
bool performanceTestRepeating(const char* name, int N)
{
    cout << fixed << setprecision(2);
    // try to create object with the given name
    std::unique_ptr<Median> m = create_Median(name);
    if (!m)
    {
        cout << "Error creating:  " << name << endl;
        return false;
    }

    m->clear();
    if (m->size() != 0)
    {
        cout << "Error, Performance Test Failed!\n";
        return false;
    }

    auto start = std::chrono::high_resolution_clock::now();
    for (int k = 0; k < N; k++)
    {
        m->add(k % 10);

        m->middle();
    }

    auto end = std::chrono::high_resolution_clock::now();
    float elapsed_ms = 1000 * std::chrono::duration_cast<std::chrono::duration<float>>(end - start).count();

    cout << std::left << setw(30) << m->name() << std::left << elapsed_ms << " [ms]" << endl;
    return true;
}

bool performanceTestAllRandom(int N)
{
    cout << endl << "Performance Test Random Iterations: " << N << endl;

    // fill array with random numbers
    vector<int> random, sorted, correct;

    for (int k = 1; k < N; k++)
    {
        int r = rand();
        random.push_back(r);
        sorted.push_back(r);
        sort(sorted.begin(), sorted.end());
        correct.push_back(sorted[(k - 1) / 2]);
    }

    if (N <= 40000)
    {
        //performanceTestRandom("MedianVector", random, correct);
        performanceTestRandom("MedianNthElement", random, correct);
        performanceTestRandom("MedianVectorLBound", random, correct);
        performanceTestRandom("MedianMultisetAdvance", random, correct);
        performanceTestRandom("MedianMultisetIterator", random, correct);
    }
    performanceTestRandom("MedianRBTree", random, correct);
    performanceTestRandom("MedianMinMaxHeap", random, correct);
    return true;
}

bool performanceTestAllWorst(int N)
{
    cout << endl << "Performance Test Worst Iterations: " << N << endl;

    if (N <= 100000)
    {
        performanceTestWorst("MedianNthElement", N);
        performanceTestWorst("MedianVectorLBound", N);
        performanceTestWorst("MedianMultisetAdvance", N);
        performanceTestWorst("MedianMultisetIterator", N);
    }
    performanceTestWorst("MedianRBTree", N);
    performanceTestWorst("MedianMinMaxHeap", N);

    return true;
}

bool performanceTestAllRepeating(int N)
{
    cout << endl << "Performance Test Repeating Iterations: " << N << endl;

    if (N <= 40000)
    {
        performanceTestRepeating("MedianNthElement", N);
        performanceTestRepeating("MedianVectorLBound", N);
        performanceTestRepeating("MedianMultisetAdvance", N);
        performanceTestRepeating("MedianMultisetIterator", N);
    }
    
    performanceTestRepeating("MedianRBTree", N);
    performanceTestRepeating("MedianMinMaxHeap", N);

    return true;
}



