#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>

#include <string>
#include <cstring>
#include <cmath>
#include <cctype>
#include <ctime>

#include <algorithm>
//#define _TEST
#ifndef _TEST
    #define TEST  while(0)
#endif // _TEST
using namespace std;
struct People
{
    int index;
    int power;
};
bool cmp(People a,People b)
{
    if(a.power!=b.power)
        return a.power>b.power;
    else
        return a.index<b.index;
}
People p[20010];
int N,K;
int E[15];
int main()
{
    cin>>N>>K;
    for(int i=1;i<=10;i++)
        cin>>E[i];
    for (int i=1;i<=N;i++)
    {
        cin>>p[i].power;
        p[i].index=i;
    }
    sort(p+1,p+N+1,cmp);
    for (int i=1;i<=N;i++)
    {
        TEST cout<<p[i].power<<endl;

        p[i].power+=E[(/*p[i].power*/ i-1)%10+1];
    }
    sort(p+1,p+N+1,cmp);
    for (int i=1;i<=K;i++)
    {
        cout<<p[i].index<<" ";
    }
    cout<<endl;
    return 0;
}
