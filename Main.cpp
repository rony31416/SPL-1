#include <bits/stdc++.h>
#include <string>
#include <fstream>
#include <algorithm>
#include <sstream>
#include "stringLibrary.h"
#include "processOperation.h"
#include "printOperation.h"
#include "factorization_method.h"
#include "tfIdfOperation.h"

using namespace std;

int main()
{

    greetings();
    cout<<"Enter file name: \n";
    string fileName;
    cin>>fileName;
    storeText(fileName);
    storeSuffix();

    Tokenization();
    cout << "Number of word : ";
    cout << countElements(words) << endl;
    stopWordRemove();

    cout << "Number of word after removing stop word : ";
    int rootWord = countElements(tokenizedWords);
    cout << rootWord << endl
         << endl;

    // TF start
    double *TF_Matrix[N];
    int num_sentence = total_word_in_sentence.size();
    cout << "sentence :" << num_sentence << "\n";
    for (int i = 0; i < rootWord; i++)
    {
        TF_Matrix[i] = (double *)malloc(num_sentence * sizeof(double));
    }

    TF(TF_Matrix, tokenizedWords, freq_in_sentence, total_word_in_sentence, countElements(tokenizedWords), num_sentence);
    // print_matrix(TF_Matrix, rootWord, num_sentence);

    // IDF start
    double *IDF_Matrix[N];
    for (int i = 0; i < rootWord; i++)
    {
        IDF_Matrix[i] = (double *)malloc((int)1 * sizeof(double));
    }
    IDF(IDF_Matrix, freq_in_sentence, num_sentence_contain_word, num_sentence, countElements(tokenizedWords));
    // print_matrix(IDF_Matrix,rootWord,1);

    // TF_IDF calculate
    double *Trans_TF_IDF[N];
    for (int i = 0; i < num_sentence; i++)
    {
        Trans_TF_IDF[i] = (double *)malloc(rootWord * sizeof(double));
    }

    transpose_matrix(TF_Matrix, Trans_TF_IDF, num_sentence, rootWord);
    // print_matrix(Trans_TF_IDF, num_sentence, rootWord);

    cout << "\n\nTFIDF\n";

    double *TF_IDF[N];
    for (int i = 0; i < num_sentence; i++)
    {
        TF_IDF[i] = (double *)malloc(rootWord * sizeof(double));
    }
    TFIDF(TF_IDF, Trans_TF_IDF, IDF_Matrix, num_sentence, rootWord);
    // print_matrix(TF_IDF, num_sentence, rootWord);

    int choice;
    while (true)
    {
        cout << "Enter your choice to print: " << endl;
        cout << "1. RootWord" << endl;
        cout << "2. TF" << endl;
        cout << "3. IDF" << endl;
        cout << "4. TF-IDF" << endl;
        cout << "5. Exit" << endl;

        cin >> choice;
        if (choice == 1)
        {
            for (int i = 0; i < rootWord; i++)
            {
                cout << tokenizedWords[i] << "  ";
            }
            cout << "\n";
        }
        else if (choice == 2)
        {
            printf("TF matrix : \n");
            print_matrix(TF_Matrix, rootWord, num_sentence);
        }
        else if (choice == 3)
        {
            printf("IDF matrix\n");
            print_matrix(IDF_Matrix, rootWord, 1);
        }
        else if (choice == 4)
        {
            printf("TF-IDF matrix\n");
            print_matrix(TF_IDF, num_sentence, rootWord);
        }
        else if (choice == 5)
        {
            break;
        }
        else
        {
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    int k;
    cout << "dimention for factorized TFIDF Matrix: ";
    cin >> k;

    double *W_Mat[N], *H_Mat[N];
    int i,j;
    for (i = 0; i < num_sentence; i++)
    {
        W_Mat[i] = (double *)malloc(k * sizeof(double));
    }
    for (i = 0; i < k; i++)
    {
        H_Mat[i] = (double *)malloc(rootWord * sizeof(double));
    }

    gradientDescent(TF_IDF,W_Mat,H_Mat, num_sentence, rootWord, k);
    fclose(stdout);

    
    return 0;
}
