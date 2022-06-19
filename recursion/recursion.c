#include <stdio.h>
#include <stdlib.h>

int fact(int n);
int print(int n);


int main()
{
  // print(5);
  int key = 3;
  int fac_val = fact(key);
  printf("factorial of %d : %d\n", key, fac_val);
  return 0;
}


// first go till depth and the print. A typical use of popping out of stack
int print(int n)
{
  if (n> 0)
  {
    print(n-1);
    printf("%d ", n);
  }
  else
    return 0;
}


// factorial function
int fact(int n)
{
  if (n == 0 || n == 1)
  {
    return 1;
  }
  
  return n * fact(n-1);
}