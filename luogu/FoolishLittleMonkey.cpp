#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>

#include <string>
#include <cstring>
#include <cmath>
#include <cctype>

#include <algorithm>
#include <functional>
#include <queue>

using namespace std;
string word;
int bud[30];
int Maxium=0,Minium=11110;
bool isOK(int x)
{
    int up=sqrt(x);
    if(x==1||x==0)
    return false;
    for(int i=2;i<=up;i++)
    {
        if(x%i==0)
            return false;
    }
        return true;
}
int main()
{
    cin>>word;
    int len=word.size();
    for (int i=0;i<len;i++)
    {
        bud[word[i]-'a']++;
    }
    sort(bud,bud+26);
    Maxium=bud[25];
    int __i=0;
    while(bud[__i]==0) __i++;
    Minium=bud[__i];
    //cout<<Maxium<<Minium<<endl;
    int result=Maxium-Minium;
    //cout<<result<<endl;
    if(isOK(result))
    {
        cout<<"Lucky Word\n"<<result<<endl;
    }
    else
    {
        cout<<"No Answer\n"<<0<<endl;
    }
    return 0;
}
