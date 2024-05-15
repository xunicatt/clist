#ifndef __CLIST_H__
#define __CLIST_H__

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/*
**  ERROR CODES
*/
enum CList_Error_t {
    CLIST_SUCCESS,
    CLIST_GOT_NULL_PTR,
    CLIST_MEM_ALLOC_FAIL,
    CLIST_INDEX_OUT_OF_BOUND,
    __MAX_ERR_SIZE
};

/*
** Stores Error Infos
*/
struct CList_Error_Info_t {
    enum CList_Error_t error;
    const char* msg;
};

/*
**  Stores Data of a Node
*/
struct CList_Node_t {
    void *__ptr;
    struct CList_Node_t *__prev;
    struct CList_Node_t *__next;
};

/*
** @name Linked List
** @brief call `clist_init` or `clist_init_type` to initialize the Linked List before start using it.
** @brief `clist_free` must be called after finish using the Linked List.
*/
struct CList_t {
    struct CList_Node_t *__front;
    struct CList_Node_t *__rear;
    size_t __obj_size;
    size_t __list_size;
};

typedef struct CList_t CList_t;
typedef struct CList_Node_t CList_Node_t;
typedef enum CList_Error_t CList_Error_t;
typedef struct CList_Error_Info_t CList_Error_Info_t;

/*
**  INTERNAL FUNCTION
*/
CList_Node_t* __clist_create_node(void*,size_t);

/*
**  INTERNAL FUNCTIONS
*/
void *__clist_get_raw_ptr(CList_Node_t*);

/*
** @brief Get Error message from a error code.
** @param CList_Error_t
** @returns CList_Error_Info_t
*/
CList_Error_Info_t clist_get_error_info(CList_Error_t);

/*
** @brief Initializes a CList_t Linked List.
** @brief Use `clist_init_type` to automatically set size of a type.
** @param CList_t* 
** @param size_t item_size
** @returns CList_Error_t
*/
CList_Error_t clist_init(CList_t*,size_t);

/*
** @brief Inserts an item at front in a Linked List.
** @brief Use `clist_insert_front_val` for direct Value intersion.
** @param CList_t* 
** @param void* address_of_an_item
** @returns CList_Error_t
*/
CList_Error_t clist_insert_front(CList_t*,void*);

/*
** @brief Inserts an item at rear in a Linked List.
** @brief Use `clist_insert_rear_val` for direct Value intersion.
** @param CList_t* 
** @param void* address_of_an_item
** @returns CList_Error_t
*/
CList_Error_t clist_insert_rear(CList_t*,void*);

/*
** @brief Inserts an item at an index in a Linked List.
** @brief Use `clist_insert_at_val` for direct Value intersion.
** @param CList_t* 
** @param void* address_of_an_item
** @param size_t index
** @returns CList_Error_t
*/
CList_Error_t clist_insert_at(CList_t*,void*,size_t);

/*
** @brief Removes an item from front in a Linked List.
** @param CList_t* 
** @returns CList_Error_t
*/
CList_Error_t clist_remove_front(CList_t*);

/*
** @brief Removes an item from rear in a Linked List.
** @param CList_t* 
** @returns CList_Error_t
*/
CList_Error_t clist_remove_rear(CList_t*);

/*
** @brief Removes an item from an index in a Linked List.
** @param CList_t* 
** @returns CList_Error_t
*/
CList_Error_t clist_remove_at(CList_t*,size_t);

/*
** @brief Get pointer to the first Node of the Linked List.
** @param CList_t* 
** @returns CList_Node_t*
*/
CList_Node_t* clist_begin(CList_t*);

/*
** @brief Get pointer to the last Node of the Linked List.
** @param CList_t* 
** @returns CList_Node_t*
*/
CList_Node_t* clist_rbegin(CList_t*);

/*
** @brief Get pointer to the last Node of the Linked List.
** @param CList_t* 
** @returns CList_Node_t*
*/
CList_Node_t* clist_end(CList_t*);

/*
** @brief Get pointer to the first Node of the Linked List.
** @param CList_t* 
** @returns CList_Node_t*
*/
CList_Node_t* clist_rend(CList_t*);

/*
** @brief Moves the Node pointer to next Node in Linked List.
** @brief If the linked list is empty or the Node is at the end it return `NULL`.
** @param CList_Node_t* 
** @returns CList_Node_t*
*/
CList_Node_t* clist_next(CList_Node_t*);

/*
** @brief Moves the Node pointer to previous Node in Linked List.
** @brief If the linked list is empty or the Node is at the end it return `NULL`.
** @param CList_Node_t* 
** @returns CList_Node_t*
*/
CList_Node_t* clist_prev(CList_Node_t*);

/*
** @brief Returns a pointer to the Node at an index from Linked List.
** @brief If the linked list is empty it return `NULL`.
** @brief If the index is out of range from the size of Linked List, a pointer to the Last Node is returned.
** @param CList_t* 
** @param size_t index 
** @returns CList_Node_t*
*/
CList_Node_t* clist_node_at(CList_t*, size_t);

/*
** @brief Updates the value at an index in Linked List.
** @brief Use `clist_update_at_val` for direct Value intersion.
** @param CList_t* 
** @param void* address_of_an_item
** @param size_t index 
** @returns CList_Error_t
*/
CList_Error_t clist_update_at(CList_t*,void*,size_t);

/*
** @brief Use `clist_map` to perfrom some operation using function callback.
** @param CList_t* 
** @param void* callback_argument
** @param function void func(CList_Node_t *n,void *arg)
** @returns CList_Error_t
*/
CList_Error_t clist_map(CList_t*, void *, void (*)(CList_Node_t*,void*));

/*
** @brief Get size of the Linked List.
** @param CList_t* 
** @returns size_t
*/
size_t clist_size(CList_t*);

/*
** @brief Must be called after finish using the Linked List.
** @brief Calling `clist_free` will deallocate all memory allocated by `CList_t` and `CList_Node_t`.s
** @param CList_t* 
*/
void clist_free(CList_t*);

/*
** @brief Macro to initialize a CList_t Linked List.
** @param CList_t* list
** @param linked_list_data_type type
** @param CList_Error_t err
*/
#define clist_init_type(list, type, err) err = clist_init(list, sizeof(type))

/*
** @brief Macro to itterate over Nodes in Linked List.
** @param CList_t* list
** @param CList_Node_t* node
*/
#define clist_for_each(list, node) for(node = clist_begin(list); node != clist_end(list); node = clist_next(node))

/*
** @brief Macro to itterate in reverese order over Nodes in Linked List.
** @param CList_t* list
** @param CList_Node_t* node
*/
#define clist_for_each_reverse(list, node) for(node = clist_rbegin(list); node != clist_end(list); node = clist_prev(node))

/*
** @brief Macro to get value from a Node [Safe].
** @brief If the Node is `NULL` then the default value will be set.
** @param CList_Node_t* node
** @param linked_list_data_type type
** @param linked_list_data_type default-value
** @returns linked_list_data_type
*/
#define clist_node_unwrap_safe_as(node, type, default) (node == NULL?(default):(*((type*)__clist_get_raw_ptr(node))))

/*
** @brief Macro to get value from a Node [Unsafe].
** @brief Can cause Segmentation Fault if the Node is `NULL`.
** @brief Using `clist_node_unwrap_safe_as` is a better option.
** @param CList_Node_t* node
** @param linked_list_data_type type
** @returns linked_list_data_type
*/
#define clist_node_unwrap_unsafe_as(node, type) *((type*)node->__ptr)

/*
** @brief Macro to insert value of an item at front in a Linked List.
** @param CList_t* list
** @param linked_list_data_type type
** @param linked_list_data_type val
** @param CList_Error_t err
*/
#define clist_insert_front_val(list, type, val, err) {\
                                                    type __clist_hidden = (val);\
                                                    err = clist_insert_front((list), &__clist_hidden);\
                                                }\

/*
** @brief Macro to insert value of an item at rear in a Linked List.
** @param CList_t* list
** @param linked_list_data_type type
** @param linked_list_data_type val
** @param CList_Error_t err
*/
#define clist_insert_rear_val(list, type, val, err) {\
                                                    type __clist_hidden = (val);\
                                                    err = clist_insert_rear((list), &__clist_hidden);\
                                                }\

/*
** @brief Macro to insert value of an item at an index in a Linked List.
** @param CList_t* list
** @param linked_list_data_type type
** @param linked_list_data_type val
** @param size_t index
** @param CList_Error_t err
*/
#define clist_insert_at_val(list, type, val, index, err) {\
                                                        type __clist_hidden = (val);\
                                                        err = clist_insert_at((list), &__clist_hidden, index);\
                                                    }\

/*
** @brief Macro to update value of an item at an index in a Linked List.
** @param CList_t* list
** @param linked_list_data_type type
** @param linked_list_data_type val
** @param size_t index
** @param CList_Error_t err
*/
#define clist_update_at_val(list, type, val, index, err) {\
                                                        type __clist_hidden = (val);\
                                                        err = clist_update_at((list), &__clist_hidden, index);\
                                                    }\

/*
** @brief Macro to get pointer to an object from a node.
** @param CList_Node_t* node
** @param linked_list_data_type type
*/
#define clist_node_get_type_ptr(node, type) (type)__clist_get_raw_ptr(node)

#endif