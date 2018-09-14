# AVL-Tree
A C++ class implementation of an AVL tree

# Insert
Follow the insertion path and keep a pointer, named A, to the last node in the path with balance factor 1 or -1. If there is no such node update balance factors in the pathand terminate. If bf of A was 1 (-1) and the node was inserted in the left (right) sub tree now bf of A is 0, update factors from A down to the inserted node and terminate. If A is now unbalanced, rotate and update factors from A down to the inserted node.

# Remove
Find the element that is to be removed, while keeping a stack of the path up to that element. If that element has two children rotate with the max elemnt in the left subtree, so it now has one or zero children and track the path to the new location. Next remove the element and hang its subtree onto the parent. Finally, update the balance factor ascending the path doing rotations if needed. 

#Find
Standard BST search.
