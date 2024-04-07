#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure for representing a syntax tree node
typedef struct TreeNode {
    char* label;
    char* value;
    struct TreeNode** children;
    int num_children;
} TreeNode;

// Function to create a new syntax tree node
TreeNode* createNode(char* label, char* value, int num_children) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->label = strdup(label);
    node->value = strdup(value);
    node->num_children = num_children;
    node->children = (TreeNode**)malloc(num_children * sizeof(TreeNode*));
    return node;
}

// Function to recursively print the syntax tree
void printSyntaxTree(TreeNode* root, int depth) {
    if (root == NULL)
        return;

    for (int i = 0; i < depth; i++)
        printf("  ");

    printf("%s", root->label);
    if (root->value != NULL)
        printf(": %s", root->value);
    printf("\n");

    for (int i = 0; i < root->num_children; i++)
        printSyntaxTree(root->children[i], depth + 1);
}

// Function to parse a declaration and construct the syntax tree
TreeNode* parseDeclaration(char* declaration) {
    TreeNode* root = createNode("Declaration", NULL, 0);
    char* token = strtok(declaration, " ");

    while (token != NULL) {
        root->children[root->num_children++] = createNode("DeclarationPart", token, 0);
        token = strtok(NULL, " ");
    }

    return root;
}

int main() {
    char declaration[100];

    // Input a declaration
    printf("Enter a declaration: ");
    fgets(declaration, sizeof(declaration), stdin);
    declaration[strcspn(declaration, "\n")] = '\0'; // Remove newline character

    // Parse the declaration and construct the syntax tree
    TreeNode* syntaxTree = parseDeclaration(declaration);

    // Print the syntax tree
    printf("Syntax Tree for Declaration:\n");
    printSyntaxTree(syntaxTree, 0);

    // Free the memory used by the syntax tree
    // Note: This is a simplified example and doesn't handle all memory deallocation scenarios.
    for (int i = 0; i < syntaxTree->num_children; i++)
        free(syntaxTree->children[i]);
    free(syntaxTree);

    return 0;
}
