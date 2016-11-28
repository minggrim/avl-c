typedef struct avl_op avl_op_t;
typedef struct avl_node avl_node_t;
typedef struct avl_root_t avl_root_t;
typedef int (*compare_func_t) (void *, void*);
typedef int (*ll_func_t) (avl_node_t*);
typedef int (*rr_func_t) (avl_node_t*);
typedef int (*rl_func_t) (avl_node_t*);
typedef int (*lr_func_t) (avl_node_t*);

struct avl_op{
    compare_func_t compare;
    ll_func_t ll;
    rr_func_t rr;
    rl_func_t rl;
    lr_func_t lr;
};

struct avl_node{
    void *data;
    unsigned int subtree_height;
    avl_node_t *parent;
    avl_node_t *left;
    avl_node_t *right;
};

struct avl_root{
    avl_node_t *root;
    avl_op_t *ops;
};

void avl_init(avl_root_t *root);
void avl_insert(avl_root_t *root, void *data);
void avl_delete(avl_root_t *root, void *data);
void avl_fini(avl_root_t *root);
