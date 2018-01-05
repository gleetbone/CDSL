#AVLTree

This data structure implements a self-balancing binary search tree. So it's relatively fast to insert or remove an item, and it will remain balanced as more and more items are inserted and deleted. (Re)Balancing the tree takes place on every insert and delete on just the part of the tree that has just changed. The AVL balancing operation keeps each branch of the tree quite close in length, more so than the red-black algorithm, but requires a bit more work to do so. 

There is also an AVLTree_kv version that is implemented as a tree of keys with an associated value for each key.

This data structure is one that only achieves 99.7% coverage in testing. Some parts of the rebalancing algorithm implementation (a few lines) do not ever get called. I'm not sure if this is because they will never be called due to the nature of the tree structure and the rebalancing algorithm, or because I'm not clever enough to devise a unit test to reach them. 

###Protocols Supported

- P_Clonable
- P_Iterable
- P_DIterable
