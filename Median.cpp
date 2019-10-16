#include "Median.h"
#include <algorithm>
#include <stdexcept>

using namespace std;

void MedianVector::clear()
{
	m_arr.clear();
}

size_t MedianVector::size() const
{
	return m_arr.size();
}

int MedianVector::middle() const
{
	if (!m_arr.size())
		throw out_of_range("out of range");

	return m_arr[(m_arr.size() - 1) / 2];
}

bool MedianVector::add(int a)
{
	m_arr.push_back(a);
	sort(m_arr.begin(), m_arr.end());
	return true;
}

//
// MedianNthElement
//
size_t MedianNthElement::size() const
{
	return m_arr.size();
}

bool MedianNthElement::add(int a)
{
	m_arr.push_back(a);
	std::nth_element(m_arr.begin(), m_arr.begin() + (m_arr.size() - 1) / 2, m_arr.end());
	return true;
}

void MedianNthElement::clear()
{
	m_arr.clear();
}

int MedianNthElement::middle() const
{
	if (!m_arr.size())
		throw out_of_range("out of range");
	return m_arr[(m_arr.size() - 1) / 2];
}

//
// MedianVectorLBound
// 
size_t MedianVectorLBound::size() const
{
	return m_arr.size();
}

// uses lower_bound to find the proper position where to insert the value
bool MedianVectorLBound::add(int a)
{
	auto it = lower_bound(m_arr.begin(), m_arr.end(), a);
	if (it == m_arr.end())
	{
		m_arr.push_back(a);
		return true;
	}
	else
		m_arr.insert(it, a); // insert before iterator it

	return true;
}

void MedianVectorLBound::clear()
{
	m_arr.clear();
}

int MedianVectorLBound::middle() const
{
	if (!m_arr.size())
		throw out_of_range("out of range");

	return m_arr[(m_arr.size() - 1) / 2];
}

//
// MedianMultisetAdvance
//

size_t MedianMultisetAdvance::size() const
{
	return m_set.size();
}

int MedianMultisetAdvance::middle() const
{
	if (!m_set.size())
		throw out_of_range("out of range");

	auto it = m_set.begin();
	advance(it, (m_set.size() - 1) / 2);
	return *it;
}

void MedianMultisetAdvance::clear()
{
	m_set.clear();
}

bool MedianMultisetAdvance::add(int a)
{
	return m_set.insert(a) != m_set.end();
}

//
//  MedianMultisetIterator
//
MedianMultisetIterator::MedianMultisetIterator()
{
	m_it = m_set.end();
	m_pos = 0;
}

size_t MedianMultisetIterator::size() const
{
	return m_set.size();
}

int MedianMultisetIterator::middle() const
{
	if (!m_set.size())
		throw out_of_range("out of range");

	return *m_it;
}

void MedianMultisetIterator::clear()
{
	m_set.clear();
	m_it = m_set.end();
	m_pos = 0;
}

bool MedianMultisetIterator::add(int a)
{
	auto it = m_set.insert(a);
	if (it == m_set.end())
		return false;

	if (m_it == m_set.end())
		m_it = it;
	else
	{
		// check if the inserted element iterator position is equal to the previous
		if (it != m_set.begin())
		{	
			auto itPrev = it;
			itPrev--;
			// check if to use advance
			if (*itPrev == *it)
			{
				// reset iterator and update stored pointers
				auto it = m_set.begin();
				advance(it, (m_set.size() - 1) / 2);
				m_it = it;
				m_pos = (m_set.size() - 1) / 2;
				return true;
			}
		}

		// check if the added value is less or equal to the value in the stored pointer
		// and move the iterator correspondingly
		if (*it <= *m_it)
		{
			m_pos++;

			if (m_pos * 2 >= m_set.size())
			{
				m_it--;
				m_pos--;
			}
		}
		else
		{
			if (m_pos * 2 < m_set.size() - 2)
			{
				m_it++;
				m_pos++;
			}
		}
	}
	return true;
}
