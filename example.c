#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "header.h"

int main(int argc, char const *argv[]) {
    hash_table *ht = malloc(sizeof(dll_node) * TABLE_SIZE);
    int key = 5;
    info data = {.name = "John"};

    ht = m_hash_insert(ht, key, &data);
    int index = m_h(key);
    printf("index: %d", index);
    print_list((*ht)[index]);
}
