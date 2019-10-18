#include <vector>
#include <chrono>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include "PerformanceTest.h"

using namespace std;

// test performance with randomly generated values 
// compares results of the middle() function in the cycle
// set elapsed_ms to elapsed time in ms, in float format
// returns true on success
bool performanceTestRandom(Median& m, vector<int> random, vector<int> correct, float& elapsed_ms)
{
    m.clear();
    if (m.size() != 0)
        return false;
    vector<int> arr;
    auto start = std::chrono::high_resolution_clock::now();
    for (int k = 0; k < random.size(); k++)
    {
        m.add(random[k]);

        if (m.middle() != correct[k])
            return false;
    }
    auto end = std::chrono::high_resolution_clock::now();
    elapsed_ms = 1000 * std::chrono::duration_cast<std::chrono::duration<float>>(end - start).count();
    return true;
}

// test performance with adding values in descending order
// compares results of the middle() function in the cycle
// set elapsed_ms to elapsed time in ms, in float format
// returns true on success
bool performanceTestWorst(Median& m, int N, float& elapsed_ms)
{
    m.clear();
    if (m.size() != 0)
        return false;

    auto start = std::chrono::high_resolution_clock::now();
    for (int k = N; k >= 0; k--)
    {
        m.add(k);

        if (m.middle() != (k + N) / 2)
            return false;
    }

    if (m.middle() != N / 2)
        return false;

    auto end = std::chrono::high_resolution_clock::now();
    elapsed_ms = 1000 * std::chrono::duration_cast<std::chrono::duration<float>>(end - start).count();
    return true;
}

// test performance with adding only repeating values from 0 to 9
// set elapsed_ms to elapsed time in ms, in float format
// returns true on success
bool performanceTestRepeating(Median& m, int N, float& elapsed_ms)
{
    m.clear();
    if (m.size() != 0)
        return false;

    auto start = std::chrono::high_resolution_clock::now();
    for (int k = 0; k < N; k++)
    {
        m.add(k % 10);

        m.middle();
    }

    auto end = std::chrono::high_resolution_clock::now();
    elapsed_ms = 1000 * std::chrono::duration_cast<std::chrono::duration<float>>(end - start).count();
    return true;
}

bool performanceTestAllRandom(int N)
{
    cout << endl << "Performance Test Random Iterations: " << N << endl;

    cout << fixed << setprecision(2);

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

    float elapsed;
    if (N <= 10000)
    {
        MedianVector m1;
        if (!performanceTestRandom(m1, random, correct, elapsed))
        {
            cout << "Error, Performance Test Failed!\n";
            return false;
        }
        cout << "MedianVector:\t\t" << elapsed << " [ms]" << endl;
    }

    MedianNthElement m2;
    if (!performanceTestRandom(m2, random, correct, elapsed))
    {
        cout << "Error, Performance Test Failed!\n";
        return false;
    }
    cout << "MedianNthElement:\t" << elapsed << " [ms]" << endl;

    MedianVectorLBound m3;
    if (!performanceTestRandom(m3, random, correct, elapsed))
    {
        cout << "Error, Performance Test Failed!\n";
        return false;
    }
    cout << "MedianVectorLBound:\t" << elapsed << " [ms]" << endl;

    MedianMultisetAdvance m4;
    if (!performanceTestRandom(m4, random, correct, elapsed))
    {
        cout << "Error, Performance Test Failed!\n";
        return false;
    }
    cout << "MedianMultisetAdvance:\t" << elapsed << " [ms]" << endl;

    MedianMultisetIterator m5;
    if (!performanceTestRandom(m5, random, correct, elapsed))
    {
        cout << "Error, Performance Test Failed!\n";
        return false;
    }
    cout << "MedianMultisetIterator:\t" << elapsed << " [ms]" << endl;

    MedianRBTree m6;
    if (!performanceTestRandom(m6, random, correct, elapsed))
    {
        cout << "Error, Performance Test Failed!\n";
        return false;
    }
    cout << "MedianRBTree:\t\t" << elapsed << " [ms]" << endl;


    return true;
}

bool performanceTestAllWorst(int N)
{
    cout << endl << "Performance Test Worst Iterations: " << N << endl;

    cout << fixed << setprecision(2);

    float elapsed;

    MedianNthElement m2;
    if (!performanceTestWorst(m2, N, elapsed))
    {
        cout << "Error, Performance Test Failed!\n";
        return false;
    }
    cout << "MedianNthElement:\t" << elapsed << " [ms]" << endl;
    
    MedianVectorLBound m3;
    if (!performanceTestWorst(m3, N, elapsed))
    {
        cout << "Error, Performance Test Failed!\n";
        return false;
    }
    cout << "MedianVectorLBound:\t" << elapsed << " [ms]" << endl;
    
    MedianMultisetAdvance m4;
    if (!performanceTestWorst(m4, N, elapsed))
    {
        cout << "Error, Performance Test Failed!\n";
        return false;
    }
    cout << "MedianMultisetAdvance:\t" << elapsed << " [ms]" << endl;
    
    MedianMultisetIterator m5;
    if (!performanceTestWorst(m5, N, elapsed))
    {
        cout << "Error, Performance Test Failed!\n";
        return false;
    }
    cout << "MedianMultisetIterator:\t" << elapsed << " [ms]" << endl;

    MedianRBTree m6;
    if (!performanceTestWorst(m6, N, elapsed))
    {
        cout << "Error, Performance Test Failed!\n";
        return false;
    }
    cout << "MedianRBTree:\t\t" << elapsed << " [ms]" << endl;

    cout << endl;

    return true;
}

bool performanceTestAllRepeating(int N)
{
    cout << "Performance Test Repeating Iterations: " << N << endl;

    cout << fixed << setprecision(2);

    float elapsed;

    MedianNthElement m2;
    if (!performanceTestRepeating(m2, N, elapsed))
    {
        cout << "Error, Performance Test Failed!\n";
        return false;
    }
    cout << "MedianNthElement:\t" << elapsed << " [ms]" << endl;

    MedianVectorLBound m3;
    if (!performanceTestRepeating(m3, N, elapsed))
    {
        cout << "Error, Performance Test Failed!\n";
        return false;
    }
    cout << "MedianVectorLBound:\t" << elapsed << " [ms]" << endl;
    MedianMultisetAdvance m4;
    if (!performanceTestRepeating(m4, N, elapsed))
    {
        cout << "Error, Performance Test Failed!\n";
        return false;
    }
    cout << "MedianMultisetAdvance:\t" << elapsed << " [ms]" << endl;
    
    MedianMultisetIterator m5;
    if (!performanceTestRepeating(m5, N, elapsed))
    {
        cout << "Error, Performance Test Failed!\n";
        return false;
    }
    cout << "MedianMultisetIterator:\t" << elapsed << " [ms]" << endl;

    MedianRBTree m6;
    if (!performanceTestRepeating(m6, N, elapsed))
    {
        cout << "Error, Performance Test Failed!\n";
        return false;
    }
    cout << "MedianRBTree:\t\t" << elapsed << " [ms]" << endl;

    cout << endl;

    return true;
}



