# RBTree_kv

This data structure implements a self-balancing binary search tree. So it's relatively fast to insert or remove an item, and it will remain balanced as more and more items are inserted and deleted. (Re)Balancing the tree takes place on every insert and delete on just the part of the tree that has just been changed. The red-black balancing operation keeps each branch of the tree fairly close in length, but less so than the AVL algorithm, so it requires a bit less work to keep the tree balanced.  The red-black algorithm is usually the one specified for keeping large binary search trees in balance for real world work.

Each node of this version of the red-black binary search tree holds a key and a value. The tree is sorted according to the key.

### Protocols Supported

- P_Basic
- P_Iterable_kv
- P_DIterable_kv
