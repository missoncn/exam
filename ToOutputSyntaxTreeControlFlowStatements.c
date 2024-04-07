#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure for representing a syntax tree node
typedef struct TreeNode {
    char data[100];
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

// Function to create a new node
TreeNode* createNode(const char *data) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    strcpy(newNode->data, data);
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to build syntax tree for control flow statements
TreeNode* buildSyntaxTree(const char *statement) {
    const char delim[] = " ,(){};";
    char *token = strtok((char*)statement, delim);
    TreeNode *root = createNode(token);

    while (token != NULL) {
        token = strtok(NULL, delim);
        if (token != NULL) {
            TreeNode *current = root;
            while (current->right != NULL)
                current = current->right;
            current->right = createNode(token);
        }
    }

    return root;
}

// Function to print syntax tree using inorder traversal
void printSyntax(TreeNode* root) {
    if (root == NULL)
        return;

    if (root->left != NULL)
        printf("(");

    printSyntax(root->left);
    printf("%s", root->data);
    printSyntax(root->right);

    if (root->left != NULL)
        printf(")");
}

int main() {
    char statement[1000];

    // Input a control flow statement
    printf("Enter a control flow statement: ");
    fgets(statement, sizeof(statement), stdin);
    statement[strcspn(statement, "\n")] = '\0'; // Remove newline character

    // Build syntax tree
    TreeNode* syntaxTree = buildSyntaxTree(statement);

    // Print syntax tree
    printf("Syntax tree for the statement: ");
    printSyntax(syntaxTree);
    printf("\n");

    // Free the memory used by the syntax tree
    // Note: This is a simplified example and doesn't handle all memory deallocation scenarios.
    free(syntaxTree);

    return 0;
}
