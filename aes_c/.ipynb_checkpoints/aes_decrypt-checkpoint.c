#include "uart.h"
#include "bearssl.h"
#include <stdlib.h>
#include <string.h>
#define IV_LEN 0x10
#define KEY_LEN 0x10
#define KEY "thistheembseckey"
int main() {
    uart_init(UART2);
    int ret; 
    char * key = KEY;//the key is already defined
    unsigned char iv[IV_LEN];
    
    //the iv is read in 
    for(int i = 0; i < IV_LEN; i++) {
        iv[i] = uart_read(UART2, BLOCKING, &ret);
    }
    unsigned short data_len = uart_read(UART2, BLOCKING, &ret) | (uart_read(UART2, BLOCKING, &ret) << 8) ;//we have our iphertext size
    char * data = malloc(data_len);  
    for(int i = 0; i < data_len; i++) {
        data[i] = uart_read(UART2, BLOCKING, &ret);//data is our ciphertext
    }
    // TODO: Decrypt here!
    
    
    char * flag = strstr(data, "embsec{");
    int i = 0;
    while(flag[i] != '}') {
        uart_write(UART2, data[i]);
        i += 1;
    }
    uart_write(UART2, data[i]);
    uart_write(UART2, '\n');
    return 0;
}