/* mipslabwork.c

   This file written 2015 by F Lundevall
   Updated 2017-04-21 by F Lundevall

   This file should be changed by YOU! So you must
   add comment(s) here with your name(s) and date(s):

   This file modified 2017-04-31 by Ture Teknolog 

   For copyright and licensing, see file COPYING */

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h"  /* Declatations for these labs */

int mytime = 0x5957;

volatile int* trisE = (volatile int*) 0xbf886100; //Pointer till trisE som ligger på addressen, säger om den ska vara in/output
volatile int* portE = (volatile int*) 0xbf886110; //Pointer till portE som ligger på addressen, där värdet som vi skriver ligger                                     //värdet för de 8 bitarna vilket sätter LEDs som av eller på

char textstring[] = "text, more text, and even more text!";

int timeoutcounter = 0;
int prime = 1234567;

/* Interrupt Service Routine */
void user_isr( void ) {
  IFSCLR(0) = 0x100;
  timeoutcounter++;
  int sw = getsw();
  if(timeoutcounter == 10)
  { 
    time2string( textstring, mytime );
    display_string( 3, textstring );
    display_update();
    tick( &mytime );
    timeoutcounter = 0;

    /*om switchen sätts på kör den if satsen*/
    if(((sw >> 9) & 0x1) == 1){
      mytime += 2;
    } 
  }
}

/* Lab-specific initialization goes here */
void labinit( void )
{
  *trisE &= ~0xff; //maskar och sätter bit 7 till 0 som 0 för att deklarera dessa som output
 
  T2CON = 0x0;
  TRISD |= (0x7f << 5); //sätter dem första 7 bitarna till 1 och shiftar till rätt plats           
  TMR2 = 0; //sätter timer värdet till 0
 
  PR2 = 31250; //sätter periodlängden till 100 ms 80M/256/10
  IPCSET(2) = 0x1F;
  IECSET(0) = 0x100;
  T2CON = 0x8070; //kolla PIC32 family reference manual section 14. s. 9. Sätter på timer 2 och prescalar till 1:256
  //0000 0000 0000 0000 0000 0000 0001 1111

  INTCONSET = 0x4;

  enable_interrupt(); 
  return; 
}         

/* This function is called repetitively from the main program */
void labwork( void ) {
 prime = nextprime( prime );
 display_string( 0, itoaconv( prime ) );
 display_update();
}



//TRISE, TRISESET & TRISECLR handlar alla om input och output - SET(input) & CLR(output) behandlar specifika bitar medans TRISE behandlar alla i port E
//