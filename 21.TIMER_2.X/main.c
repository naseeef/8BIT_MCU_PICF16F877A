/*
 * File:   main.c
 * Author: Naseef
 *
 * Created on 9 May, 2022, 9:51 AM
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
void t2delay();
void main()
{
  TRISB=0;
  T2CON=0b01111000;      //postscale=16,prescale=1,timer off
  while(1)
  {
    PORTB=255;
    t2delay();
    PORTB=0;
    t2delay();
  }
}
void t2delay()
{
  unsigned int i;
  T2CON|=(1<<2);        //timer2 on
  for(i=0;i<675;i++)
  {
    while(!TMR2IF);  
    TMR2IF=0;
  }
}
