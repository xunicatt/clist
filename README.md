# clist
A very simple to use Linked List libray for C.

# Installation
```bash
$ make install #to install
$ make uninstall #to uninstall
```
+ Header File: clist.h
+ Static Library File: libclist.a [-lclist]

# Documentation
+ Initialise the Object:
```c
CList_t clist;
CList_Error_t err;

err = clist_init(&clist, sizeof(int));
clist_init_type(&clist, int, err); //macro to do the same operation
```

+ Insert an element:

```c
int x = 45;
err = clist_insert_front(&clist, &x);

//macro to do the same previous two operation
clist_insert_front_val(&clist, int, 45, err);

int y = 14;
err = clist_insert_rear(&clist, &y);

//macro to do the same previous two operation
clist_insert_rear_val(&clist, int, 14, err);

int z = 37;
err = clist_insert_at(&clist, &x, 7); //7 is the index

//macro to do the same previous two operation
clist_insert_at_val(&clist, int, 45, 7, err);
```

+ Update an elemnt:
```c
int i = 99;
err = clist_update_at(&clist, &i, 0); //updates the element with new value at 0th index

//macro to do the same previous two operation
clist_update_at_val(&clist, int, 99, 0, err);
```

+ Remove an element:
```c
err = clist_remove_front(&clist);
err = clist_remove_rear(&clist);
err = clist_remove_at(&clist, 0);
```

+ Iterators:
```c
CList_Node_t *n;
n = clist_begin(&clist); //get the first node of linked list
//returns null if linked list is empty

n = clist_rbegin(&clist); //get the last node of linked list
//returns null if linked list is empty

CList_Node_t *end;
end = clist_end(&clist); //returns the end of linked list
end = clist_rend(&clist); //returns the reverse end of linked list

n = clist_next(n); //moves node `n` to next node
n = clist_prev(n); //moves node `n` to previous node

//n equals to end on reaching either size of the linked list

//itterating the linked list
CList_Node_t *iter;
clist_for_each(&clist, iter) {
    //iter contains the data
}

//itterating the linked list in reverse
clist_for_each_reverse(&clist, iter) {
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
CList_Node_t *n0 = clist_node_at(&clist, 4); //get node
int val0 = clist_node_unwrap_safe_as(n0, int, 0);
```

+ Linked List Size:
```c
size_t s = clist_size(&clist);

//itterating using size
for(size_t i = 0; i < s; i++) {
    CList_Node_t *n = clist_node_at(&clist, i);
    int val = clist_node_unwrap_safe_as(n, int, -1);
}
```

+ Map function:
```c
//map function in clist allows to itterate over the linked-list
//while calling call-back function at each node
void sum(CList_Node_t *n, void *data) {
    int *sum_val = (int *)data;
    *sum_val += clist_node_unwrap_safe_as(n, int, 0);
}

//in other function
int sum_val = 0;
clist_map(&clist, &sum_val, sum);
//sum_val will contain sum of all nodes
```
