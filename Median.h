#pragma once
#include <vector>
#include <set>
#include <queue>
#include "RBTree.h"

/**
 * @file Median.h
 * @brief Main declaration header for Median Intefrace and several Median implemntations 
 *
 * Following Median implementations are provided:
 *   MedianVector
 *   MedianNthElement
 *   MedianVectorLBound
 *   MedianMultisetAdvance
 *   MedianMultisetIterator
 *   MedianRBTree 
 *   MedianMinMaxHeap
 */

//!  Median class
/*!
  Median calculation class interface
  <br><br>
  All Median Calculations classes needs to support Median Units Tests platform 
  and should inherit <b>Median</b> interface and implement its virtual methods.
  <br>
  Purpose of Median and the derived classes is to find the <b>middle</b> element. 
  By <b>middle</b> it is understood the sorted in ascending order element exactly at position N/2, where N is the number of
  all added elements, if N is odd. If N is even, the <b>middle</b> element is at positoon N/2-1. This is shown below:
  <br>
  <br> Odd - 1,2,3   N=3, <b>middle</b> is 2, at position 1
  <br> Even - 1,2,3,4  N=4, <b>middle</b> is 2 also at position 1
  <br> Odd - 1,2,3,4,5  N=5, <b>middle</b> is 3 at position 2
  <br>
  <br> Median classes implementations were tested with units test (see UnitTests.h).
  <br> Performance tests comparing the algorithms are run in Release (see PerformanceTest.h).
*/
class Median
{
public:
    /// add new integer element
    virtual bool    add(int a) = 0;
    /// return value of the middle element
    virtual int     middle() const = 0;
    /// return number of all elements
    virtual size_t  size() const = 0;
    /// empty container
    virtual void    clear() = 0;
    /// return string with container name
    virtual const char* name() const = 0;
};

//!  MedianVector finds median using <b>std::vector</b> and <b>std::sort</b>
/*!
  MedianVector class implements Median with using for storage <b>std::vector</b> and <b>std::sort</b> to keep elements sorted.
  <br><b>add() Average Complexity O(n log n) </b> 
  <br><b>middle() Average Complexity O(1) </b>
  <br>
  <br> There is also additional cost for memory copies.
*/
class MedianVector : public Median
{
public:
    virtual bool        add(int a) ;
    virtual int         middle() const;
    virtual size_t      size() const ;
    virtual void        clear() ;
    static const char*  Name() ;
    virtual const char* name() const ;
    
protected:
    /// vector used for storage of the sorted elements
    std::vector<int> m_arr;
};


//!  MedianVector finds median using <b>std::vector></b> and <b>std::nth_element </b>
/*!
  MedianNthElement class implements Median with using for storage std::vector and std::nth_element to keep sorted the middle element only.
  <br><b>add() Average Complexity O(n) </b>
  <br><b>middle() Average Complexity O(1) </b>
  <br>
  <br> There is also additional cost for memory copies.
*/
class MedianNthElement : public Median
{
public:
    virtual bool        add(int a);
    virtual int         middle() const;
    virtual size_t      size() const;
    virtual void        clear();
    static const char*  Name() ;
    virtual const char* name() const ;

protected:
    /// vector used for storage of the sorted elements
    std::vector<int> m_arr;
};

//!  MedianVectorLBound calculate median using <b>std::vector</b> and <b>std::lower_bound</b>
/*!
  MedianVectorLBound class implements Median with using for storage std::vector and std::lower_bound to sort only the last inserted element only.
  First the position of the inserted element is found with <b>std::lower_bound</b>, and then the new element is inserted there.
  <br><b>add() Average Complexity O(log n) </b>
  <br><b>middle() Average Complexity O(1) </b>
  <br>
  <br> There is also additional cost for memory copies.
*/

class MedianVectorLBound : public Median
{
public:
    virtual bool        add(int a);
    virtual int         middle() const;
    virtual size_t      size() const;
    virtual void        clear();
    static const char*  Name() ;
    virtual const char* name() const ;

private:
    /// vector used for storage of the sorted elements
    std::vector<int> m_arr;
};


//!  MedianMultisetAdvance finds median using <b>std::multiset</b> and <b>std::advance</b>
/*!
  MedianMultisetAdvance uses for storage container <b>std::multiset</b> all values are sorted by default in ascending order. 
  Insert is done with the standard insert() routine of the multiset, obtaining then the middle element is done with std::advance.
  <br><b>add() Average Complexity O(log n)</b>
  <br><b>middle() Average Complexity O(n)</b>
*/
class MedianMultisetAdvance : public Median
{
public:
    virtual bool        add(int a);
    virtual int         middle() const;
    virtual size_t      size() const;
    virtual void        clear();
    static const char*  Name() ;
    virtual const char* name() const ;

protected:
    /// multiset used for storage of the sorted elements
    std::multiset<int> m_set;
};

//!  MedianMultisetIterator finds median using <b>std::multiset</b> and saved iterator to the middle element. 
/*!
  MedianMultisetIterator uses for storage container std::multiset, all values are sorted by default in ascending order.
  After insert <b>m_it</b> and <b>m_pos</b> variables are updated to point to the middle element.
  <br><b>add() Average Complexity O(log n) </b>
  <br><b>middle() Average Complexity O(1) </b>
*/

class MedianMultisetIterator : public Median
{
public:
    MedianMultisetIterator();
    virtual bool        add(int a);
    virtual int         middle() const;
    virtual size_t      size() const;
    virtual void        clear();
    static const char* Name() ;
    virtual const char* name() const ;

protected:
    /// vector used for storage of the sorted elements
    std::multiset<int>              m_set;
    /// iterator to the middle element inside the set
    std::multiset<int>::iterator    m_it;
    /// position of the middle element inside the set
    std::set<int>::size_type        m_pos;
};

/*!
   MedianRBTree uses for storage container Red-Black tree, all values are sorted in ascending order.
   Allows obtaining of the middle value as start iterating from the root. 
   Since Red-Black is a self balancing tree, the middle value would be very near to the root so the search has constant average complexity 
  <br><b>add() Average Complexity O(log n) </b>
  <br><b>middle() Average Complexity O(1) </b>
*/

//!  MedianRBTree finds median using <b>RBTree</b>
class MedianRBTree : public Median
{
public:
    virtual bool        add(int a);
    virtual int         middle() const;
    virtual size_t      size() const;
    virtual void        clear();
    static const char*  Name() ;
    virtual const char* name() const ;

protected:
    /// RBTree container used for storage of the sorted elements
    RBTree  m_bt;
    const char* N = "n" ;
};

//!  MedianMinMaxHeap finds median using two <b>std::priority_queue</b>
/*!
   <br>MedianMinMaxHeap uses for storage container two binary heaps, one min and one max.
   <br>Allows inserting duplicating values.
   <br>Obtain the middle value as checks which of both heaps has more elements.
   <br> See:  https://www.geeksforgeeks.org/median-of-stream-of-running-integers-using-stl/
   <br><b>add() Average Complexity O(log n) </b>
   <br><b>middle() Average Complexity O(1) </b>
*/
class MedianMinMaxHeap : public Median
{
public:
    virtual bool	add(int a);
    virtual int		middle() const;
    virtual size_t	size() const;
    virtual void	clear();
    static const char*  Name();
    virtual const char* name() const;

protected:
    // max heap to store the smaller half elements 
    std::priority_queue<int, std::vector<int>, std::less<int> > m_s;
    // min heap to store the greater half elements 
    std::priority_queue<int, std::vector<int>, std::greater<int> > m_g;
    // keep the middle element
    int m_middle;
};



