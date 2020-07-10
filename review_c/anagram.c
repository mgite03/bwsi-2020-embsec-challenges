#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "uart.h"

uint8_t isAnagram (char* str_a, char* str_b) {
    /* Your code goes here */
    
    int i;
    int j;
 
    for (i = 0; i < strlen(str_a); i ++){

        char a_char = str_a[i];
        if (a_char == ' ')
            continue;
    
        for (j = 0; j < strlen(str_b); j ++){
            if (a_char == str_b[j]){
                str_b[j] = ' ';

            }
        }
    }
        
    int k;
    for (k = 0; k < strlen(str_b); k ++){
        if (str_b[k] == ' ')
            continue;
        else
            return 0;
    }
    

    
    return 1;
} 

int main () {
    uart_init(UART2);
    int ret;
    uint8_t numTests;
    char str_a[50];
    char str_b[50];
    uint8_t strPtr = 0;
    uint8_t testResult = 0;
    
    // Get ammount of tests
    numTests = uart_read(UART2, BLOCKING, &ret);

    // Begin main program loop
    for (int i = 0; i < numTests; i++) {
        char value = 0;
        uint8_t strPtr = 0;

        // Recieve first string
        while (value != 10) {
            value = uart_read(UART2, BLOCKING, &ret);
            str_a[strPtr++] = value;
        }
        str_a[(strPtr-1)] = '\0';  // Replaces newline with null terminator
        value = 0;
        strPtr = 0;

        // Recieve next string
        while (value != 10) {
            value = uart_read(UART2, BLOCKING, &ret);
            str_b[strPtr++] = value;
        }
        str_b[(strPtr-1)] = '\0';

        // Return result of test
        testResult = isAnagram(str_a, str_b);
        uart_write(UART2, (char) testResult);
    }

    return 0;
}
