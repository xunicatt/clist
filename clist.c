#include "clist.h"

void
clist_error_handler(
    CList_Error_t err
) {
    if(err == CLIST_SUCCESS) return;
    fprintf(stderr, "%s\n", __clist_error_msg[err]);
}

CList_Node_t*
__clist_create_node(void *obj, size_t obj_size) {
    CList_Node_t *node = (CList_Node_t *)malloc(sizeof(CList_Node_t));
    if(node == NULL) return NULL;

    node->__prev = NULL;
    node->__next = NULL;
    node->__ptr = malloc(obj_size);
    if(node->__ptr == NULL) {
        free(node);
        return NULL;
    }

    memcpy(node->__ptr, obj, obj_size);
    return node;
}

void*
__clist_get_raw_ptr(
    CList_Node_t *n
) {
    return n->__ptr;
}

CList_Error_t 
clist_init(
    CList_t *l, 
    size_t object_size
) {
    if(l == NULL) return CLIST_MEM_ALLOC_FAIL;
    
    l->__front = l->__rear = NULL;
    l->__list_size = 0;
    l->__obj_size = object_size;

    return CLIST_SUCCESS;
}

CList_Error_t
clist_insert_front(
    CList_t *l, 
    void *obj
) {
    if(l == NULL || obj == NULL) return CLIST_GOT_NULL_PTR;

    if(l->__front == NULL || l->__rear == NULL) {
        l->__front = l->__rear = __clist_create_node(obj, l->__obj_size);
        if(l->__front == NULL) return CLIST_MEM_ALLOC_FAIL;

        l->__list_size++;
        return CLIST_SUCCESS;
    }

    CList_Node_t* new_front = __clist_create_node(obj, l->__obj_size);  
    if(new_front == NULL) return CLIST_MEM_ALLOC_FAIL;
    
    new_front->__next = l->__front;
    l->__front->__prev = new_front;
    l->__front = new_front;

    l->__list_size++;
    return CLIST_SUCCESS;
}

CList_Error_t
clist_insert_rear(
    CList_t *l,
    void *obj
) {
    if(l == NULL || obj == NULL) return CLIST_GOT_NULL_PTR;

    if(l->__front == NULL || l->__rear == NULL) {
        l->__front = l->__rear = __clist_create_node(obj, l->__obj_size);
        if(l->__front == NULL) return CLIST_MEM_ALLOC_FAIL;
        l->__list_size++;
        return CLIST_SUCCESS;
    }

    CList_Node_t* new_rear = __clist_create_node(obj, l->__obj_size);  
    if(new_rear == NULL) return CLIST_MEM_ALLOC_FAIL;

    new_rear->__prev = l->__rear;
    l->__rear->__next = new_rear;
    l->__rear = new_rear;

    l->__list_size++;
    return CLIST_SUCCESS;
}

CList_Error_t
clist_insert_at(
    CList_t* l,
    void* obj,
    size_t index
) {
    if(l == NULL || obj == NULL) return CLIST_GOT_NULL_PTR;

    if(index == 0) return clist_insert_front(l, obj);
    if(index >= l->__list_size) return clist_insert_rear(l, obj);

    CList_Node_t *node;
    
    
    while(index-- > 1 && node) {
        if(index < l->__list_size >> 1) {
            node = l->__front;
            
        }else{

        }

        node = node->__next;
    }

    CList_Node_t* tmp_node = __clist_create_node(obj, l->__obj_size);
    tmp_node->__next = node->__next;
    node->__next = tmp_node;
}

CList_Error_t
clist_remove_front(
    CList_t *l
) {
    if(l == NULL) return CLIST_GOT_NULL_PTR;
    if(l->__front == NULL) return CLIST_SUCCESS;

    CList_Node_t *node = l->__front;
    l->__front = l->__front->__next;
    if(l->__front == NULL) l->__rear = NULL;

    free(node->__ptr);
    free(node);
}

CList_Error_t
clist_remove_rear(
    CList_t *l
) {
    if(l == NULL) return CLIST_GOT_NULL_PTR;
    if(l->__rear == NULL) return CLIST_SUCCESS;

    CList_Node_t *node = l->__front;
    l->__front = l->__front->__next;
    if(l->__front == NULL) l->__rear = NULL;

    free(node->__ptr);
    free(node);
}

CList_Node_t*
clist_begin(
    CList_t *l
) {
    if(l == NULL) return NULL;
    return l->__front;    
}

CList_Node_t*
clist_end(
    CList_t *l
) {
    return NULL;
}

CList_Node_t*
clist_next(
    CList_Node_t* n
) {
    if(n == NULL) return NULL;
    return n->__next;
}

size_t
clist_size(
    CList_t* l
) {
    return l->__list_size;
}

CList_Node_t*
clist_node_at(
    CList_t* l,
    size_t index
) {
    if(index >= l->__list_size) return NULL;
    if(index == 0) return l->__front;
    if(index == l->__list_size - 1) return l->__rear;

    CList_Node_t* node = l->__front;

    while(index > 0 && node != NULL) {
        node = node->__next;
        index--;
    }

    return node;
}

CList_Error_t
clist_map(
    CList_t *l,
    void *arg,
    void (*func)(CList_Node_t*,void*)
) {
    if(l == NULL || func == NULL) return CLIST_GOT_NULL_PTR;
    
    CList_Node_t *n;
    clist_for_each(l, n) {
        func(n, arg);
    }
}

void
clist_free(
    CList_t *l
) {
    if(l == NULL) return;
    if(l->__front == NULL || l->__rear == NULL) return;

    CList_Node_t *tmp = l->__front;

    while(tmp) {
        l->__front = l->__front->__next;
        free(tmp->__ptr);
        free(tmp);
        tmp = l->__front;
    }
}