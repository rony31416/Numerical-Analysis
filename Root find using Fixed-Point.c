#include <stdio.h>
#include <math.h>

double g(double x)
{
    return (1+cos(x))/3;
}

double fixed_point_method(double x0, double tolerance)
{
    double x1 = g(x0);
    while (fabs(x1 - x0) >= tolerance)
    {
        x0 = x1;
        x1 = g(x0);
    }
    return x1;
}

int main()
{
    double x0 = 0;
    double tolerance = 0.0001;
    double root = fixed_point_method(x0, tolerance);
    printf("The root is: %f\n", root);
    return 0;
}
