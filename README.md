# Median

Demonstrates several implementations of median of sorted elements calculation:
<br>
<br> <b>MedianVector</b> - uses std::sort
<br> <b>MedianNthElement</b> - uses std::nth_element
<br> <b>MedianVectorLBound</b> - uses std::lower_bound
<br> <b>MedianMultisetAdvance</b> - uses std::multiset and std::advance
<br> <b>MedianMultisetIterator</b> - uses std::multiset with median iterator
<br> <b>MedianRBTree</b> - uses Red-Black tree
<br> <b>MedianMinMaxHeap</b> - uses std::priority_queue as min and max binary heap (the fastest method)
<br>
<br>
Compiled with VS2017 or later (with loading CMakeLists.txt from File->Open->CMake..).

This will build a console application that runs Unit Tests for several containers in Debug
and several Performance tests in Release. 


 
 


