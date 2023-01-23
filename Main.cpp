#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
using namespace std;

void openFile(ifstream&, string);
void processFile_wordByword(ifstream &);
map<string,int> wordCount;
map<string,int> storeWord,stopWord;
map<string,int> wordAfterRemoveSw;


int main()
{
    wordCount.clear();
    storeWord.clear();
    stopWord.clear();
    wordAfterRemoveSw.clear();

    ifstream FILE;
    openFile(FILE,"input.txt");
    processFile_wordByword(FILE);
    FILE.close();



    openFile(FILE,"write.txt");
    string str,line,word;
    istringstream iss;
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
                storeWord[word]++;
            }
        }
    }

    FILE.close();

    openFile(FILE,"stopWords.txt");


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
                stopWord[word]++;
            }
        }
    }
    cout<<storeWord.size()<<"\n";
    for(auto u : storeWord) cout<<u.first<<"\n";

    FILE.close();

    fstream f;
    f.open("swRemove.txt");

    std::map<std::string, int>::iterator it = storeWord.begin();

    for(int i = 0 ; i < storeWord.size(); i++,it++)
    {
        string word = it->first;
        bool ok = false;

        //cout<<"word : "<<word<<"\n";
        for(auto  u : stopWord)
        {
            if(u.first == word)
            {
                ok = true;
                cout<<"paisi :: "<<word<<"\n";
            }
        }

        if(!ok) f<<word<<"\n";

    }
    return 0;
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
    fstream f;
    f.open("write.txt");
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
                //  cout<<word<<" ";
                wordCount[word]++;
            }
            // cout<<"\n";
        }
    }

    for(auto str : wordCount)
    {
        f<<str.first<<"\n";//<<str.second<<"\n";
    }

}
