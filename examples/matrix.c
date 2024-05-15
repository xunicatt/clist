#include <stdio.h>
#include <clist.h>

int main(void) {
    CList_t mat;
    CList_Error_t err;
    int global_i = 1;
    clist_init_type(&mat, CList_t, err);
    
    for(int i = 0; i < 5; i++) {
        clist_insert_at_val(&mat, CList_t, (CList_t){0}, i, err);

        CList_Node_t *node = clist_node_at(&mat, i);
        CList_t *row = clist_node_get_type_ptr(node, CList_t*);
        clist_init_type(row, int, err);

        for(int j = 1; j <= 2; j++)
            clist_insert_at_val(row, int, global_i++, j-1, err);
    }

    CList_Node_t *node;
    clist_for_each(&mat, node) {
        CList_t *row = clist_node_get_type_ptr(node, CList_t*);
        CList_Node_t *row_node;

        clist_for_each(row, row_node) {
            int val = clist_node_unwrap_safe_as(row_node, int, -1);
            printf("%d ", val);
        }

        puts("\n");
    }

    for(int i = 0; i < clist_size(&mat); i++) {
        CList_Node_t *node = clist_node_at(&mat, i);
        clist_free(clist_node_get_type_ptr(node, CList_t*));
    }   

    clist_free(&mat);
}
