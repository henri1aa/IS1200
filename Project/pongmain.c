/* mipslabmain.c

   This file written 2015 by Axel Isaksson,
   modified 2015, 2017 by F Lundevall

   Latest update 2017-04-21 by F Lundevall

   For copyright and licensing, see file COPYING */

/*
To do list:
- Fixa så att bollen och paddlarna skrivs separat 
- Någon typ av poängställning, upp till 11?
- Om det går att vi har collisionscheck som en funktion istället för att jämföra y-värden
- Städa upp koden, ta bort onödig kod (fixa kommentarerna)
*/

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h"  /* Declatations for these labs */

int main(void) 
{
    /*
      Following code is written 2015 by Axel Isaksson,
      modified 2015, 2017 by F Lundevall

	  This will set the peripheral bus clock to the same frequency
	  as the sysclock. That means 80 MHz, when the microcontroller
	  is running at 80 MHz. Changed 2017, as recommended by Axel.
	*/
	SYSKEY = 0xAA996655;  /* Unlock OSCCON, step 1 */
	SYSKEY = 0x556699AA;  /* Unlock OSCCON, step 2 */
	while(OSCCON & (1 << 21)); /* Wait until PBDIV ready */
	OSCCONCLR = 0x180000; /* clear PBDIV bit <0,1> */
	while(OSCCON & (1 << 21));  /* Wait until PBDIV ready */
	SYSKEY = 0x0;  /* Lock OSCCON */
	
	/* Set up output pins */
	AD1PCFG = 0xFFFF;
	ODCE = 0x0;
	TRISECLR = 0xFF;
	PORTE = 0x0;
	
	/* Output pins for display signals */
	PORTF = 0xFFFF;
	PORTG = (1 << 9);
	ODCF = 0x0;
	ODCG = 0x0;
	TRISFCLR = 0x70;
	TRISGCLR = 0x200;
	
	/* Set up input pins */
	TRISDSET = (1 << 8);
	TRISFSET = (1 << 1);
	
	/* Set up SPI as master */
	SPI2CON = 0;
	SPI2BRG = 4;
	/* SPI2STAT bit SPIROV = 0; */
	SPI2STATCLR = 0x40;
	/* SPI2CON bit CKP = 1; */
    SPI2CONSET = 0x40;
	/* SPI2CON bit MSTEN = 1; */
	SPI2CONSET = 0x20;
	/* SPI2CON bit ON = 1; */
	SPI2CONSET = 0x8000;
	 
	display_init();
 	display_textupdate();

	/*
	The follwoing code is written T Björkdahl & H Gidehag
	Function calls is taken from labwork
	*/

	/* Initialize swithes and buttons */
	int sw = getsw();  
	int btns1 = getbtns1();
 	int btns2 = getbtns2(); 

	reset = 0;

	/* Calls functions in pongwork.c */
	while( 1 )
	{
		while(reset == 0)
		{
			start();
		}
		while(reset == 1)
		{
			game();
			/* "Pauses" game */
			while(getsw()) 
			{
				delay(0);
			}
		}
	}
	return 0;
}
