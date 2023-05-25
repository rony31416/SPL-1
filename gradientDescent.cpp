#include <iostream>
#include "matrixOperation.h"
#include "printOperation.h"
#include "factorization_method.h"

using namespace std;

void update_Matrix_H(double **W, double **H, double **V, int row, int k, int col)
{
    double *transpose_Matrix_W[N1];
    double *numerator_Matrix[N1];

    for (int i = 0; i < k; i++)
    {
        transpose_Matrix_W[i] = (double *)malloc(row * sizeof(double));
    }

    for (int i = 0; i < k; i++)
    {
        numerator_Matrix[i] = (double *)malloc(col * sizeof(double));
    }

    transpose(W, transpose_Matrix_W, row, k); // calculating transpose of W

    multiply(numerator_Matrix, transpose_Matrix_W, V, k, row, col); // WT*V

    double *Temp_matrix[N1]; // Temo_Matrix for storing WT*W in
    double *denominator[N1];

    for (int i = 0; i < k; i++)
        Temp_matrix[i] = (double *)malloc(k * sizeof(double));
    for (int i = 0; i < k; i++)
        denominator[i] = (double *)malloc(col * sizeof(double));

    multiply(Temp_matrix, transpose_Matrix_W, W, k, row, k); // WT*W
    multiply(denominator, Temp_matrix, H, k, k, col);        //(WT*W)*H
    double *updated_H[N1];                                   // the term that is to be multiplied with H

    for (int i = 0; i < k; i++)
        updated_H[i] = (double *)malloc(col * sizeof(double));
    divide_each_element(updated_H, numerator_Matrix, denominator, k, col);

    double *ans_H[N1];

    for (int i = 0; i < k; i++)
        ans_H[i] = (double *)malloc(col * sizeof(double));
    multiply_each_element(ans_H, H, updated_H, k, col);

    copy_matrix(ans_H, H, k, col);
    Delete_Matrix(ans_H, k);
    Delete_Matrix(updated_H, k);
    Delete_Matrix(denominator, k);
    Delete_Matrix(Temp_matrix, k);
    Delete_Matrix(numerator_Matrix, k);
    Delete_Matrix(transpose_Matrix_W, k);
}
void update_Matrix_W(double **W, double **H, double **V, int row, int k, int col)
{
    double *transpose_H[N1], *numerator[N1];

    for (int i = 0; i < col; i++)
    {
        transpose_H[i] = (double *)malloc(k * sizeof(double));
    }

    transpose(H, transpose_H, k, col);

    for (int i = 0; i < row; i++)
    {
        numerator[i] = (double *)malloc(k * sizeof(double));
    }

    multiply(numerator, V, transpose_H, row, col, k);

    double *HHT[N1];

    for (int i = 0; i < k; i++)
        HHT[i] = (double *)malloc(k * sizeof(double));

    multiply(HHT, H, transpose_H, k, col, k);

    double *denominator_Matrix[N1];
    for (int i = 0; i < row; i++)
    {
        denominator_Matrix[i] = (double *)malloc(k * sizeof(double));
    }

    multiply(denominator_Matrix, W, HHT, row, k, k);

    double *changes_W_Matrix[N1];

    for (int i = 0; i < row; i++)
    {
        changes_W_Matrix[i] = (double *)malloc(k * sizeof(double));
    }

    divide_each_element(changes_W_Matrix, numerator, denominator_Matrix, row, k);

    double *ans_W[N1];

    for (int i = 0; i < row; i++)
    {
        ans_W[i] = (double *)malloc(k * sizeof(double));
    }

    multiply_each_element(ans_W, W, changes_W_Matrix, row, k);
    copy_matrix(ans_W, W, row, k);
    Delete_Matrix(ans_W, row);
    Delete_Matrix(changes_W_Matrix, row);
    Delete_Matrix(denominator_Matrix, row);
    Delete_Matrix(HHT, k);
    Delete_Matrix(transpose_H, col);
    Delete_Matrix(numerator, row);
}

// gradientDescent function without parameter

void gradientDescent(double **TFIDF, double **W_Mat, double **H_Mat, int row, int col, int k)
{
    //print_matrix(TFIDF,row,col);
    double *matrix[N1];
    int i, j;

    for (i = 0; i < row; i++)
    {
        matrix[i] = (double *)malloc(col * sizeof(double));
    }

    for (i = 0; i < row; i++)
    {
        for (j = 0; j < col; j++)
        {
            matrix[i][j] = TFIDF[i][j];
        }
    }
    Normalization(matrix, row, col);
    print_matrix(matrix, row, col);
    double *W[N1], *H[N1];

    for (i = 0; i < row; i++)
    {
        W[i] = (double *)malloc(k * sizeof(double));
    }
    for (i = 0; i < k; i++)
    {
        H[i] = (double *)malloc(col * sizeof(double));
    }

    // generating random number for matrix W
    for (i = 0; i < row; i++)
    {
        for (j = 0; j < k; j++)
        {
            W[i][j] = Make_random_number();
        }
    }

    // generating random number for matrix H
    for (i = 0; i < k; i++)
    {
        for (j = 0; j < col; j++)
        {
            H[i][j] = Make_random_number();
        }
    }

    double *V[N1]; // V[N] matrix for storing W*H
    for (i = 0; i < row; i++)
    {
        V[i] = (double *)malloc(col * sizeof(double));
    }
    multiply(V, W, H, row, k, col);

    int iteration = 1;
    double cost = cost_calculate(matrix, V, row, col);
    double initial_cost = cost;
    double prev_cost = 0;
    printf("Updating costs: \n");
    while (cost > EPSILON)
    {
        if ((iteration % 2) == 0)
        {
            update_Matrix_H(W, H, matrix, row, k, col);
        }
        else
        {
            update_Matrix_W(W, H, matrix, row, k, col);
        }
        iteration++;
        multiply(V, W, H, row, k, col);
        cost = cost_calculate(matrix, V, row, col);
        cout << "cost : " << cost << "\t"
             << "at iteration : " << iteration << "\n";
        if (fabs(prev_cost - cost) <= EPSILON)
        {
            printf("Find relative minima\n");
            break;
        }
        else
        {
            prev_cost = cost;
        }
    }

    print_two_matrix(W, H, row, k, col);
    copy_matrix(W, W_Mat, row, k);
    copy_matrix(H, H_Mat, k, col);

    int choice2;
    while (true)
    {
        cout << "Enter your choice to print :\n";
        cout << "1.W Matrix\n";
        cout << "2.H Matrix\n";
        cout<<  "3.W*H Matrix\n";
        cout << "4.Exit\n";
        cin >> choice2;
        if (choice2 == 1)
        {
            printf("W Matrix\n");
            print_matrix(W_Mat, row, k);
        }
        else if (choice2 == 2)
        {
            printf("H Matrix\n");
            print_matrix(H_Mat, k, col);
        }
        else if (choice2 = 3)
        {
            printf("TF-IDF\n");
            print_matrix(TFIDF,row,col);
            printf("W*H Matrix\n");
            printf("sentence X feature --->>\n");
            multiply(TFIDF,W_Mat,H_Mat,row,k,col);
            print_matrix(TFIDF,row,col);
        }
        else
        {
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    freopen("result_nmf.txt", "w", stdout);
    printf("The beginning cost was: %lf\n", initial_cost);
    printf("The final cost was: %lf\n", cost);
    printf("Total number of iterations before arriving at result: %d\n", iteration);
    printf("The broken down matrix:\n ");
    print_two_matrix(W, H, row, k, col);
    fclose(stdout);
}

void gradientDescentMethod(double **matrix, double **A, double **B, int row, int k, int col)
{
    int i, j;
    for (i = 0; i < row; i++)
    {
        for (j = 0; j < k; j++)
        {
            A[i][j] = Make_random_number();
        }
    }

    for (i = 0; i < k; i++)
    {
        for (j = 0; j < col; j++)
        {
            B[i][j] = Make_random_number();
        }
    }
    double *V[N1];
    for (int i = 0; i < row; i++)
        V[i] = (double *)malloc(col * sizeof(double));

    int counter = 1;
    printf("Initial cost:\n");
    // cost function
    multiply(V, A, B, row, k, col);
    double cost = cost_calculate(matrix, V, row, col);
    double initial_cost = cost;
    double prev_cost = 0;
    printf("Updating costs:\n ");
    while (cost > 0.05)
    {

        if ((counter % 2) == 0)
        {
            update_Matrix_H(A, B, matrix, row, k, col);
        }
        else
        {
            update_Matrix_W(A, B, matrix, row, k, col);
        }
        counter++;
        multiply(V, A, B, row, k, col);
        cost = cost_calculate(matrix, V, row, col);
        if (fabs(prev_cost - cost) <= EPSILON)
        {
            break;
        }
        else
        {
            prev_cost = cost;
        }
    }
    printf("Factorization complete!\n");
}
