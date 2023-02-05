#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <sstream>
#include "stringLibrary.h"
using namespace std;
#define N 1000


string words[N];
string Bochon_suffix[N];
string Bivokti_suffix[N];
string quantifier[N];
string stopWord[N];
string tags[N];
string tokenizedWords[N];


void print(string s[])
{
    for(int i = 0 ; i < countElements(s) ; i++) cout<<s[i]<<"\n";

    cout<<"------------------------------\n";
}

void openFile(ifstream &FILE, string fileName)
{
    FILE.open(fileName);
    if(!FILE.is_open())
    {
        cout<<"Failed to open file\n";
    }

}

void processFile_wordByword(ifstream &FILE)
{
    string line,word;
    istringstream iss;
    int i = 0;
    while(!FILE.eof())
    {
        getline(FILE,line);
        if(FILE.good())
        {
            iss.clear();
            iss.str(line);
            while(iss.good())
            {
                iss>>word;
                words[i] = word;
                i++;
            }
        }
    }
}

void storeText()
{
    ifstream FILE;
    openFile(FILE,"input.txt");
    processFile_wordByword(FILE);

    FILE.close();
}

void storeSuffixFromTextFile(string name)
{
    ifstream FILE;
    string s;
    int i = 0;

    if(name == "bochon")
    {
        openFile(FILE,"BochonSuffix.txt");
        while(getline(FILE,s))
        {
            Bochon_suffix[i] = s;
            i++;
        }
        FILE.close();
    }
    else if(name == "bivokti")
    {
        openFile(FILE,"BivoktiSuffix.txt");
        while(getline(FILE,s))
        {
            Bivokti_suffix[i] = s;
            i++;
        }
        FILE.close();
    }
    else if(name == "quantifier")
    {
        openFile(FILE,"Quantifiers.txt");
        while(getline(FILE,s))
        {
            quantifier[i] = s;
            i++;
        }
        FILE.close();
    }
    else if(name == "stopword")
    {
        openFile(FILE,"stopWords.txt");
        while(getline(FILE,s))
        {
            stopWord[i] = s;
            i++;
        }
        FILE.close();
    }
}

void storeSuffix()
{
    storeSuffixFromTextFile("bochon");
    storeSuffixFromTextFile("bivokti");
    storeSuffixFromTextFile("quantifier");
    storeSuffixFromTextFile("stopword");
}

void Tokenization()
{
    int k = 0;

    int n = countElements(words);
    for (int i = 0; i < n; i++)
    {
        char* updatedStr = new char[N];
        string DARI1 = "।";
        string DARI2 = "৷";

        int find1 = stringPatternSearch(words[i],DARI1);
        int find2 = stringPatternSearch(words[i],DARI2);

        if(find1 != -1 || find2 != -1)
        {
            if(find1 != -1)
                words[i] = replaceFirstOccurrence(words[i],DARI1,"#");
            else
                words[i] = replaceFirstOccurrence(words[i],DARI2,"#");
        }

        int idx = 0;
        for (int j = 0; j < words[i].size(); j++)
        {
            if (!ispunct(words[i][j]) && words[i][j]!='#')
                updatedStr[idx++] = words[i][j];
        }

        for(int j = 0; j < idx; j++)
            tokenizedWords[k].push_back(updatedStr[j]);

        k++;
    }
}

int main()
{
    storeText();
    storeSuffix();

    Tokenization();

    print(words);
    print(tokenizedWords);


    return 0;
}
