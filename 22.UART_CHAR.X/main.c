/*
 * File:   main.c
 * Author: Naseef
 *
 * Created on 9 May, 2022, 11:18 AM
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

void ser_int();
void tx(unsigned char);
unsigned char rx();
void txstr(unsigned char *);

void main()
{
 char a; 
 TRISC6=0; //Output (TX)
 TRISC7=1; //Input (RX)
 ser_int();
 txstr(" Enter the letters in keyboard\n\r\r");
 while(1) {
 a= rx(); 
 tx(a); //tx(rx());
 } 
} 

void ser_int()
{
 TXSTA=0x20; //BRGH=0, TXEN = 1, Asynchronous Mode, 8-bit mode
 RCSTA=0b10010000; //Serial Port enabled,8-bit reception
 SPBRG= 31; //9600 baudrate for 20Mhz// BAUD RATE= FOC/(64*(X+1))LOW SPEED (BRGH=0 )//
 TXIF=RCIF=0;
}
 
void tx(unsigned char a)
{
 TXREG=a;
 while(!TXIF);
 TXIF = 0;
}

unsigned char rx()
{
 while(!RCIF);
 RCIF=0;
 return RCREG;
}

void txstr(unsigned char *s)
{
 while(*s) { //loop will terminate when *s is equal to \0
 tx(*s++);
 }
}
