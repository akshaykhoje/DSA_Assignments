#include <stdio.h>

int steps = 0;

//smaller n implies smaller block and hence should be above others
void move(int n, char src, char helper, char dest)
{
  // base case
  if (n == 0)
    return;

  steps++;
  // recursive case
  // move N - 1 disks to the helper

  move(n - 1, src, dest, helper);
  printf("Move disk %d from %c to %c\n", n, src, dest);
  move(n - 1, helper, src, dest);
}


int main()
{
  int n;
  printf("Enter the number of disks\n");
  scanf("%d", &n);

  move(n, 'A', 'C', 'B');
  printf("Total number of iterations required are: %d\n", steps);

  return 0;
}