#ifndef MATRIX_OPERATION
#define MATRIX_OPERATION
#include <iostream>
#include <algorithm>
#include <math.h>
using namespace std;
#define STANDARD_EPSILON 2.220446049250E-16
#define EPSILON 2e-4
#define e 2.71828
const double sig = 5.0;
const double Mu = 10.0;

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

void Normalization(double **matrix, int row, int col)
{
    double avg, sd, var = 0.0, sum = 0.0;

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            sum += matrix[i][j];
        }
    }
    avg = sum / (row * col);

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            var += power((matrix[i][j] - avg), 2);
        }
    }
    var = var / ((row * col) - 1);
    sd = sqrt(var);

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            matrix[i][j] = matrix[i][j] / sd;
        }
    }
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

bool is_same_matrix(double **sourceMatrix, double **destinationMatrix, int rows, int columns)
{
     bool ok = true;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            if(destinationMatrix[i][j] != sourceMatrix[i][j])
            {
                ok = false;
                return ok;
            }
        }
    }
    return ok;
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

double Random_generator(double minValue, double maxValue)
{
    double range = (maxValue - minValue);
    double div = (double)RAND_MAX / range; // 32767 is the max value of rand()
    return minValue + ((double)rand() / div);
}

double Exponential_Find() // e^(-0.5*x^2)
{
    double Power, x;
    x = Random_generator(-8.0, 10.0);       // random number generator within -10.0 to 10.0
    Power = ((x - sig) / Mu); // x-sigma/Mu is the power
    double half = -0.5;
    Power = pow((half * Power), 2.0); // e^-0.5*power^2
    return pow(e, Power);
}

double Make_random_number()
{
    /*srand(time(NULL));

    double random_number = rand() / (double)RAND_MAX;

    if (random_number < 0)
    {
        random_number = random_number * (-1);
    }*/
      return (0.398922804 / sig) * Exponential_Find();
}
#endif
