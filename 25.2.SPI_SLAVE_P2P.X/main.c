/*
 * File:   main.c
 * Author: Naseef
 *
 * Created on 11 May, 2022, 10:49 AM
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
#include<stdint.h>
#define _XTAL_FREQ 20000000
void interrupt ISR(void);
void SPI_Slave_Init();
uint8_t SPI_Read();
uint8_t Data;
void main(void)
{
   SPI_Slave_Init(); 
  TRISB = 0x00; 
   while(1)
  {
  
    PORTB = Data;
  }
  return;
}
void SPI_Slave_Init()
{
  SSPM0 = 0;
  SSPM1 = 0;
  SSPM2 = 1;
  SSPM3 = 0;
  SSPEN = 1;
  CKP = 0;
  CKE = 0;
  SMP = 0;
  TRISC5 = 0; 
  TRISC4 = 1; 
  TRISC3 = 1; 
  PCFG3 =0;
  PCFG2 =1;
  PCFG1 =0; 
   PCFG0 =0;
   TRISA5=1;
   SSPIE=1;
   PEIE=1;
   GIE=1;
}
uint8_t SPI_Read()
{
    uint8_t Data;
    if(BF)
{
    Data = SSPBUF;
    BF=0;
    SSPIF=0;
    SSPOV=0;
    return Data;
}
    
}
void interrupt ISR(void)
{ 
    if(SSPIF)
{
    Data= SSPBUF;
  SSPIF = 0; 
}
}