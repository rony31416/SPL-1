#ifndef PRINT_LIBRARY_H
#define PRINT_LIBRARY_H
#include<iostream>
#include<algorithm>
#include "printOperation.h"

using namespace std;

void print_two_matrix(double **m1, double **m2, int m, int k, int n)
{

    printf("First matrix=\n");
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < k; j++)
        {
            printf("%lf\t", m1[i][j]);
        }
        cout << endl;
    }
    printf("Second matrix=\n");

    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%lf\t", m2[i][j]);
        }
        cout << endl;
    }
    cout << endl;
}
// when we print a declared 2d array
void print_matrix(double **V, int m, int n)
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%lf ", V[i][j]);
        }
        printf("\n");
    }
   
}

void greetings()
{
    printf("\t---------------------------------------------------------\n");
    printf("\t|\t\t\t\t\t\t\t|\n");
    printf("\t|\t\t\tWelcome!\t\t\t|\n");
    printf("\t|\t\tTo Bangla Topic Modelling\t\t|\n");
    printf("\t|\t\t\t\t\t\t\t|\n");
    printf("\t---------------------------------------------------------\n");

}

#endif
