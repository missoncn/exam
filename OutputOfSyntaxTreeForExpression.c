#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Structure for representing a syntax tree node
typedef struct TreeNode {
    char data;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

// Function to create a new node
TreeNode* createNode(char data) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to check if a character is an operator
bool isOperator(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/');
}

// Function to build syntax tree from postfix expression
TreeNode* buildSyntaxTree(char *expression) {
    TreeNode* stack[100]; // Assuming maximum size of the stack
    int top = -1;

    for (int i = 0; expression[i] != '\0'; i++) {
        if (!isOperator(expression[i])) {
            stack[++top] = createNode(expression[i]);
        } else {
            TreeNode* rightOperand = stack[top--];
            TreeNode* leftOperand = stack[top--];

            TreeNode* operatorNode = createNode(expression[i]);
            operatorNode->left = leftOperand;
            operatorNode->right = rightOperand;

            stack[++top] = operatorNode;
        }
    }

    return stack[top];
}

// Function to print syntax tree using inorder traversal
void printSyntax(TreeNode* root) {
    if (root == NULL)
        return;
    
    if (root->left != NULL || root->right != NULL)
        printf("(");

    printSyntax(root->left);
    printf("%c", root->data);
    printSyntax(root->right);

    if (root->left != NULL || root->right != NULL)
        printf(")");
}

int main() {
    char expression[100];

    // Input a postfix expression
    printf("Enter a postfix expression: ");
    scanf("%s", expression);

    // Build syntax tree
    TreeNode* syntaxTree = buildSyntaxTree(expression);

    // Print syntax tree
    printf("Syntax tree for the expression: ");
    printSyntax(syntaxTree);
    printf("\n");

    // Free the memory used by the syntax tree
    // Note: This is a simplified example and doesn't handle all memory deallocation scenarios.
    free(syntaxTree);

    return 0;
}
