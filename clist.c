#include "clist.h"

struct clist_node_t {
    void *__ptr;
    struct clist_node_t *__prev;
    struct clist_node_t *__next;
};

struct clist_t {
    struct clist_node_t *__front;
    struct clist_node_t *__rear;
    size_t __obj_size;
    size_t __list_size;
};

static const char* __clist_error_msg[__MAX_ERR_SIZE] = {
    "success",
    "got null ptr",
    "memory allocation failed",
    "index out of bound"
};

const char *
clist_get_error_info(
    const clist_error_t err
) {
    return __clist_error_msg[err];
}

static clist_node_t*
__clist_create_node(
    const void *obj, 
    size_t obj_size
) {
    clist_node_t *node = (clist_node_t *)malloc(sizeof(clist_node_t));
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
    const clist_node_t *n
) {
    if(n == NULL) return NULL;
    return n->__ptr;
}

clist_t*
clist_init(
    const size_t object_size
) { 
    clist_t *l = (clist_t*)malloc(sizeof(clist_t));
    if(l == NULL) return NULL;

    l->__front = l->__rear = NULL;
    l->__list_size = 0;
    l->__obj_size = object_size;

    return l;
}

clist_error_t
clist_insert_front(
    clist_t *l, 
    const void *obj
) {
    if(l == NULL || obj == NULL) return CLIST_GOT_NULL_PTR;

    if(l->__front == NULL || l->__rear == NULL) {
        l->__front = l->__rear = __clist_create_node(obj, l->__obj_size);
        if(l->__front == NULL) return CLIST_MEM_ALLOC_FAIL;

        l->__list_size++;
        return CLIST_SUCCESS;
    }

    clist_node_t* new_front = __clist_create_node(obj, l->__obj_size);  
    if(new_front == NULL) return CLIST_MEM_ALLOC_FAIL;
    
    new_front->__next = l->__front;
    l->__front->__prev = new_front;
    l->__front = new_front;

    l->__list_size++;
    return CLIST_SUCCESS;
}

clist_error_t
clist_insert_rear(
    clist_t *l,
    const void *obj
) {
    if(l == NULL || obj == NULL) return CLIST_GOT_NULL_PTR;

    if(l->__front == NULL || l->__rear == NULL) {
        l->__front = l->__rear = __clist_create_node(obj, l->__obj_size);
        if(l->__front == NULL) return CLIST_MEM_ALLOC_FAIL;
        l->__list_size++;
        return CLIST_SUCCESS;
    }

    clist_node_t* new_rear = __clist_create_node(obj, l->__obj_size);  
    if(new_rear == NULL) return CLIST_MEM_ALLOC_FAIL;

    new_rear->__prev = l->__rear;
    l->__rear->__next = new_rear;
    l->__rear = new_rear;

    l->__list_size++;
    return CLIST_SUCCESS;
}

clist_error_t
clist_insert_at(
    clist_t* l,
    const void* obj,
    size_t index
) {
    if(l == NULL || obj == NULL) return CLIST_GOT_NULL_PTR;

    if(index == 0) return clist_insert_front(l, obj);
    if(index >= l->__list_size) return clist_insert_rear(l, obj);

    clist_node_t *node;
    
    if(index < l->__list_size >> 1) {
        node = l->__front;
        
        while(index-- > 1 && node)
            node = node->__next;
    }else{
        node = l->__rear;
        index = l->__list_size - index;
        while(index-- > 0 && node)
            node = node->__prev;
    }

    clist_node_t* tmp_node = __clist_create_node(obj, l->__obj_size);
    if(tmp_node == NULL) return CLIST_MEM_ALLOC_FAIL;
    
    tmp_node->__next = node->__next;
    if(tmp_node->__next)
        tmp_node->__next->__prev = tmp_node;
    
    node->__next = tmp_node;
    tmp_node->__prev = node;
    return CLIST_SUCCESS;
}

clist_error_t
clist_remove_front(
    clist_t *l
) {
    if(l == NULL) return CLIST_GOT_NULL_PTR;
    if(l->__front == NULL) return CLIST_SUCCESS;

    clist_node_t *node = l->__front;
    l->__front = l->__front->__next;
    if(l->__front == NULL) l->__rear = NULL;

    free(node->__ptr);
    free(node);
    l->__list_size--;
    return CLIST_SUCCESS;
}

clist_error_t
clist_remove_rear(
    clist_t *l
) {
    if(l == NULL) return CLIST_GOT_NULL_PTR;
    if(l->__rear == NULL) return CLIST_SUCCESS;

    clist_node_t *node = l->__front;
    l->__front = l->__front->__next;
    if(l->__front == NULL) l->__rear = NULL;

    free(node->__ptr);
    free(node);
    l->__list_size--;
    return CLIST_SUCCESS;
}

clist_error_t
clist_remove_at(
    clist_t *l,
    size_t index
) {
    if(l == NULL) return CLIST_GOT_NULL_PTR;

    if(index == 0) return clist_remove_front(l);
    if(index == l->__list_size - 1) return clist_remove_rear(l);
    if(index >= l->__list_size) return CLIST_INDEX_OUT_OF_BOUND;

    clist_node_t *node;
    
    if(index < l->__list_size >> 1) {
        node = l->__front;
        while(index-- > 1 && node)
            node = node->__next;
    }else{
        node = l->__rear;
        index = l->__list_size - index;
        while(index-- > 0 && node)
            node = node->__prev;
    }

    node->__prev->__next = node->__next;
    node->__next->__prev = node->__prev;

    free(node->__ptr);
    free(node);
    l->__list_size--;
    return CLIST_SUCCESS;
}

clist_node_t*
clist_begin(
    const clist_t *l
) {
    if(l == NULL) return NULL;
    return l->__front;    
}

clist_node_t*
clist_rbegin(
    const clist_t *l
) {
    if(l == NULL) return NULL;
    return l->__rear;    
}

clist_node_t*
clist_end(
    const clist_t *l
) {
    return NULL;
}

clist_node_t*
clist_rend(
    const clist_t *l
) {
    return NULL;
}

clist_node_t*
clist_next(
    const clist_node_t* n
) {
    if(n == NULL) return NULL;
    return n->__next;
}

clist_node_t*
clist_prev(
    const clist_node_t* n
) {
    if(n == NULL) return NULL;
    return n->__prev;
}

size_t
clist_size(
    const clist_t* l
) {
    if(l == NULL) return 0;
    return l->__list_size;
}

clist_node_t*
clist_node_at(
    const clist_t* l,
    size_t index
) {
    if(l == NULL) return NULL;
    if(index >= l->__list_size) return NULL;
    if(index == 0) return l->__front;
    if(index == l->__list_size - 1) return l->__rear;

    clist_node_t* node;

    if(index < l->__list_size >> 1) {
        node = l->__front;
        while(index-- > 0 && node)
            node = node->__next;
    }else{
        node = l->__rear;
        index = l->__list_size - index;
        while(index-- > 1 && node)
            node = node->__prev;
    }

    return node;
}

clist_error_t
clist_map(
    const clist_t *l,
    void *arg,
    clist_map_function_t* func
) {
    if(l == NULL || func == NULL) return CLIST_GOT_NULL_PTR;
    
    clist_node_t *n;
    clist_for_each(l, n) {
        func(n, arg);
    }

    return CLIST_SUCCESS;
}

clist_error_t
clist_update_at(
    const clist_t *l,
    const void *val,
    const size_t index
) {
    if(l == NULL || val == NULL) return CLIST_GOT_NULL_PTR;
    if(index >= l->__list_size) return CLIST_INDEX_OUT_OF_BOUND;

    clist_node_t *n = clist_node_at(l, index);
    memcpy(n->__ptr, val, l->__obj_size);
    return CLIST_SUCCESS;
}

void
clist_free(
    clist_t *l
) {
    if(l == NULL) return;
    if(l->__front == NULL || l->__rear == NULL) return;

    clist_node_t *tmp = l->__front;

    while(tmp) {
        l->__front = l->__front->__next;
        free(tmp->__ptr);
        free(tmp);
        tmp = l->__front;
    }

    free(l);
}