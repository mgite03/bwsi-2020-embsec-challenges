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
    
//     test_AES_generic(char *name,
// 	const br_block_cbcenc_class *ve,
// 	const br_block_cbcdec_class *vd,
// 	const br_block_ctr_class *vc,
// 	int with_MC, int with_CBC)
    
    
    //a struct in c is kinda like a calss, but you can't have methods in it - it's kinda just a package of daata
    //so ppl include functions as function pointers
    
    
    // "in your design, you can grab these lines as is" -gabe
    const br_block_cbcdec_class * vd = &br_aes_big_cbcdec_vtable;// creates vd w a type cbcdec_class  --- represents all implementations for aes
    br_aes_gen_cbcdec_keys v_dc; 
    const br_block_cbcdec_class **dc;
    
    dc = &v_dc.vtable;
    vd->init(dc, key, KEY_LEN);// dereferencing to a function
    vd->run(dc, iv, data, data_len);//bearssl decrypts the data in place, so it's not a new variable
    //after you run this last line, the last block is the iv

    
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