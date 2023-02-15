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
- TEST  
  test/index/b_plus_tree_test.cpp  
  test/index/b_plus_tree_print_test.cpp  
  test/index/b_plus_tree_page_test.cpp  
  test/index/b_plus_tree_insert_test.cpp  
  test/index/b_plus_tree_delete_test.cpp  
  test/index/b_plus_tree_concurrent_test.cpp  
---
### Test

There are 3 test for this lab:

- b_plus_tree_test

```
cd build
make b_plus_tree_test
./test/b_plus_tree_test
```
- b_plus_tree_print_test
```
make b_plus_tree_print_test
./test/b_plus_tree_print_test
```
- b_plus_tree_concurrent_test
```
make b_plus_tree_concurrent_test  
./test/b_plus_tree_concurrent_test  
```
---
### Result
* b_plus_tree_concurrent_test
![b_plus_tree_concurrent_test](https://user-images.githubusercontent.com/86907571/218813397-24040554-c89e-440b-ae96-13bc12bb53e0.png)
---
* b_plus_tree_print_test  
insert:  
![insert menu](https://user-images.githubusercontent.com/86907571/218813671-bc678461-f916-4776-8c2e-0f09073c8308.png)  

delete:  
![delete](https://user-images.githubusercontent.com/86907571/218813697-0b1e55c1-a0ed-43a8-98c5-d7d45c805eba.png)  

quit:  
![quit](https://user-images.githubusercontent.com/86907571/218899601-ee8643a6-27da-42fc-9f2d-c56ee4fa9b98.png)
 
