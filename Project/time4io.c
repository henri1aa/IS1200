#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h"  /* Declatations for these labs */

#define TRISD		PIC32_R (0x860C0) // Port D: mask as input
#define PORTD		PIC32_R (0x860D0) // Port D: read inputs, write outputs
#define TRISF		PIC32_R (0x86140) // Port F: mask of inputs 
#define PORTF		PIC32_R (0x86150) // Port F: read inputs, write outputs

int getsw( void )
{
    int n = 0xf00;
    n &= PORTD; //maskar ut den 3:e byten
    return n;
}

int getbtns1( void )
{   
    int n = 0xe0;
    n &= PORTD; //maskar ut bit 8-6
    return n;
}

int getbtns2( void )
{   
    int f = 0x2;
    f &= PORTF; //maskar ut bit 1
    return f;
}

