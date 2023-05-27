#include <stdio.h>
#include <math.h>

/*
  concept
  (rony-1325)
  let suppose a Matrix A(3 X 2) is
       1  1
 A =   0  1
      -1  1
  first of all , make transpose of A

   A^T =
   1  0 -1
   1  1  1

   find V :

   now A^T X A is a square and also a symmetric matrix
   let firstly calculate A^T X A as V matrix
   then find the eigen  values for matrix V and also corresponding eigenvectors.
   After normalized we get matrix V

   now finding sigma matrix:

   we have to find a matrix(sigma) which also have the same dimension of given A matrix'
   now ,calculate the rank;
   rank is the nonzero eigen value of a matrix;
   and calculate a diagonal matrix which contain square root of every eigen value according to descending order
   then fixed the dimension by filling every entries with zero


   finding U:

   similarly
   now we calculate  A X A^T is a square and also a symmetric matrix
   let firstly calculate A X A^T  as U matrix
   then find the eigen  values for matrix U and also corresponding eigenvectors.
   After normalized we get matrix U

  */

double result[10][10], d[10][10], s[10][10], s1[10][10], s1t[10][10],trans[10][10],input[10][10],svd[10][10],sigma[10][10];
double temp[10][10],eigen[100],theta, zero=1e-5, max,pi=3.141592654;
int num_of_index = 0,indx_point = 0;

int find_rank(double mat[], int n);
void MatrixMultiplication(double Mat1[][10],double Mat2[][10],int m,int n);
void jacobi(double a[][10],int n);
int main()
{
    int m,n, i, j, k, p, q, flag;

    printf("Enter the rows and column of the matrix: ");
    scanf("%d %d",&m,&n);

    printf("Enter the Matrix:\n");

    for(i = 0; i < m; i++)
    {
        for(j = 0; j < n; j++)
            scanf ("%lf", &input[i][j]);
    }

    printf("\nThe given matrix 'A' is :\n");
    printf("____________________________\n\n");

    for(i = 0; i < m; i++)
    {
        for(j = 0; j < n; j++)
        {
            printf ("%8.4f ", input[i][j]);
        }
        printf ("\n");
    }
    printf ("\n");

    //transpose matrix formation AT
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < m; j++)
        {
            trans[i][j]=input[j][i];
        }
    }

    printf("Transpose matrix(A^T):\n");
    printf("__________________________\n\n");

    for(i = 0; i < n; i++)
    {
        for(j = 0; j < m; j++)
        {
            printf ("%8.4f ", trans[i][j]);
        }
        printf ("\n");
    }

    printf("\n\t\tComputation of V:\n");
    printf("\t________________________________\n");

    printf("\nMultiplication of (A^T * A):\n");
    printf("_____________________________________\n");

    MatrixMultiplication(trans,input,n,m);

    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
            printf ("%8.4f ",result[i][j]);
        }
        printf ("\n");
    }

    printf("\n");

    jacobi(result,n);

    printf("\n 'V' matrix is:\n");
    printf("________________________\n");

    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
            printf("%8.4f ",svd[j][i]);
        }
        printf("\n");
    }

    printf("\n\t\tComputation of E(sigma) :\n");
    printf("\t___________________________________\n");

    for(i = 0; i < num_of_index; i++)
    {
        for(j = 0; j < num_of_index; j++)
        {
            if(eigen[i]>eigen[j])
            {
                double tem=eigen[j];
                eigen[j]=eigen[i];
                eigen[i]=tem;
            }
        }
    }
    printf("\nEigenvalues are (According to Descending order):\n");
    printf("---------------------------------------------------\n");

    for(i = 0; i < num_of_index; i++)
    {
        printf("%8.4f ",eigen[i]);
    }

    int rankk = find_rank(eigen,num_of_index);
    printf("\n\nrank of the matrix is : %d \n\n",rankk);

    int nth = 0;
    for(i = 0; i < m; i++)
    {
        for(j = 0; j < n; j++)
        {
            if(i == j && nth < rankk)
            {
                sigma[i][j] = sqrt(eigen[nth]);
                nth++;
            }
        }
    }

    printf("sigma matrix E : \n");
    printf("____________________\n");
    for(i = 0; i < m; i++)
    {
        for(j = 0; j < n; j++)
        {

            printf ("%8.4f ",sigma[i][j]);

        }
        printf("\n");
    }

    printf("\n\n");
    printf("\n\t\tComputation of U:\n");
    printf("\t________________________________\n\n");

    printf("\n Multiplication of (A * A^T):\n");
    printf("______________________________\n\n");

    MatrixMultiplication(input,trans,m,n);

    for(i = 0; i < m; i++)
    {
        for(j = 0; j < m; j++)
        {
            printf ("%8.4f ",result[i][j]);
        }
        printf ("\n");
    }

    printf("\n");

    jacobi(result,m);

    printf("\n 'U' matrix is:\n");
    printf("________________________\n\n");

    for(i = 0; i < m; i++)
    {
        for(j = 0; j < m; j++)
        {
            printf("%8.4f ",svd[j][i]);
        }
        printf("\n");
    }
    printf("\n\n");

    return 0;


}


int find_rank(double mat[], int n)
{
    int rankk = 0;
    for(int i = 0 ; i < n ; i++)
    {
        if(abs(mat[i] - 0) > 1e-5) rankk++;
    }
    return rankk;
}



void MatrixMultiplication(double Mat1[][10],double Mat2[][10],int m,int n)
{

    int l=n;
    if(m>n) l=m;

    for(int i=0; i<l; i++)
    {
        for(int j=0; j<l; j++)
        {
            result[i][j]=0;
        }
    }

    for(int i=0; i<m; i++)
    {
        for(int j=0; j<m; j++)
        {
            for( int k=0; k<n; k++)
            {
                result[i][j]+=Mat1[i][k]*Mat2[k][j];
            }
        }
    }
}


void jacobi(double a[][10],int n)
{

    int i,j,flag,p,q;

    for(i=0; i<n; i++)
    {
        for(j=0; j<n; j++)
        {
            d[i][j]= a[i][j];
            if(i==j)
                s[i][j]= 1;
            else
                s[i][j]= 0;
        }
    }

    do
    {
        flag= 0;
        p=0;
        q=1;
        max= fabs(d[p][q]);

        for(i=0; i<n; i++)
        {
            for(j=0; j<n; j++)
            {
                if(i!=j)
                {
                    if (max < fabs(d[i][j]))
                    {
                        max= fabs(d[i][j]);
                        p = i;
                        q = j;
                    }
                }
            }
        }

        if(d[p][p]==d[q][q])
        {
            if (d[p][q] > 0)
                theta= pi/4;
            else
                theta= -pi/4;
        }
        else
        {
            theta=0.5*atan(2*d[p][q]/(d[p][p]-d[q][q]));
        }

        for(i=0; i<n; i++)
        {
            for(j=0; j<n; j++)
            {
                if(i==j)
                {
                    s1[i][j]= 1;
                    s1t[i][j]= 1;
                }
                else
                {
                    s1[i][j]= 0;
                    s1t[i][j]= 0;
                }
            }
        }

        s1[p][p]= cos(theta);
        s1t[p][p]= s1[p][p];

        s1[q][q]= cos(theta);
        s1t[q][q]= s1[q][q];

        s1[p][q]= -sin(theta);
        s1[q][p]= sin(theta);

        s1t[p][q]= s1[q][p];
        s1t[q][p]= s1[p][q];

        for(i=0; i<n; i++)
        {
            for(j=0; j<n; j++)
            {
                temp[i][j]= 0;
                for(p=0; p<n; p++)  temp[i][j]+= s1t[i][p]*d[p][j];
            }
        }

        for(i=0; i<n; i++)
        {
            for(j=0; j<n; j++)
            {
                d[i][j]= 0;
                for(p=0; p<n; p++)  d[i][j]+= temp[i][p]*s1[p][j];
            }
        }

        for(i=0; i<n; i++)
        {
            for(j=0; j<n; j++)
            {
                temp[i][j]= 0;
                for(p=0; p<n; p++)  temp[i][j]+= s[i][p]*s1[p][j];
            }
        }

        for(i=0; i<n; i++)
        {
            for(j=0; j<n; j++)  s[i][j]= temp[i][j];
        }

        for(i=0; i<n; i++)
        {
            for(j=0; j<n; j++)
            {
                if(i!=j)
                    if(fabs(d[i][j]) > zero) flag= 1;
            }
        }
    }
    while(flag==1);

    printf("The eigenvalues are:\n\n");
    double val=0;
    for(i=0; i<n; i++)
    {
        int point = 0;
        val=d[i][i];
        printf("%8.4lf ",val);
        for(indx_point = 0; indx_point < num_of_index; indx_point++)
        {
            if(abs(eigen[indx_point]-val) < 1e-4)
            {
                point = 1;
                break;
            }
        }

        if(point == 0)
        {
            eigen[num_of_index]=val;
            num_of_index++;
        }

    }

    printf("\n\nThe corresponding eigenvectors are:\n\n");

    int r=0,c=0;

    for(j=0; j<n; j++)
    {
        printf("(");
        for(i=0; i<n-1; i++)
        {
            printf("% 8.4lf,",s[i][j]);
            svd[r][c]=s[i][j];
            c++;
        }
        printf("%8.4lf )^T\n",s[n-1][j]);
        svd[r][c]=s[n-1][j];
        r++;
        c=0;
    }
    printf("\n");
}

/*
Enter the rows and column of the matrix: 3 2
Enter the Matrix:
1 1
0 1
-1 1

The given matrix 'A' is :
____________________________

  1.0000   1.0000
  0.0000   1.0000
 -1.0000   1.0000

Transpose matrix(A^T):
__________________________

  1.0000   0.0000  -1.0000
  1.0000   1.0000   1.0000

		Computation of V:
	________________________________

Multiplication of (A^T * A):
_____________________________________
  2.0000   0.0000
  0.0000   3.0000

The eigenvalues are:

  2.0000   3.0000

The corresponding eigenvectors are:

(  1.0000,  0.0000 )^T
(  0.0000,  1.0000 )^T


 'V' matrix is:
________________________
  1.0000   0.0000
  0.0000   1.0000

		Computation of E(sigma) :
	___________________________________

Eigenvalues are (According to Descending order):
---------------------------------------------------
  3.0000   2.0000

rank of the matrix is : 2

sigma matrix E :
____________________
  1.7321   0.0000
  0.0000   1.4142
  0.0000   0.0000



		Computation of U:
	________________________________


 Multiplication of (A * A^T):
______________________________

  2.0000   1.0000   0.0000
  1.0000   1.0000   1.0000
  0.0000   1.0000   2.0000

The eigenvalues are:

  3.0000   0.0000   2.0000

The corresponding eigenvectors are:

(  0.5774,  0.5774,  0.5774 )^T
( -0.4082,  0.8165, -0.4082 )^T
( -0.7071, -0.0000,  0.7071 )^T


 'U' matrix is:
________________________

  0.5774  -0.4082  -0.7071
  0.5774   0.8165  -0.0000
  0.5774  -0.4082   0.7071
*/
