#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

bool isValidDelimiter(char ch) {
    if (ch == ' ' || ch == '+' || ch == '-' || ch == '*' ||
        ch == '/' || ch == ',' || ch == ';' || ch == '>' ||
        ch == '<' || ch == '=' || ch == '(' || ch == ')' ||
        ch == '[' || ch == ']' || ch == '{' || ch == '}')
        return (true);
    return (false);
}

bool isValidOperator(char ch) {
    if (ch == '+' || ch == '-' || ch == '*' || ch == '/' ||
        ch == '>' || ch == '<' || ch == '=')
        return (true);
    return (false);
}

bool isValidKeyword(char *str) {
    char keywords[][10] = {"if", "else", "while", "do", "break",
                           "continue", "int", "double", "float",
                           "return", "char", "case", "sizeof",
                           "long", "short", "typedef", "switch",
                           "unsigned", "void", "static", "struct",
                           "goto"};

    for (int i = 0; i < sizeof(keywords) / sizeof(keywords[0]); ++i) {
        if (!strcmp(str, keywords[i])) {
            return true;
        }
    }
    return false;
}

bool isValidInteger(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (!(isdigit(str[i]))) {
            return false;
        }
    }
    return true;
}

bool isRealNumber(char *str) {
    int dotCount = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (isdigit(str[i])) {
            continue;
        } else if (str[i] == '.') {
            dotCount++;
            if (dotCount > 1) {
                return false; // More than one dot is not allowed
            }
        } else {
            return false; // Invalid character
        }
    }
    return dotCount == 1; // Must have exactly one dot
}

bool isvalidIdentifier(char *str) {
    if (!(isalpha(str[0]) || str[0] == '_')) {
        return false;
    }
    for (int i = 1; str[i] != '\0'; i++) {
        if (!(isalnum(str[i]) || str[i] == '_')) {
            return false;
        }
    }
    return true;
}

char *subString(char *str, int left, int right) {
    char *subStr = (char *)malloc(sizeof(char) * (right - left + 2));
    for (int i = left; i <= right; i++) {
        subStr[i - left] = str[i];
    }
    subStr[right - left + 1] = '\0';
    return subStr;
}

void detectTokens(char *str) {
    int left = 0, right = 0;
    int length = strlen(str);
    
    while (right <= length && left <= right) {
        if (isValidDelimiter(str[right]) == false) {
            right++;
        }
        
        if (isValidDelimiter(str[right]) == true && left == right) {
            if (isValidOperator(str[right])) {
                printf("Valid operator: '%c'\n", str[right]);
                right++;
                left = right;
            } else {
                right++;
                left = right;
            }
        } else if (isValidDelimiter(str[right]) == true && left != right ||
                   (right == length && left != right)) {
            char *subStr = subString(str, left, right - 1);
            if (isValidKeyword(subStr) == true) {
                printf("Valid keyword: '%s'\n", subStr);
            } else if (isValidInteger(subStr) == true) {
                printf("Valid integer: '%s'\n", subStr);
            } else if (isRealNumber(subStr) == true) {
                printf("Real number: '%s'\n", subStr);
            } else if (isvalidIdentifier(subStr) == true &&
                       isValidDelimiter(str[right - 1]) == false) {
                printf("Valid identifier: '%s'\n", subStr);
            } else if (isvalidIdentifier(subStr) == false &&
                       isValidDelimiter(str[right - 1]) == false) {
                printf("Invalid identifier: '%s'\n", subStr);
            }
            left = right;
        }
    }
}

int main() {
    char str[100] = "float x = a + 1b; ";
    fgets(str,100,stdin);
    printf("The program is: '%s'\n", str);
    printf("All tokens are:\n");
    detectTokens(str);
    return 0;
}
