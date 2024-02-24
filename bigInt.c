#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bigInt.h"

#define INIT_SIZE 10

void initBigInt(BigInt *num) {
    num->digits = (int *)malloc(INIT_SIZE * sizeof(int));
    num->size = 0;
    num->capacity = INIT_SIZE;
    num->isNegative = 0;
    memset(num->digits, 0, INIT_SIZE * sizeof(int));
}

void resizeBigInt(BigInt *num) {
    if (num->size >= num->capacity) {
        num->capacity *= 2;
        num->digits = (int *)realloc(num->digits, num->capacity * sizeof(int));
    }
}

void addDigit(BigInt *num, int digit) {
    resizeBigInt(num);
    num->digits[num->size++] = digit;
}

void printBigInt(BigInt *num) {
    if (num->size == 0) {
        printf("0");
        return;
    }

    if (num->isNegative) {
        printf("-");
    }

    for (int i = num->size - 1; i >= 0; i--) {
        printf("%d", num->digits[i]);
    }
}

void swapBigInt(BigInt *num1, BigInt *num2) {
    BigInt temp = *num1;
    *num1 = *num2;
    *num2 = temp;
}

int compareBigInt(BigInt *num1, BigInt *num2) {
    if (num1->size > num2->size) {
        return 1;
    } else if (num1->size < num2->size) {
        return -1;
    } else {
        for (int i = num1->size - 1; i >= 0; i--) {
            if (num1->digits[i] > num2->digits[i]) {
                return 1;
            } else if (num1->digits[i] < num2->digits[i]) {
                return -1;
            }
        }
        return 0;
    }
}

void addBigInt(BigInt *result, BigInt *num1, BigInt *num2) {
    int maxSize = (num1->size > num2->size) ? num1->size : num2->size;
    int digit1, digit2, sum;
    int carry = 0;

    if (num1->isNegative == num2->isNegative) {
        result->isNegative = num1->isNegative;

        for (int i = 0; i < maxSize || carry; i++) {
            digit1 = (i < num1->size) ? num1->digits[i] : 0;
            digit2 = (i < num2->size) ? num2->digits[i] : 0;
            sum = carry + digit1 + digit2;

            addDigit(result, sum % 10);
            carry = sum / 10;
        }
    } else {
        int cmp = compareBigInt(num1, num2);
        if (cmp < 0) {
            swapBigInt(num1, num2);
        }

        result->isNegative = num1->isNegative;

        for (int i = 0; i < maxSize; ++i) {
            digit1 = (i < num1->size) ? num1->digits[i] : 0;
            digit2 = (i < num2->size) ? num2->digits[i] : 0;

            if(digit1 < digit2) {
                num1->digits[i+1]--;
                digit1 += 10;
            }

            sum = digit1 - digit2;
            addDigit(result, sum);
        }

        while (result->size > 1 && result->digits[result->size - 1] == 0) {
            result->size--;
        }
    }
}

void subBigInt(BigInt *result, BigInt *num1, BigInt *num2) {
    int maxSize = (num1->size > num2->size) ? num1->size : num2->size;
    int digit1, digit2, sum;

    int cmp = compareBigInt(num1, num2);
    if (cmp < 0) {
        swapBigInt(num1, num2);
        num1->isNegative = (num1->isNegative) ? 0 : 1;
        num2->isNegative = (num2->isNegative) ? 0 : 1;
    }

    if (num1->isNegative == num2->isNegative) {
        num2->isNegative = (num2->isNegative) ? 0 : 1;

        result->isNegative = num1->isNegative;

        for (int i = 0; i < maxSize; ++i) {
            digit1 = (i < num1->size) ? num1->digits[i] : 0;
            digit2 = (i < num2->size) ? num2->digits[i] : 0;

            if(digit1 < digit2) {
                num1->digits[i+1]--;
                digit1 += 10;
            }

            sum = digit1 - digit2;
            addDigit(result, sum);
        }
    } else {
        result->isNegative = num1->isNegative;

        int carry = 0;
        for (int i = 0; i < maxSize || carry; i++) {
            digit1 = (i < num1->size) ? num1->digits[i] : 0;
            digit2 = (i < num2->size) ? num2->digits[i] : 0;
            sum = carry + digit1 + digit2;

            addDigit(result, sum % 10);
            carry = sum / 10;
        }
    }

    while (result->size > 1 && result->digits[result->size - 1] == 0) {
        result->size--;
    }
}

void multiplyBigInt(BigInt *result, BigInt *num1, BigInt *num2) {
    int product, carry = 0;
    BigInt value, temp;

    int cmp = compareBigInt(num1, num2);
    if (cmp < 0) {
        swapBigInt(num1, num2);
    }

    for (int i = 0; i < num2->size; i++) {
        initBigInt(&value);
        initBigInt(&temp);

        for(int k = i; k > 0; --k) {
            addDigit(&value,0);
        }

        for (int j = 0; j < num1->size; j++) {
            product = (num2->digits[i] * num1->digits[j]) + carry;
            carry = product / 10;
            product %= 10;

            addDigit(&value,product);
            if(j == num1->size-1 && carry != 0)
                addDigit(&value,carry);
        }

        temp = *result;
        initBigInt(result);
        addBigInt(result, &temp, &value);
    }

    result->isNegative = (num1->isNegative == num2->isNegative) ? 0 : 1;
}

void divideBigInt(BigInt *result, BigInt *num1, BigInt *num2) {
    BigInt one, sub, tempResult;
    int isNegative;

    initBigInt(&one);
    initBigInt(&sub);
    initBigInt(&tempResult);
    addDigit(&one, 1);

    if(num2->digits[num2->size - 1] == 0) {
        return;
    }

    int cmp = compareBigInt(num1, num2);
    if (cmp < 0) {
        initBigInt(result);
        return;
    }

    isNegative = (num1->isNegative == num2->isNegative) ? 0 : 1;
    num1->isNegative = 0;
    num2->isNegative = 0;

    while(cmp >= 0) {
        subBigInt(&sub, num1, num2);
        num2->isNegative = 0;
        cmp = compareBigInt(&sub, num2);
        addBigInt(result, &tempResult, &one);

        *num1 = sub;
        tempResult = *result;
        initBigInt(&sub);
        initBigInt(result);
    }
    swapBigInt(result, &tempResult);
    result->isNegative = isNegative;
}

void moduleBigInt(BigInt *result, BigInt *num1, BigInt *num2) {
    BigInt one, sub, tempResult;
    int isNegative, originalSign1, originalSign2;

    if(num2->digits[num2->size - 1] == 0) {
        return;
    }

    if(num2->size == 1 && num2->digits[0] == 1) {
        return;
    }

    initBigInt(&one);
    initBigInt(&sub);
    initBigInt(&tempResult);

    addDigit(&one, 1);

    originalSign1 = num1->isNegative;
    originalSign2 = num2->isNegative;

    int cmp = compareBigInt(num1, num2);
    if(cmp <= 0) {
        if (!(num1->isNegative)) {
            if(num2->isNegative) {
                addBigInt(result, num1, num2);
                result->isNegative = 1;
            } else {
                swapBigInt(result, num1);
                result->isNegative = 0;
            }
        } else {
            if(num2->isNegative) {
                swapBigInt(result, num1);
                result->isNegative = 1;
            } else {
                addBigInt(result, num1, num2);
                result->isNegative = 0;
            }
        }
        return;
    }

    isNegative = num2->isNegative;
    num1->isNegative = 0;
    num2->isNegative = 0;

    while(1) {
        num1->isNegative = 0;
        num2->isNegative = 0;
        subBigInt(&sub, num1, num2);
        cmp = compareBigInt(&sub, num2);
        addBigInt(result, &tempResult, &one);

        *num1 = sub;
        tempResult = *result;
        initBigInt(result);

        if(cmp < 0)
            break;

        initBigInt(&sub);
    }

    result->isNegative = isNegative;

    if(originalSign1 != originalSign2) {
        num2->isNegative = 0;
        subBigInt(result, num2, &sub);
        result->isNegative = isNegative;
    } else {
        swapBigInt(result, &sub);
        result->isNegative = originalSign1;
    }
}

void freeBigInt(BigInt *num) {
    free(num->digits);
    num->size = 0;
    num->capacity = 0;
    num->isNegative = 0;
}