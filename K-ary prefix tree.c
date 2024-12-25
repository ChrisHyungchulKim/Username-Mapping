/*
 * This file implements a k-ary prefix tree (trie) for mapping usernames to user IDs.
 * Each node represents a character, and paths from the root to a node represent usernames.
 * The tree uses linked lists to store child nodes, sorted in ascending order by character.
 */

#include "hw11.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/* Creates and initializes a new prefix tree. */
tree_node_t *create_prefix_tree(void) {
    tree_node_t *root = (tree_node_t *)malloc(sizeof(tree_node_t));
    if (root != NULL) {
        root->user_id = -1;
        root->children = NULL;
    }
    return root;
} /* create_prefix_tree() */

/* Inserts a username and user ID into the prefix tree. */
int insert_user(tree_node_t *root, const char *username, int user_id) {
    assert(root != NULL && username != NULL && user_id >= 0);

    int length = strlen(username);
    for (int i = 0; i < length; ++i) {
        char c = username[i];
        if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'))) {
            return INVALID_USERNAME;
        }
    }

    tree_node_t *current_node = root;
    for (int i = 0; i < length; ++i) {
        char c = username[i];
        list_node_t *prev = NULL, *current = current_node->children, *new_list_node = NULL;
        tree_node_t *new_tree_node = NULL;

        while (current != NULL && current->c < c) {
            prev = current;
            current = current->next;
        }

        if (current != NULL && current->c == c) {
            current_node = current->child;
        } else {
            new_list_node = (list_node_t *)malloc(sizeof(list_node_t));
            if (new_list_node == NULL) return NOT_FOUND;

            new_tree_node = (tree_node_t *)malloc(sizeof(tree_node_t));
            if (new_tree_node == NULL) {
                free(new_list_node);
                return NOT_FOUND;
            }

            new_list_node->c = c;
            new_list_node->next = current;
            new_list_node->child = new_tree_node;

            new_tree_node->user_id = -1;
            new_tree_node->children = NULL;

            if (prev == NULL) {
                current_node->children = new_list_node;
            } else {
                prev->next = new_list_node;
            }
            current_node = new_tree_node;
        }
    }

    if (current_node->user_id != -1) return ALREADY_EXISTS;

    current_node->user_id = user_id;
    return OK;
} /* insert_user() */

/* Retrieves the user ID for a given username. */
int get_user_id(tree_node_t *root, const char *username) {
    assert(root != NULL && username != NULL);

    int length = strlen(username);
    for (int i = 0; i < length; ++i) {
        char c = username[i];
        if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'))) {
            return INVALID_USERNAME;
        }
    }

    tree_node_t *current_node = root;
    for (int i = 0; i < length; ++i) {
        char c = username[i];
        list_node_t *current = current_node->children;

        while (current != NULL && current->c < c) {
            current = current->next;
        }

        if (current != NULL && current->c == c) {
            current_node = current->child;
        } else {
            return NOT_FOUND;
        }
    }

    return current_node->user_id != -1 ? current_node->user_id : NOT_FOUND;
} /* get_user_id() */

/* Deletes the user ID associated with a username, setting it to -1. */
int delete_user(tree_node_t *root, const char *username) {
    assert(root != NULL && username != NULL);

    int length = strlen(username);
    for (int i = 0; i < length; ++i) {
        char c = username[i];
        if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'))) {
            return INVALID_USERNAME;
        }
    }

    tree_node_t *current_node = root;
    for (int i = 0; i < length; ++i) {
        char c = username[i];
        list_node_t *current = current_node->children;

        while (current != NULL && current->c < c) {
            current = current->next;
        }

        if (current != NULL && current->c == c) {
            current_node = current->child;
        } else {
            return NOT_FOUND;
        }
    }

    if (current_node->user_id == -1) return NOT_FOUND;

    current_node->user_id = -1;
    return OK;
} /* delete_user() */

/* Deletes the entire prefix tree and deallocates memory. */
void delete_tree(tree_node_t **root) {
    assert(root != NULL && *root != NULL);

    if (*root != NULL) {
        list_node_t *current = (*root)->children, *next = NULL;

        while (current != NULL) {
            next = current->next;
            if (current->child != NULL) {
                delete_tree(&current->child);
            }
            free(current);
            current = next;
        }

        free(*root);
        *root = NULL;
    }
} /* delete_tree() */

/* Debugging function to print the tree for visualization (optional). */
void print_tree(tree_node_t *root, char *buffer, int depth) {
    if (root == NULL) return;

    if (root->user_id != -1) {
        buffer[depth] = '\0';
        printf("Username: %s, User ID: %d\n", buffer, root->user_id);
    }

    list_node_t *current = root->children;
    while (current != NULL) {
        buffer[depth] = current->c;
        print_tree(current->child, buffer, depth + 1);
        current = current->next;
    }
} /* print_tree() */
