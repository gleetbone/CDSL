# AVLTree

This data structure implements a self-balancing binary search tree. So it's relatively fast to insert or remove an item, and it will remain balanced as more and more items are inserted and deleted. (Re)Balancing the tree takes place on every insert and delete on just the part of the tree that has just changed. The AVL balancing operation keeps each branch of the tree quite close in length, more so than the red-black algorithm, but requires a bit more work to do so. 

There is also an AVLTree_kv version that is implemented as a tree of keys with an associated value for each key.

### Protocols Supported

- P_Basic
- P_Iterable
- P_DIterable
