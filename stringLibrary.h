#ifndef STRINGLIBRARY_H
#define STRINGLIBRARY_H
#include<iostream>
#include<algorithm>
using namespace std;

int strlen(string str)
{
    int length = 0;
    for (int i = 0; str[i] != '\0'; i++)
    {
        length++;
    }
    return length;
}




#endif
