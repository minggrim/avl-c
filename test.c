#include "avl.h"
#include <stdlib.h>
#include <stdio.h>
int main(){
    avl_root_t* root = malloc(sizeof(avl_root_t));
    avl_init(root, NULL);
    avl_dump(root);
    void *a = (void*)malloc(1);
    printf("add %p\n", a);
    avl_insert(root, a);
    avl_dump(root);
    a = (void*)malloc(1);
    printf("add %p\n", a);
    avl_insert(root, (void*)malloc(1));
    avl_dump(root);
    a = (void*)malloc(1);
    printf("add %p\n", a);
    avl_insert(root, (void*)malloc(1));
    avl_dump(root);
    a = (void*)malloc(1);
    printf("add %p\n", a);
    avl_insert(root, (void*)malloc(1));
    avl_dump(root);
}
