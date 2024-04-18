## avl

self-balancing binary search tree
efficient search, at cost of rigid balancing requirements

### Why it matters?
 ** Provides a rigid balancing factor. Most implementations
 of binary trees rely on red-black trees, which have a better
 amortized complexity of overall operations. 
 The AVL guarantees a better worst-case time complexity for
 consultation, fixing the over-head cost during insertion.
 ** Better operational time estimation.
 ** Better performance over persistent data. (write once, read many)
