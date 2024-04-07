#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_SYMBOLS 10
#define MAX_PRODUCTIONS 10

// Structure to represent a production
typedef struct Production {
    char lhs;
    char rhs[MAX_SYMBOLS];
} Production;

// Structure to represent a set of symbols
typedef struct SymbolSet {
    char symbols[MAX_SYMBOLS];
    int count;
} SymbolSet;

// Function to add a symbol to a set
void addToSet(SymbolSet* set, char symbol) {
    if (set->count < MAX_SYMBOLS) {
        set->symbols[set->count++] = symbol;
    }
}

// Function to print a set
void printSet(SymbolSet* set) {
    printf("{ ");
    for (int i = 0; i < set->count; i++) {
        printf("%c ", set->symbols[i]);
    }
    printf("}\n");
}

// Function to check if a symbol is in a set
bool isInSet(SymbolSet* set, char symbol) {
    for (int i = 0; i < set->count; i++) {
        if (set->symbols[i] == symbol) {
            return true;
        }
    }
    return false;
}

// Function to compute FIRST set for a given non-terminal symbol
void computeFirst(Production productions[MAX_PRODUCTIONS], int numProductions, char nonTerminal, SymbolSet* firstSet) {
    for (int i = 0; i < numProductions; i++) {
        if (productions[i].lhs == nonTerminal) {
            if (productions[i].rhs[0] == '\0' || productions[i].rhs[0] == nonTerminal) {
                addToSet(firstSet, '\0');
            } else {
                addToSet(firstSet, productions[i].rhs[0]);
            }
        }
    }
}

// Function to compute FOLLOW set for a given non-terminal symbol
void computeFollow(Production productions[MAX_PRODUCTIONS], int numProductions, char nonTerminal, SymbolSet* followSet) {
    if (productions[0].lhs == nonTerminal) {
        addToSet(followSet, '$');
    }

    for (int i = 0; i < numProductions; i++) {
        for (int j = 0; productions[i].rhs[j] != '\0'; j++) {
            if (productions[i].rhs[j] == nonTerminal) {
                if (productions[i].rhs[j + 1] != '\0') {
                    computeFirst(productions, numProductions, productions[i].rhs[j + 1], followSet);
                } else {
                    computeFollow(productions, numProductions, productions[i].lhs, followSet);
                }
            }
        }
    }
}

int main() {
    int numProductions;
    Production productions[MAX_PRODUCTIONS];

    // Input the number of productions
    printf("Enter the number of productions: ");
    scanf("%d", &numProductions);
    getchar(); // Consume newline character

    // Input the productions
    printf("Enter the productions in the form 'LHS -> RHS':\n");
    for (int i = 0; i < numProductions; i++) {
        printf("Production %d: ", i + 1);
        scanf("%c -> %s", &productions[i].lhs, productions[i].rhs);
        getchar(); // Consume newline character
    }

    // Compute FIRST and FOLLOW sets for a non-terminal symbol
    char nonTerminal;
    printf("\nEnter the non-terminal symbol to compute FIRST and FOLLOW sets for: ");
    scanf("%c", &nonTerminal);

    SymbolSet firstSet = { .count = 0 };
    computeFirst(productions, numProductions, nonTerminal, &firstSet);

    SymbolSet followSet = { .count = 0 };
    computeFollow(productions, numProductions, nonTerminal, &followSet);

    // Print the FIRST and FOLLOW sets
    printf("\nFIRST(%c) = ", nonTerminal);
    printSet(&firstSet);

    printf("FOLLOW(%c) = ", nonTerminal);
    printSet(&followSet);

    return 0;
}
