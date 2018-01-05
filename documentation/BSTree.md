#BSTree

This data structure implements a non-self-balancing binary search tree. So it's fast to insert or remove an item, but it will become unbalanced as more and more items are inserted and deleted. When commanded to balance itself, the entire tree is re-balanced - potentially a time consuming operation for larger trees.

There is also a BSTree_kv version that is implemented as a tree of keys with an associated value for each key.

###Protocols Supported

- P_Clonable
- P_Iterable
- P_DIterable
