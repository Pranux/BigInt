#ifndef BIGINT_H
#define BIGINT_H

typedef struct {
    int *digits;
    int size;
    int capacity;
    int isNegative;
} BigInt;

/**
 * Function to initialize a BigInt
 * @param num BigInt number
 */
void initBigInt(BigInt *num);

/**
 * // Function to resize the BigInt array if needed
 * @param num BigInt number
 */
void resizeBigInt(BigInt *num);

/**
 * Function to add a digit to the BigInt
 * @param num BigInt number
 * @param digit digit that will be added to BigInt
 */
void addDigit(BigInt *num, int digit);

/**
 * Function to print the BigInt
 * @param num BigInt number
 */
void printBigInt(BigInt *num);

/**
 * Function to swap two BigInt numbers
 * @param num1 first BigInt number
 * @param num2 second BigInt number
 */
void swapBigInt(BigInt *num1, BigInt *num2);

/**
 * Function to compare two BigInt numbers (ignoring sign)
 * @param num1 first BigInt number
 * @param num2 second BigInt number
 * @return -1 if num 1 < num2, 1 if num1 > num2, 0 if num1 = num2
 */
int compareBigInt(BigInt *num1, BigInt *num2);

/**
 * Function to add two BigInt numbers
 * @param result num1 + num2
 * @param num1 first BigInt number
 * @param num2 second BigInt number
 */
void addBigInt(BigInt *result, BigInt *num1, BigInt *num2);

/**
 * Function to subtract two BigInt numbers
 * @param result num1 - num2
 * @param num1 first BigInt number
 * @param num2 second BigInt number
 */
void subBigInt(BigInt *result, BigInt *num1, BigInt *num2);

/**
 * Function to subtract two BigInt numbers
 * @param result num1 * num2
 * @param num1 first BigInt number
 * @param num2 second BigInt number
 */
void multiplyBigInt(BigInt *result, BigInt *num1, BigInt *num2);

/**
 * Function to subtract two BigInt numbers
 * @param result num1 / num2
 * @param num1 first BigInt number
 * @param num2 second BigInt number
 */
void divideBigInt(BigInt *result, BigInt *num1, BigInt *num2);

/**
 * Function to subtract two BigInt numbers
 * @param result num1 % num2
 * @param num1 first BigInt number
 * @param num2 second BigInt number
 */
void moduleBigInt(BigInt *result, BigInt *num1, BigInt *num2);

/**
 * Function to free allocated memory for BigInt number
 * @param num BigInt number
 */
void freeBigInt(BigInt *num);

#endif