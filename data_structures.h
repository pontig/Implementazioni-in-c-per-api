#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 101

typedef struct Info {
    // TODO: Add your own data members
} info;

//=============================================================
// Queue, implemented as a circular array
// Stack, implementede as an array
//=============================================================

// Typedef for the queue
typedef struct Queue {
    info data[MAX_SIZE];
    int head;
    int tail;
} queue;

// Enqueue
void enqueue(queue *q, info data) {
    q->data[q->tail] = data;
    if (q->tail == MAX_SIZE - 1) {
        q->tail = 0;
    } else {
        q->tail++;
    }
}

// Dequeue
info dequeue(queue *q) {
    info data = q->data[q->head];
    if (q->head == MAX_SIZE - 1) {
        q->head = 0;
    } else {
        q->head++;
    }
    return data;
}

// Typedef for the stack
typedef struct Stack {
    info data[MAX_SIZE];
    int top;
} stack;

// Push
void push(stack *s, info data) {
    s->data[s->top] = data;
    if (s->top == MAX_SIZE - 1) {
        printf("Stack overflow\n");
    } else {
        s->top++;
    }
}

// Pop
info pop(stack *s) {
    info data = s->data[s->top - 1];
    if (s->top == 0) {
        printf("Stack underflow\n");
    } else {
        s->top--;
    }
    return data;
}

//==================================================================
// Double Linked List
//==================================================================

// Typedef double-linked list
typedef struct dll_node {
    struct dll_node *prev;
    struct dll_node *next;
    int key;
    info *info;
} dll_node;

// List search
dll_node *dll_search(dll_node *head, int key) {
    dll_node *current = head;
    while (current != NULL) {
        if (current->key == key) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

// List insert
dll_node *dll_insert(dll_node *head, int key, info *info) {
    dll_node *new_node = (dll_node *)malloc(sizeof(dll_node));
    new_node->key = key;
    new_node->info = info;
    new_node->prev = NULL;
    new_node->next = NULL;
    if (head == NULL) {
        return new_node;
    }
    dll_node *current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = new_node;
    new_node->prev = current;
    return head;
}

// List delete
dll_node *dll_delete(dll_node *head, int key) {
    dll_node *current = head;
    while (current != NULL) {
        if (current->key == key) {
            if (current->prev != NULL) {
                current->prev->next = current->next;
            }
            if (current->next != NULL) {
                current->next->prev = current->prev;
            }
            free(current);
            return head;
        }
        current = current->next;
    }
    return head;
}

//==================================================================
// Tree
//==================================================================

// Typedef for the tree
typedef struct tree_node {
    int key;
    info *info;
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
void *tree_insert(tree_node *root, int key, info *info) {
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
    return;
}

// Tree delete
tree_node *tree_delete(tree_node *root, tree_node *elm) {
    if (elm->left == NULL || elm->right == NULL) {
        tree_node y = *elm;
    } else
        tree_node y = *tree_successor(elm);
    if (y->left != NULL) {
        tree_node *x = y->left;
    } else {
        tree_node *x = y->right;
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
    free(elm);
    return y;
}

//==================================================================
// Red-Black Tree
//==================================================================

// Typedef enum red,black
typedef enum {
    RED,
    BLACK
} color;

// Typedef red-black tree node
typedef struct rb_node {
    struct rb_node *left;
    struct rb_node *right;
    struct rb_node *parent;
    int key;
    info *info;
    color color;
} rb_node;

// Rotations
void *left_rotate(rb_node *root, rb_node *x) {
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

void *right_rotate(rb_node *root, rb_node *y) {
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
void *rb_fixup(rb_node *root, rb_node *elm) {
    if (elm->parent == NULL) {
        elm->color = BLACK;
    } else {
        rb_node *father = elm->parent;
        if (father->color == RED) {
            if (father == elm->parent->left) {
                rb_node *uncle = elm->parent->right;
                if (uncle->color == RED) {
                    father->color = BLACK;
                    uncle->color = BLACK;
                    father->parent->color = RED;
                    rb_fixup(root, elm->parent);
                } else {
                    if (elm == father->right) {
                        elm = parent
                        left_rotate(root, elm->parent);
                        parent = elm->parent;
                    }
                    father->color = BLACK;
                    father->parent->color = RED;
                    right_rotate(root, father->parent);
                }
            } else {
                rb_node *uncle = elm->parent->left;
                if (uncle->color == RED) {
                    father->color = BLACK;
                    uncle->color = BLACK;
                    father->parent->color = RED;
                    rb_fixup(root, elm->parent);
                } else {
                    if (elm == father->left) {
                        elm = parent
                        right_rotate(root, elm->parent);
                        parent = elm->parent;
                    }
                    father->color = BLACK;
                    father->parent->color = RED;
                    left_rotate(root, father->parent);
                }
            }
        }
    }
}