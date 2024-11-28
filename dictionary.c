#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ArvoreBinaria.h"

typedef struct Node {
    char us[46];
    char pt[46];
    struct Node* left;
    struct Node* right;
} Node;

Node* create_node(char* us, char* pt) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node) {
        strcpy(new_node->us, us);
        strcpy(new_node->pt, pt);
        new_node->left = new_node->right = NULL;
    }
    return new_node;
}

Node* insert(Node* root, char* us, char* pt, int (*compara)(char*, char*)) {
    if (root == NULL) {
        return create_node(us, pt);
    }
    if (compara == compara_us) {
        if (compara(us, root->us) < 0) {
            root->left = insert(root->left, us, pt, compara);
        } else if (compara(us, root->us) > 0) {
            root->right = insert(root->right, us, pt, compara);
        }
    } else {
        if (compara(pt, root->pt) < 0) {
            root->left = insert(root->left, us, pt, compara);
        } else if (compara(pt, root->pt) > 0) {
            root->right = insert(root->right, us, pt, compara);
        }
    }
    return root;
}

char* search(Node* root, char* key, int (*compara)(char*, char*)) {
    if (root == NULL) {
        return NULL;
    }
    int cmp;
    if (compara == compara_us) {
        cmp = compara(key, root->us);
        if (cmp == 0) {
            return root->pt;
        }
    } else {
        cmp = compara(key, root->pt);
        if (cmp == 0) {
            return root->us;
        }
    }
    if (cmp < 0) {
        return search(root->left, key, compara);
    } else {
        return search(root->right, key, compara);
    }
}

void free_tree(Node* root) {
    if (root) {
        free_tree(root->left);
        free_tree(root->right);
        free(root);
    }
}

void load_dictionary(Node** us_tree, Node** pt_tree) {
    FILE* file = fopen("dict.txt", "r");
    if (!file) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    char line[100];
    while (fgets(line, sizeof(line), file)) {
        if (line[0] == '#') break;
        line[strcspn(line, "\n")] = '\0'; // Remove newline
        char* us = strtok(line, ",");
        char* pt = strtok(NULL, ",");
        if (us && pt) {
            *us_tree = insert(*us_tree, us, pt, compara_us);
            *pt_tree = insert(*pt_tree, us, pt, compara_pt);
        }
    }
    fclose(file);
}

void translate(Node* root, int (*compara)(char*, char*)) {
    char line[100];
    while (fgets(line, sizeof(line), stdin)) {
        if (line[0] == '#') break;
        line[strcspn(line, "\n")] = '\0'; // Remove newline
        char* word = strtok(line, ",");
        while (word) {
            // Trim whitespace
            while (*word == ' ') word++;
            char* end = word + strlen(word) - 1;
            while (end > word && (*end == ' ')) {
                *end = '\0';
                end--;
            }
            char* translation = search(root, word, compara);
            if (translation) {
                printf("%s\n", translation);
            } else {
                printf("Não encontrada\n");
            }
            word = strtok(NULL, ",");
        }
    }
    printf("#\n");
}

int main() {
    Node* us_tree = NULL;
    Node* pt_tree = NULL;
    load_dictionary(&us_tree, &pt_tree);

    char direction[10];
    fgets(direction, sizeof(direction), stdin);
    direction[strcspn(direction, "\n")] = '\0'; // Remove newline

    if (strncmp(direction, "USPT", 4) == 0) {
        translate(us_tree, compara_us);
    } else if (strncmp(direction, "PTUS", 4) == 0) {
        translate(pt_tree, compara_pt);
    }

    free_tree(us_tree);
    free_tree(pt_tree);
    return 0;
}