#include "avl.h"


void avl_init(avl_root_t *root){
}
void avl_insert(avl_root_t *root, void *data){
}
void avl_delete(avl_root_t *root, void *data){
}
void avl_fini(avl_root_t *root){
}

static int ll_rotate(avl_node_t* node){
}
static int rr_rotate(avl_node_t* node){
}
static int rl_rotate(avl_node_t* node){
}
static int lr_rotate(avl_node_t* node){
}
static int compare(void *data_l, void *data_r){
}

static avl_op_t op_default = {
    .ll = ll_rotate,
    .rr = rr_rotate,
    .rl = rl_rotate,
    .lr = lr_rotate,
    .compare = compare,
};
