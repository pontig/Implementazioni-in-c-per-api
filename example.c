#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "header.h"

int main(int argc, char const *argv[]) {
    tree_info ins = {.name = "test"};

    // fill a red black tree with some keys and i as info, using the rb_insert function
    // use a for loop to insert all the keys

    tree_node *root = NULL;
    for (int i = 0; i < 10; i++) {
        rb_insert(root, i, &ins);
    }
    inorder_tree_walk(root);

    return 0;
}
