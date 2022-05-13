/*
 * File:   main.c
 * Author: Naseef
 *
 * Created on 9 May, 2022, 12:53 PM
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

LCD_init();
void ser_int();
unsigned char tx(unsigned char);
unsigned char rx();

void ser_int()
{
 TRISC=0x80;
 TXSTA= 0x20;
 RCSTA= 0b10010000;
 SPBRG=31;
}
 
unsigned char tx(unsigned char a)
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
void LCD_Command(unsigned char cmd)
{
RD1=0;
RD2=0;
__delay_ms(10);
PORTD=(cmd);
RD3=1;
__delay_ms(10);
RD3=0;
__delay_ms(10);
PORTD=(cmd<<4);
RD2=0;
RD3=1;
__delay_ms(10);
RD3=0;
__delay_ms(10);
}

void LCD_data(unsigned char data)
{
RD1=0;
RD2=1;
__delay_ms(10);
PORTD=(data);
RD3=1;
__delay_ms(10);
RD3=0;
__delay_ms(10);
PORTD=(data<<4);
RD2=1;
RD3=1;
__delay_ms(10);
RD3=0;
__delay_ms(10);
}

LCD_init()
{
LCD_Command (0x02); //Send four bit initialization of LCD
LCD_Command (0x28);
LCD_Command (0x80); //Cursor at Home position
LCD_Command (0x0C); //Display On Cursor off
LCD_Command (0x06); 
__delay_ms(10);
}

void main()
{ 
TRISD=0x00;
TRISB=0X00;
LCD_init();
ser_int();

char str[]="Good Morning!";
for (int i=0;str[i]!='\0';i++)
{
    LCD_data(str[i]);
    tx(str[i]);
}
__delay_ms(100);
}