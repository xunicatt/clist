#include <stdio.h>
#include <clist.h>

int main(void) {
    CList_t clist;
    CList_Error_t err;

    clist_init_type(&clist, int, err);

    for(int i = 1; i <= 10; i++)
        clist_insert_at_val(&clist, int, i*2, i-1, err);

    CList_Node_t *n;
    clist_for_each(&clist, n)
        printf("%d\n", clist_node_unwrap_safe_as(n, int, -1));

    clist_free(&clist);
    return 0;
}