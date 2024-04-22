# Assignment 8: Finding Anagrams with Hashtables

- About: 
    - Design a hashtable structure and implement methods: put, lookup, resize, and remove to manage key-value pairs.
    - In this case, we store the key as a string sorted in alphabetical order, and the corresponding values are stored in a linked list, containing strings with the same characters as the key.
  
- Provided files: 
* ```words.txt```: The word file you need to read in to find anagrams with. 
* ```Hashtable_easy.h```: A starting point to structuring your hashtable that 
stores strings (```char*```s). **IF** you want to use it. 
* ```Hashtable.h```: **IF** you want, you can use this to start structuring 
and building your hashtable. 
* ```Hashtable.c```: Stub file for your hashtable code, contains FNV Hash function. 
* ```LinkedList.c```: Placeholder file. Please replace with your version of LinkedList.c
* ```LinkedList_easy.h```: Contains API for a LinkedList that holds strings. It's an easier 
implementation than the other LinkedList. Feel free to replace with your own version if the signatures do not align.
* ```LinkedList.h```: Contains API for a generic LinkedList implementation that you can 
use for your Hashtable implementation, if you'd like.
* ```Makefile```: Generic starting Makefile
* ```test_hashtable.cc```: A starting test file for you to use to test your hashtable implementation. 

- unit test:
```
make test
./test_suite
```
```
[==========] Running 10 tests from 1 test case.
[----------] Global test environment set-up.
[----------] 10 tests from Hashtable
[ RUN      ] Hashtable.Create
[       OK ] Hashtable.Create (0 ms)
[ RUN      ] Hashtable.AddOneRemoveOne
Before removal:
====== Anagram Report ======
estt -> [ test ]
Current key: estt
Comparing keys: "estt" and "test"

After removal:
====== Anagram Report ======
[       OK ] Hashtable.AddOneRemoveOne (0 ms)
[ RUN      ] Hashtable.HashKeyToBucketNum
Hash key for "test" is: 5
Putting key "estt" in the hashtable...
Key stored in the map: "estt"
Current key: estt
Comparing keys: "estt" and "estt"
Removal is successful
[       OK ] Hashtable.HashKeyToBucketNum (0 ms)
[ RUN      ] Hashtable.AddOneElemDestroy
[       OK ] Hashtable.AddOneElemDestroy (0 ms)
[ RUN      ] Hashtable.AddOneElemTwoTimes
[       OK ] Hashtable.AddOneElemTwoTimes (0 ms)
[ RUN      ] Hashtable.AddOneRemoveTwice
Current key: estt
Comparing keys: "estt" and "test"
[       OK ] Hashtable.AddOneRemoveTwice (0 ms)
[ RUN      ] Hashtable.AddMultipleItems
[       OK ] Hashtable.AddMultipleItems (0 ms)
[ RUN      ] Hashtable.LookupInHashtable
[       OK ] Hashtable.LookupInHashtable (0 ms)
[ RUN      ] Hashtable.TwoElemsOneBucket
[       OK ] Hashtable.TwoElemsOneBucket (0 ms)
[ RUN      ] Hashtable.Resize
before resizing: 2
before resizing - Load Factor: 0.67
after resizing: 3
after resizing - Load Factor: 0.50
[       OK ] Hashtable.Resize (0 ms)
[----------] 10 tests from Hashtable (0 ms total)

[----------] Global test environment tear-down
[==========] 10 tests from 1 test case ran. (0 ms total)
[  PASSED  ] 10 tests.
```
- check memory leak
- check clint code style

- Resources: 

* https://medium.com/basecs/hashing-out-hash-functions-ea5dd8beb4dd (Hash Functions)
* https://medium.com/basecs/taking-hash-tables-off-the-shelf-139cbf4752f0?source=---------17----------------------- (Hash Tables, generally)
* http://www.cs.yale.edu/homes/aspnes/classes/223/notes.html#hashTables (Hashtables in C)
* http://www.cs.yale.edu/homes/aspnes/classes/223/notes.html#File_IO  (Reading a file in C)
* http://www.cs.yale.edu/homes/aspnes/classes/223/notes.html#functionPointers (Function Pointers, for more challenge)
