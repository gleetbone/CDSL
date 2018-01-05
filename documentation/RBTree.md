#RBTree

This data structure implements a self-balancing binary search tree. So it's relatively fast to insert or remove an item, and it will remain balanced as more and more items are inserted and deleted. (Re)Balancing the tree takes place on every insert and delete on just the part of the tree that has just changed. The red-black balancing operation keeps each branch of the tree fairly close in length, but less so than the AVL algorithm, so it requires a bit less work to keep the tree balanced.  The red-black algorithm is usually the one specified for keeping large binary search trees in balance for real world work.

There is also a RBTree_kv version that is implemented as a tree of keys with an associated value for each key.

###Protocols Supported

- P_Clonable
- P_Iterable
- P_DIterable
