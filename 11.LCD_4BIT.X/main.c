/*
 * File:   main.c
 * Author: Naseef
 *
 * Created on 19 April, 2022, 10:00 AM
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

void LCD_Command(unsigned char cmd)
{   
RD1=0;
__delay_ms(10);
PORTD=(cmd);
RD2=1;
__delay_ms(10);
RD2=0;
__delay_ms(10);

PORTD=(cmd<<4);
RD1=0;
RD2=1;
__delay_ms(10);
RD2=0;
__delay_ms(10);
}

void LCD_data(unsigned char data)
{  
RD1=1;  
__delay_ms(10);
PORTD =(data);
RD2=1;
__delay_ms(10);
RD2=0;
__delay_ms(10);

PORTD =(data<<4);
RD1=1;
RD2=1;
__delay_ms(10);
RD2=0;
__delay_ms(10);
}

void LCD_init()
{
LCD_Command (0x02);     //Send four bit initialization of LCD
LCD_Command (0x28);
LCD_Command (0x80);    //Cursor at Home position
LCD_Command (0x0C);    //Display On Cursor off
LCD_Command (0x06);    //Auto increment cursor
__delay_ms(10);
}

void main(void)
{
TRISD=0x00;
LCD_init();
LCD_data('a');
return;
}
