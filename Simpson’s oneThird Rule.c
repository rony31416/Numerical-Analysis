#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAXN 10
#define PI   3.14159

int main (void) {
  int i;
  double sumX=0, sumO=0.0, sumE=0, h;
  double x[MAXN + 1]={0.0, 0.2, 0.4, 0.6, 0.8, 1.0, 1.2, 1.4, 1.6, 1.8, 2.0};
  double y[MAXN + 1]={1.0, 1.04, 1.16, 1.36, 1.64, 2.0, 2.44, 2.96, 3.56, 4.24, 5.0};
  double intT, intS3;

  h = x[1] - x[0];

  sumX = ( y[0] + y[MAXN] );
  for (i=1; i< MAXN; i=i+2)
    sumO =  sumO + y[i];
  for (i=2; i< MAXN; i=i+2)
    sumE =  sumE + y[i];

  intS3 = h*(sumX + 4*sumO + 2*sumE )/3;

  printf("Simpson’s 1/3 Rule - - - - - - - - -\n");
  printf("  Integration Value = %lf\n",intS3);
  printf("- - - - - - - - - - - - - - - - - - - -\n");

  return EXIT_SUCCESS;
}
