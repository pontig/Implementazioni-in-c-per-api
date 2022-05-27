#include <stdio.h>
#include <stdlib.h>

typedef struct t_Info {
    char name[10];
    // TODO: Add your own data members
} tree_info;

//==================================================================
// Tree
//==================================================================

// Typedef for the tree
typedef struct tree_node {
    int key;
    tree_info *info;
    struct tree_node *left;
    struct tree_node *right;
    struct tree_node *parent;
} tree_node;

// Inorder tree walk
void inorder_tree_walk(tree_node *root) {
    if (root == NULL) {
        return;
    }
    inorder_tree_walk(root->left);
    printf("%d ", root->key);
    inorder_tree_walk(root->right);
}

// Tree search
tree_node *tree_search(tree_node *root, int key) {
    if (root == NULL) {
        return NULL;
    }
    if (root->key == key) {
        return root;
    }
    if (key < root->key) {
        return tree_search(root->left, key);
    } else {
        return tree_search(root->right, key);
    }
}

// Tree minimum and maximum
tree_node *tree_minimum(tree_node *root) {
    if (root == NULL) {
        return NULL;
    }
    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}

tree_node *tree_maximum(tree_node *root) {
    if (root == NULL) {
        return NULL;
    }
    while (root->right != NULL) {
        root = root->right;
    }
    return root;
}

// Tree successor and predecessor
tree_node *tree_successor(tree_node *root) {
    if (root == NULL) {
        return NULL;
    }
    if (root->right != NULL) {
        return tree_minimum(root->right);
    }
    tree_node *current = root->parent;
    while (current != NULL && root == current->right) {
        root = current;
        current = current->parent;
    }
    return current;
}

tree_node *tree_predecessor(tree_node *root) {
    if (root == NULL) {
        return NULL;
    }
    if (root->left != NULL) {
        return tree_maximum(root->left);
    }
    tree_node *current = root->parent;
    while (current != NULL && root == current->left) {
        root = current;
        current = current->parent;
    }
    return current;
}

// Tree insert
tree_node *tree_insert(tree_node *root, int key, tree_info *info) {
    if (root == NULL) {
        tree_node *new_node = (tree_node *)malloc(sizeof(tree_node));
        new_node->key = key;
        new_node->info = info;
        new_node->left = NULL;
        new_node->right = NULL;
        new_node->parent = NULL;
        return new_node;
    }
    if (key < root->key) {
        root->left = tree_insert(root->left, key, info);
        root->left->parent = root;
    } else {
        root->right = tree_insert(root->right, key, info);
        root->right->parent = root;
    }
    return root;
}

// Function to print binary tree in 2D
// It does reverse inorder traversal
void print2DUtil(tree_node *root, int space) {
    // Base case
    if (root == NULL)
        return;

    // Increase distance between levels
    space += 10;

    // Process right child first
    print2DUtil(root->right, space);

    // Print current node after space
    // count
    printf("\n");
    for (int i = 10; i < space; i++)
        printf(" ");
    printf("%d\n", root->key);

    // Process left child
    print2DUtil(root->left, space);
}

// Wrapper over print2DUtil()
void print2D(tree_node *root) {
    // Pass initial space count as 0
    print2DUtil(root, 0);
}

// Tree delete
tree_node *tree_delete(tree_node *root, tree_node *elm) {
    tree_node *y, *x;
    if (elm->left == NULL || elm->right == NULL) {
        y = elm;
    } else {
        y = tree_successor(elm);
    }
    if (y->left != NULL) {
        x = y->left;
    } else {
        x = y->right;
    }
    if (x != NULL) {
        x->parent = y->parent;
    }
    if (y->parent == NULL) {
        root = x;
    } else if (y == y->parent->left) {
        y->parent->left = x;
    } else {
        y->parent->right = x;
    }

    if (y != elm) {
        elm->key = y->key;
        elm->info = y->info;
    }
    return y;
}

//==================================================================
// Red-Black Tree
//==================================================================

// Typedef enum red, black
typedef enum {
    RED,
    BLACK
} rb_color;

// Typedef red-black tree node
typedef struct rb_node {
    struct rb_node *left;
    struct rb_node *right;
    struct rb_node *parent;
    int key;
    info *info;
    rb_color color;
} rb_node;

// Rotations
void left_rotate(rb_node *root, rb_node *x) {
    rb_node *y = x->right;
    x->right = y->left;
    if (y->left != NULL) {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == NULL) {
        root = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
    return;
}

void right_rotate(rb_node *root, rb_node *y) {
    rb_node *x = y->left;
    y->left = x->right;
    if (x->right != NULL) {
        x->right->parent = y;
    }
    x->parent = y->parent;
    if (y->parent == NULL) {
        root = x;
    } else if (y == y->parent->left) {
        y->parent->left = x;
    } else {
        y->parent->right = x;
    }
    x->right = y;
    y->parent = x;
    return;
}

// Red-Black tree fixup
void rb_insert_fixup(rb_node *root, rb_node *elm) {
    if (elm->parent == NULL) {
        elm->color = BLACK;
    } else {
        rb_node *father = elm->parent;
        if (father->color == RED) {
            if (father == father->parent->left) {
                rb_node *brother = elm->parent->right;
                if (brother->color == RED) {
                    father->color = BLACK;
                    brother->color = BLACK;
                    father->parent->color = RED;
                    rb_insert_fixup(root, elm->parent);
                } else {
                    if (elm == father->right) {
                        elm = father;
                        left_rotate(root, elm);
                        father = elm->parent;
                    }
                    father->color = BLACK;
                    father->parent->color = RED;
                    right_rotate(root, father->parent);
                }
            } else {
                rb_node *brother = elm->parent->left;
                if (brother->color == RED) {
                    father->color = BLACK;
                    brother->color = BLACK;
                    father->parent->color = RED;
                    rb_insert_fixup(root, elm->parent);
                } else {
                    if (elm == father->left) {
                        elm = father;
                        right_rotate(root, elm);
                        father = elm->parent;
                    }
                    father->color = BLACK;
                    father->parent->color = RED;
                    left_rotate(root, father->parent);
                }
            }
        }
    }
}

// Red-Black tree insert
void rb_insert(rb_node *root, int key, info *info) {
    rb_node *parent = NULL;
    rb_node *current = root;
    while (current != NULL) {
        parent = current;
        if (key < current->key) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    rb_node *new_node = (rb_node *)malloc(sizeof(rb_node));
    new_node->key = key;
    new_node->info = info;
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->parent = parent;
    new_node->color = RED;
    if (parent == NULL) {
        root = new_node;
    } else if (key < parent->key) {
        parent->left = new_node;
    } else {
        parent->right = new_node;
    }
    rb_insert_fixup(root, new_node);
    return;
}

// Red-Black tree delete fixup
void rb_delete_fixup(rb_node *root, rb_node *elm) {
    if (elm->color == RED || elm->parent == NULL) {
        elm->color = BLACK;
    } else if (elm == elm->parent->left) {
        rb_node *brother = elm->parent->right;
        if (brother->color == RED) {
            brother->color = BLACK;
            elm->parent->color = RED;
            left_rotate(root, elm->parent);
            brother = elm->parent->right;
        }
        if (brother->left->color == BLACK && brother->right->color == BLACK) {
            brother->color = RED;
            rb_delete_fixup(root, elm->parent);
        } else {
            if (brother->right->color == BLACK) {
                brother->left->color = BLACK;
                brother->color = RED;
                right_rotate(root, brother);
                brother = elm->parent->right;
            }
            brother->color = elm->parent->color;
            elm->parent->color = BLACK;
            brother->right->color = BLACK;
            left_rotate(root, elm->parent);
        }
    } else {
        rb_node *brother = elm->parent->left;
        if (brother->color == RED) {
            brother->color = BLACK;
            elm->parent->color = RED;
            right_rotate(root, elm->parent);
            brother = elm->parent->left;
        }
        if (brother->right->color == BLACK && brother->left->color == BLACK) {
            brother->color = RED;
            rb_delete_fixup(root, elm->parent);
        } else {
            if (brother->left->color == BLACK) {
                brother->right->color = BLACK;
                brother->color = RED;
                left_rotate(root, brother);
                brother = elm->parent->left;
            }
            brother->color = elm->parent->color;
            elm->parent->color = BLACK;
            brother->left->color = BLACK;
            right_rotate(root, elm->parent);
        }
    }
}

// Red-Black tree delete
rb_node *rb_delete(rb_node *root, rb_node *elm) {
    rb_node *succ = (elm->left == NULL || elm->right == NULL) ? elm : tree_successor(elm);
    rb_node *child = (succ->left == NULL) ? succ->right : succ->left;

    child->parent = succ->parent;
    if (succ->parent == NULL) {
        root = child;
    } else if (succ == succ->parent->left) {
        succ->parent->left = child;
    } else {
        succ->parent->right = child;
    }
    if (succ != elm) {
        elm->key = succ->key;
        elm->info = succ->info;
    }
    if (succ->color == BLACK) {
        rb_delete_fixup(root, child);
    }
    return succ;
}