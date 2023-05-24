#ifndef PRINT_LIBRARY_H
#define PRINT_LIBRARY_H
#include <bits/stdc++.h>
#include <algorithm>
#include "tfIdfOperation.h"
using namespace std;

int repWord(vector<pair<int, pair<string, int>>> &freq, int line_number, string word)
{
    int cnt = 0;

    for (const auto &element : freq)
    {
        int firstValue = element.first;
        string secondFirstValue = element.second.first;
        int secondSecondValue = element.second.second;
        if (firstValue == line_number)
        {
            if (secondFirstValue == word)
            {
                return secondSecondValue;
            }
        }
    }
    return 0;
}

void TF(double **TF_Matrix, string *tokenizedWords, vector<pair<int, pair<string, int>>> &freqVector,
        map<int, int> &wordMap, int n)
{

    set<int> numberOfsentence;
    for (const auto &element : freqVector)
    {
        int firstValue = element.first;
        string secondFirstValue = element.second.first;
        int secondSecondValue = element.second.second;
        // cout << "First: " << firstValue << ", Second First: " << secondFirstValue << ", Second Second: " << secondSecondValue << endl;
        numberOfsentence.insert(firstValue);
    }

    int totalSentence = numberOfsentence.size();

    double *tf_matrix[n + 10];
    int i, j;
    for (i = 0; i < n; i++)
    {
        tf_matrix[i] = (double *)malloc(totalSentence * sizeof(double));
    }

    for (i = 0; i < n; i++)
    {
        for (j = 1; j <= totalSentence; j++)
        {
            double repValue = (double)repWord(freqVector, j, tokenizedWords[i]);
            double number_of_word_in_sentence = (double)wordMap[j];

            // cout<<"nemo :" <<repValue<<"\tdnemo :"<<number_of_word_in_sentence<<"\n";
            tf_matrix[i][j - 1] = repValue / number_of_word_in_sentence;
        }
    }
    cout << "okk\n";

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < totalSentence; j++)
        {
            TF_Matrix[i][j] = tf_matrix[i][j];
        }
    }
}

#endif