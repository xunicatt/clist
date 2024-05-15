#include <stdio.h>
#include <clist.h>

int main(void) {
    CList_t clist;

    clist_init(&clist, sizeof(int));

    for(int i = 1; i <= 10; i++) {
        int val = i * 2;
        clist_insert_at(&clist, &val, i - 1);
    }

    for(CList_Node_t *n = clist_begin(&clist); n != clist_end(&clist); n = clist_next(n)) {
        int val = clist_node_unwrap_safe_as(n, int, -1);
        printf("%d\n", val);
    }

    clist_free(&clist);
    return 0;
}