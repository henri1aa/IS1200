/* mipslabwork.c

   This file written 2015 by F Lundevall
   Updated 2017-04-21 by F Lundevall

   This file should be changed by YOU! So you must
   add comment(s) here with your name(s) and date(s):

   This file modified 2017-04-31 by Ture Teknolog 

   For copyright and licensing, see file COPYING */

#include <stdint.h>   /* Declarations of uint_32 and the like */  
#include <stdlib.h>
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h"  /* Declatations for these labs */

/* 
The following code was written by T Björkdahl & H Gidehag 
*/

int p1 = 10;
int p2 = 10;

int x = 62;
int y = 16; 

int xDir = 1;
int yDir = 1;

char scorep1 = 0x30;
char scorep2 = 0x30;

int winner = 2;

void user_isr(void)
{
  int btns1 = getbtns1();
  int btns2 = getbtns2();

  /*
  Left paddle "p1=y"
  Written by T Bjorkdahl
  */
  if(btns1 & 0x80) //btn 4, move the left paddle up on screen
  {
    p1--;
    if(p1 <= 0)
    {
      p1 = 0;  //stops when paddle reaches top of the screen
    }
  }

  if(btns1 & 0x40) //btn 3, move left paddle down on screen
  {
    p1++;
    if(p1 >= 20)
    {
      p1 = 20; //stops when paddle reaches bottom of the screen
    }
  }

  /*
  Right paddle "p2=y"
  Written by H Gidehag
  */  
  if(btns1 & 0x20) //btn 2, move right paddle up on screen
  {
    p2--;
    if(p2 <= 0)
    {
      p2 = 0;  //stops when paddle reaches top of display
    }
  }
  
  if(btns2 & 0x2) //btn 1, move right paddle down on screen
  {
    p2++;
    if(p2 >= 20)
    {
      p2 = 20; //stops when paddle reaches bottom of display
    }
  }  
}

/* This function is called repetitively from the main program */
void game( void ) 
{
  x += xDir; 
	y += yDir;
  
  int btns1 = getbtns1();
  int btns2 = getbtns2();

  user_isr();

  /* Collision with left wall or paddle */
  if(x <= 2 && (y > p1 + 12 || y < p1) && (y + 4 > p1 + 12 || y + 4 < p1))
  { 
    x = 62;
    y = 16;
    scorep2++;
    delay(500);
    if(scorep2 == 0x3A)
    {      
      winner = 0; // "Player 2 won"
      reset = 0; // Returns to start screen
    }
  }
  else if(x <= 2)
  {
    x = 2;
    xDir = 1;
  }

  /* Collision with right wall or paddle */
  if(x >= 123 && (y > p2 + 12 || y < p2) && (y + 4 > p2 + 12 || y + 4 < p2))
  {
    x = 62;
    y = 16;
    scorep1++;
    delay(500);
    if(scorep1 == 0x3A)
    {
      winner = 1; // "player 1 won"
      reset = 0; // Returns to start screen
    }
  }
  else if(x >= 123)
  {
    x = 123;
    xDir = -1;
  }

  /* Collision with upper or lower wall */
  if(y <= 0)
  {
    y = 0;
    yDir = 1;
  }
  if(y >= 28)
  {
    y = 28; 
    yDir = -1;
  }

  clear_display();

  /* Displays scoreboard, ball and paddles */
  insertScore(scorep1, scorep2, "-");
  paint_score(52, 0, 3);
  paint_sprite((uint8_t *)pright, 126, p2, 2, 12);
  paint_sprite((uint8_t *)pleft, 0, p1, 2, 12);
  paint_sprite((uint8_t *)ball, x, y, 4, 4);
  delay(12);

  display_update();
}

/* Game start screen */
void start( void )
{
  int btns1 = getbtns1();
  int btns2 = getbtns2();

  p1 = 10;
  p2 = 10;

  x = 62;
  y = 16; 

  clear_display();
  
  /* Display winner */
  if(winner == 1)
  {
    display_string(0, "Player 1 won!");
    paint_text(6, 0, 16, 0);
    display_string(3, "Press btn 1&4");
    paint_text(6, 24, 16, 3);
    xDir = 1;
    yDir = 1;
  }
  if(winner == 0)
  {
    display_string(0, "Player 2 won!");
    paint_text(6, 0, 16, 0);
    display_string(3, "Press btn 1&4");
    paint_text(6, 24, 16, 3);
    xDir = -1;
    yDir = 1;
  }
  if(winner == 2)
  {
    display_string(0, "Press btn 1&4");
    paint_text(6, 0, 16, 0);
  }

  /* Reset scoreboard */
  scorep1 = 0x30;
  scorep2 = 0x30;

  /* Displays ball and paddles */
  paint_sprite((uint8_t *)pright, 126, p2, 2, 12);
  paint_sprite((uint8_t *)pleft, 0, p1, 2, 12);
  paint_sprite((uint8_t *)ball, x, y, 4, 4);

  display_update();

  if(btns1 && btns2)
  {
    delay(1000);
    reset = 1; // Starts game
  }
}