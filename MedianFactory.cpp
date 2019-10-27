#include "MedianFactory.h"

std::unique_ptr<Median> create_Median(const std::string& name)
{
    std::unique_ptr<Median> res;
    if (name == MedianVector::Name())
        res = std::make_unique< MedianVector>();
    else if (name == MedianNthElement::Name())
        res = std::make_unique< MedianNthElement>();
    else if (name == MedianVectorLBound::Name())
        res = std::make_unique< MedianVectorLBound>();
    else if (name == MedianMultisetAdvance::Name())
        res = std::make_unique< MedianMultisetAdvance>();
    else if (name == MedianMultisetIterator::Name())
        res = std::make_unique< MedianMultisetIterator>();
    else if (name == MedianRBTree::Name())
        res = std::make_unique< MedianRBTree>();
    else if (name == MedianMinMaxHeap::Name())
        res = std::make_unique< MedianMinMaxHeap>();
    // if we reach this point, return empty pointer
    return res;
}
