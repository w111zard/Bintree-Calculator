#include <stdlib.h>

#include "binary_tree.h"

node_t *create_node() {
  node_t *node = (node_t *) malloc(sizeof(node_t));
  node->left = NULL;
  node->right = NULL;
  return node;
}

void delete_tree(node_t *node) {
  if (node != NULL) {
    delete_tree(node->left);
    delete_tree(node->right);
    free(node);
  }
}
