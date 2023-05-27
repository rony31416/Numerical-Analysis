#include<stdio.h>
#include<math.h>

#define F(x)  (c1 + c2*x + c3*x*x + c4*x*x*x)

int MAXN = 11;

/*
  //ronymajumder
  //1325

  question:
  `````````
   Find the qubic polynomial that is the least
   squares fit to the following data

  x =  0.0  0.2   0.4   0.6   0.8   1.0  1.2   1.4   1.6   1.8  2.0
 fx =  1.0  1.04  1.16  1.36  1.64  2.0  2.44  2.96  3.56  4.24  5.0

  concept:

  the qubic polynomial  F(x) = c1 + c2*x + c3*(x*x) + c4*(x*x*x);

  Ax = b;
  A`Ax = A`b      [here A`means transpose of matrix A]

  now we get A`A which is a square matrix;
  let consider A`A = MatA         [MatA is a square matrix]
           and  A`b = k           [k is a column matrix]

  so,
  MatA.x = k
  now by applying Gauss-Jordan elimination we get

 | c1| = |value1|
 | c2| = |value2|
 | c3| = |value3|
 | c4| = |value4|
*/

double matrix[11][4];//matrix A
double TransMat[4][11];//transpose matrix
double matMult[4][5]; //MatA
double b[11][1];//b matrix
double RMat[4][1];//k matrix -----A`b


int main()
{
    double x[MAXN]= {0.0,0.2,0.4,0.6,0.8,1.0,1.2,1.4,1.6,1.8,2.0};
    double fx[MAXN]= {1.0,1.04,1.16,1.36,1.64,2.0,2.44,2.96,3.56,4.24,5.0};

    for(int i = 0 ; i < MAXN ; i++)
    {
        b[i][0] = fx[i];
    }
    //somikoron er coefficient matrix
    for(int i = 0 ; i < 11 ; i++)
    {
        for(int j = 0 ; j < 4 ; j++)
        {
            matrix[i][j] = pow(x[i],j);
        }
    }

    //print korlam
    printf("Matrix A \n");
    for(int i = 0 ; i < 11 ; i++)
    {
        for(int j = 0 ; j < 4 ; j++)
        {
            printf("%.4lf\t ",matrix[i][j]);
        }
        printf("\n");
    }

    printf("\nMatrix b \n");
    for(int i = 0 ; i < MAXN ; i++)
    {
        printf("%.4lf\n",b[i][0]);
    }

    //transpose korlam

    for(int i = 0 ; i < 4 ; i++)
    {
        for(int j = 0 ; j < MAXN ; j++)
        {
            TransMat[i][j] = matrix[j][i];
        }
    }

    printf("\nTranspose Matrix A`\n");
    for(int i = 0 ; i < 4 ; i++)
    {
        for(int j = 0 ; j < 11 ; j++)
        {
            printf("%.4lf\t ",TransMat[i][j]);
        }
        printf("\n");
    }


    //make MatA or A`X A
    for(int i = 0 ; i < 4 ; i++)
    {
        for(int j = 0 ; j < 4 ; j++)
        {
            for(int k = 0 ; k < 11 ; k++ )
            {
                matMult[i][j] += TransMat[i][k]*matrix[k][j];
            }
        }
    }


    printf("\nSquare matrix MatA \n");

    for(int i = 0 ; i < 4 ; i++)
    {
        for(int j = 0 ; j < 4 ; j++)
        {
            printf("%4lf\t",matMult[i][j]);
        }
        printf("\n");
    }


    //make matrix k by A` X b
    for(int i = 0 ; i < 4 ; i++ )
    {
        for(int j = 0 ; j < 1 ; j++)
        {
            for(int k = 0 ; k < MAXN ; k++)
            {
                RMat[i][j] += TransMat[i][k]*b[k][j];
            }
        }
    }


    printf("\nMatrix k \n");
    for(int i = 0 ; i < 4 ; i++)
    {
        printf("%4lf\n",RMat[i][0]);
    }


    //makeing augment matrix
    for(int i = 0 ; i < 4 ; i ++)
    {
        matMult[i][4] = RMat[i][0];
    }

    printf("\nAugment Matrix\n");
    for(int i = 0 ; i < 4 ; i++)
    {
        for(int j = 0 ; j < 5 ; j++)
        {
            printf("%4lf\t",matMult[i][j]);
        }
        printf("\n");
    }




    // Applying Gauss-Jordan elimination
    int N = 4;
    for (int i = 0; i < N; i++)
    {
        double pivot = matMult[i][i];
        for (int j = 0; j < N+1; j++)
        {
            matMult[i][j] /= pivot;
        }

        for (int k = 0; k < N; k++)
        {
            if (k != i)
            {
                double factor = matMult[k][i];
                for (int j = 0; j < N+1; j++)
                {
                    matMult[k][j] -= factor * matMult[i][j];
                }
            }
        }
    }


    printf("\nMatA after Gauss-Jordan elimination \n");
    for(int i = 0 ; i < 4 ; i++)
    {
        for(int j = 0 ; j < 5 ; j++)
        {
            printf("%4lf\t",matMult[i][j]);
        }
        printf("\n");
    }

    printf("\nValue \n");
    for(int i = 0 ; i < 4 ; i++)
    {
        printf("c%d\t%4lf\n",i+1,matMult[i][4]);
    }

    return 0;
}

/*
Matrix A
1.0000	 0.0000	 0.0000	 0.0000
1.0000	 0.2000	 0.0400	 0.0080
1.0000	 0.4000	 0.1600	 0.0640
1.0000	 0.6000	 0.3600	 0.2160
1.0000	 0.8000	 0.6400	 0.5120
1.0000	 1.0000	 1.0000	 1.0000
1.0000	 1.2000	 1.4400	 1.7280
1.0000	 1.4000	 1.9600	 2.7440
1.0000	 1.6000	 2.5600	 4.0960
1.0000	 1.8000	 3.2400	 5.8320
1.0000	 2.0000	 4.0000	 8.0000

Matrix b
1.0000
1.0400
1.1600
1.3600
1.6400
2.0000
2.4400
2.9600
3.5600
4.2400
5.0000

Transpose Matrix A`
1.0000	 1.0000	 1.0000	 1.0000	 1.0000	 1.0000	 1.0000	 1.0000	 1.0000	 1.0000 1.0000
0.0000	 0.2000	 0.4000	 0.6000	 0.8000	 1.0000	 1.2000	 1.4000	 1.6000	 1.8000 2.0000
0.0000	 0.0400	 0.1600	 0.3600	 0.6400	 1.0000	 1.4400	 1.9600	 2.5600	 3.2400 4.0000
0.0000	 0.0080	 0.0640	 0.2160	 0.5120	 1.0000	 1.7280	 2.7440	 4.0960	 5.8320 8.0000

Square matrix MatA
11.000000	11.000000	15.400000	24.200000
11.000000	15.400000	24.200000	40.532800
15.400000	24.200000	40.532800	70.664000
24.200000	40.532800	70.664000	126.617920

Matrix k
26.400000
35.200000
55.932800
94.864000

Augment Matrix
11.000000	11.000000	15.400000	24.200000	26.400000
11.000000	15.400000	24.200000	40.532800	35.200000
15.400000	24.200000	40.532800	70.664000	55.932800
24.200000	40.532800	70.664000	126.617920	94.864000

MatA after Gauss-Jordan elimination
1.000000	0.000000	0.000000	0.000000	1.000000
0.000000	1.000000	0.000000	0.000000	0.000000
0.000000	0.000000	1.000000	0.000000	1.000000
0.000000	0.000000	0.000000	1.000000	0.000000

Value
c1	1.000000
c2	0.000000
c3	1.000000
c4	0.000000
*/
