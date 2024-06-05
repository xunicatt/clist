#include <stdio.h>
#include <clist.h>

int main(void) {
    clist_t *list = clist_init_t(int);
    if(list == NULL) {
        printf("failed to initialize list\n");
        exit(1);
    }

    size_t size = 0;
    clist_error_t err;

    printf("Enter a size: ");
    scanf("%zd", &size);

    for(int i = 0; i < size; i++) {
        int x;
        printf("Element[%d]: ", i);
        scanf("%d", &x);
        
        err = clist_insert_at(list, &x, i);
        if(err != CLIST_SUCCESS) {
            printf("failed: %s\n", clist_get_error_info(err));
            clist_free(list);
            exit(1);
        }
    }

    clist_node_t *n = NULL;
    clist_for_each(list, n) {
        printf("%d ", clist_node_unwrap_unsafe_as(n, int));
    }

    clist_free(list);
}