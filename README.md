# SCU DB project2——朱俊宏2020141230141

### The files involved are as follows

- Task1
  src/include/page/b_plus_tree_page.h
  src/page/b_plus_tree_page.cpp
  src/include/page/b_plus_tree_internal_page.h
  src/page/b_plus_tree_internal_page.cpp
  src/include/page/b_plus_tree_leaf_page.h
  src/page/b_plus_tree_leaf_page.cpp
- Task2
  src/include/index/b_plus_tree.h
  src/index/b_plus_tree.cpp
- Task3
  src/include/index/index_iterator.h
  src/index/index_iterator.cpp

* TEST

​		test/index/b_plus_tree_test.cpp

​		test/index/b_plus_tree_print_test.cpp

​		test/index/b_plus_tree_page_test.cpp

​		test/index/b_plus_tree_insert_test.cpp

​		test/index/b_plus_tree_delete_test.cpp

​		test/index/b_plus_tree_concurrent_test.cpp

---

### Build

Using CLion to load Project1, then execute:

```
cd cmake-build-debug
make
```

### Test

There are 2 test for this lab:

- b_plus_tree_test

```
cd cmake-build-debug
make b_plus_tree_test
./test/b_plus_tree_test
```

- b_plus_tree_print_test

```
cd cmake-build-debug
make b_plus_tree_print_test
./test/b_plus_tree_print_test
```

* b_plus_tree_page_test
* b_plus_tree_insert_test
* b_plus_tree_delete_test
* b_plus_tree_concurrent_test

### Result


