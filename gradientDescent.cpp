#include<iostream>
using namespace std;

//gradientDescent function without parameter

void gradientDescent()
{
    double *matrix[N];
    int col,row,i,j,k;

    printf("Enter the number of row and column : ");
    scanf("%d%d",&row,&col);

    for(i = 0 ; i < row ; i++)
    {
        matrix[i] = (double *)malloc(col *sizeof(double));
    }

    printf("Enter Matrix :" );

    for(i = 0 ; i < row ; i++)
    {
        for(j = 0 ; j <  col ; j++)
        {
            cin>>matrix[i][j];
        }
    }

    printf("Enter dimension: ");
    scanf("%d",&k);

    printf("Matrix broken and initialized using Gaussian dist: ");
    double *W[N], *H[N];

    for(i = 0 ; i < row ; i++)
    {
        W[i] = (double *)malloc(k* sizeof(double));
    }
    for(i = 0 ; i < k ; i++)
    {
        H[i] = (double *)malloc(col *sizeof(double));
    }

    //generating random number for matrix W
    for (i = 0; i < row; i++)
    {
        for (j = 0; j < k; j++)
        {
            W[i][j] = Rand_number_generator();
        }
    }

    //generating random number for matrix H
    for (i = 0; i < k; i++)
    {
        for (j = 0; j < col; j++)
        {
            H[i][j] = Rand_number_generator();
        }
    }

    printf("Print broken down matrices:\n");

    double *V[N];// V[N] matrix for storing W*H
    for (i = 0; i < row; i++)
    {
        V[i] = (double *)malloc(col * sizeof(double));
    }
    multiply(V, W, H, row, k, col);


}



void gradientDescent(double **resultMatrix,double **A,double **B,int row,int k,int col)
{
    int i,j;
    for(i = 0 ; i < row ; i++)
    {
        for(j = 0 ; j < k ; j++)
        {
            A[i][j] = Random_number_generator();
        }
    }

    for(i = 0 ; i < k ; i++)
    {
        for(j = 0 ; j < col ; j++)
        {
            B[i][j] = Random_number_generator();
        }
    }

    double *V[N];
    for(i = 0 ; i < row ; i++)
    {
        v[i] = (double*)malloc(col *sizeof(double));
    }

}

