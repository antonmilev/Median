# Median
<br>Demonstrates several implementations of median of sorted elements calculation:
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
<br>To compile with VS2017 or later: 
<br>load CMakeLists.txt from File->Open->CMake.., after generates cache is completed, choose CMake->Build all
<br>
<br>To compile with GCC:
<br>cmake -D CMAKE_BUILD_TYPE=Release .
<br>cmake -D CMAKE_BUILD_TYPE=Debug .
<br>
<br>This will build a console application that runs Unit Tests for several containers in Debug
<br>and several Performance tests in Release. 


 
 


