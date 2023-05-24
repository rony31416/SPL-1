#pragma once
#include <bits/stdc++.h>
using namespace std;

void TF(double **TF_Matrix, string *tokenizedWords, 
        vector<pair<int, pair<string, int>>> &freqVector, map<int, int> &wordMap, int n, int num_sentence);

void IDF(double **IDF_Matrix, vector<pair<int, pair<string, int>>> &freqVector,
         map<string, int> &num_sentence_contain_word, int num_sentence, int num_word);

void transpose_matrix(double **TF_Matrix, double **Trans_TF_IDF, int num_sentence, int rootWord);

void TFIDF(double **TF_IDF, double **Trans_TF_IDF, double **IDF_Matrix, int num_sentence, int rootWord);