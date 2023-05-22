#ifndef MATRIX_OPERATION
#define MATRIX_OPERATION
#include<iostream>
#include<algorithm>


void multiply(double** resultMatrix, double** matrix1, double** matrix2, int rows1, int sharedDimension, int columns2)
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

void copy_matrix(double** sourceMatrix, double** destinationMatrix, int rows, int columns)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            destinationMatrix[i][j] = sourceMatrix[i][j];
        }
    }
}

void transpose(double** inputMatrix, double** transposeMatrix, int rows, int columns)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            transposeMatrix[j][i] = inputMatrix[i][j];
        }
    }
}

void multiply_element_wise(double** resultMatrix, double** matrix1, double** matrix2, int rows, int columns)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            resultMatrix[i][j] = matrix1[i][j] * matrix2[i][j];
        }
    }
}

void divide_element_wise(double** resultMatrix, double** matrix1, double** matrix2, int rows, int columns)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            resultMatrix[i][j] = matrix1[i][j] / matrix2[i][j];
        }
    }
}



