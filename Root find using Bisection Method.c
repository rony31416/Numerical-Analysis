
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define MAXN 200
#define F(x) ((x)*(x)*(x) +4*(x)*(x)-10)

int main()
{
    int i;
    double a = 1;
    double b = 2;
    double TOL = 0.00005;
    double x0 ;
    double fa,fb,fx0;
    fa = F(a);
    fb = F(b);
    if(fa*fb >= 0 )
    {
        printf("There do not exist any root -_-\n");
        return 0;
    }
    for(int i = 1 ; i< MAXN ; i++)
    {

        x0 = (a+b)/2;
        fx0 = F(x0);
         printf("%d\t%lf\t%lf\t%lf\t%lf\n",i,a,b,x0,fx0);
        if(fabs(fx0) <= TOL)
        {
            printf("Root : %lf, Itr : %d\n",x0,i);
            return 0;
        }

        if(fa*fx0 < 0)
        {
            b = x0;
            fb = fx0;
        }
        else
        {
            a = x0;
            fa = fx0;
        }
    }
    printf("Itr Overflow ! \n");

    return 0;

}
