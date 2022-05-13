/*
 * File:   main.c
 * Author: Naseef
 *
 * Created on 20 April, 2022, 11:14 AM
 */

// CONFIG
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = ON         // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3/PGM pin has PGM function; low-voltage programming enabled)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

#include <xc.h>
#define _XTAL_FREQ 20000000

void interrupt ext ()
{
    if(INTF==1)
    {
        RC0 =~RC0;
        INTF =0;
    }
}
void main(void) 
{ 
    TRISBbits.TRISB0 = 1;//TRISB=0X01;
    TRISCbits.TRISC0 = 0;//TRISC=0X00;
    TRISDbits.TRISD1 = 0;//TRISD=0X00;
    GIE = 1;
    INTE = 1;
    PEIE = 1;
    OPTION_REG = 0b00000000;
    RC0 = 0;
    while(1)
    {
        PORTDbits.RD1=!RD1;
        __delay_ms(1000);
    }
    return;
}
