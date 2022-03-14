#ifndef __PACKING_H__
#define __PACKING_H__
#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

typedef struct _TreeNode {
    int label;
    int width;
    int height;
    char packingType;
    int x;
    int y;
    struct _TreeNode* left;
    struct _TreeNode* right;
} TreeNode;

typedef struct _StackItem {
    TreeNode* node;
    struct _StackItem* next;
} StackItem;

TreeNode* readInputFile(char* filename);
int isLeaf(TreeNode* tree);
int getTreeSize(TreeNode* tree, int current);
void freeTree(TreeNode* tree);

TreeNode* createNodeFromLine(char* line);
void push(StackItem** head, TreeNode* node);
TreeNode* pop(StackItem** head);
void buildTree(StackItem** stack, TreeNode** tree);
void preorderOutput(FILE* file, TreeNode* tree);
void calcDimensions(TreeNode* tree);
void dimensionsOutput(FILE* file, TreeNode* tree);

// Calculates all the x, y coordinates within tree
void calculateCoordinates(TreeNode* tree);
// Main idea:
// - write a recursive function to update each tree node's coordinates
// - if the current node is an H, need to add the right node's height to all the
//   y coordinates of the nodes on the left
// - recurse into the left and right sides
// - once that's working, do something similar for x coordinates

// Adds x, y to all the nodes within tree
void addCoordinates(TreeNode* tree, int x, int y);
// Write the coordinate output to file
void coordinatesOutput(FILE* file, TreeNode* tree);

#endif
