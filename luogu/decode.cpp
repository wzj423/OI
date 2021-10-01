/**
luogu P1071
*/
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>

#include <cstring>
#include <cmath>
#include <string>

using namespace std;
string s,t,str;
int M[30];
int vis[30];
void fail()
{
    cout<<"Failed"<<endl;
    exit(0);
}
int main()
{
    std::ios::sync_with_stdio(false);
    cin>>s>>t>>str;
    for(int i=s.size()-1; i>=0; i--)

        if(M[s[i]-'A']==0||M[s[i]-'A']==t[i])
            {
                M[s[i]-'A']=t[i];
                if(M[s[i]-'A']==0)
                vis[t[i]-'A']++;
            }
        else
            fail();
    for(int i=1; i<26; i++)
        if(M[i]==0||vis[M[i]-'A']>1)
            fail();
    for(int i=str.size()-1; i>=0; i--)
        if(M[str[i]-'A']!=0)
            str[i]=M[str[i]-'A'];
        else
            fail();
    cout<<str<<endl;
    return 0;
}
