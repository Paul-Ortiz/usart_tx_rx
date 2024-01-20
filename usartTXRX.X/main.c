/*
 * File:   main.c
 * Author: Paul
 *
 * Created on January 6, 2024, 11:32 PM
 */

#include <xc.h>
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF       // Power-up Timer Enable bit (PWRT enabled)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)


#define _XTAL_FREQ 20000000  //20Mhz

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
