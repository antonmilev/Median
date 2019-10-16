#include <vector>
#include <chrono>
#include <iostream>
#include <algorithm>
#include "PerformanceTest.h"

using namespace std;

bool performanceTest(Median& m, int N, long& elapsed_ms)
{
    m.clear();
    if (m.size() != 0)
        return false;
    vector<int> arr;
    chrono::time_point<std::chrono::system_clock> start, end;
    start = chrono::system_clock::now();
    for (int k = 1; k < N; k++)
    {
        int a = rand() % 10000;
        arr.push_back(a);

        sort(arr.begin(), arr.end());

        m.add(a);

        if (m.middle() != arr[(k - 1) / 2])
            return false;
    }
    end = std::chrono::system_clock::now();
    elapsed_ms = (long)chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    return true;
}

bool performanceTestAll(int N)
{
    cout << "Performance Test Iterations: " << N << endl;
    
    long elapsed;
    MedianVector m1;
    if (!performanceTest(m1, N, elapsed))
    {
        cout << "Error, Performance Test Failed!\n";
        return false;
    }
    cout << "MedianVector:\t\t" << elapsed << " [ms]" << endl;

    MedianNthElement m2;
    if (!performanceTest(m2, N, elapsed))
    {
        cout << "Error, Performance Test Failed!\n";
        return false;
    }
    cout << "MedianNthElement:\t" << elapsed << " [ms]" << endl;

    MedianVectorLBound m3;
    if (!performanceTest(m3, N, elapsed))
    {
        cout << "Error, Performance Test Failed!\n";
        return false;
    }
    cout << "MedianVectorLBound:\t" << elapsed << " [ms]" << endl;

    MedianMultisetAdvance m4;
    if (!performanceTest(m4, N, elapsed))
    {
        cout << "Error, Performance Test Failed!\n";
        return false;
    }
    cout << "MedianMultisetAdvance:\t" << elapsed << " [ms]" << endl;

    MedianMultisetIterator m5;
    if (!performanceTest(m5, N, elapsed))
    {
        cout << "Error, Performance Test Failed!\n";
        return false;
    }
    cout << "MedianMultisetIterator:\t" << elapsed << " [ms]" << endl;

    return true;
}

