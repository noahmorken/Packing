#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "packing.h"

TreeNode* tree;

int main(int argc, char *argv[]) {
    // Check the args
    if (argc != 5) {
        printf("Usage: %s <in_file> <out_file1> <out_file2> <out_file3>\n", argv[0]);
        return EXIT_FAILURE;
    }

    tree = readInputFile(argv[1]);
    if (tree == NULL) {
        printf("Error reading input file.%s\n", argv[1]);
       return EXIT_FAILURE;
    }

    FILE* fp1 = fopen(argv[2], "w");
    if (fp1 == NULL) {
        printf("Failed to write first output file.\n");
        freeTree(tree);
        return EXIT_FAILURE;
    }
    preorderOutput(fp1, tree);
    fclose(fp1);

    FILE* fp2 = fopen(argv[3], "w");
    if (fp2 == NULL) {
        printf("Failed to write second output file.\n");
        freeTree(tree);
        return EXIT_FAILURE;
    }
    calcDimensions(tree);
    dimensionsOutput(fp2, tree);
    fclose(fp2);

    FILE* fp3 = fopen(argv[4], "w");
    if (fp3 == NULL) {
        printf("Failed to write third output file.\n");
        freeTree(tree);
        return EXIT_FAILURE;
    }
    calculateCoordinates(tree);
    coordinatesOutput(fp3, tree);
    fclose(fp3);

    freeTree(tree);

    return EXIT_SUCCESS;
}
