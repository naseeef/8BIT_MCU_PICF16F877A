/*
 * File:   main.c
 * Author: Naseef
 *
 * Created on 9 May, 2022, 9:48 AM
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


#include<xc.h>
#define _XTAL_FREQ 12000000
void t1delay();
void main()
{
  TRISB=0;
  T1CON=0x01;   //Prescale value = 1:1, It using Internal clock, Timer 1 ON
  while(1) {
    PORTB=0xff;
    t1delay();
    PORTB=0;
    t1delay();
  }
}
void t1delay()
{
  int i;
  for(i=0;i<42;i++) {
    TMR1H=TMR1L=0;
    while(!TMR1IF);
    TMR1IF=0;
  }
}
