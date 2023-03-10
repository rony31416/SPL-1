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
    fstream f;
    f.open("write.txt");

    for(int i = 0 ; i < countElements(s) ; i++){
        cout<<s[i]<<"\n";
        f<<s[i]<<"\n";

    }
    f<<"-------------------------------\n";
    cout<<"------------------------------\n";
    f.close();
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
        string DARI1 = "???";
        string DARI2 = "???";

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

void stopWordRemove() {
  vector<string> result;
  int n = countElements(words);
  int m = countElements(stopWord);

  for(int i = 0 ; i < n ; i++)
  {
      bool matching = true;
      for(int j = 0 ; j < m ; j++)
      {
          if(words[i] == stopWord[j])
          {
              matching = false;
              break;
          }
      }
      if(matching)
      {
          result.push_back(words[i]);
      }
  }

  for(int i = 0 ; i < N ; i++)
  {
      words[i].clear();
  }

  for(int i = 0 ; i < result.size() ; i++)
  {
      words[i] = result[i];
  }

}


int main()
{
    storeText();
    storeSuffix();

    Tokenization();
    cout<<"Number of word : ";
    cout<<countElements(words)<<endl;
    stopWordRemove();

    cout<<"Number of word after removing stop word : ";
    cout<<countElements(words)<<endl;
    print(words);


    return 0;
}
