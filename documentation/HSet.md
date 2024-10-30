# HSet

This data structure implements a hash set. Items in the set require a hash code to be computed which is used to compare and store them. The storage algorithm uses an array of linked lists keyed to the hash code - the size of the storage array can be specified at creation or changed on the fly. Too small an array slows storage and retrieval times, and too large an array wastes space. The array size should be a prime number for best results.

The basic set operations are included - union, intersection, symmetric difference, and so on.

### Protocols Supported

- P_Basic
- P_Iterable
