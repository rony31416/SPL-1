#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
using namespace std;

void openFile(ifstream&, string);
void processFile_wordByword(ifstream &);
map<string,int> wordCount;


int main()
{
    ifstream FILE;
    openFile(FILE,"input.txt");
    processFile_wordByword(FILE);
    //int i = 1;
    for(auto u : wordCount)
    {
        cout<<u.first<<" "<<u.second<<"\n";
    }

    FILE.close();
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
                cout<<word<<" ";
                wordCount[word]++;
            }
            cout<<"\n";
        }
    }

    for(auto str : wordCount)
    {
        f<<str.first<<" "<<str.second<<"\n";
    }

}
