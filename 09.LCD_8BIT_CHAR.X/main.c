/*
 * File:   main.c
 * Author: Naseef
 *
 * Created on 18 April, 2022, 10:20 AM
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

#include <xc.h>

LCD_command(unsigned char cmd)
{
    PORTB = cmd;
    RC0 = 0;
    RC1 = 1;
    __delay_ms(10);
    RC1 = 0;
}
LCD_data(unsigned char data)
{
PORTB = data;
    RC0 = 1;
    RC1 = 1;
    __delay_ms(10);
    RC1 = 0;
 }

void main(void) 
{
    TRISB = 0x00;
    TRISC = 0x00;
    LCD_command(0x38);        // enable 8 bit mode  chars 
    LCD_command(0x0E);       
    LCD_command(0x01);        // Clear Display
    LCD_command(0x80);        // Move the curs
    
    //LCD_data('A');

 while(1)
    {
    LCD_data('A');
    }
    return;
}
