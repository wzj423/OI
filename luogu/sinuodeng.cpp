//这题用来练习STL是不错的
//可以让你的打表判断看起来高级一点
#include <map>
#include <set>
#include <cstdio>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
bool cmp (string a,string b)
{
    return a > b;
}
int main()
{
    map<string,string> tra;
    vector<string> word1;
    vector<string> word2;
    set<string> words1;
    set<string> words2;
    string ss;
    string s;
    words1.insert("a");words1.insert("both");words1.insert("another");
    words1.insert("first");words1.insert("second");words1.insert("third");
    words1.insert("one");words1.insert("two");words1.insert("three");words2.insert("four");
    words2.insert("five");words2.insert("six");words2.insert("seven");words2.insert("eight");
    words2.insert("nine");words2.insert("eleven");words2.insert("twelve");
    words2.insert("thirteen");words2.insert("fourteen");words2.insert("fifteen");words2.insert("sixteen");
    words2.insert("seventeen");words2.insert("eighteen");words2.insert("nineteen");
    tra["a"] = "01";tra["both"] = "04";tra["third"] = "09";
    tra["first"] = "01";tra["second"] = "04";tra["another"] = "01";
    tra["one"] = "01";tra["two"] = "04";tra["three"] = "09";tra["four"] = "16";
    tra["five"] = "25";tra["six"] = "36";tra["seven"] = "49";tra["eight"] = "64";
    tra["nine"] = "81";tra["eleven"] = "21";tra["twelve"] = "44";
    tra["thirteen"] = "69";tra["fourteen"] = "96";tra["fifteen"] = "25";tra["sixteen"] = "56";
    tra["seventeen"] = "89";tra["eighteen"] = "24";tra["nineteen"] = "61";
    for (int i = 0;i < 6;i ++)
    {
        cin >> ss;
        if (words1.count(ss))
        word1.push_back(tra[ss]);
        if (words2.count(ss))
        word2.push_back(tra[ss]);
    }
    //if (word1.empty()) cout << "NO!" <<endl;
    //if (word2.empty()) cout << "NO!" <<endl;
    //s =    word1.back(); cout << s;
    if (word1.empty() && word2.empty())
    {
        printf("0");
        return 0;
    }
    if (!word1.empty());
    {
        sort(word1.begin(),word1.end(),cmp);
        cout << (word1.back())[1];
        word1.pop_back();
    }
    while (!word1.empty())
    {
        s = word1.back();
        word2.push_back(s);
        word1.pop_back();
    }
    sort(word2.begin(),word2.end(),cmp);
    while (!word2.empty())
    {
        cout << (word2.back());
        word2.pop_back();
    }
    return 0;
}
