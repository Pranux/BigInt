#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "bigInt.h"

int validateBigInt(char *num);
void userInput(char *num1, char *operator, char *num2);
void stringToBigInt(BigInt *result, const char *str);

int main(void) {

    BigInt num1, num2, result;
    char numbers1[1000];
    char numbers2[1000];
    char operator = 0;

    initBigInt(&num1);
    initBigInt(&num2);
    initBigInt(&result);

    userInput(numbers1, &operator, numbers2);
    stringToBigInt(&num1, numbers1);
    stringToBigInt(&num2, numbers2);

    printBigInt(&num1);
    printf(" %c ", operator);
    printBigInt(&num2);
    printf(" = ");

    switch(operator) {
        case '+':
            addBigInt(&result, &num1, &num2);
            printBigInt(&result);
            break;
        case '-':
            subBigInt(&result, &num1, &num2);
            printBigInt(&result);
            break;
        case '*':
            multiplyBigInt(&result, &num1, &num2);
            printBigInt(&result);
            break;
        case '/':
            divideBigInt(&result, &num1, &num2);
            printBigInt(&result);
            break;
        case '%':
            moduleBigInt(&result, &num1, &num2);
            printBigInt(&result);
            break;
        default:
            break;
    }

    // Free allocated memory
    freeBigInt(&num1);
    freeBigInt(&num2);
    freeBigInt(&result);

    return 0;
}

int validateOperator(char operator) {
    if(operator == '+' || operator == '-' || operator == '*' || operator == '/' || operator == '%')
        return 1;
    return 0;
}

int validateBigInt(char *num) {
    int strLength = strlen(num);
    int startIndex = 0;

    if (num[0] == '-')
        startIndex = 1;

    for (int i = startIndex; i < strLength; i++) {
        if (!isdigit(num[i]))
            return 0;
    }
    return 1;
}

void userInput(char *num1, char *operator, char *num2) {
    printf("This program is like calculator that works with unlimited length numbers.\n");
    printf("You can do such operations as: +, -, *, /, %%.\n");
    printf("What operation would you like to do (numbers and operators should be seperated with a space): ");

    while(scanf("%s %c %s", num1, operator, num2) != 3 || !validateBigInt( num1) ||
        !validateBigInt(num2) || !validateOperator(*operator) || getchar() != '\n') {

        printf("Something went wrong, try again: ");
        scanf("%*[^\n]");
    }
}

void stringToBigInt(BigInt *result, const char *str) {
    int strLength = strlen(str);

    int startIndex = 0;
    if (str[0] == '-') {
        result->isNegative = 1;
        startIndex = 1;
    }

    for (int i = strLength-1; i >= startIndex; --i) {
        int digit = str[i] - '0';
        addDigit(result, digit);
    }
}