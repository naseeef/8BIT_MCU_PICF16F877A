/*
 * File:   main.c
 * Author: Naseef
 *
 * Created on 18 April, 2022, 11:10 AM
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

void LCD_init()
{
    LCD_command(0x02);
    LCD_command(0x38);        // enable 8 bit mode  chars 
    LCD_command(0x80);       
    LCD_command(0x0C);        // Clear Display
    LCD_command(0x06);        // Move the curs
    __delay_ms(10);
}

void main(void) 
{
    TRISB = 0x00;
    TRISC = 0x00;
    LCD_init();
    LCD_command(0x80);
    char a[]={"Good Morning"};
    for (int i=0; a[i]!='\0';i++)
    {
        LCD_data(a[i]);
    }   
}

/*
#include <xc.h>
#define _XTAL_FREQ 16000000


void LCD_Command(unsigned char cmd)
{
    
RC0=0;
__delay_ms(10);
PORTB=(cmd);
RC1=1;
__delay_ms(10);
RC1=0;
__delay_ms(10);

}
void LCD_data(unsigned char data)
{
    
RC0=1;  
__delay_ms(10);
PORTB =(data);
RC1=1;
__delay_ms(10);
RC1=0;
__delay_ms(10);

}
void LCD_init()
{
LCD_Command (0x02);     //Send four bit initialization of LCD
LCD_Command (0x38);
LCD_Command (0x80);    //Cursor at Home position
LCD_Command (0x0C);    //Display On Cursor off
LCD_Command (0x06);    //Auto increment cursor
__delay_ms(10);
   
}

void main(void)
{
TRISB=0x00;
TRISC=0X00;
LCD_init();
LCD_Command(0x80);
char a[]={"good morning"};
int i;
 for(i=0;a[i]!='\0';i++)
    {
    LCD_data(a[i]);
    }
return;
}
 */