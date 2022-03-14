#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "packing.h"

/* static void printTree(TreeNode* tree, int level) {
    if (tree != NULL) {
        for (int i=0; i<level; i++) {
            printf(i==level-1 ? "|-" : "  ");
        }
        if (isLeaf(tree)) {
            printf("%d((%d, %d)(%d,%d))\n", tree->label,
                    tree->width, tree->height, tree->x, tree->y);
        }
        else {
            printf("-%c(%d, %d)\n", tree->packingType, tree->width, tree->height);
        }
        printTree(tree->left, level+1);
        printTree(tree->right, level+1);
    }
} */

TreeNode* readInputFile(char* filename) {
    FILE* fp = fopen(filename, "r");
    char line[80];
    TreeNode* node;
    TreeNode* tree = NULL;
    StackItem* stack = NULL;

    if (fp == NULL) {
        return NULL;
    }
    while (fgets(line, 80, fp) != NULL) {
        printf("%s", line);
        fflush(stdout);
        node = createNodeFromLine(line);
        push(&stack, node);
    }
    buildTree(&stack, &tree);
    fclose(fp);

    return tree;
}

int isLeaf(TreeNode* tree) {
    return (tree->left == NULL && tree->right == NULL);
}

int getTreeSize(TreeNode* tree, int current) {
    if (tree == NULL) {
        return 0;
    }
    int leftSize = getTreeSize(tree->left, current);
    int rightSize = getTreeSize(tree->right, current);
    return leftSize + rightSize + 1;
}

void freeTree(TreeNode* tree) {
    if (tree->left != NULL) {
        freeTree(tree->left);
    }
    if (tree->right != NULL) {
        freeTree(tree->right);
    }
    free(tree);
}

TreeNode* createNodeFromLine(char* line) {
    TreeNode* node = calloc(sizeof(TreeNode), 1);
    char delim[] = ",()";
    char* ptr = strtok(line, delim);
    if (*ptr == 'H' || *ptr == 'V') {
        node->packingType = *ptr;
    }
    else {
        node->label = atoi(ptr);
        ptr = strtok(NULL, delim);
        node->width = atoi(ptr);
        ptr = strtok(NULL, delim);
        node->height = atoi(ptr);
    }
    return node;
}

void push(StackItem** head, TreeNode* node) {
    StackItem* item = calloc(sizeof(StackItem), 1);
    item->node = node;
    item->next = *head;
    (*head) = item;
}

TreeNode* pop(StackItem** head) {
    StackItem* item = (*head);
    if (item == NULL) {
        return NULL;
    }
    TreeNode* node = item->node;
    StackItem* next = item->next;
    free(item);
    (*head) = next;
    return node;
}

void buildTree(StackItem** stack, TreeNode** tree) {
    TreeNode* node = pop(stack);
    if (node == NULL) {
        return;
    }
    (*tree) = node;
    if (node->packingType == 'H' || node->packingType == 'V') {
        buildTree(stack, &((*tree)->right));
        buildTree(stack, &((*tree)->left));
    }
}

void preorderOutput(FILE* file, TreeNode* tree) {
    if (isLeaf(tree)) {
        fprintf(file, "%d(%d,%d)\n", tree->label, tree->width, tree->height);
    }
    else {
        fprintf(file, "%c\n", tree->packingType);
        preorderOutput(file, tree->left);
        preorderOutput(file, tree->right);
    }
}

void calcDimensions(TreeNode* tree) {
    if (isLeaf(tree)) {
        return;
    }
    calcDimensions(tree->left);
    calcDimensions(tree->right);
    if (tree->packingType == 'H') {
        tree->height = tree->left->height + tree->right->height;
        tree->width = MAX(tree->left->width, tree->right->width);
    } 
    else if (tree->packingType == 'V') {
        tree->height = MAX(tree->left->height, tree->right->height);
        tree->width = tree->left->width + tree->right->width;
    }
}

void dimensionsOutput(FILE* file, TreeNode* tree) {
    // printTree(tree, 0);
    if (tree == NULL) {
        return;
    }
    dimensionsOutput(file, tree->left);
    dimensionsOutput(file, tree->right);
    if (isLeaf(tree)) {
        fprintf(file, "%d(%d,%d)\n", tree->label, tree->width, tree->height);
    }
    else {
        fprintf(file, "%c(%d,%d)\n", tree->packingType, tree->width, tree->height);
    }
}

void calculateCoordinates(TreeNode* tree) {
    if (tree == NULL) {
        return;
    }
    if (tree->packingType == 'H') {
        addCoordinates(tree->left, 0, tree->right->height);
    } 
    else if (tree->packingType == 'V') {
        addCoordinates(tree->right, tree->left->width, 0);
    }
    calculateCoordinates(tree->left);
    calculateCoordinates(tree->right);
}

void addCoordinates(TreeNode* tree, int x, int y) {
    if (tree == NULL) {
        return;
    }
    tree->x += x;
    tree->y += y;
    addCoordinates(tree->left, x, y);
    addCoordinates(tree->right, x, y);
}

void coordinatesOutput(FILE* file, TreeNode* tree) {
    if (tree == NULL) {
        return;
    }
    coordinatesOutput(file, tree->left);
    coordinatesOutput(file, tree->right);
    if (isLeaf(tree)) {
        fprintf(file, "%d((%d,%d)(%d,%d))\n", tree->label, tree->width,
                tree->height, tree->x, tree->y);
    }
    //printTree(tree, 0);
}
