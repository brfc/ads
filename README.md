## avl

self-balancing binary search tree
efficient search, at cost of rigid balancing requirements

#### Why it matters?
 * Provides a rigid balancing factor. Most implementation
 of binary trees rely on red-black trees, which have a better
 amortized complexity of overall operations. 
 The AVL guarantees a better worst-case time complexity for
 consultation, fixing the over-head cost during insertion.
 * Better operational time estimation.
 * Better performance over persistent data. (write once, read many)

--- 
## Ring Buffer

Also known as a circular buffer or cyclic buffer, 
is a fixed-size buffer with a wrap-around mechanism.

#### Why it matters?
 * Efficient use of memory, constant time complexity, no overhead
 with memory allocations.
 * Usefull in produce/consume scenarios with different rate
 operations.
 * Data streaming, audio, serial communication, network packet
 processing.

---
## Trie

A trie, also known as a prefix tree, is a tree-like data structure
that is used to store a dynamic set of strings where the keys are usually strings/chars. 

#### Why it matters?
 * Tries are commonly used in scenarios where efficient string searching,
 prefix matching, and autocomplete functionalities are required.
 * Dictionary and Spell checking, Autocomplete and predictive text,
 IP Routing, Lexicographic sorting, IP Routing lookup, Network Packet
 Routing.

---
## Segment Tree

A segment tree is a tree-like data structure used for storing information 
about intervals or segments of an array. 
Each node of the tree represents a segment of the array.
Enables efficient querying of various operations over segments of an array,
such as finding the minimum, maximum, sum, or any other associative operation
over a specified range of indices.

#### Why it matters?
 * Range Query Operations, Dynamic Updates, Parallelism (due to independent segmentation).
 * Performance (Cache efficiency due to linear structure implementation).
 * Efficient Update and Querying at space overhead cost.

---

# Coverage
To get coverage data, install lcov beforehand. Then, generate project with DENABLE_COVERAGE.
> cmake -DENABLE_COVERAGE=true ..

> make

> ctest && make coverage 
