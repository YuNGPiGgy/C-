#include "MapArray.h"
#include "SetList.h"
#include <string>
#include <iostream>
#include <fstream>
#include <iterator>

using namespace std;

int main()
{
    MapArray<string, int> sampleWords;
    SetList<string> stopWords;

    ifstream inSample("sample_doc.txt");
    ifstream inStop("stopwords.txt");

    for_each(istream_iterator<string>(inStop), istream_iterator<string>(), [&](string s1)
             {
                 stopWords.insert(s1);
             });
    for_each(istream_iterator<string>(inSample), istream_iterator<string>(), [&](string a)
    {
        transform(a.begin(), a.end(), a.begin(), ::tolower);
        string b(a);
        
        if(stopWords.find(b) == stopWords.end())
        {
            sampleWords[a] += 1;
        }
    });

    ofstream freq;
    freq.open("frequency.txt");
    for_each(sampleWords.begin(), sampleWords.end(), [&](pair <string, int> p)
    {
        freq << p.first << ": " << p.second << endl;
    });
    freq.close();	
    return 0;
}
