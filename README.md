#Simple avl implementation for my own
##build library
```
cmake .
make
```
##usage
avl_init(&root, <compare_func>, <print_func>)
compare_func : define specific compare, NULL for default address compare
print_func : define specific print function, avl_dump will call back when walking nodes 
