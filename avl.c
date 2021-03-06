#include "avl.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>


static void update_subtree_height(avl_node_t* node){
    if(node->right && node->left)
        node->subtree_height = 
            (node->right->subtree_height > node->left->subtree_height)?
                node->right->subtree_height + 1: node->left->subtree_height + 1;
    else if(node->right && !node->left)
        node->subtree_height = node->right->subtree_height + 1;
    else if(node->left && !node->right)
        node->subtree_height = node->left->subtree_height + 1;
    else
        node->subtree_height = 0;
}
static avl_node_t* ll_rotate(avl_node_t* root){
    //update link
    avl_node_t* lchild = root->left;
    root->left = lchild->right;
    lchild->right = root;
    //update old root subtree_height
    update_subtree_height(root);
    //update new root subtree_height
    update_subtree_height(lchild);
    return lchild;
}
static avl_node_t* rr_rotate(avl_node_t* root){
    //update link
    avl_node_t* rchild = root->right;
    root->right = rchild->left;
    rchild->left = root;
    //update old root subtree_height
    update_subtree_height(root);
    //update new root subtree_height
    update_subtree_height(rchild);
    return rchild;
}
static avl_node_t* rl_rotate(avl_node_t* root){
    avl_node_t* rchild = root->right;
    avl_node_t* rlgrand = root->right->left;
    //update link
    root->right = rlgrand->left;
    rchild->left = rlgrand->right;
    rlgrand->left = root;
    rlgrand->right = rchild;
    //update old root subtree_height
    update_subtree_height(root);
    //update rchild subtree_height
    update_subtree_height(rchild);
    //update rlgrand subtree_height
    update_subtree_height(rlgrand);
    return rlgrand;
}
static avl_node_t* lr_rotate(avl_node_t* root){
    avl_node_t* lchild = root->left;
    avl_node_t* lrgrand = root->left->right;
    root->left = lrgrand->right;
    lchild->right = lrgrand->left;
    lrgrand->right = root;
    lrgrand->left = lchild;
    //update old root subtree_height
    update_subtree_height(root);
    //update rchild subtree_height
    update_subtree_height(lchild);
    //update rlgrand subtree_height
    update_subtree_height(lrgrand);
    return lrgrand;
}

static void print_address(void *data){
    printf("address %p", data);
}

static int address_compare(void *data_l, void *data_r){
    if(data_l > data_r)
        return -1;
    else if(data_l < data_r)
        return 1;
    else
        return 0;
}

static avl_op_t op_default = {
    .ll = ll_rotate,
    .rr = rr_rotate,
    .rl = rl_rotate,
    .lr = lr_rotate,
    .compare = address_compare,
    .print_data = print_address,
};

static avl_node_t* rotate(avl_op_t *ops, avl_node_t *node){
    if(node->subtree_height >= 2){
        avl_node_t *lchild = node->left;
        avl_node_t *rchild = node->right;
        int diff = ((lchild)?lchild->subtree_height+1:0) 
                   - ((rchild)?rchild->subtree_height+1:0);
        //printf("subtree_height : %d diff : %d\n", node->subtree_height, diff);
        avl_node_t* gll;
        avl_node_t* glr;
        avl_node_t* grl;
        avl_node_t* grr;
        int child_diff;
        switch(diff){
            case 2:
                gll = lchild->left;
                glr = lchild->right;
                child_diff = ((gll)?gll->subtree_height+1:0)
                             - ((glr)?glr->subtree_height+1:0);
                switch(child_diff){
                    case 1:
                        return ops->ll(node);
                    break;
                    case 0:
                    case -1:
                        return ops->lr(node);
                    break;
                    default:
                        assert(0 && "impossible case l, must be internal error!");
                    break;
                }
            break;
            case -2:
                grl = rchild->left;
                grr = rchild->right;
                child_diff = ((grl)?grl->subtree_height+1:0)
                             - ((grr)?grr->subtree_height+1:0);
                switch(child_diff){
                    case 0:
                    case 1:
                        return ops->rl(node);
                    break;
                    case -1:
                        return ops->rr(node);
                    break;
                    default:
                        assert(0 && "impossible case r, must be internal error!");
                    break;
                }
            break;
            case 1:
            break;
            case 0:
            break;
            case -1:
            break;
            default:
                assert(0 && "impossible case, must be internal error!");
            break;
        }
    }
    return NULL;
}

static avl_node_t * insert_to_node(avl_op_t *ops, avl_node_t *node, void* data){
    int cmp = ops->compare(node->data, data);
    if(cmp > 0){
        avl_node_t *right_node = node->right;
        if(right_node){
            node->right = insert_to_node(ops, right_node, data);
            update_subtree_height(node);
            avl_node_t *new_root = rotate(ops, node);
            return (new_root)?new_root:node;
        }
        else{
            //create a leaf node and connect to parent
            avl_node_t* cnode = (avl_node_t*)calloc(1, sizeof(avl_node_t));
            cnode->data = data;
            cnode->subtree_height = 0;
            node->right = cnode;
            update_subtree_height(node);
            return node;
        }
    }
    else if (cmp < 0){
        avl_node_t *left_node = node->left;
        if(left_node){
            node->left = insert_to_node(ops, left_node, data);
            update_subtree_height(node);
            avl_node_t *new_root = rotate(ops, node);
            return (new_root)?new_root:node;
        }
        else{
            //create a leaf node and connect to parent
            avl_node_t* cnode = (avl_node_t*)calloc(1, sizeof(avl_node_t));
            cnode->data = data;
            cnode->subtree_height = 0;
            node->left = cnode;
            update_subtree_height(node);
            return node;
        }
    }
    else{
        return node;
    }
}
static void* search_under_node(avl_op_t *ops, avl_node_t *node, void* data){
    int cmp = ops->compare(node->data, data);
    if(cmp > 0){
        avl_node_t *right_node = node->right;
        if(right_node)
            return search_under_node(ops, right_node, data);
        else
            return NULL;
    }
    else if(cmp < 0){
        avl_node_t *left_node = node->left;
        if(left_node)
            return search_under_node(ops, left_node, data);
        else
            return NULL;
    }
    else
        return node->data;
}

static avl_node_t* remove_right_most_node(avl_op_t *ops, avl_node_t *node, avl_node_t **find){
    if(node){
        if(node->right){
            node->right = remove_right_most_node(ops, node->right, find);
            update_subtree_height(node);
            avl_node_t* new_root = rotate(ops, node);
            return (new_root)?new_root:node;
        }            
        else{//we are the node
            *find = node;
            return node->left;
        }
    }
    else
        return NULL;
}

static void free_under_node(avl_node_t *node){
    if(!node)
        return;
    if(node->left)
        free_under_node(node->left);
    if(node->right)
        free_under_node(node->right);
    void *data = node->data;
    free(node);
    free(data);
}

static avl_node_t* delete_under_node(avl_op_t *ops, avl_node_t *node, avl_node_t **find, void* data){
    int cmp = ops->compare(node->data, data);
    if(cmp > 0){
        avl_node_t *right_node = node->right;
        if(right_node){
            node->right = delete_under_node(ops, right_node, find, data);
            update_subtree_height(node);
            avl_node_t* new_root = rotate(ops, node);
            return (new_root)?new_root:node;
        }
        else{
            *find = NULL;
            return node;
        }
    }
    else if(cmp < 0){
        avl_node_t *left_node = node->left;
        if(left_node){
            node->left = delete_under_node(ops, left_node, find, data);
            update_subtree_height(node);
            avl_node_t* new_root = rotate(ops, node);
            return (new_root)?new_root:node;
        }
        else{
            *find = NULL;
            return node;
        }
    }
    else{//we are the deleted node
        *find = node;
        avl_node_t* find_right_most = NULL;
        avl_node_t* new_left = remove_right_most_node(ops, node->left, &find_right_most);
        
        //update_subtree_height(node);
        if(find_right_most){
            find_right_most->left = new_left;
            find_right_most->right = node->right;
            update_subtree_height(find_right_most);
            avl_node_t* new_root = rotate(ops, find_right_most);
            return (new_root)?new_root:find_right_most;
        }
        else//promote right child, no need update
            return node->right;
        
    }
}

void avl_init(avl_root_t **rootp, compare_func_t cmp, print_func_t pt){
    avl_root_t* root = calloc(1, sizeof(avl_root_t));
    root->root = NULL;
    root->ops = (avl_op_t*) calloc(1, sizeof(avl_op_t));
    pthread_rwlock_init(&root->tree_lock, NULL);
    memcpy(root->ops, &op_default, sizeof(avl_op_t));
    if(cmp)
        root->ops->compare = cmp;
    if(pt)
        root->ops->print_data = pt;
    *rootp = root;
}
void avl_insert(avl_root_t *root, void *data){
    pthread_rwlock_wrlock(&root->tree_lock);
    if(root->root){
        root->root = insert_to_node(root->ops, root->root, data);
        update_subtree_height(root->root);
    }
    else{
        root->root = (avl_node_t*) calloc(1, sizeof(avl_node_t));
        root->root->data = data;
        root->root->subtree_height = 0;
    }
    pthread_rwlock_unlock(&root->tree_lock);
}
void* avl_search(avl_root_t *root, void *data){
    pthread_rwlock_rdlock(&root->tree_lock);
    void *search = NULL;
    if(root->root)
        search = search_under_node(root->ops, root->root, data);
    pthread_rwlock_unlock(&root->tree_lock);
    return search;
}
static void print_node(avl_node_t *node, avl_op_t *ops){
    printf("[depth:%d,", node->subtree_height);
    
    if(node->right)
        printf("rdepth:%d,", node->right->subtree_height + 1);
    else
        printf("rdepth:%d,", 0);
    if(node->left)
        printf("ldepth:%d]", node->left->subtree_height + 1);
    else
        printf("ldepth:%d]", 0);

    ops->print_data(node->data);
    printf("\n");
    if(node->right)
        print_node(node->right, ops);
    if(node->left)
        print_node(node->left, ops);
}
void avl_dump(avl_root_t *root){
    pthread_rwlock_rdlock(&root->tree_lock);
    printf("dump avl tree\n");
    if (root->root){
        print_node(root->root, root->ops);
    }
    printf("end of dump\n");
    pthread_rwlock_unlock(&root->tree_lock);
}
void* avl_delete(avl_root_t *root, void *data){
    pthread_rwlock_wrlock(&root->tree_lock);
    if (root->root){
        avl_node_t* find = NULL;
        root->root = delete_under_node(root->ops, root->root, &find, data);
        pthread_rwlock_unlock(&root->tree_lock);
        if(find){
            void* data = find->data;
            free(find);
            return data;
        }
        else
            return NULL;
    }
    pthread_rwlock_unlock(&root->tree_lock);
    return NULL;
}
int avl_fini(avl_root_t *root){
    int error = pthread_rwlock_destroy(&root->tree_lock);
    if(error)
        return EZAVL_DESTROY_TREE_LOCK_FAILED;
    free_under_node(root->root);
    free(root->ops);
    free(root);
    return EZAVL_SUCCESS;
}


