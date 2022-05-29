#ifndef __BINARY_TREE_H__
#define __BINARY_TREE_H__

enum {
  NUMBER,
  OPERATION
};

typedef struct node {
  int type;
  double value;
  char operation;
  struct node *left;
  struct node *right;
} node_t;

node_t *create_node();
void delete_tree(node_t *node);

#endif /* #ifndef __BINARY_TREE_H__ */
