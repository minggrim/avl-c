#ifndef _EZAVL_H
#define _EZAVL_H
#include <pthread.h>
typedef struct avl_op avl_op_t;
typedef struct avl_node avl_node_t;
typedef struct avl_root avl_root_t;
typedef int (*compare_func_t) (void *, void*);
typedef void (*print_func_t) (void *);
typedef avl_node_t* (*ll_func_t) (avl_node_t*);
typedef avl_node_t* (*rr_func_t) (avl_node_t*);
typedef avl_node_t* (*rl_func_t) (avl_node_t*);
typedef avl_node_t* (*lr_func_t) (avl_node_t*);

typedef enum {
    EZAVL_SUCCESS   =   0,
    EZAVL_DESTROY_TREE_LOCK_FAILED,
}avl_error_t;

struct avl_op{
    compare_func_t compare;
    print_func_t print_data;
    ll_func_t ll;
    rr_func_t rr;
    rl_func_t rl;
    lr_func_t lr;
};

struct avl_node{
    void *data;
    int subtree_height;
//    avl_node_t *parent;
    avl_node_t *left;
    avl_node_t *right;
};

struct avl_root{
    avl_node_t *root;
    avl_op_t *ops;
    pthread_rwlock_t tree_lock;
};

extern void avl_init(avl_root_t **root, compare_func_t cmp, print_func_t pt);
extern void avl_insert(avl_root_t *root, void *data);
extern void* avl_search(avl_root_t *root, void *data);
extern void* avl_delete(avl_root_t *root, void *data);
extern void avl_dump(avl_root_t *root);
extern int avl_fini(avl_root_t *root);
#endif
