#include <stdio.h>
#include <stdint.h>
#include "uart.h"
#include Bear



//takes in an int, stores it as binary, but we don't have access to print that, so we're taking a
void intToBin (uint8_t target, char* buffer) {//we're going to assume that the buffer points to an array that can store an 8 bit integer
    /* Your code goes here */
    
    int i;
    
    
    for (i = 0; i <= 7; i++){
        uint8_t temp;
        char write;
        temp = target >> (7-i); //bit shifting, we want 
        temp = temp & 0x1;//gets last bit
        
        if (temp == 1){
            write = '1';
        } else {
            write = '0';
        }
        
        buffer[i] = write;
    }
    
    buffer[8] = '\0';

} 

int main () {
    uart_init(UART2);
    uint8_t value;
    int ret;
    char binaryStr[9];

    // Begin main program loop
    while (value != 10) {
        value = uart_read(UART2, BLOCKING, &ret);
        intToBin(value, binaryStr);
        uart_write_str(UART2, binaryStr);
    }

    return 0;
}
