/*
 * File:   main.c
 * Author: naseef
 *
 * Created on 12 April, 2022, 8:13 PM
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
#define _XTAL_FREQ 16000000

void main(void) {
    
    //TRISB=0x02; //Is equal to 0x00
    TRISB0=0;
    TRISB1=1;
    
    while(1)
    {
        if (RB1 == 1)
        {
        //PORTB = 0x0f;
            RB0 = 1;
        }
        else
        {
            //PORTB = 0;
            RB0 = 0;
        }

    }
    return;
}