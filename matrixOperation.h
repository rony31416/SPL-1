#ifndef MATRIX_OPERATION
#define MATRIX_OPERATION
#include <iostream>
#include <algorithm>
#include <math.h>
using namespace std;
#define STANDARD_EPSILON 2.220446049250E-16
#define EPSILON 1e-4
const int N1 = 10000;

double power(double a, int n)
{
    double res = 1;
    while (n)
    {
        if (n % 2)
        {
            res = ((res) * (a));
            n--;
        }
        else
        {
            a = ((a) * (a));
            n /= 2;
        }
    }
    return res;
}

double Determinant(double **matrix, int row, int column)
{
    if (row == 1)
    {
        return matrix[0][0];
    }
    else if (row == 2)
    {
        return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
    }
    else
    {
        double determinant = 0;
        for (int i = 0; i < row; i++)
        {
            double sign = (i % 2 == 0) ? 1 : -1;
            determinant += sign * matrix[0][i] * Determinant(matrix + i + 1, row - 1, column - 1);
        }
        return determinant;
    }
}

void Mahalanobis_distance(double **Distance, double **to, double **from, int row, int col)
{
    double row_mean[N1];
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            Distance[i][j] = 0;
        }
    }

    for (int j = 0; j < col; j++)
    {
        double value = 0;
        for (int i = 0; i < row; i++)
        {
            value += power((to[i][j] - from[i][j]), 2);
        }
        row_mean[j] = sqrt(value);
    }

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            if (i == j)
                Distance[i][j] = (1 / row_mean[j]);
        }
    }
}

double cost_calculate(double **initial_matrix, double **current_matrix, int row, int col)
{
    double total_cost = 0.0;
    double total = 0.0;

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {

            total += power((initial_matrix[i][j] - current_matrix[i][j]), 2);
        }
    }
    total_cost = sqrt(total);

    cout << "Cost is :" << total_cost << endl;

    return total_cost;
}

void multiply(double **resultMatrix, double **matrix1, double **matrix2, int rows1, int sharedDimension, int columns2)
{
    for (int i = 0; i < rows1; i++)
    {
        for (int j = 0; j < columns2; j++)
        {
            resultMatrix[i][j] = 0;
            for (int x = 0; x < sharedDimension; x++)
            {
                resultMatrix[i][j] += matrix1[i][x] * matrix2[x][j];
            }
        }
    }
}

void copy_matrix(double **sourceMatrix, double **destinationMatrix, int rows, int columns)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            destinationMatrix[i][j] = sourceMatrix[i][j];
        }
    }
}

void transpose(double **inputMatrix, double **transposeMatrix, int rows, int columns)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            transposeMatrix[j][i] = inputMatrix[i][j];
        }
    }
}

void multiply_each_element(double **resultMatrix, double **matrix1, double **matrix2, int rows, int columns)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            resultMatrix[i][j] = matrix1[i][j] * matrix2[i][j];
        }
    }
}

void divide_each_element(double **resultMatrix, double **matrix1, double **matrix2, int rows, int columns)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            resultMatrix[i][j] = matrix1[i][j] / matrix2[i][j];
        }
    }
}

void Delete_Matrix(double **matrix, int row)
{
    for (int i = 0; i < row; i++)

    {
        free(matrix[i]);
    }
}

double Make_random_number()
{
    srand(time(NULL));

    double random_number = rand() / (double)RAND_MAX;

    if (random_number < 0)
    {
        random_number = random_number * (-1);
    }
    return random_number;
}
#endif
