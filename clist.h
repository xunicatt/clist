#ifndef __CLIST_H__
#define __CLIST_H__

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

enum CList_Error_t {
    CLIST_SUCCESS,
    CLIST_GOT_NULL_PTR,
    CLIST_MEM_ALLOC_FAIL,
    __MAX_ERR_SIZE
};

static const char* __clist_error_msg[__MAX_ERR_SIZE] = {
    "success",
    "got null ptr",
    "memory allocation failed"
};

struct CList_Node_t {
    void *__ptr;
    struct CList_Node_t *__prev;
    struct CList_Node_t *__next;
};

struct CList_t {
    struct CList_Node_t *__front;
    struct CList_Node_t *__rear;
    size_t __obj_size;
    size_t __list_size;
};

typedef struct CList_t CList_t;
typedef struct CList_Node_t CList_Node_t;
typedef enum CList_Error_t CList_Error_t;

CList_Node_t* __clist_create_node(void*,size_t);
void *__clist_get_raw_ptr(CList_Node_t*);

void clist_error_handler(CList_Error_t);
CList_Error_t clist_init(CList_t*,size_t);

CList_Error_t clist_insert_front(CList_t*,void*);
CList_Error_t clist_insert_rear(CList_t*,void*);
CList_Error_t clist_insert_at(CList_t*,void*,size_t);

CList_Error_t clist_remove_front(CList_t*);
CList_Error_t clist_remove_rear(CList_t*);
CList_Error_t clist_remove_at(CList_t*,size_t);

CList_Node_t* clist_begin(CList_t*);
CList_Node_t* clist_end(CList_t*);
CList_Node_t* clist_next(CList_Node_t*);
CList_Node_t* clist_node_at(CList_t*, size_t);
CList_Error_t clist_update_at(CList_t*,void*,size_t);

size_t clist_size(CList_t*);

CList_Error_t clist_map(CList_t*, void *, void (*)(CList_Node_t*,void*));

void clist_free(CList_t*);

#define clist_for_each(list, node) for(node = clist_begin(list); node != clist_end(list); node = clist_next(node))
#define clist_node_unwrap_safe_as(node, type, default) (node == NULL?(default):(*((type*)__clist_get_raw_ptr(node))))
#define clist_node_unwrap_unsafe_as(node, type) *((type*)node->__ptr)

#define clist_insert_front_val(list, type, val) {\
                                                    type __clist_hidden = (val);\
                                                    clist_insert_front((list), &__clist_hidden);\
                                                }\

#define clist_insert_rear_val(list, type, val) {\
                                                    type __clist_hidden = (val);\
                                                    clist_insert_rear((list), &__clist_hidden);\
                                                }\


#define clist_insert_at_val(list, type, val, index) {\
                                                        type __clist_hidden = (val);\
                                                        clist_insert_at((list), &__clist_hidden, index);\
                                                    }\


#endif