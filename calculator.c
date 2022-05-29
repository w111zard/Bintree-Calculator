#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "calculator.h"
#include "binary_tree.h"

static node_t *create_tree(char *beg, char *end);
static double calculate_node(node_t *node);
static char *find_lowest_operation(char *beg, char *end);
static int is_digit(char symbol);
static int operation_priority(char operation);
static int is_operation(char operation);

double calculate(char *expression) {
  char *beg = expression;
  char *end = beg + strlen(expression) - 1;
  node_t *tree = create_tree(beg, end);
  double result = calculate_node(tree);
  delete_tree(tree);
  return result;
}

static node_t *create_tree(char *beg, char *end) {
  node_t *node = create_node();
  
  char *lowest_operation = find_lowest_operation(beg, end);
  if (lowest_operation == NULL) {
    node->type = NUMBER;
    while (! is_digit(*beg)) {
      ++beg;
    }
    node->value = strtod(beg, NULL);
    return node;
  }
  else {
    node->type = OPERATION;
    node->operation = *lowest_operation;
    node->left = create_tree(beg, lowest_operation - 1);
    node->right = create_tree(lowest_operation + 1, end);
    return node;
  }
}

static double calculate_node(node_t *node) {
  if (node->type == OPERATION) {
    switch (node->operation) {
    case '+':
      return calculate_node(node->left) + calculate_node(node->right);
    case '-':
      return calculate_node(node->left) - calculate_node(node->right);
    case '*':
      return calculate_node(node->left) * calculate_node(node->right);
    case '/':
      if (calculate_node(node->right) == 0) {
	dprintf(2, "[!] Program has stoped! Detected division by zero!\n");
	exit(EXIT_FAILURE);
      }
      return calculate_node(node->left) / calculate_node(node->right);
    }
  }
  return node->value;
}

static char *find_lowest_operation(char *beg, char *end) {
  char *lowest_operation = end;
  int lowest_nesting_level = 0;

  while ((lowest_operation > beg) && (!is_operation(*lowest_operation))) {
    if (*lowest_operation == '(')
      --lowest_nesting_level;
    else if (*lowest_operation == ')')
      ++lowest_nesting_level;
    --lowest_operation;
  }
  
  if (lowest_operation == beg) {
    return NULL; // there are no operations in beg
  }

  int nesting_level = lowest_nesting_level;
  for (char *elem = lowest_operation - 1; elem > beg; --elem) {
    if (is_operation(*elem)) {
      if (nesting_level < lowest_nesting_level) {
	// we have found an operation with a lower proirity
	lowest_operation = elem;
	lowest_nesting_level = nesting_level;
      }
      else if ((nesting_level == lowest_nesting_level) && (operation_priority(*elem) < operation_priority(*lowest_operation))) {
	// we have found an operation with a lower proirity
	lowest_operation = elem;
	lowest_nesting_level = nesting_level;
      }
    }
    else {
      if (*elem == '(')
	--nesting_level;
      else if (*elem == ')')
	++nesting_level;
    }
  }

  return lowest_operation;
}

static int is_digit(char symbol) {
  return (symbol >= '0') && (symbol <= '9');
}

static int operation_priority(char operation) {
  if ((operation == '+') || (operation == '-'))
    return 1;
  else
    return 2;
}

static int is_operation(char operation) {
  switch (operation) {
  case '+':
  case '-':
  case '*':
  case '/':
    return 1;
    
  default:
    return 0;
  }
}
