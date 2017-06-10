# AVL-Tree
C++ implementation of an AVL tree

# Insert
Follow the insertion path and keep a pointer, named A, to the last node in the path with balance factor 1 or -1. If there is no such node update balance factors in the pathand terminate. If bf of A was 1 (-1) and the node was inserted in the left (right) sub tree now bf of A is 0, update factors from A down to the inserted node and terminate. If A is now unbalanced, rotate and update factors from A down to the inserted node.
