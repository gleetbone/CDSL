#Cable

This data structure is for very long character strings and has lots of utility API functions for finding and replacing substrings. The strings contain eight bit ASCII-type characters, not Unicode. The internal data structure is a red-black tree of substrings. 

The name of this data structure implies a lot of strings wound together - all of the good names (like ropes or twines) were already taken.

This data structure is one that only achieves 99.9% coverage in testing. Some parts of the deletion algorithm implementation (a few lines) do not ever get called. I'm not sure if this is because they will never be called due to the nature of the tree structure and the rebalancing algorithm, or because I'm not clever enough to devise a unit test to reach them. 

###Protocols Supported

none