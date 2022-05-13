/*
 * File:   main.c
 * Author: Naseef
 *
 * Created on 22 April, 2022, 11:14 AM
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
//#include <stdint.h>
#define _XTAL_FREQ 16000000
#define rs RC2
#define en RC3
#define R1 RD0
#define R2 RD1
#define R3 RD2
#define R4 RD3
#define C1 RD4
#define C2 RD5
#define C3 RD6
#define C4 RD7

void lcd_init();
void cmd(unsigned char a);
void dat(unsigned char b);
void show(unsigned char *s);
void lcd_delay();
unsigned char key();
void keyinit();

unsigned char keypad[4][4]={{'7','8','9','/'},{'4','5','6','*'},{'1','2','3','-'},{'C','0','=','+'}};
unsigned char rowloc,colloc;

void main()
{
    unsigned int i;
    TRISC=0;
    lcd_init();
    keyinit();
    unsigned char b;
    cmd(0x80);
    show(" Enter the Key ");
    
    while(1)
    {
        cmd(0xc7);
        b=key();
        dat(b);
        cmd(0xc8);
        b=key();
        dat(b);
        cmd(0xc9);
        b=key();
        dat(b);
    } 
}

void lcd_init()
{
    cmd(0x02);
    cmd(0x28);
    cmd(0x0e);
    cmd(0x06);
    cmd(0x80);
}

void cmd(unsigned char cmd)
{
    rs=0; 
   __delay_ms(10);
   PORTC =(cmd);
   en=1;
   __delay_ms(10);
   en=0;
   __delay_ms(10);
   PORTC=(cmd<<4);
   rs =0;
   en =1;
   __delay_ms(10);
   en =0;
   __delay_ms(10);
}

void dat(unsigned char data)
{
    rs =1; 
   __delay_ms(10);
   PORTC =(data);
   en=1;
   __delay_ms(10);
   en=0;
   __delay_ms(10);
   PORTC=(data<<4);
   rs =1;
   en=1;
   __delay_ms(10);
   en=0;
   __delay_ms(10);
}

void show(unsigned char *s)
{
 while(*s) 
    {
        dat(*s++);
    }
}

void lcd_delay()
{
    unsigned int lcd_delay;
    for(lcd_delay=0;lcd_delay<=1000;lcd_delay++); //looping until condition false
}

void keyinit()
{
    TRISD=0XF0;
    PORTD=0X00;
}

unsigned char key()
{
    PORTD=0X00;
    while(C1&&C2&&C3&&C4);
        {
        while(!C1||!C2||!C3||!C4) 
            {
            __delay_ms(100); 

            R1=0;
            R2=R3=R4=1;
            if(!C1||!C2||!C3||!C4) 
                {
                    rowloc=0;
                    break;
                }
            R2=0;
            R1=R3=R4=1;
            if(!C1||!C2||!C3||!C4) 
                {
                    rowloc=1;
                    break;
                }
            R3=0;
            R2=R1=R4=1;
            if(!C1||!C2||!C3||!C4) 
                {
                    rowloc=2;
                    break;
                }
            R4=0;
            R2=R3=R1=1;
            if(!C1||!C2||!C3||!C4)
                {
                    rowloc=3;
                    break;
                }

            }
       }
    
    if(C1==0&&C2!=0&&C3!=0&&C4!=0)
    colloc=0;
    else if(C1!=0&&C2==0&&C3!=0&&C4!=0)
    colloc=1;
    else if(C1!=0&&C2!=0&&C3==0&&C4!=0)
    colloc=2;
    else if(C1!=0&&C2!=0&&C3!=0&&C4==0)
    colloc=3;
    while(C1==0||C2==0||C3==0||C4==0);
    
    return (keypad[rowloc][colloc]);
}
