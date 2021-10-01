/**
玩具谜题
Luogu P1563
*/
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>

#include <cstring>
#include <cmath>
#include <cctype>
#include <string>

#include <algorithm>
#include <queue>
#include <stack>

using namespace std;
typedef long long LL;
struct peo
{
    int pos;
    string name;
} P[10010];
int N,M;
// code

void init()
{
    cin>>N>>M;
    //cout<<N<<" "<<M<<endl;
    for(int i=0; i<N; ++i)
    {
        cin>>P[i].pos>>P[i].name;
        //cout<<P[i].pos<<" "<<P[i].name<<endl;
    }
    //cin>>M;
}

void work()
{
    int curPos=0;
    int direct,step;
    for(int i=1; i<=M; ++i)
    {
        cin>>direct>>step;
        if(direct==P[curPos].pos)
        {
            curPos=(curPos-step);
        }
        else
        {
            curPos=(curPos+step);
        }
        while(curPos<0)
            curPos+=N;
        curPos%=N;
        //cout<<P[curPos].name<<endl;
    }
    cout<<P[curPos].name<<endl;
}
int main()
{
    init();
    work();
    return 0;
}


