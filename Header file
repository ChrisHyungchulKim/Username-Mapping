#ifndef HW11_H
#define HW11_H

#include <stddef.h>

/* Error Codes */
#define OK 0
#define ALREADY_EXISTS -1
#define INVALID_USERNAME -2
#define NOT_FOUND -3

/* Structures */
typedef struct list_node {
    char c;
    struct tree_node *child;
    struct list_node *next;
} list_node_t;

typedef struct tree_node {
    int user_id; /* User ID (-1 if not an end of username) */
    list_node_t *children; /* Linked list of children */
} tree_node_t;

/* Function Prototypes */
tree_node_t *create_prefix_tree(void);
int insert_user(tree_node_t *root, const char *username, int user_id);
int get_user_id(tree_node_t *root, const char *username);
int delete_user(tree_node_t *root, const char *username);
void delete_tree(tree_node_t **root);

#endif /* HW11_H */
