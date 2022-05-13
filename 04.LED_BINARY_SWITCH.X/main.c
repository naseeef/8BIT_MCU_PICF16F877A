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
    
    TRISB=0x00; //Is equal to 0x00
    
    int n=1;

/*UP COUNT
    while(1)
    {
        while(n<16)
        {
            PORTB = 0x00+n;
            __delay_ms(1000);
            n++;
        }
    } */
    /*DOWN COUNT*/
     while(1)
    {
        while(n<16)
        {
            PORTB = 0xff-n;
            __delay_ms(1000);
            n++;
        }
    }
    
    return;
} 