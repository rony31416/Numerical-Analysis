#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAXN 10
#define PI   3.14159

int main (void)
{
    int i;
    double a=0, b=2.0, h;
    double x[MAXN + 1], f[MAXN + 1], df[MAXN + 1];

    h = (b - a)/MAXN;
    x[0] = a;
    for (i=1; i< MAXN; i++)
        x[i] = x[i-1] + h;
    x[i] = b;

    for (i=0; i<= MAXN; i++)
        f[i] = x[i] * x[i] + 1;
    for (i=1; i<= MAXN; i++)
        df[i] = ( f[i] - f[i-1] )/( x[i] - x[i-1] );

    printf("- - - - - - - - - - - - - - - - - - - -\n");
    printf("  i    x[i]       f[i]       df[i]\n");
    printf("- - - - - - - - - - - - - - - - - - - -\n");
    printf("%3d %10lf %10lf     ----\n",i,x[i],f[i] );
    for (i=1; i<= MAXN; i++)
        printf("%3d %10lf %10lf %10lf\n",i,x[i],f[i],df[i] );
    printf("- - - - - - - - - - - - - - - - - - - -\n");


    return EXIT_SUCCESS;
}
