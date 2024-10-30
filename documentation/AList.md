# AList

This data structure implements a doubly linked list using an array to hold the contained items. So it's fast to get an item by index and iterate through the list, but slower to add or remove items because large chunks of the array may have to be moved to accomodate the insertion or removal.

This data structure is a lot like Sequence with the difference that you can use the contained array like a list.

### Protocols Supported

- P_Basic
- P_Indexable
- P_Iterable
- P_DIterable
