#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <array>
#include <Windows.h>
#include <random> 
#include "UnitTests.h"

using namespace std;

static CONSOLE_SCREEN_BUFFER_INFO ConsoleInfo;
static HANDLE  screen = GetStdHandle(STD_OUTPUT_HANDLE);
void printc(int color, const char* output, ...)
{
    GetConsoleScreenBufferInfo(screen, &ConsoleInfo);
    SetConsoleTextAttribute(screen, color);
    va_list argList;
    va_start(argList, output);
    vprintf(output, argList);
    va_end(argList);
    SetConsoleTextAttribute(screen, ConsoleInfo.wAttributes);
}

void printResult(const char* fname, bool bRes)
{
    printf("%-#40s: ", fname);
    bRes ? printc(2, "Passed\n") : printc(4, "Failed\n");
    //bRes ? printf("Passed\n") : printf("Failed\n");
}

int test_median_basic(Median& m)
{
    try
    {
        {
            m.clear();

            // test if clear was sucessful
            if (m.size() != 0)
                goto error;

            //test if throws correctly out of trange, when empty
            try
            {
                if (m.middle() == 0)
                    goto error;
            }
            catch (out_of_range)
            {
                // it is Ok
            }
            catch (...)
            {
                goto error;
            }

            if (!m.add(10))
                goto error;

            if (m.middle() != 10 || m.size() != 1)
                goto error;

            if (!m.add(20))
                goto error;

            if (m.middle() != 10 || m.size() != 2)
                goto error;

            if (!m.add(15))
                goto error;

            if (m.middle() != 15 || m.size() != 3)
                goto error;

            if (!m.add(60))
                goto error;

            if (m.middle() != 15 || m.size() != 4)
                goto error;

            if (!m.add(1))
                goto error;

            if (m.middle() != 15 || m.size() != 5)
                goto error;
        }

        {
            // sorted is - 22, 34, 40, 53, 68, 73, 79, 100, 126, 136
            array<int, 10> a = { 100, 34, 79, 73, 53, 68, 40, 126, 136, 22 };
            for (int k = 0; k < 20; k++)
            {
                m.clear();
                if (m.size() != 0)
                    goto error;

                shuffle(a.begin(), a.end(), std::default_random_engine(0));
                for (int i : a)
                {
                    if (!m.add(i))
                        goto error;
                }
                if (m.middle() != 68 || m.size() != 10)
                    goto error;
            }
        }

        printResult("test_median()", true);
        return 0;

    error:
        printResult("test_median()", false);
        return 1;
    }
    catch (...)
    {
        printResult("test_median() [exception]", false);
        return 1;
    }
}

int test_median_iter(Median& m)
{
    try
    {
        // test with incremental values
        {
            m.clear();
            if (m.size() != 0)
                goto error;
            for (int k = 1; k < 1000; k++)
            {
                m.add(k);
                if (m.middle() != (k + 1) / 2)
                    goto error;
            }
        }

        // test with repeating values
        {
            m.clear();
            if (m.size() != 0)
                goto error;
            for (int k = 1; k < 10; k++)
            {
                m.add(1);
            }       
            
            for (int k = 1; k < 10; k++)
            {
                m.add(2);
            }
            
            if (m.middle() != 1)
                goto error;

            m.add(2);

            if (m.middle() != 2)
                goto error;

            m.add(1);

            if (m.middle() != 1)
                goto error;
        }

        // test with larger set ot repeating values
        {
            m.clear();
            if (m.size() != 0)
                goto error;
            int k;
            for (k = 1; k < 500; k++)
            {
                m.add(k % 10);
            }   

            for (k = 499; k > 0; k--)
            {
                m.add(k % 10);
            }
            
            if (m.middle() != 5)
            {
                m.middle();
                goto error;
            }
        }


        printResult("test_median_iter()", true);
        return 0;

    error:
        printResult("test_median_iter()", false);
        return 1;
    }
    catch (...)
    {
        printResult("test_median_iter() [exception]", false);
        return 1;
    }
}

int test_median_random(Median& m)
{
    try
    {
        {
            m.clear();
            if (m.size() != 0)
                goto error;
            vector<int> arr;
            for (int k = 1; k < 1000; k++)
            {
                int a = rand() % 10000;
                arr.push_back(a);

                sort(arr.begin(), arr.end());

                m.add(a);

                if (m.middle() != arr[(k - 1) / 2])
                    goto error;
            }
        }

        printResult("test_median_random()", true);
        return 0;

    error:
        printResult("test_median_random()", false);
        return 1;
    }
    catch (...)
    {
        printResult("test_median_random() [exception]", false);
        return 1;
    }
}

int unitTest(Median& m)
{
    int errors = 0;
    errors += test_median_basic(m);
    errors += test_median_iter(m);
    errors += test_median_random(m);
    m.clear();
    return errors;
}

int unitTest_MedianVector()
{
    printf("Test MedianVector...\n");
    MedianVector m;
    int errors = unitTest(m);
    printf("\nErrors: %d\n", errors);
    return errors;
}

int unitTest_MedianNthElement()
{
    printf("Test MedianNthElement...\n");
    MedianNthElement m;
    int errors = unitTest(m);
    printf("\nErrors: %d\n", errors);
    return errors;
}

int unitTest_MedianVectorLBound()
{
    printf("Test MedianVectorLBound...\n");
    MedianVectorLBound m;
    int errors = unitTest(m);
    printf("\nErrors: %d\n", errors);
    return errors;
}

int unitTest_MedianMultisetAdvance()
{
    printf("Test MedianMultisetAdvance...\n");
    MedianMultisetAdvance m;
    int errors = unitTest(m);
    printf("\nErrors: %d\n", errors);
    return errors;
}

int unitTest_MedianMultisetIterator()
{
    printf("Test MedianMultisetIterator...\n");
    MedianMultisetIterator m;
    int errors = unitTest(m);
    printf("\nErrors: %d\n", errors);
    return errors;
}




