
//#include "print-primes.c"
#include <stdio.h>
#include <stdlib.h>

#define COLUMNS 6



int print_number(int n){ 
  static int line = 1;
  printf("%10d", n); //Tegar & Henrietta
  if(line == COLUMNS) //Tegar
    {
      printf("\n"); //Henrietta
      line = 0; //Tegar
    }
  line++;
}

void print_sieves(int n)
{   
  char *arr; //pekar till ett ställe där vi ska lagra skiten
  arr = (char *)malloc(sizeof(char) * n); //pekar dit och säger hur mycket skit vi ska lagra
  for(int i = 2; i < n; i++)
  {
    arr[i] = i;
  }

  for(int i = 2; i < n; i++)
  {
    int j = arr[i]*arr[i]; //j = i^2, vi behöver inte titta på tidigiare multiplar av i då vi redan har gjort det.
    if(arr[i] != 0) // 0 = sammansatt tal
    {   
      print_number(i);
      //sätter alla multiplar av i som 0 = sammansatt tal
      while(j < n)
      {
      arr[j] = 0;  //alla multiplar/sammansatta tal sätter vi som 0
      j+=i;  //går till nästa multipel av i
      }
    }
  }
  printf("\n");
  free(arr); //frigör den från bördan
}

// 'argc' contains the number of program arguments, and
// 'argv' is an array of char pointers, where each
// char pointer points to a null-terminated string.
int main(int argc, char *argv[]){
  if(argc == 2)
    print_sieves(atoi(argv[1]));
  else
    printf("Please state an interger number.\n");
  return 0;
}