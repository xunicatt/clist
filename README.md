# clist
A very simple to use Linked List libray for C. </br>
Currently working on improving the documentation.

# Installation
+ Linux/macOS:
```bash
$ make install #to install
$ make uninstall #to uninstall
```
+ Header File: clist.h
+ Static Library File: libclist.a [-lclist]

# Compiling
+ Linux/macOS:
```bash
$ gcc <file-name> -I /usr/local/include -L /usr/local/lib -lclist
```

# Reference
### Types
+ clist_error_t
+ clist_node_t
+ clist_map_function_t
+ clist_t

### Functions
+ clist_get_error_info
+ clist_init
+ clist_insert_front
+ clist_insert_rear
+ clist_insert_at
+ clist_remove_front
+ clist_remove_rear
+ clist_remove_at
+ clist_begin
+ clist_rbegin
+ clist_end
+ clist_rend
+ clist_next
+ clist_prev
+ clist_node_at
+ clist_update_at
+ clist_map
+ clist_size
+ clist_free

### Macros
+ clist_init_t
+ clist_list_end
+ clist_for_each
+ clist_for_each_reverse
+ clist_node_unwrap_safe_as
+ clist_node_unwarp_unsafe_as
+ clist_insert_front_val
+ clist_insert_rear_val
+ clist_insert_at_val
+ clist_update_at_val
+ clist_node_get_type_ptr
+ clist_is_empty


# Documentation
+ Initialise the Object:
```c
clist_t *clist;
clist_error_t err;

clist = clist_init(sizeof(int));
clist = clist_init_t(int); //macro to do the same operation
```

+ Insert an element:

```c
int x = 45;
err = clist_insert_front(clist, &x);

//macro to do the same previous two operation
clist_insert_front_val(clist, int, 45, err);

int y = 14;
err = clist_insert_rear(clist, &y);

//macro to do the same previous two operation
clist_insert_rear_val(clist, int, 14, err);

int z = 37;
err = clist_insert_at(clist, &x, 7); //7 is the index

//macro to do the same previous two operation
clist_insert_at_val(clist, int, 45, 7, err);
```

+ Update an elemnt:
```c
int i = 99;
err = clist_update_at(clist, &i, 0); //updates the element with new value at 0th index

//macro to do the same previous two operation
clist_update_at_val(clist, int, 99, 0, err);
```

+ Remove an element:
```c
err = clist_remove_front(clist);
err = clist_remove_rear(clist);
err = clist_remove_at(clist, 0);
```

+ Iterators:
```c
clist_node_t *n;
n = clist_begin(clist); //get the first node of linked list
//returns null if linked list is empty

n = clist_rbegin(clist); //get the last node of linked list
//returns null if linked list is empty

clist_node_t *end;
end = clist_end(clist); //returns the end of linked list
end = clist_rend(clist); //returns the reverse end of linked list

n = clist_next(n); //moves node `n` to next node
n = clist_prev(n); //moves node `n` to previous node

//n equals to end on reaching either size of the linked list

//itterating the linked list
clist_node_t *iter;
clist_for_each(clist, iter) {
    //iter contains the data
}

//itterating the linked list in reverse
clist_for_each_reverse(clist, iter) {
    //iter contains the data
}
```

+ Unwraping a Node Value:
```c
int val = clist_node_unwrap_unsafe_as(n, int); //not safe, if the node is `NULL` then it will cause an segfault
val = clist_node_unwrap_safe_as(n, int, -1); //if the node is `NULL`, -1 will be assigned in val else the node value
```

+ Get Node at an index:
```c
clist_node_t *n0 = clist_node_at(clist, 4); //get node
int val0 = clist_node_unwrap_safe_as(n0, int, 0);
```

+ Linked List Size:
```c
size_t s = clist_size(clist);

//itterating using size
for(size_t i = 0; i < s; i++) {
    clist_node_t *n = clist_node_at(clist, i);
    int val = clist_node_unwrap_safe_as(n, int, -1);
}
```

+ Map function:
```c
//map function in clist allows to itterate over the linked-list
//while calling call-back function at each node
void sum(clist_node_t *n, void *data) {
    int *sum_val = (int *)data;
    *sum_val += clist_node_unwrap_safe_as(n, int, 0);
}

//in other function
int sum_val = 0;
clist_map(clist, (void*)&sum_val, (const clist_map_function_t*)sum);
//sum_val will contain sum of all nodes
```
