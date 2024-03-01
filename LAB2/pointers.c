


#include <stdio.h>

char* text1 = "This is a string.";
char* text2 = "Yet another thing.";
int list1[40]; //list1: .space 80 (alokerar 80 bytes av minne) => int list1[40] (4 byte i en int, 80/)
int list2[40]; //list2: .space 80 (alokerar 80 bytes av minne) => int list2[40] (4 byte i en int, 80)
int count = 0; //count: .word 0, word = 4 bytes = int, värdet av count blir 0



void printlist(const int* lst){
  printf("ASCII codes and corresponding characters.\n");
  while(*lst != 0){
    printf("0x%03X '%c' ", *lst, (char)*lst);
    lst++;
  }
  printf("\n");
}

void endian_proof(const char* c){
  printf("\nEndian experiment: 0x%02x,0x%02x,0x%02x,0x%02x\n", 
         (int)*c,(int)*(c+1), (int)*(c+2), (int)*(c+3)); //börjar från minsta och ökar uppåt, alltså little från höger till vänster eller nåt
}

void copycodes(char* p, int q[], int* c)
{
  while(*p != 0)
  {
    *q = *p;
    q++;
    p++;
    (*c)++;
  }
}

void work()
{
  copycodes(text1, list1, &count);
  copycodes(text2, list2, &count);
}

int main(void){
  work();
  printf("\nlist1: ");
  printlist(list1);
  printf("\nlist2: ");
  printlist(list2);
  printf("\nCount = %d\n", count);
  endian_proof((char*) &count);
}
