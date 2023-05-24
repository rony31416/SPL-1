#include <bits/stdc++.h>
#include <string>
#include <fstream>
#include <algorithm>
#include <sstream>
#include "stringLibrary.h"
#include "processOperation.h"
#include "printOperation.h"
#include "factorization_method.h"


using namespace std;

int main()
{

    greetings();

    storeText();
    storeSuffix();

    Tokenization();
    cout<<"Number of word : ";
    cout<<countElements(words)<<endl;
    stopWordRemove();

    cout<<"Number of word after removing stop word : ";
    cout<<countElements(tokenizedWords)<<endl;
   // print(tokenizedWords);
    
    gradientDescent();


    return 0;
}
