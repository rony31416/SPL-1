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
        map<int, int> &wordMap, int n, int num_sentence)
{

    /*
        set<int> numberOfsentence;
        for (const auto &element : freqVector)
        {
            int firstValue = element.first;
            string secondFirstValue = element.second.first;
            int secondSecondValue = element.second.second;
            // cout << "First: " << firstValue << ", Second First: " << secondFirstValue << ", Second Second: " << secondSecondValue << endl;
            numberOfsentence.insert(firstValue);
        }
    */
    int totalSentence = num_sentence;

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
  //  cout << "okk\n";
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < totalSentence; j++)
        {
            TF_Matrix[i][j] = tf_matrix[i][j];
        }
    }
}

void IDF(double **IDF_Matrix, vector<pair<int, pair<string, int>>> &freqVector, map<string, int> &num_sentence_contain_word, int num_sentence, int num_word)
{
    double *idf_matrix[num_word + 10];
    int i, j;
    for (i = 0; i < num_word; i++)
    {
        idf_matrix[i] = (double *)malloc((int)1 * sizeof(double));
    }
    for (i = 0; i < num_word; i++)
    {
        double totalSentence = (double)num_sentence;
        string s = freqVector[i].second.first;
        int freq = num_sentence_contain_word[s];
        double contain = (double)freq;
        idf_matrix[i][0] = log10(num_sentence / freq);
    }

    for (int i = 0; i < num_word; i++)
    {
        IDF_Matrix[i][0] = idf_matrix[i][0];
        // cout<<idf_matrix[i][0]<<"\n";//\t"<<num_sentence_contain_word[freqVector[i].second.first]<<"\n";
    }
}

void transpose_matrix(double **TF_Matrix, double **Trans_TF_IDF, int num_sentence, int rootWord)
{
    for (int i = 0; i < num_sentence; i++)
    {
        for (int j = 0; j < rootWord; j++)
        {
            Trans_TF_IDF[i][j] = TF_Matrix[j][i];
        }
    }
}

void TFIDF(double **TF_IDF, double **Trans_TF_IDF, double **IDF_Matrix, int num_sentence, int rootWord)
{
    for (int i = 0; i < num_sentence; i++)
    {
        for (int j = 0; j < rootWord; j++)
        {
            TF_IDF[i][j] = Trans_TF_IDF[i][j] * IDF_Matrix[j][0];
        }
    }
}

#endif