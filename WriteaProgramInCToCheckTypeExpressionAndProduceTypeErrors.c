#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define MAX_EXPR_LENGTH 100

// Function to check if character is an operator
bool isOperator(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}

// Function to check if character is a digit
bool isDigit(char ch) {
    return isdigit(ch);
}

// Function to check if character is a letter
bool isLetter(char ch) {
    return isalpha(ch);
}

// Function to check expression for type errors
void checkExpressionType(char *expression) {
    int i, len = strlen(expression);
    bool isArithmetic = false;
    bool isAlphabetic = false;

    for (i = 0; i < len; i++) {
        if (!(isOperator(expression[i]) || isDigit(expression[i]) || isspace(expression[i]))) {
            printf("Error: Invalid character '%c' at position %d\n", expression[i], i + 1);
            return;
        }

        if (isLetter(expression[i])) {
            isAlphabetic = true;
        }

        if (isDigit(expression[i])) {
            isArithmetic = true;
        }
    }

    if (isAlphabetic && isArithmetic) {
        printf("Error: Mixed alphanumeric expression\n");
        return;
    }

    if (!isAlphabetic && !isArithmetic) {
        printf("Error: Expression contains no alphanumeric characters\n");
        return;
    }

    if (isAlphabetic) {
        printf("Type: Alphabetic Expression\n");
    }

    if (isArithmetic) {
        printf("Type: Arithmetic Expression\n");
    }
}

int main() {
    char expression[MAX_EXPR_LENGTH];
    
    printf("Enter an expression: ");
    fgets(expression, MAX_EXPR_LENGTH, stdin);
    
    // Remove trailing newline character from fgets
    expression[strcspn(expression, "\n")] = '\0';

    checkExpressionType(expression);

    return 0;
}
