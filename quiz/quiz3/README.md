#quiz3
- about
    - Implement the function `isBST(tree) => boolean`. `isBst` takes as argument a tree and returns true if it is a BST, false otherwise.
    - Implement the function `findNumsBelow(bst, num) => int[]`. FindNum traverses a BST and returns all values less than num in an array.

- input/output example:
```
10
1
11
Tree is BST: true

Input: num1 = 10, num2 = 1
Output:
Numbers below 10: 1 
No elements are founded smaller than 1
```
- check memory leak:
```
valgrind --leak-check=full ./a.out
```

```
==1172202== HEAP SUMMARY:
==1172202==     in use at exit: 0 bytes in 0 blocks
==1172202==   total heap usage: 6 allocs, 6 frees, 1,116 bytes allocated
==1172202== 
==1172202== All heap blocks were freed -- no leaks are possible
==1172202== 
==1172202== For lists of detected and suppressed errors, rerun with: -s
==1172202== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)placeholder
```
