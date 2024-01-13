/*
 * File:   main.c
 * Author: Paul
 *
 * Created on January 6, 2024, 11:32 PM
 */

#include <xc.h>
#pragma config FOSC = HS    //4Mhz

#define _XTAL_FREQ 20000000  //4Mhz

#define led PORTCbits.RC4

char data[4] = {'U', 'P', 'S', ' '};

__interrupt() void myInterrupt(){
    if(RCIF == 1 ){
        data[0] = RCREG;
        TXREG = data[0];
        __delay_ms(1);
        RCIF = 0;
    }

}

void main(void) {
    TRISC4 = 0;         //LED
    TRISC6 = 0;         //TX
    TRISC7 = 1;         //Rx
    SPEN = 1;           // HABILITA TX RX PARA PUERTO SERIAL
    TX9 =0;             // 8 bits transmitter
    
    SYNC = 0;           //Asynchronous
    BRGH = 1;           //High speed
    SPBRG = 64;         //19200 BAUDIOS
    CREN = 1;           //Receiver Enable
    TXEN = 1;           //Transmitter Enable
    RCIE = 1;           //Receiver Interrupt Enable
    PEIE = 1;           //Peripherical Interrupt Enable
    GIE = 1;            //Global Interrupt Enable
    
    
    while (1){
        led = 1;
        /*
        for (int i = 0; i<=3; i++){
        TXREG = data[i];
        __delay_ms(1);
        }*/
        __delay_ms(1000);
        led = 0;  
        __delay_ms(1000);
    }
    return;
}
