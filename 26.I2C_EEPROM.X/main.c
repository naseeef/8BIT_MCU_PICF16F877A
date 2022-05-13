/*
 * File:   main.c
 * Author: Naseef
 *
 * Created on 12 May, 2022, 12:54 PM
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
#include "lcd8bit.h"
#include "i2c.h"
#define _XTAL_FREQ 12000000

void main()
{
    lcd_init();
    i2c_init();
    
    show("mem writing");

    i2c_send_byte(0x0000,"external eeprom");
    
    for(int i=0;i<10000;i++);
    //__delay_ms(1000);
    cmd(0x80);
    show(" mem Reading...");

    for(int i=0;i<1000;i++);
    //__delay_ms(1000);
    cmd(0xc0);
    dat(i2c_read_byte(0x0000));
    dat(i2c_read_byte(0x0001));
    dat(i2c_read_byte(0x0002));
    dat(i2c_read_byte(0x0003));
    dat(i2c_read_byte(0x0004));
    dat(i2c_read_byte(0x0005));
    dat(i2c_read_byte(0x0006));
    dat(i2c_read_byte(0x0007));
    dat(i2c_read_byte(0x0008));
    dat(i2c_read_byte(0x0009));
    dat(i2c_read_byte(0x000a));
    dat(i2c_read_byte(0x000b));
    dat(i2c_read_byte(0x000c));
    dat(i2c_read_byte(0x000d));
    dat(i2c_read_byte(0x000e));
   
    while(1);
}
