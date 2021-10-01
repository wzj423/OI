/**
Luogu P1328
NOIp2014 TG T1
*/
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>

#include <cmath>
#include <cctype>
#include <cstring>
#include <string>

#include <algorithm>
#include <queue>
#include <stack>

using namespace std;
int Map[5][5]=
{
    0,0,1,1,0,
    1,0,0,1,0,
    0,1,0,0,1,
    0,0,1,0,1,
    1,1,0,0,0,
};
int N,Na,Nb;
int Ra[210],Rb[210];
int Pa,Pb;
int Sa,Sb;
int main()
{
    std::ios::sync_with_stdio(false);
    cin>>N>>Na>>Nb;
    for(int i=0;i<Na;i++)
        cin>>Ra[i];
    for(int i=0;i<Nb;i++)
        cin>>Rb[i];
    for(int i=1;i<=N;i++)
    {
        Sa+=Map[Ra[Pa]][Rb[Pb]];
        Sb+=Map[Rb[Pb]][Ra[Pa]];
        Pa=(Pa+1)%Na;
        Pb=(Pb+1)%Nb;
    }
    cout<<Sa<<" "<<Sb<<endl;
    return 0;
}
