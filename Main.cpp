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

    storeText();
    storeSuffix();

    Tokenization();
    cout << "Number of word : ";
    cout << countElements(words) << endl;
    stopWordRemove();

    cout << "Number of word after removing stop word : ";
    int rootWord = countElements(tokenizedWords);
    cout<<rootWord<<endl;
    // print(tokenizedWords);

/*        for (const auto &element : freq_in_sentence)
    {
        int firstValue = element.first;
        string secondFirstValue = element.second.first;
        int secondSecondValue = element.second.second;
        cout << "First: " << firstValue << ", Second First: " << secondFirstValue << ", Second Second: " << secondSecondValue << endl;
       // freq_in_sentence.insert(firstValue);
    }
*/

    double *TF_Matrix[N];
    int num_of_sentence = total_word_in_sentence.size(); 
    for(int i = 0 ;  i <  rootWord ; i++)
    {
        TF_Matrix[i] = (double *)malloc( num_of_sentence* sizeof(double));
    }

    TF(TF_Matrix,tokenizedWords, freq_in_sentence, total_word_in_sentence, countElements(tokenizedWords));
    
    print_matrix(TF_Matrix,rootWord,num_of_sentence);
    
    // gradientDescent();

    return 0;
}
