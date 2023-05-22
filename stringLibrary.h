#ifndef STRINGOPERATIONS_H
#define STRINGOPERATIONS_H
#include<iostream>
#include<algorithm>

using namespace std;

int len(string str)
{
    int length = 0;
    for (int i = 0; str[i] != '\0'; i++)
    {
        length++;
    }
    return length;
}

int countElements(string str[])
{
    int count = 0;
    int i = 0;
    while (!str[i].empty())
    {
        count++;
        i++;
    }
    return count;
}
//---------------------------------------------------------------
//Rabin-Karp Algorithm for Pattern Searching
int stringPatternSearch(string text,string pattern)
{

    const int BASE = 256;
    const int MOD = 1e9 + 7;

    // pattern hash koto?
    long long pattern_hash = 0;
    for (int i = 0; i < pattern.size(); ++i)
    {
        int new_char = pattern[i] - 'a' + 1;
        pattern_hash = (pattern_hash * BASE + new_char) % MOD;
    }

    long long text_window_hash = 0;
    for (int i = 0; i < pattern.size(); ++i)
    {
        int new_char = text[i] - 'a' + 1;
        text_window_hash = (text_window_hash * BASE + new_char) % MOD;
    }

    // power = BASE^(|pattern|-1)
    long long power = 1;
    for (int i = 0; i < (int) pattern.size() - 1; ++i)
    {
        power = power * BASE % MOD;
    }

    // text er surur 3 size window ase
    for (int i = 0, j = (int) pattern.size() - 1; j < text.size(); ++i, ++j)
    {
        if (text_window_hash == pattern_hash)
        {
            return i;
        }

        // leftmost char ta baad dite hobe
        int out_char = text[i] - 'a' + 1;
        // here power = BASE^(|pattern|-1)
        text_window_hash = (text_window_hash - out_char * power) % MOD;
        if (text_window_hash < 0) text_window_hash += MOD;

        text_window_hash = text_window_hash * BASE % MOD;

        if (j + 1 < text.size())
        {
            int in_char = text[j + 1] - 'a' + 1;
            text_window_hash = (text_window_hash + in_char) % MOD;
        }
    }

    return -1;
}
//-----------------------------------------------------------
//KMP Algorithm for Pattern Searching
int* computeLPS(string pattern)
{
    int patternLength = pattern.size();
    int* lps = new int[patternLength];
    lps[0] = 0;
    int k = 0;
    for (int i = 1; i < patternLength; i++)
    {
        while (k > 0 && pattern[k] != pattern[i])
        {
            k = lps[k-1];
        }
        if (pattern[k] == pattern[i])
        {
            k++;
        }
        lps[i] = k;
    }
    return lps;
}

int stringFind(string text, string pattern)
{
    int position = -1;
    int* lps = computeLPS(pattern);
    int matchedIndex = 0;
    for (int currentIndex = 0; currentIndex < text.length(); currentIndex++)
    {
        while (matchedIndex > 0 && pattern[matchedIndex] != text[currentIndex])
        {
            matchedIndex = lps[matchedIndex - 1];
        }
        if (pattern[matchedIndex] == text[currentIndex])
        {
            matchedIndex++;
        }
        if (matchedIndex == len(pattern) )
        {
            position = currentIndex - (len(pattern) - 1);
            matchedIndex = lps[matchedIndex - 1];
        }
    }
    return position;
}
//---------------------------------------------------------------

string get_substring(const string& str, int start, int end)
{
    string result;
    for (int i = start; i < end; ++i)
    {
        result += str[i];
    }
    return result;
}



string replaceFirstOccurrence(string inputString, string target, string replacement)
{
    string result = "";
    int targetIndex = stringFind(inputString, target);
    for(int i = 0; i < targetIndex; i++)
        result += inputString[i];

    int remainingChars = 1 + inputString.length() - result.length() - target.length();

    for(int i = 0; i < replacement.length(); i++)
        result += replacement[i];

    for(int i = inputString.length() - remainingChars; i < inputString.length(); i++)
        result += inputString[i];

    return result;
}

#endif

