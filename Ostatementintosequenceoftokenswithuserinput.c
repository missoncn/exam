#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to tokenize the input string
void tokenizeInput(char *input) {
    // Define delimiters for tokens
    const char delimiters[] = " ,;(){}[]";
    
    // Use strtok to tokenize the input string
    char *token = strtok(input, delimiters);
    
    // Loop through tokens and print them
    while (token != NULL) {
        printf("Token: %s\n", token);
        token = strtok(NULL, delimiters);
    }
}

int main() {
    // Maximum length for the input statement
    const int maxInputLength = 1000;
    
    // Allocate memory for the input statement
    char input[maxInputLength];
    
    // Prompt the user for input
    printf("Enter an I/O statement: ");
    
    // Use scanf to get user input
    if (scanf("%[^\n]s", input) == 1) {
        // Clear the input buffer
        while (getchar() != '\n');
        
        // Tokenize the input statement
        tokenizeInput(input);
    } else {
        printf("Error reading input.\n");
    }

    return 0;
}
