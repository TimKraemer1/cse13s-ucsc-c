#include <stdio.h>
#include <stdlib.h>

#include "node.h"

Node *node_create(uint8_t symbol, uint64_t frequency) {
    Node *n = (Node *) malloc(sizeof(Node));
    n->symbol = symbol;
    n->frequency = frequency;
    n->right = NULL;
    n->left = NULL;
    return n;
}

void node_delete(Node **n) {
    if (*n) {
        free(*n);
        *n = NULL;
    }
}

Node *node_join(Node *left, Node *right) {
    uint8_t new_frequency = left->frequency + right->frequency;
    Node *parent_node;
    parent_node = node_create(36, new_frequency);
    parent_node->left = left;
    parent_node->right = right;
    return parent_node;
}

void node_print(Node *n) {
    printf("Node's Symbol: %c Node's Frequency: %lu\n", n->symbol, n->frequency);
}
