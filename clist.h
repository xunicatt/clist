#ifndef __CLIST_H__
#define __CLIST_H__

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define __CLIST_VERSION__ "v1.0.0"
#define __CLIST_VERSION_MAJ__ 1
#define __CLIST_VERSION_MIN__ 0
#define __CLIST_VERSION_PATCH__ 0

/*
**  ERROR CODES
*/
typedef enum clist_error_t {
    CLIST_SUCCESS,
    CLIST_GOT_NULL_PTR,
    CLIST_MEM_ALLOC_FAIL,
    CLIST_INDEX_OUT_OF_BOUND,
    __MAX_ERR_SIZE
} clist_error_t;

/*
**  @brief Stores Data of a Node
*/
typedef struct clist_node_t clist_node_t;

/*
**  @brief clist map function
** @param clist_node_t* node
** @param void* arg
*/
typedef void (clist_map_function_t)(clist_node_t*,void*);

/*
** @name Linked List
** @brief call `clist_init` or `clist_init_type` to initialize the Linked List before start using it.
** @brief `clist_free` must be called after finish using the Linked List.
*/
typedef struct clist_t clist_t;

/*
**  INTERNAL FUNCTIONS
*/
void *__clist_get_raw_ptr(const clist_node_t*);

/*
** @brief Get Error message from a error code.
** @param clist_error_t
** @returns const char*
*/
const char* clist_get_error_info(const clist_error_t);

/*
** @brief Initializes a clist_t Linked List.
** @brief Use `clist_init_type` to automatically set size of a type.
** @param size_t item_size
** @returns clist_t*
*/
clist_t* clist_init(const size_t);

/*
** @brief Inserts an item at front in a Linked List.
** @brief Use `clist_insert_front_val` for direct Value intersion.
** @param clist_t* 
** @param void* address_of_an_item
** @returns clist_error_t
*/
clist_error_t clist_insert_front(clist_t*,const void*);

/*
** @brief Inserts an item at rear in a Linked List.
** @brief Use `clist_insert_rear_val` for direct Value intersion.
** @param clist_t* 
** @param void* address_of_an_item
** @returns clist_error_t
*/
clist_error_t clist_insert_rear(clist_t*,const void*);

/*
** @brief Inserts an item at an index in a Linked List.
** @brief Use `clist_insert_at_val` for direct Value intersion.
** @param clist_t* 
** @param void* address_of_an_item
** @param size_t index
** @returns clist_Error_t
*/
clist_error_t clist_insert_at(clist_t*,const void*,size_t);

/*
** @brief Removes an item from front in a Linked List.
** @param clist_t* 
** @returns clist_error_t
*/
clist_error_t clist_remove_front(clist_t*);

/*
** @brief Removes an item from rear in a Linked List.
** @param clist_t* 
** @returns clist_error_t
*/
clist_error_t clist_remove_rear(clist_t*);

/*
** @brief Removes an item from an index in a Linked List.
** @param clist_t* 
** @returns clist_error_t
*/
clist_error_t clist_remove_at(clist_t*,size_t);

/*
** @brief Get pointer to the first Node of the Linked List.
** @param clist_t* 
** @returns clist_node_t*
*/
clist_node_t* clist_begin(const clist_t*);

/*
** @brief Get pointer to the last Node of the Linked List.
** @param clist_t* 
** @returns clist_node_t*
*/
clist_node_t* clist_rbegin(const clist_t*);

/*
** @brief Get pointer to the last Node of the Linked List.
** @param clist_t* 
** @returns clist_node_t*
*/
clist_node_t* clist_end(const clist_t*);

/*
** @brief Get pointer to the first Node of the Linked List.
** @param clist_t* 
** @returns clist_node_t*
*/
clist_node_t* clist_rend(const clist_t*);

/*
** @brief Moves the Node pointer to next Node in Linked List.
** @brief If the linked list is empty or the Node is at the end it return `NULL`.
** @param clist_node_t* 
** @returns clist_node_t*
*/
clist_node_t* clist_next(const clist_node_t*);

/*
** @brief Moves the Node pointer to previous Node in Linked List.
** @brief If the linked list is empty or the Node is at the end it return `NULL`.
** @param clist_node_t* 
** @returns clist_node_t*
*/
clist_node_t* clist_prev(const clist_node_t*);

/*
** @brief Returns a pointer to the Node at an index from Linked List.
** @brief If the linked list is empty it return `NULL`.
** @brief If the index is out of range from the size of Linked List, a pointer to the Last Node is returned.
** @param clist_t* 
** @param size_t index 
** @returns clist_node_t*
*/
clist_node_t* clist_node_at(const clist_t*, size_t);

/*
** @brief Updates the value at an index in Linked List.
** @brief Use `clist_update_at_val` for direct Value intersion.
** @param clist_t* 
** @param void* address_of_an_item
** @param size_t index 
** @returns clist_error_t
*/
clist_error_t clist_update_at(const clist_t*,const void*,const size_t);

/*
** @brief Use `clist_map` to perfrom some operation using function callback.
** @param clist_t* 
** @param void* callback_argument
** @param clist_map_function_t*
** @returns clist_Error_t
*/
clist_error_t clist_map(const clist_t*, void *, clist_map_function_t*);

/*
** @brief Get size of the Linked List.
** @param clist_t* 
** @returns size_t
*/
size_t clist_size(const clist_t*);

/*
** @brief Must be called after finish using the Linked List.
** @brief Calling `clist_free` will deallocate all memory allocated by `CList_t` and `CList_Node_t`.s
** @param clist_t* 
*/
void clist_free(clist_t*);

/*
** @brief Macro to initialize a CList_t Linked List.
** @param data-type type
** @returns clist_t*
*/
#define clist_init_t(type) (clist_init(sizeof(type)))

/*
** @brief End of a linkedlist [both side]
*/
#define clist_list_end NULL

/*
** @brief Macro to itterate over Nodes in Linked List.
** @param clist_t* list
** @param clist_node_t* node
*/
#define clist_for_each(list, node) for(node = clist_begin(list); node != clist_list_end; node = clist_next(node))

/*
** @brief Macro to itterate in reverese order over Nodes in Linked List.
** @param clist_t* list
** @param clist_node_t* node
*/
#define clist_for_each_reverse(list, node) for(node = clist_rbegin(list); node != clist_list_end; node = clist_prev(node))

/*
** @brief Macro to get value from a Node [Safe].
** @brief If the Node is `NULL` then the default value will be set.
** @param clist_node_t* node
** @param linked_list_data_type type
** @param linked_list_data_type default-value
** @returns linked_list_data_type
*/
#define clist_node_unwrap_safe_as(node, type, default) (node == NULL?(default):(*((type*)__clist_get_raw_ptr(node))))

/*
** @brief Macro to get value from a Node [Unsafe].
** @brief Can cause Segmentation Fault if the Node is `NULL`.
** @brief Using `clist_node_unwrap_safe_as` is a better option.
** @param clist_node_t* node
** @param linked_list_data_type type
** @returns linked_list_data_type
*/
#define clist_node_unwrap_unsafe_as(node, type) (*((type*)__clist_get_raw_ptr(node)))

/*
** @brief Macro to insert value of an item at front in a Linked List.
** @param clist_t* list
** @param linked_list_data_type type
** @param linked_list_data_type val
** @param clist_error_t err
*/
#define clist_insert_front_val(list, type, val, err) {\
                                                    type __clist_hidden = (val);\
                                                    err = clist_insert_front((list), &__clist_hidden);\
                                                }\

/*
** @brief Macro to insert value of an item at rear in a Linked List.
** @param clist_t* list
** @param linked_list_data_type type
** @param linked_list_data_type val
** @param clist_error_t err
*/
#define clist_insert_rear_val(list, type, val, err) {\
                                                    type __clist_hidden = (val);\
                                                    err = clist_insert_rear((list), &__clist_hidden);\
                                                }\

/*
** @brief Macro to insert value of an item at an index in a Linked List.
** @param clist_t* list
** @param linked_list_data_type type
** @param linked_list_data_type val
** @param size_t index
** @param clist_error_t err
*/
#define clist_insert_at_val(list, type, val, index, err) {\
                                                        type __clist_hidden = (val);\
                                                        err = clist_insert_at((list), &__clist_hidden, index);\
                                                    }\

/*
** @brief Macro to update value of an item at an index in a Linked List.
** @param clist_t* list
** @param linked_list_data_type type
** @param linked_list_data_type val
** @param size_t index
** @param clist_error_t err
*/
#define clist_update_at_val(list, type, val, index, err) {\
                                                        type __clist_hidden = (val);\
                                                        err = clist_update_at((list), &__clist_hidden, index);\
                                                    }\

/*
** @brief Macro to get pointer to an object from a node.
** @param clist_node_t* node
** @param linked_list_data_type type
*/
#define clist_node_get_type_ptr(node, type) ((type)__clist_get_raw_ptr(node))

/*
** @brief Check if list is empty.
** @returns bool
*/
#define clist_is_empty(list) (clist_size(list) == 0)

#endif
