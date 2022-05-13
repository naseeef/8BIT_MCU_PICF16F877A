/*
 * File:   main.c
 * Author: Naseef
 *
 * Created on 21 April, 2022, 10:32 AM
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

void ADC_Init ();
void LCD_Command (unsigned char cmnd);
void LCD_Char (unsigned char data);
void LCD_init (void);
void LCD_num1 (long int val, int calb_val);
void LCD_float(unsigned int val);
void LCD_num (unsigned int val);
void LCD_heads (void);

void main(void) 
{
    TRISB =0x00;
    TRISC = 0x00;
    ADC_Init ();
    LCD_init();
    LCD_heads();
    unsigned int ADC_VALUE,PRE_ADC_VALUE = 0;
    while (1)
    {
        GO_nDONE=1;
        while(GO_nDONE==1);
        __delay_ms(10);
        ADC_VALUE= ((ADRESH<<8)+ADRESL);
        LCD_Command (0x8C);
        LCD_num (ADC_VALUE);
        LCD_Command (0xCF);
        LCD_float(ADC_VALUE);
        /*if (PRE_ADC_VALUE != ADC_VALUE)
        {
            PRE_ADC_VALUE = ADC_VALUE;
            LCD_Command (0xC0);
            LCD_float(ADC_VALUE);
            LCD_Command (0x01);
        }*/
    }
    return;
}

void ADC_Init ()
{
    ADCON0 = 0x85; //Channel 0 selected, FOSC/64 selected, ADON = 1; GO/DONE = 1; 
    ADCON1 = 0xC0; // Right Justified, ADCS2 = 1.
}

void LCD_Command (unsigned char cmnd)
{
    RC0 = 0;
    PORTB = ((cmnd >> 4) & 0x0F) ;
    RC1 = 1;
    __delay_ms(10);
    RC1 = 0;
    __delay_ms(10);
    PORTB = ((cmnd)& 0x0F);
     RC1 = 1;
    __delay_ms(10);
    RC1 = 0;
    __delay_ms(10);
}

void LCD_Char (unsigned char data)
{
    RC0 = 1;
    PORTB = ((data >> 4) & 0x0F);
    RC1 = 1;
    __delay_ms(10);
    RC1 = 0;
    __delay_ms(10);
    PORTB = ((data) & 0x0F);
     RC1 = 1;
    __delay_ms(10);
    RC1 = 0;
    __delay_ms(10);
}

void LCD_init (void)
{
    LCD_Command (0x02); 
    LCD_Command (0x28); //Send four bit initialization of LCD
    LCD_Command (0x80); //Cursor at Home position
    LCD_Command (0x0C); //Display On Cursor off
    LCD_Command (0x06); //Auto increment cursor
    LCD_Command (0x01);
    __delay_ms(10);
}

void LCD_num (unsigned int val)
{
    int remainder, digit1, digit2, digit3, digit4, result, result1;
    if (val<=9)
    {
        LCD_Char (val+0x30);
    }
    else if (val>=10 && val <100)
    {
        remainder = val % 10;
        digit1 = remainder;
        digit2 = val/10;
        LCD_Char(digit2+0x30);
        LCD_Char(digit1+0x30);
    }
    else if (val>=100 && val <1000)
    {
        remainder = val % 10;
        result1 = val /10;
        digit1 = remainder;
        remainder = result1%10;
        digit2 = remainder;
        digit3 = result1/10;
        LCD_Char(digit3+0x30);
        LCD_Char(digit2+0x30);
        LCD_Char(digit1+0x30);
    }
    else if (val>=1000 && val <9999)
    {
        remainder = val % 10;
        result1 = val /10;
        digit1 = remainder;
        remainder = result1%10;
        digit2 = remainder;
        result = result1/10;
        remainder = result%10;
        digit3=remainder;
        digit4 = result/10;
        LCD_Char(digit4+0x30);
        LCD_Char(digit3+0x30);
        LCD_Char(digit2+0x30);
        LCD_Char(digit1+0x30);
    }
}

void LCD_num1 (long int val, int calb_val)
{
    unsigned int remainder, digit1, digit2, digit3, result, 
    result1;
    result = ((val*100)/calb_val);
    remainder = result% 10;
    result1 = result /10;
    digit1 = remainder;
    remainder = result1%10;
    digit2 = remainder;
    remainder = (result1/10);
    digit3=remainder;
    LCD_Char(digit3+0x30);
    LCD_Char('.');
    LCD_Char(digit2+0x30);
    LCD_Char(digit1+0x30);
}

void LCD_float(unsigned int val)
{
    unsigned int volt;
    int calb_val = 200;
    //char adc[10];
    volt = (val);
    LCD_num1(volt,calb_val);
    //itoa (volt,adc,10);
}

void LCD_heads (void)
{
    /*char h1[] = {"ADC:"};
    char h2[] = {"INPUT:"};*/
    
    char h1[] = {"ADC OUTPUT:"};
    char h2[] = {"INPUT VOLTAGE:"};
    
    LCD_Command (0x80);
    for (int i =0;h1[i]!='\0';i++)
    {
        LCD_Char(h1[i]);
    }
    
    LCD_Command (0xC0);;
    for (int i =0;h2[i]!='\0';i++)
    {
        LCD_Char(h2[i]);
    }
}