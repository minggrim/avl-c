#include "avl.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
typedef struct {
    int key;
} my_data_t;
int my_compare(void *A, void *B){
    my_data_t * a_cast = (my_data_t*) A;
    my_data_t * b_cast = (my_data_t*) B;
    if(a_cast->key < b_cast->key)
        return 1;
    else if(a_cast->key > b_cast->key)
        return -1;
    else
        return 0;
}
void my_print(void *data){
    my_data_t * data_cast = (my_data_t*) data;
    printf("key %d", data_cast->key);
}
int main(){
    avl_root_t* root;
    avl_init(&root, my_compare, my_print);
    my_data_t* a;
    my_data_t* keep;
    for(int i = 1; i <= 10000000; i++){
        a = (my_data_t *)calloc(1, sizeof(my_data_t));
        a->key = i;
        avl_insert(root, a);
    }
    for(int i = 10000000; i >= 1; i--){
        a = (my_data_t *)calloc(1, sizeof(my_data_t));
        a->key = i;
        void *d = avl_delete(root, a);
        free(d);
        free(a);
        assert(d);
    }
    avl_fini(root);
}
